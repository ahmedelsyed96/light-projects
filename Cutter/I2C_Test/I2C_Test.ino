#include <LiquidCrystal_I2C.h>

/* Include DigitLedDisplay Library */
#include "DigitLedDisplay.h"

/* Arduino Pin to Display Pin
   10 to DIN,
   11 to CS,
   12 to CLK */
DigitLedDisplay ld = DigitLedDisplay(10, 11, 12);






// Define stepper motor connections:
#define dirPin 3
#define stepPin 2
// Define relay pin
#define relayPin 8
// Define start and stop pins
#define startPin 6
#define stopPin 7
#define Sensor 9

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
void lcd_print(int s, int d);


bool sr = false;
bool sp = false;
long int dc_counter = 0; 
// varibles 
float speed_delay;
float speed_lcd;
float lenght;
float cycles;

void setup() {

  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  /* Set the brightness min:1, max:15 */
  ld.setBright(10);
  /* Set the digit count */
  ld.setDigitLimit(8);

  
  // Make sure backlight is on         
  lcd.backlight();      
  // Print a message on both lines of the LCD.
  //Set cursor to character 2 on line 0
  lcd.setCursor(1,0);   
  lcd.print("Loading ....");
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(relayPin,OUTPUT);
  pinMode(startPin,INPUT);
  pinMode(stopPin,INPUT);
  pinMode(Sensor,INPUT);
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin, LOW);
  ld.printDigit(dc_counter);
}

void loop() {
  // These four lines result in 1 step:
  speed_delay = map(analogRead(A0), 0, 1023, 20, 100);
  speed_lcd   = map(speed_delay, 20 , 100 , 100,0);
  lenght      = map(analogRead(A1), 0.0 , 1023.0, 1.0 ,  300);
  cycles      = lenght/18.3;
   
  lcd_print(speed_lcd,lenght);
  if (digitalRead(startPin) == HIGH){
    sr = true;
    sp = false;
    }   

  while (sr == true ){
  ld.printDigit(dc_counter);
  //Serial.println(cycles); 
  if(digitalRead(stopPin) == LOW || digitalRead(Sensor) == HIGH){
    sp = true;
    sr = false;
    }
  //Serial.print(sr);
  //Serial.print(" ");
  //Serial.println(sp);
  //delay(100);  
  if (sr == true && sp == false){
    for(double counter = 0 ; counter < (6400*cycles) ; counter ++ ){
    
      //Serial.print(counter);
      //Serial.print("    ");
      //Serial.println((6400*cycles));
      digitalWrite(stepPin, HIGH);  
      delayMicroseconds(speed_delay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed_delay);
      if (digitalRead(stopPin) == LOW){sp = true;sr = false;break;}
      } 
      
      if (digitalRead(stopPin) == LOW){sp = true;}
      digitalWrite(relayPin,HIGH);
      delay(1000);
      digitalWrite(relayPin,LOW);
      if (digitalRead(stopPin) == LOW){sp = true;}
      dc_counter +=1;
   }
   delay(250);}
   delay(500);

   
}






void lcd_print(int s, int d){

  lcd.clear();
  lcd.setCursor(1,0);   //Set cursor to character 2 on line
  lcd.print("Speed = ");
  lcd.setCursor(9,0);
  lcd.print(s);
  lcd.setCursor(14,0);
  lcd.print("%");

  lcd.setCursor(1,1);   //Set cursor to character 2 on line
  lcd.print("Lenght= ");
  lcd.setCursor(9,1);
  lcd.print(d);
  lcd.setCursor(14,1);
  lcd.print("CM");
  lcd.print(d);
  }
