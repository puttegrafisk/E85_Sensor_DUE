// A program that takes the value from a continental E85 sensor and sends the value to the SRAM of a SAAB T5 ECU

// note that you can hook up a button and a SAAB Reostat to control the E85 amount manually. 
// Added that for debugging and as a fail-safe for the sensor.

#include <due_can.h> 
#include "variant.h" 

int const POT = A0;
int const MAN_SW = A4;
int const E85 = A2;

int const DisplayMAX = 7; 

#define Man 0
#define Auto 1

bool Switch;
bool Dual = 1;
bool SRAM = 1;
bool MAN;
bool ON = 0;
bool SIDPrev = 0;
bool SIDPrev1 = 0;
bool SIDPrev2 = 0;
bool SIDPrev3 = 0;
bool SIDPrev4 = 0;
bool SIDPrev5 = 0;
bool Error = 0;
unsigned long Time;
int Avg;
int Volt;
int Times;
int Display = 0;
byte SRAMbyte[6];
char Message1[13] = "message done";
char Message[13];
int Seq;
int Prevseq;
int Loopseq;
unsigned long Looptime;
char ADR[4];
char c1;
char c2;
int ErrorTimes;

CAN_FRAME SID;
CAN_FRAME MSG;
CAN_FRAME frame;
CAN_FRAME Ack;

void ReadSRAM(unsigned long adress){ //Sends a command to read an (or a few) SRAM bytes
  
  //Serial.println("ReadSRAM1"); //debugging
 
 SENDCAN1(0x5, 0xC7, byte((adress + 5) >> 24 & 0xFF), byte((adress + 5) >> 16 & 0xFF), byte((adress + 5) >> 8 & 0xFF), byte((adress + 5) & 0xFF), 0x00, 0x00, 0x00);
 
 //Serial.println("ReadSRAM2"); //debugging


}


void SENDCAN(int Adress, byte byte0, byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7){
  //a function to simplify sending CANBUS messages. I-BUS
  
  MSG.id = Adress;
  MSG.extended = false;
  MSG.priority = 0;
  MSG.length = 8;
  byte Chunks[8] = {byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7};
  
    MSG.data.bytes[0] = Chunks[0];
    MSG.data.bytes[1] = Chunks[1];
    MSG.data.bytes[2] = Chunks[2];
    MSG.data.bytes[3] = Chunks[3];
    MSG.data.bytes[4] = Chunks[4];
    MSG.data.bytes[5] = Chunks[5];
    MSG.data.bytes[6] = Chunks[6];
    MSG.data.bytes[7] = Chunks[7];
  
  if(Can0.sendFrame(MSG) == 1) Serial.println("CAN_SENT");
  else Serial.println("CAN_FAIL");
}


void SENDCAN1(int Adress, byte byte0, byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7){
  //a function to simplify sending CANBUS messages. P-BUS

  
  MSG.id = Adress;
  MSG.extended = false;
  MSG.priority = 0;
  MSG.length = 8;
  byte Chunks[8] = {byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7};
  
    MSG.data.bytes[0] = Chunks[0];
    MSG.data.bytes[1] = Chunks[1];
    MSG.data.bytes[2] = Chunks[2];
    MSG.data.bytes[3] = Chunks[3];
    MSG.data.bytes[4] = Chunks[4];
    MSG.data.bytes[5] = Chunks[5];
    MSG.data.bytes[6] = Chunks[6];
    MSG.data.bytes[7] = Chunks[7];
    
  if(Can1.sendFrame(MSG) == 1) Serial.println("CAN1_SENT");
  else Serial.println("CAN1_FAIL");
}


void WriteSID(char Text[13], char Text0[13] ) {
  // funtion for taking 2 character arrays and displaying them on the SID-diplay. Dual = both rows

  if(ON == 1){
    
  
  if(Dual == 1){
  SENDCAN(0x328, 0x45, 0x96, 0x81, Text[0],   Text[1],   Text[2],  Text[3],  Text[4]);  //CAN0.sendMsgBuf(0x328, 0, 8, Data0);
  //delay(1);
  SENDCAN(0x328, 0x04, 0x96, 0x01, Text[5],   Text[6],   Text[7],  Text[8],  Text[9]); //CAN0.sendMsgBuf(0x328, 0, 8, Data1);
  //delay(1);
  SENDCAN(0x328, 0x03, 0x96, 0x01, Text[10],   Text[11],   0x00,  0x00,  0x00); //CAN0.sendMsgBuf(0x328, 0, 8, Data2);
  //delay(1);
  SENDCAN(0x328, 0x02, 0x96, 0x82, Text0[0],   Text0[1],   Text0[2],  Text0[3],  Text0[4]); //CAN0.sendMsgBuf(0x328, 0, 8, Data3);
  //delay(1);
  }
  else if(Dual == 0) SENDCAN(0x328, 0x42, 0x96, 0x82, Text0[0],   Text0[1],   Text0[2],  Text0[3],  Text0[4]);
  SENDCAN(0x328, 0x01, 0x96, 0x02, Text0[5],   Text0[6],   Text0[7],  Text0[8],  Text0[9]); //CAN0.sendMsgBuf(0x328, 0, 8, Data4);
  //delay(1);
  SENDCAN(0x328, 0x00, 0x96, 0x02, Text0[10],   Text0[11],   0x00,  0x00,  0x00); //CAN0.sendMsgBuf(0x328, 0, 8, Data5); 
  //delay(1);

  if(Dual == 1) SENDCAN(0x348, 0x11, 0x01, 0x05, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, Pre3);
  //delay(1);
  SENDCAN(0x348, 0x11, 0x02, 0x05, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, Pre4);
 }
  }


void EndSID(bool One, bool Two){
  //Function for telling the SID that i'm done sending text to it
  
  
//byte END0[8] = {0x11, 0x01, 0xFF, 0x19, 0x00, 0x00, 0x00, 0x00}; //for reference only 
//delay(2);
//byte END1[8] = {0x11, 0x02, 0xFF, 0x19, 0x00, 0x00, 0x00, 0x00};


  
  if(One == 1) SENDCAN(0x348, 0x11, 0x01, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, END0);
  //delay(1);
  if(Two == 1) SENDCAN(0x348, 0x11, 0x02, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00); //CAN0.sendMsgBuf(0x348, 0, 8, END1);
  }


void Ping() {
  // Makes the SID send out an aural chime in the form of a "ding" 

  //byte Peep[8] = {0x80, 0x04, 0, 0, 0, 0, 0, 0} ; //for reference only

  SENDCAN(0x430, 0x80, 0x04, 0, 0, 0, 0, 0, 0); //CAN0.sendMsgBuf(0x430, 0, 8, Peep); 
}


void Change(bool MANUAL) {
  // Checks if the "manual" button is pressed or not, sends a chime and says manual or auto on the SID
  

if(ON == 1) Ping();
if(MANUAL == Man) {
  Serial.println("MANUAL");
  WriteSID( Message1 , "   Manual   ");
}
else if(MANUAL == Auto) {
  
  Serial.println("AUTO");
  WriteSID( Message1 , "   Auto     ");
}
delay(500);
if(ON == 0) EndSID(1, 1);
}


void Frequency() {
  //The E85 sensor sends out a frequency that depends on the E85 amount, here we read the frequency.
  //PulseL or PulseH's period (not sure which one) can be used to get the fuel temperature.


 unsigned long PulseL;
 unsigned long PulseH;
 unsigned long FPeriod;
 unsigned long Period;
 
 PulseL = pulseIn(E85, LOW,  50000);
 PulseH = pulseIn(E85, HIGH, 50000);

 FPeriod = PulseL + PulseH;
 Avg = 1000000 / FPeriod;
}

void WriteSRAM(char ADr[4], char C1, char C2) { // function for writing data to the SRAM
  //ADr is 4 ascii characters refering to the SRAM adress in HEX. C1 and C2 are together the value of the written byte in Hex (ascii characters)
switch(Seq){ //determines at which message in the sequence we are
 case 0: 
 for(int i; i < 4; i++){ADR[i] = ADr[i];}
 c1 = C1;
 c2 = C2;
 SRAMmessage(0x57);
 break;
 case 1:
 SRAMmessage(ADR[0]);
 break;
 case 2:
 SRAMmessage(ADR[1]);
 break;
 case 3:
 SRAMmessage(ADR[2]);
 break;
 case 4:
 SRAMmessage(ADR[3]);
 break;
 case 5:
 SRAMmessage(c2);
 break;
 case 6:
 SRAMmessage(c1);
 break;
 case 7:
 Seq = -1;
 SRAMmessage(0x0D);
 break;
 
 }}
void SRAMmessage(byte Data){ //Sends the next message in the sequence
SENDCAN1(0x06, 0xC4, Data, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
   Prevseq = Seq;
}


void WriteValue(int Dis){ //takes the value from a specific SRAM byte and writes it to the next SID message

 if(Dis == 0){
  ReadSRAM(0x7704); //symbol for E85 amount
  String Answer = String(map(SRAMbyte[0], 0, 255, 0, 100));
  Message1[0] = ' ' ;
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[4] = ' ' ;
  Message1[5] = 'B' ;
  Message1[6] = 'l' ;
  Message1[7] = 'e' ;
  Message1[8] = 'n' ;
  Message1[9] = 'd' ;
  Message1[10] = ' ' ;
  Message1[11] = ' ' ;
  
 }
 else if(Dis == 1){
  ReadSRAM(0x101B); //symbol for battery voltage
  String Answer = String(SRAMbyte[0]);
  Message1[0] = Answer.charAt(0);
  Message1[1] = Answer.charAt(1);
  Message1[2] = '.' ;
  Message1[3] = Answer.charAt(2);
  Message1[4] = ' ' ;
  Message1[5] = 'B' ;
  Message1[6] = 'a' ;
  Message1[7] = 't' ;
  Message1[8] = 't' ;
  Message1[9] = ' ' ;
  Message1[10] = 'V' ;
  Message1[11] = ' ' ;
 }
 else if(Dis == 2){
  ReadSRAM(0x1033); //symbol for manifol temperature
  String Answer = String(SRAMbyte[0]);
  Message1[0] = ' ' ;
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[4] = ' ' ;
  Message1[5] = 'M' ;
  Message1[6] = 'a' ;
  Message1[7] = 'n' ;
  Message1[8] = 'i' ;
  Message1[9] = ' ' ;
  Message1[10] = 'T' ;
  Message1[11] = ' ' ;
 }
 else if(Dis == 3){
  ReadSRAM(0x1013); //symbol for manifold pressure 
  String Answer = String(SRAMbyte[0]);
  Message1[0] = ' ' ;
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[4] = ' ' ;
  Message1[5] = 'M' ;
  Message1[6] = 'a' ;
  Message1[7] = 'n' ;
  Message1[8] = 'i' ;
  Message1[9] = ' ' ;
  Message1[10] = 'P' ;
  Message1[11] = ' ' ;
 }
 else if(Dis == 4){
  ReadSRAM(0x101C); //symbol for vehicle speed
  String Answer = String(SRAMbyte[0]);
  Message1[0] = ' ' ;
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[4] = ' ' ;
  Message1[5] = 'S' ;
  Message1[6] = 'p' ;
  Message1[7] = 'e' ;
  Message1[8] = 'e' ;
  Message1[9] = 'd' ;
  Message1[10] = ' ' ;
  Message1[11] = ' ' ;
 }
 else if(Dis == 5){
  ReadSRAM(0x1031); // symbol for Lambda intager, used for feul adaption
  String Answer = String(SRAMbyte[0]);
  Message1[0] = ' ' ;
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[4] = ' ' ;
  Message1[5] = 'L' ;
  Message1[6] = 'a' ;
  Message1[7] = 'm' ;
  Message1[8] = 'I' ;
  Message1[9] = 'n' ;
  Message1[10] = 't' ;
  Message1[11] = ' ' ;
 }
 else if(Dis == 6){
  ReadSRAM(0x102E); //symbol for coolant temperature
  String Answer = String(SRAMbyte[0]);
  Message1[0] = ' ' ;
  Message1[1] = Answer.charAt(0);
  Message1[2] = Answer.charAt(1);
  Message1[3] = Answer.charAt(2);
  Message1[4] = ' ' ;
  Message1[5] = 'W' ;
  Message1[6] = 'a' ;
  Message1[7] = 't' ;
  Message1[8] = 'e' ;
  Message1[9] = 'r' ;
  Message1[10] = 'T' ;
  Message1[11] = ' ' ;
 }
 else if(Dis == 7){
  ReadSRAM(0x10F2); // symbol for the missfire counter (reads 2 SRAM bytes at the same time)
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
  Message1[10] = ' ' ;
  Message1[11] = ' ' ;
 }
 
}


void Buttons(){ //function that reads the SID buttons
  
  //Serial.println("Buttons"); //debugging
  
  Can0.get_rx_buff(SID);
 if(SID.id == 0x290){ 
  
  //Serial.println(SID.data.bytes[5], HEX); //debugging

  
  /*if(SID.data.bytes[3] == 0x40){ //old function for setting the E85 value by voltage
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
   else SIDPrev1 = 0;*/

    if(SID.data.bytes[5] == 0x80){ //CLR button, chages between 1 row and 2 rows of the SID
     if(SIDPrev4 == 0 && ON == 1){ 
      if(Dual == 1){
        Dual = 0;
        EndSID(1 , 0);
      }else if(Dual == 0) Dual = 1;
      SIDPrev4 = 1;
     }
   }
   else SIDPrev4 = 0;

  if(SID.data.bytes[5] == 0x30){ // + and - buttons togehter, starts/stops the SID user interface
     if(SIDPrev == 0){ 
      if(ON == 1){
        ON = 0;
        EndSID(1, 1);
      }else if(ON == 0) ON = 1;
      Ping();
      SIDPrev = 1;
     }
   }
   else SIDPrev = 0;

   if(SID.data.bytes[5] == 0x40){ // SET button, swaps the bottom and top row of the SID info
     if(SIDPrev5 == 0 && ON == 1){ 
      if(Switch == 1){
        Switch = 0;
        
      }else if(Switch == 0) Switch = 1;
     
      SIDPrev5 = 1;
     }
   }
   else SIDPrev5 = 0;


  if(SID.data.bytes[3] == 0x10){ //+ button, changes the SRAM byte beeing displayed
     if(SIDPrev2 == 0 && Display < DisplayMAX && ON == 1){ 
        Display = Display + 1;
       
      }
      
      SIDPrev2 = 1;
     
   }
   else SIDPrev2 = 0;

   if(SID.data.bytes[3] == 0x20){ //- button, changes the SRAM byte beeing displayed
     if(SIDPrev3 == 0 && Display > 0 && ON == 1){     
        Display = Display - 1;
        
      }
      
      SIDPrev3 = 1;
     
   }
   else SIDPrev3 = 0;
}}

 
void setup() {
  
  Serial.begin(115200); //setting up the USB and CAN cummunications
  Serial.println("Starting");
  Can0.begin(47619);
  Can1.begin(615384);
  Can1.setBigEndian(true);
  Serial.println("Starting");
  Can0.setBigEndian(true);
  Can1.watchFor(0xC);
  Can0.watchFor(0x290);
  //Can0.setRXFilter(0, 0x290, false);
  
  /*for (int i; i < 8; i++){
 WriteSID("Welcome     ", "Onboard     "); //welcome onboard message for startup, could make the SID bug out and restart sometimes
 Serial.println("Welcome"); //debugging
 delay(700); 
 }//*/
  
  
 pinMode(POT , INPUT);
 pinMode(MAN_SW , INPUT);
 pinMode(E85 ,INPUT);
 Serial.println(Message1);
 Serial.println(Message);
 
 //Dual = 0;
 //ON = 0;
  
 Looptime = millis();
}


void loop(){ 

  //Serial.println("loop");
  if(Can0.available() > 0) Buttons(); //read the buttons
  if(Can1.available() > 0){           //read the other stuff on the P-BUS
   Can1.get_rx_buff(frame);
  if(frame.id == 0xC && frame.data.bytes[0] == 0xC7){
    //Serial.println("CAN1_READ");
    SRAMbyte[0] = frame.data.bytes[7];
    SRAMbyte[1] = frame.data.bytes[6];
    SRAMbyte[2] = frame.data.bytes[5];
    SRAMbyte[3] = frame.data.bytes[4];
    SRAMbyte[4] = frame.data.bytes[3];
    SRAMbyte[5] = frame.data.bytes[2];
  }
  if(frame.id == 0xC && frame.data.bytes[0] == 0xC6 && frame.data.bytes[1] == 0x00){ 
    //if an ack was sent, this send it to the next message in the WriteSRAM sequence
    Seq = Seq + 1;
  }
  }
  
  if(millis() > Looptime + 10000){ //timeout for the WriteSRAM function so it won't get stuck forever if an ack is missed
    Seq = 0;
  }
  if(Seq == 0){
    Looptime = millis();
  }

  if(Error == 0 && SRAM == 0) analogWrite(DAC1, Volt); //an old function for setting the E85 amount by voltage
  else if(Error == 0 && SRAM == 1){
    
  byte Value = map(Volt, 0, 4096, 0, 255); //map the E85 value correctly
  Value = constrain(Value, 0, 255);
  String Info = String(Value, HEX); // turn the value into a an ascii string of the HEX value
  
  for(int i = 0; i < 2; i = i+1 ){
    
    if(isLowerCase(Info.charAt(i))){
      Info.setCharAt(i, Info.charAt(i) - 0x20); //make the characters upper case
    }
  }
  if(true){ // <--- don't know why this is here but hey, it ain't hurting anyone
   
   digitalWrite(DAC1, LOW); //turns of the voltage (if used)
   if(Seq == Prevseq + 1 || Seq == 0){ //checks if T5 has sent and ack
   if(Value >= 0x10)WriteSRAM("7704", Info.charAt(1), Info.charAt(0)); //writes the value to the SRAM
   if(Value < 0x10 && Value != 0) WriteSRAM("7704", Info.charAt(0), '0');
   if(Value == 0) WriteSRAM("7704", '0', '0');
  }}
  Times = Times + 1; 
}
  
if(Times > 10) Times = 0; // a counter that's not used anymore

Avg = 0;     //Reset the variables
int percent; 
Volt = 0;
int Res;

 

 

 Message1[0] = 0; // reset the top SID-row
 Message1[1] = 0; 
 Message1[2] = 0; 
 Message1[3] = 0; 
 Message1[4] = 0;
 Message1[5] = 0;
 Message1[6] = 0;
 Message1[7] = 0;
 Message1[8] = 0;
 Message1[9] = 0;
 Message1[10] = 0;
 Message1[11] = 0;
 
 

 
//Serial.println("Loop");
Message[0] = ' ' ; //reset the bottom line
Message[1] = ' ' ;
Message[2] = ' ' ; 
Message[3] = '%' ; 
Message[4] = ' ' ; 
Message[5] = 'E' ; 
Message[6] = '8' ; 
Message[7] = '5' ; 
Message[8] = ' ' ; 
Message[9] = ' ' ; 

if(SRAM == 1){ //indication of SRAM writing
 Message[10] = 'S' ; 
 Message[11] = 'R' ;  
}
else if(SRAM == 0){ //indicating that the (now unused) voltage mode has been selected
 Message[10] = 'V' ; 
 Message[11] = 'O' ; 
}

WriteValue(Display); 
  
 //Serial.println("Display"); //debugging

//Serial.println("After Disp"); //debugging

if(digitalRead(MAN_SW) == 1) { //check the manual switch
 if(MAN == 0) Change(Man); 
 
 //Serial.println("Reo");
Res = ((4096.0)/(analogRead(POT)) - 1) * 100; // SAAB Reostat linear mapping from 0-4096
Res = constrain(Res, 315, 4350);              // Used in manual mode for selecting the e85 amount
Volt = map(Res, 4350, 315, 0, 4096);
 
  MAN = 1;
}
else if(digitalRead(MAN_SW) == 0) {
  if(MAN == 1) Change(Auto);

 //Serial.println("Before Freq"); //debugging
 
  Frequency(); //Get the frequency from the E85 sensor

 //Serial.println("After Freq"); //debugging
 
 Avg = constrain(Avg, 50, 125);
 Volt = map(Avg, 50, 125, 0, 4096); //map the sensorvalue from 0 to 4096

  MAN = 0;
}

percent = map(Volt, 0, 4096, 0, 100); // turn the E85 value into percent (note: E85 not Ethanol amount. 85% Ethanol = 100% E85)

Message[2] = percent % 10 + 48;  //write out the E85 percentage
Message[1] = (percent - (percent % 10))/10 + 48;
if(percent == 100) {
Message[0] = '1';
Message[1] = '0';
Message[2] = '0';
}
 

if(pulseIn(E85, LOW, 100000) == 0 && MAN == 0){ //check if the sensor is working
 if(Error == 0){
  Error = 1;
 }
 if(Error == 1){
   ErrorTimes = ErrorTimes + 1;
   if(ErrorTimes %10 == 5){ // send a chime if the sensor is dead
    Ping();
   }  
 }
 
Message[0] = 'E' ; // Writing the errorcode to the SID-message
Message[1] = 'R' ;
Message[2] = 'R' ; 
Message[3] = 'O' ; 
Message[4] = 'R' ; 
Message[5] = ' ' ; 
Message[6] = 'S' ; 
Message[7] = 'E' ; 
Message[8] = 'N' ; 
Message[9] = 'S' ; 
Message[10]= 'O' ; 
Message[11]= 'R' ; 
  

  
}else {
  Error = 0;
  ErrorTimes = 0; //reset errors if the sensor is working
}
 


if(Switch == 0) WriteSID(Message1 , Message); // write message to the SID
if(Switch == 1) WriteSID(Message , Message1); //same but if the rows are swapped

/*Serial.println(Volt); //debugging

Serial.println(Seq); //debugging
Serial.println(Message1); //debugging
Serial.println(Message);//*/ //debugging


 
 Time = millis(); 
 while(millis() < Time + 50); //this limits the code to 20 times per second, or when a CAN-message is recived
 }
