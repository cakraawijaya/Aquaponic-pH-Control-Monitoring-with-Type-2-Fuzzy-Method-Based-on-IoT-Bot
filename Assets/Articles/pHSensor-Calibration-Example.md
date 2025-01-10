## Step One: Determine the values of 𝑌, 𝑋, 𝑌², 𝑋², dan 𝑋𝑌

<img width="810" src="../Documentation/Experiment/PH4502C Calibration.png" alt="ph-probe-settings">

<br><br>

Install a jumper cable in the ``` Positive (+) ``` part of the pH BNC connector, then connect it to the ``` Negative (-) ``` part of the pH BNC connector. This was done deliberately by the author to make calibration easier. Next, upload the program code.

<table><tr><td width="810">
   
```ino
#define pHpin 35 // GPIO pin 35 is used for pH sensor
int pHValue; // This variable is used to hold the ADC reading value
float voltage; // This variable is used to store the voltage reading value

void setup() {
   Serial.begin(115200); // Default baudrate for ESP32
   pinMode(pHpin, INPUT); // Initialize the pH sensor pins as input
}

void loop() {
   pHValue = analogRead(pHpin); // Read the sensor ADC
   // ESP32 ADC => 4095 => 12 bits
   // Reference voltage => 5V
   voltage = pHValue * (5.0 / 4095.0); // Read pure sensor voltage 
   Serial.println(voltage); // Print voltage value to Serial Monitor
   delay(1000); // Delay for 1 second
}
```

</td></tr></table><br>

Turn the potentiometer until the desired output is reached (target: 2.5V). This 2.5V is obtained from half of 5V which is assumed to be the value of the neutral voltage determination. If the value has stabilized, then remove the jumper in the pH BNC connector area. Next, perform a test like the following steps :

<br>

• ``` Acidic state (𝑌=4) ```

<table><tr><td width="810">
   
   1. Connect the sensor probe to the BNC connector.
   
   2. Dip the sensor probe into water containing an acidic solution.
      
   3. Wait for the voltage to stabilize.
      
   4. Please record the voltage value (𝑋) read by the sensor.
      
   5. Next, find the value of 𝑌², 𝑋², and 𝑋𝑌.
      
   6. Calculate all the values and put them in the table.
   
</td></tr></table><br>

• ``` Neutral state (𝑌=7) ```

<table><tr><td width="810">
   
   1. Connect the sensor probe to the BNC connector.
   
   2. Dip the sensor probe into neutral water.
      
   3. Wait for the voltage to stabilize.
      
   4. Please record the voltage value (𝑋) read by the sensor.
      
   5. Next, find the value of 𝑌², 𝑋², and 𝑋𝑌.
      
   6. Calculate all the values and put them in the table.
   
</td></tr></table><br>

• ``` Alkaline state (𝑌=10) ```

<table><tr><td width="810">
   
   1. Connect the sensor probe to the BNC connector.
   
   2. Dip the sensor probe into water containing an alkaline solution.
      
   3. Wait for the voltage to stabilize.
      
   4. Please record the voltage value (𝑋) read by the sensor.
      
   5. Next, find the value of 𝑌², 𝑋², and 𝑋𝑌.
      
   6. Calculate all the values and put them in the table.
   
</td></tr></table><br>

You can see the calculation example as follows :

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

## Step Two: Find the value of 𝑎 and 𝑏

The values that have been obtained from the previous stage just need to be entered into the equations ``` 𝑎 ``` and ``` 𝑏 ```. The calculation example is like this :

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

The ``` value of 𝑎 ``` is ``` 21.84 ``` and the ``` value of 𝑏 ``` is ``` -5.27 ```.

<br><br>

## Step Three: Input 𝑎 and 𝑏 Values in the Linear Regression Equation

The ``` value of 𝑎 ``` and ``` value of 𝑏 ``` can just be entered into the ``` linear regression ``` equation so that it becomes :

   <table><tr><td width="800" height="80">

   $\ Y = 21,84+(-5,27 . X) $
         
   </td></tr></table><br>

The above equation can be directly used for ``` PH4502C sensor ``` calibration purposes.
