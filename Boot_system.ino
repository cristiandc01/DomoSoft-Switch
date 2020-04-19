void bootConfig() {
  wifi_ok = 1;
  /*  Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("SoftAP IP: ");
    Serial.println(WiFi.softAPIP());
  */

  Main = SPIFFS.open("/settings/time_correction", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();
  Serial.println(ciaoF);
  timeClient.setTimeOffset(ciaoF.toInt());
  timeClient.setUpdateInterval(900000);
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  if (timeState == 1) {
    bootcheck();
  }
  Main = SPIFFS.open("/device_name", "r");

  while (Main.available()) {

    devname += char(Main.read());
  }
  Main.close();
  devname2 =  devname;
  WiFi.hostname(devname2);
/* SINRIC VERRA DISATTIVATO
  if (sinricOK) {
    Main = SPIFFS.open("/cloud/api", "r");
    while (Main.available()) {
      MyApiKey += char(Main.read());
    }
    Main.close();
    delay(200);
    deviceID = "";
    Main = SPIFFS.open("/cloud/device_id", "r");
    while (Main.available()) {
      deviceID += char(Main.read());
    }
    Main.close();
    connectSinric();
  }
*/
  if (mqtt_conf) {

    discovered = EEPROM.read(201);
    hassio_prefix = "";
    Main = SPIFFS.open("/discovery/prefix", "r");

    while (Main.available()) {

      hassio_prefix += char(Main.read());
    }
    Main.close();

    rele1_control_topic = "relay/rele1/control_" + devname;



    rele1_status_topic = "relay/rele1/status_" + devname;


    mqtt_server = "";
    for (int i = 108; i < 123; ++i)
    {
      mqtt_server += char(EEPROM.read(i));
    }

    mqtt_user = "";
    for (int i = 124; i < 144; ++i)
    {
      mqtt_user += char(EEPROM.read(i));
    }

    mqtt_password = "";
    for (int i = 145; i < 165; ++i)
    {
      mqtt_password  += char(EEPROM.read(i));
    }

    client.setServer(mqtt_server.c_str(), 1883);

    if (mqtt_conn()) { //tento la prima connessione
      lastReconnectAttempt = 0;
      E_MQ = 0;
      if (discovered) {
        discover();
      }
      MQTT_sync();
    }
  }

}
