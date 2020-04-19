uint8_t r1_on[] = {0xA0, 0x01, 0x01, 0xA2};
uint8_t r1_off[] = {0xA0, 0x01, 0x00, 0xA1};
uint8_t r2_on[] = {0xA0, 0x02, 0x01, 0xA3};
uint8_t r2_off[] = {0xA0, 0x02, 0x00, 0xA2};
//for (byte i = 0; i < sizeof(r1_on); i++)(Serial.write(r1_on[i]));
void relay_sync() {
  if (pulse) {} {
    if (rele1S) {
      if (mode1 == 0) {

        digitalWrite(pin1, payloadON.toInt());
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
        digitalWrite(pin1, payloadOFF.toInt());
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

void rele1_tick() {
  if (rele1S) {
    if (mode1 == 0) {

      digitalWrite(pin1, payloadOFF.toInt());
      if (led1 != 255) {
        digitalWrite(led1, ledOFF);
      }
    } else if (mode1 == 1) {

      Serial.print(payloadOFF);

      if (led1 != 255) {
        digitalWrite(led1, ledOFF);
      }
    }
    rele1S = 0;
    EEPROM.write(300, rele1S);
    EEPROM.commit();
    MQTT_sync();
    //   PowerStateUpdateAlexa(deviceID, "OFF");
    //   PowerStateUpdateGhome(deviceID, false);
  } else {
    if (mode1 == 0) {
      if (pulse) {
        digitalWrite(pin1, payloadON.toInt());   rele1S = 1; MQTT_sync();
        if (led1 != 255) {
          digitalWrite(led1, ledON);
        }
        delay(200);
        digitalWrite(pin1, payloadOFF.toInt()); rele1S = 0; MQTT_sync();
        if (led1 != 255) {
          digitalWrite(led1, ledOFF);
        }
        return;
        return;
      } else {
        digitalWrite(pin1, payloadON.toInt());
        if (led1 != 255) {
          digitalWrite(led1, ledON);
        }
      }
    } else if (mode1 == 1) {
      Serial.print(payloadON);
    }
    rele1S = 1;
    EEPROM.write(300, rele1S);
    EEPROM.commit();
    MQTT_sync();
    //  PowerStateUpdateAlexa(deviceID, "ON");
    //  PowerStateUpdateGhome(deviceID, true);
  }
}







//specifico

void rele1_tick_on() {
  if (mode1 == 0) {

    if (pulse) {
      digitalWrite(pin1, payloadON.toInt());   rele1S = 1; MQTT_sync();
      if (led1 != 255) {
        digitalWrite(led1, ledON);
      }
      delay(200);
      digitalWrite(pin1, payloadOFF.toInt()); rele1S = 0; MQTT_sync();
      if (led1 != 255) {
        digitalWrite(led1, ledOFF);
      }
      return;
    } else {
      digitalWrite(pin1, payloadON.toInt());
      if (led1 != 255) {
        digitalWrite(led1, ledON);
      }
    }
  } else if (mode1 == 1) {
    Serial.print(payloadON);
  }
  rele1S = 1;
  EEPROM.write(300, rele1S);
  EEPROM.commit();
  MQTT_sync();
  // PowerStateUpdateAlexa(deviceID, "ON");
  // PowerStateUpdateGhome(deviceID, true);
}

void rele1_tick_off() {
  if (mode1 == 0) {

    digitalWrite(pin1, payloadOFF.toInt());
    if (led1 != 255) {
      digitalWrite(led1, ledOFF);
    }
  } else if (mode1 == 1) {
    Serial.print(payloadOFF);
    if (led1 != 255) {
      digitalWrite(led1, ledOFF);
    }
  }
  rele1S = 0;
  EEPROM.write(300, rele1S);
  EEPROM.commit();
  MQTT_sync();
  // PowerStateUpdateAlexa(deviceID, "OFF");
  //PowerStateUpdateGhome(deviceID, false);
}
//2
