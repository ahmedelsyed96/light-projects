// Define the arduino pins 
// We will Photoresistor to detect the coverd section
// Define the sensor pin, head light, rear light and the buzzer 
int sensorPin = A0;
int rear_led = 9;
int head_led = 10;
int buzzer   = 11;
// Set the initial value for the sensor reading to zero 
int sensorValue = 0;


void setup()
{
  // Setup the pin mode 
  pinMode(sensorPin, INPUT);
  pinMode(rear_led, OUTPUT);
  pinMode(head_led, OUTPUT);
  pinMode(buzzer  , OUTPUT);
  // Start Serial communication
  Serial.begin(9600);
}

void loop()
{
  // read the value from the sensor
  sensorValue = analogRead(A0);
  // print the sensor reading so you know its range
  Serial.println(sensorValue);
  // convert the reading to state 
      //>> 0 means coverd section
      //>> 1 means not coverd section
  int state = map(sensorValue, 0,1024 , 0,2);
  Serial.println(state);
  // Case one >> outside the covered section
  if (state == 1){
    // head light is off 
    digitalWrite(head_led, LOW);
    // Buzzer is off 
    digitalWrite(buzzer, LOW);
    // rear light flash every 1 sec 
    digitalWrite(rear_led, HIGH);
    delay(1000);
    digitalWrite(rear_led, LOW);
    delay(1000);
  }
  // Case two >> inside the covered section
  else{
    // rear light is on 
    digitalWrite(rear_led, HIGH);
    // Buzzer is on 
    digitalWrite(buzzer, HIGH);
    // head light flash every 0.25 sec 
    digitalWrite(head_led, HIGH);
    delay(250);
    digitalWrite(head_led, LOW);
    delay(250);
  }
  
}
