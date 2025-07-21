#include "App_DisplayDemo.h"

void App_DisplayDemo_Init(void)
{
    /* 0. ������ʱ��,���ڸ� lvgl �ṩʱ���� */
    Driver_TIM6_Init();
    Driver_TIM6_Start();

    /* 1. ��ʼ�� lvgl �� */
    lv_init();
    /* 2. ��ʼ����ʾ�豸 */
    lv_port_disp_init();
    /* 3. ��ʼ�������豸(�����豸) */
    lv_port_indev_init();
}

void btn_cb(lv_event_t *e)
{
    static uint8_t cnt = 0;
    lv_obj_t *obj = lv_event_get_current_target(e);
    lv_obj_t *label = lv_obj_get_child(obj, 0);
    lv_label_set_text_fmt(label, "Atguigu %d", cnt++);
}

/* ����һ����ť */
void App_Display_CreateButton(void)
{
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_height(btn, 30);
    lv_obj_add_event_cb(btn, btn_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_t *label;
    label = lv_label_create(btn);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label, "Atguigu");

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 10);
    lv_style_set_border_color(&style_btn, lv_color_black());
    lv_style_set_border_opa(&style_btn, LV_OPA_30);
    lv_obj_add_style(btn, &style_btn, LV_STATE_DEFAULT);
}