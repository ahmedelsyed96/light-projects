#include <Servo.h>

Servo H_servo;  // create servo object to control a Horizontal servo
Servo V_servo;  // create servo object to control a vertical servo

int LDR_1 = A0;  // analog pin used to connect the LDR
int LDR_2 = A1;
int LDR_3 = A2;
int LDR_4 = A3;

int tollerance = 50;

int H_angel = 45;
int V_angel = 45; 


void setup() {
  H_servo.attach(9);  // attaches the servo on pin 9 to the servo object
  V_servo.attach(10);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  
  int read_ldr_1 = analogRead(A0);
  int read_ldr_2 = analogRead(A1);
  int read_ldr_3 = analogRead(A2);
  int read_ldr_4 = analogRead(A3);
  int avg_th = read_ldr_1 - read_ldr_2;
  int avg_bh = read_ldr_3 - read_ldr_4;
  int avg_rv = read_ldr_1 - read_ldr_3;
  int avg_lv = read_ldr_2 - read_ldr_4;
  Serial.print(read_ldr_1);
  Serial.print("   ");
  Serial.print(read_ldr_2);
  Serial.print("   ");
  Serial.print(read_ldr_3);
  Serial.print("   ");
  Serial.println(read_ldr_4);


  
  if ( avg_th > tollerance || avg_bh > tollerance){
    if(avg_th > avg_bh){
      if(read_ldr_1 > read_ldr_2){H_angel++;}
      else{H_angel--;}H_servo.write(H_angel);
      }
    else{
      if(read_ldr_3 > read_ldr_4){H_angel++;}
      else{H_angel--;}H_servo.write(H_angel);}
    }




    
   if ( avg_rv> tollerance || avg_lv> tollerance){
      if (avg_rv>avg_lv){
        if( read_ldr_1> read_ldr_3){V_angel++;}
        }else{V_angel--;}V_servo.write(V_angel);
        }
      else{        
        if( read_ldr_2> read_ldr_4){V_angel++;}
        else{V_angel--;}V_servo.write(V_angel);
        
    }

}
