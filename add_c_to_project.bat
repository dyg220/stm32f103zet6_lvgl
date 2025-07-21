@echo off
setlocal enabledelayedexpansion

:: Step 1: Initialize variables
set "src_dir=mid\lvgl\src"
set "porting_dir=mid\lvgl\porting"

set "base_dir=mid\lvgl"
set "output_file=group.xml"
set "project_file=lvgl_Register.uvprojx"
set "project_file_bak=lvgl_Register.uvprojx_bak"

copy "%project_file%" "%project_file_bak%" 

:: Create the output XML file
(
echo ^<Group^>
echo    ^<GroupName^>mid/lvgl/src^</GroupName^>
echo    ^<Files^>
) > %output_file%

:: Step 2: Traverse directories and find .c files
for /r "%src_dir%" %%i in (*) do (
    if /I "%%~xi"==".c" (
        set "file_path=%%i"
        set "file_name=%%~nxi"
        set "relative_path=!file_path:%cd%\=!"
        (
        echo ^<File^>
        echo    ^<FileName^>!file_name!^</FileName^>
        echo    ^<FileType^>1^</FileType^>
        echo    ^<FilePath^>!relative_path!^</FilePath^>
        echo ^</File^>
        )   >>%output_file%
    )
)

:: Close the XML structure
(
echo    ^</Files^>
echo ^</Group^>
) >> %output_file%


:: Create the output XML file
(
echo ^<Group^>
echo    ^<GroupName^>mid/lvgl/porting^</GroupName^>
echo    ^<Files^>
) >> %output_file%

:: Step 2: Traverse directories and find .c files
for /r "%porting_dir%" %%i in (*) do (
    if /I "%%~xi"==".c" (
        set "file_path=%%i"
        set "file_name=%%~nxi"
        set "relative_path=!file_path:%cd%\=!"
        (
        echo ^<File^>
        echo    ^<FileName^>!file_name!^</FileName^>
        echo    ^<FileType^>1^</FileType^>
        echo    ^<FilePath^>!relative_path!^</FilePath^>
        echo ^</File^>
        )   >>%output_file%
    )
)

:: Close the XML structure
(
echo    ^</Files^>
echo ^</Group^>
) >> %output_file%

(
echo ^<Group^>
echo  ^<GroupName^>mid/lvgl^</GroupName^>
echo  ^<Files^>
echo	^<File^>
echo	  ^<FileName^>lv_conf.h^</FileName^>
echo	  ^<FileType^>5^</FileType^>
echo	  ^<FilePath^>.\mid\lvgl\lv_conf.h^</FilePath^>
echo	^</File^>
echo	^<File^>
echo	  ^<FileName^>lvgl.h^</FileName^>
echo	  ^<FileType^>5^</FileType^>
echo	  ^<FilePath^>.\mid\lvgl\lvgl.h^</FilePath^>
echo	^</File^>
echo  ^</Files^>
echo ^</Group^>
)>>%output_file%


:: Step 3: Insert the group into the project file
:: Find the line number of the last occurrence of "<Groups>"
for /f "delims=:" %%a in ('findstr /N "Groups" %project_file%') do (
    set "last_line=%%a"
)

set /a "tmp_line=last_line-1"

(for /f "usebackq tokens=* delims=" %%a in (`type "%project_file%" ^| findstr /n "^"`) do (
    set "line=%%a"
    set "line=!line:*:=!"
    echo. !line!
    set /a tmp_line-=1
    if !tmp_line! leq 0 goto :end_loop
)) > tmp.txt

:end_loop

type %output_file% >> tmp.txt



set /a "last_line-=1"
more +%last_line% "%project_file%" >> tmp.txt

type tmp.txt > %project_file%

del tmp.txt 
del %output_file%

