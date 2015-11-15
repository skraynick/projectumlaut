/*************************************************************
Motor Shield 2-Channel DC Motor Demo
by Randy Sarafan

For more information see:
http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/

long duration, distance, FrontSensor, BackSensor;

void setup() {

  Serial.begin(9600);
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin

  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);

}

void loop(){

  //Motor A forward
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  //Spins the motor on Channel A at full speed

  //Motor B forward
  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B

  analogWrite(11, 100);    //Spins the motor on Channel B at half speed
  analogWrite(3, 100);

  sonarSensor(4, 5);
  FrontSensor = distance;
  sonarSensor(7, 6);
  BackSensor = distance;

  Serial.print(FrontSensor);
  Serial.print(" - ");
  Serial.println(BackSensor);

  if (FrontSensor<40 || BackSensor<40){
    turn();
  }
}

void sonarSensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}

void turn(){

  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delayMicroseconds(100000);
  analogWrite(11, 0);    //turn off the motor
  analogWrite(3, 0);
  delayMicroseconds(10000);
  
  //Motor A forward
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  //Spins the motor on Channel A at full speed

  //Motor B forward
  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  
  analogWrite(11, 255);    //Spins the motor
  analogWrite(3, 255);
  delayMicroseconds(2000000);
}
  
