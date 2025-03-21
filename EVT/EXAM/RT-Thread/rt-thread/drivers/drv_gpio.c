/*
 * File      : drv_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-20     ZYH            the first version
 * 2017-11-15     ZYH            update to 3.0.0
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include <rtthread.h>
#include "drivers/pin.h"


#ifdef RT_USING_PIN
#define __CH32_PIN(index, gpio, gpio_index) {index, GPIO##gpio##_CLK_ENABLE, GPIO##gpio, GPIO_Pin_##gpio_index}
#define __CH32_PIN_DEFAULT  {-1, 0, 0, 0}


static void GPIOA_CLK_ENABLE(void)
{
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA, ENABLE);
}

static void GPIOB_CLK_ENABLE(void)
{
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOB, ENABLE);
}

#if (CH32M030_PIN_NUMBERS >36)
static void GPIOC_CLK_ENABLE(void)
{
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC, ENABLE);
}
#endif


#if (CH32V10X_PIN_NUMBERS >64)
static void GPIOE_CLK_ENABLE(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
}
#endif





/* GPIO driver */
struct pin_index
{
    int index;
    void (*rcc)(void);
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index pins[] =
{

#if (CH32M030_PIN_NUMBERS == 48)
  #if (Pack==LQFP48)
    __CH32_PIN_DEFAULT,
    __CH32_PIN(1, A, 10),
    __CH32_PIN(2, A, 11),
    __CH32_PIN(3, A, 12),
    __CH32_PIN(4, A, 13),
    __CH32_PIN(5, A, 14),
    __CH32_PIN(6, A, 15),
    __CH32_PIN(7, B, 2),
    __CH32_PIN(8, B, 3),
    __CH32_PIN(9, B, 4),
    __CH32_PIN(10, B, 5),
    __CH32_PIN(11, B, 6),
    __CH32_PIN(12, B, 8),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(15, B, 9),
    __CH32_PIN(16, B, 10),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(19, B, 11),
    __CH32_PIN(20, B, 12),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(23, B, 13),
    __CH32_PIN(24, B, 14),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(27, B, 15),
    __CH32_PIN_DEFAULT,
    __CH32_PIN(29, C, 0),
    __CH32_PIN(30, C, 1),
    __CH32_PIN(31, C, 2),
    __CH32_PIN(32, C, 3),
    __CH32_PIN(33, C, 4),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(37, A, 0),
    __CH32_PIN(38, A, 1),
    __CH32_PIN(39, A, 2),
    __CH32_PIN(40, A, 3),
    __CH32_PIN(41, B, 0),
    __CH32_PIN(42, B, 1),
    __CH32_PIN(43, A, 4),
    __CH32_PIN(44, A, 5),
    __CH32_PIN(45, A, 6),
    __CH32_PIN(46, A, 7),
    __CH32_PIN(47, A, 8),
    __CH32_PIN_DEFAULT,
  #endif

  #if (Pack==QFN48)
   __CH32_PIN_DEFAULT,
   __CH32_PIN(1, A, 12),
   __CH32_PIN(2, A, 13),
   __CH32_PIN(3, A, 14),
   __CH32_PIN(4, A, 15),
   __CH32_PIN(5, B, 2),
   __CH32_PIN(6, B, 3),
   __CH32_PIN(7, B, 4),
   __CH32_PIN(8, B, 5),
   __CH32_PIN(9, B, 6),
   __CH32_PIN(10, B, 8),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(13, B, 9),
   __CH32_PIN(14, B, 10),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(17, B, 11),
   __CH32_PIN(18, B, 12),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(21, B, 13),
   __CH32_PIN(22, B, 14),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(25, B, 15),
   __CH32_PIN_DEFAULT,
   __CH32_PIN(27, C, 0),
   __CH32_PIN(28, C, 1),
   __CH32_PIN(29, C, 2),
   __CH32_PIN(30, C, 3),
   __CH32_PIN(31, C, 4),
   __CH32_PIN(32, C, 5),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(35, A, 0),
   __CH32_PIN(36, A, 1),
   __CH32_PIN(37, A, 2),
   __CH32_PIN(38, A, 3),
   __CH32_PIN(39, B, 0),
   __CH32_PIN(40, B, 1),
   __CH32_PIN(41, A, 4),
   __CH32_PIN(42, A, 5),
   __CH32_PIN(43, A, 6),
   __CH32_PIN(44, A, 7),
   __CH32_PIN(45, A, 8),
   __CH32_PIN_DEFAULT,
   __CH32_PIN(47, A, 10),
   __CH32_PIN(48, A, 11),

  #endif

  #if (Pack==QFN48_7)
   __CH32_PIN_DEFAULT,
   __CH32_PIN(1, A, 10),
   __CH32_PIN(2, A, 11),
   __CH32_PIN(3, A, 12),
   __CH32_PIN(4, A, 13),
   __CH32_PIN(5, A, 14),
   __CH32_PIN(6, A, 15),
   __CH32_PIN(7, B, 2),
   __CH32_PIN(8, B, 3),
   __CH32_PIN(9, B, 4),
   __CH32_PIN(10, B, 5),
   __CH32_PIN(11, B, 6),
   __CH32_PIN(12, B, 8),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(15, B, 9),
   __CH32_PIN(16, B, 10),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(19, B, 11),
   __CH32_PIN(20, B, 12),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(23, B, 13),
   __CH32_PIN(24, B, 14),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(27, B, 15),
   __CH32_PIN_DEFAULT,
   __CH32_PIN(29, B, 7),
   __CH32_PIN(30, C, 0),
   __CH32_PIN(31, C, 1),
   __CH32_PIN(32, C, 3),
   __CH32_PIN(33, C, 4),
   __CH32_PIN(34, C, 5),
   __CH32_PIN_DEFAULT,
   __CH32_PIN_DEFAULT,
   __CH32_PIN(37, A, 0),
   __CH32_PIN(38, A, 1),
   __CH32_PIN(39, A, 2),
   __CH32_PIN(40, A, 3),
   __CH32_PIN(41, B, 0),
   __CH32_PIN(42, B, 1),
   __CH32_PIN(43, A, 4),
   __CH32_PIN(44, A, 5),
   __CH32_PIN(45, A, 6),
   __CH32_PIN(46, A, 7),
   __CH32_PIN(47, A, 8),
   __CH32_PIN_DEFAULT,
  #endif
#endif

#if (CH32M030_PIN_NUMBERS == 28)
    __CH32_PIN_DEFAULT,
    __CH32_PIN(1, B, 1),
    __CH32_PIN(2, A, 7),
    __CH32_PIN(3, A, 8),
    __CH32_PIN_DEFAULT,
    __CH32_PIN(5, A, 10),
    __CH32_PIN(6, A, 11),
    __CH32_PIN(7, B, 4),
    __CH32_PIN(8, B, 5),
    __CH32_PIN(9, B, 6),
    __CH32_PIN(10, B, 8),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(13, B, 9),
    __CH32_PIN(14, B, 10),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(17, B, 11),
    __CH32_PIN(18, B, 12),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(21, B, 13),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(26, A, 2),
    __CH32_PIN(27, A, 3),
    __CH32_PIN(28, B, 0),
#endif
#if (CH32M030_PIN_NUMBERS == 32)
    __CH32_PIN_DEFAULT,
    __CH32_PIN(1, A, 10),
    __CH32_PIN(2, A, 13),
    __CH32_PIN(3, A, 14),
    __CH32_PIN(4, B, 2),
    __CH32_PIN(5, B, 3),
    __CH32_PIN(6, B, 4),
    __CH32_PIN(7, B, 5),
    __CH32_PIN(8, B, 6),
    __CH32_PIN(9, B, 8),
    __CH32_PIN_DEFAULT,
    __CH32_PIN(11, B, 9),
    __CH32_PIN_DEFAULT,
    __CH32_PIN(13, B, 10),
    __CH32_PIN_DEFAULT,
    __CH32_PIN(15, B, 11),
    __CH32_PIN_DEFAULT,
    __CH32_PIN(17, B, 13),
    __CH32_PIN(18, B, 15),
    __CH32_PIN_DEFAULT,
    __CH32_PIN(20, C, 5),
    __CH32_PIN_DEFAULT,
    __CH32_PIN_DEFAULT,
    __CH32_PIN(23, A, 0),
    __CH32_PIN(24, A, 1),
    __CH32_PIN(25, A, 2),
    __CH32_PIN(26, A, 3),
    __CH32_PIN(27, B, 0),
    __CH32_PIN(28, B, 1),
    __CH32_PIN(29, A, 4),
    __CH32_PIN(30, A, 7),
    __CH32_PIN(31, A, 8),
    __CH32_PIN_DEFAULT,
#endif
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};
static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_Pin_0, EXTI7_0_IRQn},
    {GPIO_Pin_1, EXTI7_0_IRQn},
    {GPIO_Pin_2, EXTI7_0_IRQn},
    {GPIO_Pin_3, EXTI7_0_IRQn},
    {GPIO_Pin_4, EXTI7_0_IRQn},
    {GPIO_Pin_5, EXTI7_0_IRQn},
    {GPIO_Pin_6, EXTI7_0_IRQn},
    {GPIO_Pin_7, EXTI7_0_IRQn},
    {GPIO_Pin_8, EXTI15_8_IRQn},
    {GPIO_Pin_9, EXTI15_8_IRQn},
    {GPIO_Pin_10, EXTI15_8_IRQn},
    {GPIO_Pin_11, EXTI15_8_IRQn},
    {GPIO_Pin_12, EXTI15_8_IRQn},
    {GPIO_Pin_13, EXTI15_8_IRQn},
    {GPIO_Pin_14, EXTI15_8_IRQn},
    {GPIO_Pin_15, EXTI15_8_IRQn},
};
struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;
    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }
    return index;
};

void ch32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    GPIO_WriteBit(index->gpio, index->pin, (BitAction)value);
}

int ch32_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;
    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }
    value = GPIO_ReadInputDataBit(index->gpio, index->pin);
    return value;
}

void ch32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    GPIO_InitTypeDef GPIO_InitStruct;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    rt_kprintf("get pin index\r\n");
    /* GPIO Periph clock enable */
    index->rcc();
    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.GPIO_Pin = index->pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if (mode == PIN_MODE_INPUT_AIN)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
//        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* output setting: od. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
//        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    }
    else if (mode == PIN_MODE_OUTPUT_AF_OD)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    }
    else if (mode == PIN_MODE_OUTPUT_AF_PP)
    {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    }

    GPIO_Init(index->gpio, &GPIO_InitStruct);
}


rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if ((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}

rt_inline const struct pin_irq_map *get_pin_irq_map(uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};
rt_err_t ch32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                              rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == pin &&
            pin_irq_hdr_tab[irqindex].hdr == hdr &&
            pin_irq_hdr_tab[irqindex].mode == mode &&
            pin_irq_hdr_tab[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

rt_err_t ch32_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

rt_err_t ch32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                              rt_uint32_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return RT_ENOSYS;
        }
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_ENOSYS;
        }
        irqmap = &pin_irq_map[irqindex];
        /* GPIO Periph clock enable */
        index->rcc();
        RCC_PB2PeriphClockCmd(RCC_PB2Periph_AFIO,ENABLE);

        /* Configure GPIO_InitStructure */
        GPIO_InitStruct.GPIO_Pin = index->pin;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;

        EXTI_InitStructure.EXTI_Line=index->pin;/* 外部中断线和引脚号对应 */
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }

        GPIO_Init(index->gpio, &GPIO_InitStruct);
        EXTI_Init(&EXTI_InitStructure);
        NVIC_SetPriority(irqmap->irqno,5<<4);
        NVIC_EnableIRQ( irqmap->irqno );

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return RT_ENOSYS;
        }
        NVIC_DisableIRQ(irqmap->irqno);
    }
    else
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _ch32_pin_ops =
{
    ch32_pin_mode,
    ch32_pin_write,
    ch32_pin_read,
    ch32_pin_attach_irq,
    ch32_pin_dettach_irq,
    ch32_pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    int result;
    result = rt_device_pin_register("pin", &_ch32_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    pin_irq_hdr(bit2bitno(GPIO_Pin));
}


void EXTI7_0_IRQHandler(void) __attribute__((interrupt()));
void EXTI15_8_IRQHandler(void) __attribute__((interrupt()));

void EXTI7_0_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    if( (EXTI_GetITStatus(EXTI_Line0)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line1)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line2)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line3)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line4)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line5)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line6)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line7)!=RESET) )
    {
    HAL_GPIO_EXTI_Callback(GPIO_Pin_0);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_1);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_2);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_3);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_4);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_5);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_6);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_7);
    EXTI_ClearITPendingBit(EXTI_Line0|EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line7);
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

void EXTI15_8_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    if( (EXTI_GetITStatus(EXTI_Line8)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line9)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line10)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line11)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line12)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line13)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line14)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line15)!=RESET) )
    {
    HAL_GPIO_EXTI_Callback(GPIO_Pin_8);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_9);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_10);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_11);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_12);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_13);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_14);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_15);
    EXTI_ClearITPendingBit(EXTI_Line8|EXTI_Line9|EXTI_Line10|EXTI_Line11|EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15);
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

#endif
