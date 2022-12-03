char nodo2[256]; //variable para envió de datos por serial
//HUMEDAD
const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

//TEMPERATURA
//-Libraries
#include <DHT.h>
//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//-Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
  Serial.begin(115200);
  dht.begin();
}

float lecturaHUMEDAD() {
  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent >= 100)
  {
    soilmoisturepercent = 100;
    return (soilmoisturepercent);
  }
  else if (soilmoisturepercent <= 0)
  {
    soilmoisturepercent = 0;
    return (soilmoisturepercent);
  }
  else if (soilmoisturepercent > 0 && soilmoisturepercent < 100)
  {
    return (soilmoisturepercent);
  }
  delay(250);
}

float lecturaTEMPERATURA(){
    //Read data and store it to variables hum and temp
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    return (temp);
    delay(250); //Delay
}

void loop() {

  char humChar[32]; //Almacena la lecutra en un char array para conversion
  char tempChar[32]; //Almacena la lecutra en un char array para conversion

  float humFloat = lecturaHUMEDAD(); //Almacena en un float el return de la funcion
  float tempFloat = lecturaTEMPERATURA(); //Almacena en un float el return de la funcion

  dtostrf(humFloat, 4, 2, humChar); //Convierte un float(phFloat) de minimo 4 de longitud con 2 decimales hacia un char(phChar)
  //String phString(phChar); //Se crea una variable String con el contenido del char(phChar)
  dtostrf(tempFloat, 4, 2, tempChar); //Convierte un float(phFloat) de minimo 4 de longitud con 2 decimales hacia un char(phChar)
  //String phString(condChar); //Se crea una variable String con el contenido del char(phChar)
  //Serial.print("phChar: ");
  //Serial.println(phChar);

  sprintf(nodo2, "{\"id\":\"2\",\"datetime\":\"2022-06-13 22:10:10\",\"humedad\":\"%s\",\"temperatura\":\"%s\"}\n", humChar, tempChar);
  Serial.write(nodo2);
  delay(12000);
}
