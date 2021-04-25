
void relay2_sync() {
  if (pulse) {} {
    if (rele2S) {
      if (mode1 == 0) {

        digitalWrite(pin2, payloadON.toInt());
        if (led1 != 255) {
          digitalWrite(led1, ledON);
        }
      } else if (mode1 == 1) {
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
      } else if (mode1 == 1) {
        Serial.print(payloadOFF);
        if (led1 != 255) {
          digitalWrite(led1, ledOFF);
        }
      }

    }
  }
}

void rele2_tick() {
  if (rele2S) {
    if (mode1 == 0) {

      digitalWrite(pin2, payloadOFF.toInt());
      if (led1 != 255) {
        digitalWrite(led1, ledOFF);
      }
    } else if (mode1 == 1) {

      Serial.print(payloadOFF);

      if (led1 != 255) {
        digitalWrite(led1, ledOFF);
      }
    }
    rele2S = 0;
    EEPROM.write(301, rele2S);
    EEPROM.commit();
    MQTT_sync();

  } else {
    if (mode1 == 0) {
      if (pulse) {
        digitalWrite(pin2, payloadON.toInt());   rele2S = 1; MQTT_sync();
        if (led1 != 255) {
          digitalWrite(led1, ledON);
        }
        delay(200);
        digitalWrite(pin2, payloadOFF.toInt()); rele2S = 0; MQTT_sync();
        if (led1 != 255) {
          digitalWrite(led1, ledOFF);
        }
        return;
        return;
      } else {
        digitalWrite(pin2, payloadON.toInt());
        if (led1 != 255) {
          digitalWrite(led1, ledON);
        }
      }
    } else if (mode1 == 1) {
      Serial.print(payloadON);
    }
    rele2S = 1;
    EEPROM.write(301, rele2S);
    EEPROM.commit();
    MQTT_sync();
    //  PowerStateUpdateAlexa(deviceID, "ON");
    //  PowerStateUpdateGhome(deviceID, true);
  }
}







//specifico

void rele2_tick_on() {
  if (mode1 == 0) {

    if (pulse) {
      digitalWrite(pin2, payloadON.toInt());   rele2S = 1; MQTT_sync();
      if (led1 != 255) {
        digitalWrite(led1, ledON);
      }
      delay(200);
      digitalWrite(pin2, payloadOFF.toInt()); rele2S = 0; MQTT_sync();
      if (led1 != 255) {
        digitalWrite(led1, ledOFF);
      }
      return;
    } else {
      digitalWrite(pin2, payloadON.toInt());
      if (led1 != 255) {
        digitalWrite(led1, ledON);
      }
    }
  } else if (mode1 == 1) {
    Serial.print(payloadON);
  }
  rele2S = 1;
  EEPROM.write(301, rele2S);
  EEPROM.commit();
  MQTT_sync();

}

void rele2_tick_off() {
  if (mode1 == 0) {

    digitalWrite(pin2, payloadOFF.toInt());
    if (led1 != 255) {
      digitalWrite(led1, ledOFF);
    }
  } else if (mode1 == 1) {
    Serial.print(payloadOFF);
    if (led1 != 255) {
      digitalWrite(led1, ledOFF);
    }
  }
  rele2S = 0;
  EEPROM.write(301, rele2S);
  EEPROM.commit();
  MQTT_sync();

}
//2
