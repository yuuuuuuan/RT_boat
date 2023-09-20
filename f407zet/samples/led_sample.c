#include <stdio.h>
#include <finsh.h>
#include <rtthread.h>
#include <drv_common.h>
#include <rtdevice.h>
#define LED_PIN             GET_PIN(B,0)
int led_sample(void)
{
    unsigned int count = 1;

        /* 设置 LED 引脚为输出模式 */
        rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

        while (50 > count)
        {
            /* LED 灯亮 */
            rt_pin_write(LED_PIN, PIN_LOW);
            rt_kprintf("led on, count: %d\n", count);
            rt_thread_mdelay(500);

            /* LED 灯灭 */
            rt_pin_write(LED_PIN, PIN_HIGH);
            rt_kprintf("led off\n");
            rt_thread_mdelay(500);

            count++;
        }
        rt_pin_write(LED_PIN, PIN_LOW);
        return 0;
}

MSH_CMD_EXPORT(led_sample, led blink);
