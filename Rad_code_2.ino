#include <SFE_BMP180.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "IRremote.h"

const int pressurePin = A2;
double pressureLevel = 0;
float pressure = 0;
int i = -1;
int sensorPin = A2;   
int sensorValue = 0; 
float Vout=0;
float P=0;


// Declare the Servo pin 
int servoPin = 9; 
// Create a servo object 
Servo Servo1;

LiquidCrystal_I2C lcd(0x27, 16, 2);

boolean buttonState = LOW;
boolean buttonState2 = LOW;
boolean storage = LOW;
double standard = 0;
String standardstr = "";

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.init();
  //lcd.backlight();
  Serial.begin(9600);
  pinMode(pressurePin, OUTPUT);
  //pinMode(ServoPin, OUTPUT);
  //bool success = bmp180.begin();
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  Servo1.attach(servoPin);

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  } 
  if (standard > 0)
  {
  pressure = P * 1000;
  if(pressure < standard)
  {
    Servo1.write(180);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressure Low");
  }
}/* --(end main loop )-- */
/*-----( Function )-----*/
}
void translateIR() // takes action based on IR code received
{
  switch(results.value)
  {
  case 0xFF629D:
  Serial.println("Reset");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reset");
  standardstr = "";
  standard = 0;
  break;
  case 0xFF22DD: 
  if (buttonState2 == LOW)
  {
    lcd.backlight();
    break;
  }
  if (buttonState2 == HIGH)
  {
    lcd.backlight();
    break;
  }
  case 0xFF02FD: 
  if (buttonState == LOW)
  {
    Serial.println("Motor turned on.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lever pulled up.");
    Servo1.write(180); 
    delay(2000); 
    buttonState = HIGH;
    break;
  }
  if (buttonState == HIGH)
  {
    Serial.println("Lever pulled up.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lever pushed down");
    Servo1.write(0); 
    delay(1000); 
    buttonState = LOW;
    break;
  }
  case 0xFFC23D: 
    if (storage == LOW)   
    {
      storage = HIGH;
      Serial.println("Storage On");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Storage On");
      delay(2000);
      lcd.clear();
     // standardstr = String(standard);
      break;
    }
    if (storage = HIGH)
    {
      storage = LOW;
      Serial.println("Storage Off");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Storage Off");
      Serial.println(standardstr+"000");
      standard = standardstr.toDouble();
      Serial.println(standard);
      break;
    }
  case 0xFFA857: Serial.println(" REVERSE"); break;
  case 0xFF6897: 
  Serial.println(" 0");    
  if (storage == HIGH)
  {
    standardstr = standardstr + "0";
    lcd.clear();
    lcd.setCursor(i+1, 0);
    i=i+1;
    lcd.print("0");
  }
  break;
  case 0xFF9867: Serial.println(" End storage");
    PressureSensor();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressure Sensor Enabled");
  break;
  case 0xFFB04F: Serial.println(" 3");
  if (storage == HIGH)
  {
    standardstr = standardstr + "3";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("3");
  }
  break;
  case 0xFF30CF: Serial.println(" 1");
  if (storage == HIGH)
  {
    standardstr = standardstr + "1";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("1");
  }
  break;
  case 0xFF18E7: Serial.println(" 2");
  if (storage == HIGH)
  {
    standardstr = standardstr + "2";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("2");
  }
  break;
  case 0xFF7A85: Serial.println(" 3");    
  if (storage == HIGH)
  {
    standardstr = standardstr + "3";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("3");
  }
  break;
  case 0xFF10EF: Serial.println(" 4"); 
  if (storage == HIGH)
  {
    standardstr = standardstr + "4";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("4");
  }
  break;
  case 0xFF38C7: Serial.println(" 5"); 
  if (storage == HIGH)
  {
    standardstr = standardstr + "5";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("5");
  }
  break;
  case 0xFF5AA5: Serial.println(" 6"); 
  if (storage == HIGH)
  {
    standardstr = standardstr + "6";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("6");
  }
  break;
  case 0xFF42BD:Serial.println(" 7"); 
  if (storage == HIGH)
  {
    standardstr = standardstr + "7";
    lcd.clear();
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("7");
  }
  break;
  case 0xFF4AB5: Serial.println(" 8"); 
  if (storage == HIGH)
  {
    standardstr = standardstr + "8";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("8");
  }
  break;
  case 0xFF52AD: Serial.println(" 9"); 
  if (storage == HIGH)
  {
    standardstr = standardstr + "9";
    lcd.setCursor(i+1, 0);
    i = i+1;
    lcd.print("9");
  }
  break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  //default: 
   // Serial.println(" other button   ");

  }// End Case

  delay(200); // Do not get immediate repeat


} 

void PressureSensor()
{
  int i=0;
    int sum=0;
    int offset=0;
    Serial.println("init...");
    for(i=0;i<10;i++)
    {
         sensorValue = analogRead(sensorPin)-512;
         sum+=sensorValue;
    }
    offset=sum/10.0;
    Serial.println("Ok");
    while(1)
    {
       sensorValue = analogRead(sensorPin)-offset; 
       Vout=(5*sensorValue)/1024.0;
       P=Vout-2.5;           
       Serial.print("Presure = " );                       
       Serial.print(P*1000); 
       Serial.println("Psi");
       delay(1000);   
    }
}
