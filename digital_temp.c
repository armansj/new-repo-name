/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
*********/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <L298N.h>
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4
#define ENA 10
#define IN1 8
#define IN2 9

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{

  // data should put between serial begin and sensors begin otherwise it will not work correctly

  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library

    // Setup motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Ensure motor is off at start
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  sensors.begin();
}

void loop(void){ 
  
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  Serial.print(sensors.getTempCByIndex(0)); 

  // check if temperatur is more than 23 then start motor
  if(sensors.getTempCByIndex(0)>23){

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 150);  // Adjust speed (0-255)

  }else{

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  }
  // print temp based farenheit
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(1000);
}
