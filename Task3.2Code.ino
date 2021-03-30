#include "Adafruit_DHT.h"
#define DHTPIN 4 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//LED used to indicate when device is reading temp
int led = D7;
int temp = 0;

void setup() {
    Particle.subscribe("hook-response/Argon Temp & Humidity", myHandler, MY_DEVICES);
	dht.begin();
	Particle.variable("temperature", temp);
	//Spark.variable("temperature", t);
}

void myHandler(const char *event, const char *data) {
  // Handle the integration response
}


void loop() {

    //turn on board's LED to signal that temp is being measured
    digitalWrite(led, HIGH); 
    
	temp = dht.getTempCelcius();


    // Check if any reads failed and exit early (to try again).
	if (isnan(temp)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

	//Used for testing purposes, publishes to Particle Console
	Particle.publish("Temp: ", String(temp));

    //publish data to thingspeak
	//Particle.publish("Argon Temp & Humidity", String(t), PRIVATE);

    //turn off built-in LED after delay to indicate reading finished
    delay(5000);
	digitalWrite(led, LOW); 

}
