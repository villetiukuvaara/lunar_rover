/*
 * Lunar rover
 * Controls a robot with two DC motors and an IR remote
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

// Motor things
#define MOTOR0 (uint8_t)0x00
#define MOTOR1 (uint8_t)0x01

typedef struct
{
  uint8_t id;
  bool brake = false;
  bool fwd = true;
  uint8_t speed = 0;
  float multiplier = 1;
} motor_t;

motor_t motor_0, motor_1;

void motor_update(motor_t motor)
{
  if(motor.id == MOTOR0)
  {
    digitalWrite(12, motor_0.fwd ? HIGH : LOW); // Establishes direction of Channel A
    digitalWrite(9, motor_0.brake ? HIGH : LOW);   // Brake for Channel A
    //uint8_t s = motor_0.speed ;//* motor_0.multiplier;
    //Serial.print("Speed = ");
    Serial.println(s);
    analogWrite(3, s);   // Spins the motor on Channel A
  }
  else if(motor.id == MOTOR1)
  {
    digitalWrite(13, motor_1.fwd ? HIGH : LOW);  // Establishes direction of Channel B
    digitalWrite(8, motor_1.brake ? HIGH : LOW);   // Brake for Channel B
    uint8_t s = motor_1.speed ;//* motor_1.multiplier;
    analogWrite(11, s);    // Spins the motor on Channel B
  }
}

void motor_update()
{
  motor_update(motor_0);
  motor_update(motor_1);
}

void motor_init()
{
  motor_0.id = MOTOR0;
  motor_1.id = MOTOR1;
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
}

void ir_release_btn()
{
  Serial.print("Waiting for button release... ");
  do
  {
    irrecv.resume();
    delay(140);
  } while(irrecv.decode(&results));// && results.value != IR_REPEAT)
  Serial.println("button released");
}

void setup()
{
  Serial.begin(115200);

  // Init motors
  Serial.println("Enabling motors");
  motor_init();
  motor_update();
  Serial.println("Enabled motors");

  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop()
{
  if (irrecv.decode(&results))
  {
    //Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    switch(results.value)
    {
      case IR_1:
        motor_0.multiplier = 0.33;
        motor_1.multiplier = 0.33;
        //delay(100);
        ir_release_btn();
        Serial.println("Set multiplier 1");
        break;
      case IR_2:
        motor_0.multiplier = 0.67;
        motor_1.multiplier = 0.67;
        //delay(100);
        ir_release_btn();
        Serial.println("Set multiplier 2");
        break;
      case IR_3:
        motor_0.multiplier = 1;
        motor_1.multiplier = 1;
        //delay(100);
        ir_release_btn();
        Serial.println("Set multiplier 3");
        break;
        
      case IR_UP:
        Serial.println("Forward");
        motor_0.speed = 255;
        motor_0.fwd = true;
        motor_0.brake = false;
        motor_1.speed = 255;
        motor_1.fwd = true;
        motor_1.brake = false;
        motor_update();
        
        ir_release_btn();
        motor_0.brake = true;
        motor_1.brake = true;
        motor_update();

        break;

      case IR_DOWN:
        Serial.println("Back");
        motor_0.speed = 255;
        motor_0.fwd = false;
        motor_0.brake = false;
        motor_1.speed = 255;
        motor_1.fwd = false;
        motor_1.brake = false;
        motor_update();
        
        ir_release_btn();
        motor_0.brake = true;
        motor_1.brake = true;
        motor_update();

        break;
      
      case IR_LEFT:
        Serial.println("Left");
        motor_0.speed = 170;
        motor_0.fwd = true;
        motor_0.brake = false;
        motor_1.speed = 255;
        motor_1.fwd = true;
        motor_1.brake = false;
        motor_update();
        
        ir_release_btn();
        motor_0.brake = true;
        motor_1.brake = true;
        motor_update();

        break;
        
      case IR_RIGHT:
        Serial.println("Right");
        motor_0.speed = 255;
        motor_0.fwd = true;
        motor_0.brake = false;
        motor_1.speed = 170;
        motor_1.fwd = true;
        motor_1.brake = false;
        motor_update();
        
        ir_release_btn();
        motor_0.brake = true;
        motor_1.brake = true;
        motor_update();

        break;

        case IR_STAR:
        Serial.println("Rotate CW");
        motor_0.speed = 255;
        motor_0.fwd = false;
        motor_0.brake = false;
        motor_1.speed = 255;
        motor_1.fwd = true;
        motor_1.brake = false;
        motor_update();
        
        ir_release_btn();
        motor_0.brake = true;
        motor_1.brake = true;
        motor_update();

        case IR_POUND:
        Serial.println("Rotate CCW");
        motor_0.speed = 255;
        motor_0.fwd = true;
        motor_0.brake = false;
        motor_1.speed = 255;
        motor_1.fwd = false;
        motor_1.brake = false;
        motor_update();
        
        ir_release_btn();
        motor_0.brake = true;
        motor_1.brake = true;
        motor_update();

        break;
        
        default:
        delay(100);
    }
  }
  //delay(100);
}




