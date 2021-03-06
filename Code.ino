#include <IRremote.h>
#include <LiquidCrystal.h>
//Define Pins
int redLed = 12;//tv
int yellowLed = 10;//ac
int greenLed = 9;//audio player
int blueLed = 8;//charger1
int whiteLed=7;//fan
int motor = 6;
int PWM_value=205; // initial pulse width
int RECV_PIN = 11;
int itsONled[]={0,0,0,0};
int motorPin1 = 2;
int motorPin2 = 3;
int motorPin3 = 5;
int motorPin4 = 4;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A0, en = A1, d4 = A5, d5 = A4, d6 = A3, d7 = A2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//IR Library stuff
IRrecv irrecv(RECV_PIN);
decode_results results;

//Codes
#define Button_1_red_led 2295 //Code received from button 1
#define Button_2_yellow_led 34935 //Code received from button 2
#define Button_3_green_led 18615 //Code received from button 3
#define Button_4_blue_led 10455 //Code received from button 4
#define Button_5_white_led 43095 //Code received from button 5
#define Button_VOLup_fan_speed 32895 //Code received from button VOL+
#define Button_VOLdown_fan_speed 36975 //Code received from button VOL-
#define Button_rewind_Shutter_open 8415  //Code received from button <<
#define Button_forward_Shutter_close 24735 //Code received from button >>



void setup()
{
  //Set Led Pins
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  digitalWrite(whiteLed,LOW);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    
  //Enable serial usage and IR signal
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); 
  Serial.println("Enabled IRin");
    
} 

void loop() 
{
  if (irrecv.decode(&results)){//irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
    unsigned int value = results.value; //Get the value of results as an unsigned int, so we can use switch case
    lcd.setCursor(0,0);
    lcd.clear();
    switch (value) 
    {
      case Button_1_red_led:
      	if (itsONled[1] == 1)
        {
          digitalWrite(redLed, LOW);//Button 1 --> OFF
          itsONled[1] = 0;
          Serial.print("Red LED off");
          lcd.print("Red LED off");
        }
      	else
        {
          digitalWrite(redLed, HIGH);//Button 1 --> ON
          itsONled[1] = 1;
          Serial.print("Red LED on");
          lcd.print("Red LED on");
        }
      	break;
      
      
      case Button_2_yellow_led:
      	if (itsONled[1] == 1)
        {
          digitalWrite(yellowLed, LOW);//Button 2 --> OFF
          itsONled[1] = 0;
          Serial.print("Yellow LED off");
          lcd.print("Yellow LED off");
        }
      	else
        {
          digitalWrite(yellowLed, HIGH);//Button 2 --> ON
          itsONled[1] = 1;
          Serial.print("Yellow LED on");
          lcd.print("Yellow LED on");
        }
      	break;
      
      case Button_3_green_led:
      	if (itsONled[1] == 1)
        {
          digitalWrite(greenLed, LOW);//Button 3 --> OFF
          itsONled[1] = 0;
          Serial.print("Green LED off");
          lcd.print("Green LED off");
        }
      	else
        {
          digitalWrite(greenLed, HIGH);//Button 3 --> ON
          itsONled[1] = 1;
          Serial.print("Green LED on");
          lcd.print("Green LED on");
        }
      	break;
      
      
      case Button_4_blue_led:
      	if (itsONled[1] == 1)
        {
          digitalWrite(blueLed, LOW);//Button 4 --> OFF
          itsONled[1] = 0;
          Serial.print("Blue LED off");
          lcd.print("Blue LED off");
        }
      	else
        {
          digitalWrite(blueLed, HIGH);//Button 4 --> ON
          itsONled[1] = 1;
          Serial.print("Blue LED on");
          lcd.print("Blue LED on");
        }
      	break;
      
      
      case Button_5_white_led:
      	if (itsONled[1] == 1)
        {
          digitalWrite(whiteLed, LOW);//Button 5 --> OFF
          itsONled[1] = 0;
          analogWrite(motor,0); // motor stop
          Serial.println("Fan has stopped.");
          lcd.print("Fan has stopped.");
        }
      	else if (itsONled[1] == 0)
        {
          digitalWrite(whiteLed, HIGH);//Button 5 --> ON
          itsONled[1] = 1;
          analogWrite(motor,PWM_value); // motor start
          Serial.println("Fan is running."); // display message 
          lcd.print("Fan is running.");
        }
        break;
      
       case Button_VOLup_fan_speed: // for volume up button 

        {
          Serial.println("initial pwm");
          Serial.println(PWM_value);
          if(PWM_value<255) PWM_value+=10;  // increase pulse width
		  Serial.print("Fan speed increased : PWM= ");
          Serial.println(PWM_value);  // display message
          lcd.print("Fan speed +");
          analogWrite(motor,PWM_value); // and increase motor speed  
        }
        break;

       case Button_VOLdown_fan_speed://for volume down button

        {
          Serial.println("initial pwm");
          Serial.println(PWM_value);
          if(PWM_value>25) PWM_value-=10;  // decrease pulse width
          Serial.print("Fan speed decreased : PWM= ");
          Serial.println(PWM_value);   // display message
          lcd.print("Fan speed -");
          analogWrite(motor,PWM_value);   // and decrease motor speed
        } 
      	break;
      
      case Button_rewind_Shutter_open://Code received from button <<
      if (itsONled[1] == 0)
      {
        digitalWrite(motorPin1, LOW);
  		digitalWrite(motorPin2, HIGH);
  		digitalWrite(motorPin3, HIGH);
  		digitalWrite(motorPin4, LOW);
        itsONled[1]=1;
        Serial.print("blinds opening");
        lcd.print("blinds opening");
        
      }
      else
      {
        digitalWrite(motorPin1, LOW);
  		digitalWrite(motorPin2, LOW);
  		digitalWrite(motorPin3, LOW);
  		digitalWrite(motorPin4, LOW);
        itsONled[1]=0;
        Serial.print("blinds opened");
        lcd.print("blinds opened");
      }
      break;
      
      case Button_forward_Shutter_close://Code received from button >>
      if (itsONled[1] == 0)
      {
        digitalWrite(motorPin1, HIGH);
  		digitalWrite(motorPin2, LOW);
  		digitalWrite(motorPin3, LOW);
  		digitalWrite(motorPin4, HIGH);
        itsONled[1]=1;
        Serial.print("blinds closing");
        lcd.print("blinds closing");
        
      }
      else
      {
        digitalWrite(motorPin1, LOW);
  		digitalWrite(motorPin2, LOW);
  		digitalWrite(motorPin3, LOW);
  		digitalWrite(motorPin4, LOW);
        itsONled[1]=0;
        Serial.print("blinds closed");
        lcd.print("blinds closed");
      }
      break;
      
    }
       
    Serial.println("\n");
    Serial.println(value);
    irrecv.resume(); // Receive the next value    
  }
}