#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

/* 定义 LED 亮灭电平 */
#define LED_ON  (0)
#define LED_OFF (1)
#define PIN_LED_R   GET_PIN(A,7)
#define PIN_LED_G   GET_PIN(A,6)
#define PIN_LED_B   GET_PIN(A,5)
/* 定义 8 组 LED 闪灯表，其顺序为 R G B */
static const rt_uint8_t _blink_tab[][3] =
{
    {LED_ON, LED_ON, LED_ON},
    {LED_OFF, LED_ON, LED_ON},
    {LED_ON, LED_OFF, LED_ON},
    {LED_ON, LED_ON, LED_OFF},
    {LED_OFF, LED_OFF, LED_ON},
    {LED_ON, LED_OFF, LED_OFF},
    {LED_OFF, LED_ON, LED_OFF},
    {LED_OFF, LED_OFF, LED_OFF},
};

int rgb_sample(void)
{
    unsigned int count = 1;
    unsigned int group_num = sizeof(_blink_tab)/sizeof(_blink_tab[0]);
    unsigned int group_current;

    /* 设置 RGB 灯引脚为输出模式 */
    rt_pin_mode(PIN_LED_R, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED_G, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED_B, PIN_MODE_OUTPUT);

    while (50 > count)
    {
        /* 获得组编号 */
        group_current = count % group_num;

        /* 控制 RGB 灯 */
        rt_pin_write(PIN_LED_R, _blink_tab[group_current][0]);
        rt_pin_write(PIN_LED_G, _blink_tab[group_current][1]);
        rt_pin_write(PIN_LED_B, _blink_tab[group_current][2]);

        /* 输出 LOG 信息 */
        rt_kprintf("group: %d | red led [%-3.3s] | green led [%-3.3s] | blue led [%-3.3s]\n",
            group_current,
            _blink_tab[group_current][0] == LED_ON ? "ON" : "OFF",
            _blink_tab[group_current][1] == LED_ON ? "ON" : "OFF",
            _blink_tab[group_current][2] == LED_ON ? "ON" : "OFF");

        /* 延时一段时间 */
        rt_thread_mdelay(500);
        count++;
    }
            rt_pin_write(PIN_LED_R,0);
            rt_pin_write(PIN_LED_G,0);
            rt_pin_write(PIN_LED_B,0);

    return 0;
}

MSH_CMD_EXPORT(rgb_sample, rgb blink);
