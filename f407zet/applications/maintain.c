/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-26     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "maintain"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

int maintain(void)
{
    int count = 1;

    while (count)
    {
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
