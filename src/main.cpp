#include <Arduino.h>


// LEDs of GeekWorm ESP32 DevKit
#define LED_BUILTIN 27



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

// LEDS of GeekWorm ESP32
#define SERIAL_BAUDRATE 119200
#define LED_BUILTIN 27



void xTaskBlink( void *pvParameters );
void xTaskAnalogReadA3( void *pvParameters );

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void setup() {
  
  Serial.begin(SERIAL_BAUDRATE);
  
  xTaskCreatePinnedToCore(
    xTaskBlink
    ,  "xTaskBlink"
    ,  1024  
    , nullptr
    ,  2
    ,  nullptr
    ,  ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    xTaskAnalogReadA3
    ,  "xAnalogReadA3"
    ,  1024  
    ,  nullptr
    ,  1  
    ,  nullptr
    ,  ARDUINO_RUNNING_CORE);
}
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void loop()
{
  // Empty.
}
#pragma clang diagnostic pop



/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void xTaskBlink(void *pvParameters)
{
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) 
  {
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(100); 
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(100);

    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(10);
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(500);
  }
}

void xTaskAnalogReadA3(void *pvParameters)
{
  (void) pvParameters;
  
  for (;;)
  {

    int sensorValueA3 = analogRead(A3);

    Serial.println(sensorValueA3);
    vTaskDelay(10);  
  }
}
