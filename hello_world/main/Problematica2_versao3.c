#include <stdio.h>
#include "driver/touch_pad.h"
#include "esp_intr_alloc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Variáveis de estado
volatile int estado_injecao = 0;
volatile int estado_abs = 0;
volatile int estado_temperatura = 0;
volatile int estado_airbag = 0;
volatile int estado_cinto = 0;

// Função para inicializar os sensores touch com interrupções
void init_touch_sensors() {
    touch_pad_init();
    touch_pad_config(TOUCH_PAD_NUM0, 0);
    touch_pad_config(TOUCH_PAD_NUM1, 0);
    touch_pad_config(TOUCH_PAD_NUM2, 0);
    touch_pad_config(TOUCH_PAD_NUM3, 0);
    touch_pad_config(TOUCH_PAD_NUM4, 0);

    // Habilita as interrupções dos sensores touch
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    touch_pad_intr_enable();
    touch_pad_sw_start();
}

// Função de callback para lidar com as interrupções
void IRAM_ATTR touch_interrupt_handler(void *arg) {
    uint16_t touch_value;

    touch_pad_clear_status();  // Limpa a interrupção

    touch_pad_read(TOUCH_PAD_NUM0, &touch_value);
    if (touch_value < 500) estado_injecao = 1;

    touch_pad_read(TOUCH_PAD_NUM1, &touch_value);
    if (touch_value < 500) estado_abs = 1;

    touch_pad_read(TOUCH_PAD_NUM2, &touch_value);
    if (touch_value < 500) estado_temperatura = 1;

    touch_pad_read(TOUCH_PAD_NUM3, &touch_value);
    if (touch_value < 500) estado_airbag = 1;

    touch_pad_read(TOUCH_PAD_NUM4, &touch_value);
    if (touch_value < 500) estado_cinto = 1;
}

// Tasks para cada subsistema
void task_injecao(void *pvParameters) {
    while (1) {
        if (estado_injecao) {
            printf("Controlando injeção eletrônica...\n");
            estado_injecao = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_abs(void *pvParameters) {
    while (1) {
        if (estado_abs) {
            printf("Controlando ABS...\n");
            estado_abs = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_temperatura(void *pvParameters) {
    while (1) {
        if (estado_temperatura) {
            printf("Controlando temperatura do motor...\n");
            estado_temperatura = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_airbag(void *pvParameters) {
    while (1) {
        if (estado_airbag) {
            printf("Controlando Airbag...\n");
            estado_airbag = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_cinto(void *pvParameters) {
    while (1) {
        if (estado_cinto) {
            printf("Controlando Cinto de Segurança...\n");
            estado_cinto = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main() {
    init_touch_sensors();

    // Configura o handler da interrupção
    esp_intr_alloc(ETS_CACHE_IA_INTR_SOURCE, 0, touch_interrupt_handler, NULL, NULL);

    // Cria as threads para cada subsistema
    xTaskCreate(task_injecao, "Task Injeção", 2048, NULL, 1, NULL);
    xTaskCreate(task_abs, "Task ABS", 2048, NULL, 1, NULL);
    xTaskCreate(task_temperatura, "Task Temperatura", 2048, NULL, 1, NULL);
    xTaskCreate(task_airbag, "Task Airbag", 2048, NULL, 1, NULL);
    xTaskCreate(task_cinto, "Task Cinto", 2048, NULL, 1, NULL);

    // Loop principal vazio, já que tudo é feito pelas threads
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));  // Apenas mantém o main ativo
    }
}
