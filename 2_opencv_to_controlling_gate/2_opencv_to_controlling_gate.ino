

// Include username and password
#include "credentials.h"
#include "root.h"
#include "parameters.h"

// Import another 
#include <WiFi.h>
#include <ArduinoJson.h> // For JSON responses
#include <WebServer.h> // untuk server

// Membuat web server object
WebServer server(80);

// flagging untuk menyalakan lampu
int led = 12;  
int isOn = 0;

void preSetupModule(){
  pinMode(led, OUTPUT);
}

void setup() {

  preSetupModule();
  
  // serial bauth, ada 115200, untuk debuging
  Serial.begin(115200);

  // Pasang usernamd and passwd
  WiFi.begin(ssid, passwd);

  // Check apakah terkoneksi atau tidak
  while (WiFi.status() != WL_CONNECTED){
    // always loop jika tidak koneksi
    delay(1000); // delay satu detik untuk setiap request login
    Serial.println("Bismillah, koneksi.....");
  }
  Serial.println("Alhamdulillah terkoneksi....");
  Serial.println(WiFi.localIP());


  // setup endpoint
  server.on("/", endpoint_awal);

  server.on("/open_gate", endpoint_open_the_gate);
  server.on("/close_gate", endpoint_close_the_gate);
  

  // mulai server
  server.begin();
  Serial.println("Server is started");
}

void endpoint_awal(){
  Serial.println("Take me home");
  isOn = 0;
  server.send (200, "text/html", getHomePage());
  
}

void endpoint_open_the_gate(){
  // here is to open the gate
  if (server.method() != HTTP_POST){
    // Kirim ke server method is not alloed
    server.send(405,"aplication/json",error_method);
    
    // retun, do nothing
    return;
  }

  // turnon the module
  isOn = 255;
  
  // baca jsonnya
  String json_raw = server.arg("plain");
  Serial.println("Data is received");
  Serial.println(json_raw);

  server.send(200,"aplication/json",status_gating);
}

void endpoint_close_the_gate(){
  // here is to open the gate
  if (server.method() != HTTP_POST){
    // Kirim ke server method is not alloed
    server.send(405,"aplication/json",error_method);
    
    // retun, do nothing
    return;
  }

  // turnon the module
  isOn = 0;
  
  // baca jsonnya
  String json_raw = server.arg("plain");
  Serial.println("Data is received");
  Serial.println(json_raw);

  server.send(200,"aplication/json",status_gating);
}

void loop() {
  // untuk menanganin input dari cleint
  server.handleClient();

  // untuk menangani output module
  analogWrite(led, isOn);

}
