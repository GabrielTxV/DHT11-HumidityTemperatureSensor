#include "DHT.h"

// Defina o pino onde o sensor DHT11 está conectado
#define DHTPIN 2

// Defina o tipo de sensor DHT
#define DHTTYPE DHT11

// Inicialize o sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Tempo de intervalo para cálculo da média (3 minutos)
#define INTERVAL 180000

// Variáveis para armazenamento das leituras e controle do tempo
unsigned long previousMillis = 0;
float totalTemperature = 0;
float totalHumidity = 0;
float temperatureReadings[100]; // Armazena até 100 leituras para cálculo do desvio padrão
float humidityReadings[100];
int numReadings = 0;

void setup() {
  // Inicia a comunicação serial para monitoramento
  Serial.begin(9600);
  
  // Inicializa o sensor DHT
  dht.begin();
}

void loop() {
  // Captura o tempo atual
  unsigned long currentMillis = millis();

  // Leitura da temperatura e umidade
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verifica se as leituras são válidas
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  // Exibe a leitura atual no monitor serial
  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Armazena as leituras em arrays para cálculo posterior do desvio padrão
  if (numReadings < 100) {
    temperatureReadings[numReadings] = temperature;
    humidityReadings[numReadings] = humidity;
  }

  // Acumula os valores para o cálculo da média
  totalTemperature += temperature;
  totalHumidity += humidity;
  numReadings++;

  // Verifica se o tempo de intervalo de 3 minutos foi atingido
  if (currentMillis - previousMillis >= INTERVAL) {
    // Calcula a média das leituras
    float averageTemperature = totalTemperature / numReadings;
    float averageHumidity = totalHumidity / numReadings;

    // Cálculo do desvio padrão para temperatura
    float sumSquaredTempDiff = 0;
    float sumSquaredHumDiff = 0;
    for (int i = 0; i < numReadings; i++) {
      sumSquaredTempDiff += pow(temperatureReadings[i] - averageTemperature, 2);
      sumSquaredHumDiff += pow(humidityReadings[i] - averageHumidity, 2);
    }
    float stdDevTemperature = sqrt(sumSquaredTempDiff / numReadings);
    float stdDevHumidity = sqrt(sumSquaredHumDiff / numReadings);

    // Exibe a média e o desvio padrão no monitor serial
    Serial.println("===== Resultados das últimas leituras =====");
    Serial.print("Média de Umidade: ");
    Serial.print(averageHumidity);
    Serial.print(" %\t");
    Serial.print("Desvio Padrão de Umidade: ");
    Serial.print(stdDevHumidity);
    Serial.println(" %");

    Serial.print("Média de Temperatura: ");
    Serial.print(averageTemperature);
    Serial.print(" *C\t");
    Serial.print("Desvio Padrão de Temperatura: ");
    Serial.print(stdDevTemperature);
    Serial.println(" *C");
    Serial.println("===========================================");

    // Reinicia as variáveis para o próximo ciclo de 3 minutos
    totalTemperature = 0;
    totalHumidity = 0;
    numReadings = 0;
    previousMillis = currentMillis;
  }

  // Atraso de 2 segundos entre as leituras
  delay(2000);
}
