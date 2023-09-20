#include <rtthread.h>
#include <rtdevice.h>

#define PWM_DEV_NAME        "pwm3"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL1    1       /* PWM通道 */
#define PWM_DEV_CHANNEL2    2       /* PWM通道 */
#define PWM_DEV_CHANNEL3    3       /* PWM通道 */

struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */

static int pwm_rgb_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse, dir;

    period = 500000;    /* 周期为0.5ms，单位为纳秒ns */
    dir = 1;            /* PWM脉冲宽度值的增减方向 */
    pulse = 0;          /* PWM脉冲宽度值，单位为纳秒ns */

    /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }
    else
        rt_kprintf("pwm sample run success! can find %s device!\n");
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL1, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL1);

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL2, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL2);

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL3, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL3);
    int i=1;
    while (1)
    {


        rt_thread_mdelay(50);
        if (dir)
        {
            pulse += 10000;      /* 从0值开始每次增加5000ns */
        }
        else
        {
            pulse -= 10000;      /* 从最大值开始每次减少5000ns */
        }
        if (pulse >= period)
        {
            dir = 0;
        }
        if (0 == pulse && dir == 0)
        {
            dir = 1;
            i++;
        }
        switch(i)
        {
            case 1:
                rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL1, period, pulse);
                break;
            case 2:
                rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL2, period, pulse);
                break;
            case 3:
                rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL3, period, pulse);
                break;
            default:
                i=1;
        }
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pwm_rgb_sample, pwm sample);
