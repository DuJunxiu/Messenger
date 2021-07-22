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

#define ASSERT_RTN_INT()

typedef void (*callback_t)(void* callback_data, uint8_t msg, uint32_t handle, void* pParam);

#endif
