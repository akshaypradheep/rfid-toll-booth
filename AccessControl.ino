//AccessControl.ino

#define Ready 8
#define Relay 10
#define Warning 9
char tag[] ="12006202C4B6"; // Replace with your Tag ID
char input[12];				
int count = 0;				
boolean match = 0;			
void setup()
{
	Serial.begin(9600);
        pinMode(Ready,OUTPUT);		
	pinMode(Relay,OUTPUT);	
	pinMode(Warning,OUTPUT); 
}
void loop()
{        
        digitalWrite(Ready,HIGH);
  
	if(Serial.available())// check serial data ( RFID reader)
	{        
    digitalWrite(Ready,LOW);
		count = 0; // Reset the counter to zero
		while(Serial.available() && count < 12) 
		{
			input[count] = Serial.read(); 
			count++;
			delay(5);
		}
		if(count == 12) // 
		{
			count =0; // reset counter varibale to 0
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
		if(match == 1) 
		{
			Serial.println("Congratulation Access Allowed");
			digitalWrite(Relay,HIGH);
			delay (5000);				
			digitalWrite (Relay,LOW);
		}
		else
		{
			Serial.println("Access Denied"); // Incorrect Tag Message
			digitalWrite(Warning,HIGH);
			delay(500);
			digitalWrite(Warning,LOW);
		}
		for(count=0; count<12; count++) 
		{
			input[count]= 'F';
		}
		count = 0;
	}
}
