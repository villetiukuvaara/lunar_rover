#define MOTOR0 (uint8_t)0x00
#define MOTOR1 (uint8_t)0x01

typedef struct
{
  uint8_t id;
  bool brake = false;
  bool fwd = true;
  uint8_t speed = 0;
} motor_t;

motor_t motor_0, motor_1;

void motor_update(motor_t motor)
{
  if(motor.id == MOTOR0)
  {
    digitalWrite(12, motor_0.fwd ? HIGH : LOW); // Establishes direction of Channel A
    digitalWrite(9, motor_0.brake ? HIGH : LOW);   // Brake for Channel A
    analogWrite(3, motor_0.speed);   // Spins the motor on Channel A
  }
  else if(motor.id == MOTOR1)
  {
    digitalWrite(13, motor_1.fwd ? HIGH : LOW);  // Establishes direction of Channel B
    digitalWrite(8, motor_1.brake ? HIGH : LOW);   // Brake for Channel B
    analogWrite(11, motor_1.speed);    // Spins the motor on Channel B
  }
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


void setup()
{
  motor_init();
  motor_update(motor_0);
  motor_update(motor_1);
}

void loop()
{
  while(1)
  {
    motor_0.speed = 255;
    motor_1.speed = 125;
    motor_0.brake = false;
    motor_1.brake = false;
    motor_0.fwd = true;
    motor_1.fwd = true;

    motor_update(motor_0);
    motor_update(motor_1);

    delay(1000);
    
    motor_1.speed = 125;
    motor_0.fwd = false;
    motor_1.brake = true;

    motor_update(motor_0);
    motor_update(motor_1);

    delay(1000);
  }
}


