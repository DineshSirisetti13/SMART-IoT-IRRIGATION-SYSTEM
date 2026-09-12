#include <lpc214x.h>				


#include "uart0.h"


#include "m_delay.h"


#include "lcd.h"


#include "esp01.h"


#include "dht11.h"


#include "kpm.h"


#define FOSC      12000000


#define CCLK  	  5*FOSC


#define PCLK  	  CCLK/4


#define PREINT_VAL  ((PCLK/32768)-1)


#define PREFRAC_VAL  (PCLK - ((PREINT_VAL + 1) * 32768))


 


void rtc_init()
{


	SEC=20; //Initialized seconds


	MIN=21; //Initialized minutes


	HOUR=12;//Initialized hour


}


extern char buff[100],dummy;


extern unsigned char i,ch,r_flag;


char I_t1,I_t2,I_t3;//Iregation timings	are 1 min / 2 min / 3 min

//char S_t1,S_t2;	//soil readings

 char T_t1,H_t1,T_t2,H_t2,T_t3,H_t3; // Temprature and Humidity timings

extern volatile int flag;


unsigned char min,sec ,humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum;

   

extern int humidity,temperature;

  
int flag1=0,flag2=0;

void SetIrrigationTiming(void)

{

int val;

flag1=1;

    


    Write_CMD_LCD(0x01);

    
    Write_str_LCD("Set Motor Time");

    
    delay_ms(800);
    
    val = Get1DigitValue("Enter HighTemp LowHum:");

    
	    if(val != -1) I_t1 = val;

		delay_ms(800);


		Write_CMD_LCD(0x01);


    val = Get1DigitValue("Enter ModTemp ModHum:");

    
    if(val != -1) I_t2 = val;

	delay_ms(800);


	Write_CMD_LCD(0x01);


    val = Get1DigitValue("Enter LowTemp HighHum:");

    
    if(val != -1) I_t3 = val;

	delay_ms(800);


    Write_CMD_LCD(0x01);


    Write_CMD_LCD(0x80);

    
    Write_str_LCD("Saved Successfully");

    
    delay_ms(1000);

    
    Write_CMD_LCD(0X01);
}


void Set_Temp_Humidity(void)

{

	int val;

	flag2=1;

    


    Write_CMD_LCD(0x01);

    Write_str_LCD("Set Temp & Hum");

    delay_ms(800);



	delay_ms(800);

    val = Get2DigitValue("1.LOW TEMPERATURE:");

	Write_str_LCD("Temp Range (0-50)");

    if(val != -1) T_t1 = val;


 	delay_ms(800);
	val = Get2DigitValue("1.HIGH HUMIDITY:");

	Write_str_LCD("Humrange is (0-99)");

    if(val != -1) H_t1 = val;




 //Write_str_LCD("Temp Range (0-50)");

 delay_ms(800);
    val = Get2DigitValue("2.MOD TEMPERATURE:");

		Write_str_LCD("Temp Range (0-50)");

	

    if(val != -1) T_t2 = val;


    val = Get2DigitValue("2.MOD HUMIDITY:");

  	Write_str_LCD("Humrange is (0-100)");

    if(val != -1) H_t2 = val;
	
 

 delay_ms(800);
    val = Get2DigitValue("3.HIGH TEMPERATURE:");

	Write_str_LCD("Temp Range (0-50)");

    if(val != -1) T_t3 = val;




	delay_ms(800);
    val = Get2DigitValue("3.LOW HUMIDITY:");

		Write_str_LCD("Humrange is (0-100)");

    if(val != -1) H_t3 = val;


    Write_CMD_LCD(0x01);

    Write_str_LCD("Saved");

    delay_ms(1000);

    Write_CMD_LCD(0X01);
}


void menu_base_int(void)

{	 char ch;

    if(flag == 1)

    {  

		flag = 0;

        Write_CMD_LCD(0x01);

        Write_CMD_LCD(0x80);

        Write_str_LCD("1.Irrigation Time");

        Write_CMD_LCD(0xC0);

        //Write_str_LCD("2.Moisture Thresh");

        //Write_CMD_LCD(0x94);

        Write_str_LCD("2.Temp & Humidity");

	   Write_CMD_LCD(0x94);
	   Write_str_LCD("3.EXIT");


        Write_CMD_LCD(0xD4);

        Write_str_LCD("Select Option:");

	ch = keyScan();

        switch(ch)

        {

            case '1': SetIrrigationTiming(); break;

            //case '2': SetMoisture_Threshold(); break;

            case '2': Set_Temp_Humidity(); break;
		  
		   case '3':Write_CMD_LCD(0x01);
		           return;

            default:

                Write_CMD_LCD(0x01);

                Write_str_LCD("Invalid Option");

                delay_ms(1000);

        }

    }

}


void compare_temp_hum(void)

{

int delay_time;

 if((flag1==1) && (flag2==1))

{

delay_time=0;

	//flag1=0;

  

// Check soil moisture first
if ((IOPIN0 >> 21) & 1)
{				 

int cnt=0;
    if ((temperature >= T_t3) && (humidity <= H_t3))
        delay_time = I_t1;

    else if ((temperature >= T_t2) && (humidity >= H_t2))
        delay_time = I_t2; 

    else if ((temperature <= T_t1) && (humidity <= H_t1))
        delay_time = I_t3;

    // If any condition matched
    if (delay_time > 0)
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("MOTOR STATUS");
		                                                                                              
        IOSET0 = 1 << 20;   // Motor ON
		Write_CMD_LCD(0xC0);
	  Write_str_LCD("SENDING TO CLOUD");				
        esp01_sendToThingspeak3(1);
        //Write_str_LCD("SENDING TO CLOUD");
	  			
				sec=59;
				min=delay_time;
				if(min==1)
				min=0;

				Write_CMD_LCD(0x01);	

				while(1)
				{

				
				 Write_CMD_LCD(0x80);

				 Write_str_LCD("MOTOR TURN ON");
                 Write_CMD_LCD(0XC0);				 

        //delay_s(60 * delay_time);
				 //Write_int_LCD(cnt);

				cnt++;


				delay_s(1);
				if((cnt==(delay_time*60)) || ((IOPIN0 >> 21) & 1)==0)

				{

				break;

				}
				if((IOPIN0>>21)&1==0)
				break;
				if(sec==0)
				{
				min--;
				sec=59;
				}
				Write_DAT_LCD((min/10)+'0');
			     Write_DAT_LCD((min%10)+'0');
				Write_DAT_LCD(':');
				Write_DAT_LCD((sec/10)+'0');
				Write_DAT_LCD((sec%10)+'0');
				sec--;
				delay_ms(1);
				}
				IOCLR0 = 1 << 20;   // Motor OFF
        

				Write_CMD_LCD(0x01);

				Write_str_LCD("MOTOR TURN OFF");
				
				//Write_CMD_LCD(0x01);

				esp01_sendToThingspeak3(0);

        		Write_CMD_LCD(0x01);

        
    }
}

}

}
