[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?style=flat)](https://github.com/ellerbrock/open-source-badges/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg?logo=github&color=%23F7DF1E)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/cakraawijaya/Aquaponic-pH-Control-Monitoring-with-Type-2-Fuzzy-Method-Based-on-IoT-Bot?logo=Codeforces&logoColor=white&color=%23F7DF1E)
![Project](https://img.shields.io/badge/Project-ESP32-light.svg?style=flat&logo=espressif&logoColor=white&color=%23F7DF1E)
![Type](https://img.shields.io/badge/Type-Skripsi-light.svg?style=flat&logo=gitbook&logoColor=white&color=%23F7DF1E)

# Aquaponic pH Control-Monitoring with Type 2 Fuzzy Method-Based on IoT-Bot
<strong>Dokumentasi Proyek Skripsi - Informatika UPN Veteran Jatim</strong><br><br>
Sistem akuaponik adalah sistem pertanian gabungan antara ikan dengan sayuran yang saling menguntungkan. Di sisi lain, gagal panen juga dapat menjadi kekhawatiran bagi para petani akuaponik karena hal ini dapat terjadi kapan saja. Kegagalan panen dapat dipengaruhi oleh banyak faktor, namun biasanya disebabkan oleh ketidakjelasan pH air yang tinggi di sekitar ruang lingkup budidaya. Para petani akuaponik khawatir jika gagal panen terus berlanjut akan membahayakan ketahanan pangan mereka. Proyek ini dibuat dengan harapan dapat mengatasi masalah pH tersebut. Proyek ini telah dilaksanakan dan memakan waktu kurang lebih 1 tahun. Sistem yang dibuat dapat mengontrol dan memonitoring perubahan pH air setiap saat. Sistem ini berbasis Internet of Things (IoT), dengan menggunakan MQTT sebagai protokol komunikasinya. Sistem ini juga dilengkapi dengan kecerdasan buatan, yang menggunakan IT2FL (Interval Type-2 Fuzzy Logic) sebagai pendukung keputusannya. Selain itu, antarmuka sistem menggunakan Bot Telegram, sehingga memudahkan pengguna untuk berinteraksi.

<br><br>

## Kebutuhan Proyek
| Bagian | Deskripsi |
| --- | --- |
| Papan Pengembangan | DOIT ESP32 DEVKIT V1 |
| Papan Pendukung | Arduino Uno R3 |
| Editor Kode | Arduino IDE 1.8.19 (Versi Lama yang Stabil) |
| Dukungan Aplikasi | • Bot Telegram<br>• Matlab R2020 |
| Driver | CP210X USB Driver |
| Platform IoT | io-t.net |
| Protokol Komunikasi | • Inter Integrated Circuit (I2C)<br>• Message Queuing Telemetry Transport (MQTT)<br>• MTProto |
| Arsitektur IoT | 3 Lapisan |
| Matlab |  Fuzzy Interface System |
| Bahasa Pemrograman | C/C++ |
| Pustaka Arduino | • WiFi (bawaan)<br>• PubSubClient oleh Nick O'Leary (Versi: 2.8)<br>• LiquidCrystal_I2C oleh Frank de Brabander (Versi: 1.1.2)<br>• CTBot oleh Stefano Ledda (Versi: 2.1.11)<br>• ArduinoJson oleh Benoit Blanchon (Versi: 6.19.4)<br>• RTClib oleh Adafruit (Versi: 2.0.2) |
| Aktuator | • Submersible pump aquarium (x1)<br>• Pneumatic solenoid valve (x2)<br>• Piezoelectric (x1)<br>• Relay elektromekanis 2-channel (x1) |
| Sensor | • pH Sensor (x1)<br>• RTC (x1) |
| Layar | LCD I2C (x1) |
| Objek Percobaan | • Benih sawi pakcoy<br>• Benih lele dumbo |
| Komponen Lainnya | • Kabel USB Mikro - USB tipe A (x1)<br>• Kabel jumper (1 set)<br>• Switching power supply 12V 1A (x1)<br>• Saklar bulat (x1)<br>• Papan ekspansi ESP32 (x1)<br>• PCB Dot Matrix (x1)<br>• Terminal PCB block screw (x10)<br>• Socket female jack DC (x1)<br>• Connector male jack DC (x3)<br>• Probe Elektroda pH (x1)<br>• Pipa (1 set)<br>• Netpot (1 set)<br>• Rockwool (1 set)<br>• Kain flanel (1 set)<br>• Saringan air (x1)<br>• Dop kaca (1 set)<br>• Botol (x2)<br>• Tatakan beroda akuarium (x1)<br>• Akuarium (x1)<br>• Kotak akrilik (x1)<br>• Skun (1 set)<br>• Plat galvanis (x1)<br>• Baut plus (1 set)<br>• Mur (1 set) |

<br><br>

## Unduh & Instal
1. Arduino IDE

   <table><tr><td width="810">
      
   ```
   https://www.arduino.cc/en/software
   ```

   </td></tr></table><br>

2. CP210X USB Driver

   <table><tr><td width="810">

   ```
   https://bit.ly/CP210X_USBdriver
   ```

   </td></tr></table><br>

3. Matlab R2020

   <table><tr><td width="810">

   ```
   https://bit.ly/MATLAB_R2020a_Installer
   ```

   </td></tr></table>

<br><br>

## Rancangan Proyek
<table>
<tr>
<th width="840">Infrastruktur</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Diagram/Infrastructure.jpg" alt="infrastructure"></td>
</tr>
</table>
<table>
<tr>
<th width="280">Diagram Ilustrasi</th>
<th width="280">Desain Prototipe</th>
<th width="280">Desain Wadah Utama</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Diagram/Pictorial Diagram.jpg" alt="pictorial-diagram"></td>
<td><img src="Assets/Documentation/Design/Prototype Design.jpg" alt="prototype-design"></td>
<td><img src="Assets/Documentation/Design/Main Box Design.jpg" alt="mainBox-design"></td>
</tr>
</table>
<table>
<tr>
<th width="280">Sistem Antarmuka Fuzzy IT2FL</th>
<th width="280">Variabel Masukan IT2FL</th>
<th width="280">Variabel Keluaran IT2FL</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Experiment/Fuzzy Interface System IT2FL.jpg" alt="fis-it2fl"></td>
<td><img src="Assets/Documentation/Experiment/IT2FL Input Variable.jpg" alt="varin-it2fl"></td>
<td><img src="Assets/Documentation/Experiment/IT2FL Output Variable.jpg" alt="varout-it2fl"></td>
</tr>
</table>

<br><br>

## Memindai Alamat I2C Yang Ada Pada LCD
<table><tr><td width="840">
   
```ino
/*
  =====================================================
  I2C Scanner untuk Arduino / ESP32 / ESP8266
  by: Devan Cakra Mudra Wijaya, S.Kom.
  =====================================================

  Fungsi:
  - Mendeteksi seluruh perangkat I2C yang terhubung
  - Menampilkan alamat perangkat dalam format HEX
  - Menampilkan jumlah perangkat yang ditemukan


  =====================================================
  Pin SDA dan SCL untuk Arduino / ESP32 / ESP8266
  =====================================================
  Koneksi I2C Arduino (default):
  - Arduino Uno / Nano (ATmega328P)
    SDA -> A4
    SCL -> A5

  - Arduino Mega 2560
    SDA -> D20
    SCL -> D21

  - Board Arduino lainnya
    SDA -> Pin SDA
    SCL -> Pin SCL
    (Lihat datasheet atau pinout board)

  Koneksi I2C ESP32 (default):
  SDA -> GPIO 21
  SCL -> GPIO 22

  Koneksi I2C ESP8266 (default):
  SDA -> GPIO 4 (D2)
  SCL -> GPIO 5 (D1)
*/

// Memanggil library Wire untuk komunikasi I2C
#include <Wire.h>

// Konstanta untuk menentukan jeda antar scan (5000 ms = 5 detik)
const uint32_t SCAN_INTERVAL = 5000;


// Fungsi untuk menginisialisasi komunikasi I2C
// Konfigurasi pin SDA dan SCL akan disesuaikan secara otomatis berdasarkan jenis board yang digunakan
void initI2C() {

  // Jika board yang digunakan adalah ESP32, maka:
  #if defined(ESP32)

    // Mengaktifkan komunikasi I2C
    // SDA = GPIO21
    // SCL = GPIO22
    Wire.begin(21, 22);

  // Jika board yang digunakan adalah ESP8266, maka:
  #elif defined(ESP8266)

    // Mengaktifkan komunikasi I2C
    // SDA = D2 (GPIO4)
    // SCL = D1 (GPIO5)
    Wire.begin(D2, D1);

  // Jika board yang digunakan bukan ESP32 maupun ESP8266
  // Contoh: Arduino Uno, Nano, Mega, Leonardo, dll, maka:
  #else

    // Mengaktifkan komunikasi I2C menggunakan pin hardware bawaan board
    Wire.begin();

  #endif

}


// Fungsi setup() dijalankan satu kali saat board pertama kali menyala atau reset
// Digunakan untuk inisialisasi perangkat keras, komunikasi serial, sensor, modul, dan konfigurasi awal program
void setup() {

  // Memulai komunikasi Serial dengan baud rate 115200
  Serial.begin(115200);

  // Mengecek apakah board menggunakan USB native
  // Contoh: Arduino Leonardo, Arduino Micro, beberapa ESP32-S2/S3
  #if defined(USBCON) || defined(ARDUINO_USB_CDC_ON_BOOT)

    // Jika iya, maka:
    // Program akan menunggu sampai Serial Monitor terhubung sebelum melanjutkan eksekusi program
    while (!Serial);

  #endif

  // Menunggu selama 2 detik sebelum program dimulai
  delay(2000);

  // Menampilkan header program
  Serial.println("====================================");
  Serial.println("         I2C DEVICE SCANNER         ");
  Serial.println("by: Devan Cakra Mudra Wijaya, S.Kom.");
  Serial.println("====================================");

  // Mencetak baris kosong
  Serial.println();

  // Menginisialisasi komunikasi I2C
  initI2C();
}


// Fungsi loop() dijalankan terus-menerus setelah Fungsi setup() selesai
// Seluruh logika utama program biasanya ditempatkan di dalam fungsi ini
void loop() {

  // Variabel untuk menyimpan kode error hasil komunikasi I2C
  uint8_t error;

  // Variabel untuk menyimpan alamat I2C yang sedang diperiksa
  uint8_t address;

  // Variabel penghitung jumlah device yang ditemukan
  uint8_t deviceCount = 0;

  // Menampilkan informasi bahwa proses scan dimulai
  Serial.println("------------------------------------");
  Serial.println("Scanning I2C bus...");
  Serial.println("------------------------------------");

  // Melakukan perulangan dari alamat 1 sampai 126
  // Alamat I2C valid adalah 0x01 sampai 0x7E
  for (address = 1; address < 127; address++) {

    // Memulai komunikasi ke alamat yang sedang diuji
    Wire.beginTransmission(address);

    // Mengakhiri transmisi dan menyimpan hasilnya
    // 0 = sukses
    // 1 = data terlalu panjang
    // 2 = NACK saat alamat dikirim
    // 3 = NACK saat data dikirim
    // 4 = error lain
    error = Wire.endTransmission();

    // Jika tidak ada error, maka:
    if (error == 0) {

      // Menampilkan informasi device ditemukan
      Serial.print("[FOUND] Device at address 0x");

      // Jika alamat kurang dari 16, maka:
      // Tambahkan angka 0 di depan agar format HEX rapi
      if (address < 16) {
        Serial.print("0");
      }

      // Menampilkan alamat dalam format HEX
      Serial.println(address, HEX);

      // Menambah jumlah device yang ditemukan
      deviceCount++;
    }

    // Jika terjadi error tidak dikenal, maka:
    else if (error == 4) {

      // Menampilkan pesan error
      Serial.print("[ERROR] Unknown error at address 0x");

      // Jika alamat kurang dari 16, maka:
      // Tambahkan angka 0 di depan agar format HEX rapi
      if (address < 16) {
        Serial.print("0");
      }

      // Menampilkan alamat yang bermasalah dalam format HEX
      Serial.println(address, HEX);
    }

    // Jika error selain 0 atau 4, maka:
    // Diabaikan, biasanya ini terjadi karena tidak ada perangkat pada alamat tersebut
  }

  // Mencetak baris kosong
  Serial.println();

  // Jika tidak ada device ditemukan, maka:
  if (deviceCount == 0) {

    // Tampilkan pesan tidak ada device
    Serial.println("No I2C devices found.");
  }
  else { // Jika setidaknya satu perangkat ditemukan, maka:

    // Menampilkan jumlah device yang ditemukan
    Serial.print("Total devices found: ");

    // Menampilkan nilai deviceCount
    Serial.println(deviceCount);
  }

  // Menampilkan informasi waktu scan berikutnya
  Serial.print("Next scan in ");

  // Mengubah milidetik menjadi detik
  Serial.print(SCAN_INTERVAL / 1000);

  // Menampilkan satuan detik
  Serial.println(" seconds.");

  // Baris kosong
  Serial.println("\n");

  // Menunggu selama 5 detik sebelum scan ulang
  delay(SCAN_INTERVAL);
}
```

</td></tr></table><br><br>

## Kalibrasi Sensor pH
Sensor pH dapat di kalibrasi dengan menggunakan hasil perhitungan regresi linear. Persamaan regresi linear dapat anda lihat sebagai berikut.

<table>
   <tr>
   <td width="40">I</td>
   <td width="800" height="80">

   $\ Y = a+b.X $
         
   </td>
   </tr>
</table><br>

Penjelasan dari simbol-simbol yang ada di persamaan I, dapat anda lihat selengkapnya pada tabel berikut.

<table>
   <tr height="50px">
      <th width="120">Simbol</th>
      <th width="720">Keterangan</th>
   </tr>
   <tr>
      <td>𝑌</td>
      <td>nilai buffer pH</td>
   </tr>
   <tr>
      <td>𝑋</td>
      <td>nilai tegangan yang diperoleh berdasarkan Y</td>
   </tr>
   <tr>
      <td>𝑎 dan 𝑏</td>
      <td>nilai ketetapan regresi linear</td>
   </tr>
</table><br>

Nilai ketetapan regresi linear (a dan b) dapat diperoleh melalui persamaan II dan III.

<table>
   <tr>
   <td width="40">II</td>
   <td width="800" height="80">
   
   $\ a = \frac{\sum Y.\sum X^{2}-\sum X.\sum XY}{n.\sum X^{2}-(\sum X)^{2}} $

   </td>
   </tr>
   <tr>
   <td width="40">III</td>
   <td width="800" height="80">
   
   $\ b = \frac{n.\sum XY-\sum X.\sum Y}{n.\sum X^{2}-(\sum X)^{2}} $

   </td>
   </tr>
</table><br>

Contoh kalibrasi sensor pH: <a href="https://github.com/devancakra/Aquaponic-pH-Control-Monitoring-with-Type-2-Fuzzy-Method-Based-on-IoT-Bot/blob/master/Assets/Articles/Contoh-Kalibrasi-SensorpH.md">Klik Disini</a>

<br><br>

## Kalibrasi Sensor RTC
Sensor RTC ini dapat di kalibrasi dengan menggunakan kode program berikut :

<table><tr><td width="840">

```ino
#include <RTClib.h> // Memanggil pustaka RTC
RTC_DS3231 rtc; // Konstruktor

void setup() {
   RTCinit(); // Memanggil metode RTCinit
}

void loop() {}

void RTCinit() {
   // Memulai RTC
   rtc.begin();

   // Atur Waktu Sekarang
   // Jika sudah di kalibrasi, silakan tutup dengan komentar
   rtc.adjust(DateTime(YYYY, MM, DD, HH, MM, SS));
}
```

</td></tr></table><br><br>

## Pengaturan Arduino IDE
1. Buka ``` Arduino IDE ``` terlebih dahulu, kemudian buka proyek dengan cara klik ``` File ``` -> ``` Open ``` :

   <table><tr><td width="810">
      
      ``` PH_IT2FL.ino ```

   </td></tr></table><br>
   
2. Isi ``` Url Pengelola Papan Tambahan ``` di Arduino IDE

   <table><tr><td width="810">
      
      Klik ``` File ``` -> ``` Preferences ``` -> masukkan ``` Boards Manager Url ``` dengan menyalin tautan berikut :
      
      ```
      https://dl.espressif.com/dl/package_esp32_index.json
      ```

   </td></tr></table><br>
   
3. ``` Pengaturan Board ``` di Arduino IDE

   <table>
      <tr><th width="810">

      Cara mengatur board ``` DOIT ESP32 DEVKIT V1 ```
            
      </th></tr>
      <tr><td width="810">
      
      • Klik ``` Tools ``` -> ``` Board ``` -> ``` Boards Manager ``` -> Instal ``` esp32 ```.
   
      • Kemudian pilih papan dengan mengklik: ``` Tools ``` -> ``` Board ``` -> ``` ESP32 Arduino ``` -> ``` DOIT ESP32 DEVKIT V1 ```.
   
      • Board ``` Arduino Uno ``` yang ada di proyek ini hanya digunakan sebagai filter atau pembagi tegangan.
   
      • Anda tidak perlu melakukan konfigurasi pada board ``` Arduino Uno ```, cukup hanya berfokus pada ``` ESP32 ``` saja.

      </td></tr>
   </table><br>
   
4. ``` Ubah Kecepatan Papan ``` di Arduino IDE

   <table><tr><td width="810">
      
      Klik ``` Tools ``` -> ``` Upload Speed ``` -> ``` 9600 ```

   </td></tr></table><br>
   
5. ``` Instal Pustaka ``` di Arduino IDE

   <table><tr><td width="810">
      
      Unduh semua file zip pustaka. Kemudian tempelkan di: ``` C:\Users\Computer_Username\Documents\Arduino\libraries ```

   </td></tr></table><br>

6. ``` Pengaturan Port ``` di Arduino IDE

   <table><tr><td width="810">
      
      Klik ``` Port ``` -> Pilih sesuai dengan port perangkat anda ``` (anda dapat melihatnya di Device Manager) ```

   </td></tr></table><br>

7. Ubah ``` Nama WiFi ```, ``` Kata Sandi WiFi ```, dan sebagainya sesuai dengan apa yang anda gunakan saat ini.<br><br>

8. Sebelum mengunggah program, silakan klik: ``` Verify ```.<br><br>

9. Jika tidak ada kesalahan dalam kode program, silakan klik: ``` Upload ```.<br><br>
    
10. Beberapa hal yang perlu anda lakukan saat menggunakan ``` board ESP32 ``` :

    <table><tr><td width="810">
       
       • Jika ``` board ESP32 ``` tidak dapat memproses ``` Source Code ``` secara total -> Tekan tombol ``` EN (RST) ``` -> ``` Restart ```.

       • Jika ``` board ESP32 ``` tidak dapat memproses ``` Source Code ``` secara otomatis maka :<br>

      - Ketika informasi: ``` Uploading... ``` telah muncul -> segera tekan dan tahan tombol ``` BOOT ```.<br>

      - Ketika informasi: ``` Writing at .... (%) ``` telah muncul -> lepaskan tombol ``` BOOT ```.

       • Jika pesan: ``` Done Uploading ``` telah muncul -> ``` Program yang diisikan tadi sudah bisa dioperasikan ```.

       • Jangan tekan tombol ``` BOOT ``` dan ``` EN ``` secara bersamaan karena hal ini bisa beralih ke mode ``` Unggah Firmware ```.

    </td></tr></table><br>

11. Jika masih ada masalah saat unggah program, maka coba periksa pada bagian ``` driver ``` / ``` port ``` / ``` yang lainnya ```.

<br><br>

## Pengaturan io-t.net
1. Memulai io-t.net :

   <table><tr><td width="810">
      
      • Buka situs resminya di tautan berikut : <a href="https://io-t.net/">io-t.net</a>.
      
      • Jika anda belum memiliki akun, silakan <a href="https://i-ot.net/register">Daftar</a> terlebih dahulu -> aktivasi akun melalui email.
      
      • Jika anda sudah memiliki akun, silakan <a href="https://i-ot.net/login">Masuk</a> untuk dapat mengakses layanan io-t.net.

   </td></tr></table><br>

2. Buat node :

   <table><tr><td width="810">
      
      • Masuk ke menu ``` Instance ``` -> ``` Atur Node ```.
      
      • Lalu berikan nama yang unik pada node yang anda gunakan.

   </td></tr></table><br>

3. Buat device :

   <table><tr><td width="810">
      
      • Masuk ke menu ``` Devices ```.
   
      • Pilih ``` Tambah Devices ``` -> isi bagian ``` Client ID ```, ``` Access ```, ``` Topic ``` sesuai dengan kebutuhan. Contohnya :
      
      - ``` Client ID ``` -> ``` Phiotnet_v1 ```.
        
      - ``` Access ``` -> ``` Publish & Subscribe ```.
        
      - ``` Topic ``` -> ``` detect ```.

   </td></tr></table>
   
<br><br>

## Pengaturan Bot Telegram
1. Buka <a href="https://t.me/botfather">@BotFather</a>.<br><br>

2. Ketik ``` /newbot ```.<br><br>

3. Ketik nama bot yang diinginkan, contoh: ``` phiotnet_bot ```.<br><br>

4. Ketik nama pengguna bot yang diinginkan, contoh: ``` phiotnet_bot ```.<br><br>

5. Lakukan juga untuk pengaturan gambar bot, deskripsi bot, dan lain sebagainya menyesuaikan dengan kebutuhan anda.<br><br>

6. Salin ``` API token bot telegram anda ``` -> lalu tempelkan pada bagian ``` #define BOTtoken "YOUR_API_BOT_TOKEN" ```. 

   <table><tr><td width="810">
   Contohnya yaitu :<br><br>

   ```ino
   #define BOTtoken "2006772150:AAE6Fdjk3KbiySkzV6CLbd6ClJDzgTfJ5y0"
   ```

   </td></tr></table>

<br><br>

## Pengaturan Matlab
1. Buka ``` Matlab ```.<br><br>

2. Buka kotak dialog ``` Set Path ``` menggunakan perintah :
   
   <table><tr><td width="810">
      
   ```
   pathtool
   ```

   </td></tr></table>
   
   <img width="810" src="Assets/Documentation/Experiment/MATLAB Set Path.jpg" alt="set-path-matlab"><br><br>

3. Pilih ``` Add Folder... ``` -> cari folder ``` FIS-IT2FLS-Toolbox-MATLAB ``` -> ``` Select Folder ```.<br><br>

4. Klik ``` Save ``` dan kemudian klik ``` Close ```.<br><br>

5. Buka ``` IT2FL Toolbox ``` menggunakan perintah :
   
   <table><tr><td width="810">

   ```
   fuzzyt2
   ```

   </td></tr></table>
   
   <img width="810" src="Assets/Documentation/Experiment/IT2FL Toolbox.jpg" alt="it2fl-toolbox"><br><br>

6. Selebihnya tinggal anda atur sesuai dengan kebutuhan anda.

<br><br>
   
## Memulai
1. Unduh dan ekstrak repositori ini.<br><br>
   
2. Pastikan anda memiliki komponen elektronik yang diperlukan.<br><br>
   
3. Pastikan komponen anda telah dirancang sesuai dengan diagram.<br><br>
   
4. Konfigurasikan perangkat anda menurut pengaturan di atas.<br><br>

5. Selamat menikmati [Selesai].

<br><br>

## Demonstrasi Aplikasi
Via Telegram: <a href="https://t.me/phiotnet_bot">@phiotnet_bot</a>

<br><br>

## Sorotan
<table>
<tr>
<th width="280">Produk</th>
<th width="280">Sistem Pendukung Keputusan (SPK) IT2FL</th>
<th width="280">Bot Telegram</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Experiment/Product.jpg" alt="product"></td>
<td><img src="Assets/Documentation/Experiment/IT2FL Decision Support System.jpg" alt="it2fl-spk"></td>
<td><img src="Assets/Documentation/Experiment/Telegram Bot.jpg" alt="telegram-bot"></td>
</tr>
</table>

<br><br>
<b>Informasi lebih lanjut:</b><br>
<table><tr><td width="840">
   • Skripsi : <a href="http://repository.upnjatim.ac.id/id/eprint/7014"><u>Akses 1</u></a> atau <a href="https://www.academia.edu/127498955"><u>Akses 2</u></a><br><br>
   • Jurnal : <a href="https://publikasi.mercubuana.ac.id/index.php/Incomtech/article/view/15453"><u>Artikel 1</u></a> atau <a href="https://www.researchgate.net/publication/363660330"><u>Artikel 2</u></a>
</td></tr></table>

<br><br>

## <img src="https://github.com/user-attachments/assets/932b96eb-cbc7-42f1-8938-43cb431889a5" width="16" height="16"> Catatan
<ul>
<li>
   <strong><p>Saran Perbaikan Hardware :</p></strong>
   <table>
   <tr>
   <td width="20">1.</td>
   <td width="820">Catu daya pada rangkaian mikrokontroler dan aktuator itu perlu diatur ulang secara terpisah agar sistem dapat berfungsi dengan baik dan aman.</td>
   </tr>
   <tr>
   <td width="20">2.</td>
   <td width="820">Gunakan PSU standar dengan kapasitas 3A untuk menyuplai beberapa perangkat yang terpasang, misalnya aktuator.</td>
   </tr>
   <tr>
   <td width="20">3.</td>
   <td width="820">Tambahkan Step Down Converter untuk mendapatkan tegangan yang lebih stabil dan sesuai dengan kebutuhan perangkat. Dengan adanya komponen ini, maka tidak membutuhkan Arduino Uno.</td>
   </tr>
   <tr>
   <td width="20">4.</td>
   <td width="820">Ubah pengaturan Relay Elektromekanis 2-Channel dari NO (Normally Open) menjadi NC (Normally Close) untuk mengurangi panas berlebih.</td>
   </tr>
   <tr>
   <td width="20">5.</td>
   <td width="820">Tambahkan isolator pada komponen listrik untuk mencegah arus bocor.</td>
   </tr>
   <tr>
   <td width="20">6.</td>
   <td width="820">Tambahkan kipas atau ventilasi untuk meningkatkan aliran udara dan mencegah panas berlebih.</td>
   </tr>
   <tr>
   <td width="20">7.</td>
   <td width="820">Tambahkan Heat Sink pada komponen yang rentan panas.</td>
   </tr>
   <tr>
   <td width="20">8.</td>
   <td width="820">Tambahkan MCB (Miniature Circuit Breaker) untuk mencegah arus berlebih, sehingga perangkat tetap aman dan terlindungi.</td>
   </tr>
   <tr>
   <td width="20">9.</td>
   <td width="820">Tambahkan casing khusus untuk melindungi Probe Sensor pH dari kerusakan, terutama akibat benturan.</td>
   </tr>
   <tr>
   <td width="20">10.</td>
   <td width="820">Pertimbangkan untuk memilih lebih dari 1 Development Board untuk meningkatkan optimalisasi sistem.</td>
   </tr>
   <tr>
   <td width="20">11.</td>
   <td width="820">Pertimbangkan untuk mengganti Relay Elektromekanis 2-Channel dengan Relay SSR DD untuk memperoleh kendali yang lebih halus (tanpa noise), respon lebih cepat, konsumsi daya lebih rendah, efisiensi lebih tinggi, serta daya tahan lebih baik untuk penggunaan jangka panjang.</td>
   </tr>
   <tr>
   <td width="20">12.</td>
   <td width="820">Pertimbangkan untuk mengganti kotak akrilik dengan box panel standar agar perangkat yang ada jauh lebih aman dan rapi.</td>
   </tr>
   <tr>
   <td width="20">13.</td>
   <td width="820">Pertimbangkan untuk mengganti kabel sesuai dengan standar penggunaan. Untuk listrik DC, gunakan kabel AVS 1 x 0,5mm², yang lebih tahan lama dibandingkan kabel pita. Sementara itu, untuk listrik AC, gunakan kabel NYY-HY 2 x 1,5mm², karena lebih tahan terhadap air, cuaca, serta gangguan fisik seperti gigitan tikus.</td>
   </tr>
   </table>
</li><br>
<li>
   <strong><p>Saran Perbaikan Firmware :</p></strong>
   <table>
   <tr>
   <td width="20">1.</td>
   <td width="820">Optimalkan algoritma untuk mengurangi latensi pada proses pengambilan keputusan. Disarankan menggunakan RTOS (Real-Time Operating System) agar dapat mengatur lebih baik prioritas fungsi yang ada.</td>
   </tr>
   <tr>
   <td width="20">2.</td>
   <td width="820">Tambahkan metode OTA (Over The Air) untuk meningkatkan keamanan jaringan, termasuk Bot Telegram.</td>
   </tr>
   <tr>
   <td width="20">3.</td>
   <td width="820">Tambahkan EEPROM untuk menyimpan hasil kalibrasi sensor pH secara permanen, sehingga kalibrasi tidak perlu dituliskan di method loop() lagi. Hal ini dapat menghemat waktu dan meningkatkan efisiensi perangkat.</td>
   </tr>
   <tr>
   <td width="20">4.</td>
   <td width="820">Tambahkan pustaka ArduLite dan gunakan sintaksnya untuk meringankan beban ESP32, karena dapat mengurangi penggunaan memori ESP32. ArduLite ini sangat ideal untuk proyek-proyek dengan sumber daya terbatas yang mengutamakan efisiensi dan kesederhanaan. Tautan: https://github.com/ArduLite/ArduLite.</td>
   </tr>
   </table>
</li><br>
<li>
   <strong><p>Saran Peningkatan Fitur Otomatisasi :</p></strong>
   <table>
   <tr>
   <td width="20">1.</td>      
   <td width="820">Pompa otomatis yang diintegrasikan dengan sensor level untuk mengontrol pengisian cairan berupa pH dan AB Mix.</td>
   </tr>
   <tr>
   <td width="20">2.</td>      
   <td width="820">Pemberian pakan otomatis berbasis waktu untuk memberikan pakan secara terjadwal.</td>
   </tr>
   <tr>
   <td width="20">3.</td>      
   <td width="820">Pompa otomatis yang dikendalikan melalui bot telegram untuk mempermudah proses pengurasan dan pengisian air.</td>
   </tr>
   <tr>
   <td width="20">4.</td>      
   <td width="820">Pemantauan kualitas air pada kolam atau akuarium menggunakan perpaduan antara sensor pH, suhu air, dan amonia.</td>
   </tr>
   <tr>
   <td width="20">5.</td>      
   <td width="820">Penyinaran tanaman dengan lampu pertumbuhan untuk menumbuhkan tanaman secara optimal meski dalam kondisi yang minim cahaya (sebagai pengganti sinar matahari).</td>
   </tr>
   </table>
</li><br>
<li>
   <strong><p>Saran Optimalisasi Media Tanam :</p></strong>
   <table>
   <tr>
   <td width="20">1.</td>
   <td width="820">Tingkatkan jumlah modul hidroponik agar mampu menampung lebih banyak tanaman.</td>
   </tr>
   <tr>
   <td width="20">2.</td>
   <td width="820">Eksplorasi media tanam alternatif seperti arang sekam atau cocopeat untuk meningkatkan efisiensi pertumbuhan tanaman.</td>
   </tr>
   </table>
</li>
</ul>

<br><br>

## Apresiasi
Jika karya ini bermanfaat bagi anda, maka dukunglah karya ini sebagai bentuk apresiasi kepada penulis dengan mengklik tombol ``` ⭐Bintang ``` di bagian atas repositori.

<br><br>

## Penafian
Aplikasi ini merupakan hasil karya saya sendiri dan bukan merupakan hasil plagiat dari penelitian atau karya orang lain, kecuali yang berkaitan dengan layanan pihak ketiga yang meliputi: pustaka, kerangka kerja, dan lain sebagainya.

<br><br>

## LISENSI
LISENSI MIT - Hak Cipta © 2022 - Devan C. M. Wijaya, S.Kom

Dengan ini diberikan izin tanpa biaya kepada siapa pun yang mendapatkan salinan perangkat lunak ini dan file dokumentasi terkait perangkat lunak untuk menggunakannya tanpa batasan, termasuk namun tidak terbatas pada hak untuk menggunakan, menyalin, memodifikasi, menggabungkan, mempublikasikan, mendistribusikan, mensublisensikan, dan/atau menjual salinan Perangkat Lunak ini, dan mengizinkan orang yang menerima Perangkat Lunak ini untuk dilengkapi dengan persyaratan berikut:

Pemberitahuan hak cipta di atas dan pemberitahuan izin ini harus menyertai semua salinan atau bagian penting dari Perangkat Lunak.

DALAM HAL APAPUN, PENULIS ATAU PEMEGANG HAK CIPTA DI SINI TETAP MEMILIKI HAK KEPEMILIKAN PENUH. PERANGKAT LUNAK INI DISEDIAKAN SEBAGAIMANA ADANYA, TANPA JAMINAN APAPUN, BAIK TERSURAT MAUPUN TERSIRAT, OLEH KARENA ITU JIKA TERJADI KERUSAKAN, KEHILANGAN, ATAU LAINNYA YANG TIMBUL DARI PENGGUNAAN ATAU URUSAN LAIN DALAM PERANGKAT LUNAK INI, PENULIS ATAU PEMEGANG HAK CIPTA TIDAK BERTANGGUNG JAWAB, KARENA PENGGUNAAN PERANGKAT LUNAK INI TIDAK DIPAKSAKAN SAMA SEKALI, SEHINGGA RISIKO ADALAH MILIK ANDA SENDIRI.
