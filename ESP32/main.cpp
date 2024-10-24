//----------------------Skeleton Code--------------------// 
#include <WiFi.h> 
#include <WiFiUdp.h> 
#include <ArduinoOTA.h> 
int input0 = 19;  // Input 0 (will be inverted) 
int input1 = 22;  // Input 1 (direct) 
int selectS = 21; // Selection line 
int ledPin = 2;  // LED to display MUX output 
//    Can be client or even host   // 
#ifndef STASSID 
#define STASSID "6t"  // Replace with your network credentials 
#define STAPSK  "12345678" 
#endif 
 
const char* ssid = STASSID; 
const char* password = STAPSK; 
 
 
void OTAsetup() { 
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); 
  while (WiFi.waitForConnectResult() != WL_CONNECTED) { 
    delay(20000); 
    ESP.restart(); 
  } 
  ArduinoOTA.begin(); 
} 
 
void OTAloop() { 
  ArduinoOTA.handle(); 
} 
 
//-------------------------------------------------------// 
 
void setup(){ 
  OTAsetup(); 
 
  //-------------------// 
  // Custom setup code // 
  //-------------------// 
 pinMode(input0, INPUT);   // Input 0 pin 
  pinMode(input1, INPUT);   // Input 1 pin 
  pinMode(selectS, INPUT);  // Selection line pin 
  pinMode(ledPin, OUTPUT);  // LED pin for output 
 
} 
 
void loop() { 
  OTAloop(); 
  delay(10);  // If no custom loop code ensure to have a delay in loop 
  //-------------------// 
  // Custom loop code  // 
  //-------------------// 
 int val0 = digitalRead(input0);   // Read Input 0 
  int val1 = digitalRead(input1);   // Read Input 1 
  int select = digitalRead(selectS); // Read Selection line 
 
  // Invert input 0 
  int inverted_val0 = !val0; 
 
  // MUX logic 
  int mux_output; 
  if (select == HIGH) { 
    // If S = 1, select Input 1 
    mux_output = val1; 
  } else { 
    // If S = 0, select inverted Input 0 
    mux_output = inverted_val0; 
  } 
 
  // Control the LED based on MUX output 
  if (mux_output == HIGH) { 
    digitalWrite(ledPin, HIGH); // Turn on the LED if MUX output is 1 
  } else { 
    digitalWrite(ledPin, LOW);  // Turn off the LED if MUX output is 0 
  } 
 delay(100); 
}
