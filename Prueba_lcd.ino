#include <LiquidCrystal.h>

LiquidCrystal lcd(4,5,6,7,8,9);

void setup() {

  // Inicializamos la interfaz para el LCD
  lcd.begin(16,2);
}

void loop() {
  //Primer mensaje a mostrar en el LCD
  lcd.setCursor(0,0); //Indicamos la posicion donde se mostrara la primera parte del mensaje
   lcd.print("Bendiciones");
   lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
   lcd.print("Grupo #1");
   delay(4000);
   lcd.clear();//limpiamos el lcd para mostrar el nuevo mensaje
   delay(1500);
   //-------------------------------------
   lcd.blink();// Displayamos el blink del cursor sobre el LCD
   delay(3000);
   lcd.noBlink();//apagamos el blink del cursor
   //--------------------------------------
   //Segundo mensaje a mostrar
   lcd.setCursor(0,0);//Indicamos la posicion donde se mostrara la primera parte del mensaje
   lcd.print("Estacion");
   lcd.setCursor(0,1);// posicion para la segunda parte del mensaje
   lcd.print("Meteorologica");
   delay(4000);
   lcd.clear();
   delay(1500);
}
