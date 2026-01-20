#include <stdio.h>
#include "esp_log.h"
#include "mpu6050.h"
#include "i2cdev.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MPU_6050";

#define I2C_NUM I2C_NUM_0
#define I2C_SCL GPIO_NUM_22
#define I2C_SDA GPIO_NUM_21
#define MPU_ADDR 0X68

void app_main(void) {

    mpu6050_dev_t mpu = {0};
    mpu6050_acceleration_t accel;

    ESP_ERROR_CHECK(i2cdev_init());
    ESP_ERROR_CHECK(
        mpu6050_init_desc(&mpu, MPU_ADDR, I2C_NUM, I2C_SDA, I2C_SCL)
    );
    ESP_ERROR_CHECK(mpu6050_init(&mpu));

    ESP_LOGI(TAG, "initialized device.");

    mpu6050_set_dlpf_mode(&mpu, MPU6050_DLPF_3);
    mpu6050_set_full_scale_accel_range(&mpu, MPU6050_ACCEL_RANGE_2);

    while (1)
    {
        mpu6050_get_acceleration(&mpu, &accel);
        ESP_LOGI(TAG, "ACCEL: x=%.2f y=%.2f z=%.2f", accel.x, accel.y, accel.z);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    // The execution will never reach here. Just for reference
    mpu6050_free_desc(&mpu);
}