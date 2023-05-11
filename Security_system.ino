#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define RED_PIN 2
#define GREEN_PIN 3

MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
 int buzzerPin = 5;
void setup() { 
 Serial.begin(9600);
 SPI.begin();

 pinMode(buzzerPin, OUTPUT);
 pinMode(RED_PIN, OUTPUT);
 pinMode(GREEN_PIN, OUTPUT);
 
 rfid.PCD_Init();
// Serial.println(F("READING THE CARD UNIQUE ID:"));
 for (byte i = 0; i < 6; i++) {
 key.keyByte[i] = 0xFF;
 }
}
void loop(){
 if(!rfid.PICC_IsNewCardPresent()){
 return;
 }
 if(!rfid.PICC_ReadCardSerial()){
 return;
 }
 if (rfid.uid.uidByte[0] != nuidPICC[0] || rfid.uid.uidByte[1] != nuidPICC[1] || rfid.uid.uidByte[2] != nuidPICC[2] || rfid.uid.uidByte[3] != nuidPICC[3] ) {
  for (byte i = 0; i < 4; i++) {
  nuidPICC[i] = rfid.uid.uidByte[i];
  }
 
  // Serial.println(F("********************"));
  printHex(rfid.uid.uidByte, rfid.uid.size);
  // Serial.println(F("\n********************"));
  }
  else{
  // Serial.println(F("This card was lastly detected."));
    printHex(rfid.uid.uidByte, rfid.uid.size);
  }

  if(Serial.available())
  {
    String message = Serial.readStringUntil('\n');
      message.trim(); // remove whitespace

      if (strcmp(message.c_str(), "Found") == 0) {
        success();
      } else {
        error();
      }

      delay(60);
  }
 
 /*
 * Halt PICC
 * Stop encryption on PCD
 */
 rfid.PICC_HaltA();
 rfid.PCD_StopCrypto1();
}


void success(){
  digitalWrite(GREEN_PIN,HIGH);
  digitalWrite(buzzerPin,HIGH);
  delay(500);
  digitalWrite(buzzerPin,LOW);
  digitalWrite(GREEN_PIN,LOW);
}

void error(){
  digitalWrite(RED_PIN,HIGH);
  digitalWrite(buzzerPin,HIGH);
  delay(100);
  digitalWrite(buzzerPin,LOW);
  delay(100);
  digitalWrite(buzzerPin,HIGH);
  delay(100);
  digitalWrite(buzzerPin,LOW);
  delay(100);
  digitalWrite(buzzerPin,HIGH);
  delay(100);
  digitalWrite(buzzerPin,LOW);
  delay(100);
  digitalWrite(buzzerPin,HIGH);
  delay(100);
  digitalWrite(buzzerPin,LOW);
  digitalWrite(RED_PIN,LOW);
}



void printHex(byte *buffer, byte bufferSize){
 for (byte i = 0; i < bufferSize; i++){
 Serial.print(buffer[i] < 0x10 ? " 0" : " ");
 Serial.print(buffer[i], HEX);
 
 }
 Serial.print("\n");

 
}
