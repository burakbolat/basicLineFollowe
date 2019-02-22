#define motorL 9
#define motorR 11

//c1 enable1 leftMotor, c2 enable2 rightMotor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
}

  
  int prevError = 0;

void loop() {
  // A0 sensor 1 and goes on
  int sensorVal = analogRead(A0);
  int sensorVal1 = analogRead(A1);
  int sensorVal2 = analogRead(A2);
  int sensorVal3 = analogRead(A3);
  int sensorVal4 = analogRead(A4);
  int sensorVal5 = analogRead(A5);

  /*
  Serial.println(sensorVal);
  Serial.println(sensorVal1);
  Serial.println(sensorVal2);
  Serial.println(sensorVal3);
  Serial.println(sensorVal4);
  Serial.println(sensorVal5);
  Serial.println("read");
  delay(1000);

  /*analogWrite(9,100);
  analogWrite(11,100);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  digitalWrite(1,HIGH);
  digitalWrite(2,LOW);*/

//adjust white 0 and black 1
//right -1 left 1
  sensorVal = (sensorVal> 800)? -1: 0;
  sensorVal1 = (sensorVal1> 800)? -1: 0;
  sensorVal2 = (sensorVal2> 800)? -1: 0;
  sensorVal3 = (sensorVal3> 800)? 1: 0;
  sensorVal4 = (sensorVal4> 800)? 1: 0;
  sensorVal5 = (sensorVal5> 800)? 1: 0;

/*
  Serial.println(sensorVal);
  Serial.println(sensorVal1);
  Serial.println(sensorVal2);
  Serial.println(sensorVal3);
  Serial.println(sensorVal4);
  Serial.println(sensorVal5);
  Serial.println("read");
  delay(1000);
  */
  
  int error = (3* sensorVal1)+ (sensorVal2)+ (sensorVal3)+ (3* sensorVal4);
  int p = 30;
  int d = 20;
  int pwm = error * p + (error - prevError) * d; 
  pwm = (pwm<0) ? pwm *= -1 : pwm;
     
   

 
  //left motor will run
  if(sensorVal1 == 0 && sensorVal3 == 0 && sensorVal2 == 0 && sensorVal4 == 0){
    analogWrite(motorL, 100);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);

    analogWrite(motorR,100);
    digitalWrite(2,HIGH);
    digitalWrite(1,LOW);
  }
  else if(error < -2){
    analogWrite(motorL,pwm);
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);

    analogWrite(motorR,pwm/2);
    digitalWrite(1,LOW);
    digitalWrite(2,HIGH);
  }
  //right motor will run
  else if(error > 2){
    
    analogWrite(motorL, pwm/2);
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);

    analogWrite(motorR, pwm);
    digitalWrite(1,HIGH);
    digitalWrite(2,LOW);
  }
  else if(error < 2 && error > -2){
    

    analogWrite(motorL, 100);
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);

    analogWrite(motorR, 100);
    digitalWrite(1,HIGH);
    digitalWrite(2,LOW);
  }

  
  
  prevError = error;
}




