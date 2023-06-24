#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SoftwareSerial.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>

// Digital pin connected to the DHT sensor
#define DHTPIN 12   
#define MQ2PIN 14
#define BUZZER 0
// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);


float mq2Value;
float temperature;
float humidity;

#define WIFI_SSID "Doom"
#define WIFI_PASSWORD "Andrei1999"

#define API_KEY "AIzaSyCKXf4s9w99Wn3VInFAcNh-tB4i1F3AinM"
#define DATABASE_URL "https://espproject-d3e83-default-rtdb.europe-west1.firebasedatabase.app"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

String incomingData;
char serialData;

String gateway_temperature;
String gateway_humidity;
String gateway_gas;

SoftwareSerial ESPserial(4, 5); // RX, TX



// REPLACE WITH THE MAC Address of your receiver 
// this is the receiver




//DHT dht(DHTPIN, DHTTYPE);

// Define variables to store DHT readings to be sent
//float temperature;
//float humidity;

// Define variables to store incoming readings
//float incomingTemp_D98F;
//float incomingHum_D98F;
//float incomingTemp_A942;
//float incomingHum_A942;
//float incomingTemp_15B5;
//float incomingHum_15B5;

// Updates DHT readings every 30 seconds
const long interval = 30000; 
unsigned long previousMillis = 0;    // will store last time DHT was updated 

// Variable to store if sending data was successful
//String success;

//Structure example to send data
//Must match the receiver structure
//typedef struct struct_message {
//    float temp;
//    float hum;
//} struct_message;
//

typedef struct Data{
  int id;
  float temperature;
  float humidity;
} Data;

Data myData;

Data nodeMCU_D98F;
Data nodeMCU_A942;
Data nodeMCU_15B5;

Data nodeMCUStruct[3] = {nodeMCU_D98F, nodeMCU_A942, nodeMCU_15B5};

String str;

// Callback when data is sent
//void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
//  Serial.print("Last Packet Send Status: ");
//  if (sendStatus == 0){
//    Serial.println("Delivery success");
//  }
//  else{
//    Serial.println("Delivery fail");
//  }
//}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  nodeMCUStruct[myData.id-1].temperature = myData.temperature;
  nodeMCUStruct[myData.id-1].humidity = myData.humidity;
}

//void getReadings(){
//  // Read Temperature
//  temperature = dht.readTemperature();
//  // Read temperature as Fahrenheit (isFahrenheit = true)
//  //float t = dht.readTemperature(true);
//  if (isnan(temperature)){
//    Serial.println("Failed to read from DHT");
//    temperature = 0.0;
//  }
//  humidity = dht.readHumidity();
//  if (isnan(humidity)){
//    Serial.println("Failed to read from DHT");
//    humidity = 0.0;
//  }
//}

void printIncomingReadings(){
  
  Serial.println(temperature);
  Serial.println(humidity);
  Serial.println(mq2Value);
  Serial.println(nodeMCUStruct[0].temperature);
  Serial.println(nodeMCUStruct[0].humidity);
  Serial.println(nodeMCUStruct[1].temperature);
  Serial.println(nodeMCUStruct[1].humidity);
  Serial.println(nodeMCUStruct[2].temperature);
  Serial.println(nodeMCUStruct[2].humidity);
  

  ESPserial.println(temperature);
  ESPserial.println(humidity);
  ESPserial.println(mq2Value);
  ESPserial.println(nodeMCUStruct[0].temperature);
  ESPserial.println(nodeMCUStruct[0].humidity); 
  ESPserial.println(nodeMCUStruct[1].temperature);
  ESPserial.println(nodeMCUStruct[1].humidity);
  ESPserial.println(nodeMCUStruct[2].temperature);
  ESPserial.println(nodeMCUStruct[2].humidity);

}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  ESPserial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Init DHT sensor
  dht.begin();
  pinMode(BUZZER, OUTPUT);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  //WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  //esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  //esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

//  auth.user.email = "esp8266@gmail.com";
//  auth.user.password = "Tintenpatronen1&";

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
 
}
 
void loop() {
  digitalWrite(BUZZER, LOW);
  unsigned long currentMillis = millis();
  mq2Value = analogRead(MQ2PIN);
  humidity=dht.readHumidity();
  temperature=dht.readTemperature();
  if (isnan(mq2Value)){
    Serial.println("Can't read from MQ2");
    mq2Value = 0.0;
  }
  else mq2Value = map(mq2Value,0,850,0,100);
  
  if (isnan(temperature)){
    Serial.println("Can't read from DHT Temp");
    temperature = 0.0;
  }
  if (isnan(humidity)){
    Serial.println("Can't read from DHT Hum");
    humidity = 0.0;
  }
  printIncomingReadings();
  
  if (Firebase.ready())
  {
    Serial.println("Firebase is ready to be used");
    if (signupOK)
    {
      Serial.println("Signed up");
        Firebase.RTDB.setFloat(&fbdo, "kitchentemperature", temperature);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "kitchenhumidity", humidity);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "kitchengas", mq2Value);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "bedroom1temperature",nodeMCUStruct[0].temperature);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "bedroom1humidity",nodeMCUStruct[0].humidity);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "bedroom2temperature",nodeMCUStruct[1].temperature);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "bedroom2humidity",nodeMCUStruct[1].humidity);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "bathroomtemperature",nodeMCUStruct[2].temperature);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
        Firebase.RTDB.setFloat(&fbdo, "bathroomhumidity",nodeMCUStruct[2].humidity);
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      
    }
  }
  if (mq2Value > 50)
  {
    for(int i=1;i<=4;i++)
    {
      digitalWrite(BUZZER, HIGH);
      delay(500);
      digitalWrite(BUZZER, LOW);
      delay(500);
    }
  }
  
  
  
  delay(30000);
}
