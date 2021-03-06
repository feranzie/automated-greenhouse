
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
int sensor_pin = 36;
int value ;
int sensorValue; 
const int LDR_PIN = 34;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

#define RELAY_FAN_PIN 25 // ESP32 pin connected to relay
#define RELAY_H_PIN 33 // ESP32 pin connected to relay
#define LIGHTRELAY 32 // ESP32 pin connected to relay
#define SOILRELAY 26 // ESP32 pin connected to relay



#define DHT_SENSOR_PIN 14 // ESP32 pin connected to DHT sensor
#define DHT_SENSOR_TYPE DHT11

#define TEMP_UPPER_THRESHOLD  30 // upper t=emperature threshold
#define highhumid  35 // upper t=emperature threshold


DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
   // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  Serial.begin(9600); // initialize serial
  dht_sensor.begin(); // initialize the DHT sensor
  Serial.println("Reading");
  delay(2000);
  pinMode(RELAY_FAN_PIN,OUTPUT);
  pinMode(RELAY_H_PIN,OUTPUT);
    pinMode(LIGHTRELAY,OUTPUT);
        pinMode(SOILRELAY,OUTPUT);



  
  analogReadResolution(10);

}

void loop() {
  
  float temperature = dht_sensor.readTemperature();;  // read temperature in Celsius
   float h = dht_sensor.readHumidity();
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    if (temperature > TEMP_UPPER_THRESHOLD) {
      Serial.println("Turn the fan on");
      digitalWrite(RELAY_FAN_PIN, HIGH); // turn on
    } else if (temperature < TEMP_UPPER_THRESHOLD) {
      Serial.println("Turn the fan off");
      digitalWrite(RELAY_FAN_PIN, LOW ); // turn off
    }
  }
  Serial.println(temperature);
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    if (h > 76) {
      Serial.println("Turn the fan on");
      digitalWrite(RELAY_H_PIN, HIGH); // turn on
    } else if (h < 76) {
      Serial.println("Turn the fan off");
      digitalWrite(RELAY_H_PIN, LOW ); // turn off
    }
  }
  Serial.println(h);
 
  value= analogRead(sensor_pin);
  value = map(value,550,0,0,100);
  Serial.print("Moisture : ");
  Serial.print(value);
  Serial.println("%");
  delay(1000);
   int LDR_Reading = analogRead(LDR_PIN);
   float LDR_Voltage = ((float)LDR_Reading*3.3/1023);
   Serial.print("light intensity : ");Serial.print(LDR_Reading); 
   // Serial.print("light intensity : ");
  //Serial.print(sensorValue, DEC); // prints the value read
  Serial.print(" \n"); // prints a space between the numbers
  //delay(1000); // wait 100ms for next reading
  // wait a 2 seconds between readings
  //delay(2000);
   // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("t:" );
  lcd.print(temperature);
  
  lcd.setCursor(9,0);
  lcd.print("h:");
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("s:");
  lcd.print(value);
    lcd.print(" ");
  lcd.setCursor(9,1);
  lcd.print("l:");
  lcd.print(LDR_Reading);
  lcd.print(" ");
//  sprintf(buffer,"%4d',LDR_Reading);
   if (LDR_Reading < 400) {
      Serial.println("Turn the fan on");
      digitalWrite(LIGHTRELAY, HIGH); // turn on
    } else if (LDR_Reading > 400) {
      Serial.println("Turn the fan off");
      digitalWrite(LIGHTRELAY, LOW ); // turn off
    }

    if (value < -30) {
      Serial.println("Turn the fan on");
      digitalWrite(SOILRELAY, HIGH); // turn on
    } else if (value > -20) {
      Serial.println("Turn the fan off");
      digitalWrite(SOILRELAY, LOW ); // turn off
    }
 
}




 
