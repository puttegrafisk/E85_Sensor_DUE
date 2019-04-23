/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */



// Brainstorm more shit!

#include <due_can.h>
#include "variant.h"
//Beginning of Auto generated function prototypes by Atmel Studio
void ReadSRAM(byte AdressH, byte AdressL);
void SENDCAN(int Adress, byte byte0, byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7);
void SENDCAN1(int Adress, byte byte0, byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7);
void WriteSID(char Text12, char Text012);
void EndSID();
void Ping();
void Change(bool MANUAL);
void Frequency();
void WriteSRAM(char ADR4, char c1, char c2);
void WriteValue(int Dis);
void Buttons();
//End of Auto generated function prototypes by Atmel Studio



int const POT = A0;
int const MAN_SW = A4;
int const E85 = A2;

int const DisplayMAX = 7;

#define Man 0
#define Auto 1


bool SRAM;
bool MAN;
bool ON = 1;
bool SIDPrev = 0;
bool SIDPrev1 = 0;
bool SIDPrev2 = 0;
bool SIDPrev3 = 0;
bool Error = 0;
unsigned long Time;
int Avg;
int Volt;
int Times;
int Display = 0;
byte SRAMbyte[6];
char Message1[13] = "message done";


void ReadSRAM(byte AdressH,byte AdressL){
  //Serial.println("ReadSRAM1");
 int Adr;
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, AdressH, AdressL, 0x00, 0x00, 0xC7);
 //Serial.println("ReadSRAM2");


}


void SENDCAN(int Adress, byte byte0, byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7){
  CAN_FRAME MSG;
  MSG.id = Adress;
  MSG.length = 8;
  byte Chunks[8] = {byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7};
  for(int i; i < 8; i++){
    MSG.data.bytes[i] = Chunks[i];
  }
  if(Can0.sendFrame(MSG) == 1) Serial.println("CAN_SENT");
  else Serial.println("CAN_FAAAAIL");
}


void SENDCAN1(int Adress, byte byte0, byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7){
  CAN_FRAME MSG;
  MSG.id = Adress;
  MSG.length = 8;
  byte Chunks[8] = {byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7};
  for(int i; i < 8; i++){
    MSG.data.bytes[i] = Chunks[i];
  }
  Can1.sendFrame(MSG);
}


void WriteSID(char Text[12], char Text0[12] ) {


  if(ON == 1){
    
  SENDCAN(0x368, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x368, 0, 8, Pre0);
  //delay(10);
  SENDCAN(0x368, 0x01, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x368, 0, 8, Pre1);
  //delay(10);
  SENDCAN(0x368, 0x02, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x368, 0, 8, Pre2);
  //delay(10);

  SENDCAN(0x328, 0x45, 0x96, 0x01, Text[0],   Text[1],   Text[2],  Text[3],  Text[4]);  //CAN0.sendMsgBuf(0x328, 0, 8, Data0);
  //delay(10);
  SENDCAN(0x328, 0x04, 0x96, 0x01, Text[5],   Text[6],   Text[7],  Text[8],  Text[9]); //CAN0.sendMsgBuf(0x328, 0, 8, Data1);
  //delay(10);
  SENDCAN(0x328, 0x03, 0x96, 0x01, Text[10],   Text[11],   0x00,  0x00,  0x00); //CAN0.sendMsgBuf(0x328, 0, 8, Data2);
  //delay(10);
  SENDCAN(0x328, 0x02, 0x96, 0x02, Text0[0],   Text0[1],   Text0[2],  Text0[3],  Text0[4]); //CAN0.sendMsgBuf(0x328, 0, 8, Data3);
  //delay(10);
  SENDCAN(0x328, 0x01, 0x96, 0x02, Text0[5],   Text0[6],   Text0[7],  Text0[8],  Text0[9]); //CAN0.sendMsgBuf(0x328, 0, 8, Data4);
  //delay(10);
  SENDCAN(0x328, 0x00, 0x96, 0x02, Text0[10],   Text0[11],   0x00,  0x00,  0x00); //CAN0.sendMsgBuf(0x328, 0, 8, Data5); 
  //delay(10);
  
  SENDCAN(0x348, 0x11, 0x01, 0x04, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, Pre3);
  //delay(10);
  SENDCAN(0x348, 0x11, 0x02, 0x05, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, Pre4);
 }
  }


void EndSID(){
  
byte END0[8] = {0x11, 0x01, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00};
//delay(2);
byte END1[8] = {0x11, 0x02, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00};
  
  SENDCAN(0x348, 0x11, 0x01, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, END0);
  SENDCAN(0x348, 0x11, 0x02, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, END1);
  }


void Ping() {

  byte Peep[8] = {0x80, 0x04, 0, 0, 0, 0, 0, 0} ;

  SENDCAN(0x430, 0x80, 0x04, 0, 0, 0, 0, 0, 0); //CAN0.sendMsgBuf(0x430, 0, 8, Peep); 
}


void Change(bool MANUAL) {

if(ON == 1) Ping();
if(MANUAL == Man) {
  Serial.println("MANUAL");
  WriteSID( "" , "   Manual   ");
}
else if(MANUAL == Auto) {
  
  Serial.println("AUTO");
  WriteSID( "" , "   Auto     ");
}
delay(1000);
EndSID();
}


void Frequency() {

if(micros() > 4294667295) delay(500);
  
 unsigned long Period;
 Time = millis();
 while(E85 == HIGH){
  if(millis() > Time + 6) break;
 }
 Time = millis();
 while(E85 == LOW){
  if(millis() > Time + 20) break;
 }
 Time = micros();
 while(E85 == HIGH){
  if(micros() > Time + 6000) break;
 }
 while(E85 == LOW){
  if(micros() > Time + 20000) break;
 }
 Period = micros() - Time;
 
 Avg = 1000000 / Period;
}

void WriteSRAM(char ADR[4], char c1, char c2) {

 
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57,   0xC4);
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, ADR[0], 0xC4);
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, ADR[1], 0xC4);
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, ADR[2], 0xC4);
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, ADR[3], 0xC4);
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, c1,     0xC4);
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, c2,     0xC4);
 SENDCAN1(0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D,   0xC4);
 }
 

void WriteValue(int Dis){

 if(Dis == 0){
  ReadSRAM(0x77, 0x04);
  String Answer = String(SRAMbyte[0]);
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[5] = 'B' ;
  Message1[6] = 'l' ;
  Message1[7] = 'e' ;
  Message1[8] = 'n' ;
  Message1[9] = 'd' ;
  
 }
 else if(Dis == 1){
  ReadSRAM(0x10, 0x1B);
  String Answer = String(SRAMbyte[0]);
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[5] = 'B' ;
  Message1[6] = 'a' ;
  Message1[7] = 't' ;
  Message1[8] = 't' ;
  Message1[10] = 'V' ;
 }
 else if(Dis == 2){
  ReadSRAM(0x10, 0x33);
  String Answer = String(SRAMbyte[0]);
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[5] = 'M' ;
  Message1[6] = 'a' ;
  Message1[7] = 'n' ;
  Message1[8] = 'i' ;
  Message1[10] = 'T' ;
 }
 else if(Dis == 3){
  ReadSRAM(0x10, 0x13);
  String Answer = String(SRAMbyte[0]);
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[5] = 'M' ;
  Message1[6] = 'a' ;
  Message1[7] = 'n' ;
  Message1[8] = 'i' ;
  Message1[10] = 'P' ;
 }
 else if(Dis == 4){
  ReadSRAM(0x10, 0x1C);
  String Answer = String(SRAMbyte[0]);
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[5] = 'S' ;
  Message1[6] = 'p' ;
  Message1[7] = 'e' ;
  Message1[8] = 'e' ;
  Message1[9] = 'd' ;
 }
 else if(Dis == 5){
  ReadSRAM(0x10, 0x31);
  String Answer = String(SRAMbyte[0]);
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[5] = 'L' ;
  Message1[6] = 'a' ;
  Message1[7] = 'm' ;
  Message1[8] = 'I' ;
  Message1[9] = 'n' ;
  Message1[10] = 't' ;
 }
 else if(Dis == 6){
  ReadSRAM(0x10, 0x2E);
  String Answer = String(SRAMbyte[0]);
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[5] = 'W' ;
  Message1[6] = 'a' ;
  Message1[7] = 't' ;
  Message1[8] = 'e' ;
  Message1[9] = 'r' ;
  Message1[10] = 'T' ;
 }
 else if(Dis == 7){
  ReadSRAM(0x10, 0xF2);
  int text = SRAMbyte[1] + (SRAMbyte[0] * 0x100);
  String Answer = String(text);
  Message1[0] = Answer.charAt(0);
  Message1[1] = Answer.charAt(1);
  Message1[2] = Answer.charAt(2);
  Message1[3] = Answer.charAt(3);
  Message1[4] = Answer.charAt(4);
  Message1[5] = 'M' ;
  Message1[6] = 'i' ;
  Message1[7] = 's' ;
  Message1[8] = 's' ;
  Message1[9] = 'F' ;
 }}


void setup() {
  
  Serial.begin(115200);
  Serial.println("Starting");
  Can0.begin(47619);
  Can1.begin(615000);
  Serial.println("Starting");
  Can0.setBigEndian(true);
  Can1.setBigEndian(true);
  //Can0.setRXFilter(0, 0x290, false);
  Can0.watchFor(0x290);
  Can1.watchFor(0x0C);
  
  
 pinMode(POT , INPUT);
 pinMode(MAN_SW , INPUT);
 pinMode(E85 ,INPUT);
 Serial.println(Message1);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
 WriteSID("Welcome     ", "Onboard     ");
 Serial.println("Welcome");
 delay(1000);
  Serial.println(Message1);
}



void Buttons(){
  Serial.println("Buttons");
  CAN_FRAME *SID;
  Can0.get_rx_buff(*SID);
 if(SID->id == 0x290){ 
  Serial.println(SID->data.bytes[5], HEX);
  if(SID->data.bytes[3] == 0x40){
    if(SIDPrev1 == 0 && ON == 1){ 
      if(SRAM == 1){
        SRAM = 0;
        
      }else if(SRAM == 0) {
        SRAM = 1;
        
      }
      Ping();
      SIDPrev1 = 1;
     }
   }
   else SIDPrev1 = 0;

  if(SID->data.bytes[5] == 0xC0){
     if(SIDPrev == 0){ 
      if(ON == 1){
        ON = 0;
        EndSID();
      }else if(ON == 0) ON = 1;
      Ping();
      SIDPrev = 1;
     }
   }
   else SIDPrev = 0;

  if(SID->data.bytes[3] == 0x10){
     if(SIDPrev2 == 0 && Display < DisplayMAX){     
        Display = Display + 1;
        Ping();
      }
      
      SIDPrev2 = 1;
     
   }
   else SIDPrev2 = 0;

   if(SID->data.bytes[3] == 0x20){
     if(SIDPrev3 == 0 && Display > 0){     
        Display = Display - 1;
        Ping();
      }
      
      SIDPrev3 = 1;
     
   }
   else SIDPrev3 = 0;
}}



void loop(){
  Serial.println("loop");
if(Times > 20) Times = 0;
char Message[12];
Avg = 0; 
int percent;
Volt = 0;
int Res;
for(int i; i < 6; i++){
 SRAMbyte[i] = 0; 
}
 
for(int i; i < 12; i++){
 Message1[i] = 0; 
}
 

Message[0] = ' ' ;
Message[1] = ' ' ;
Message[2] = ' ' ; 
Message[3] = '%' ; 
Message[4] = ' ' ; 
Message[5] = 'E' ; 
Message[6] = '8' ; 
Message[7] = '5' ; 
Message[8] = ' ' ; 
Message[9] = ' ' ; 

if(SRAM == 1){
 Message[10] = 'S' ; 
 Message[11] = 'R' ;  
}
else if(SRAM == 0){
 Message[10] = 'V' ; 
 Message[11] = 'O' ; 
}
CAN_FRAME *frame;
if(Can1.rx_avail() == 1){
   Can1.get_rx_buff(*frame);
  if(frame->id == 0x0C){
    SRAMbyte[0] = frame->data.bytes[5];
    SRAMbyte[1] = frame->data.bytes[4];
    SRAMbyte[2] = frame->data.bytes[3];
    SRAMbyte[3] = frame->data.bytes[2];
    SRAMbyte[4] = frame->data.bytes[1];
    SRAMbyte[5] = frame->data.bytes[0];
  }}

WriteValue(Display);
  
 //Serial.println("Display");

//Serial.println("After Disp");

if(digitalRead(MAN_SW) == 1) {
 if(MAN == 0) Change(Man);
 
 //Serial.println("Reo");
Res = ((4096.0)/(analogRead(POT)) - 1) * 100; // SAAB Reostat
Res = constrain(Res, 4, 1120);
Volt = map(Res, 1120, 4, 0, 4096);
 
  MAN = 1;
}
else if(digitalRead(MAN_SW) == 0) {
  if(MAN == 1) Change(Auto);

 
 //Serial.println("Before Freq");
Frequency();
 //Serial.println("After Freq");
Volt = map(Avg, 50, 125, 0, 4096);

  MAN = 0;
}

percent = map(Volt, 0, 4096, 0, 100);

Message[2] = percent % 10 + 48;
Message[1] = (percent - (percent % 10))/10 + 48;
if(percent == 100) {
Message[0] = '1';
Message[1] = '0';
Message[2] = '0';
}
 
if(percent < 0 || percent > 100) {
 if(Error == 0){
  Ping();
  Error = 1;
 }
 
Message[0] = 'E' ;
Message[1] = 'R' ;
Message[2] = 'R' ; 
Message[3] = 'O' ; 
Message[4] = 'R' ; 
Message[5] = ' ' ; 
Message[6] = 'V' ; 
Message[7] = 'A' ; 
Message[8] = 'L' ; 
Message[9] = 'U' ; 
Message[10] = 'E' ; 
Message[11] = ' ' ; 

if(pulseIn(E85, HIGH, 100000) == 0){

Message[6] = 'S' ; 
Message[7] = 'E' ; 
Message[8] = 'N' ; 
Message[9] = 'S' ; 
Message[10] = 'O' ; 
Message[11] = 'R' ; 
  
}
  
}else Error = 0;
 
if(Error == 0 && SRAM == 0) analogWrite(DAC1, Volt);
else if(Error == 0 && SRAM == 1){
  byte Value = map(Volt, 0, 4096, 0, 255);
  Value = constrain(Value, 0, 255);
  String Info = String(Value, HEX);
  if(Times == 20){
   digitalWrite(DAC1, LOW);
   WriteSRAM("7704", Info.charAt(0), Info.charAt(1));
  }
  Times = Times + 1;
}

WriteSID(Message1 , Message);
if (Can0.rx_avail() == 1) Buttons();
/*Serial.println(Volt);
Serial.println(MAN);
Serial.println(Res);
Serial.println(Message1);
Serial.println(Message);*/
 
// Time = millis();
 //while(millis() < Time + 50){


 
 
//}
 }
