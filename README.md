[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?style=flat)](https://github.com/ellerbrock/open-source-badges/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg?logo=github&color=%23F7DF1E)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/cakraawijaya/Aquaponic-pH-Control-Monitoring-with-Type-2-Fuzzy-Method-Based-on-IoT-Bot?logo=Codeforces&logoColor=white&color=%23F7DF1E)
![Project](https://img.shields.io/badge/Project-ESP32-light.svg?style=flat&logo=espressif&logoColor=white&color=%23F7DF1E)
![Type](https://img.shields.io/badge/Type-Undergraduate%20Thesis-light.svg?style=flat&logo=gitbook&logoColor=white&color=%23F7DF1E)

# Aquaponic-pH-Control-Monitoring-with-Type-2-Fuzzy-Method-Based-on-IoT-Bot
<strong>Undergraduate Thesis Project Documentation (S1) - Informatics UPN Veteran Jatim</strong><br><br>
An aquaponic system is a combined farming system between fish with vegetables where the activities are mutually beneficial. On the other hand, crop failure can also be a concern for aquaponic farmers as this can happen at any time. Harvest failure can be influenced by many factors, but is usually caused by the high pH ambiguity of the water around the scope of cultivation. The aquaponic farmers are worried that if the crop failure continues it will harm their food security. This project was created in the hope of solving the pH problem. This project has been carried out and took approximately 1 year. The system created can control and monitor changes in water pH at any time. This system is based on the Internet of Things (IoT), using MQTT as the communication protocol. This system is also equipped with artificial intelligence, which uses IT2FL (Interval Type-2 Fuzzy Logic) as its decision support. In addition, the system interface uses Telegram Bot, making it easier for users to interact.

<br><br>

## Project Requirements
| Part | Description |
| --- | --- |
| Development Board | DOIT ESP32 DEVKIT V1 |
| Supporting Board | Arduino Uno R3 |
| Code Editor | Arduino IDE |
| Application Support | • Telegram Bot<br>• Matlab R2020 |
| Driver | CP210X USB Driver |
| IoT Platform | io-t.net |
| Communications Protocol | • Inter Integrated Circuit (I2C)<br>• Message Queuing Telemetry Transport (MQTT)<br>• MTProto |
| IoT Architecture | 3 Layer |
| Matlab |  Fuzzy Interface System |
| Programming Language | C/C++ |
| Arduino Library | • WiFi (default)<br>• PubSubClient<br>• LiquidCrystal_I2C<br>• CTBot<br>• ArduinoJson<br>• RTClib |
| Actuators | • Submersible pump aquarium (x1)<br>• Pneumatic solenoid valve (x2)<br>• Piezoelectric (x1) |
| Sensor | • pH Sensor (x1)<br>• RTC (x1) |
| Display | LCD I2C (x1) |
| Experimental Object | • Pakcoy mustard seeds<br>• Dumbo catfish fry |
| Other Components | • Micro USB cable - USB type A (x1)<br>• Jumper cable (1 set)<br>• Switching power supply 12V 1A (x1)<br>• Electromechanical relay 2-channel (x1)<br>• Round switch (x1)<br>• ESP32 expansion board (x1)<br>• PCB Dot Matrix (x1)<br>• Terminal PCB block screw (x10)<br>• Socket female jack DC (x1)<br>• Connector male jack DC (x3)<br>• Probe Elektroda pH (x1)<br>• Pipes (1 set)<br>• Netpot (1 set)<br>• Rockwool (1 set)<br>• Flannel fabric (1 set)<br>• Water filter (x1)<br>• Glass hubcap (1 set)<br>• Bottle (x2)<br>• Aquarium wheeled placemat (x1)<br>• Aquarium (x1)<br>• Acrylic box (x1)<br>• Skun (1 set)<br>• Galvanized plate (x1)<br>• Bolts plus (1 set)<br>• Nuts (1 set) |

<br><br>

## Download & Install 
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

## Project Designs
<table>
<tr>
<th width="840">Infrastructure</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Diagram/Infrastructure.jpg" alt="infrastructure"></td>
</tr>
</table>
<table>
<tr>
<th width="280">Pictorial Diagram</th>
<th width="280">Prototype Design</th>
<th width="280">Main Box Design</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Diagram/Pictorial Diagram.jpg" alt="pictorial-diagram"></td>
<td><img src="Assets/Documentation/Design/Prototype Design.jpg" alt="prototype-design"></td>
<td><img src="Assets/Documentation/Design/Main Box Design.jpg" alt="mainBox-design"></td>
</tr>
</table>
<table>
<tr>
<th width="280">Fuzzy Interface System IT2FL</th>
<th width="280">IT2FL Input Variable</th>
<th width="280">IT2FL Output Variable</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Experiment/Fuzzy Interface System IT2FL.jpg" alt="fis-it2fl"></td>
<td><img src="Assets/Documentation/Experiment/IT2FL Input Variable.jpg" alt="varin-it2fl"></td>
<td><img src="Assets/Documentation/Experiment/IT2FL Output Variable.jpg" alt="varout-it2fl"></td>
</tr>
</table>

<br><br>

## Scanning the I2C Address on the LCD
<table><tr><td width="840">
   
```ino
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial); // Wait for serial monitor
  Serial.println("\nI2C Scanner");
}

void loop() {
  int nDevices = 0;
  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address) {
    // The i2c_scanner uses the return value of the Wire.endTransmission
    // To see if a device did acknowledge to the address
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
  delay(5000); // Wait 5 seconds for next scan
}
```

</td></tr></table><br><br>

##  pH Sensor Calibration
The pH sensor can be calibrated using the results of a linear regression calculation. You can see the linear regression equation as follows.

<table>
   <tr>
   <td width="40">I</td>
   <td width="800" height="80">

   $\ Y = a+b.X $
         
   </td>      
   </tr>
</table><br>

Explanation of the symbols in equation I, you can see more details in the following table.

<table>
   <tr height="50px">
      <th width="120">Symbol</th>
      <th width="720">Description</th>
   </tr>
   <tr>
      <td>𝑌</td>
      <td>pH buffer value</td>
   </tr>
   <tr>
      <td>𝑋</td>
      <td>voltage value obtained based on Y</td>
   </tr>
   <tr>
      <td>𝑎 and 𝑏</td>
      <td>linear regression determination value</td>
   </tr>
</table><br>

The linear regression determination values (a and b) can be obtained through equations II and III.

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

Example of pH sensor calibration: <a href="https://github.com/devancakra/Aquaponic-pH-Control-Monitoring-with-Type-2-Fuzzy-Method-Based-on-IoT-Bot/blob/master/Assets/Articles/pHSensor-Calibration-Example.md">Click Here</a>

<br><br>

## RTC Sensor Calibration
This RTC sensor can be calibrated using the following program code :
   
<table><tr><td width="840">

```ino
#include <RTClib.h> // Calling the RTC library
RTC_DS3231 rtc; // Constructor

void setup() {
   RTCinit(); // Calling the RTCinit method
}

void loop() {}

void RTCinit() {
   // Starting up the RTC
   rtc.begin();

   // DateTime Setting
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

   // Set Time Now
   // If calibrated, please close with a comment
   rtc.adjust(DateTime(YYYY,MM,DD,HH,MM,SS));
}
```

</td></tr></table><br><br>

## Arduino IDE Setup
1. Open the ``` Arduino IDE ``` first, then open the project by clicking ``` File ``` -> ``` Open ``` : 

   <table><tr><td width="810">
   
      ``` PH_IT2FL.ino ```

   </td></tr></table><br>
   
2. Fill in the ``` Additional Board Manager URLs ``` in Arduino IDE

   <table><tr><td width="810">
      
      Click ``` File ``` -> ``` Preferences ``` -> enter the ``` Boards Manager Url ``` by copying the following link :
      
      ```
      https://dl.espressif.com/dl/package_esp32_index.json
      ```

   </td></tr></table><br>
   
3. ``` Board Setup ``` in Arduino IDE

   <table>
      <tr><th width="810">

      How to setup the ``` DOIT ESP32 DEVKIT V1 ``` board
            
      </th></tr>
      <tr><td>
      
      • Click ``` Tools ``` -> ``` Board ``` -> ``` Boards Manager ``` -> Install ``` esp32 ```. 
      
      • Then selecting a Board by clicking: ``` Tools ``` -> ``` Board ``` -> ``` ESP32 Arduino ``` -> ``` DOIT ESP32 DEVKIT V1 ```.

      • ``` Arduino Uno ``` board in this project is only used as a filter or voltage divider.

      • You don't need to configure the ``` Arduino Uno ``` board, just focus on the ``` ESP32 ```.

   </td></tr></table><br>
   
4. ``` Change the Board Speed ``` in Arduino IDE

   <table><tr><td width="810">
      
      Click ``` Tools ``` -> ``` Upload Speed ``` -> ``` 9600 ```

   </td></tr></table><br>
   
5. ``` Install Library ``` in Arduino IDE

   <table><tr><td width="810">
      
      Download all the library zip files. Then paste it in the: ``` C:\Users\Computer_Username\Documents\Arduino\libraries ```

   </td></tr></table><br>

6. ``` Port Setup ``` in Arduino IDE

   <table><tr><td width="810">
      
      Click ``` Port ``` -> Choose according to your device port ``` (you can see in device manager) ```

   </td></tr></table><br>

7. Change the ``` WiFi Name ```, ``` WiFi Password ```, and so on according to what you are currently using.<br><br>

8. Before uploading the program please click: ``` Verify ```.<br><br>

9. If there is no error in the program code, then please click: ``` Upload ```.<br><br>
    
10. Some things you need to do when using the ``` ESP32 board ``` :

    <table><tr><td width="810">
       
      • ``` Arduino IDE ``` information: ``` Uploading... ``` -> immediately press and hold the ``` BOOT ``` button.

      • ``` Arduino IDE ``` information: ``` Writing at .... (%) ``` -> release the ``` BOOT ``` button.

      • Wait until the message appears: ``` Done Uploading ``` -> ``` The program is directly operated ```.

      • Press the ``` EN (RST) ``` button and then ``` Restart ``` to handle the ``` ESP32 ``` board that cannot process the ``` SC ```.

      • Do not press the ``` BOOT ``` and ``` EN ``` buttons at the same time as this may switch to ``` Upload Firmware ``` mode.

    </td></tr></table><br>

11. If there is still a problem when uploading the program, then try checking the ``` driver ``` / ``` port ``` / ``` others ``` section.

<br><br>

## Io-t.net Setup
1. Getting started with io-t.net :

   <table><tr><td width="810">
      
      • Go to the official website at the following link : <a href="https://io-t.net/">io-t.net</a>.
      
      • If you do not have an account, please <a href="https://i-ot.net/register">Register</a> first -> activate your account via email.
      
      • If you already have an account, please <a href="https://i-ot.net/login">Sign In</a> to be able to access io-t.net services.

   </td></tr></table><br>

2. Create a node :

   <table><tr><td width="810">
      
      • Go to ``` Instance ``` menu -> ``` Set Node ```.
      
      • Then give the node a unique name that you use.

   </td></tr></table><br>

3. Create a device :

   <table><tr><td width="810">
      
      • Go to ``` Devices ``` menu.
      
      • Select ``` Add Devices ``` -> fill in the ``` Client ID ```, ``` Access ```, ``` Topic ``` sections as needed. For example :
   
      - ``` Client ID ``` -> ``` Phiotnet_v1 ```.

      - ``` Access ``` -> ``` Publish & Subscribe ```.

      - ``` Topic ``` -> ``` detect ```.

   </td></tr></table>
   
<br><br>

## Telegram Bot Setup
1. Open <a href="https://t.me/botfather">@BotFather</a>.<br><br>

2. Type ``` /newbot ```.<br><br>

3. Type the desired bot name, for example: ``` phiotnet_bot ```.<br><br>

4. Type the desired bot username, for example: ``` phiotnet_bot ```.<br><br>

5. Also do it for bot image settings, bot descriptions, and so on according to your needs.<br><br>

6. Copy ``` your telegram bot API token ``` -> then paste it into the ``` #define BOTtoken "YOUR_API_BOT_TOKEN" ``` section. 

   <table><tr><td width="810">
   For example :<br><br>

   ```ino
   #define BOTtoken "2006772150:AAE6Fdjk3KbiySkzV6CLbd6ClJDzgTfJ5y0"
   ```
   
   </td></tr></table>

<br><br>

## Matlab Setup
1. Open the ``` Matlab ```.<br><br>

2. Open the ``` Set Path ``` dialog box using the command :
   
   <table><tr><td width="810">
      
   ```
   pathtool
   ```

   </td></tr></table>
   
   <img width="810" src="Assets/Documentation/Experiment/MATLAB Set Path.jpg" alt="set-path-matlab"><br><br>

3. Select ``` Add Folder... ``` -> search the ``` FIS-IT2FLS-Toolbox-MATLAB ``` folder -> ``` Select Folder ```.<br><br>

4. Click ``` Save ``` and then click ``` Close ```.<br><br>

5. Open the ``` IT2FL Toolbox ``` using the command :
   
   <table><tr><td width="810">

   ```
   fuzzyt2
   ```

   </td></tr></table>
   
   <img width="810" src="Assets/Documentation/Experiment/IT2FL Toolbox.jpg" alt="it2fl-toolbox"><br><br>

6. The rest you can customize according to your needs.

<br><br>

## Get Started
1. Download and extract this repository.<br><br>
   
2. Make sure you have the necessary electronic components.<br><br>
   
3. Make sure your components are designed according to the diagram.<br><br>
   
4. Configure your device according to the settings above.<br><br>

5. Please enjoy [Done].

<br><br>

## Demonstration of Application
Via Telegram: <a href="https://t.me/phiotnet_bot">@phiotnet_bot</a>

<br><br>

## Highlights
<table>
<tr>
<th width="280">Product</th>
<th width="280">IT2FL Decision Support System</th>
<th width="280">Telegram Bot</th>
</tr>
<tr>
<td><img src="Assets/Documentation/Experiment/Product.jpg" alt="product"></td>
<td><img src="Assets/Documentation/Experiment/IT2FL Decision Support System.jpg" alt="it2fl-spk"></td>
<td><img src="Assets/Documentation/Experiment/Telegram Bot.jpg" alt="telegram-bot"></td>
</tr>
</table>

<br>
<strong>More information:</strong> <br><br>
<table><tr><td width="840">

   • Undergraduate Thesis: <a href="http://repository.upnjatim.ac.id/id/eprint/7014"><u>Click Here</u></a><br><br>
   • SINTA-type journals: <a href="https://publikasi.mercubuana.ac.id/index.php/Incomtech/article/view/15453"><u>Click Here</u></a><br><br>
   • Non SINTA-type journals: <a href="https://www.researchgate.net/publication/363660330_SISTEM_KONTROL_PH_UP-DOWN_BERBASIS_NODEMCU32_DENGAN_METODE_ON-OFF_CONTROLLER"><u>Click Here</u></a>
</td></tr></table>

<br><br>

## <img src="https://github.com/user-attachments/assets/932b96eb-cbc7-42f1-8938-43cb431889a5" width="16" height="16"> Notes
<ul>
<li>
   <strong><p>Hardware Repairs Suggestions :</p></strong>      
   <table>
   <tr>
   <td width="20">1.</td>
   <td width="820">Use a standard PSU with a capacity of 3A to supply all installed devices.</td>
   </tr>
   <tr>
   <td width="20">2.</td>
   <td width="820">Change the Electromechanical relay 2-channel setting from NO (Normally Open) to NC (Normally Close) to reduce overheating.</td>
   </tr>
   <tr>
   <td width="20">3.</td>
   <td width="820">Add a Step Down Converter to get a more stable voltage and in accordance with the needs of the device. With this component, there is no need for an Arduino Uno.</td>
   </tr>
   <tr>
   <td width="20">4.</td>
   <td width="820">Add insulators to electrical components to prevent leakage current.</td>
   </tr>
   <tr>
   <td width="20">5.</td>
   <td width="820">Add fans or vents to increase airflow and prevent overheating.</td>
   </tr>
   <tr>
   <td width="20">6.</td>
   <td width="820">Add Heat Sinks to heat-prone components.</td>
   </tr>
   <tr>
   <td width="20">7.</td>
   <td width="820">Add an MCB (Miniature Circuit Breaker) to prevent overcurrent, keeping the device safe and secure.</td>
   </tr>
   <tr>
   <td width="20">8.</td>
   <td width="820">Add a special case to protect the pH Sensor Probe from damage, especially from impact.</td>
   </tr>
   <tr>
   <td width="20">9.</td>
   <td width="820">Consider choosing more than 1 Development Board to improve system optimization.</td>
   </tr>
   <tr>
   <td width="20">10.</td>
   <td width="820">Consider replacing the 2-Channel Electromechanical Relay with the SSR DD Relay for smoother control (no noise), faster response, lower power consumption, higher efficiency, and better durability for long-term use.</td>
   </tr>
   <tr>
   <td width="20">11.</td>
   <td width="820">Consider replacing the acrylic box with a standard panel box to make the device much more secure and presentable.</td>
   </tr>
   <tr>
   <td width="20">12.</td>
   <td width="820">Consider replacing the cables according to the standard of use. For DC electricity, use AVS 1 x 0.5mm² cables, which are more durable than ribbon cables. Meanwhile, for AC electricity, use NYY-HY 2 x 1.5mm² cables, which are more resistant to water, weather, and physical disturbances such as rat bites.</td>
   </tr>
   </table>
</li><br>
<li>
   <strong><p>Firmware Repairs Suggestions :</p></strong>
   <table>
   <tr>
   <td width="20">1.</td>
   <td width="820">Optimize the algorithm to reduce latency in the decision-making process. It is recommended to use RTOS (Real-Time Operating System) in order to better prioritize the functions.</td>
   </tr>
   <tr>
   <td width="20">2.</td>
   <td width="820">Add OTA (Over The Air) methods to improve network security, including Telegram Bot.</td>
   </tr>
   </table>
</li><br>
<li>
   <strong><p>Automation Feature Improvement Suggestions :</p></strong>
   <table>
   <tr>
   <td width="20">1.</td>
   <td width="820">Automatic pump integrated with a level sensor to control liquid filling in the form of pH and AB Mix.</td>
   </tr>
   <tr>
   <td width="20">2.</td>
   <td width="820">Time-based automatic feeding for scheduled feeding.</td>
   </tr>
   <tr>
   <td width="20">3.</td>
   <td width="820">Automatic pump controlled via telegram bot to simplify the process of draining and replenishing water.</td>
   </tr>
   <tr>
   <td width="20">4.</td>
   <td width="820">Monitoring water quality in ponds or aquariums using a combination of pH, water temperature, and ammonia sensors.</td>
   </tr>
   <tr>
   <td width="20">5.</td>
   <td width="820">Plant irradiation with growth lamps to grow plants optimally even in low light conditions (as a substitute for sunlight).</td>
   </tr>
   </table>
</li><br>
<li>
   <strong><p>Planting Media Optimization Suggestions :</p></strong>
   <table>
   <tr>
   <td width="20">1.</td>
   <td width="820">Increase the number of hydroponic modules to accommodate more plants.</td>
   </tr>
   <tr>
   <td width="20">2.</td>
   <td width="820">Exploration of alternative growing media such as husk charcoal or cocopeat to improve plant growth efficiency.</td>
   </tr>
   </table>
</li>
</ul>

<br><br>

## Appreciation
If this work is useful to you, then support this work as a form of appreciation to the author by clicking the ``` ⭐Star ``` button at the top of the repository.

<br><br>

## Disclaimer
This application is my own work and is not the result of plagiarism from other people's research or work, except those related to third party services which include: libraries, frameworks, and so on.

<br><br>

## LICENSE
MIT License - Copyright © 2022 - Devan C. M. Wijaya, S.Kom

Permission is hereby granted without charge to any person obtaining a copy of this software and the software-related documentation files to deal in them without restriction, including without limitation the right to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons receiving the Software to be furnished therewith on the following terms:

The above copyright notice and this permission notice must accompany all copies or substantial portions of the Software.

IN ANY EVENT, THE AUTHOR OR COPYRIGHT HOLDER HEREIN RETAINS FULL OWNERSHIP RIGHTS. THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, THEREFORE IF ANY DAMAGE, LOSS, OR OTHERWISE ARISES FROM THE USE OR OTHER DEALINGS IN THE SOFTWARE, THE AUTHOR OR COPYRIGHT HOLDER SHALL NOT BE LIABLE, AS THE USE OF THE SOFTWARE IS NOT COMPELLED AT ALL, SO THE RISK IS YOUR OWN.
