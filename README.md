1. Proje Özeti

Bu çalışmada, Android tabanlı bir mobil arayüz üzerinden Bluetooth protokolü ile uzaktan kontrol edilebilen bir mobil robot tasarlanmıştır. Sistemde haberleşme köprüsü olarak  ESP32 modülü, motor kontrolü ve ana mantıksal işlemler için ise Arduino Uno kullanılmıştır.

2. Donanım Mimarisi

Sistem donanımı şu bileşenlerden oluşmaktadır:

* **Ana Kontrolcü:** Arduino Uno.

* **Haberleşme Birimi:** ESP32 Geliştirme Kartı.

* **Hareket Sistemi:** L298N Motor Sürücü ve DC Motorlar.

* **Güç Kaynağı:** Sistem kararlılığı için motorlar ve ESP32/Arduino ayrı güç hatlarından beslenmiştir.

* **Hız Tespit (EDS):** 24.5 cm aralıklı IR Sensör çifti.

3. Sistemin Çalışma Mantığı

* Android telefondan gönderilen veriler, ESP32 üzerindeki Bluetooth protokolü ile alınır.

* ESP32, aldığı bu verileri UART (Seri Haberleşme) üzerinden Arduino Uno'ya aktarır.

* Arduino, gelen komutu işleyerek ('F', 'B', 'S' vb.) L298N sürücüsünü tetikler ve robotu hareket ettirir.

* Robot EDS istasyonundan geçerken, 24.5 cm aralıklı IR sensörler aracılığıyla hız tespiti yapılır ve sonuç LCD ekrana yazdırılır.

  ## 👤 Geliştirici
---
**İbrahim GÜLCAN** <br>
Mikroişlemciler ve Gömülü Sistemler Dersi Projesi <br>

