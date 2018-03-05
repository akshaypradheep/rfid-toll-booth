//=======================================gsm================================================
#include <GSM.h>
#include <Servo.h>
GSM gsmAccess; 
GSM_SMS sms;
char remoteNumber[20]= "9633184689";
//============================================================================================
char tag[20] ="12006202C4B6"; 
char input[12];				
int count = 0;
int blnc = 10;		
boolean match = 0;			
void setup()
{
	Serial.begin(9600);
  
}
void loop()
{        
  //======================================= READ The data =============================================
	if(Serial.available())
	{        
		count = 0; 
		while(Serial.available() && count < 12) 
		{
			input[count] = Serial.read(); 
			count++;
			delay(5);
		}
  //============================================= check wether the rfid is match =======================
		if(count == 12)  
		{
			count =0;
			match = 1;
			while(count<12 && match !=0)  
			{
				if(input[count]==tag[count])
				  match = 1; 
				else
				  match= 0;
				  count++; 
			}
		}
  // ===================================================================================================
		if(match == 1 && blnc > 0) 
		{
			Serial.println("Congratulation Access Allowed");
      
      sms.beginSMS(remoteNumber);
      sms.print("happy journy your balenc is ");
      sms.endSMS(); 
		}
		if(match == 1 && blnc <= 0)
		{
			Serial.println("recharge your account"); // Incorrect Tag Message
      sms.beginSMS(remoteNumber);
      sms.print("recharge your account");
      sms.endSMS(); 
		}
    else{
      Serial.print("acces denined");
    }
		for(count=0; count<12; count++) 
		{
			input[count]= 'F';
		}
		count = 0;
	}
}

 

