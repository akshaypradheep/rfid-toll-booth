//ReadTag.ino

char input[12];				
int count = 0;				
			
void setup()
{
	Serial.begin(9600);		
	
}
void loop()
{      
  
     
	if(Serial.available())// check serial data ( RFID reader)
	{
		count = 0; // Reset the counter to zero
		/* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is	empty 
		   or till 12 Bytes (the ID size of our Tag) is read */
		while(Serial.available() && count < 12) 
		{
			input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
			count++; // increment counter
			delay(5);
		}
                Serial.println("I received: ");
                for(int i=0;i<12;i++)
                Serial.print(input[i]);
		Serial.println();
		
        }


}