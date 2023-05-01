# include <Arduino.h>
# include <SparkFun_TB6612.h>

// Channel Pin-Map
#define CH1 A0
#define CH2 A1
#define CH3 A2
#define CH4 A3
#define CH5 A4

#define XAIN1 22
#define XBIN1 24
#define XAIN2 26
#define XBIN2 28
#define XPWMA 5
#define XPWMB 6
#define XSTBY 7



#define YAIN1 30
#define YBIN1 32
#define YAIN2 34
#define YBIN2 36
#define YPWMA 2
#define YPWMB 3
#define YSTBY 4

const int xoffsetA = 1;
const int xoffsetB = 1;

const int yoffsetA = 1;
const int yoffsetB = 1;

int speedCar = 255;     // 50 - 255.
int speed_Coeff = 2;

// Channel Values

int rcCH1 = 0; // Left - Right
int rcCH2 = 0; // Forward - Reverse
int rcCH3 = 0; // Acceleration
int rcCH4 = 0; // 
int rcCH5 = 0; // knob/sweep

char state = NULL; //Serial debugging

Motor xmotor1 = Motor(XAIN1, XAIN2, XPWMA, xoffsetA, XSTBY);
Motor xmotor2 = Motor(XBIN1, XBIN2, XPWMB, xoffsetB, XSTBY);

Motor ymotor1 = Motor(YAIN1, YAIN2, YPWMA, yoffsetA, YSTBY);
Motor ymotor2 = Motor(YBIN1, YBIN2, YPWMB, yoffsetB, YSTBY);

// Motor Speed Values - Start at zero for driver X
int MotorSpeedX = 0;
int MotorSpeedY = 0;

// Motor Direction Values - 0 = backward, 1 = forward for driver Y
int MotorDirX = 1;
int MotorDirY = 1;


// Control MotorDriver X
void mControlX(int mspeed, int mdir) {

  // Determine direction
  if (mdir == 0) {
    // Motor backward
//    Serial.print("Going Back X | Motor Speed: ");
    back(xmotor1, xmotor2, -mspeed);
    Serial.println(mspeed);
    
  } else {
    // Motor forward
//    Serial.println("Going Ahead X | Motor Speed: ");
    forward(xmotor1, xmotor2, mspeed);
    Serial.println(mspeed);
  }

}

// Control MotorDriver Y
void mControlY(int mspeed, int mdir) {

  // Determine direction
  if (mdir == 0) {
    // Motor backward
//    Serial.println("Going Back Y | Motor Speed: ");
    back(ymotor1, ymotor2, -mspeed);
    Serial.println(mspeed);
    
  } else {
    // Motor forward
//    Serial.println("Going Ahead Y | Motor Speed: ");
    forward(ymotor1, ymotor2, mspeed);
    Serial.println(mspeed);
  }

}

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
   int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup(){

  // Start serial monitor for debugging
  Serial.begin(115200);

  // Set all the motor control pins to outputs

  pinMode(XPWMA, OUTPUT);
  pinMode(XPWMB, OUTPUT);
  pinMode(XAIN1, OUTPUT);
  pinMode(XAIN2, OUTPUT);
  pinMode(XBIN1, OUTPUT);
  pinMode(XBIN2, OUTPUT);
  pinMode(XSTBY, OUTPUT);

  pinMode(YPWMA, OUTPUT);
  pinMode(YPWMB, OUTPUT);
  pinMode(YAIN1, OUTPUT);
  pinMode(YAIN2, OUTPUT);
  pinMode(YBIN1, OUTPUT);
  pinMode(YBIN2, OUTPUT);
  pinMode(YSTBY, OUTPUT);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);

  rcCH1 = map(readChannel(CH1, -100, 100, 0), -80, 80, -100, 100);
  rcCH2 = map(readChannel(CH2, -100, 100, 0), -70, 70, -100, 100);
  rcCH3 = constrain(map(readChannel(CH3, 0, 155, 0), 20, 130, 0, 155), 0, 255);
  rcCH5 = readChannel(CH5, -100, 100, 0);
  rcCH4 = map(readChannel(CH4, -100, 100, 0), -80, 80, -100, 100);

  // Set LED pin as output


  // Keep motors on standby for two seconds & flash LED
  digitalWrite(XSTBY, LOW);
//  digitalWrite(carLED, HIGH);
  delay (1000);
//  digitalWrite(carLED, LOW);
  delay (1000);
  digitalWrite(YSTBY, HIGH);

}

void loop() {

  // Get RC channel values
  rcCH1 = map(readChannel(CH1, -100, 100, 0), -80, 80, -100, 100);
  rcCH2 = map(readChannel(CH2, -100, 100, 0), -70, 70, -100, 100);
  rcCH3 = constrain(map(readChannel(CH3, 0, 155, 0), 20, 130, 0, 155), 0, 255);
  rcCH5 = readChannel(CH5, -100, 100, 0);
  rcCH4 = map(readChannel(CH4, -100, 100, 0), -80, 80, -100, 100);

  // Print values to serial monitor for debugging
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);
 
  Serial.print(" Ch2 = ");
  Serial.print(rcCH2);
 
  Serial.print(" Ch3 = ");
  Serial.print(rcCH3);
 
  Serial.print(" Ch4 = ");
  Serial.print(rcCH4);
 
  Serial.print(" Ch5 = ");
  Serial.println(rcCH5);

  // Set speeds with channel 3 value
  MotorSpeedX = rcCH3;
  MotorSpeedY = rcCH3;

  // Set Mode with channel 6 value
 
    // Normal Mode

    // Turn off LED
//    digitalWrite(carLED, LOW);

    // Set forward/backward direction with channel 2 value
    if (rcCH2 >= 0) {
      //Forward
      MotorDirX = 1;
      MotorDirY = 1;
      Serial.println("Forward");
      delay(20);
    } else {
      //Backward
      MotorDirX = 0;
      MotorDirY = 0;
      Serial.println("Backward");
      delay(20);
    }

    // Add channel 2 speed
    MotorSpeedX = MotorSpeedX + abs(rcCH2);
    MotorSpeedY = MotorSpeedY + abs(rcCH2);

    // Set left/right offset with channel 1 value
    MotorSpeedX = MotorSpeedX - rcCH1;
    MotorSpeedY = MotorSpeedY + rcCH1;

  

  // Ensure that speeds are between 0 and 255
  MotorSpeedX = constrain(MotorSpeedX, 0, 255);
  MotorSpeedY = constrain(MotorSpeedY, 0, 255);

  //Drive Motors
  Serial.println("Driving Motors");
  mControlX(MotorSpeedX, MotorDirX);
  mControlY(MotorSpeedY, MotorDirY);

  // Print speed values to serial monitor for debugging
  Serial.print("MotorDriver X Speed = ");
  Serial.println(MotorSpeedX);
  Serial.print("MotorDriver Y Speed = ");
  Serial.println(MotorSpeedY);

  // Slight delay
  delay(50);

}