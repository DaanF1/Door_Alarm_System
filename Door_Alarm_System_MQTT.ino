/* Door Alarm System using MQTT
  This system makes use of buttons to simulate the opening of a door.
  When the door is opened, the yellow LED light starts flickering. 
  After some time the red LED light starts flickering and a buzzer plays an alarm sound.
  The alarm can be stopped by pressing both buttons at once. 

  Protocol
  The MQTT broker contains the following topics:
  Door_Alarm_System (Base topic)
    1 (Unique ID)
      doorOpened (Indicates door state, 1 is open, 0 is closed)
      alarm (Indicates alarm state, 1 is on, 0 is off)

  Broker addresses
  Some brokers that you can use are:
    broker.hivemq.com
    test.mosquitto.org
    mqtt.eclipse.org
*/

// Board manager URL's: https://dl.espressif.com/dl/package_esp32_index.json
//                      https://arduino.esp8266.com/stable/package_esp8266com_index.json

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = ""; // WiFi name
const char* password = ""; // WiFi password
const char* mqtt_server = "broker.hivemq.com"; // Hosted broker service

const char* baseTopic = "Door_Alarm_System";
const char* id = "1"; // Device ID (needed for MQTT connection)
const char* doorName = "/doorOpened";
const char* alarmName = "/alarm";

const String doorTopic = String(baseTopic) + "/" + String(id) + doorName;
const String alarmTopic = String(baseTopic) + "/" + String(id) + alarmName;

// Clients:
WiFiClient espClient;
PubSubClient client(espClient);

// Pin layout:
const int buttonOne = 18;
const int buttonTwo = 5;
const int yellowLed = 4;
const int redLed = 15;
const int buzzer = 2;

bool doorOpened = false;
bool alarmOn = false;
bool prevStateButtonOne = HIGH;
bool prevStateButtonTwo = HIGH;

bool yellowLedState = true; // States for switching LED on/off
bool redLedState = true;  // States for switching LED on/off
const int partSecondsBeforeAlarm = 100; // How many part seconds need to pass before the alarm goes off
int countedPartSeconds = 0; // A part second is 0,1 seconds

void setup_wifi();
void reconnect(); // Reconnect to MQTT broker
void callback(char* topic, byte* payload, unsigned int length); // Callback from MQTT broker

void setup() {
  Serial.begin(115200); // Serial monitor

  // Set all LED pins to output
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  // Set buttons to input (pullup = LOW for registering input)
  pinMode(buttonOne, INPUT_PULLUP);
  pinMode(buttonTwo, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  digitalWrite(buttonOne, HIGH);
  digitalWrite(buttonTwo, HIGH);

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  setup_wifi();

  // Setup MQTT client
  client.setServer(mqtt_server, 1883); // Port 1883 is the standard unencrypted MQTT port
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) { // Auto reconnect when disconnected
    reconnect();
  }
  client.loop(); // Keep client connected

  // Check a button is pressed
  bool btnOne = digitalRead(buttonOne);
  bool btnTwo = digitalRead(buttonTwo);

  // Check if the door is opened
  if ((btnOne == LOW && prevStateButtonOne == HIGH) && (btnTwo == LOW && prevStateButtonTwo == HIGH)) {
    Serial.println("Both buttons pressed!");
    if (btnOne == LOW && btnTwo == LOW) {
      doorOpened = false;
    }
    String doorMsg = String(doorOpened);
    client.publish(doorTopic.c_str(), doorMsg.c_str()); // MQTT broker: door closed
  }
  else if (btnOne == LOW && prevStateButtonOne == HIGH) {
    Serial.println("Button one pressed!");
    if (btnOne == LOW) {
      doorOpened = true;
    }
    String doorMsg = String(doorOpened);
    client.publish(doorTopic.c_str(), doorMsg.c_str()); // MQTT broker: door opened
  }
  else if (btnTwo == LOW && prevStateButtonTwo == HIGH) {
    Serial.println("Button two pressed!");
    if (btnTwo == LOW) {
      doorOpened = true;
    }
    String doorMsg = String(doorOpened);
    client.publish(doorTopic.c_str(), doorMsg.c_str()); // MQTT broker: door opened
  }

  // LED & buzzer logic
  if (alarmOn) {
    countedPartSeconds++;

    if (countedPartSeconds < partSecondsBeforeAlarm) { // Flicker yellow LED
      if (yellowLedState) {
        digitalWrite(yellowLed, HIGH);
        yellowLedState = false;
      } 
      else {
        digitalWrite(yellowLed, LOW);
        yellowLedState = true;
      }
    }
    else { // Flicker red LED and sound buzzer alarm
      digitalWrite(yellowLed, LOW);

      if (redLedState){
        digitalWrite(redLed, HIGH);
        redLedState = false;
        tone(buzzer, 440); // Pitch buzzer low
      } 
      else {
        digitalWrite(redLed, LOW);
        redLedState = true;
        tone(buzzer, 660); // Pitch buzzer high
      }
      delay(900); // Add time to the part second to make it 1 second delay total
    }

    // Add time to make a part second (0.1 second)
    delay(90);
  }

  prevStateButtonOne = btnOne;
  prevStateButtonTwo = btnTwo;
  delay(10); // Short delay to not send too much data
}

void setup_wifi() {
  delay(10);
  Serial.println();
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect(id)) { // If the client is connected to the broker, subscribe to the relevant topics
      Serial.println("connected");

      client.subscribe(doorTopic.c_str());
      client.subscribe(alarmTopic.c_str());
    } 
    else { // Print failed state and retry connection later
      Serial.print("failed, rc=");
      Serial.print(client.state());

      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) { // Convert the given payload to a readable message
    message += (char)payload[i];
  }
  Serial.print("Message arrived from [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (String(topic) == doorTopic) {
    if (message == "0") { // 0 indicates door closed
      Serial.println("Door opened!");

      alarmOn = false;
      String alarmMsg = String(alarmOn);
      client.publish(alarmTopic.c_str(), alarmMsg.c_str()); // MQTT broker: alarm off
    }
    else if (message == "1") { // 1 indicates door opened
      Serial.println("Door opened!");

      alarmOn = true;
      String alarmMsg = String(alarmOn);
      client.publish(alarmTopic.c_str(), alarmMsg.c_str()); // MQTT broker: alarm on
    }
  } 
  else if (String(topic) == alarmTopic) {
    if (message == "0") { // 0 indicates alarm turned off
      Serial.println("Alarm turned off!");
      alarmOn = false;
      countedPartSeconds = 0;

      // Stop LED's from flickering and stop the buzzer sounding alarm
      tone(buzzer, 0);
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, LOW);
    }
  }
}