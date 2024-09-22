## Tahap Pertama: Menentukan nilai 𝑌, 𝑋, 𝑌², 𝑋², dan 𝑋𝑌

<img width="810" src="../Images/Calibration/1.png" alt="ph-probe-settings">

<br><br>

Pasang kabel jumper di bagian ``` Positif (+) ``` konektor BNC pH, lalu hubungkan ke bagian ``` Negatif (-) ``` konektor BNC pH. Hal ini sengaja dilakukan oleh penulis agar memudahkan kalibrasi. Selanjutnya, unggah kode program.

<table><tr><td width="810">
   
```ino
#define pHpin 35 // Pin GPIO 35 digunakan untuk sensor pH
int pHValue; // Variabel ini digunakan untuk menampung nilai pembacaan ADC
float voltage; // Variabel ini digunakan untuk menyimpan nilai pembacaan tegangan

void setup(){
   Serial.begin(115200); // Baudrate default untuk ESP32
   pinMode(pHpin, INPUT); // Inisialisasi pin sensor pH sebagai input
}

void loop(){
   pHValue = analogRead(pHpin); // Baca ADC sensor
   // ADC ESP32 => 4095 => 12 bit
   // Tegangan referensi => 5V
   voltage = pHValue * (5.0 / 4095.0); // Baca tegangan sensor murni
   Serial.println(voltage); // Cetak nilai tegangan ke Serial Monitor
   delay(1000); // Tunda selama 1 detik
}
```

</td></tr></table><br>

Putar potensiometer hingga output yang diinginkan itu tercapai (target: 2,5V). 2,5V ini diperoleh dari setengah 5V yang diasumsikan sebagai nilai ketetapan tegangan netral. Jika sudah stabil nilainya, maka lepaskan jumper yang ada di area konektor BNC pH tersebut. Selanjutnya, lakukan pengujian seperti langkah-langkah berikut :

<br>

• ``` Keadaan asam (𝑌=4) ```

<table><tr><td width="810">
   
   1. Sambungkan probe sensor ke konektor BNC.
   
   2. Celupkan probe sensor ke dalam air yang mengandung larutan asam.
      
   3. Tunggu hingga tegangan menjadi stabil.
      
   4. Silakan catat nilai tegangan (𝑋) yang dibaca oleh sensor tersebut.
      
   5. Selanjutnya tinggal mencari nilai 𝑌², 𝑋², dan 𝑋𝑌.
      
   6. Silakan hitung semua nilai dan taruh hasilnya ke dalam tabel.
   
</td></tr></table><br>

• ``` Keadaan netral (𝑌=7) ```

<table><tr><td width="810">
   
   1. Sambungkan probe sensor ke konektor BNC.
   
   2. Celupkan probe sensor ke dalam air yang netral.
      
   3. Tunggu hingga tegangan menjadi stabil.
      
   4. Silakan catat nilai tegangan (𝑋) yang dibaca oleh sensor tersebut.
      
   5. Selanjutnya tinggal mencari nilai 𝑌², 𝑋², dan 𝑋𝑌.
      
   6. Silakan hitung semua nilai dan taruh hasilnya ke dalam tabel.
   
</td></tr></table><br>

• ``` Keadaan basa (𝑌=10) ```

<table><tr><td width="810">
   
   1. Sambungkan probe sensor ke konektor BNC.
   
   2. Celupkan probe sensor ke dalam air yang mengandung larutan basa.
      
   3. Tunggu hingga tegangan menjadi stabil.
      
   4. Silakan catat nilai tegangan (𝑋) yang dibaca oleh sensor tersebut.
      
   5. Selanjutnya tinggal mencari nilai 𝑌², 𝑋², dan 𝑋𝑌.
      
   6. Silakan hitung semua nilai dan taruh hasilnya ke dalam tabel.
   
</td></tr></table><br>

Contoh perhitungannya dapat anda lihat sebagai berikut :

<img height="220" width="500" src="../Images/Calibration/2.png">

<br><br>

## Tahap Kedua: Mencari nilai 𝑎 dan 𝑏

Nilai yang sudah didapat dari tahap sebelumnya tinggal dimasukkan ke dalam persamaan ``` 𝑎 ``` dan ``` 𝑏 ```. Contoh perhitungannya seperti ini :

<img height="450" width="500" src="../Images/Calibration/3.png">
   <table><tr><td width="800" height="80">
   
   &nbsp;
   $\ a = \frac{\sum Y.\sum X^{2}-\sum X.\sum XY}{n.\sum X^{2}-(\sum X)^{2}} $
   <br><br>&nbsp;&nbsp;&nbsp;
   $\ = \frac{(21) . (24,46) - (8,45) . (55,67)}{(3) . (24,46) - (71,4)} = \frac{513,66 - 470,41}{73,38 -71,4} $
   <br><br>&nbsp;&nbsp;&nbsp;
   $\ = \frac{43,25}{1,98} = 21,84 $

   </td></tr></table>
   
<br><br>

Telah didapatkan ``` nilai 𝑎 ``` sebesar ``` 21,84 ``` dan ``` nilai 𝑏 ``` sebesar ``` -5,27 ```.

<br><br>

## Tahap Ketiga: Memasukkan Nilai 𝑎 dan 𝑏 ke dalam Persamaan Regresi Linier

``` Nilai 𝑎 ``` dan ``` nilai 𝑏 ``` tinggal dimasukkan ke dalam persamaan ``` regresi linear ``` sehingga menjadi :

   <table><tr><td width="800" height="80">

   $\ Y = 21,84+(-5,27 . X) $
         
   </td></tr></table>
   
<br><br>

Persamaan di atas bisa langsung digunakan untuk keperluan kalibrasi ``` sensor PH4502C ```.
