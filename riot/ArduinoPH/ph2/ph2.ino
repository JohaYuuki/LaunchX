
float calibration = 28.00; //valor de calibración
const int analogInPin = A0;
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10], temp;
String valorpH;
char nodo2[256];
char lectura[6];

void setup() {
  Serial.begin(115200);
}

float lecturaPH() {
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(analogInPin);
    delay(30);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++) {
    avgValue += buf[i];
  }

  float pHVol = (float)avgValue * 5.0 / 1024 / 6;
  //Serial.print("pHVol: ");
  //Serial.println(pHVol);
  float phValue = -5.70 * pHVol + calibration;
  //Serial.print("phValue: ");
  //Serial.println(phValue);
  delay(200);
  return (phValue);
}

void loop() {
  //Pasar de float a string es medio raro pero este combo es bueno

  char phChar[32]; //Almacena la lecutra en un char array para conversion

  float phFloat = lecturaPH(); //Almacena en un float el return de la funcion
  //Serial.print("phFloat: ");
  //Serial.println(phFloat);
  
  dtostrf(phFloat, 4, 2, phChar); //Convierte un float(phFloat) de minimo 4 de longitud con 2 decimales hacia un char(phChar)
  String phString(phChar); //Se crea una variable String con el contenido del char(phChar)
  //Serial.print("phChar: ");
  //Serial.println(phChar);
  
  //phString.replace(" ", ""); //Al string se le quitan los espacios en blanco producto de la conversion float->char y queda listo

  //Esto solo hacer con JSON ya listo para ser enviado por Serial, no con cada lectura, es solo un ejemplo.
  //TIP: para mandar por Serial.write un String no es comptible, "esto si" pero String val = "esto" no se puede, busquen la documentacion.
  //Lo que si es compatible es enviar Serial.write(charArray);
  //Por eso se convierte una vez más el String sin espacios en blanco resultado del float->char y se guarda devuelta en phChar.
  /*
    phString.toCharArray(phChar, phString.length());
    Serial.write(phChar); //lo que se va a mandar por serial
    Serial.write("\n"); //Siempre debe ir el salto de linea
    delay(2000); //cambiar a conveniencia
  */

  sprintf(nodo2, "{\"id\":\"2\",\"datetime\":\"2022-06-13 22:10:10\",\"ph\":\"%s\"}\n", phChar);
  Serial.write(nodo2);
  //Serial.write("\n");
  //Serial.print(nodo2);
  //Serial.println(" ");
  //Serial.print(valorpH);
  //Serial.println("string");
  //Serial.print(lecturaPH());
  //Serial.println(" ");
  delay(12000);
}
