
#include <Arduino.h>
#include <EEPROM.h>

// MOTOR & ENCODER 
#define leftM1_AIN1 18
#define leftM2_AIN2 19
#define rightM1_BIN1 17
#define rightM2_BIN2 5
#define pwmLeft_A 25
#define pwmRight_B 26
#define leftEncA 15
#define leftEncB 2
#define rightEncA 23
#define rightEncB 4

volatile long countEncoderLeft = 0, countEncoderRight = 0;
long distanceLeft = 0, distanceRight = 0;
long pidRightFreq = 100, pidLeftFreq = 100;

const float pulsesPerRevolution = 11.0f * 21.3f * 2.0f;
const float circumference = 201.0f; // mm

float speed = 0;
long setPulsePerCycleLeft = 0;
long setPulsePerCycleRight = 0;
bool stopFlag = false;
int direction = 0;
int phase = 0;

float balanceFactorLeft = 1.0f;
float balanceFactorRight = 1.0f;
float minSpeed = 0.6f;

//  LINE SENSOR
#define NUMBER_OF_EYES 8
const byte eyePin[NUMBER_OF_EYES] = {14, 27, 33, 32, 35, 34, 39, 36};
bool eyeValue[NUMBER_OF_EYES];

//  COLOR SENSOR 
#define S0 21
#define S1 22
#define S2 13
#define S3 16
#define sensorOut 3  

int redFreq = 0, blueFreq = 0;
char savedColor = 'N';

// EEPROM 
#define ADDR_RED 0
#define ADDR_BLUE 4
int refRed = 0, refBlue = 0;

// MOTOR FUNCTIONS 
void setLeftPWM(byte n) { ledcWrite(0, n); }
void setRightPWM(byte n) { ledcWrite(1, n); }

void stopMotor() {
  setLeftPWM(0);
  setRightPWM(0);
  countEncoderLeft = 0;
  countEncoderRight = 0;
}

void setupMotor() {
  pinMode(leftM1_AIN1, OUTPUT);
  pinMode(leftM2_AIN2, OUTPUT);
  pinMode(rightM1_BIN1, OUTPUT);
  pinMode(rightM2_BIN2, OUTPUT);

  pinMode(leftEncA, INPUT);
  pinMode(leftEncB, INPUT);
  pinMode(rightEncA, INPUT);
  pinMode(rightEncB, INPUT);

  digitalWrite(leftM1_AIN1, HIGH);
  digitalWrite(leftM2_AIN2, LOW);
  digitalWrite(rightM1_BIN1, HIGH);
  digitalWrite(rightM2_BIN2, LOW);

  ledcSetup(0, 20000, 8);
  ledcAttachPin(pwmLeft_A, 0);
  ledcSetup(1, 20000, 8);
  ledcAttachPin(pwmRight_B, 1);
}

// SPEED SET 
void setSpeed(float n) {
  speed = n;
  float rpm = (n * 60.0f) / (circumference / 1000.0f);
  setPulsePerCycleLeft = (long)((rpm * pulsesPerRevolution) / (60.0f * pidLeftFreq));
  setPulsePerCycleRight = (long)((rpm * pulsesPerRevolution) / (60.0f * pidRightFreq));
}

// ENCODER
void checkLeftEncoder() {
  static byte preA = 0;
  byte nowA = digitalRead(leftEncA);
  if (nowA != preA) {
    preA = nowA;
    countEncoderLeft++;
    distanceLeft++;
  }
}

void checkRightEncoder() {
  static byte preB = 0;
  byte nowB = digitalRead(rightEncB);
  if (nowB != preB) {
    preB = nowB;
    countEncoderRight++;
    distanceRight++;
  }
}

void controlLeftRPM() {
  static long intE = 0, preLeftPID = 0, preE = 0;
  static float kP = 3.0f, kI = 0.02f, kD = 0.008f;

  long now = micros();
  if (now - preLeftPID >= (long)(1e6 / pidLeftFreq)) {
    preLeftPID = now;
    long target = setPulsePerCycleLeft;
    if (direction > 0) target = (long)(target * (1.0f - 0.14f * abs(direction)));
    long e = (long)(target * balanceFactorLeft) - countEncoderLeft;

    if (stopFlag || speed == 0) e = 0;
    intE += e;
    if (stopFlag || speed == 0) intE = 0;

    countEncoderLeft = 0;
    int pwm = (int)(kP * e + kI * intE + kD * (e - preE));
    pwm = constrain(pwm, 0, 255);
    setLeftPWM((byte)pwm);
    preE = e;
  }
}

void controlRightRPM() {
  static long intE = 0, preRightPID = 0, preE = 0;
  static float kP = 2.5f, kI = 0.02f, kD = 0.008f;

  long now = micros();
  if (now - preRightPID >= (long)(1e6 / pidRightFreq)) {
    preRightPID = now;
    long target = setPulsePerCycleRight;
    if (direction < 0) target = (long)(target * (1.0f - 0.14f * abs(direction)));
    long e = (long)(target * balanceFactorRight) - countEncoderRight;

    if (stopFlag || speed == 0) e = 0;
    intE += e;
    if (stopFlag || speed == 0) intE = 0;

    countEncoderRight = 0;
    int pwm = (int)(kP * e + kI * intE + kD * (e - preE));
    pwm = constrain(pwm, 0, 255);
    setRightPWM((byte)pwm);
    preE = e;
  }
}

//  LINE SENSOR 
void setupLineSensor() {
  for (int i = 0; i < NUMBER_OF_EYES; i++) pinMode(eyePin[i], INPUT);
}

void checkEyes() {
  for (int i = 0; i < NUMBER_OF_EYES; i++) eyeValue[i] = digitalRead(eyePin[i]);
}

void checkDirection() {
  byte left = 0, right = 0, all = 0;
  for (byte i = 0; i < NUMBER_OF_EYES; i++) all += eyeValue[i];

  for (byte i = 0; i < NUMBER_OF_EYES; i++) {
    if (eyeValue[i] == 0) break;
    left += eyeValue[i];
  }
  for (int i = NUMBER_OF_EYES - 1; i >= 0; i--) {
    if (eyeValue[i] == 0) break;
    right += eyeValue[i];
  }

  stopFlag = (all == NUMBER_OF_EYES || all == 0);
  if (stopFlag) return;
  direction = -(int)(right - left);
}

// SPEED MONITOR 
float totalDistanceMM() {
  float leftMM = (distanceLeft * circumference) / pulsesPerRevolution;
  float rightMM = (distanceRight * circumference) / pulsesPerRevolution;
  return (leftMM + rightMM) / 2.0f;
}

//  COLOR SENSOR
void setupColorSensor() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
}

void saveReferenceValues(int red, int blue) {
  EEPROM.put(ADDR_RED, red);
  EEPROM.put(ADDR_BLUE, blue);
  EEPROM.commit();
  Serial.printf(">> Lưu vào EEPROM: RED=%d, BLUE=%d\n", red, blue);
}

void loadReferenceValues() {
  EEPROM.get(ADDR_RED, refRed);
  EEPROM.get(ADDR_BLUE, refBlue);
  Serial.printf(">> Đọc EEPROM: RED=%d, BLUE=%d\n", refRed, refBlue);
}

// COLOR SENSOR NEW LOGIC 
char readColorRGB() {
  int r, b;

  // RED
  digitalWrite(S2, LOW); digitalWrite(S3, LOW);
  r = pulseIn(sensorOut, LOW, 2000UL);

  // BLUE
  digitalWrite(S2, LOW); digitalWrite(S3, HIGH);
  b = pulseIn(sensorOut, LOW, 2000UL);

  Serial.printf("R=%d  B=%d\n", r, b);

  if (r < b) return 'R';
  else if (b < r) return 'B';
  else return 'N'; // không xác định
}

char readColorDuringStop() {
  unsigned long t0 = millis();
  int redCount = 0, blueCount = 0;
  while (millis() - t0 < 5000) {
    char c = readColorRGB();
    if (c == 'R') redCount++;
    else if (c == 'B') blueCount++;
    delay(50);
  }
  if (redCount > blueCount) return 'R';
  else if (blueCount > redCount) return 'B';
  else return 'N';
}

// MAIN 
void setup() {
  Serial.begin(115200);
  EEPROM.begin(64);
  loadReferenceValues();

  setupMotor();
  setupLineSensor();
  setupColorSensor();
  setSpeed(0.3f);

  Serial.println("System Ready!");
}

void loop() {
  checkEyes();
  checkDirection();
  checkLeftEncoder();
  checkRightEncoder();
  controlLeftRPM();
  controlRightRPM();

  float travelMM = totalDistanceMM();

  if (phase == 0) {
    if (travelMM >= 1500.0f) setSpeed(minSpeed);
    if (travelMM > 2000.0f) {
      phase = 1;
      balanceFactorLeft = 0.0f;
      balanceFactorRight = 0.0f;
      setSpeed(0.0f);
      stopMotor();
      Serial.println("[PHASE 0 → 1] Dừng lại để đọc màu...");
      savedColor = readColorDuringStop(); // chỉ đọc ở đây
      Serial.printf("[PHASE 1] savedColor = %c\n", savedColor);
    }
  }
  else if (phase == 1) {
    if (savedColor == 'B') {
      balanceFactorLeft = 1.4f; balanceFactorRight = 1.0f;
      Serial.println("[PHASE 1] Màu BLUE → Rẽ Phải");
    } else if (savedColor == 'R') {
      balanceFactorLeft = 3.3f; balanceFactorRight = 1.0f;
      Serial.println("[PHASE 1] Màu RED → Rẽ Trái");
    } else {
      balanceFactorLeft = 1.0f; balanceFactorRight = 1.5f;
      Serial.println("[PHASE 1] Không chắc màu → mặc định");
    }
    stopFlag = false;
    setSpeed(minSpeed);
    phase = 2;
  }

  //  BLUE STOP & TURN LEFT
  if (phase >= 2 && savedColor == 'B' && stopFlag) {
    // đánh lái nhẹ sang trái bằng cách giảm PWM phải
    byte leftPWM = 50;   // giá trị nhỏ để di chuyển chậm
    byte rightPWM = 0;  // giảm để đánh lái sang trái
    setLeftPWM(leftPWM);
    setRightPWM(rightPWM);
    Serial.println("[BLUE DETECTED & STOPPED] Đánh lái nhẹ sang trái...");
    // kiểm tra lại line để reset stopFlag
    checkEyes();
    checkDirection();
    if (!stopFlag) {
      // khi tìm lại line, quay về điều khiển PID bình thường
      setSpeed(minSpeed);
      Serial.println("[LINE FOUND] Quay về PID bình thường");
    }
  }
  if (phase >= 2 && savedColor == 'R' && stopFlag) {
    // đánh lái nhẹ sang trái bằng cách giảm PWM phải
    byte leftPWM = 0;   // giá trị nhỏ để di chuyển chậm
    byte rightPWM = 50;  // giảm để đánh lái sang trái
    setLeftPWM(leftPWM);
    setRightPWM(rightPWM);
    Serial.println("[RED DETECTED & STOPPED] Đánh lái nhẹ sang phai...");
    // kiểm tra lại line để reset stopFlag
    checkEyes();
    checkDirection();
    if (!stopFlag) {
      // khi tìm lại line, quay về điều khiển PID bình thường
      setSpeed(minSpeed);
      Serial.println("[LINE FOUND] Quay về PID bình thường");
    }
  }
  

  //  NEW: STOP AFTER 5 METERS
  if (totalDistanceMM() >= 6450.0f) { stopMotor(); while(1); }

  delay(1);
}