

void check_hour() {
  if (timeClient.getSeconds() == 0) {
    if (timeClient.getMinutes() == 0) {
      String filetempo = "/crono/" + String(timeClient.getDay()) + ".json";
      Main = SPIFFS.open(filetempo, "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      Main.close();
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(ciaoF);
      String on1 = json ["on1"];
      String on2 = json ["on2"];
      String on3 = json ["on3"];
      String off1 = json ["off1"];
      String off2 = json ["off2"];
      String off3 = json ["off3"];

    
        if (on1 == String(timeClient.getHours())) {
          rele1_tick_on();

        }
        else if (on2 == String(timeClient.getHours())) {
          rele1_tick_on();

        }
        else if (on3 == String(timeClient.getHours())) {
          rele1_tick_on();

        }

      





      else if (off1 == String(timeClient.getHours())) {
        rele1_tick_off();

      }
      else if (off2 == String(timeClient.getHours())) {
        rele1_tick_off();

      }
      else if (off3 == String(timeClient.getHours())) {
        rele1_tick_off();

      }




    }
  }
}











void bootcheck() {

  String filetempo = "/crono/" + String(timeClient.getDay()) + ".json";
  Main = SPIFFS.open(filetempo, "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(ciaoF);
  String on1 = json ["on1"];
  String on2 = json ["on2"];
  String on3 = json ["on3"];
  String off1 = json ["off1"];
  String off2 = json ["off2"];
  String off3 = json ["off3"];

 
    if (on1 == String(timeClient.getHours())) {
      rele1_tick_on();

    }
    else if (on2 == String(timeClient.getHours())) {
      rele1_tick_on();
    }
    else if (on3 == String(timeClient.getHours())) {
      rele1_tick_on();

    }

  





  else if (off1 == String(timeClient.getHours())) {
    rele1_tick_off();

  }
  else if (off2 == String(timeClient.getHours())) {
    rele1_tick_off();

  }
  else if (off3 == String(timeClient.getHours())) {
    rele1_tick_off();
  }




}
