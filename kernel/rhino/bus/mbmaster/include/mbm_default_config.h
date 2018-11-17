/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef _MBM_DEFAULT_CONFIG_H
#define _MBM_DEFAULT_CONFIG_H

#ifndef MBM_LOG_LEVEL
#define MBM_LOG_LEVEL MB_LOG_ERROR
#endif

#ifndef MBM_RTU_ENABLED
#define MBM_RTU_ENABLED               1
#endif

#ifndef MBM_ASCII_ENABLED
#define MBM_ASCII_ENABLED             0
#endif

#ifndef MBM_TCP_ENABLED
#define MBM_TCP_ENABLED               0
#endif

#ifndef MBM_FUNC_READ_HOLDING_ENABLED
#define MBM_FUNC_READ_HOLDING_ENABLED 1
#endif

#ifndef MBM_FUNC_READ_COILS_ENABLED
#define MBM_FUNC_READ_COILS_ENABLED   1
#endif

#ifndef MBM_HANDLER_MAX
#define MBM_HANDLER_MAX   1
#endif

#endif