void verifica_pulsante() {
  if (digitalRead(in1) == payloadIN) {
    rele1_tick();
    delay(200);
  }
}
void verifica_pulsante2() {
  if (inmode2 == 2) {
    if (digitalRead(in2) != preIN2) {
      preIN2 = digitalRead(in2);
      rele1_tick();
      EEPROM.write(301, preIN2);
      EEPROM.commit();
      delay(200);
    }
  } else {
    if (digitalRead(in2) == payloadIN2) {
      rele1_tick();
      delay(200);
    }
  }
}
