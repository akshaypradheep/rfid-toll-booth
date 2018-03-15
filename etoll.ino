 #include <EEPROM.h>  
 #include<Servo.h>
 Servo gate;
int count,j,i,list_flag;
const int rcSw = 7;
char input[12];  
char list[4][13]={"180001FA7F9C","18003DA5C949","120062414475","12006202C4B6"};
char name[4][17]={"KL08AK47","KL08AB8055","KL08AC5451","KL08AC001"};
int blnc[4];
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  gate.attach(3);
  pinMode(rcSw,INPUT);
}

void loop() {
  if (Serial1.available()) {
      count = 0;
      while(count < 12)          // Read 12 characters and store them in input array
      {
         input[count] = Serial1.read();
         count++;
         delay(10);
      }
  }
//Serial.println(input);
for(j=0;j<4;j++)
      {
        for(i=0;i<11;i++)
        {
          if(list[j][i]==input[i])
          list_flag=j;
          else
          list_flag=7;
        }
      if(list_flag==j)
      break;
      }

      
    readBlnc();
    if(list_flag == 0){
     access(0);
     recharge(0);
    }
    if(list_flag == 1){
     access(1);
     recharge(1);
    }
    if(list_flag == 2){
      access(2);
      recharge(2);
    }
    if(list_flag == 3){
      access(3);
      recharge(3);
    }

    //-----------------------------------------------------------------------------------
    for(count=0; count<12; count++) 
    {
      input[count]= 'F';
    }
    count = 0;
}
void readBlnc(){
  int i;
  for(i=0;i<4;i++){
    blnc[i] = EEPROM.read(i);
  }
}
void access(int n){
  if(blnc[n]>0){
    int temp = (blnc[n])-1;
    EEPROM.write(n,temp);
      Serial.print(name[list_flag]);
      Serial.print("________________Allowed___Balence :");
      Serial.println(temp);
      list_flag = 10;
      gate.write(0);
      delay(1000);
      gate.write(0);
  }
  else{
    Serial.println("Reacharge Your account");
    gate.write(90);
  }
  gate.write(90);
}
void recharge(int n){
  if(digitalRead(rcSw)==HIGH){
  EEPROM.write(n,10);
  Serial.println("Recharge was succesfull");
}
}


