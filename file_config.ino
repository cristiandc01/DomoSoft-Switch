void readConf() {
  Serial.println("--- Welcome to SmartReader configuration ---");
  Main = SPIFFS.open("/config/rele1.txt", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Serial.print("Loaded: ");
  Serial.println(ciaoF);
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(ciaoF);
  String pin = json ["pin"];
  String mode = json ["mode"];
  String typeS = json ["type"];
  String pulseS = json ["pulse"];
  String payload1 = json ["payloadON"];
  String payload2 = json ["payloadOFF"];
  String input1 = json ["in1"];
  String payIN = json ["payloadIN1"];
  String bstate = json ["bootState"];
  String input2 = json ["in2"];
  String payIN2 = json ["payloadIN2"];
  String INMODE2 = json ["IN2mode"];
  String LED = json ["led1"];
  String LEDMOD = json ["ledMode"];
  payloadOFF = payload2;
  payloadON = payload1;
  if (pin == "false") {
    pin1 = 255;
  } else {
    pin1 = pin.toInt();

  }
  if (LED == "false") {
    led1 = 255;
  } else {
    led1 = LED.toInt();
    pinMode(led1, OUTPUT);
  }
  if (LEDMOD == "normal") {
    ledON = 1;
    ledOFF = 0;
  } else if (LEDMOD == "inverted") {
    ledON = 0;
    ledOFF = 1;

  }
  payloadIN = payIN.toInt();
  if (input1 == "false") {
    in1 = 255;
  } else {
    in1 = input1.toInt();
    if (payloadIN == 0) {
      pinMode(in1, INPUT_PULLUP);
    }
  }

  mode1 = mode.toInt();
  type = typeS;
  if (pulseS == "true") {
    pulse = true;
  } else {
    pulse = false;
  }
  if (bstate != "false") {
    bootState = bstate.toInt();
  } else {
    bootState = 255;
  }
  payloadIN2 = payIN2.toInt();
  if (input2 == "false") {
    in2 = 255;
  } else {
    in2 = input2.toInt();
    if (payloadIN2 == 0) {
      pinMode(in2, INPUT_PULLUP);
    }
  }
  if (INMODE2 == "dual") {
    inmode2 = 2;
  } else {
    inmode2 = 1;
  }
  if (mode1 == 0) {
    pinMode(pin1, OUTPUT);
  }

  Serial.println("--- Closing SmartReader configuration ---");
}
