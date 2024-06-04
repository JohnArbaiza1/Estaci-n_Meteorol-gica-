#include <LiquidCrystal.h>
#include <DHT.h>
int SENSOR = 2;
int temp, humedad;
int ledRed = 10;
int ledGreen = 11;
int ledBlue = 12;

LiquidCrystal lcd(4,5,6,7,8,9);
DHT dht (SENSOR, DHT11);

void setup() {

  // Inicializamos la interfaz para el LCD
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT); // Declaración de ledGren
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  temp = dht.readTemperature();
  humedad = dht.readHumidity();
  if (temp < 27) {
    digitalWrite(ledBlue, 1);
    digitalWrite(ledRed, 0);
    digitalWrite(ledGreen, 0);
  } else if (temp >= 27 && temp < 31) {
    digitalWrite(ledGreen, 1);
    digitalWrite(ledBlue, 0);
    digitalWrite(ledRed, 0);
  } else {
    digitalWrite(ledRed, 1);
    digitalWrite(ledBlue, 0);
    digitalWrite(ledGreen, 0);
  }
  //Primer mensaje a mostrar en el LCD
  lcd.setCursor(0,0); //Indicamos la posicion donde se mostrara la primera parte del mensaje
   lcd.print("Temperatura");
   lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
   lcd.print(temp);
   lcd.print(" Centigrados");
   delay(1000);
   lcd.clear();//limpiamos el lcd para mostrar el nuevo mensaje
   delay(1500);
   //-------------------------------------
   lcd.blink();// Displayamos el blink del cursor sobre el LCD
   delay(1000);
   lcd.noBlink();//apagamos el blink del cursor
   //--------------------------------------
   //Segundo mensaje a mostrar
   lcd.setCursor(0,0);//Indicamos la posicion donde se mostrara la primera parte del mensaje
   lcd.print("   Humedad");
   lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
   lcd.print("   ");
   lcd.print(humedad);
   lcd.print(" g/m3");
   delay(1000);
   lcd.clear();
   delay(1500);
}
