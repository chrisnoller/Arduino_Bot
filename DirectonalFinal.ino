// set constants for pins used for motor controller
// credit for bluetooth code from: http://blog.miguelgrinberg.com/post/building-an-arduino-robot-part-ii-programming-the-arduino
#define directionPinA 12
#define directionPinB 13
#define speedPinA 3
#define speedPinB 11
#define brakePinA 9
#define brakePinB 8

void setup() 
{
  // initiate serial connection, and set motor controller pins to outputs
  Serial.begin(9600);
  pinMode(directionPinA, OUTPUT);
  pinMode(directionPinB, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(speedPinB, OUTPUT);
  pinMode(brakePinA, OUTPUT);
  pinMode(brakePinB, OUTPUT);
}

void Move_Forward()
{
  // turn brakes off, set direction (motors are mounted backwards)
  // set speed to max
  digitalWrite(brakePinA, LOW);
  digitalWrite(brakePinB, LOW);
  digitalWrite(directionPinA, LOW);
  digitalWrite(directionPinB, LOW);
  analogWrite(speedPinA, 255);
  analogWrite(speedPinB, 255);
}

void Move_Backward()
{
  digitalWrite(brakePinA, LOW);
  digitalWrite(brakePinB, LOW);
  digitalWrite(directionPinA, HIGH);
  digitalWrite(directionPinB, HIGH);
  analogWrite(speedPinA, 255);
  analogWrite(speedPinB, 255);
}

void Brake()
{
  // turn motors off and brakes on
  analogWrite(speedPinA, 0);
  analogWrite(speedPinB, 0);
  digitalWrite(brakePinA, HIGH);
  digitalWrite(brakePinB, HIGH);
}

void Turn_Left(int x)
{
  // set one motor forward and one motor backward
  digitalWrite(directionPinA, LOW);
  digitalWrite(directionPinB, HIGH);
  analogWrite(speedPinA, x);
  analogWrite(speedPinB, x);
  digitalWrite(brakePinA, LOW);
  digitalWrite(brakePinB, LOW); 
}

void Turn_Right(int x)
{
  digitalWrite(directionPinA, HIGH);
  digitalWrite(directionPinB, LOW);
  analogWrite(speedPinA, x);
  analogWrite(speedPinB, x);
  digitalWrite(brakePinA, LOW);
  digitalWrite(brakePinB, LOW); 
}

void loop() 
{
  // if data is coming in, store data input in cmd variable
  // print data input to screen
  if (Serial.available() > 0)
  {
    char cmd = Serial.read();
    Serial.print("Received: ");
    Serial.println(cmd);
    // "adsw" keypad for soft surface, "jlki" for hard surface
    if (cmd == 'a')
    {
      Turn_Left(255);
    }
    else if (cmd == 'j')
    {
      Turn_Left(200);
    }
    else if (cmd == 'w' || cmd == 'i')
    {
      Move_Forward();
    }
    else if (cmd == 's' || cmd == 'k')
    {
      Move_Backward();
    }
    else if (cmd == 'd')
    {
      Turn_Right(255);
    }
    else if (cmd == 'l')
    {
      Turn_Right(200);
    }
    else if (cmd == ' ')
    {
      Brake();
    }    
  }
}
