#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

//================ LCD ==================
LiquidCrystal_I2C lcd(0x27, 16, 2);

//================ SERVO =================
Servo doorServo;
const int servoPin = 9;

//================ FLEX SENSOR ===========
const int flexPin = A0;

// Change this after checking Serial Monitor
const int FLEX_THRESHOLD = 600;

//================ PASSWORD ==============
String password = "1234";
String enteredPassword = "";

//================ KEYPAD ================
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,10};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//========================================

bool doorOpen = false;

//========================================

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  doorServo.attach(servoPin);
  doorServo.write(0);

  lcd.setCursor(0,0);
  lcd.print("SMART DOOR");
  lcd.setCursor(0,1);
  lcd.print("LOCK SYSTEM");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Enter Pass:");
}

//========================================

void loop()
{
  checkFlexSensor();
  checkPassword();
}

//========================================
// FLEX SENSOR
//========================================

void checkFlexSensor()
{
  int flexValue = analogRead(flexPin);

  Serial.print("Flex Value: ");
  Serial.println(flexValue);

  if(flexValue > FLEX_THRESHOLD && !doorOpen)
  {
    lcd.clear();
    lcd.print("Flex Detected");
    delay(1000);

    openDoor();
  }

  delay(100);
}

//========================================
// PASSWORD
//========================================

void checkPassword()
{
  char key = keypad.getKey();

  if(key)
  {
    if(key >= '0' && key <= '9')
    {
      if(enteredPassword.length() < 8)
      {
        enteredPassword += key;

        lcd.setCursor(0,1);

        for(int i=0;i<enteredPassword.length();i++)
          lcd.print("*");
      }
    }

    else if(key == '*')
    {
      enteredPassword = "";

      lcd.clear();
      lcd.print("Enter Pass:");
    }

    else if(key == '#')
    {
      if(enteredPassword == password)
      {
        lcd.clear();
        lcd.print("Access Granted");

        delay(1000);

        openDoor();
      }
      else
      {
        lcd.clear();
        lcd.print("Wrong Password");

        delay(2000);

        lcd.clear();
        lcd.print("Enter Pass:");
      }

      enteredPassword = "";
    }
  }
}

//========================================
// OPEN DOOR
//========================================

void openDoor()
{
  doorOpen = true;

  lcd.clear();
  lcd.print("Door Opening");

  for(int pos=0; pos<=90; pos++)
  {
    doorServo.write(pos);
    delay(15);
  }

  lcd.clear();
  lcd.print("Door Open");

  delay(5000);

  lcd.clear();
  lcd.print("Door Closing");

  for(int pos=90; pos>=0; pos--)
  {
    doorServo.write(pos);
    delay(15);
  }

  doorOpen = false;

  lcd.clear();
  lcd.print("Door Locked");

  delay(2000);

  lcd.clear();
  lcd.print("Enter Pass:");
}
