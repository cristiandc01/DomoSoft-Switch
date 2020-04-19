
bool testWifi(void) {
  if (bootMode == 0) {
    if (EEPROM.read(200) == 1) {
      if (WiFi.SSID() == "") {
        return false;
      }
      int c = 1;
      Serial.println("Waiting for Wifi to connect");

      while (c) {
        if (WiFi.status() == WL_CONNECTED) {
          normalset();

          return true;

        }

        delay(500);
        char read = Serial.read();
        switch (read) {
          case '*':
            EEPROM.write(200, 0);
            EEPROM.commit();
            ESP.restart();


        }
      }

      return false;
    } else {
      mqtt_conf = 0;
      Serial.println("NEW USER, opening AP");
      return false;
    }


  } else {
    mqtt_conf = 0;
    EEPROM.write(bootMode_add, 0);
    EEPROM.commit();
    return false;
  }
}




void launchWeb(int webtype) {
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  dnsServer.start(DNS_PORT, "*", apIP);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  content = "<!DOCTYPE HTML>\r\n<html><head><meta name='viewport' content='width=device-width, initial-scale=1'></head><h3>Configurazione guidata WiFi DomoSoft</h3><h5>Generic Relay 1CH</h5>";  if (bootMode) {
    content += "<p>E' stato premuto il pulsante di RESET, tuttavia le impostazioni interne non sono state ripristinate!</p><a href='HardReset'><button>Ripristino totale</button></a><a href='reboot'><button>Riavvia</button></a><br>";
  }
  content += "<br><h4>Scegli un WiFi disponibile</h4><br>";
  content += "<p>";
  content += st;
  content += "</p><h4>Inserisci le informazioni della rete</h4><div><form method='get' action='setting'><label>Nome Rete: </label><input name='ssid' length=32><br><label>Password rete: </label><input name='pass' type='password' length=64><br><input type='submit'></form></div>";

  createWebServer(webtype);
  // Start the server
  server.onNotFound([]() {
    server.send(200, "text/html", content);
  });
  server.begin();
  Serial.println("Server started");
}
void setupAP() {


  if (EEPROM.read(200) == 255) {
    delay(1000);

    Serial.println( "Sembra che la memoria sia danneggiata. Eseguo un Ripristino...");

    delay(800);
    for (int i = 0; i < 512; ++i) {
      EEPROM.write(i, 0);
    }
    EEPROM.commit();
    ESP.restart();
  }
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {


    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("DomoSoft Relay", "", 6);
  Serial.println("softap");
  launchWeb(1);
  Serial.println("over");


}

void createWebServer(int webtype)
{
  if ( webtype == 1 ) {
    server.on("/", []() {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      server.send(200, "text/html", content);
    });
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      server.send(200, "text/html", "<html><body<h1>Configurazione avvenuta! prego riconnettersi al propio wifi</h1>");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 97; ++i) {
          EEPROM.write(i, 0);
        }
        WiFi.disconnect();
        WiFi.begin(qsid, qpass);
        //write config hapneed
        EEPROM.write(200, 1);
        EEPROM.commit();
        server.send(200, "text/html", "<html><body<h1>Configurazione avvenuta! prego riconnettersi al propio wifi</h1>");
        statusCode = 200;
        ESP.restart();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.send(statusCode, "application/json", content);
    });





    server.on("/reboot", []() {
      ESP.restart();
      delay(1000);
    });

    server.on("/HardReset", []() {
      server.send(200, "text/html", "<html><body<h1>Reset Avvenuto, il dispositivo si sta riavviando...</h1>");

      HardReset();
      delay(1000);
      ESP.restart();
    });

    httpUpdater.setup(&server, "/sideload/firmware");
  } else if (webtype == 0) {
    server.on("/", []() {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      server.send(200, "application/json", "{\"IP\":\"" + ipStr + "\"}");
    });

  }
}
