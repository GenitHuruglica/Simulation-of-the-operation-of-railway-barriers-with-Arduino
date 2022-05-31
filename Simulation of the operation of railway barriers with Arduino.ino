#include <EEPROM.h>
#include <Servo.h>


Servo servo_motorri;  // inicializimi i servo motorrit.


const int trig1 = 10; //Inicializmi i TrigPin te senzorit.
const int echo1 = 11; //Inicializmimi i EchoPin te senzorit.

long matja;
int distanca;

const int LED=13; //inicializimi i LED drites se kuqe (Semaforit).



void setup() {
  servo_motorri.attach(9); 

  
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);      // Inicializmi i porteve te servo-motorrit.
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {


  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);

  matja = pulseIn(echo1, HIGH);
  distanca = (0.034 * matja) / 2;

  if (distanca <= 20) {
    int vlera1 = EEPROM.read(111);  // Vlera e kendit te sero motorrit pasi te detektohet objekti nga sensori.
    Serial.println(vlera1);


    int angle = vlera1;

    while (angle != 200) {        // kushti perderisa kendi i servo motorrit nuk eshte konstant.         
      servo_motorri.write (angle);
      angle = angle + 10;         
      Serial.println(angle);
      delay (100);                // koha e uljes se Barrieres.
      digitalWrite(LED,HIGH);     //Semafori ON!
    }
    
    
    if(EEPROM.read(111) < 170){
  
      EEPROM.write(111, angle);
      delay (3000);            // Koha e ndritjes se Barrieres.
  
    }
    
  }
  else {
    servo_motorri.write(90);  //shkalla se sa leviz servomotorri
    EEPROM.write(111, 90);
    digitalWrite(LED,LOW); //semafori OFF.
  }




}
