#include<lpc21xx.h>

#include"typedef.h"

#include"defines.h"

#include<string.h>

#include "m_delay.h"

#include"kpm_defines.h"

#include "lcd.h"

u8 kpmLUT[4][4]={{'1','2','3','A'},

	{'4','5','6','B'},

	{'7','8','9','C'},

	{'*','0','#','D'}};	


void Initkpm(void)

{


	WNIBBLE(IODIR1,ROW0,15);

}

u32 ColScan(void)

{

	return ((RNIBBLE(IOPIN1,COL0)<15)?0:1);

}

u32 RowCheck(void)

{

	u32 rno;

	for(rno=0;rno<4;rno++)

	{

		WNIBBLE(IOPIN1,ROW0,~(1<<rno));

		if(ColScan()==0)

		{

			break;

		}

	}

	//make as default

	WNIBBLE(IOPIN1,ROW0,0X0);

	return rno;

}

u32 ColCheck(void)

{

	u32 cno;

	for(cno=0;cno<4;cno++)

	{

		if(RBIT(IOPIN1,(COL0+cno))==0)

		{

			break;

		}


	}

	return cno;

}

u32 keyScan(void)

{

	u32 rno,cno,keyV;

	//wait for switch press

	while(ColScan());
	delay_ms(100);


	//find the rno

	rno=RowCheck();

	//find the cno

	cno=ColCheck();

	//get the key value using kpmLUT

	keyV=kpmLUT[rno][cno];

	//wait for swtich press

	while(!ColScan());

	return keyV;


}

u32 ReadNum(void)

{

	u8 key;

	u32 sum=0;

	while(1)

	{

		key=keyScan();

		if(key>='0' && key<='9')

		{

			LCD_Init();

			Write_LCD(key);

			sum=(sum*10)+(key-'0');

		}

		else if(key=='=')

		{

			break;

		} 

	}

	return sum;

} 

int Get2DigitValue(char *msg)

{

    char arr[3] = {0};

    char key;

    int i = 0;

    int val;


again:

    i = 0;

    arr[0] = arr[1] = 0;


    Write_CMD_LCD(0x01);


    // Row 1: message

    Write_CMD_LCD(0x80);

    Write_str_LCD(msg);


    // Row 2: user input

    Write_CMD_LCD(0xC0);


    while(i < 2)

    {

        key = keyScan();


        if(key >= '0' && key <= '9')

        {

            arr[i++] = key;

            Write_DAT_LCD(key);

						delay_ms(100);

        }

        else if(key == 'C' && i > 0)

        {

            i--;

            Write_CMD_LCD(0x10);

            Write_DAT_LCD(' ');

            Write_CMD_LCD(0x10);

        }

        else if(key == '*')

        {

            Write_CMD_LCD(0x01);

            Write_str_LCD("Skipped");

            delay_ms(500);

            return -1;

        }

    }


    val = (arr[0]-'0')*10 + (arr[1]-'0');


    // Temperature validation

    if(strstr(msg, "TEMP") != 0 && val > 50)

    {

        Write_CMD_LCD(0x01);

        Write_str_LCD("Invalid Temp!");

        Write_CMD_LCD(0xC0);

        Write_str_LCD("Enter 0-50");

        delay_ms(1000);

        goto again;

    }


    // Humidity validation

    if(strstr(msg, "HUM") != 0 && val > 99)

    {

        Write_CMD_LCD(0x01);

        Write_str_LCD("Invalid Hum!");

        Write_CMD_LCD(0xC0);

        Write_str_LCD("Enter 0-99");

        delay_ms(1000);

        goto again;

    }


    return val;

}

int Get1DigitValue(char *msg)

{

    char key;


again:

    Write_CMD_LCD(0x01);


    // Row 1: message

    Write_CMD_LCD(0x80);

    Write_str_LCD(msg);


    // Row 2: input

    Write_CMD_LCD(0xC0);


    while(1)

    {

        key = keyScan();


        if(key >= '0' && key <= '9')

        {

            // Allow only 0 to 3

            if(key >= '0' && key <= '3')

            {

                Write_DAT_LCD(key);

								delay_ms(500);

                return (key - '0');

            }

            else

            {

                Write_CMD_LCD(0x01);

                Write_str_LCD("Invalid!");

                Write_CMD_LCD(0xC0);

                Write_str_LCD("Enter 0-3 only");

                delay_ms(1000);

                goto again;

            }

        }

        else if(key == '*')

        {

            Write_CMD_LCD(0x01);

            Write_str_LCD("Skipped");

            delay_ms(500);

            return -1;

        }

    }
 
}


