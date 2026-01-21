#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "dht.h"

#define DHT_PIN GPIO_NUM_4
#define DHT_TYPE DHT_TYPE_AM2301 // DHT22

static const char *TAG = "DHT22";

void app_main() {

    float temp = 0, humidity = 0;

    printf("Reading DHT22 sensor...\n");
    while (1) {

        esp_err_t result = dht_read_float_data(
            DHT_TYPE,
            DHT_PIN, 
            &humidity, 
            &temp
        );

        if (result == ESP_OK) {
            ESP_LOGI(TAG, "Humidity: %.1f%%", humidity);
            ESP_LOGI(TAG, "Temperature: %.1f°C\n", temp);
        } else {
            ESP_LOGI(TAG, "Failed to read dht22.\n");
        }

        vTaskDelay(pdMS_TO_TICKS(2000)); // DHT22 cannot be read every 1 second → must be ≥ 2 seconds
    }
}