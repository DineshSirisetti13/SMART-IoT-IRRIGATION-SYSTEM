#include <string.h>


#include "uart0.h"


#include "m_delay.h"


#include "lcd.h"


extern char buff[200];


extern unsigned char i;




void esp01_connectAP()
{


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD("AT");


	delay_ms(1000);


	UART0_Str("AT\r\n");


	i=0;memset(buff,'\0',200);


	while(i<4);


	delay_ms(500);


	buff[i] = '\0';


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD(buff);


	delay_ms(2000);


	if(strstr(buff,"OK"))
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("OK");


		delay_ms(1000);		


	}


	else
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("ERROR");


		delay_ms(1000);		


		return;


	}


	


	


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD("ATE0");


	delay_ms(1000);


	UART0_Str("ATE0\r\n");


	i=0;memset(buff,'\0',200);


	while(i<4);


	delay_ms(500);


	buff[i] = '\0';


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD(buff);


	delay_ms(2000);


	if(strstr(buff,"OK"))
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("OK");


		delay_ms(1000);		


	}


	else
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("ERROR");


		delay_ms(1000);		


		return;


	}


	


	


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);



	Write_str_LCD("AT+CIPMUX");


	delay_ms(1000);


	UART0_Str("AT+CIPMUX=0\r\n");


	i=0;memset(buff,'\0',200);


	while(i<4);


	delay_ms(500);


	buff[i] = '\0';


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD(buff);


	delay_ms(2000);


	if(strstr(buff,"OK"))
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("OK");


		delay_ms(1000);		


	}


	else
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("ERROR");


		delay_ms(1000);		


		return;


	}


	


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD("AT+CWQAP");


	delay_ms(1000);


	UART0_Str("AT+CWQAP\r\n");


	i=0;memset(buff,'\0',200);


	while(i<4);


	delay_ms(1500);


	buff[i] = '\0';


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD(buff);


	delay_ms(2000);


	if(strstr(buff,"OK"))
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("OK");


		delay_ms(1000);		


	}
	else
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("ERROR");


		delay_ms(1000);		


		return;


	}

	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD("AT+CWJAP");


	delay_ms(1000);


	//need to change the wifi network name and password


	//UART0_Str("AT+CWJAP=\"name\",\"password\"\r\n");

	UART0_Str("AT+CWJAP=\"dinesh\",\"123456789\"\r\n");
	i=0;memset(buff,'\0',200);


	while(i<4);


	delay_ms(2500);


	buff[i] = '\0';


	Write_CMD_LCD(0x01);


	Write_CMD_LCD(0x80);


	Write_str_LCD(buff);


	delay_ms(2000);


	if(strstr(buff,"WIFI CONNECTED"))
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("OK");


		delay_ms(1000);		


	}


	else
	{


		Write_CMD_LCD(0xC0);


		Write_str_LCD("ERROR");


		delay_ms(1000);		


		return;


	}

}


void esp01_sendToThingspeak1(float val1,float val2)

{


	//Write_CMD_LCD(0x01);


//	Write_CMD_LCD(0x80);


	//Write_str_LCD("AT+CIPSTART");


	delay_ms(1000);


	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");


	i=0;memset(buff,'\0',200);


	while(i<5);


	delay_ms(2500);


	buff[i] = '\0';


//	Write_CMD_LCD(0x01);


//	Write_CMD_LCD(0x80);


//	Write_str_LCD(buff);


	delay_ms(2000);


	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{


//		Write_CMD_LCD(0xC0);


//		Write_str_LCD("OK");


		delay_ms(1000);


		


//		Write_CMD_LCD(0x01);


//		Write_CMD_LCD(0x80);


//		Write_str_LCD("AT+CIPSEND");


		delay_ms(1000);


		UART0_Str("AT+CIPSEND=64\r\n");


		i=0;memset(buff,'\0',200);


		//while(buff[i] != '>');


		delay_ms(500);


		//need to change the thingspeak write API key accordind to your channel


		//UART0_Str("GET /update?api_key=UNIQUE_KEY&field1=");

		UART0_Str("GET /update?api_key=XN99FUUM8IXTHFLY&field1=");

		UART0_Float(val2);		//for temperature


		 UART0_Str("&field2=");

		 UART0_Float(val1);		   //for humidity

		UART0_Str("\r\n\r\n");



		delay_ms(5000);


		delay_ms(5000);


		buff[i] = '\0';


//		Write_CMD_LCD(0x01);


//		Write_CMD_LCD(0x80);


//		Write_str_LCD(buff);


		delay_ms(2000);


		if(strstr(buff,"SEND OK"))


		{


			//Write_CMD_LCD(0x01);


			//Write_str_LCD("DATA UPDATED");


			delay_ms(1000);			


			//Write_CMD_LCD(0x01);
		}


		else


		{


			Write_CMD_LCD(0x01);


			Write_str_LCD("TEMPRATURE IS NOT UPDATED");


			delay_ms(1000);

			

			Write_CMD_LCD(0x01);	


		}
	}


	else

	{

		Write_CMD_LCD(0xC0);

		Write_str_LCD("ERROR1");

		delay_ms(1000);

		Write_CMD_LCD(0x01);		

		return;

	}

}		  




void esp01_sendToThingspeak2(float val)


{

//	Write_CMD_LCD(0x01);

//	Write_CMD_LCD(0x80);

//	Write_str_LCD("AT+CIPSTART");

	delay_ms(1000);


	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");


	i=0;memset(buff,'\0',200);


	while(i<5);


	delay_ms(2500);


	buff[i] = '\0';


//	Write_CMD_LCD(0x01);


//	Write_CMD_LCD(0x80);


//	Write_str_LCD(buff);


	delay_ms(2000);


	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{


//		Write_CMD_LCD(0xC0);


//		Write_str_LCD("OK");


		delay_ms(1000);


		


	//	Write_CMD_LCD(0x01);

  
//		Write_CMD_LCD(0x80);


//		Write_str_LCD("AT+CIPSEND");


		delay_ms(1000);


		UART0_Str("AT+CIPSEND=51\r\n");


		i=0;memset(buff,'\0',200);


		//while(buff[i] != '>');


		delay_ms(500);


		//need to change the thingspeak write API key accordind to your channel

		//ex: UART0_Str("GET /update?api_key=MMLFKIA5R2RDFPW5&field1=");

		UART0_Str("GET /update?api_key=XN99FUUM8IXTHFLY&field2=");
		
		//UART0_Str(val);
		
		UART0_Float(val);

		UART0_Str("\r\n\r\n");
		
		delay_ms(5000);
		
		delay_ms(5000);
		
		buff[i] = '\0';

		//Write_CMD_LCD(0x01);
			
		//Write_CMD_LCD(0x80);

		//Write_str_LCD(buff);


		delay_ms(2000);


		if(strstr(buff,"SEND OK"))


		{


//			Write_CMD_LCD(0x01);


		//	Write_str_LCD("DATA UPDATED");


			delay_ms(1000);			


//			Write_CMD_LCD(0x01);
		}


		else


		{


			Write_CMD_LCD(0x01);


			Write_str_LCD("HUMIDITY IS NOT UPADTED");


			delay_ms(1000);

			

			Write_CMD_LCD(0x01);	


		}
	}


	else

	{

		Write_CMD_LCD(0xC0);

		Write_str_LCD("ERROR2");

		delay_ms(1000);

		Write_CMD_LCD(0x01);

		return;

	}

}  


void esp01_sendToThingspeak3(float val)
{
    // Write_CMD_LCD(0x01);
    // Write_CMD_LCD(0x80);
    // Write_str_LCD("AT+CIPSTART");

    delay_ms(1000);

    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

    i = 0;
    memset(buff, '\0', 200);

    while(i < 5);

    delay_ms(2500);

    buff[i] = '\0';

    // Write_CMD_LCD(0x01);
    // Write_CMD_LCD(0x80);
    // Write_str_LCD(buff);

    delay_ms(2000);

    if(strstr(buff, "CONNECT") || strstr(buff, "ALREADY CONNECTED"))
    {
        // Write_CMD_LCD(0xC0);
        // Write_str_LCD("OK");

        delay_ms(1000);

        // Write_CMD_LCD(0x01);
        // Write_CMD_LCD(0x80);
        // Write_str_LCD("AT+CIPSEND");

        delay_ms(1000);

        UART0_Str("AT+CIPSEND=51\r\n");

        i = 0;
        memset(buff, '\0', 200);

        // while(buff[i] != '>');

        delay_ms(500);

        // Change the ThingSpeak Write API key according to your channel
        UART0_Str("GET /update?api_key=XN99FUUM8IXTHFLY&field3=");				  					

        UART0_Float(val);

        UART0_Str("\r\n\r\n");

        delay_ms(5000);
        delay_ms(5000);

        buff[i] = '\0';

        // Write_CMD_LCD(0x01);
        // Write_CMD_LCD(0x80);
        // Write_str_LCD(buff);

        delay_ms(2000);

        if(strstr(buff, "SEND OK"))
        {
           // Write_CMD_LCD(0x01);
            //Write_str_LCD("DATA UPDATED");
            delay_ms(1000);

            //Write_CMD_LCD(0x01);
        }
        else
        {
            Write_CMD_LCD(0x01);
            Write_str_LCD("MOTOR DATA NOT UPDATED");
            delay_ms(1000);

            Write_CMD_LCD(0x01);
        }
    }
    else
    {
        Write_CMD_LCD(0xC0);
        Write_str_LCD("ERROR2");
        delay_ms(1000);

        Write_CMD_LCD(0x01);

        return;
    }
}
