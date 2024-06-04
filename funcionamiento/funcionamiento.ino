//-------------------------------
//Librerias Empleadas
//-------------------------------
#include <LiquidCrystal.h>
#include <DHT.h>
#include<Servo.h>
//--------------------------------
//Variables y constantes a emplear
//--------------------------------
//Para el sensor de agua   
#define pin_Encendido 12
#define pin_sensor  A0
const int BUZZER = 13; //Pin del buzzer
int valor_Sensor = 0; //Para determinar el valor arrojado por el sensor
//---------------------------------------------------------------------
//Parte del sensor de temperatura LM35
float vf_mv = 5000.0; //Voltaje de referncia en minivoltios
#define pin_LM35  A1
int valTemp = 0;
float mv = 0;
float tempC = 0;
float tempF = 0;
//---------------------------------------------------------------------
//Parte del servo motor y fotoresistencia
Servo motor;
int sol = A5;
int solVal;
//--------------------------------
int SENSOR = 2;
int temp, humedad;
int ledRed = A4;
int ledGreen = 11;
int ledBlue = 10;
//---------------------------------
LiquidCrystal lcd(4,5,6,7,8,9);
DHT dht (SENSOR, DHT11);

void setup() {
  //---------------------------------------
  // Inicializamos la interfaz para el LCD
  lcd.begin(16, 2);
  //--------------------------------------
  //Parte de la detencion de lluvia
  //---------------------------------
  Serial.begin(9600);
  pinMode(pin_Encendido,OUTPUT);  
  pinMode(BUZZER,OUTPUT);
  digitalWrite(pin_Encendido,LOW);
  //---------------------------------
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT); // Declaración de ledGren
  Serial.begin(9600);
  dht.begin();
  //-----------------------------------
  //Parte del rastreador de sol
  //-----------------------------------
  motor.attach(3);
  pinMode(sol, INPUT);
  //-----------------------------------
}

void loop() {
  motor.write(-5);
  //------------------------------------------
  //llamamos a la funcion encarga del mensaje
  mensajesInicio();
  delay(4000);
  lcd.clear();
  delay(1500);
  //-----------------------------------------
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
   //-----------------------------------------------------------------
   //Parte donde se trabaja la logica para detectar la lluvia
   //-----------------------------------------------------------------
    digitalWrite(pin_Encendido,HIGH); //Enciende el sensor
    delay(10);
    valor_Sensor = analogRead(pin_sensor); //Leemos el valor analogico arrojado por el sensor
    digitalWrite(pin_Encendido,LOW); //Apagamos el sensor
    //Imprimimos el valor obtenido
    // Serial.print("Valor del Sensor: ");
    // Serial.println(valor_Sensor);
    if(valor_Sensor > 100){
      lcd.print("Estado del clima");
      lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
      lcd.print("Lluvioso");
      digitalWrite(BUZZER,HIGH);
      delay(3000);
      digitalWrite(BUZZER,LOW);
   }
   else{
      lcd.print("Estado del clima");
      lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
      lcd.print("Despejado");
   }

  delay(1000);
  lcd.clear();
  delay(1500);
  //------------------------------------------------
  //Llamamos a la funcion de la temperatura
  temperatura();
  delay(2000);
  lcd.clear();
  delay(1000);
  //------------------------------------------------
  //Llamamos a la funcion de restrear sol
  //------------------------------------------------
  rastreadorLuzSolar();
  delay(2000);
  //------------------------------------------------
}

//---------------------------------------------------------------------------
//Funcion encargada del mensaje de bienvenida
//---------------------------------------------------------------------------
void mensajesInicio(){
    lcd.setCursor(0,0); //Indicamos la posicion donde se mostrara la primera parte del mensaje
    lcd.print("  Grupo #1");
    delay(4000);
    lcd.clear();//limpiamos el lcd para mostrar el nuevo mensaje
    delay(1500);
    //--------------------------------------------------------------------------
   lcd.blink();// Displayamos el blink del cursor sobre el LCD
   delay(3000);
   lcd.noBlink();//apagamos el blink del cursor
   //--------------------------------------------------------------------------
  //Segundo mensaje a mostrar
   lcd.setCursor(0,0);//Indicamos la posicion donde se mostrara la primera parte del mensaje
   lcd.print("Estacion");
   lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
   lcd.print("Meteorologica");
}

//---------------------------------------------------------------------------
//Parte donde se trabaja la logica de la captura y calculo de la temperatura
//---------------------------------------------------------------------------
 void temperatura(){
  //Obtenemos el valor del sensor LM35
  valTemp  = analogRead(pin_LM35);

  //Hacemos la conevrsion del valTemp en mv(milivoltios)
  mv = (valTemp / 1024.0) * vf_mv;

  //Convertimos el voltaje a temperatura en grados Celcius
  tempC = mv / 10;

  //Convertimos de Celsius a Fahrenheit
  tempF = tempC * 9 / 5 + 32;

  //Imprimos la temperatura 
  lcd.print("Temperatura LM35");
  delay(1000);
  lcd.clear();
  delay(1500);
  lcd.print(tempC);
  lcd.print(" Grados C");
  lcd.setCursor(0,1);
  lcd.print(tempF);
  lcd.print(" Graods F");
  delay(4000);
}

//---------------------------------------------------------------------------
//Parte donde se trabaja el rastreador del sol
//---------------------------------------------------------------------------
void rastreadorLuzSolar(){
   delay(2000);
    solVal = analogRead(sol);
    // Serial.println(solVal);
    delay(100);
    if(solVal <= 60){
      motor.write(100);
      lcd.print("Cielo Totalmente");
      lcd.setCursor(0,1);
      lcd.print("Soleado");
      delay(4000);
      lcd.clear();
      delay(2000);
    }
    else if(solVal >= 60 && solVal <= 300){
      motor.write(135);
      lcd.print("Atardecer cielo");
      lcd.setCursor(0,1);
      lcd.print("Despejado");
      delay(4000);
      lcd.clear();
      delay(2000);
    }
    else if(solVal >= 300 && solVal <= 600){
      motor.write(45);
      lcd.print("Cielo Nublado");
      lcd.setCursor(0,1);
      lcd.print("Parcialmente");
      delay(1000);
      lcd.clear();
      delay(2000);
    }
    else if( solVal >= 600 && solVal <= 1000){
      motor.write(20);
      lcd.print("Cielo Totalmente");
      lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
      lcd.print("Nublado");
      delay(4000);
      lcd.clear();
      delay(2000);
    }
    delay(1000);
}
