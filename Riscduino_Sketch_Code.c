////////////////////////////////////////////// 
//        RemoteXY include library          // 
////////////////////////////////////////////// 

// RemoteXY select connection mode and include library  
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h> 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Ultrasonic.h>

// RemoteXY connection settings  
#define REMOTEXY_SERIAL Serial 
#define REMOTEXY_SERIAL_SPEED 115200 
#define REMOTEXY_WIFI_SSID "RemoteXY" 
#define REMOTEXY_WIFI_PASSWORD "123456789" 
#define REMOTEXY_SERVER_PORT 6377 


// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,2,0,0,0,30,0,8,13,0,
  2,0,68,25,22,11,2,26,31,31,
  79,78,0,79,70,70,0,1,0,16,
  25,12,12,2,31,88,0 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t button_1; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 

#define PIN_SWITCH_1 13
#define PIN_BUTTON_1 12
#define DHT_PIN 2 // Pin where the DHT22 is connected
#define DHT_TYPE DHT22 // DHT 22 (AM2302) type
DHT dht(DHT_PIN, DHT_TYPE);

#define ULTRASONIC_TRIG_PIN 3 // Pin where the Ultrasonic sensor's trigger is connected
#define ULTRASONIC_ECHO_PIN 4 // Pin where the Ultrasonic sensor's echo is connected
Ultrasonic ultrasonic(ULTRASONIC_TRIG_PIN, ULTRASONIC_ECHO_PIN);



void setup()  
{ 
  RemoteXY_Init();  
  pinMode(PIN_SWITCH_1, OUTPUT);
  pinMode(PIN_BUTTON_1, OUTPUT);

  dht.begin(); // Initialize DHT sensor
  
  // TODO: setup code for other sensors and peripherals
}


void loop()  
{  
  RemoteXY_Handler(); 
  //noInterrupts();

  // Read data from DHT22 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read data from Ultrasonic sensor
  float distance_cm = ultrasonic.read(CM);
  //interrupts();

  // Check if the readings are valid
  if (!isnan(humidity) && !isnan(temperature)) {
    // TODO: Use humidity and temperature readings as needed
  } else {
    // Failed to read from DHT sensor
    Serial.println("Failed to read from DHT sensor!");
  }

  if (distance_cm > 0) {
    // TODO: Use distance_cm as needed (distance in centimeters)
  } else {
    // Failed to read distance from Ultrasonic sensor
    Serial.println("Failed to read from Ultrasonic sensor!");
  }

  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1 == 0) ? LOW : HIGH);
  digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1 == 0) ? LOW : HIGH);

  // TODO: Add your loop code here

  // Delay to avoid excessive readings and to allow RemoteXY to handle communication
  delay(1000); // Delay for 1 second
}