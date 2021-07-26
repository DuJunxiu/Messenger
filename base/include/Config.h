#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef signed char         int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef char                BOOL;

#define TRUE    (0)
#define FALSE   (-1)

typedef int net_handle_t;

#define ASSERT_AND_LOG_RTN_INT(x) if (!(x)) return -1;
#define ASSERT_AND_LOG_RTN_VOID(x) if (!(x)) return;
#define ASSERT_AND_LOG_RTN_BOOL(x) if (!(x)) return false;

typedef void (*callback_t)(void* callback_data, uint8_t msg, uint32_t handle, void* pParam);

enum SERVER_CMD
{
    NOTHING = 0,
    START   = 1,
    STOP    = 2,
    RESUME  = 3,
    RELOAD  = 4
};

#endif
