#include <DHT.h>


#define DHTPIN 2
#define DHTTYPE DHT11

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// LED pins

int redLED = 7;
int yellowLED = 6;
int greenLED = 5;


void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

  pinMode(redLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  
  
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print(humidity);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0,1);
  lcd.print("Hum : ");
  lcd.print(humidity);
  lcd.print(" %");

  digitalWrite(greenLED,HIGH);

  float heatIndex = dht.computeHeatIndex(temperature,humidity,false);
  Serial.println(heatIndex);


  // LED Logic
  if (heatIndex < 27) {           // Comfortable
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  }

  else if (heatIndex >= 27 && heatIndex < 32) {   // Moderate
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  }

  else {                         // Hot / Uncomfortable
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
  }

  delay(3000);

}
  