// Pin definitions
const int xPin = 2;       // Input for X
const int yPin = 3;       // Input for Y
const int qPin = 4;       // Input for Q (Flip-Flop's Q output from Pin 3 of 7474)
const int dPin = 5;       // Output to D input of the Flip-Flop (Pin 1 of 7474)
const int clkPin = 6;     // Clock signal to Flip-Flop (Pin 5 of 7474)
const int ledPin = 8;     // LED to display Q output

void setup() {
  // Set pin modes
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(qPin, INPUT);    // Q output from the flip-flop
  pinMode(dPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  pinMode(ledPin, OUTPUT); // LED output

  // Initialize clock to LOW
  digitalWrite(clkPin, LOW);
}

void loop() {
  // Read inputs
  bool X = digitalRead(xPin);
  bool Y = digitalRead(yPin);
  bool Q = digitalRead(qPin);   // Read Q from the 7474's output pin

  // Calculate S = X ⊕ Y ⊕ Q
  bool S = X ^ Y ^ Q;

  // Set the D input of the Flip-Flop
  digitalWrite(dPin, S);

  // Generate a clock pulse to trigger the Flip-Flop
  digitalWrite(clkPin, HIGH);   // Rising edge
  delay(100);                    // Short delay to ensure clock is stable
  digitalWrite(clkPin, LOW);    // Falling edge

  // Display the state of Q using the LED
  digitalWrite(ledPin, Q);      // Turn LED on if Q is HIGH, off if Q is LOW

  // Add a small delay to control the clock speed (optional)
  delay(1000);
}
