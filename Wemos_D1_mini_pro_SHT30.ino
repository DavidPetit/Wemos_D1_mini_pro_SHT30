#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WEMOS_SHT3X.h>

// Wifi constants
const char* wifi_ssid = "...";
const char* wifi_pass = "...";

// MQTT constants
const char* mqtt_server = "...";
const char* mqtt_user = "...";
const char* mqtt_pass = "...";
const char* mqtt_temp_topic = "...";
const char* mqtt_hum_topic = "...";
const int mqtt_port = 8883;
boolean retained = true;

// SHT30 object
SHT3X sht30(0x45);

// Wifi client object
WiFiClient espClient;

// PubSub object
PubSubClient client(espClient);

// Callback for mqtt client
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

// Setup function
void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// Wifi Setup function
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Connect to MQTT broker function
void connect() {
  // Loop until we're connected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Loop
void loop() {
  if (!client.connected()) {
     connect();
  }
  
  client.loop();

  sht30.get();
  Serial.print("Temperature in Celsius : ");
  char buffer[10];
  client.publish(mqtt_temp_topic, dtostrf(sht30.cTemp, 5, 1, buffer), retained);
  Serial.println(sht30.cTemp);
  Serial.print("Relative Humidity : ");
  client.publish(mqtt_hum_topic, dtostrf(sht30.humidity, 5, 2, buffer), retained);
  Serial.println(sht30.humidity);
  Serial.println();
  delay(30000);
}
