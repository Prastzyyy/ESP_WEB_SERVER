#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#include "web.h"

const char* ssid = "Prastzy.net";
const char* password = "123456781";

ESP8266WebServer server(80);

const int led = 2;  

float nilaiKelembaban;
float nilaiSuhu;
String kondisiLED;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", SendHTML(nilaiSuhu, nilaiKelembaban, kondisiLED));
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
  message += " " + server.argName(i) + ": " + server.arg(i)+ "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void handleData() {
  Serial.println("Endpoint /data accessed");
  String json = "{";
  json += "\"nilaiSuhu\":" + String(nilaiSuhu) + ",";
  json += "\"nilaiKelembaban\":" + String(nilaiKelembaban) + ",";
  json += "\"kondisiLED\":\"" + kondisiLED + "\"";
  json += "}";
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(200, "application/json", json);
}

void setup(void){
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println(" ");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) {
  Serial.println("MDNS responder started");
  }
  IPAddress ip = WiFi.localIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

//====================================================
  server.on("/", [](){
    server.send(200, "text/html", SendHTML(nilaiSuhu, nilaiKelembaban, kondisiLED)); 
  });
  
  server.on("/led_hidup", [](){
    digitalWrite(led, LOW);
    Serial.println("");
    Serial.print("Led Menyala"); //text pada serial monitor
    kondisiLED = "Menyala";
    server.send(200, "text/html", SendHTML(nilaiSuhu, nilaiKelembaban, kondisiLED)); 
  });
  
  server.on("/led_mati", [](){
    digitalWrite(led, HIGH);
    Serial.println("");
    Serial.print("Led Mati");
    kondisiLED = "Padam";
    server.send(200, "text/html", SendHTML(nilaiSuhu, nilaiKelembaban, kondisiLED));
  });
//====================================================
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop(void){
  server.handleClient();
  nilaiSuhu = random (60, 91);
  nilaiKelembaban = random (25, 36);
  delay (1000);
}
