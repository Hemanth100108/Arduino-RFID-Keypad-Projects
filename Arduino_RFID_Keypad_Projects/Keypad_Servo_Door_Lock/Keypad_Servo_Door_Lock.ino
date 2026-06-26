#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo doorServo;

// Pins
#define SERVO_PIN 10
#define BUZZER_PIN 11

//------------- Keypad -----------------

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Change password here
String correctPIN = "1234";

String enteredPIN = "";

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);      // Locked position

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  showEnterPIN();
}

void loop()
{
  char key = keypad.getKey();

  if(key && isDigit(key))
  {
    enteredPIN += key;

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);

    display.setCursor(0,0);
    display.println("Enter PIN");

    display.setCursor(0,35);

    for(int i=0;i<enteredPIN.length();i++)
      display.print("*");

    display.display();

    if(enteredPIN.length()==4)
    {
      delay(300);

      if(enteredPIN==correctPIN)
        accessGranted();
      else
        accessDenied();

      enteredPIN="";
      delay(1000);
      showEnterPIN();
    }
  }
}

void showEnterPIN()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("Enter PIN");

  display.display();
}

void accessGranted()
{
  display.clearDisplay();
  display.setTextSize(2);

  display.setCursor(0,0);
  display.println("Access");
  display.println("Granted");
  display.display();

  // Open Door
  for(int angle=0; angle<=90; angle++)
  {
    doorServo.write(angle);
    delay(10);
  }

  display.clearDisplay();
  display.setCursor(0,15);
  display.println("Door Open");
  display.display();

  delay(5000);

  // Close Door
  for(int angle=90; angle>=0; angle--)
  {
    doorServo.write(angle);
    delay(10);
  }

  display.clearDisplay();
  display.setCursor(0,15);
  display.println("Door Locked");
  display.display();

  delay(1500);
}

void accessDenied()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("Wrong PIN!");
  display.setCursor(0,35);
  display.println("Try Again");
  display.display();

  for(int i=0;i<3;i++)
  {
    digitalWrite(BUZZER_PIN,HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN,LOW);
    delay(200);
  }
}