#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"


#define ANSWERSIZE 3

//Variables for rtc:
RTC_DS1307 rtc;
bool isPass;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char daysOff[7][12]={"Sun"};
static boolean PowerCycled = true;

//Variables for basic
String answer = "PAM";
String str_recieved_from_RPi = "";
char str[256];
char tmp;
int alarm_hour;
int alarm_minute;



void setup() {
  Wire.begin(9);
//  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  Wire.onReceive(receiveEvent); // data slave received
  Serial.begin(9600);
  Serial.println("I2C Slave ready!");

  Serial.begin(9600);
 isPass = false;
 if (! rtc.begin())
 {
   Serial.print("Couldn't find RTC");
   while (1);
 }

  if (! rtc.isrunning())
 {
   Serial.print("RTC is NOT running!");
   Serial.println();
 }

// rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void receiveEvent(int byteCount) {
  Serial.println("x");
  int count = 0;
  while ( Wire.available()) {
  
   tmp = (char)Wire.read();
//   Serial.println(tmp);
   str[count]=tmp;
   count++;
   str_recieved_from_RPi+=tmp;
  }
  
  for (int i =1; i<count;i++){
    Serial.println(str[i]);
  }
  String function="";
  function=function+str[1];
  
  //Thiết lập thời gian bật mạch Raspberry Pi
  if (function=="w"){
    Serial.println("Set wake up ....");
    String hour = "";
    hour = hour+str[2]+str[3];
    String minute = "";
    minute = minute+str[4]+str[5];
    alarm_hour = hour.toInt();
    alarm_minute = minute.toInt();
    Serial.print(alarm_hour);
    Serial.print(":");
    Serial.println(alarm_minute);
    Serial.println("Reset to not pass");
    isPass=false;
  }
}

void requestEvent() {
  byte response[ANSWERSIZE];
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response,sizeof(response));
  Serial.println("Request event");
}

void wake_up(){
  Serial.println("Wake up action .... ");
  digitalWrite(3, LOW);
  delay(1000);  
  digitalWrite(3, HIGH);
}

void time_loop(){
  DateTime now = rtc.now();
   
   if(now.hour() == alarm_hour && now.minute()==alarm_minute && !isPass ){
    Serial.println(now.dayOfTheWeek());
    if(now.dayOfTheWeek()==6){
    Serial.println("Is Sat");
    }
    wake_up();
    isPass= true;
   }

   if(isPass){
    if(now.hour()==alarm_hour && now.minute()>alarm_minute){
      isPass=false;
    }
   }
   if(now.hour()<=9)
   {
     Serial.print("0");
     Serial.print(now.hour());
   }
   else {
    Serial.print(now.hour());
   }
   Serial.print(':');
   if(now.minute()<=9)
   {
     Serial.print("0");
     Serial.print(now.minute());
   }
   else {
    Serial.print(now.minute());
   }
   Serial.print(':');
   if(now.second()<=9)
   {
     Serial.print("0");
     Serial.print(now.second());
   }
   else {
    Serial.print(now.second());
   }
   Serial.println();

   Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
   Serial.print(",");
   if(now.day()<=9)
   {
     Serial.print("0");
     Serial.print(now.day());
   }
   else {
    Serial.print(now.day());
   }
   Serial.print('/');
   if(now.month()<=9)
   {
     Serial.print("0");
     Serial.print(now.month());
   }
   else {
    Serial.print(now.month());
   }
   Serial.print('/');
   if(now.year()<=9)
   {
     Serial.print("0");
     Serial.print(now.year());
   }
   else {
    Serial.print(now.year());
   } 
   Serial.println();
   delay(1000);
}
void loop() {
  time_loop();
}
