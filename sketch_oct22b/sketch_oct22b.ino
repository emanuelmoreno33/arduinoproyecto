#include <Servo.h>
Servo servoMotor;
const int PIRPin= 7;
int detectado =0;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(13,OUTPUT);
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

void detector(int valor)
{
  
  const int LEDPin = 13;
  if (valor == HIGH)
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
  
}

int incomingbyte = 0;

void loop() {

  int value = digitalRead(PIRPin);
  if (detectado == 0)
  {
  detector(value);
  }

  int espval = digitalRead(2);
  Serial.println(espval);  
 
  if (espval == HIGH)
  {
    digitalWrite(13,HIGH);
    abrircerradura();
  }
  else
  {
    digitalWrite(13,LOW);
    cerrarcerradura();
  }

}
  

