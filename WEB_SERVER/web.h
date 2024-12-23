//web.h

#ifndef WEB_H
#define WEB_H
#include <Arduino.h>

extern String ptr;

String SendHTML(float nilaiSuhu,float nilaiKelembaban, String kondisiLED);

#endif
