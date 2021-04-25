//webserver for domosoft

#define  DomoSoft  "4.3"
#define  RelaySoft  "2.0"
#define  build "RL2-25042021"

String  version = String(DomoSoft) + " <br>Versione RelaySoft: " + String(RelaySoft) + "<br>Build: " + String(build);



#include <WiFiManager.h>
int isUpdate = 0;
#include <PubSubClient.h>
#include "FS.h"
#include <ArduinoJson.h>
#include <StreamString.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>
#include <ESP8266HTTPUpdateServerDomoSoft.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "it.pool.ntp.org", 7200, 60000);
String deviceID = "";
String MyApiKey = "";
int wifi_ok;
File Main;
bool isConnected = false;

String hassio_prefix = "homeassistant";

// MQTT variabili ----------------------------
String mqtt_server = "";
String mqtt_user = "";
String mqtt_password = "";

String IPaddress;

String devname;
String devname2;

String rele1_control_topic;
String rele1_status_topic;

String rele2_control_topic;
String rele2_status_topic;

String wil_topic;

long sync;
long lastReconnectAttempt = 0;


byte timeSet;
byte timeState;
byte E_MQ = 0;

String text;
char car;
int printa = 0;
byte preIN2;


int pin1;
int pin2;
int mode1;
String payloadON;
String payloadOFF;
bool pulse;
String type;
int in1;
int payloadIN;
int bootState;
int inmode2;
int in2;
int payloadIN2;
int led1;
int ledON;
int ledOFF;

String SerialData;
long serialBaud = 115200;
byte ricevuto;

MDNSResponder mdns;
byte mqtt_conf = 1;
String st;
String content;
int statusCode;

byte rele1S = 0;
byte rele2S = 0;

byte discovered = 0;

//SICUREZZA

String username = "";
String password = "";
const char* realm = "DomoSoft";

//Bootloader
byte bootMode_add = 97;
byte bootMode = 0;

//this ssid and Password is for Hotspot connection

WiFiClient httpclient;
ESP8266WebServer server(80);
PubSubClient client(httpclient);
ESP8266HTTPUpdateServer httpUpdater;

DNSServer dnsServer;
IPAddress apIP(192, 168, 1, 1);
const byte DNS_PORT = 53;

void setup(void) {
  EEPROM.begin(512);
  SPIFFS.begin();
  if (SPIFFS.exists("/settings/serial_baud")) {
    Main = SPIFFS.open("/settings/serial_baud", "r");
    String ciaoF;
    while (Main.available()) {
      ciaoF += char(Main.read());
    }
    Main.close();
    serialBaud = ciaoF.toInt();
    Serial.begin(serialBaud);
  } else {
    Serial.begin(serialBaud);
  }

  Serial.println();
  Serial.println("--------DC DOMOTICS--------");
  Serial.println("--------DOMOSOFT 4.3--------");
  Serial.println(version);
  Serial.println();
  delay(100);
  bootMode = EEPROM.read(bootMode_add); //read bootMode

  if (!SPIFFS.exists("/Config_ok")) {
    delay(3000);
    Serial.println("ERRORE 02: FileSystem danneggiato! Ricaricare correttamente il firmware.");
    ESP.deepSleep(  ESP.deepSleepMax(), WAKE_RF_DISABLED);
  }
  readConf();
  rele1S = EEPROM.read(300);
  rele2S = EEPROM.read(301);
  if (pulse == false) {
    if (bootState == 0) {
      if (mode1 == 0) {
        digitalWrite(pin1, payloadOFF.toInt());
        digitalWrite(pin2, payloadOFF.toInt());
        if (led1 != 255) {
          digitalWrite(led1, ledOFF);
        }
      }
      else if (mode1 == 1) {

        Serial.print(payloadOFF);
        if (led1 != 255) {
          digitalWrite(led1, ledOFF);
        }
      }
      rele1S = 0;
      EEPROM.write(300, rele1S);
      EEPROM.commit();
      rele2S = 0;
      EEPROM.write(301, rele2S);
      EEPROM.commit();

    } else if (bootState == 1) {
      if (mode1 == 0) {
        digitalWrite(pin1, payloadON.toInt());
        digitalWrite(pin2, payloadON.toInt());
        if (led1 != 255) {
          digitalWrite(led1, ledON);
        }
      }
      else if (mode1 == 1) {

        Serial.print(payloadON);
      }
      rele1S = 1;
      EEPROM.write(300, rele1S);
      EEPROM.commit();
      rele2S = 1;
      EEPROM.write(301, rele2S);
      EEPROM.commit();

    } else {

      if (pulse) {} else {
        if (rele1S) {
          if (mode1 == 0) {
            digitalWrite(pin1, payloadON.toInt());
            if (led1 != 255) {
              digitalWrite(led1, ledON);
            }
          }
          else if (mode1 == 1) {

            Serial.print(payloadON);
            if (led1 != 255) {
              digitalWrite(led1, ledON);
            }
          }
        } else {
          if (mode1 == 0) {
            digitalWrite(pin1, payloadOFF.toInt());
            if (led1 != 255) {
              digitalWrite(led1, ledOFF);
            }
          }
          else if (mode1 == 1) {

            Serial.print(payloadOFF);
            if (led1 != 255) {
              digitalWrite(led1, ledOFF);
            }
          }
        }
        if (rele2S) {
          if (mode1 == 0) {
            digitalWrite(pin2, payloadON.toInt());
            if (led1 != 255) {
              digitalWrite(led1, ledON);
            }
          }
          else if (mode1 == 1) {

            Serial.print(payloadON);
            if (led1 != 255) {
              digitalWrite(led1, ledON);
            }
          }
        } else {
          if (mode1 == 0) {
            digitalWrite(pin2, payloadOFF.toInt());
            if (led1 != 255) {
              digitalWrite(led1, ledOFF);
            }
          }
          else if (mode1 == 1) {

            Serial.print(payloadOFF);
            if (led1 != 255) {
              digitalWrite(led1, ledOFF);
            }
          }
        }
      }

    }


  } else {
    digitalWrite(pin1, payloadOFF.toInt());
    digitalWrite(pin2, payloadOFF.toInt());
  }
  WiFi.hostname("DomoSoft");

  delay(10);
  // Serial.println();
  //Serial.println();
  //Serial.println("Avvio");


  for (int i = 166; i < 181; ++i)
  {
    username += char(EEPROM.read(i));

  }

  for (int i = 181; i < 199; ++i)
  {
    password += char(EEPROM.read(i));

  }

  mqtt_conf = EEPROM.read(202);
  timeState = EEPROM.read(311);
  preIN2 = EEPROM.read(301);







  if (testWifi()) {
    bootConfig();
    relay_sync();
    relay2_sync();
    Serial.print("WIFI IP: ");
    Serial.println(WiFi.localIP());
    IPaddress =  WiFi.localIP().toString();
    return;
  }
  setAP();
  // setupAP();



}

void loop(void) {
  if (in1 != 255) {
    verifica_pulsante();
  }
  if (in2 != 255) {
    verifica_pulsante2();
  }
  timeClient.update();
  if (mqtt_conf == 1) {
    client.loop();
    if (!client.connected()) {
      long now = millis();
      if (now - lastReconnectAttempt > 30000) {
        lastReconnectAttempt = now;
        E_MQ = 1;
        // Attempt to reconnect
        if (mqtt_conn()) {
          lastReconnectAttempt = 0;
          E_MQ = 0;
          client.publish(wil_topic.c_str(), "online", true);
        }
      } else {
        client.loop();
      }


    }
  }


  long now = millis();
  if (now - sync > 10000) {
    sync = now;
    relay_sync();
  }

  server.handleClient();

  if (wifi_ok == 0) {
    dnsServer.processNextRequest();
    Ricevi();
  }

  if (timeState == 1) {
    check_hour();
  }

}
