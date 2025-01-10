## Tahap Pertama: Menentukan nilai 𝑌, 𝑋, 𝑌², 𝑋², dan 𝑋𝑌

<img width="810" src="../Documentation/Experiment/PH4502C Calibration.png" alt="ph-probe-settings">

<br><br>

Pasang kabel jumper di bagian ``` Positif (+) ``` konektor BNC pH, lalu hubungkan ke bagian ``` Negatif (-) ``` konektor BNC pH. Hal ini sengaja dilakukan oleh penulis agar memudahkan kalibrasi. Selanjutnya, unggah kode program.

<table><tr><td width="810">
   
```ino
#define pHpin 35 // Pin GPIO 35 digunakan untuk sensor pH
int pHValue; // Variabel ini digunakan untuk menampung nilai pembacaan ADC
float voltage; // Variabel ini digunakan untuk menyimpan nilai pembacaan tegangan

void setup() {
   Serial.begin(115200); // Baudrate default untuk ESP32
   pinMode(pHpin, INPUT); // Inisialisasi pin sensor pH sebagai input
}

void loop() {
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

<table>
<tr height="70">
<th width="140">$\ n $</th>
<th width="140">$\ Y $</th>
<th width="140">$\ X $</th>
<th width="140">$\ Y^{2} $</th>
<th width="140">$\ X^{2} $</th>
<th width="140">$\ XY $</th>
</tr>
<tr align="center">
<td rowspan="3">3</td>
<td>4</td>
<td>3,4</td>
<td>16</td>
<td>11,56</td>
<td>13,6</td>
</tr>
   <tr align="center">
<td>7</td>
<td>2,81</td>
<td>49</td>
<td>7,89</td>
<td>19,67</td>
</tr>
   <tr align="center">
<td>10</td>
<td>2,24</td>
<td>100</td>
<td>5,01</td>
<td>22,4</td>
</tr>
   <tr align="center">
<td>$\ \sum $</td>
<td>21</td>
<td>8,45</td>
<td>165</td>
<td>24,46</td>
<td>55,67</td>
</tr>
</table>

<br><br>

## Tahap Kedua: Mencari nilai 𝑎 dan 𝑏

Nilai yang sudah didapat dari tahap sebelumnya tinggal dimasukkan ke dalam persamaan ``` 𝑎 ``` dan ``` 𝑏 ```. Contoh perhitungannya seperti ini :

   <table><tr><td width="800" height="80">
   
   &nbsp;
   $\ a = \frac{\sum Y.\sum X^{2}-\sum X.\sum XY}{n.\sum X^{2}-(\sum X)^{2}} $
   <br><br>&nbsp;&nbsp;&nbsp;
   $\ = \frac{(21) . (24,46) - (8,45) . (55,67)}{(3) . (24,46) - (71,4)} = \frac{513,66 - 470,41}{73,38 - 71,4} $
   <br><br>&nbsp;&nbsp;&nbsp;
   $\ = \frac{43,25}{1,98} = 21,84 $
   <br><br><br><br>
   &nbsp;
   $\ b = \frac{n.\sum XY-\sum X.\sum Y}{n.\sum X^{2}-(\sum X)^{2}} $
   <br><br>&nbsp;&nbsp;&nbsp;
   $\ = \frac{(3) . (55,67) - (8,45) . (21)}{(3) . (24,46) - (71,4)} = \frac{167,01 - 177,45}{73,38 - 71,4} $
   <br><br>&nbsp;&nbsp;&nbsp;
   $\ = \frac{-10,44}{1,98} = -5,27 $

   </td></tr></table><br>

Telah didapatkan ``` nilai 𝑎 ``` sebesar ``` 21,84 ``` dan ``` nilai 𝑏 ``` sebesar ``` -5,27 ```.

<br><br>

## Tahap Ketiga: Memasukkan Nilai 𝑎 dan 𝑏 ke dalam Persamaan Regresi Linier

``` Nilai 𝑎 ``` dan ``` nilai 𝑏 ``` tinggal dimasukkan ke dalam persamaan ``` regresi linear ``` sehingga menjadi :

   <table><tr><td width="800" height="80">

   $\ Y = 21,84+(-5,27 . X) $
         
   </td></tr></table><br>

Persamaan di atas bisa langsung digunakan untuk keperluan kalibrasi ``` sensor PH4502C ```.
