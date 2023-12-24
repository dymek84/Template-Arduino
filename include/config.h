

#define DEBUG true
#define SERIAL_BAUD 115200

#define MATRIX_PIN 14
#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define MATRIX_LED_AMOUNT (MATRIX_WIDTH * MATRIX_HEIGHT)

#define STRIPE_PIN 12
#define STRIPE_LED_AMOUNT 60

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

#ifdef USE_FASTLED
#define FASTLED_INTERNAL
#include <FastLED.h>
CRGB stripe[STRIPE_LED_AMOUNT];
CRGB matrix[MATRIX_LED_AMOUNT];
#endif

#ifdef USE_I2S_MIC
#include <driver/i2s.h>
#define I2S_SAMPLE_RATE 44100
#define FFT_SAMPLES 1024
#define I2S_SAMPLE_AMOUNT (I2S_SAMPLE_RATE / 100)
#define I2S_BUFFER_SIZE (I2S_SAMPLE_AMOUNT * I2S_SAMPLE_BYTES)
#define I2S_BUFFER_AMOUNT 2
#define I2S_BUFFER_BYTES (I2S_BUFFER_SIZE * I2S_BUFFER_AMOUNT)
#define PIN_I2S_BCK 5  // I2S for microphone
#define PIN_I2S_DIN 17 // I2S for microphone
#define PIN_I2S_WS 16

i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // I2S mic transfer only works with 32b
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = FFT_SAMPLES,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};

i2s_pin_config_t pin_config = {
    .bck_io_num = PIN_I2S_BCK,         // Serial Clock (SCK)
    .ws_io_num = PIN_I2S_WS,           // Word Select (WS)
    .data_out_num = I2S_PIN_NO_CHANGE, // not used (only for speakers)
    .data_in_num = PIN_I2S_DIN         // Serial Data (SD)
};
#endif

#ifdef USE_WIFI
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <AsyncElegantOTA.h>
#include <ArduinoJson.h>

#define SSID "your-ssid"
#define PASSWORD "your-password"
#define HOSTNAME "your-hostname"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

const char *PARAM_MESSAGE = "message";

#endif