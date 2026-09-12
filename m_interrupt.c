#include<lpc21xx.h>

#include"typedef.h"

#include"m_delay.h"

#define EINT0_INPUT_PIN 0x000000C0

#define EINT0_VIC_CHNO 15

volatile int flag=0;

//#define EINT0_STATUS_LED 20

void eint0_isr(void) __irq;

//u32 gcount;

void init_int(void)

{

//PINSEL0&=~(3<<2);

PINSEL0|=EINT0_INPUT_PIN;

VICIntEnable=1<<EINT0_VIC_CHNO;

VICVectCntl1=(1<<5)|EINT0_VIC_CHNO;


VICVectAddr1=(u32)eint0_isr;


EXTMODE|=1<<1;


}

void eint0_isr(void) __irq

{


delay_ms(20);

 flag=1;

EXTINT=1<<1;


VICVectAddr=0;

}
