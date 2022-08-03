#include<Servo.h>
#include<AFMotor.h>
#define LEFT A0 //left IR sensor
#define echopin A4 // echo pin
#define trigpin A5 // Trigger pin
#define RIGHT A1 //right IR sensor


AF_DCMotor Motor1(1);
AF_DCMotor Motor2(2);
AF_DCMotor Motor3(3);
AF_DCMotor Motor4(4);
Servo myservo;
 
int pos =0;
long time;

void setup()
{
// put your setup code here, to run once:
 Motor1.setSpeed(100);
  Motor1.run(RELEASE);
  Motor2.setSpeed(100);
  Motor2.run(RELEASE);
  Motor3.setSpeed(100);
  Motor3.run(RELEASE);
  Motor4.setSpeed(100);
  Motor4.run(RELEASE);
Serial.begin(9600);
myservo.attach(10);
pinMode(RIGHT, INPUT);
pinMode(LEFT, INPUT);

pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);

}

void loop()
{
  
  long duration, distance;


digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin, LOW);
duration = pulseIn(echopin, HIGH);
distance = (duration/2) / 29.1; if (distance < 100) 
{
Serial.print(distance);
Serial.println(" cm");
myservo.write(90);
}
else if (distance<180) 
{
Serial.print(distance);
Serial.println(" cm");
myservo.write(180); 
}
else
{
Serial.println("The distance is more than 180cm");
}
unsigned int dist = read_cm();
int Right_Value = digitalRead(RIGHT);
int Left_Value  = digitalRead(LEFT);

Serial.print("R= ");
Serial.print(Right_Value);
Serial.print(" L= ");
Serial.print(Left_Value);
Serial.print(" D= ");
Serial.println(distance);

if((Right_Value==1) && (Left_Value==1))
{
  forward();
}
else if((Right_Value==0) && (Left_Value==1))
{
  turnRight();
  }
else if((Right_Value==1) && (Left_Value==0))
{turnLeft();
  }
else if((Right_Value==0) && (Left_Value==0))
{
  stop();
}
delay(15);
}

long read_cm()
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  time = pulseIn (echopin, HIGH);
  return time / 29 / 2;
}

void forward(){// turn it on going forward
Motor1.setSpeed(200);
Motor1.run(FORWARD);
Motor2.setSpeed(200);
Motor2.run(FORWARD);
Motor3.setSpeed(200);
Motor3.run(FORWARD);
Motor4.setSpeed(200);
Motor4.run(FORWARD);
}


void turnRight() // TURNING RIGHT
{
Motor1.setSpeed(200);
Motor1.run(FORWARD);
Motor2.setSpeed(200);
Motor2.run(FORWARD);
Motor3.setSpeed(100);
Motor3.run(BACKWARD);
Motor4.setSpeed(100);
Motor4.run(BACKWARD);
}

void turnLeft() // turn it on going left
{
Motor1.setSpeed(100);
Motor1.run(BACKWARD);
Motor2.setSpeed(100);
Motor2.run(BACKWARD);
Motor3.setSpeed(200);
Motor3.run(FORWARD);
Motor4.setSpeed(200);
Motor4.run(FORWARD);
}

void stop()  // stopped
{
Motor1.setSpeed(0);  
Motor1.run(RELEASE);
Motor2.setSpeed(0);
Motor2.run(RELEASE);
Motor3.setSpeed(0);
Motor3.run(RELEASE);
Motor4.setSpeed(0);
Motor4.run(RELEASE);  
}
