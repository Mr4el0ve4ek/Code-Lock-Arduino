#include <Servo.h>

Servo myservo;

#define BUTTON_PIN_1  2
#define BUTTON_PIN_2  3
#define BUTTON_PIN_3  4
#define BUTTON_PIN_4  5

#define BUZZER 8
#define LAMP 1

int Code = 0;

int Code1 = 0;
int Code2 = 0;

bool BTN1 = LOW;
bool BTN2 = LOW;
bool BTN3 = LOW;
bool BTN4 = LOW;

bool START1 = LOW;
bool START2 = LOW;

bool CodeR1 = LOW;
bool CodeR2 = LOW;

bool PR = HIGH; //выбор кодировки (LOW - набор числа (Number), HIGH - ввод пароля (NumberProtected))

int PASSWORD = 8; //пароль N (УСТАНАВЛИВАТЬ ТОЛЬКО ОТ 1 ВКЛЮЧИТЕЛЬНО!)

int PrPASSWORD1 = 6; //первое число пароля NP (УСТАНАВЛИВАТЬ ТОЛЬКО ОТ 1 ДО 20 ВКЛЮЧИТЕЛЬНО!)
int PrPASSWORD2 = 4; //второе число пароля NP (УСТАНАВЛИВАТЬ ТОЛЬКО ОТ 1 ДО 20 ВКЛЮЧИТЕЛЬНО!)
 
void setup()
{
  pinMode(LAMP, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  myservo.attach(9);
}
 
void loop()
{
  int buttonState1 = digitalRead(BUTTON_PIN_1);
  int buttonState2 = digitalRead(BUTTON_PIN_2);
  int buttonState3 = digitalRead(BUTTON_PIN_3);
  int buttonState4 = digitalRead(BUTTON_PIN_4);

  //однократная выдача сигнала с кнопок
  if(buttonState1 == 1)
  {
    BTN1 = HIGH;
  }
  if(buttonState2 == 1)
  {
    BTN2 = HIGH;
  }
  if(buttonState3 == 1)
  {
    BTN3 = HIGH;
  }
  if(buttonState4 == 1)
  {
    BTN4 = HIGH;
  }

  //считывание нажатий кнопок
  if(buttonState1 == 0 && BTN1 == HIGH)
   {
    BTN1 = LOW;

    if(PR == HIGH)
    {
      if(Code1 > 0)
      {
        Code1--;
        tone(BUZZER, 400, 100);
        delay(100);
        digitalWrite(BUZZER, LOW);
      }
    }
    
    if(PR == LOW)
    {
      tone(BUZZER, 400, 100);
      Code += 1;
      delay(100);
      digitalWrite(BUZZER, LOW);
    }
   }
   
  if(buttonState2 == 0 && BTN2 == HIGH)
  {
    BTN2 = LOW;

    if(PR == HIGH)
    {
      if(Code2 > 0)
      {
        Code2--;
        tone(BUZZER, 400, 100);
        delay(100);
        digitalWrite(BUZZER, LOW);
      }
    }

    if(PR == LOW)
    {
      tone(BUZZER, 500, 100);
      Code += 2;
      delay(100);
      digitalWrite(BUZZER, LOW);
    }
  }
  
  if(buttonState3 == 0 && BTN3 == HIGH)
  {
    BTN3 = LOW;

    if(PR == HIGH)
    {
      if(Code2 < 20)
      {
        Code2++;
        tone(BUZZER, 600, 100);
        delay(100);
        digitalWrite(BUZZER, LOW);
      }
    }

    if(PR == LOW)
    {
      tone(BUZZER, 600, 100);
      Code += 3;
      delay(100);
      digitalWrite(BUZZER, LOW);
    }
  }
  
  if(buttonState4 == 0 && BTN4 == HIGH)
  {
    BTN4 = LOW;

    if(PR == HIGH)
    {
      if(Code1 < 20)
      {
        Code1++;
        tone(BUZZER, 600, 100);
        delay(100);
        digitalWrite(BUZZER, LOW);
      }
    }
    
    if(PR == LOW)
    {
      tone(BUZZER, 700, 100);
      Code += 4;
      delay(100);
      digitalWrite(BUZZER, LOW);
    }
  }

  //система распознования пароля N
  if(PR == LOW)
  {
    if(Code == PASSWORD && START1 == HIGH)
    {
      digitalWrite(LAMP, LOW);
      START1 = LOW;
      myservo.write(0);
      tone(BUZZER, 100, 100);
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(200);
      tone(BUZZER, 100, 100);
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(200);
      tone(BUZZER, 100, 100);
      delay(100);
      digitalWrite(BUZZER, LOW);
    }
    if(Code > PASSWORD)
    {
      Code = 0;
      tone(BUZZER, 100, 100);
      delay(1000);
      digitalWrite(BUZZER, LOW);
    }
    if(Code < PASSWORD)
    {
      START1 = HIGH;
      myservo.write(180);
    }
    if(Code == 0)
    {
      digitalWrite(LAMP, HIGH);
    }
  }

  //система распознавания пароля NP
  if(PR == HIGH)
  {
    if(CodeR1 == HIGH && CodeR2 == HIGH)
    {
      if(START2 == HIGH)
      {
        digitalWrite(LAMP, LOW);
        START2 = LOW;
        myservo.write(0);
        tone(BUZZER, 100, 100);
        delay(100);
        digitalWrite(BUZZER, LOW);
        delay(200);
        tone(BUZZER, 100, 100);
        delay(100);
        digitalWrite(BUZZER, LOW);
        delay(200);
        tone(BUZZER, 100, 100);
        delay(100);
        digitalWrite(BUZZER, LOW);
      }
    }
    if(Code1 < PrPASSWORD1 || Code1 > PrPASSWORD1)
    {
      CodeR1 = LOW;
    }
    if(Code2 < PrPASSWORD2 || Code2 > PrPASSWORD2)
    {
      CodeR2 = LOW;
    }
    
    if(Code1 == PrPASSWORD1)
    {
      CodeR1 = HIGH;
    }
    if(Code2 == PrPASSWORD2)
    {
      CodeR2 = HIGH; 
    }
    
    if(CodeR1 == LOW || CodeR2 == LOW)
    {
      START2 = HIGH;
      myservo.write(180);
      digitalWrite(LAMP, HIGH);
    }
  }
}
