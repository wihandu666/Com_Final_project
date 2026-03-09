#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// LED pins
int redLED = 7;
int yellowLED = 6;
int greenLED = 5;
int buzzer = 8;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init(); 
  lcd.backlight();

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // --- Data Filtering Logic ---
  // Filters: Temp (0-50°C) and Humidity (20-90%)
  if (temperature >= 0 && temperature <= 50 && humidity >= 20 && humidity <= 90) {
    
    // 1. Serial Output
    Serial.print("Temp: "); Serial.print(temperature);
    Serial.print(" | Hum: "); Serial.print(humidity);
    Serial.print(" | HeatIndex: "); Serial.println(heatIndex);

    // 2. LCD Output
    //Page 1: Temperature and Humidity 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Hum : ");
    lcd.print(humidity);
    lcd.print(" %");

    delay(2000);

    //Page 2: Heat Index

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heat Index:");

    lcd.setCursor(0,1);
    lcd.print(heatIndex);
    lcd.print(" C");
    
    // LED Logic based on Heat Index

    if (heatIndex < 27) {           // Comfortable
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(buzzer, LOW);
    }
    else if (heatIndex >= 27 && heatIndex < 32) {   // Moderate
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, LOW);
      digitalWrite(buzzer, LOW);
    }
    else {                          // Hot / Uncomfortable
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
      digitalWrite(redLED, HIGH);

      // --- Buzzer Alarm Logic ---
      digitalWrite(buzzer, HIGH); // Turn buzzer on
      delay(500);                 // Beep for half a second
      digitalWrite(buzzer, LOW);


    }
    
  } else {
    // Logic for when data is outside the specified range
    Serial.println("Data Out of Range - Ignored");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Value Out of Range");
    
    // Optional: Turn off LEDs if data is invalid
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  }

  delay(3000);
}