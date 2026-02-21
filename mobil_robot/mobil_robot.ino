#include <SoftwareSerial.h>

// Bluetooth Bağlantısı

SoftwareSerial BT(10, 11); 
// Motor Sürücü Pinleri
// Sol Motor
const int ENA = 3;  const int IN1 = 4;  const int IN2 = 5;
// Sağ Motor
const int IN3 = 6;  const int IN4 = 7;  const int ENB = 9;

// Hız
int motorHizi = 150;

// MOTOR DENGELEME 
int solDenge = 5;   
int sagDenge = 0;    

char veri;

void setup() {
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Araba Manuel Kontrol Modunda Hazir!");
}
void loop() {
  if (BT.available()) {
    veri = BT.read();
    // --- HIZ AYARI ---
    if (veri == '0') motorHizi = 0;
    else if (veri == '1') motorHizi = 25;
    else if (veri == '2') motorHizi = 50;
    else if (veri == '3') motorHizi = 75;
    else if (veri == '4') motorHizi = 100;
    else if (veri == '5') motorHizi = 125;
    else if (veri == '6') motorHizi = 150;
    else if (veri == '7') motorHizi = 175;
    else if (veri == '8') motorHizi = 200;
    else if (veri == '9') motorHizi = 225;
    else if (veri == 'q') motorHizi = 255;
    // --- YÖN ---
    else if (veri == 'F') ileri();
    else if (veri == 'B') geri();
    else if (veri == 'L') sol();
    else if (veri == 'R') sag();
    else if (veri == 'S') dur();
  }
}
// --- HAREKET FONKSİYONLARI ---
void ileri() {
  analogWrite(ENA, constrain(motorHizi + solDenge, 0, 255));
  analogWrite(ENB, constrain(motorHizi + sagDenge, 0, 255));
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void geri() {
  analogWrite(ENA, constrain(motorHizi + solDenge, 0, 255));
  analogWrite(ENB, constrain(motorHizi + sagDenge, 0, 255));
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}
void sol() {
  analogWrite(ENA, 0); // Sol motor durur 
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
// Sağ motor iter
  analogWrite(ENB, constrain(motorHizi + sagDenge, 0, 255)); 
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void sag() {
  // Sağ motor durur, Sol motor iter
  analogWrite(ENA, constrain(motorHizi + solDenge, 0, 255));
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);

  analogWrite(ENB, 0); 
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}
void dur() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}