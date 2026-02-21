#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// --- EKRAN AYARLARI ---
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// --- PIN AYARLARI ---
const int girisSensorPin = 2;  
const int cikisSensorPin = 3;  
const int buzzerPin = 8;       

// --- AYARLAR ---
const float SENSOR_ARASI_MESAFE_CM = 24.5; 

// Hız Limiti 
float hizSiniri = 75.0; 

// Alarm Süresi 
int alarmSuresi = 2000; 

// --- DEĞİŞKENLER ---
unsigned long baslangicZamani = 0;
unsigned long bitisZamani = 0;
bool olcumBasladi = false;

void setup() {
 
  // Bu, sensör boşta dururken parazit yapmasını engelliyor
  pinMode(girisSensorPin, INPUT_PULLUP);
  pinMode(cikisSensorPin, INPUT_PULLUP);
  
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  // Açılış Testi
  digitalWrite(buzzerPin, HIGH); delay(100); digitalWrite(buzzerPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("EDS SISTEMI");
  lcd.setCursor(0, 1);
  lcd.print("ACILIYOR...");
  delay(2000);
  
  ekraniSifirla();
}

void loop() {
  // --- 1. SENSÖR (Giriş) ---
  if (digitalRead(girisSensorPin) == LOW && olcumBasladi == false) {
    
    delay(50); 
    if(digitalRead(girisSensorPin) == LOW) {
        baslangicZamani = millis();
        olcumBasladi = true;
        
        lcd.clear();
        lcd.print("ARAC GIRDI >>"); 
        lcd.setCursor(0, 1);
        lcd.print("OLCUM YAPILIYOR");
    }
  }

  // --- 2. SENSÖR (Çıkış) ---
  if (digitalRead(cikisSensorPin) == LOW && olcumBasladi == true) {
    bitisZamani = millis();
    olcumBasladi = false;

    hesaplaVeYazdir(); 
  }
}

// --- EKRANI BAŞA DÖNDÜRME FONKSİYONU ---
void ekraniSifirla() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SISTEM HAZIR");
  lcd.setCursor(0, 1);
  lcd.print("ARAC BEKLENIYOR");
}

void hesaplaVeYazdir() {
  unsigned long gecenSureMs = bitisZamani - baslangicZamani;
  float gecenSureSn = gecenSureMs / 1000.0;

  // Hatalı ölçüm engelleme 
  if (gecenSureSn <= 0.001) {
      ekraniSifirla();
      return; 
  }

  float hizCmSn = SENSOR_ARASI_MESAFE_CM / gecenSureSn; 
  
  // --- SONUÇLARI YAZDIR ---
  lcd.clear();
  
  if (hizCmSn > hizSiniri) {
    // --- HIZLI (ALARM) ---
    lcd.setCursor(0, 0);
    lcd.print("!! HIZ ASIMI !!"); 
    lcd.setCursor(0, 1);
    lcd.print(hizCmSn); lcd.print(" cm/s");
    
    digitalWrite(buzzerPin, HIGH);
    delay(alarmSuresi); 
    digitalWrite(buzzerPin, LOW);
  } 
  else {
    // --- NORMAL HIZ ---
    lcd.setCursor(0, 0);
    lcd.print("HIZ NORMAL"); 
    lcd.setCursor(0, 1);
    lcd.print(hizCmSn); lcd.print(" cm/s");
    
    digitalWrite(buzzerPin, HIGH);
    delay(150); 
    digitalWrite(buzzerPin, LOW);
    
    delay(3000); // Sonucu ekranda tut
  }

  // Bilgisayara gönder
  Serial.print("Sure: "); Serial.print(gecenSureSn); 
  Serial.print(" Hiz: "); Serial.println(hizCmSn);
  // --- SENSÖR TEMİZLEME ---
  // Eğer giriş sensörü hala LOW (engel var) ise veya parazitli ise
  // sistem burada bekler, başa dönüp tekrar "Araç Girdi" yazmaz.
  // Sensör HIGH olana kadar (önü boşalana kadar) burada kilitlenir.
  
  while(digitalRead(girisSensorPin) == LOW) {
    delay(100); 
  }
  // Sensör temizlendikten sonra ekranı sıfırlar.
  ekraniSifirla(); 
}