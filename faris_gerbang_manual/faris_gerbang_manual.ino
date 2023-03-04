
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int pinServo = 9; // PWM
int positionServo = 0; // posisi awal servo
int changes = 1; // besaran derajat servo bergerak

const int buttonPin = 2; // Digital Int atau Out
int buttonState = 0;
int buttonCondition = 0;

const int ledPin =  13; 

void setup() {
  // put your setup code here, to run once:
  myservo.attach(pinServo);
  pinMode(buttonPin,INPUT);
  pinMode(ledPin, OUTPUT);

  //Initiate Serial communication.
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


  buttonState = digitalRead(buttonPin);

  // Jika kondisi mati dan tombo dipencet
  if (buttonState == HIGH and buttonCondition == 0){
    // Ganti posisi button condition ke on-
    buttonCondition = 1;
    delay(300);
  }
  // Jika kondisinya nyala dan button state dimatikan
  else if (buttonState == HIGH and buttonCondition == 1){
    // ganti posisi button condtion ke off
    buttonCondition = 0;
    delay(300);
  }

  if (buttonCondition == 1){
    digitalWrite(ledPin, HIGH);
  }
   else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  // Doin servo bro
  if (buttonCondition == 1){
    // BUka pintu gerbang
    for (positionServo; positionServo <= 90 ; positionServo += changes){
      myservo.write(positionServo);
      Serial.print(positionServo);
      Serial.print("\n");
      delay(10);
    } 
    
  }
  else {
    for (positionServo; positionServo >= 0 ; positionServo -= changes){
      myservo.write(positionServo);
      Serial.print(positionServo);
      Serial.print("\n");
      delay(10);
    }
  }

  
}
