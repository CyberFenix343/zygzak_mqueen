#include <Servo.h>
#include <DistanceSensor.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

//WYSWIETLANIE NA WYSWIETLACZU
const int LCD_ROWS = 2;
const int LCD_COLS = 16;
#define LIGHT A2
#define TEMP A3
#define POT A0
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008,7,6,5,4,3,2,1,HIGH);


int servoPin = 3;
Servo Servo1;


#define RIGHT_ENGINE 9
#define LEFT_ENGINE 10
#define LEFT_PHASE 2
#define RIGHT_PHASE 3
#define IR_ECHO 8
#define IR_TRIG 7

const int obstacleThreshold = 20; //Próg odległości po przekroczeniu którego robot ma wykonać manewr zawracania


bool Auto = false;
bool movementEnabled = true;
int predkosc = 80; // Prędkość robota



void setup() {

  Servo1.attach(servoPin);
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.print("Zygzak McQueen");
  delay(2000);


  pinMode(IR_TRIG, OUTPUT);
  pinMode(IR_ECHO, INPUT);
  pinMode(RIGHT_ENGINE, OUTPUT);
  pinMode(LEFT_ENGINE, OUTPUT);
  pinMode(LEFT_PHASE, OUTPUT);
  pinMode(RIGHT_PHASE, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  
 
  

  // Odczyt odleglosci
  float duration, distance;
  digitalWrite(IR_TRIG, 50);
  delay(10);
  digitalWrite(IR_TRIG, 0);
 

  duration = pulseIn(IR_ECHO, 50);

  distance = ((float)(340 * duration) / 10000) / 2;
  //Serial.print("\nDistance : ");
  //Serial.println(distance);

  if (Auto) {
    // Unikanie przeszkód
    avoidObstacles(distance);
    checkModeSwitch();
  } else {
    // Sterowanie za pomocą klawiatury
    manualControl();
  }
}

void avoidObstacles(int distance) {
  if (distance < obstacleThreshold) {
    checkModeSwitch();
    Serial.println("backward");
    Backward();
   
   
    // Jeśli wykryto przeszkodę, obracaj sie w prawo
    analogWrite(RIGHT_ENGINE, 120);
    analogWrite(LEFT_ENGINE, 120);
    digitalWrite(LEFT_PHASE, LOW);
    digitalWrite(RIGHT_PHASE, HIGH);
    delay(500);
  } else {
    // Brak przeszkód, poruszaj się do przodu
    Serial.println("forward");
    Forward();
  }
}

void manualControl() {
  if (movementEnabled) {
    if (Serial.available() > 0) {
      char command = Serial.read();
      switch (command) {
        case 'w':
          Text();
          Forward();
          
          break;
        case 's':
          Text();
          Backward();
          break;
        case 'a':
          Text();
          Left();
          break;
        case 'd':
          Text();
          Right();
          break;
        case 't':
          Text();
          Stop();
          break;
        case 'q':
          Text();
          toggleAuto();
          break;
        case 'r':
          Text();
          toggleMovement();
          break;
        case '+':
          Text();
          ZwiekszPredkosc();
          break;
        case '-':
          Text();
          ZmniejszPredkosc();
          break;

       
      }
    }
  } else {
    Stop();
  }
}
void Text(){
    float temp, pot, light;
  float ctemp;
  float cpot;
  int clight;

    temp = analogRead(TEMP) * (165.0/1023.0)-40.0;
    light = analogRead(LIGHT);
    lcd.clear();
    lcd.print("R: "); lcd.print(POT); lcd.print("%");
    lcd.setCursor(8, 0);
    lcd.print("L: "); lcd.print(light); lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("T: "); lcd.print(temp); lcd.print((char)223); lcd.print("C");
}
void Forward() {
  digitalWrite(LEFT_PHASE, HIGH);
  digitalWrite(RIGHT_PHASE, LOW);
 
  analogWrite(RIGHT_ENGINE, predkosc);
  analogWrite(LEFT_ENGINE, predkosc);
  Serial.println("Jazda do przodu");
}  

void Backward() {
 digitalWrite(LEFT_PHASE, LOW);
 digitalWrite(RIGHT_PHASE, LOW);
  analogWrite(RIGHT_ENGINE, predkosc);
 analogWrite(LEFT_ENGINE, predkosc);
 Serial.println("Jazda do tyłu");
 
  
}

void Left() {
  digitalWrite(LEFT_PHASE, HIGH);
  digitalWrite(RIGHT_PHASE, LOW);
  analogWrite(RIGHT_ENGINE, 100);
  analogWrite(LEFT_ENGINE, 100);
  
}

void Right() {
  digitalWrite(LEFT_PHASE, LOW);
  digitalWrite(RIGHT_PHASE, HIGH);
  analogWrite(RIGHT_ENGINE, 100);
  analogWrite(LEFT_ENGINE, 100);
  
}

void Stop() {
  analogWrite(RIGHT_ENGINE, 0);
  analogWrite(LEFT_ENGINE, 0);
}

void toggleAuto() {
  Auto = !Auto;
}

void toggleMovement() {
  movementEnabled = !movementEnabled;
}

void ZwiekszPredkosc() {
  if (predkosc < 255) {
    predkosc += 10;
  }
}

void ZmniejszPredkosc() {
  if (predkosc > 0) {
    predkosc -= 10;
  }
}
void checkModeSwitch() {
  // Przęłączanie trybów ruchu
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'm') {
      toggleAuto();
    }
  }
}
