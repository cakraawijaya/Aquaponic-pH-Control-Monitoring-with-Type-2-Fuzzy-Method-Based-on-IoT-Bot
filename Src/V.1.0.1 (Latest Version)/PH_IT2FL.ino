//============================================================ Deklarasi Library ===========================================================
#include <WiFi.h> //Pemanggilan Library WiFi
#include <PubSubClient.h> //Pemanggilan Library PubSubClient
#include <LiquidCrystal_I2C.h> //Pemanggilan Library LiquidCrystal_I2C
#include <RTClib.h> //Pemanggilan Library RTClib
#include <CTBot.h> //Pemanggilan Library CTBot


//======================================================= Inisialisasi: Constructor ========================================================
WiFiClient espClient; //Constructor WiFiClient
PubSubClient client(espClient); //Constructor PubSubClient
LiquidCrystal_I2C lcd(0x27, 16, 2); //Constructor LiquidCrystal_I2C
RTC_DS3231 rtc; //Constructor RTC_DS3231
CTBot myBot; //Constructor CTBot
CTBotReplyKeyboard myKbd, submainKbd, sub1Kbd, sub2Kbd, sub3Kbd; //Constructor CTBotReplyKeyboard
CTBotInlineKeyboard InKbd, In3Kbd1, In3Kbd2, In3Kbd3, In3Kbd4, In3Kbd5, In3Kbd6, InNULL; //Constructor CTBotInlineKeyboard


//===================================================== Deklarasi Variabel: Tipe Data ======================================================
//Tipe data Char
char payload_Publish[4];
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"}; 

//Tipe data Float
float adc_phSensor, x, a, b;
float y, old_pHValue = 0, pHValue;
float pHair_Upper, pHair_Lower;
float AKU, AKL, ALU, ALL, NU, NL, BLU, BLL, BKU, BKL;
float SigyiMiuMFUpper, SigyiMiuMFLower, SigMiuMFUpper, SigMiuMFLower, yl, yr;
float MiuUMF[5], MiuLMF[5];
float payload_Subscribe;

//Tipe data Int
int i, yi, ycos, yout, Tarray1, Tarray2; 
int SPK[5]; 
int tanggal, bulan, tahun; 

//Tipe data String
String statusPH, statusBuzzer, statusRelaypH; 
String hari, waktu;
String rp1, rp2, sendMsg, statusKendaliIoT;

//Tipe data Boolean 
bool relayON = LOW;
bool relayOFF = HIGH;
bool ispHUpOn = false;
bool ispHDownOn = false;
bool isLcdOn = false;
bool isBuzzerOn = false;
bool ispHUp10SecondActive = false;
bool ispHUp25SecondActive = false;
bool ispHDown10SecondActive = false;
bool ispHDown25SecondActive = false;
bool isLcdLoadingActive = false;
bool isLcdpHValueActive = false;
bool isLcdAllpHONActive = false;
bool isLcdAllpHOFFActive = false;
bool isLcdpHUpONActive = false;
bool isLcdpHUpOFFActive = false;
bool isLcdpHDownONActive = false;
bool isLcdpHDownOFFActive = false;
bool isBuzzer2XFinished = false;
bool isBuzzer3XFinished = false;
bool isBuzzerActive = false;
bool viewTombol;

//Tipe data Unsigned
unsigned long currentMillis;
unsigned long startTime = 0;
unsigned long svalveStartTime1 = 0;
unsigned long svalveStartTime2 = 0;
unsigned long lcdStartTime = 0;
unsigned long buzzerStartTime = 0;
const unsigned long delayTime1 = 1000;
const unsigned long delayTime2 = 5000;
const unsigned long svalveDuration1 = 10000;
const unsigned long svalveDuration2 = 25000;


//============================================================= Define Variabel ============================================================
//Perangkat
#define PBuzzer 2 //Pin Kaki Piezo Buzzer
#define PoPin 35 //Pin Kaki pH Sensor (Po)
#define SValve1 5 //Pin Kaki pH Up
#define SValve2 18 //Pin Kaki pH Down

//Koneksi
#define ssid "YOUR_WIFI_NAME" //Nama wifi router
#define password "YOUR_WIFI_PASSWORD" //Password wifi router
#define mqtt_server "io-t.net" //Nama Platform IoT (Broker)
#define mqtt_port 1883 //Port Io-t.net
#define mqtt_username "YOUR_IOTNET_USERNAME" //Username Io-t.net
#define mqtt_password "YOUR_IOTNET_PASSWORD" //Password Io-t.net
#define mqtt_clientID "YOUR_IOTNET_CLIENTID" //Client ID Io-t.net
#define Topic "detect" //Topic MQTT : detect pH

//Bot Telegram
#define BOTtoken "YOUR_API_BOT_TOKEN" //API bot telegram
#define INrespYes "INrespYes" //Callback Inline Respon Iya ke-1 
#define INrespYes1 "INrespYes1" //Callback Inline Respon Iya ke-2 
#define INrespYes2 "INrespYes2" //Callback Inline Respon Iya ke-3
#define INrespYes3 "INrespYes3" //Callback Inline Respon Iya ke-4 
#define INrespYes4 "INrespYes4" //Callback Inline Respon Iya ke-5
#define INrespYes5 "INrespYes5" //Callback Inline Respon Iya ke-6
#define INrespYes6 "INrespYes6" //Callback Inline Respon Iya ke-7
#define INrespNo "INrespNo" //Callback Inline Respon Tidak ke-1  
#define INrespNo1 "INrespNo1" //Callback Inline Respon Tidak ke-2
#define INrespNo2 "INrespNo2" //Callback Inline Respon Tidak ke-3 
#define INrespNo3 "INrespNo3" //Callback Inline Respon Tidak ke-4


//============================================================== Method Setup ===============================================================
void setup() {
  RELAYinit(); //Memanggil method RELAYinit
  LCDinit(); //Memanggil method LCDinit
  Serial.begin(9600); //Memulai komunikasi serial dengan baud rate 9600
  connectWiFi(); //Memanggil method connectWiFi
  connectIoT(); //Memanggil method connectIoT (i-ot.net)
  connectBot(); //Memanggil method connectBot (Bot Telegram)
  ButtonBot(); //Memanggil method Tombol Custom pada Bot Telegram
  RTCinit(); //Memanggil method RTCinit
  lcdLoading(); //Memanggil method lcdLoading
  pinMode(PBuzzer, OUTPUT); //Inisialisasi pin sebagai OUTPUT
  digitalWrite(PBuzzer, LOW); //Default buzzer untuk pertama kali harus off

  //Atur Start Time
  startTime = millis();
  svalveStartTime1 = millis() - svalveDuration1;
  svalveStartTime2 = millis() - svalveDuration2;
  lcdStartTime = millis();
  buzzerStartTime = millis();
}


//============================================================== Method Loop ===============================================================
void loop() {
  //Ambil waktu saat ini
  currentMillis = millis();
  
  //Pertahankan koneksi IoT
  if (!client.connected()) { reconnect(); }
  client.loop();

  //Jika waktu sekarang dikurangi waktu terakhir lebih besar dari 1 detik maka :
  if ((currentMillis - startTime) > delayTime1) {
    readPHandControl(); //Memanggil method readPHandControl
    botTelegram(); //Memanggil method botTelegram
    startTime = currentMillis; //Perbarui waktu terakhir dijalankan
  }

  millisFlowControl(); //Kontrol respon millis
}


//============================================================= Method LCD Init ============================================================
void LCDinit() {
  lcd.init(); //Memulai komunikasi serial dengan LCD
  lcd.backlight(); //Mengaktifkan lampu latar (backlight) pada layar LCD
  lcd.clear(); lcd.setCursor(1,0); lcd.print("Memulai"); lcd.setCursor(1,1); lcd.print("Sistem pH..."); delay(1000); //Start LCD
  lcd.clear(); lcd.setCursor(1,0); lcd.print("Welcome to"); lcd.setCursor(1,1); lcd.print("PHIOTNET...."); delay(1000); //Welcome LCD
}


//============================================================ Method RTC Init =============================================================
void RTCinit() {
  rtc.begin(); //Memulai komunikasi serial dengan RTC
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Pengaturan DateTime
}


//============================================================ Method RELAY Init ===========================================================
void RELAYinit() {
  pinMode(SValve1, OUTPUT); //Inisialisasi pin sebagai output
  pinMode(SValve2, OUTPUT); //Inisialisasi pin sebagai output
  all_pH_off(); //Default relay untuk pertama kali harus off
}


//========================================================== Method Konfigurasi WiFi =======================================================
void connectWiFi() {
  Serial.println("\n==================================================================================");
  Serial.print("[Konfigurasi Wi-Fi]\nmencoba menghubungkan ke Wi-Fi : "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("\nstatus :\nWi-Fi berhasil tersambung");
  Serial.println(WiFi.localIP());
  
  WiFi.setAutoReconnect(true); //Menyambungkan kembali secara otomatis setelah sambungan terputus
  WiFi.persistent(true); //Menyambungkan kembali ke Access Point
  delay(1000);
}


//============================================================= Method Koneksi IoT =========================================================
void connectIoT() {
  Serial.print("\n[Konfigurasi IoT]\nmencoba menghubungkan ke Platform : "); 
  Serial.println(mqtt_server);
  client.setServer(mqtt_server, mqtt_port); 
  client.setCallback(receivedCallback);
}


//==================================================== Method Menghubungkan Ulang Jaringan =================================================
void reconnect() {
  while (!client.connected()) {        
    if (client.connect(mqtt_clientID, mqtt_username, mqtt_password)) {
      Serial.println("\nstatus :"); Serial.print(mqtt_server);
      Serial.println(" berhasil tersambung");  
      client.subscribe(Topic);
    } 
    else {
      Serial.println("\nstatus :"); Serial.print(mqtt_server);
      Serial.print(" gagal tersambung (" + String(client.state()) + ")\nmenyambungkan kembali");
      lcdFailIoT(); //Memanggil method lcdFailIoT
      while (!client.connect(mqtt_clientID, mqtt_username, mqtt_password)) {
        delay(500);
        Serial.print(".");
      }
      delay(1000);
    }
  } 
}


//===================================================== Method Pemanggilan Topik Subscribe =================================================
void receivedCallback(char* topic, byte* payload, unsigned int length) {  
  char message[length + 1]; //Membuat variable array untuk menampung data payload
  for (i = 0; i < length; i++) { message[i] = (char)payload[i]; } //Menampung data payload
  message[length] = '\0'; //Null terminator
  payload_Subscribe = atof(message); //Ubah string ke float dan masukkan ke variabel payload_Subscribe
}


//====================================================== Method Debugging untuk Subscribe ==================================================
void debuggingSubscribe() {
  if (payload_Subscribe != 0) {
    Serial.println("\n[Pemeriksaan Subscribe MQTT]"); 
    Serial.println("Payload: " + String(payload_Subscribe));
    Serial.println("\n==================================================================================");
  }
}


//====================================================== Method Konfigurasi Bot Telegram ===================================================
void connectBot() {
  myBot.setTelegramToken(BOTtoken);
  myBot.wifiConnect(ssid, password); 
  myBot.setMaxConnectionRetries(5);
  Serial.println("\n[Konfigurasi Bot Telegram]\nmencoba menghubungkan ke : phiotnet_bot"); 

  if (myBot.testConnection()) {
    Serial.println("\nstatus :\nbot telegram berhasil tersambung"); 
  } else { 
    Serial.print("\nstatus :\nbot telegram gagal tersambung\nmenyambungkan kembali"); 
    lcdFailBot(); //Memanggil method lcdFailBot
    while (!myBot.testConnection()) { 
      delay(1000);
      Serial.print(".");
    }
  } delay(1000); 
  
  Serial.print("==================================================================================\n\n");
}


//========================================================== Method View DateTime ==========================================================
void DTnow() {
  DateTime now = rtc.now(); //Membuat objek baru: now untuk menampung method RTC
  hari = dataHari[now.dayOfTheWeek()]; //Hari
  tanggal = now.day(), DEC; bulan = now.month(), DEC; tahun = now.year(), DEC; //DD-MM-YYYY
  waktu = String() + hari + ", " + tanggal + "-" + bulan + "-" + tahun; //Waktu
}


//====================================================== Method Millis Flow Control ======================================================
void millisFlowControl() {
  //Matikan pH Up jika masih aktif
  if (ispHUpOn) {
    //Jika pH Up telah aktif selama 10 detik, maka :
    if (ispHUp10SecondActive && (currentMillis - svalveStartTime1) >= svalveDuration1) {
      autopHUp10SecondOFF(); //Matikan relay pH Up
    }
    //Jika pH Up telah aktif selama 25 detik, maka :
    if (ispHUp25SecondActive && (currentMillis - svalveStartTime2) >= svalveDuration2) {
      autopHUp25SecondOFF(); //Matikan relay pH Up
    }
  }

  //Matikan pH Down jika masih aktif
  if (ispHDownOn) {
    //Jika pH Down telah aktif selama 10 detik, maka :
    if (ispHDown10SecondActive && (currentMillis - svalveStartTime1) >= svalveDuration1) {
      autopHDown10SecondOFF(); //Matikan relay pH Down
    }
    //Jika pH Down telah aktif selama 25 detik, maka :
    if (ispHDown25SecondActive && (currentMillis - svalveStartTime2) >= svalveDuration2) {
      autopHDown25SecondOFF(); //Matikan relay pH Down
    }
  }

  //Matikan LCD jika masih aktif
  if (isLcdOn) {
    //Jika status Loading sudah ditampilkan selama 5 detik, maka :
    if (isLcdLoadingActive && (currentMillis - lcdStartTime) >= delayTime2) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdLoadingActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
    //Jika status Nilai pH sudah ditampilkan selama 1 detik, maka :
    if (isLcdpHValueActive && (currentMillis - lcdStartTime) >= delayTime1) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdpHValueActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
    //Jika status All-pH ON sudah ditampilkan selama 5 detik, maka :
    if (isLcdAllpHONActive && (currentMillis - lcdStartTime) >= delayTime2) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdAllpHONActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
    //Jika status All-pH OFF sudah ditampilkan selama 5 detik, maka :
    if (isLcdAllpHOFFActive && (currentMillis - lcdStartTime) >= delayTime2) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdAllpHOFFActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
    //Jika status pH-Up ON sudah ditampilkan selama 5 detik, maka :
    if (isLcdpHUpONActive && (currentMillis - lcdStartTime) >= delayTime2) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdpHUpONActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
    //Jika status pH-Up OFF sudah ditampilkan selama 5 detik, maka :
    if (isLcdpHUpOFFActive && (currentMillis - lcdStartTime) >= delayTime2) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdpHUpOFFActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
    //Jika status pH-Down ON sudah ditampilkan selama 5 detik, maka :
    if (isLcdpHDownONActive && (currentMillis - lcdStartTime) >= delayTime2) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdpHDownONActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
    //Jika status pH-Down OFF sudah ditampilkan selama 5 detik, maka :
    if (isLcdpHDownOFFActive && (currentMillis - lcdStartTime) >= delayTime2) {
      lcd.clear(); //Hapus layar LCD
      isLcdOn = false; //Perbarui status LCD
      isLcdpHDownOFFActive = false; //Tandai fungsi millis bahwa LCD sudah selesai
      lcdWaiting(); //Memanggil method lcdWaiting
    }
  }

  //Jika buzzer diketahui belum aktif, maka :
  if (isBuzzerActive) {
    if (!isBuzzer2XFinished) { B2(); } //Nyalakan sebanyak 2X
    if (!isBuzzer3XFinished) { B3(); } //Nyalakan sebanyak 3X
  }
}


//======================================================= Method Read pH and Control =======================================================
void readPHandControl() {
  adc_phSensor = analogRead(PoPin); //Membaca ADC Sensor pH
  x = adc_phSensor * (5.0 / 4095.0); //Nilai tegangan murni
  a = 21.84; b = -5.27; //Linear Regression Value
  y = a + b * x; //pH Value

  //Set point atas dan bawah
  if (y > 14.00) { y = 14.00; } 
  else if (y < 0.00) { y = 0.00; }
  
  pHValue = y; //Menyimpan nilai ke variabel pHValue
  Alarm_pH(); //Memanggil method Alarm_pH

  //Cek nilai pH ada perubahan atau tidak, jika ada perubahan maka:
  if (pHValue != old_pHValue) {
    IT2FL_pH(); //Memanggil method IT2FL_pH
    dtostrf(pHValue, 4, 2, payload_Publish); //Float -> String 
    client.publish(Topic, payload_Publish, true); //Publish topik beserta payloadnya menggunakan retain message
    // debuggingSubscribe(); //Memanggil method debuggingSubscribe => Jika tidak digunakan sebaiknya dibuat komentar saja    
    old_pHValue = pHValue; //Menyimpan nilai pH saat ini ke variabel old_pHValue
  }
}


//============================================================ Method Output LCD ===========================================================
void lcdFailIoT() {
  lcd.clear(); lcd.setCursor(1,0); lcd.print("IoT Gagal"); lcd.setCursor(1,1); lcd.print("Tersambung..."); //Cetak ke layar LCD
  delay(5000); //Jeda 5 detik
}
void lcdFailBot() {
  lcd.clear(); lcd.setCursor(1,0); lcd.print("Bot Gagal"); lcd.setCursor(1,1); lcd.print("Tersambung...");  //Cetak ke layar LCD
  delay(5000); //Jeda 5 detik
}
void lcdWaiting() {
  lcd.clear(); lcd.setCursor(1,0); lcd.print("Menunggu"); lcd.setCursor(1,1); lcd.print("Perintah...");  //Cetak ke layar LCD
  delay(1000); //Jeda 1 detik
}
void lcdLoading() {
  //Jika status Loading belum ditampilkan sebelumnya, maka :
  if (!isLcdLoadingActive) {
    lcd.clear(); lcd.setCursor(1,0); lcd.print("Loading...."); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdLoadingActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}
void lcdpHValue() {
  //Jika status Nilai pH belum ditampilkan sebelumnya, maka :
  if (!isLcdpHValueActive) {
    lcd.clear(); lcd.setCursor(2,0); lcd.print("pH Air : "+ String(payload_Subscribe)); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdpHValueActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}
void lcdAllpHON() {
  //Jika status All-pH ON belum ditampilkan sebelumnya, maka :
  if (!isLcdAllpHONActive) {
    lcd.clear(); lcd.setCursor(4,0); lcd.print("All pH :"); lcd.setCursor(6,1); lcd.print("(ON)"); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdAllpHONActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}
void lcdAllpHOFF() {
  //Jika status All-pH OFF belum ditampilkan sebelumnya, maka :
  if (!isLcdAllpHOFFActive) {
    lcd.clear(); lcd.setCursor(4,0); lcd.print("All pH :"); lcd.setCursor(5,1); lcd.print("(OFF)"); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdAllpHOFFActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}
void lcdpHUpON() {
  //Jika status pH-Up ON belum ditampilkan sebelumnya, maka :
  if (!isLcdpHUpONActive) {
    lcd.clear(); lcd.setCursor(4,0); lcd.print("pH Up :"); lcd.setCursor(6,1); lcd.print("(ON)"); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdpHUpONActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}
void lcdpHUpOFF() {
  //Jika status pH-Up OFF belum ditampilkan sebelumnya, maka :
  if (!isLcdpHUpOFFActive) {
    lcd.clear(); lcd.setCursor(4,0); lcd.print("pH Up :"); lcd.setCursor(5,1); lcd.print("(OFF)"); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdpHUpOFFActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}
void lcdpHDownON() {
  //Jika status pH-Down ON belum ditampilkan sebelumnya, maka :
  if (!isLcdpHDownONActive) {
    lcd.clear(); lcd.setCursor(4,0); lcd.print("pH Down:"); lcd.setCursor(6,1); lcd.print("(ON)"); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdpHDownONActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}
void lcdpHDownOFF() {
  //Jika status pH-Down OFF belum ditampilkan sebelumnya, maka :
  if (!isLcdpHDownOFFActive) {
    lcd.clear(); lcd.setCursor(4,0); lcd.print("pH Down:"); lcd.setCursor(6,1); lcd.print("(OFF)"); //Cetak ke layar LCD
    lcdStartTime = currentMillis; //Perbarui waktu terakhir ketika LCD dinyalakan
    isLcdOn = true; //Perbarui status LCD
    isLcdpHDownOFFActive = true; //Tandai fungsi millis bahwa LCD aktif
  }
}


//========================================================= Method Output Relay pH =======================================================
//Method pH Up On 25 detik -> dengan fungsi millis
void autopHUp25SecondON() {
  //Jika Valve pH Up belum menyala 25 detik, maka :
  if (!ispHUp25SecondActive) {
    pH_up_on(); //Memanggil fungsi untuk menyalakan pH Up
    svalveStartTime2 = currentMillis; //Perbarui waktu terakhir ketika pH Up dinyalakan
    ispHUpOn = true; //Perbarui status pH Up
    ispHUp25SecondActive = true; //Tandai fungsi millis bahwa pH Up aktif
  }
}
void autopHUp25SecondOFF() {
  pH_up_off(); //Memanggil fungsi untuk mematikan pH Up
  ispHUp25SecondActive = false; //Tandai fungsi millis bahwa pH Up 25 detik sudah selesai
  ispHUpOn = ispHUp10SecondActive; //Tetap ON jika pH Up 10 detik masih aktif
}

//Method pH Up On 10 detik -> dengan fungsi millis
void autopHUp10SecondON() {
  //Jika Valve pH Up belum menyala 10 detik, maka :
  if (!ispHUp10SecondActive) {
    pH_up_on(); //Memanggil fungsi untuk menyalakan pH Up
    svalveStartTime1 = currentMillis; //Perbarui waktu terakhir ketika pH Up dinyalakan
    ispHUpOn = true; //Perbarui status pH Up
    ispHUp10SecondActive = true; //Tandai fungsi millis bahwa pH Up aktif
  }
}
void autopHUp10SecondOFF() {
  pH_up_off(); //Memanggil fungsi untuk mematikan pH Up
  ispHUp10SecondActive = false; //Tandai fungsi millis bahwa pH Up 10 detik sudah selesai
  ispHUpOn = ispHUp25SecondActive; //Tetap ON jika pH Up 25 detik masih aktif
}

void pH_up_on() { //Method pH Up on : On/Off Controller
  digitalWrite(SValve1, relayON);    //Nyalakan Solenoid Valve 1
}
void pH_up_off() { //Method pH Up off : On/Off Controller
  digitalWrite(SValve1, relayOFF);   //Matikan Solenoid Valve 1
}
void all_pH_on() { //Method pH Up dan pH Down on : On/Off Controller
  digitalWrite(SValve1, relayON); digitalWrite(SValve2, relayON);     //Seluruh Solenoid Valve pH menyala
}
void all_pH_off() { //Method pH Up dan pH Down off : On/Off Controller
  digitalWrite(SValve1, relayOFF); digitalWrite(SValve2, relayOFF);   //Seluruh Solenoid Valve pH mati
}
void pH_down_on() { //Method pH Down on : On/Off Controller
  digitalWrite(SValve2, relayON);    //Nyalakan Solenoid Valve 2
}
void pH_down_off() { //Method pH Down off : On/Off Controller
  digitalWrite(SValve2, relayOFF);   //Matikan Solenoid Valve 2
}

//Method pH Down On 10 detik -> dengan fungsi millis
void autopHDown10SecondOFF() {
  pH_down_off(); //Memanggil fungsi untuk mematikan pH Down
  ispHDown10SecondActive = false; //Tandai fungsi millis bahwa pH Down 10 detik sudah selesai
  ispHDownOn = ispHDown25SecondActive; //Tetap ON jika pH Down 25 detik masih aktif
}
void autopHDown10SecondON() {
  //Jika Valve pH Down belum menyala 10 detik, maka :
  if (!ispHDown10SecondActive) {
    pH_down_on(); //Memanggil fungsi untuk menyalakan pH Down
    svalveStartTime1 = currentMillis; //Perbarui waktu terakhir ketika pH Down dinyalakan
    ispHDownOn = true; //Perbarui status pH Down
    ispHDown10SecondActive = true; //Tandai fungsi millis bahwa pH Down aktif
  }
}

//Method pH Down On 25 detik -> dengan fungsi millis
void autopHDown25SecondOFF() {
  pH_down_off(); //Memanggil fungsi untuk mematikan pH Down
  ispHDown25SecondActive = false; //Tandai fungsi millis bahwa pH Down 25 detik sudah selesai
  ispHDownOn = ispHDown10SecondActive; //Tetap ON jika pH Down 10 detik masih aktif
}
void autopHDown25SecondON() {
  //Jika Valve pH Down belum menyala 25 detik, maka :
  if (!ispHDown25SecondActive) {
    pH_down_on(); //Memanggil fungsi untuk menyalakan pH Down
    svalveStartTime2 = currentMillis; //Perbarui waktu terakhir ketika pH Down dinyalakan
    ispHDownOn = true; //Perbarui status pH Down
    ispHDown25SecondActive = true; //Tandai fungsi millis bahwa pH Down aktif
  }
}


//============================================================= Method Alarm =============================================================
void B2(){ //Method alarm 2x bunyi : On/Off Controller
  //Jika waktu pada buzzer sudah memenuhi durasi, maka :
  if ((currentMillis - buzzerStartTime) >= delayTime1) { 
    if (i < 2) { //Pastikan bunyi belum mencapai 2 kali
      isBuzzerOn = !isBuzzerOn; //Pertukaran status buzzer
      digitalWrite(PBuzzer, isBuzzerOn ? HIGH : LOW); //Nyalakan atau Matikan buzzer
      if (!isBuzzerOn) { //Jika buzzer baru saja mati
        i++; //Increment
      }
      buzzerStartTime = currentMillis; //Perbarui waktu terakhir ketika buzzer dijalankan
    } else {
      digitalWrite(PBuzzer, LOW); //Matikan buzzer
      isBuzzer2XFinished = true; //Tandai buzzer selesai
      isBuzzerActive = false; //Matikan buzzer setelah selesai
      i = 0; //Reset hitungan untuk alarm berikutnya
    }
  }
} 
void B3(){ //Method alarm 3x bunyi : On/Off Controller
  //Jika waktu pada buzzer sudah memenuhi durasi, maka :
  if ((currentMillis - buzzerStartTime) >= delayTime1) { 
    if (i < 3) { //Pastikan bunyi belum mencapai 3 kali
      isBuzzerOn = !isBuzzerOn; //Pertukaran status buzzer
      digitalWrite(PBuzzer, isBuzzerOn ? HIGH : LOW); //Nyalakan atau Matikan buzzer
      if (!isBuzzerOn) { //Jika buzzer baru saja mati
        i++; //Increment
      }
      buzzerStartTime = currentMillis; //Perbarui waktu terakhir ketika buzzer dijalankan
    } else {
      digitalWrite(PBuzzer, LOW); //Matikan buzzer
      isBuzzer3XFinished = true; //Tandai buzzer selesai
      isBuzzerActive = false; //Matikan buzzer setelah selesai
      i = 0; //Reset hitungan untuk alarm berikutnya
    }
  }
} 
void Alarm_pH() { //Alarm Peringatan berdasarkan nilai pH
  if (pHValue >= 0.00 && pHValue < 4.00) {
    //Buzzer menyala selama 3X dalam interval jeda 1 detik
    isBuzzer3XFinished = false; isBuzzer2XFinished = true; isBuzzerActive = true;
  } else if (pHValue >= 4.00 && pHValue < 6.00) {
    //Buzzer menyala selama 2X dalam interval jeda 1 detik
    isBuzzer3XFinished = true; isBuzzer2XFinished = false; isBuzzerActive = true;
  } else if (pHValue >= 8.00 && pHValue < 11.00) {
    //Buzzer menyala selama 2X dalam interval jeda 1 detik
    isBuzzer3XFinished = true; isBuzzer2XFinished = false; isBuzzerActive = true;
  } else if (pHValue >= 11.00 && pHValue <= 14.00) {
    //Buzzer menyala selama 3X dalam interval jeda 1 detik
    isBuzzer3XFinished = false; isBuzzer2XFinished = true; isBuzzerActive = true;
  }
}


//====================================================== Method Button Bot Telegram ======================================================
void ButtonBot() {
  //Button Menu Utama
  myKbd.addButton("👁 Monitoring pH");
  myKbd.addRow();
  myKbd.addButton("🚰 Pengaturan pH");
  myKbd.addButton("🤖 Bantuan Bot");
  myKbd.enableResize();
  
  //Button Respon Menu Pengaturan pH
  submainKbd.addButton("🧪 All-pH");
  submainKbd.addButton("🧪 pH-Up");
  submainKbd.addButton("🧪 pH-Down");
  submainKbd.addRow();
  submainKbd.addButton("⬅️ Kembali");
  submainKbd.enableResize();
  
  //Button Respon Sub Menu All-pH
  sub1Kbd.addButton("1️⃣ All-pH ON");
  sub1Kbd.addButton("2️⃣ All-pH OFF");
  sub1Kbd.addRow();
  sub1Kbd.addButton("↩️ Kembali");
  sub1Kbd.enableResize();

  //Button Respon Sub Menu pH-Up
  sub2Kbd.addButton("1️⃣ pH-Up ON");
  sub2Kbd.addButton("2️⃣ pH-Up OFF");
  sub2Kbd.addRow();
  sub2Kbd.addButton("↩️ Kembali");
  sub2Kbd.enableResize();

  //Button Respon Sub Menu pH-Down
  sub3Kbd.addButton("1️⃣ pH-Down ON");
  sub3Kbd.addButton("2️⃣ pH-Down OFF");
  sub3Kbd.addRow();
  sub3Kbd.addButton("↩️ Kembali");
  sub3Kbd.enableResize();

  viewTombol = false; //Tombol -> default : hidden

  //[Menu Utama] : Inline Button Respon Menu Bantuan Bot
  InKbd.addButton("✅ Ya", INrespYes, CTBotKeyboardButtonQuery);
  InKbd.addButton("❌ Tidak", INrespNo, CTBotKeyboardButtonQuery);

  //[Sub Menu 1] : Inline Button Respon Sub Menu All-pH ON
  In3Kbd1.addButton("✅ Ya", INrespYes1, CTBotKeyboardButtonQuery);
  In3Kbd1.addButton("❌ Tidak", INrespNo1, CTBotKeyboardButtonQuery);
  //Inline Button Respon Sub Menu All-pH OFF
  In3Kbd2.addButton("✅ Ya", INrespYes2, CTBotKeyboardButtonQuery);
  In3Kbd2.addButton("❌ Tidak", INrespNo1, CTBotKeyboardButtonQuery);

  //[Sub Menu 2] : Inline Button Respon Sub Menu pH-Up ON
  In3Kbd3.addButton("✅ Ya", INrespYes3, CTBotKeyboardButtonQuery);
  In3Kbd3.addButton("❌ Tidak", INrespNo2, CTBotKeyboardButtonQuery);
  //Inline Button Respon Sub Menu pH-Up OFF
  In3Kbd4.addButton("✅ Ya", INrespYes4, CTBotKeyboardButtonQuery);
  In3Kbd4.addButton("❌ Tidak", INrespNo2, CTBotKeyboardButtonQuery);

  //[Sub Menu 3] : Inline Button Respon Sub Menu pH-Down ON
  In3Kbd5.addButton("✅ Ya", INrespYes5, CTBotKeyboardButtonQuery);
  In3Kbd5.addButton("❌ Tidak", INrespNo3, CTBotKeyboardButtonQuery);
  //Inline Button Respon Sub Menu pH-Down OFF
  In3Kbd6.addButton("✅ Ya", INrespYes6, CTBotKeyboardButtonQuery);
  In3Kbd6.addButton("❌ Tidak", INrespNo3, CTBotKeyboardButtonQuery);
}


//====================================================== Method Opsi Bot Telegram ========================================================
void botTelegram() {
  TBMessage msg; //Constructor TBMessage
  
  if (myBot.getNewMessage(msg)) {  
    if (msg.text.equalsIgnoreCase("/start")) { //Start Bot
      rp1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nSelamat datang di Layanan BOT PHIOTNET.";
      rp2 = "\n\nBot ini berguna untuk kendali dan monitoring pH pada air Akuaponik.\n\n‼️ Silahkan isi kode rahasia PHIOTNET\n.................................. *(8 Characters)";
      sendMsg = rp1 + rp2;
      myBot.sendMessage(msg.sender.id, sendMsg);
    } 
    else if (msg.text.equalsIgnoreCase("IFSK2022")) { //Menu Utama
      rp1 = "✅ Kode yang anda masukkan benar";
      myBot.sendMessage(msg.sender.id, rp1);
      main_menu:
      rp2 = "\n--------------------------------------------------------------\n 📝 MENU UTAMA \n--------------------------------------------------------------\nSilahkan pilih menu dibawah ini 👇👇";
      viewTombol = true;
      myBot.sendMessage(msg.sender.id, rp2, myKbd);
    }
    else if (msg.text.equalsIgnoreCase("👁 Monitoring pH")) { //Hasil Monitoring pH
      rp1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring pH terkini :\n\n";
      myBot.sendMessage(msg.sender.id, rp1);
      DTnow(); //Pewaktuan dari RTC
      lcdpHValue(); //Tampilkan status Nilai pH pada LCD
      rp2 = "--------------------------------------------------------------\n 👁 MONITORING PH \n--------------------------------------------------------------\n💦 pH air akuarium : " + String(payload_Subscribe) + "\n⏰ waktu : " + String(waktu) + "\n--------------------------------------------------------------"; 
      myBot.sendMessage(msg.sender.id, rp2);
      Serial.println("pH air akuaponik saat ini : " + String(payload_Subscribe) + "\nWaktu saat ini : " + String(waktu) + "\n");
    }    
    else if (msg.text.equalsIgnoreCase("🤖 Bantuan Bot")) { //Opsi Bantuan Bot
      sendMsg = "Apakah anda ingin mengakses bantuan bot sekarang?";
      myBot.sendMessage(msg.sender.id, sendMsg, InKbd); 
    }
    else if (msg.text.equalsIgnoreCase("🚰 Pengaturan pH")) { //Sub Menu Pengaturan pH
      sub_menu1:
      sendMsg = "--------------------------------------------------------------\n 🚰 PENGATURAN PH \n--------------------------------------------------------------\nBerikut pilihan sub menu yang dapat anda akses :";
      viewTombol = true;
      myBot.sendMessage(msg.sender.id, sendMsg, submainKbd);          
    }
    else if (msg.text.equalsIgnoreCase("⬅️ Kembali")) { //Opsi Kembali ke Menu Utama
      sendMsg = "✅ Berhasil kembali ke menu utama";
      myBot.sendMessage(msg.sender.id, sendMsg); 
      goto main_menu;
    }
    else if (msg.text.equalsIgnoreCase("🧪 All-pH")) { //Sub Menu All-pH
      sub_menu2:
      sendMsg = "--------------------------------------------------------------\n 🧪 ALL-PH \n--------------------------------------------------------------\nBerikut pilihan sub menu yang dapat anda akses :";
      viewTombol = true;
      myBot.sendMessage(msg.sender.id, sendMsg, sub1Kbd);        
    }
    else if (msg.text.equalsIgnoreCase("🧪 pH-Up")) { //Sub Menu pH-Up
      sub_menu3:
      sendMsg = "--------------------------------------------------------------\n 🧪 PH-UP \n--------------------------------------------------------------\nBerikut pilihan sub menu yang dapat anda akses :";
      viewTombol = true;
      myBot.sendMessage(msg.sender.id, sendMsg, sub2Kbd);          
    }
    else if (msg.text.equalsIgnoreCase("🧪 pH-Down")) { //Sub Menu pH-Down
      sub_menu4:
      sendMsg = "--------------------------------------------------------------\n 🧪 PH-DOWN \n--------------------------------------------------------------\nBerikut pilihan sub menu yang dapat anda akses :";
      viewTombol = true;
      myBot.sendMessage(msg.sender.id, sendMsg, sub3Kbd);          
    }
    else if (msg.text.equalsIgnoreCase("1️⃣ All-pH ON")) { //Opsi Sub Menu All-pH ON
      sendMsg = "Anda yakin memilih opsi All-pH ON?";
      myBot.sendMessage(msg.sender.id, sendMsg, In3Kbd1); 
    }
    else if (msg.text.equalsIgnoreCase("2️⃣ All-pH OFF")) { //Opsi Sub Menu All-pH OFF
      sendMsg = "Anda yakin memilih opsi All-pH OFF?";
      myBot.sendMessage(msg.sender.id, sendMsg, In3Kbd2); 
    }
    else if (msg.text.equalsIgnoreCase("1️⃣ pH-Up ON")) { //Opsi Sub Menu pH-Up ON
      sendMsg = "Anda yakin memilih opsi pH-Up ON?";
      myBot.sendMessage(msg.sender.id, sendMsg, In3Kbd3); 
    }
    else if (msg.text.equalsIgnoreCase("2️⃣ pH-Up OFF")) { //Opsi Sub Menu pH-Up OFF
      sendMsg = "Anda yakin memilih opsi pH-Up OFF?";
      myBot.sendMessage(msg.sender.id, sendMsg, In3Kbd4); 
    }
    else if (msg.text.equalsIgnoreCase("1️⃣ pH-Down ON")) { //Opsi Sub Menu pH-Down ON
      sendMsg = "Anda yakin memilih opsi pH-Down ON?";
      myBot.sendMessage(msg.sender.id, sendMsg, In3Kbd5); 
    }
    else if (msg.text.equalsIgnoreCase("2️⃣ pH-Down OFF")) { //Opsi Sub Menu pH-Down OFF
      sendMsg = "Anda yakin memilih opsi pH-Down OFF?";
      myBot.sendMessage(msg.sender.id, sendMsg, In3Kbd6); 
    }
    else if (msg.text.equalsIgnoreCase("↩️ Kembali")) { //Opsi Kembali ke Menu Pengaturan pH
      sendMsg = "✅ Berhasil kembali ke menu pengaturan pH";
      myBot.sendMessage(msg.sender.id, sendMsg); 
      goto sub_menu1;
    }
    else if (msg.messageType == CTBotMessageQuery) { //Respon Dari Semua Opsi
      if (msg.callbackQueryData.equals(INrespYes)) { //Respon Opsi Bantuan Bot
        rp1 = "--------------------------------------------------------------\n 🤖 BANTUAN BOT \n--------------------------------------------------------------\n\n🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut informasi yang ada di Bot PHIOTNET :\n\n1. Menu '👁 monitoring_pH' :\nfungsinya yaitu untuk memantau kondisi pH air akuaponik terkini.\n\n2. Menu '🚰 pengaturan_pH' :\nfungsinya yaitu untuk mematikan dan menyalakan pH up/down.\n\n";
        rp2 = "3. Menu '🤖 bantuan_bot' :\nfungsinya yaitu sebagai pusat informasi bot telegram.\n\n4. Aplikasi 'phiotnet_bot' ini diciptakan oleh @Devan_Cakra untuk pemenuhan Tugas Akhir (Skripsi) S1 Informatika UPN Veteran Jatim.\n\n5. Bahasa pemrograman yang dipakai yaitu Bahasa C (Arduino).\n--------------------------------------------------------------";
        sendMsg = rp1+rp2;
        myBot.sendMessage(msg.sender.id, sendMsg);
      }
      else if (msg.callbackQueryData.equals(INrespNo)) { //Respon Opsi Tidak -> main_menu
        sendMsg = "❌ Perintah telah dibatalkan!!!";
        myBot.sendMessage(msg.sender.id, sendMsg);
        goto main_menu;
      }
      else if (msg.callbackQueryData.equals(INrespYes1)) { //Respon Opsi Sub Menu All-pH ON
        all_pH_on(); //Menyalakan semua relay pH
        statusKendaliIoT = "ON"; //Status kendali ON
        lcdAllpHON(); //Tampilkan status All-pH ON pada LCD
        sendMsg = "🌊 Semua pH (Up-Down): " + statusKendaliIoT;
        myBot.sendMessage(msg.sender.id, sendMsg);
      }
      else if (msg.callbackQueryData.equals(INrespYes2)) { //Respon Opsi Sub Menu All-pH OFF
        all_pH_off(); //Mematikan semua relay pH
        statusKendaliIoT = "OFF"; //Status kendali OFF
        lcdAllpHOFF(); //Tampilkan status All-pH OFF pada LCD
        sendMsg = "💤 Semua pH (Up-Down): " + statusKendaliIoT;
        myBot.sendMessage(msg.sender.id, sendMsg);
      }
      else if (msg.callbackQueryData.equals(INrespNo1)) { //Respon Opsi Tidak -> sub_menu2
        sendMsg = "❌ Perintah telah dibatalkan!!!";
        myBot.sendMessage(msg.sender.id, sendMsg);
        goto sub_menu2;
      }
      else if (msg.callbackQueryData.equals(INrespYes3)) { //Respon Opsi Sub Menu pH-Up ON
        pH_up_on(); //Menyalakan relay pH Up
        statusKendaliIoT = "ON"; //Status kendali ON
        lcdpHUpON(); //Tampilkan status pH-Up ON pada LCD
        sendMsg = "🌊 pH (Up): " + statusKendaliIoT;
        myBot.sendMessage(msg.sender.id, sendMsg);
      }
      else if (msg.callbackQueryData.equals(INrespYes4)) { //Respon Opsi Sub Menu pH-Up OFF
        pH_up_off(); //Mematikan relay pH Up
        statusKendaliIoT = "OFF"; //Status kendali OFF
        lcdpHUpOFF(); //Tampilkan status pH-Up OFF pada LCD
        sendMsg = "💤 pH (Up): " + statusKendaliIoT;
        myBot.sendMessage(msg.sender.id, sendMsg);
      }
      else if (msg.callbackQueryData.equals(INrespNo2)) { //Respon Opsi Tidak -> sub_menu3
        sendMsg = "❌ Perintah telah dibatalkan!!!";
        myBot.sendMessage(msg.sender.id, sendMsg);
        goto sub_menu3;
      }
      else if (msg.callbackQueryData.equals(INrespYes5)) { //Respon Opsi Sub Menu pH-Down ON
        pH_down_on(); //Menyalakan relay pH Down
        statusKendaliIoT = "ON"; //Status kendali ON
        lcdpHDownON(); //Tampilkan status pH-Down ON pada LCD
        sendMsg = "🌊 pH (Down): " + statusKendaliIoT;
        myBot.sendMessage(msg.sender.id, sendMsg);
      }
      else if (msg.callbackQueryData.equals(INrespYes6)) { //Respon Opsi Sub Menu pH-Down OFF
        pH_down_off(); //Mematikan relay pH Down
        statusKendaliIoT = "OFF"; //Status kendali OFF
        lcdpHDownOFF(); //Tampilkan status pH-Down OFF pada LCD
        sendMsg = "💤 pH (Down): " + statusKendaliIoT;
        myBot.sendMessage(msg.sender.id, sendMsg);
      }
      else if (msg.callbackQueryData.equals(INrespNo3)) { //Respon Opsi Tidak -> sub_menu4
        sendMsg = "❌ Perintah telah dibatalkan!!!";
        myBot.sendMessage(msg.sender.id, sendMsg);
        goto sub_menu4;
      }
    }
    else { //Control Error jika perintah tidak sesuai
      sendMsg = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\n\n❌ Gagal mengakses, coba lagi";
      myBot.sendMessage(msg.sender.id, sendMsg);
    } 
  }  
}


//================================================== Method Interval Type 2 Fuzzy Logic ==================================================
void IT2FL_pH() {
  Serial.println("\n[Interval Type 2 Fuzzy Logic]\nproses fuzzifikasi :"); 
  Serial.println("\nDeteksi pH: " + String(pHValue, 2));
  pHair_Upper = float(pHValue); //Memasukkan nilai pH ke Himpunan atas
  pHair_Lower = float(pHValue); //Memasukkan nilai pH ke Himpunan bawah
  fuzz_it2fl(); //Memanggil Method Fuzzifikasi
  Serial.println("\nproses inferensi :"); 
  infer_it2fl(); //Memanggil Method Inferensi
  Serial.println("\nproses reduksi tipe & defuzzifikasi :"); 
  redukdefuzz_it2fl(); //Memanggil Method Reduksi Tipe dan Defuzzifikasi
  Serial.println("\n==================================================================================");
  reset_redukdeffuzz();
}


//========================================================= Method Fuzzifikasi ===========================================================
void MF_AsamKuat() { //Fungsi Keanggotaan Asam Kuat
  //MF-Upper : Asam Kuat
  if (pHair_Upper <= 0) {
    AKU = 1; Serial.print("Nilai AK-Upper: " + String(AKU));
  }
  else if (pHair_Upper > 0 && pHair_Upper < 3) {
    AKU = (3 - pHair_Upper) / (3 - 0); Serial.print("Nilai AK-Upper: " + String(AKU));
  }
  else if (pHair_Upper >= 3) {
    AKU = 0; Serial.print("Nilai AK-Upper: " + String(AKU));
  } 

  //MF-Lower : Asam Kuat
  if (pHair_Lower <= 0) {
    AKL = 1; Serial.println(" , Nilai AK-Lower: " + String(AKL));
  }
  else if (pHair_Lower > 0 && pHair_Lower < 2.8) {
    AKL = (2.8 - pHair_Lower) / (2.8 - 0); Serial.println(" , Nilai AK-Lower: " + String(AKL));
  }
  else if (pHair_Lower >= 2.8) {
    AKL = 0; Serial.println(" , Nilai AK-Lower: " + String(AKL));
  } 
}

void MF_AsamLemah() { //Fungsi Keanggotaan Asam Lemah
  //MF-Upper : Asam Lemah
  if (pHair_Upper <= 3 || pHair_Upper >= 6) {
    ALU = 0; Serial.print("Nilai AL-Upper: " + String(ALU));
  }
  else if (pHair_Upper > 3 && pHair_Upper <= 4.5) {
    ALU = (pHair_Upper - 3) / (4.5 - 3);
    Serial.print("Nilai AL-Upper: " + String(ALU));
  }
  else if (pHair_Upper > 4.5 && pHair_Upper < 6) {
    ALU = (6 - pHair_Upper) / (6 - 4.5);
    Serial.print("Nilai AL-Upper: " + String(ALU));
  } 

  //MF-Lower : Asam Lemah
  if (pHair_Lower <= 3.2 || pHair_Lower >= 5.8) {
    ALL = 0; Serial.println(" , Nilai AL-Lower: " + String(ALL));
  }
  else if (pHair_Lower > 3.2 && pHair_Lower <= 4.5) {
    ALL = (pHair_Lower - 3.2) / (4.5 - 3.2);
    Serial.println(" , Nilai AL-Lower: " + String(ALL));
  }
  else if (pHair_Lower > 4.5 && pHair_Lower < 5.8) {
    ALL = (5.8 - pHair_Lower) / (5.8 - 4.5);
    Serial.println(" , Nilai AL-Lower: " + String(ALL));
  } 
}

void MF_Netral() { //Fungsi Keanggotaan Netral
  //MF-Upper : Netral
  if (pHair_Upper <= 6 || pHair_Upper >= 8) {
    NU = 0; Serial.print("Nilai N-Upper: " + String(NU));
  }
  else if (pHair_Upper > 6 && pHair_Upper <= 7) {
    NU = (pHair_Upper - 6) / (7 - 6);
    Serial.print("Nilai N-Upper: " + String(NU));
  }
  else if (pHair_Upper > 7 && pHair_Upper < 8) {
    NU = (8 - pHair_Upper) / (8 - 7);
    Serial.print("Nilai N-Upper: " + String(NU));
  } 

  //MF-Lower : Netral
  if (pHair_Lower <= 6.2 || pHair_Lower >= 7.8) {
    NL = 0; Serial.println(" , Nilai N-Lower: " + String(NL));
  }
  else if (pHair_Lower > 6.2 && pHair_Lower <= 7) {
    NL = (pHair_Lower - 6.2) / (7 - 6.2);
    Serial.println(" , Nilai N-Lower: " + String(NL));
  }
  else if (pHair_Lower > 7 && pHair_Lower < 7.8) {
    NL = (7.8 - pHair_Lower) / (7.8 - 7);
    Serial.println(" , Nilai N-Lower: " + String(NL));
  } 
}

void MF_BasaLemah() { //Fungsi Keanggotaan Basa Lemah
  //MF-Upper : Basa Lemah
  if (pHair_Upper <= 8 || pHair_Upper >= 10) {
    BLU = 0; Serial.print("Nilai BL-Upper: " + String(BLU));
  }
  else if (pHair_Upper > 8 && pHair_Upper <= 9) {
    BLU = (pHair_Upper - 8) / (9 - 8);
    Serial.print("Nilai BL-Upper: " + String(BLU));
  }
  else if (pHair_Upper > 9 && pHair_Upper < 10) {
    BLU = (10 - pHair_Upper) / (10 - 9);
    Serial.print("Nilai BL-Upper: " + String(BLU));
  } 

  //MF-Lower : Basa Lemah
  if (pHair_Lower <= 8.2 || pHair_Lower >= 9.8) {
    BLL = 0; Serial.println(" , Nilai BL-Lower: " + String(BLL));
  }
  else if (pHair_Lower > 8.2 && pHair_Lower <= 9) {
    BLL = (pHair_Lower - 8.2) / (9 - 8.2);
    Serial.println(" , Nilai BL-Lower: " + String(BLL));
  }
  else if (pHair_Lower > 9 && pHair_Lower < 9.8) {
    BLL = (9.8 - pHair_Lower) / (9.8 - 9);
    Serial.println(" , Nilai BL-Lower: " + String(BLL));
  } 
}

void MF_BasaKuat() { //Fungsi Keanggotaan Basa Kuat
  //MF-Upper : Basa Kuat
  if (pHair_Upper <= 10) {
    BKU = 0; Serial.print("Nilai BK-Upper: " + String(BKU));
  }
  else if (pHair_Upper > 10 && pHair_Upper < 14) {
    BKU = (pHair_Upper - 10) / (14 - 10);
    Serial.print("Nilai BK-Upper: " + String(BKU));
  }
  else if (pHair_Upper >= 14) {
    BKU = 1; Serial.print("Nilai BK-Upper: " + String(BKU));
  } 

  //MF-Lower : Basa Kuat
  if (pHair_Lower <= 10.2) {
    BKL = 0; Serial.println(" , Nilai BK-Lower: " + String(BKL));
  }
  else if (pHair_Lower > 10.2 && pHair_Lower < 14) {
    BKL = (pHair_Lower - 10.2) / (14 - 10.2);
    Serial.println(" , Nilai BK-Lower: " + String(BKL));
  }
  else if (pHair_Lower >= 14) {
    BKL = 1; Serial.println(" , Nilai BK-Lower: " + String(BKL));
  } 
}

void fuzz_it2fl() {
  MF_AsamKuat(); //Memanggil Method Fungsi Keanggotaan Asam Kuat
  MF_AsamLemah(); //Memanggil Method Fungsi Keanggotaan Asam Lemah
  MF_Netral(); //Memanggil Method Fungsi Keanggotaan Netral
  MF_BasaLemah(); //Memanggil Method Fungsi Keanggotaan Basa Lemah
  MF_BasaKuat(); //Memanggil Method Fungsi Keanggotaan Basa Kuat
}


//=========================================================== Method Inferensi ===========================================================
void infer_it2fl() {
  //Proposisi Tunggal Upper => Penalaran Monoton
  MiuUMF[0] = AKU; MiuUMF[1] = ALU; MiuUMF[2] = NU; MiuUMF[3] = BLU; MiuUMF[4] = BKU;

  //Proposisi Tunggal Lower => Penalaran Monoton
  MiuLMF[0] = AKL; MiuLMF[1] = ALL; MiuLMF[2] = NL; MiuLMF[3] = BLL; MiuLMF[4] = BKL;

  //Cetak MF-Upper dan MF-Lower
  Serial.print("AK-Upper terkecil = " + String(MiuUMF[0])); Serial.println(" , AK-Lower terkecil = " + String(MiuLMF[0]));
  Serial.print("AL-Upper terkecil = " + String(MiuUMF[1])); Serial.println(" , AL-Lower terkecil = " + String(MiuLMF[1]));
  Serial.print("N-Upper terkecil = " + String(MiuUMF[2])); Serial.println(" , N-Lower terkecil = " + String(MiuLMF[2]));
  Serial.print("BL-Upper terkecil = " + String(MiuUMF[3])); Serial.println(" , BL-Lower terkecil = " + String(MiuLMF[3]));
  Serial.print("BK-Upper terkecil = " + String(MiuUMF[4])); Serial.println(" , BK-Lower terkecil = " + String(MiuLMF[4]));
  
  //Pengambilan Keputusan yang ditentukan
  SPK[0] = 0; //untuk : ON Relay pH Up Lama (25 detik)
  SPK[1] = 1; //untuk : ON Relay pH Up Sedang (10 detik)
  SPK[2] = 2; //untuk : OFF semua Relay pH (0 detik)
  SPK[3] = 3; //untuk : ON Relay pH Down Sedang (10 detik) 
  SPK[4] = 4; //untuk : ON Relay pH Down Lama (25 detik)
}


//============================================= Method Reduksi Tipe & Defuzzifikasi ======================================================
void redukdefuzz_it2fl() {
  //Menjumlah total array yang ada pada MF-Upper dan MF-Lower
  Tarray1 = sizeof(MiuUMF) / sizeof(int);
  Tarray2 = sizeof(MiuLMF) / sizeof(int);

  //Perhitungan himpunan atas
  for (i = 0; i < Tarray1; i++) {
    yi += SPK[i];
    SigyiMiuMFUpper += SPK[i] * MiuUMF[i];
    SigMiuMFUpper += MiuUMF[i];
  }

  //Perhitungan himpunan bawah
  for (i = 0; i < Tarray2; i++) {
    yi += SPK[i];
    SigyiMiuMFLower += SPK[i] * MiuLMF[i];
    SigMiuMFLower += MiuLMF[i];
  }

  //Perhitungan reduksi tipe
  //Interval kiri
  yl = ((SigyiMiuMFUpper + SigyiMiuMFLower) / (SigMiuMFLower + SigMiuMFUpper));
  Serial.println("yl = (" + String(SigyiMiuMFUpper) + " + " + String(SigyiMiuMFLower) + ") / (" + String(SigMiuMFLower) + " + " + String(SigMiuMFUpper) + ") = " + yl);
  //Interval kanan
  yr = ((SigyiMiuMFLower + SigyiMiuMFUpper) / (SigMiuMFUpper + SigMiuMFLower));
  Serial.println("yr = (" + String(SigyiMiuMFLower) + " + " + String(SigyiMiuMFUpper) + ") / (" + String(SigMiuMFUpper) + " + " + String(SigMiuMFLower) + ") = " + yr);

  //Perhitungan deffuzifikasi
  ycos = yl + yr;
  yout = floor((ycos) / 2);
  Serial.println("yout = (" + String(yl) + " + " + String(yr) + ") / 2 = " + String(yout));

  //Nilai crips berdasarkan pengambilan keputusan
  if (yout == 0) {
    statusPH = "Darurat (Asam Kuat)"; statusBuzzer = "Menyala (3x)";
    statusRelaypH = "pH-Up (ON lama: 25 detik)";
    Serial.println("\nStatus pH: " + statusPH + "\nBuzzer: " + statusBuzzer + "\nRelay: " + statusRelaypH);
    autopHUp25SecondON(); //pH Up Menyala 25 detik
  }
  else if (yout == 1) {
    statusPH = "Waspada (Asam Lemah)"; statusBuzzer = "Menyala (2x)";
    statusRelaypH = "pH-Up (ON sedang: 10 detik)";
    Serial.println("\nStatus pH: " + statusPH + "\nBuzzer: " + statusBuzzer + "\nRelay: " + statusRelaypH);
    autopHUp10SecondON(); //pH Up Menyala 10 detik
  }
  else if (yout == 2) {
    statusPH = "Aman (Netral)"; statusBuzzer = "Tidak Menyala"; 
    statusRelaypH = "All-pH (OFF: diam)";
    Serial.println("\nStatus pH: " + statusPH + "\nBuzzer: " + statusBuzzer + "\nRelay: " + statusRelaypH);
    all_pH_off(); //Seluruh Solenoid Valve pH mati
  }
  else if (yout == 3) {
    statusPH = "Waspada (Basa Lemah)"; statusBuzzer = "Menyala (2x)"; 
    statusRelaypH = "pH-Down (ON sedang: 10 detik)"; 
    Serial.println("\nStatus pH: " + statusPH + "\nBuzzer: " + statusBuzzer + "\nRelay: " + statusRelaypH);
    autopHDown10SecondON(); //pH Down Menyala 10 detik
  }
  else if (yout == 4) {
    statusPH = "Darurat (Basa Kuat)"; statusBuzzer = "Menyala (3x)";
    statusRelaypH = "pH-Down (ON lama: 25 detik)"; 
    Serial.println("\nStatus pH: " + statusPH + "\nBuzzer: " + statusBuzzer + "\nRelay: " + statusRelaypH);
    autopHDown25SecondON(); //pH Down Menyala 25 detik
  }
}


//Method ini digunakan untuk menyetel ulang perhitungan Fuzzy Type-2 agar tetap optimal
void reset_redukdeffuzz() {
  yi = 0;
  SigyiMiuMFUpper = 0;
  SigyiMiuMFLower = 0;
  SigMiuMFUpper = 0;
  SigMiuMFLower = 0;
}
