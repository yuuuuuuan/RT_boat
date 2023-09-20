/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Administrator       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "single_pwm_motor.h"
#include "ab_phase_encoder.h"
#include "encoder.h"
#include "pos_pid_controller.h"
#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5
struct rt_semaphore sem_lock;
struct rt_semaphore sem_go, sem_stop;
static rt_thread_t motor_thread = RT_NULL;
static rt_thread_t encoder_thread = RT_NULL;
static rt_thread_t controller_thread = RT_NULL;

#define PWM_DEV_NAME        "pwm4"

#define PIN1 PB6
#define PIN2 PB7

struct rt_device_pwm *pwm_dev;
void motor_thread_entry(void *parameter)
{

    single_pwm_motor_t single_pwm_motor_create(char *pwm, int channel, rt_base_t PIN1, rt_base_t PIN2);
    while (1)
        {
            // TODO: 电机控制逻辑，根据需要编写具体的控制代码
        /* 获取一个满位 */
            rt_sem_take(&sem_go, RT_WAITING_FOREVER);

             rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
             rt_err_t single_pwm_motor_enable(void *mot);

            rt_thread_delay(1000); // 延时1秒


            rt_sem_release(&sem_lock);

            rt_sem_release(&sem_go);
            rt_sem_take(&sem_stop, RT_WAITING_FOREVER);

            rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

            rt_err_t single_pwm_motor_disable(void *mot);

            rt_thread_delay(1000); // 延时1秒


            rt_sem_release(&sem_lock);


            rt_sem_release(&sem_stop);
            rt_thread_delay(1000); // 延时1秒
        }

}

void encoder_thread_entry(void* parameter)
{

    ab_phase_encoder_t ab_phase_encoder_create(rt_base_t pin_a, rt_base_t pin_b, rt_uint16_t pulse_revol, rt_uint16_t sample_time);
    rt_err_t ab_phase_encoder_enable(void *enc);
}

void controller_thread_entry(void* parameter)
{
    pos_pid_controller_t    pos_pid_controller_create(float kp, float ki, float kd, rt_uint16_t sample_time);
    while (1)
            {
                // TODO: 电机控制逻辑，根据需要编写具体的控制代码
            /* 获取一个满位 */


                 rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
                 rt_sem_release(&sem_go);

                rt_thread_delay(1000); // 延时1秒


                rt_sem_release(&sem_lock);



                rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

                rt_sem_release(&sem_stop);

                rt_thread_delay(1000); // 延时1秒


                rt_sem_release(&sem_lock);


                rt_thread_delay(1000); // 延时1秒
            }
}


int thread_init(void)
{
    rt_sem_init(&sem_lock, "lock",     1,      RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_go, "empty",   1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_stop, "full",     0,      RT_IPC_FLAG_FIFO);

    motor_thread = rt_thread_create("motor_thread",
                            motor_thread_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY,
                            THREAD_TIMESLICE);

        /* 如果获得线程控制块，启动这个线程 */
        if (motor_thread != RT_NULL)
            rt_thread_startup(motor_thread);

    encoder_thread = rt_thread_create("encoder_thread",
                              encoder_thread_entry, RT_NULL,
                              THREAD_STACK_SIZE,
                              THREAD_PRIORITY,
                              THREAD_TIMESLICE);

                /* 如果获得线程控制块，启动这个线程 */
                if (encoder_thread != RT_NULL)
                    rt_thread_startup(encoder_thread);

    controller_thread = rt_thread_create("controller_thread",
                                            controller_thread_entry, RT_NULL,
                                              THREAD_STACK_SIZE,
                                              THREAD_PRIORITY,
                                              THREAD_TIMESLICE);

                                /* 如果获得线程控制块，启动这个线程 */
                                if (controller_thread != RT_NULL)
                                    rt_thread_startup(controller_thread);
    return 0;
}
