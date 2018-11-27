#include <Servo.h>
#include <SoftwareSerial.h>
Servo servoMotor;
const int PIRPin= 5;
SoftwareSerial SIM900(7, 8);

void setup() {
  SIM900.begin(19200);
  Serial.begin(19200);
  pinMode(12,INPUT);
  pinMode(13,OUTPUT);
  servoMotor.attach(9);
  pinMode(PIRPin, INPUT);
 
}

void llamar()
   {
      Serial.println("Realizando llamada...");
      SIM900.println("ATD6642923050;");  //Comando AT para realizar una llamada
      delay(15000);  // Espera 20 segundos mientras realiza la llamada
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

void mensaje_sms2()
{
 Serial.println("Enviando SMS...");
      SIM900.print("AT+CMGF=1\r");  //Configura el modo texto para enviar o recibir mensajes
      delay(1000);
      SIM900.println("AT+CMGS=\"6641975384\"");  //Numero al que vamos a enviar el mensaje
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
  // Desplazamos a la posición 90º
  servoMotor.write(45);
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
    Serial.println("detectado ");
    delay(500);
    llamar();
    mensaje_sms();
    mensaje_sms2();
  }
  else
  {
    digitalWrite(LEDPin, LOW);
  }
  
}

void loop() {

  int espval = digitalRead(12);
  Serial.println(espval);  
 
  if (espval == HIGH)
  {
    digitalWrite(13,HIGH);
    abrircerradura();
    int value = digitalRead(PIRPin);
     detector(value);
  }
  else
  {
    digitalWrite(13,LOW);
    cerrarcerradura();
  }

}
  

