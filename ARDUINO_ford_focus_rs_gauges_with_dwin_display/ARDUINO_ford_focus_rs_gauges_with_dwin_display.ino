// Ford Focus RS gauges with Arduino UNO and DWIN displays
// this sketch is only the Arduino UNO part, sending serial data to DWIN display
// please watch the YouTube tutorial about the details

// created by upir, 2024
// youtube channel: https://www.youtube.com/upir_upir

// YouTube video: https://youtu.be/ugS3rKBZVVc
// Source files: https://github.com/upiir/arduino_focus_rs_gauges
// Wokwi simulation: https://wokwi.com/projects/405742636187304961

// Links from the video:
// Do you like this video? You can buy me a coffee ☕: https://www.buymeacoffee.com/upir
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_DDFX73l
// DWIN 3.7 Inch Bar display: https://www.aliexpress.com/item/1005006246067816.html
// Photopea (online graphics editor like Photoshop): https://www.photopea.com/
// DGUS_V7647 editor: https://www.dwin-global.com/tool-page/
// Wokwi empty Arduino UNO project: https://wokwi.com/projects/new/arduino-uno
// Wokwi serial documentation: https://docs.wokwi.com/guides/serial-monitor
// Wokwi potentiometer documentation: https://docs.wokwi.com/parts/wokwi-potentiometer
// Arduino IDE: https://www.arduino.cc/en/software
// 10K Potentiometer: https://s.click.aliexpress.com/e/_Dk1WFoV
// Breadboard wires: https://s.click.aliexpress.com/e/_DF8Uz3H
// FFC to Pin adapter board: https://s.click.aliexpress.com/e/_DCb9Ajh

// Related videos:
// Display inside the shifter knob: https://www.youtube.com/playlist?list=PLjQRaMdk7pBb6r6xglZb92DGyWJTgBVaV
// Inclinometer for a car: https://youtu.be/GosqWcScwC0
// DIY boost gauge: https://youtu.be/cZTx7T9uwA4
// Nextion pitch and roll indicator: https://youtu.be/S_ppdbb0poQ
// Nextion typewriter: https://youtu.be/ATPutFn6jfk
// Nextion with micro:bit: https://youtu.be/NpZMQjdKxBI
// DWIN with Arduino example: https://youtu.be/t21-wF5F41Y


void setup() {
  Serial.begin(115200); // start the serial communication at the speed of 115200 bauds, using pins 0 (RX) and 1 (TX)

  pinMode(A0, INPUT); // potentiometer signal pin is connected to pin A0 on Arduino board
  pinMode(A1, INPUT); // potentiometer signal pin is connected to pin A1 on Arduino board
  pinMode(A2, INPUT); // potentiometer signal pin is connected to pin A2 on Arduino board    
}

int gauge_01_value = 0; // left gauge value, 0 - 120
int gauge_02_value = 0; // center gauge value, 0 - 120
int gauge_03_value = 0; // right gauge value, 0 - 120


void loop() {

  // read the values from individual potentiometers and remap the value to 0-120 range
  gauge_01_value = map(analogRead(A0), 0, 1023, 0, 120); // left gauge
  gauge_02_value = map(analogRead(A1), 0, 1023, 0, 120); // center gauge
  gauge_03_value = map(analogRead(A2), 0, 1023, 0, 120); // right gauge
  
  // send those values to the DWIN display, the VP addresses are 1000 (left), 1100 (center) and 1200 (right)
  // the "gauge_XX_value" variable is integer (int), made from two bytes, so we use highByte and lowByte to send those two bytes
  
  // set left gauge value
  Serial.write(0x5a); // header
  Serial.write(0xa5); // header
  Serial.write(0x05); // number of bytes being send
  Serial.write(0x82); // send/set VP  
  Serial.write(0x10); // address
  Serial.write(0x00); // address
  Serial.write(highByte(gauge_01_value)); // value
  Serial.write(lowByte(gauge_01_value)); // value

  // set center gauge value
  Serial.write(0x5a); // header
  Serial.write(0xa5); // header
  Serial.write(0x05); // number of bytes being send
  Serial.write(0x82); // send/set VP  
  Serial.write(0x11); // address
  Serial.write(0x00); // address
  Serial.write(highByte(gauge_02_value)); // value
  Serial.write(lowByte(gauge_02_value)); // value

  // set right gauge value
  Serial.write(0x5a); // header
  Serial.write(0xa5); // header
  Serial.write(0x05); // number of bytes being send
  Serial.write(0x82); // send/set VP  
  Serial.write(0x12); // address
  Serial.write(0x00); // address
  Serial.write(highByte(gauge_03_value)); // value
  Serial.write(lowByte(gauge_03_value)); // value    

  Serial.println(""); // print new line character, that´s only to make the messages in the serial monitor more "readable"

  delay(16);  // wait 1000ms / 16 = 60 FPS - i.e. send new data 60 times per second
}