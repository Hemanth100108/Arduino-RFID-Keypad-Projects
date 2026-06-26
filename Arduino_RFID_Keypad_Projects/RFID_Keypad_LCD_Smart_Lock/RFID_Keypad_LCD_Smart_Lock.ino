#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER A1

MFRC522 rfid(SS_PIN, RST_PIN);

// Change 0x27 to 0x3F if required
LiquidCrystal_I2C lcd(0x27,16,2);

//---------------- RFID ----------------

String validCard1 = "AB8A6D05";   // Replace with your UID
String validCard2 = "12345678";   // Replace with your UID

//---------------- PIN -----------------

String correctPIN = "1234";
String enteredPIN = "";

bool cardVerified = false;

//--------------- Keypad ----------------

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {8,7,6,5};
byte colPins[COLS] = {4,3,2,A0};

Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

//--------------------------------------

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER,OUTPUT);
  digitalWrite(BUZZER,LOW);

  lcd.init();
  lcd.backlight();

  showScanCard();
}

void loop()
{
  if(!cardVerified)
  {
    scanRFID();
  }
  else
  {
    readPIN();
  }
}

//--------------------------------------

void showScanCard()
{
  enteredPIN="";

  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("Scan RFID");

  lcd.setCursor(3,1);
  lcd.print("Card...");
}

//--------------------------------------

void scanRFID()
{
  if(!rfid.PICC_IsNewCardPresent())
    return;

  if(!rfid.PICC_ReadCardSerial())
    return;

  String uid="";

  for(byte i=0;i<rfid.uid.size;i++)
  {
    if(rfid.uid.uidByte[i]<0x10)
      uid+="0";

    uid+=String(rfid.uid.uidByte[i],HEX);
  }

  uid.toUpperCase();

  Serial.print("UID: ");
  Serial.println(uid);

  if(uid==validCard1 || uid==validCard2)
  {
    cardVerified=true;

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Card Verified");

    lcd.setCursor(2,1);
    lcd.print("Enter PIN");

    delay(1000);
  }
  else
  {
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Invalid Card");

    lcd.setCursor(1,1);
    lcd.print("Access Denied");

    beep();

    delay(2000);

    showScanCard();
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

//--------------------------------------

void readPIN()
{
  char key=keypad.getKey();

  if(key && isDigit(key))
  {
    enteredPIN+=key;

    lcd.clear();

    lcd.setCursor(2,0);
    lcd.print("Enter PIN");

    lcd.setCursor(6,1);

    for(int i=0;i<enteredPIN.length();i++)
      lcd.print("*");

    if(enteredPIN.length()==4)
    {
      delay(300);

      if(enteredPIN==correctPIN)
      {
        accessGranted();
      }
      else
      {
        wrongPIN();
      }

      cardVerified=false;
      enteredPIN="";

      delay(2000);

      showScanCard();
    }
  }
}
//------------------------------------------------
// Access Granted
//------------------------------------------------

void accessGranted()
{
  Serial.println("Access Granted");

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Access Granted");

  lcd.setCursor(1,1);
  lcd.print("Door Unlocked");

  delay(3000);
}

//------------------------------------------------
// Wrong PIN
//------------------------------------------------

void wrongPIN()
{
  Serial.println("Wrong PIN");

  lcd.clear();

  lcd.setCursor(3,0);
  lcd.print("Wrong PIN");

  lcd.setCursor(3,1);
  lcd.print("Try Again");

  beep();

  delay(2000);
}

//------------------------------------------------
// Buzzer
//------------------------------------------------

void beep()
{
  digitalWrite(BUZZER, HIGH);
  delay(300);
  digitalWrite(BUZZER, LOW);
}