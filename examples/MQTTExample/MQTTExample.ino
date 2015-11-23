#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DeviceManager.h>
#include <Button.h>
#include <LED.h>
#include <DeviceType.h>

static byte MESSAGE_BROKER_IP[] = { 192, 168, 1, 100 };
static int MESSAGE_BROKER_PORT = 1883;

DeviceManager* deviceManager;

EthernetClient ethClient;
PubSubClient client(MESSAGE_BROKER_IP, MESSAGE_BROKER_PORT, onMessageCallBack,
		ethClient);

byte MAC[] = { 
  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

char* MESSAGING_TOPIC_IN = "sensor-topic-in";
char* MESSAGING_TOPIC_OUT = "actor-topic-out";
char* MESSAGING_CLIENT_ID = "Arduino Home Gateway";

enum {
  DEVICEID_LED1 = 1,
  DEVICEID_LED2 = 2,
  DEVICEID_LED3 = 3,
  DEVICEID_LED4 = 4,
  DEVICEID_TASTER1 = 5,
  DEVICEID_TASTER2 = 6
};
enum {
  DIGITAL_IO0 = 0,
  DIGITAL_IO1 = 1,
  DIGITAL_IO2 = 2,
  DIGITAL_IO3 = 3,
  DIGITAL_IO4 = 4,
  DIGITAL_IO5 = 5,
  DIGITAL_IO6 = 6,
  DIGITAL_IO7 = 7,
  DIGITAL_IO8 = 8,
  DIGITAL_IO9 = 9,
  DIGITAL_IO10 = 10,
  DIGITAL_IO11 = 11,
  DIGITAL_IO12 = 12,
  DIGITAL_IO13 = 13
};


void setup() {                

  deviceManager = new DeviceManager();
  Button* taster1 = new Button(0x1000, "Simple Button", 6, handleActorEvent);
  Button* taster2 = new Button(0x1001, "Simple Button", 7, handleActorEvent);

  LED* led1 = new LED(0x2000,"RGB LED Modul", 2);
  LED* led2 = new LED(0x2001,"RGB LED Modul", 3);
  LED* led3 = new LED(0x2002,"RGB LED Modul", 4);
  LED* led4 = new LED(0x2003,"RGB LED Modul", 5);

  deviceManager->addSensor(taster1->getID(), taster1);
  deviceManager->addSensor(taster2->getID(), taster2);

  deviceManager->addActor(led1->getID(),led1);
  deviceManager->addActor(led2->getID(),led2);
  deviceManager->addActor(led3->getID(),led3);
  deviceManager->addActor(led4->getID(),led4);


  Serial.begin(9600);
  Serial.println("Arduino HomeGateway 0.1 try to connect to MQTT Server");
  connect();
}

void loop() {
  client.loop();
  deviceManager->onLoop();
}


void handleActorEvent(int sensorID, int value) {
  char buffer[10];
  sprintf(buffer, "[%d,%d]", sensorID, value);

  client.publish(MESSAGING_TOPIC_IN, buffer);
}
void onMessageCallBack(char* topic, byte* payload, unsigned int length) {

  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*) malloc(length);
  // Copy the payload to the new buffer
  memcpy(p, payload, length);
  char buffer[length + 1];
  snprintf(buffer, length + 1, "%s", p);
  free(p);

  Serial.println("empfange Nachricht:");
  Serial.println(buffer);

  Serial.println("parse Nachricht:");

  String message(buffer);
  int start = message.indexOf('[');
  int end = message.indexOf(']');
  message = message.substring(start + 1, end);
  start = message.indexOf(',');
  String strId = message.substring(0, start);
  String strValue = message.substring(start + 1, message.length());

  Serial.println("ID: " + strId);
  Serial.println("Value: " + strValue);

  int id = strId.toInt();
  int value = strValue.toInt();
  deviceManager->setValue(id,value);
}

void connect() {

  Ethernet.begin(MAC);
  int connRC = client.connect(MESSAGING_CLIENT_ID);

  if (!connRC) {
    Serial.println(connRC);
    Serial.println("Could not connect to MQTT Server");
    Serial.println("Please reset the arduino to try again");

    delay(100);
    exit(-1);
  } 
  else {
    Serial.println("Connected to MQTT Server...");
    client.subscribe(MESSAGING_TOPIC_OUT);

  }
}


