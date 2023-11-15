// Incluimos librería
#include <DHT.h>
 
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
// Definir pines para el bombillo calentador
#define BOMBILLO_PIN 13 
#define VENTILADOR_PIN 10

void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600);
 
  // Comenzamos el sensor DHT
  dht.begin();
   // Configurar el pin del bombillo calentador como salida
  pinMode(BOMBILLO_PIN, OUTPUT);
  pinMode(VENTILADOR_PIN, OUTPUT);

  digitalWrite(13, HIGH);
  delay(500);

  digitalWrite(13, LOW);
  delay(500);
    digitalWrite(13, HIGH);
  delay(500);

  digitalWrite(13, LOW);
  delay(500);
}
 
void loop() {
    // Esperamos 5 segundos entre medidas
  delay(500);
 
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en Fahreheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  
  // Activar el bombillo calentador y el ventilador según la histeresis doble
  if (t < 37.5) {
    digitalWrite(BOMBILLO_PIN, HIGH); // Encender el bombillo calentador
    digitalWrite(VENTILADOR_PIN, HIGH); // Encender el ventilador
    Serial.println("Encendiendo");
  } else if (t >= 37.8) {
    digitalWrite(BOMBILLO_PIN, LOW); // Apagar el bombillo calentador
    digitalWrite(VENTILADOR_PIN, LOW); // Apagar el ventilador
    Serial.println("Apagando");
  }

}