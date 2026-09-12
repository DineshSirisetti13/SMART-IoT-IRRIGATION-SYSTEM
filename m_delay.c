//#include "typedef.h"
#include "typedef.h"

void delay_us(u32 dlys)

{

for(dlys*=12;dlys>0;dlys--);

}

void delay_ms(u32 dlys)

{

for(dlys*=12000;dlys>0;dlys--);

}

void delay_s(u32 dlys)

{

for(dlys*=12000000;dlys>0;dlys--);

}




