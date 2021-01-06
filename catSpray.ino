const int trigPin = 3;  //pirPower; distance sensor trigger
const int echoPin = 2;  //pirIn; distance sensor echo
int motorPin1 = 8;  //pin for spray mechanism
int buzzerPin = 9;

float distance = 0;  //store distance measured by distance sensor

bool triggered = false;

void setup() {
  //init distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(trigPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  distance = getDistance();

  //distance with length of hallway being 40 in wide
  if(distance < 40.0) {
    triggered = buzzerPlay();  //warning signal triggered

    if(triggered == true) {
      digitalWrite(motorPin1, HIGH);  //supply power to spray
      tone(buzzerPin, 2500);
      delay(1500);  //wait
      noTone(buzzerPin);
      digitalWrite(motorPin1, LOW);  //cut off power to spray
    }
  }

}


//helper function for warning signal
bool buzzerPlay() {
  int tempDistance = getDistance();  //measure distance again

  //person and/or cat got out of range in time, return false alarm
  if(tempDistance >= 35) {
    return false;
  }

  //not backed away in time
  else {
    tone(buzzerPin, 100);
    delay(100);
    noTone(buzzerPin);
    delay(100);
    tone(buzzerPin, 100);
    delay(100);
    noTone(buzzerPin);
    delay(100);
    return true;
  }

  
}


//helper function to get distance
float getDistance() {
  float echoTime;  //time it takes for a ping to bounce off an object
  float calcDistance;  //stores distance calculated from echoTime

  //send out 10ms long pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);  //measure how long pulse takes to bounce back to sensor

  calcDistance = echoTime/148.0;  //calc distance of object in inches

  return calcDistance;
}
