#include <Arduino.h>
int A;

void setup() {
  pinMode(2, OUTPUT); // Set pin 2 as output
  pinMode(3, INPUT); // Set pin 3 as input
  pinMode(4, INPUT); // Set pin 4 as input
  pinMode(5, INPUT); // Set pin 5 as input
}

void loop() {
  // Read the inputs from the pins
  int D3 = digitalRead(3); // Assuming you have connected the input D3 to pin 3
  int D2 = digitalRead(4); // Assuming you have connected the input D2 to pin 4
  int D1 = digitalRead(5); // Assuming you have connected the input D1 to pin 5
  
  // Calculate A based on inputs
  A = (!D3 && D2) || (!D3 && !D2);
  
  // Output A directly to pin 2
  digitalWrite(2, A );
  
  // Delay to make the output observable
  delay(500);
}
