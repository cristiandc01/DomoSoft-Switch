HTTPClient http;



void normalset () {

  // version += "<br>Chip ID: " + ESP.getFlashChipId();



  if (mdns.begin("domosoftrelay", WiFi.localIP())) {
    MDNS.addService("http", "tcp", 80);
  }

  server.on("/", []() {
    if (username == "") {
      homeweb();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      homeweb();
    }
  });



  server.on("/rele1", []() {
    if (username == "") {
      rele1_tick();
      homeweb();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      rele1_tick();
      homeweb();
    }
  });




  server.on("/rele1/on", []() {
    if (username == "") {
      rele1_tick_on();
      homeweb();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      rele1_tick_on();
      homeweb();
    }
  });

  server.on("/rele1/off", []() {
    if (username == "") {
      rele1_tick_off();
      homeweb();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      rele1_tick_off();
      homeweb();
    }
  });




  server.on("/rele1status", []() {
    if (pin1 == 255) {
      server.send(200, "text/html", "disabled");
    } else {
      server.send(200, "text/html", String(rele1S));
    }


  });




  server.on("/network", []() {

    if (username == "") {
      netweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      netweb("");
    }

  });


  server.on("/setwifi", []() {
    if (username == "") {
      String qsid = server.arg("ssid");
      String qpass = server.arg("password");

      if (qsid.length() > 0 && qpass.length() > 0) {
        netweb("Ok, rete cambiata!<br>Mi connetto alla nuova rete...");
        delay(1000);
        WiFi.disconnect();
        WiFi.begin(qsid, qpass);




      } else {
        netweb("Errore, il nome rete non può essere vuoto");
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String qsid = server.arg("ssid");
      String qpass = server.arg("password");

      if (qsid.length() > 0 && qpass.length() > 0) {
        netweb("Ok, rete cambiata!<br>Mi connetto alla nuova rete...");
        delay(1000);
        WiFi.disconnect();
        WiFi.begin(qsid, qpass);



      } else {
        netweb("Errore, il nome rete non può essere vuoto");
      }
    }
  });


  server.on("/settings", []() {
    if (username == "") {
      setweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      setweb("");
    }
  });

  server.on("/config", []() {
    if (username == "") {
      confweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      confweb("");
    }

  });

  server.on("/confdata", []() {
    if (username == "") {

      String file = "/config/rele1.txt";
      Main = SPIFFS.open(file, "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      server.send(200, "text/html", ciaoF);
      Main.close();
      ciaoF = "";
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      String file = "/config/rele1.txt";
      Main = SPIFFS.open(file, "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      server.send(200, "text/html", ciaoF);
      Main.close();
      ciaoF = "";
    }
  });


  server.on("/setconf", []() {

    if (username == "") {
      String testo = server.arg("testo");


      String file = "/config/rele1.txt" ;
      Serial.println(file);
      Main = SPIFFS.open(file, "w");
      Main.print(testo);
      Main.close();
      Serial.println("ok");
      Main = SPIFFS.open("/config.html", "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      Main.close();


      server.send(200, "text/html", ciaoF + "<h3>Salvataggio avvenuto! Riavvio...");
      ciaoF = "";
      delay(800);
      ESP.restart();

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String testo = server.arg("testo");

      String file = "/config/rele1.txt" ;
      Serial.println(file);
      Main = SPIFFS.open(file, "w");
      Main.print(testo);
      Main.close();
      Serial.println("ok");
      Main = SPIFFS.open("/config.html", "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      Main.close();


      server.send(200, "text/html", ciaoF + "<h3>Salvataggio avvenuto! Riavvio... ");
      ciaoF = "";
      delay(800);
      ESP.restart();
    }

  });

  server.on("/config/download", []() {

    if (username == "") {

      String file = "/config/rele1.txt" ;

      SD_file_download(file, devname + "_conf");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String file = "/config/rele1.txt" ;

      SD_file_download(file, devname + "_conf");

    }

  });

  server.on("/time", []() {
    if (username == "") {
      timeweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      timeweb("");
    }

  });

  server.on("/infotime", []() {
    if (username == "") {

      server.send(200, "text/html", timeClient.getFormattedTime());


    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);


      server.send(200, "text/html", timeClient.getFormattedTime() );

    }



  });

  server.on("/infoday", []() {
    if (username == "") {

      server.send(200, "text/html", String(timeClient.getDay()));


    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);


      server.send(200, "text/html", String(timeClient.getDay()));

    }



  });

  server.on("/setime", []() {
    if (username == "") {
      String timezone = server.arg("timezone");
      String legale = server.arg("legale");
      int ora_finale = timezone.toInt() + legale.toInt();
      Serial.println(ora_finale);
      timeClient.setTimeOffset(ora_finale);
      Main = SPIFFS.open("/settings/time_correction", "w");
      Main.print(ora_finale);
      Main.close();
      timeweb("OK!");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String timezone = server.arg("timezone");
      String legale = server.arg("legale");
      int ora_finale = timezone.toInt() + legale.toInt();
      Serial.println(ora_finale);
      timeClient.setTimeOffset(ora_finale);
      Main = SPIFFS.open("/settings/time_correction", "w");
      Main.print(ora_finale);
      Main.close();
      timeweb("OK!");
    }



  });


  server.on("/cronoDay", []() {
    if (username == "") {
      String daysel = server.arg("day");
      String filetempo = "/crono/" + daysel + ".json";
      Main = SPIFFS.open(filetempo, "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      server.send(200, "text/html", ciaoF);
      Main.close();
      ciaoF = "";
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      String daysel = server.arg("day");
      String filetempo = "/crono/" + daysel + ".json";
      Main = SPIFFS.open(filetempo, "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      server.send(200, "text/html", ciaoF);
      Main.close();
      ciaoF = "";
    }
  });



  server.on("/crono", []() {

    if (username == "") {

      cronoweb();





    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);


      cronoweb();


    }

  });

  server.on("/crono/on", []() {

    if (username == "") {

      cronoweb();

      timeState = 1;
      EEPROM.write(311, timeState);
      EEPROM.commit();



    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);


      cronoweb();
      timeState = 1;
      EEPROM.write(311, timeState);
      EEPROM.commit();

    }

  });

  server.on("/cronoState", []() {
    if (username == "") {
      server.send(200, "text/html", String(timeState));
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      server.send(200, "text/html", String(timeState));
    }
  });


  server.on("/crono/off", []() {

    if (username == "") {

      cronoweb();


      timeState = 0;
      EEPROM.write(311, timeState);
      EEPROM.commit();


    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);


      cronoweb();

      timeState = 0;
      EEPROM.write(311, timeState);
      EEPROM.commit();

    }

  });



  server.on("/setTime", []() {

    if (username == "") {
      String giorno = server.arg("day"); String testo = server.arg("testo");


      String filetempo = "/crono/" + giorno + ".json" ;
      Serial.println(filetempo);
      Main = SPIFFS.open(filetempo, "w");
      Main.print(testo);
      Main.close();
      Serial.println("ok");
      Main = SPIFFS.open("/crono.html", "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      Main.close();


      server.send(200, "text/html", ciaoF + "<h3>Salvataggio avvenuto! ");
      ciaoF = "";
      delay(800);


    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String giorno = server.arg("day"); String testo = server.arg("testo");

      String filetempo = "/crono/" + giorno + ".json" ;

      Main = SPIFFS.open(filetempo, "w");
      Main.print(testo);
      Main.close();
      Main = SPIFFS.open("/set.html", "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      Main.close();


      server.send(200, "text/html", ciaoF + "<h3>Salvataggio avvenuto!");
      ciaoF = "";
      delay(800);

    }

  });

  server.on("/crono/download", []() {

    if (username == "") {
      String daysel = server.arg("day");
      String filetempo = "/crono/" + daysel + ".json";
      if (daysel == "0") {
        daysel = "Domenica";
      } else if (daysel == "1") {
        daysel = "Lunedì";
      } else if (daysel == "2") {
        daysel = "Martedì";
      } else if (daysel == "3") {
        daysel = "Mercoledì";
      } else if (daysel == "4") {
        daysel = "Giovedì";
      } else if (daysel == "5") {
        daysel = "Venerdì";
      } else if (daysel == "6") {
        daysel = "Sabato";
      }
      SD_file_download(filetempo, daysel);

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String daysel = server.arg("day");
      String filetempo = "/crono/" + daysel + ".json";
      if (daysel == "0") {
        daysel = "Domenica";
      } else if (daysel == "1") {
        daysel = "Lunedì";
      } else if (daysel == "2") {
        daysel = "Martedì";
      } else if (daysel == "3") {
        daysel = "Mercoledì";
      } else if (daysel == "4") {
        daysel = "Giovedì";
      } else if (daysel == "5") {
        daysel = "Venerdì";
      } else if (daysel == "6") {
        daysel = "Sabato";
      }
      SD_file_download(filetempo, daysel);

    }

  });


  server.on("/reset", []() {      //reset the system

    if (username == "") {
      server.send(200, "text/html", "<h2>Ripristino compleatato! Riavvio in corso...</h2>");

      HardReset();
      delay(1000);
      ESP.restart();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);
      server.send(200, "text/html", "<h2>Ripristino compleatato! Riavvio in corso...</h2>");

      HardReset();
      delay(1000);
      ESP.restart();
    }
  });

  server.on("/mqttconf", []() {

    if (username == "") {
      mqttweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      mqttweb("");
    }

  });

  server.on("/mqttconf/status", []() {
    if (username == "") {
      if (!mqtt_conf) {
        server.send(200, "text/html", "0");
      } else {
        if (client.connected()) {
          server.send(200, "text/html", "1");
        } else {
          server.send(200, "text/html", "2");
        }
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      if (!mqtt_conf) {
        server.send(200, "text/html", "0"  );
      } else {
        if (client.connected()) {
          server.send(200, "text/html", "1"  );
        } else {
          server.send(200, "text/html", "2" );
        }
      }
    }
  });









  server.on("/discovery", []() {
    if (username == "") {
      String prefix = server.arg("prefix");
      if (prefix == "") {
      } else {
        hassio_prefix = prefix;

        Main = SPIFFS.open("/discovery/prefix", "r");
        Main.print(prefix);
        Main.close();
      }
      discover();
      mqttweb("<h3>Comando inviato!</h3>");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      String prefix = server.arg("prefix");
      if (prefix == "") {
      } else {
        hassio_prefix = prefix;

        Main = SPIFFS.open("/discovery/prefix", "r");
        Main.print(prefix);
        Main.close();
      }
      discover();
      mqttweb("<h3>Comando inviato!</h3>");

    }
  });


  server.on("/discovery/delete", []() {
    if (username == "") {
      String prefix = server.arg("prefix");
      if (prefix == "") {
      } else {
        hassio_prefix = prefix;
      }
      deleteConfig();
      mqttweb("<h3>Comando inviato!</h3>");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      String prefix = server.arg("prefix");
      if (prefix == "") {
      } else {
        hassio_prefix = prefix;
      }
      deleteConfig();
      mqttweb("<h3>Comando inviato!</h3>");

    }
  });


  server.on("/info/devname", []() {
    if (username == "") {

      server.send(200, "text/html", devname);


    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);


      server.send(200, "text/html", devname );

    }


  });

  server.on("/MQhost", []() {

    if (username == "") {
      mqtt_server = server.arg("iphost");

      if (mqtt_server.length() >= 16) {
        mqttweb("<h3>Errore!<br>Indirizzo troppo lungo</h3>");
      } else {
        for (int i = 108; i < 123; ++i) {
          EEPROM.write(i, 0);
        }
        for (int i = 0; i < mqtt_server.length(); ++i)
        {
          EEPROM.write(108 + i, mqtt_server[i]);
          //Serial.print("Wrote: ");
          //Serial.println(mqtt_server[i]);
        }

        EEPROM.commit();
        mqttweb("<h3>Salvataggio avvenuto</h3>");
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      mqtt_server = server.arg("iphost");

      if (mqtt_server.length() >= 16) {
        mqttweb("<h3>Errore!<br>Indirizzo troppo lungo</h3>");
      } else {
        for (int i = 108; i < 123; ++i) {
          EEPROM.write(i, 0);
        }
        for (int i = 0; i < mqtt_server.length(); ++i)
        {
          EEPROM.write(108 + i, mqtt_server[i]);
          //Serial.print("Wrote: ");
          //Serial.println(mqtt_server[i]);
        }

        EEPROM.commit();
        mqttweb("<h3>Salvataggio avvenuto</h3>");
      }
    }

  });

  server.on("/mqttstat", []() {

    if (username == "") {
      String aroma = server.arg("q");

      if (aroma == "on") {

        mqtt_conf = 1;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();
      } else {

        mqtt_conf = 0;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();




      }
      mqttweb("<h3>Salvataggio avvenuto, <br>Riavvio in corso...</h3>");
      delay(800);

      ESP.restart();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String aroma = server.arg("q");

      if (aroma == "on") {

        mqtt_conf = 1;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();
      } else {

        mqtt_conf = 0;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();




      }
      mqttweb("<h3>Salvataggio avvenuto, <br>Riavvio in corso...</h3>");
      delay(800);
      ESP.restart();
    }

  });


  server.on("/mqttreboot", []() {
    if (username == "") {
      mqtt_conf = 1;
      E_MQ = 0;
      Main = SPIFFS.open("/home.html", "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      Main.close();
      server.send(200, "text/html", ciaoF);
      ciaoF = "";
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      mqtt_conf = 1;
      E_MQ = 0;
      Main = SPIFFS.open("/home.html", "r");
      String ciaoF;
      while (Main.available()) {
        ciaoF += char(Main.read());
      }
      Main.close();
      server.send(200, "text/html", ciaoF);
      ciaoF = "";
    }
  });



  server.on("/MQuser", []() {        //set the mqtt user and password

    if (username == "") {
      mqtt_user = server.arg("username");
      mqtt_password = server.arg("pwd");

      if (mqtt_user.length() >= 21) {
        mqttweb("<h3>Errore!<br>nome utente troppo lungo (Max 20 caratteri)</h3>");
      } else {

        if (mqtt_password.length() >= 21) {
          mqttweb("<h3>Errore!<br>password troppo lunga (Max 20 caratteri)</h3>");
        } else {
          for (int i = 124; i < 144; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_user.length(); ++i)
          {
            EEPROM.write(124 + i, mqtt_user[i]);
            //Serial.print("Wrote: ");
            //  Serial.println(mqtt_user[i]);
          }
          for (int i = 145; i < 165; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_password.length(); ++i)
          {
            EEPROM.write(145 + i, mqtt_password[i]);
            //Serial.print("Wrote: ");
            //Serial.println(mqtt_password[i]);
          }

          EEPROM.commit();
          mqttweb("<h3>Salvataggio avvenuto..</h3>");
        }
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      mqtt_user = server.arg("username");
      mqtt_password = server.arg("pwd");

      if (mqtt_user.length() >= 21) {
        mqttweb("<h3>Errore!<br>nome utente troppo lungo (Max 20 caratteri)</h3>");
      } else {

        if (mqtt_password.length() >= 21) {
          mqttweb("<h3>Errore!<br>password troppo lunga (Max 20 caratteri)</h3>");
        } else {
          for (int i = 124; i < 144; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_user.length(); ++i)
          {
            EEPROM.write(124 + i, mqtt_user[i]);
            //Serial.print("Wrote: ");
            //  Serial.println(mqtt_user[i]);
          }
          for (int i = 145; i < 165; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_password.length(); ++i)
          {
            EEPROM.write(145 + i, mqtt_password[i]);
            //Serial.print("Wrote: ");
            //Serial.println(mqtt_password[i]);
          }

          EEPROM.commit();
          mqttweb("<h3>Salvataggio avvenuto..</h3>");
        }
      }
    }

  });


  server.on("/setName", []() {

    if (username == "") {
      String nome = server.arg("name");




      Main = SPIFFS.open("/device_name", "w");
      Main.print(nome);
      Main.close();

      setweb("<h3>Salvataggio avvenuto!</h3>");
      delay(800);
      ESP.restart();

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String nome = server.arg("name");




      Main = SPIFFS.open("/device_name", "w");
      Main.print(nome);
      Main.close();

      setweb("<h3>Salvataggio avvenuto!</h3>");
      delay(800);
      ESP.restart();
    }

  });

  server.on("/setBaud", []() {

    if (username == "") {
      String baud = server.arg("baud");

      Main = SPIFFS.open("/settings/serial_baud", "w");
      Main.print(baud);
      Main.close();

      setweb("<h3>Salvataggio avvenuto!<br>Riavvio...</h3>");
      delay(800);
      ESP.restart();

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String baud = server.arg("baud");

      Main = SPIFFS.open("/settings/serial_baud", "w");
      Main.print(baud);
      Main.close();

      setweb("<h3>Salvataggio avvenuto!<br>Riavvio...</h3>");
      delay(800);
      ESP.restart();
    }

  });

  server.on("/security", []() {      //print the security page
    if (username == "") {
      secweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);
      secweb("");
    }
  });

  server.on("/protect", []() {       //this part set a password to system http

    if (username == "") {
      username = "";
      password = "";
      username = server.arg("username");
      password = server.arg("password");
      if (username.length() >= 14) {
        secweb("<h3>Errore!<br>Username troppo lungo max 14</h3>");
      } else {
        if (password.length() >= 18) {
          secweb("<h3>Errore!<br>Password troppo lunga max 18</h3>");
        } else {
          for (int i = 166; i < 180; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < username.length(); ++i)
          {
            EEPROM.write(166 + i, username[i]);
          }

          for (int i = 181; i < 199; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < password.length(); ++i)
          {
            EEPROM.write(181 + i, password[i]);
          }

          EEPROM.commit();
          secweb("<h3>Salvataggio avvenuto<br></h3>");

        }
      }



    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);
      username = "";
      password = "";
      username = server.arg("username");
      password = server.arg("password");
      if (username.length() >= 14) {
        secweb("<h3>Errore!<br>Username troppo lungo max 14</h3>");
      } else {
        if (password.length() >= 18) {
          secweb("<h3>Errore!<br>Password troppo lunga max 18</h3>");
        } else {
          for (int i = 166; i < 180; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < username.length(); ++i)
          {
            EEPROM.write(166 + i, username[i]);
          }

          for (int i = 181; i < 199; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < password.length(); ++i)
          {
            EEPROM.write(181 + i, password[i]);
          }

          EEPROM.commit();
          secweb("<h3>Salvataggio avvenuto<br></h3>");

        }
      }
    }

  });

  server.on("/info", []() {
    if (username == "") {
      infoweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      infoweb("");
    }
  });

  server.on("/macadd", []() {
    if (username == "") {
      server.send(200, "text/html", String(WiFi.macAddress()));
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      server.send(200, "text/html", String(WiFi.macAddress()));
    }
  });

  if (username == "") {
    httpUpdater.setup(&server, "/settings/firmware");
  } else {
    httpUpdater.setup(&server, "/settings/firmware", username, password);
  }
  server.begin();
  //Serial.println("HTTP server started");

}
