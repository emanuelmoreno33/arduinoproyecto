#include <Servo.h>
Servo servoMotor;
const int PIRPin= 7;
const int BuzzerPin = 11;
int detectado =0;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(9);
  pinMode(13, OUTPUT);
  pinMode(PIRPin, INPUT);
}

void abrircerradura()
{
  // Desplazamos a la posición 0º
  servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);
}

void cerrarcerradura()
{
  // Desplazamos a la posición 0º
  servoMotor.write(90);
  // Esperamos 1 segundo
  delay(1000);
}

void detector()
{
 
}

int incomingbyte = 0;
void loop() {

 const int LEDPin =13;
  int value = digitalRead(PIRPin);
  if (value == HIGH)
  {
    digitalWrite(LEDPin, HIGH);
    delay(50);
    digitalWrite(LEDPin, LOW);
    delay(50);
    detectado = 1;
  }
  else
  {
    digitalWrite(LEDPin, LOW);
    detectado = 0;
  }
  if (detectado == 1)
  {
    Serial.println("detectado ");
    delay(500);
  }
  
  
  if (Serial.available() > 0) {
    incomingbyte = Serial.read();
    if (incomingbyte == 49)
    {
    abrircerradura();
    delay(1000);
    Serial.print("abriendo ");
    Serial.println(incomingbyte, DEC);
    }
    else if(incomingbyte == 50)
    {
    cerrarcerradura();
     delay(1000);
     Serial.print("cerrando ");
     Serial.println(incomingbyte, DEC);
    }
  }
  }

