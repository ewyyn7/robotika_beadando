// C++ code

const int gyalogosGomb = 10;
const int pirosAuto = 2;
const int sargaAuto = 3;
const int zoldAuto = 4;
const int pirosGyalogos = 5;
const int zoldGyalogos = 6;
bool automehet = true;
int gombState = 0;
const int buzzerPin = 7;


void autotilos()
{
	if (automehet == true)
    {
      digitalWrite(zoldAuto, LOW);
      digitalWrite(sargaAuto, HIGH);
      delay(3000);
      digitalWrite(sargaAuto, LOW);
      digitalWrite(pirosAuto, HIGH);
      automehet = false;
      delay(2000);
      digitalWrite(pirosGyalogos, LOW);
      digitalWrite(zoldGyalogos, HIGH);     
    }
}
void autoszabad()
{
	if (automehet == false)
    {
      for (int i = 0; i < 5; i++){
        digitalWrite(zoldGyalogos, HIGH);
        tone(buzzerPin, 100);
        delay(500);
        digitalWrite(zoldGyalogos, LOW);
        noTone(buzzerPin);
        delay(500);
      }
      digitalWrite(pirosGyalogos, HIGH);
      delay(3000);
      digitalWrite(sargaAuto, HIGH);
      delay(3000);
      digitalWrite(sargaAuto, LOW);
      digitalWrite(pirosAuto, LOW);
      digitalWrite(zoldAuto, HIGH);
      
      automehet = true;
    }
    
}

class Ultrasonic{
    public:
      Ultrasonic(int echo, int trig);
      void distanceMeasure(void);
      long microsecondsToCentimeters(void);
      long microsecondsToInches(void);
    private:
      int _echo;
  	  int _trig;
      long duration;
};

Ultrasonic::Ultrasonic(int echo, int trig){
    _echo = echo;
    _trig = trig;
}

void Ultrasonic::distanceMeasure(void){
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
    digitalWrite(_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(_trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(_trig,LOW);
    duration = pulseIn(_echo, HIGH);
}

long Ultrasonic::microsecondsToCentimeters(void){
    return duration/58;
}

long Ultrasonic::microsecondsToInches(void){
    return duration/148;
}

Ultrasonic ultrasonic(9, 8);
long distance;

void setup() {
  pinMode(gyalogosGomb, INPUT);
  pinMode(pirosAuto, OUTPUT);
  pinMode(sargaAuto, OUTPUT);
  pinMode(zoldAuto, OUTPUT);
  pinMode(pirosGyalogos, OUTPUT);
  pinMode(zoldGyalogos, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(sargaAuto, LOW);
  digitalWrite(pirosAuto, LOW);
  digitalWrite(zoldAuto, HIGH);
  digitalWrite(pirosGyalogos, HIGH);
  digitalWrite(zoldGyalogos, LOW);
  delay(2000);
}
int gyalogosCount = 0;
int autoCount = 0;
bool gombNyomva = false;
void loop() {  
  ultrasonic.distanceMeasure();
  distance = ultrasonic.microsecondsToCentimeters();
  Serial.println("Distance to nearest object: ");
  Serial.print(distance);
  Serial.println(" cm");
 
  gombState = digitalRead(gyalogosGomb);
  if (gyalogosCount != 0){
    if (gyalogosCount < 2){
      	Serial.println("Gyalogos mehet ennyi ideje:");
    }

    Serial.println(gyalogosCount);
  }
  if (autoCount != 0){
    if (autoCount < 2){
      	Serial.println("Auto mehet ennyi ideje:");
    }

    Serial.println(autoCount);
  }
  if (automehet == false)
  {
  	gyalogosCount++;
    //tone(buzzerPin, 100);
  }
  if (automehet == true)
  {
  	autoCount++;
    //noTone(buzzerPin);
  }
  if (gombState == 1 and automehet == true and gombNyomva == false)
  {
    Serial.println("Gyalogos gomb nyomas...");
    gombNyomva = true;
  }
  if (gombNyomva == true and automehet == true and autoCount > 30)
  {
    gyalogosCount = 0;
    Serial.println("Auto 30 MP letelt...");
    autotilos();
    autoCount = 0;
    Serial.println("Gyalogos mehet!");
    gombNyomva = false;
  }
  if (gyalogosCount == 20){
  	gyalogosCount=0;
    Serial.println("Gyalogos 20 MP letelt...");
    autoszabad();
    Serial.println("Auto indulhat!");
  }
  if(distance < 5 and automehet == false and gyalogosCount > 15)
  {
    Serial.println("Auto varakozik...");
    autoszabad();
    gyalogosCount = 0;
    Serial.println("Auto indulhat!");
      
  }
  delay(100);
}
