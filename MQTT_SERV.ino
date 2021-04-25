

bool mqtt_conn() {


  if (client.connect(String(devname).c_str(), String(mqtt_user).c_str(), String(mqtt_password).c_str(), wil_topic.c_str(), 1, true, "offline")) {
    if (!discovered) {
      client.publish(wil_topic.c_str(), "online", true);
    }
    //Serial.println("connected");
    client.setCallback(callback);
    client.subscribe(rele1_control_topic.c_str());
    if (pin2 != 255) {
      client.subscribe(rele2_control_topic.c_str());
    }

    MQTT_sync();
  }
  return client.connected();
}


void callback(String topic, byte* payload, unsigned int length) {
  String messaggio;
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.println("] ");

  for (int i = 0; i < length; i++) {

    messaggio += (char)payload[i];
  }
  delay(100);
  if (topic == rele1_control_topic) {

    if (messaggio == "1") {
      rele1_tick_on();
    } else {
      rele1_tick_off();
    }

    delay(1000);
  }


  else  if (topic == rele2_control_topic) {
    if (pin2 != 255) {
      if (messaggio == "1") {
        rele2_tick_on();
      } else {
        rele2_tick_off();
      }

      delay(1000);
    }
  }



}

void MQTT_sync() {
  client.publish(rele1_status_topic.c_str(), String(rele1S).c_str(), true);
  if (pin2 != 255) {
    client.publish(rele2_status_topic.c_str(), String(rele2S).c_str(), true);
  }


}
