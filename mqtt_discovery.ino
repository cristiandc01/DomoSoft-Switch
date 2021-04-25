byte mac[6];
String macadd;

void discover() {
  WiFi.macAddress(mac);
  macadd = mac[0] + mac[1] + mac[2] + mac[3] + mac[4] + mac[5];
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  if (pin2 != 255) {
    json["name"] = devname + " 1";
  } else {
    json["name"] = devname;
  }
  json["availability_topic"] = wil_topic;
  json["command_topic"] = rele1_control_topic;
  json["state_topic"] = rele1_status_topic;
  if (type == "lock") {
    json["payload_lock"] = "0";
    json["payload_unlock"] = "1";
    json["state_locked"] = "0";
    json["state_unlocked"] = "1";
  } else {
    json["payload_off"] = "0";
    json["payload_on"] = "1";
  }
  String IDflash = String(macadd);
  json["uniq_id"] = IDflash + "_1";
  JsonObject& dev = json.createNestedObject("dev");
  JsonArray& dev_ids = dev.createNestedArray("ids");
  dev_ids.add(IDflash);
  if (pin2 == 255) {
    dev["mf"] = "DC Domotics";
    dev["mdl"] = "DomoSwitch 2.0";
    dev["name"] = devname;
    dev["sw"] = "DomoSoft 4.3";
  }
  String topic = hassio_prefix + "/" + type + "/domosoft4/" + macadd  + "_1" + "/config";
  char JSONmessageBuffer[600];
  json.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  if (pin2 != 255) {
    discover2();
  }

  client.publish(topic.c_str(), JSONmessageBuffer, true);
  client.publish(wil_topic.c_str(), "online", true);
  discovered = 1;
  EEPROM.write(201, discovered);
  EEPROM.commit();
}



void discover2() {

  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["name"] = devname + " 2";
  json["availability_topic"] = wil_topic;
  json["command_topic"] = rele2_control_topic;
  json["state_topic"] = rele2_status_topic;
  if (type == "lock") {
    json["payload_lock"] = "0";
    json["payload_unlock"] = "1";
    json["state_locked"] = "0";
    json["state_unlocked"] = "1";
  } else {
    json["payload_off"] = "0";
    json["payload_on"] = "1";
  }

  String IDflash = String(macadd);
  json["uniq_id"] = IDflash + "_2";

  JsonObject& dev = json.createNestedObject("dev");
  JsonArray& dev_ids = dev.createNestedArray("ids");
  dev_ids.add(IDflash);

  dev["mf"] = "DC Domotics";
  dev["mdl"] = "DomoSwitch 2.0";
  dev["name"] = devname;
  dev["sw"] = "DomoSoft 4.3";

  String topic = hassio_prefix + "/" + type + "/domosoft4/" + macadd + "_2" + "/config";
  char JSONmessageBuffer[512];
  json.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  client.publish(topic.c_str(), JSONmessageBuffer, true);
  client.publish(wil_topic.c_str(), "online", true);
}






void deleteConfig() {
  WiFi.macAddress(mac);
  macadd = mac[0] + mac[1] + mac[2] + mac[3] + mac[4] + mac[5];
  String topic = hassio_prefix + "/switch/domosoft4/" + macadd  + "_1" + "/config";
  client.publish(topic.c_str(), "", true);
  topic = hassio_prefix + "/lock/domosoft4/" + macadd  + "_1" + "/config";
  client.publish(topic.c_str(), "", true);
  topic = hassio_prefix + "/light/domosoft4/" + macadd + "_1" + "/config";
  client.publish(topic.c_str(), "", true);
  if (pin2 != 255) {
    topic = hassio_prefix + "/switch/domosoft4/" + macadd  + "_2" + "/config";
    client.publish(topic.c_str(), "", true);
    topic = hassio_prefix + "/lock/domosoft4/" + macadd  + "_2" + "/config";
    client.publish(topic.c_str(), "", true);
    topic = hassio_prefix + "/light/domosoft4/" + macadd + "_2" + "/config";
    client.publish(topic.c_str(), "", true);
  }
  discovered = 0;
  EEPROM.write(201, discovered);
  EEPROM.commit();
}


//  String message = "{'name':'" + devname + "','command_topic':'" + rele1_control_topic + "','state_topic':'" + rele1_status_topic + "','payload_off':'0','payload_on':'1'}";
