#include <SoftwareSerial.h>

SoftwareSerial SIM800L(10, 11); // RX, TX pins for SIM800L

int mq2Pin = A0;      // MQ-2 analog pin
int gasThreshold =500; // Adjust based on your MQ-2 readings
int fan = 9; //cooling fan
int alert = 8; //buzzer

void setup() {
  Serial.begin(9600);
  SIM800L.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);

  Serial.println("Gas detection system started");
}

void loop() {
  int gasValue = analogRead(mq2Pin);
  Serial.print("MQ-2 Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    Serial.println("Gas detected! Sending alert...");
    //TURN ON FAN AND ALERT 
    digitalWrrite(8,HIGH);
    delay(1000);
    digitalWrrite(9,HIGH);
    delay(1000);
    // Send SMS
    SIM800L.println("AT+CMGF=1");       // Set SMS mode to text
    delay(100);
    SIM800L.println("AT+CMGS=\"+94778208822\""); // Replace with your phone number
    delay(100);
    SIM800L.println("Warning! Gas leakage detected!"); 
    delay(100);
    SIM800L.write(26); // CTRL+Z to send SMS
    delay(5000);

    // Make a call
    SIM800L.println("ATD+94778208822;"); // Replace with your phone number
    delay(30000); // Let the call ring for 30 seconds
    SIM800L.println("ATH"); // Hang up
  }
  if (gasValue < gasThreshold){
    digitalWrrite(8,LOW);
    delay(1000);
    digitalWrrite(9,LOW);
    delay(1000);

  }

  delay(2000); // Check gas every 2 seconds
}
