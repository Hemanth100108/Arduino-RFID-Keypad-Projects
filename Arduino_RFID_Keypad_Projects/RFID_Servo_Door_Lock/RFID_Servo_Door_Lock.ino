#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SS_PIN 10
#define RST_PIN 9

#define SERVO_PIN 6
#define BUZZER_PIN 7

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String cardUID = "";

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED Failed");
    while (1);
  }

  display.setTextColor(SSD1306_WHITE);

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

  checkCard(cardUID);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(2000);

  welcomeScreen();
}

//------------------------------------------------

void welcomeScreen()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(15,10);
  display.println("RFID");

  display.setTextSize(1);
  display.setCursor(18,42);
  display.println("Scan Card");

  display.display();
}

//------------------------------------------------

void checkCard(String uid)
{
  if(uid == "AB8A6D05")        // Replace with Card 1 UID
  {
    accessGranted();
  }

  else if(uid == "EE148904")   // Replace with Card 2 UID
  {
    accessGranted();
  }

  else
  {
    accessDenied();
  }
}

//------------------------------------------------

void accessGranted()
{
  Serial.println("Access Granted");

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,8);
  display.println("ACCESS");

  display.setCursor(0,30);
  display.println("GRANTED");

  display.display();

  delay(1500);

  // Open Door
  for(int angle=0; angle<=90; angle++)
  {
    doorServo.write(angle);
    delay(10);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(5,20);
  display.println("Door Open");

  display.display();

  Serial.println("Door Open");

  delay(5000);

  // Close Door
  for(int angle=90; angle>=0; angle--)
  {
    doorServo.write(angle);
    delay(10);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,20);
  display.println("Door Locked");

  display.display();

  Serial.println("Door Locked");

  delay(1500);
}

//------------------------------------------------

void accessDenied()
{
  Serial.println("Access Denied");

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,10);
  display.println("ACCESS");

  display.setCursor(5,35);
  display.println("DENIED");

  display.display();

  for(int i=0;i<3;i++)
  {
    digitalWrite(BUZZER_PIN,HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN,LOW);
    delay(200);
  }

  delay(1500);
}