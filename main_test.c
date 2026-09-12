#include<lpc21xx.h>

#include "lcd.h"

#include "kpm.h"

#include "uart0.h"

#include "esp01.h"

//#include "rtc.h"

#include "m_delay.h"

#include "m_int0.h"

#include "uart0.h"

#include "dht11.h"

#include "kpm_defines.h"


#include "menu_base.h"

//#include "main_code.h"


#define SEND_INTERVAL 3

extern int flag;


 int humidity,temperature;


int last_sent_min=-1;

int main()

{

	unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum;

   
	IODIR0=1<<20;//FOR MOTOR TURN ON

	//IOPIN0&=~(1<<4);

	IODIR0&=~(1<<21);//FOR READING THE SOIL MOSITURE SENSOR 0 WET 1 DRY


    InitUART0();	

	LCD_Init();


	Write_str_LCD("SMART IoT IRRIGATION");	

	delay_ms(1000);

    Write_CMD_LCD(0x01);


   	Initkpm();

	init_int();

	rtc_init();

	esp01_connectAP();

	delay_ms(1000);

	Write_CMD_LCD(0x01);

		//Write_str_LCD("ok");

		//delay_ms(1000);

	while(1)

	{	
		if(flag==1)
		goto a;

		//dht11_display();


		delay_s(3);


		//Write_str_LCD("dht11");	

		

		dht11_request();


		dht11_response();
				  
		//Write_str_LCD("dht11 reqcomp");

		humidity_integer = dht11_data();


		humidity_decimal = dht11_data();


		temp_integer = dht11_data();


		temp_decimal = dht11_data();


         checksum = dht11_data();


		humidity=humidity_integer+humidity_decimal;


		temperature=temp_integer+temp_decimal;


		if( (humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum )

		  {
			Write_str_LCD("Checksum Error\r\n");

			delay_ms(500);

			Write_CMD_LCD(0x01);


		   }
		else
		{

		   	//Write_DAT_LCD('.');


			Write_CMD_LCD(0x80);


			Write_str_LCD("Humidity : ");


			Write_int_LCD(humidity_integer);


			Write_DAT_LCD('.');


			Write_int_LCD(humidity_decimal);


			Write_str_LCD(" % RH ");


			Write_CMD_LCD(0xC0);


			Write_str_LCD("Temperature : ");


			Write_int_LCD(temp_integer);


			Write_DAT_LCD('.');


			Write_int_LCD(temp_decimal);


			Write_DAT_LCD(223);


			Write_str_LCD("C");


			Write_CMD_LCD(0xD4);


			Write_str_LCD("Checksum : ");


			Write_int_LCD(checksum);


			delay_ms(3000);


			//Write_CMD_LCD(0x01);

			//arr[0]=humidity_integer;


			//arr[1]=temp_integer;

			}

				
			 while((MIN%SEND_INTERVAL==0) && (MIN!=last_sent_min))

			 {
					esp01_sendToThingspeak1(humidity,temperature);

					last_sent_min=MIN;
			 }
	

			 //esp01_sendToThingspeak1(humidity,temperature);

			// delay_s(180);

			// esp01_sendToThingspeak1(humidity,temperature);

		 	


		a: menu_base_int();

	

	compare_temp_hum();


		//delay_s(16);

			

	}

}

