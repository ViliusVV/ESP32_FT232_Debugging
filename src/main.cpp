#include <Arduino.h>


// LEDS of GeekWorm ESP32 DevKit
#define LED_BUILTIN 27

#define ARDUINO_RUNNING_CORE 1



// Set FT232H usb driver to winUsb in Zadig
// In .platformio\packages\tool-openocd-esp32\share\openocd\scripts\interface\ftdi\esp32_devkitj_v1.cfg 
// replace ftdi_vid_pid line to ftdi_vid_pid 0x0403 0x6014

// Connecting
// FT232->  ESP32
// AD0  ->  13
// AD1  ->  12
// AD2  ->  15
// AD3  ->  14 
// GND  ->   GND

// LEDS of GeekWorm ESP32 DevKit
#define LED_BUILTIN 27



void TaskBlink( void *pvParameters );
void TaskAnalogReadA3( void *pvParameters );

void setup() {
  
  Serial.begin(119200);
  
  xTaskCreatePinnedToCore(
    TaskBlink
    ,  "TaskBlink"   
    ,  1024  
    ,  NULL
    ,  2
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    TaskAnalogReadA3
    ,  "AnalogReadA3"
    ,  1024  
    ,  NULL
    ,  1  
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);
}

void loop()
{
  // Empty.
}



/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters) 
{
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) 
  {
    digitalWrite(LED_BUILTIN, HIGH);   
    vTaskDelay(100); 
    digitalWrite(LED_BUILTIN, LOW);    
    vTaskDelay(100);  
  }
}

void TaskAnalogReadA3(void *pvParameters) 
{
  (void) pvParameters;
  
  for (;;)
  {

    int sensorValueA3 = analogRead(A3);

    Serial.println(sensorValueA3);
    vTaskDelay(10);  
  }
}
