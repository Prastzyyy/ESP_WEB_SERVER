//web.cpp

#include "web.h"

String ptr;

String SendHTML(float nilaiSuhu,float nilaiKelembaban, String kondisiLED){ 
 String ptr = "<!DOCTYPE html> <html>\n"; 
 ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; 
 ptr +="<title>Proyek dengan ESP8266</title>\n"; 
 ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; }\n"; 
 ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n"; 
 ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n"; 
 ptr +="</style>\n"; 
 ptr +="</head>\n"; 
 ptr +="<body>\n"; 
 ptr +="<div id=\"identitas\">\n"; 
 ptr +="<h1>Prasetyo Ade Pamungkas</h1>\n"; 
 ptr +="<p>NIM: H1A021023 </p>"; 
 ptr +="<p>Jurusan Teknik Elektro FT Unsoed </p>"; 
 ptr +="</div>\n"; 

 ptr +="<div id=\"webpage\">\n"; 
 ptr +="<h1>Pembacaan suhu dan kelembaban</h1>\n"; 
 ptr +="<p>Suhu: "; 
 ptr +=nilaiSuhu; 
 ptr +=" <sup>o</sup>C</p>"; 
 ptr +="<p>Kelembaban: "; 
 ptr +=nilaiKelembaban; 
 ptr +=" %</p>"; 
 ptr +="<p>Kondisi LED : " + kondisiLED + "</p>"; 
 ptr +="</div>\n"; 
 ptr +="<div id=\"saklar\">\n"; 
 ptr +="<h1>Kendali LED</h1>\n"; 
 ptr +="<button onclick=\"controlLED('/led_hidup')\">ON</button>"; 
 ptr +="<button onclick=\"controlLED('/led_mati')\">OFF</button>"; 
 ptr +="</div>\n"; 

 ptr +="<script>\n";
 ptr +="function controlLED(endpoint) {\n";
 ptr +="  fetch(endpoint).then(response => response.text()).then(data => {\n";
 ptr +="    console.log(data);\n";
 ptr +="  });\n";
 ptr +="}\n";
 ptr +="setInterval(() => {\n";
 ptr +="  fetch('/data').then(res => res.json()).then(data => {\n";
 ptr +="    document.getElementById('webpage').innerHTML = `\n";
 ptr +="      <h1>Pembacaan suhu dan kelembaban</h1>\n";
 ptr +="      <p>Suhu: ${data.nilaiSuhu} <sup>o</sup>C</p>\n";
 ptr +="      <p>Kelembaban: ${data.nilaiKelembaban} %</p>\n";
 ptr +="      <p>Kondisi LED : ${data.kondisiLED}</p>`;\n";
 ptr +="  });\n";
 ptr +="}, 1000);\n";
 ptr +="</script>\n";
 
 ptr +="</body>\n"; 
 ptr +="</html>\n"; 
 return ptr; 
}
