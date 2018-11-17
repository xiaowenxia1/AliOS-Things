/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */
#include <mbmaster_api.h>

static mb_handler_t mb_handler[MBM_HANDLER_MAX]; 

mb_handler_t* mb_alloc_handler()
{
    MB_CRITICAL_ALLOC();
    MB_CRITICAL_ENTER();
    for (uint8_t i = 0; i < MBM_HANDLER_MAX; i++) {
        if(mb_handler[i].used == 0) {
            mb_handler[i].used = 1;
            MB_CRITICAL_EXIT();
            return &mb_handler[i];
        }
    }
    MB_CRITICAL_EXIT();
    return NULL;
}

void mb_free_handler(mb_handler_t* handler)
{
    MB_CRITICAL_ALLOC();
    MB_CRITICAL_ENTER();
    if (handler->used ==1) {
        handler->used = 0;
    }
    MB_CRITICAL_EXIT();
}

mb_status_t mb_mutex_create(MB_MUTEX_T *mutex)
{
    krhino_mutex_create(mutex, "mb_mutex");
    return MB_SUCCESS;
}

mb_status_t mb_mutex_lock(MB_MUTEX_T *mutex)
{
    krhino_mutex_lock(mutex, RHINO_WAIT_FOREVER);
    return MB_SUCCESS;
}

mb_status_t mb_mutex_unlock(MB_MUTEX_T *mutex)
{
    krhino_mutex_unlock(mutex);
    return MB_SUCCESS;
}

mb_status_t mb_mutex_del(MB_MUTEX_T *mutex)
{
    krhino_mutex_del(mutex);
    return MB_SUCCESS;
}
