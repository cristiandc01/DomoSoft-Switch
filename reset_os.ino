void HardReset() {
  for (int i = 0; i < 360; ++i) {
    EEPROM.write(i, 0);
  }

  Main = SPIFFS.open("/device_name", "w");
  Main.print("DomoSoft device");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/discovery/prefix", "w");
  Main.print("homeassistant");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/crono/0.json", "w");
  Main.print("{\"on1\":\"N\",\"off1\":\"N\",\"on2\":\"N\",\"off2\":\"N\",\"on3\":\"N\",\"off3\":\"N\"}");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/crono/1.json", "w");
  Main.print("{\"on1\":\"N\",\"off1\":\"N\",\"on2\":\"N\",\"off2\":\"N\",\"on3\":\"N\",\"off3\":\"N\"}");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/crono/2.json", "w");
  Main.print("{\"on1\":\"N\",\"off1\":\"N\",\"on2\":\"N\",\"off2\":\"N\",\"on3\":\"N\",\"off3\":\"N\"}");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/crono/3.json", "w");
  Main.print("{\"on1\":\"N\",\"off1\":\"N\",\"on2\":\"N\",\"off2\":\"N\",\"on3\":\"N\",\"off3\":\"N\"}");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/crono/4.json", "w");
  Main.print("{\"on1\":\"N\",\"off1\":\"N\",\"on2\":\"N\",\"off2\":\"N\",\"on3\":\"N\",\"off3\":\"N\"}");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/crono/5.json", "w");
  Main.print("{\"on1\":\"N\",\"off1\":\"N\",\"on2\":\"N\",\"off2\":\"N\",\"on3\":\"N\",\"off3\":\"N\"}");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/crono/6.json", "w");
  Main.print("{\"on1\":\"N\",\"off1\":\"N\",\"on2\":\"N\",\"off2\":\"N\",\"on3\":\"N\",\"off3\":\"N\"}");
  Main.close();
  WiFi.disconnect(true);
}
