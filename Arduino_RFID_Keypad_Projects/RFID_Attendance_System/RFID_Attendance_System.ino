#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

// Change address to 0x3F if your LCD doesn't work
LiquidCrystal_I2C lcd(0x27, 16, 2);

String cardUID = "";

//---------------- Student Details ----------------

String student1UID = "AB8A6D05";
String student2UID = "12345678";

String student1Name = "Hemanth";
String student2Name = "Arun";

//-------------------------------------------------

unsigned long lastScan1 = 0;
unsigned long lastScan2 = 0;

const unsigned long duplicateDelay = 10000;

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();

  welcomeScreen();
}

void loop()
{
  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  cardUID = "";

  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10)
      cardUID += "0";

    cardUID += String(rfid.uid.uidByte[i], HEX);
  }

  cardUID.toUpperCase();

  Serial.print("UID: ");
  Serial.println(cardUID);

  checkAttendance(cardUID);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1500);

  welcomeScreen();
}

//------------------------------------------------

void welcomeScreen()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Scan Card");
  lcd.setCursor(1,1);
  lcd.print("Attendance");
}

//------------------------------------------------

void checkAttendance(String uid)
{
  unsigned long currentTime = millis();

  if(uid == student1UID)
  {
    if(currentTime - lastScan1 >= duplicateDelay)
    {
      lastScan1 = currentTime;
      markAttendance(student1Name);
    }
    else
    {
      duplicateScan();
    }
  }

  else if(uid == student2UID)
  {
    if(currentTime - lastScan2 >= duplicateDelay)
    {
      lastScan2 = currentTime;
      markAttendance(student2Name);
    }
    else
    {
      duplicateScan();
    }
  }

  else
  {
    unknownCard();
  }
}

//------------------------------------------------

void markAttendance(String name)
{
  Serial.println("Attendance Recorded");
  Serial.print("Student : ");
  Serial.println(name);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(name);

  lcd.setCursor(0,1);
  lcd.print("Attendance OK");
}

//------------------------------------------------

void duplicateScan()
{
  Serial.println("Duplicate Scan Ignored");

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Already Marked");

  lcd.setCursor(0,1);
  lcd.print("Wait 10 Sec");
}

//------------------------------------------------

void unknownCard()
{
  Serial.println("Unknown Card");

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Access Denied");

  lcd.setCursor(0,1);
  lcd.print("Unknown Card");
}