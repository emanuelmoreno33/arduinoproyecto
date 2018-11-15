#include <Servo.h>
#include <SoftwareSerial.h>
Servo servoMotor;
const int PIRPin= 7;
int detectado =0;
SoftwareSerial SIM900(7, 8);

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(13,OUTPUT);
  servoMotor.attach(9);
  pinMode(13, OUTPUT);
  pinMode(PIRPin, INPUT);
  SIM900.begin(19200);
  delay(15000);
}

void llamar()
   {
      Serial.println("Realizando llamada...");
      SIM900.println("ATD6642923050;");  //Comando AT para realizar una llamada
      delay(20000);  // Espera 20 segundos mientras realiza la llamada
      SIM900.println("ATH");  // Cuelga la llamada
      delay(1000);
      Serial.println("Llamada finalizada");
   }
void mensaje_sms()
{
 Serial.println("Enviando SMS...");
      SIM900.print("AT+CMGF=1\r");  //Configura el modo texto para enviar o recibir mensajes
      delay(1000);
      SIM900.println("AT+CMGS=\"6642923050\"");  //Numero al que vamos a enviar el mensaje
      delay(1000);
      SIM900.println("El sensor detecto que alguien esta en tu casa.");  // Texto del SMS
      delay(100);
      SIM900.println((char)26); //Comando de finalización ^Z
      delay(100);
      SIM900.println();
      delay(5000);  // Esperamos un tiempo para que envíe el SMS
      Serial.println("SMS enviado");
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
    llamar();
    mensaje_sms();
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
  

