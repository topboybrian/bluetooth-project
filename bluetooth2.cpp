#include <SoftwareSerial.h>
 
// Define the pins for the motion sensor and Bluetooth speaker.
#define MOTION_SENSOR_PIN 2
#define BLUETOOTH_RX_PIN 3
#define BLUETOOTH_TX_PIN 4
 
// Define the distance thresholds for music playback and volume adjustment.
#define PLAYBACK_DISTANCE 300 // in feet
#define VOLUME_DISTANCE 200 // in feet
 
SoftwareSerial bluetooth(BLUETOOTH_RX_PIN, BLUETOOTH_TX_PIN);
 
void setup() {
  // Initiate serial communication at 9600 baud rate.
  Serial.begin(9600);
 
  // Set the motion sensor pin as input.
  pinMode(MOTION_SENSOR_PIN, INPUT);
 
  // Set the Bluetooth speaker pins as input and output respectively.
  pinMode(BLUETOOTH_RX_PIN, INPUT);
  pinMode(BLUETOOTH_TX_PIN, OUTPUT);
 
  // Set the baud rate for the Bluetooth communication.
  bluetooth.begin(9600);
}
 
void loop() {
  // Read the motion sensor value.
  int motionSensorValue = digitalRead(MOTION_SENSOR_PIN);
 
  // If motion is detected, play the song through the Bluetooth speaker.
  if (motionSensorValue == HIGH) {
    playSong();
  }
 
  // Read the distance from the Bluetooth speaker.
  int distance = readDistance();
 
  // If the distance is within the volume adjustment threshold, adjust the volume.
  if (distance <= VOLUME_DISTANCE) {
    adjustVolume(distance);
  }
 
  // Delay for stability and to prevent rapid changes.
  delay(100);
}
 
void playSong() {
  // Send the play command to the Bluetooth speaker.
  bluetooth.println("play");
}
 
int readDistance() {
  // Send the distance measurement command to the Bluetooth speaker.
  bluetooth.println("distance");
 
  // Wait for the response from the Bluetooth speaker.
  while (bluetooth.available() == 0) {
    // Do nothing until data is received.
  }
 
  // Read the distance value from the Bluetooth speaker.
  int distance = bluetooth.parseInt();
 
  // Return the distance value.
  return distance;
}
 
void adjustVolume(int distance) {
  // Calculate the volume level based on the distance.
  int volume = map(distance, 0, VOLUME_DISTANCE, 0, 255);
 
  // Send the volume adjustment command to the Bluetooth speaker.
  bluetooth.print("volume ");
  bluetooth.println(volume);
}