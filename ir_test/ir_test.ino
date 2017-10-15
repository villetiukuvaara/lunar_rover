/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

 #include <IRremote.h>

 // IR Codes
#define IR_0      0xFF9867
#define IR_1      0xFFA25D
#define IR_2      0xFF629D
#define IR_3      0xFFE21D
#define IR_4      0xFF22DD
#define IR_5      0xFF02FD
#define IR_6      0xFFC23D
#define IR_7      0xFFE01F
#define IR_8      0xFFA857
#define IR_9      0xFF906F
#define IR_UP     0xFF18E7
#define IR_DOWN   0xFF4AB5
#define IR_LEFT   0xFF10EF
#define IR_RIGHT  0xFF5AA5
#define IR_OK     0xFF38C7
#define IR_STAR   0xFF6897
#define IR_POUND  0xFFB04F
#define IR_REPEAT 0xFFFFFFFF

int RECV_PIN = A2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    switch(results.value)
    {
      case IR_UP:
        Serial.println("UP");
        break;
      case IR_DOWN:
        Serial.println("DOWN");
        break;
      case IR_LEFT:
        Serial.println("LEFT");
        break;
      case IR_RIGHT:
        Serial.println("RIGHT");
        break;
    }
  }
  delay(100);
}
