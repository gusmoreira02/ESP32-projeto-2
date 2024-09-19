#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <driver/gpio.h>
#include <stdio.h>

#define SENSOR_DELAY 1 // 1us para aquisição de amostra
#define ACTUATOR_DELAY 5 // 5us para atuação

// Deadlines em microsegundos
#define INJECAO_DEADLINE 500
#define TEMPERATURA_DEADLINE 20000
#define ABS_DEADLINE 100000
#define AIRBAG_DEADLINE 100000
#define CINTO_DEADLINE 1000000

// Amostragem e display
#define AMOSTRAS_NECESSARIAS 200
#define DISPLAY_UPDATE_TIME pdMS_TO_TICKS(1000) // 1 segundo

// Variáveis globais para armazenar estados
volatile int sensor_injecao = 0;
volatile int sensor_temperatura = 0;
volatile int sensor_abs = 0;
volatile int sensor_airbag = 0;
volatile int sensor_cinto = 0;

void monitor_injecao_task(void *pvParameters) {
    while (1) {
        // Simula leitura de sensor de injeção eletrônica
        sensor_injecao = 1;
        vTaskDelay(pdMS_TO_TICKS(SENSOR_DELAY));

        // Simula atuação (ação após pedal pressionado)
        vTaskDelay(pdMS_TO_TICKS(INJECAO_DEADLINE));
        printf("Atuador de injeção ativado!\n");
        vTaskDelay(pdMS_TO_TICKS(ACTUATOR_DELAY));
    }
}

void monitor_temperatura_task(void *pvParameters) {
    while (1) {
        // Simula leitura do sensor de temperatura
        sensor_temperatura = 1;
        vTaskDelay(pdMS_TO_TICKS(SENSOR_DELAY));

        // Simula atuação se temperatura exceder limite
        vTaskDelay(pdMS_TO_TICKS(TEMPERATURA_DEADLINE));
        printf("Atuador de temperatura ativado!\n");
        vTaskDelay(pdMS_TO_TICKS(ACTUATOR_DELAY));
    }
}

void monitor_abs_task(void *pvParameters) {
    while (1) {
        // Simula leitura do sensor ABS
        sensor_abs = 1;
        vTaskDelay(pdMS_TO_TICKS(SENSOR_DELAY));

        // Simula atuação após acionamento do pedal
        vTaskDelay(pdMS_TO_TICKS(ABS_DEADLINE));
        printf("Atuador ABS ativado!\n");
        vTaskDelay(pdMS_TO_TICKS(ACTUATOR_DELAY));
    }
}

void monitor_airbag_task(void *pvParameters) {
    while (1) {
        // Simula leitura do sensor de choque (airbag)
        sensor_airbag = 1;
        vTaskDelay(pdMS_TO_TICKS(SENSOR_DELAY));

        // Simula atuação após detecção de choque
        vTaskDelay(pdMS_TO_TICKS(AIRBAG_DEADLINE));
        printf("Atuador Airbag ativado!\n");
        vTaskDelay(pdMS_TO_TICKS(ACTUATOR_DELAY));
    }
}

void monitor_cinto_task(void *pvParameters) {
    while (1) {
        // Simula leitura do sensor de cinto de segurança
        sensor_cinto = 1;
        vTaskDelay(pdMS_TO_TICKS(SENSOR_DELAY));

        // Simula atuação após detecção de movimento
        vTaskDelay(pdMS_TO_TICKS(CINTO_DEADLINE));
        printf("Atuador Cinto de segurança ativado!\n");
        vTaskDelay(pdMS_TO_TICKS(ACTUATOR_DELAY));
    }
}

void display_task(void *pvParameters) {
    while (1) {
        // Atualiza o display com os estados dos sensores
        printf("Estado dos Sensores:\n");
        printf("Injeção: %d\n", sensor_injecao);
        printf("Temperatura: %d\n", sensor_temperatura);
        printf("ABS: %d\n", sensor_abs);
        printf("Airbag: %d\n", sensor_airbag);
        printf("Cinto: %d\n", sensor_cinto);

        // Atualiza a cada 1 segundo
        vTaskDelay(DISPLAY_UPDATE_TIME);
    }
}

void app_main() {
    // Task para monitoramento do airbag (Prioridade 5 - Mais alta)
    xTaskCreate(monitor_airbag_task, "Monitor Airbag", 2048, NULL, 5, NULL);
    
    // Task para monitoramento do ABS (Prioridade 4)
    xTaskCreate(monitor_abs_task, "Monitor ABS", 2048, NULL, 4, NULL);

    // Task para monitoramento da injeção eletrônica (Prioridade 3)
    xTaskCreate(monitor_injecao_task, "Monitor Injeção", 2048, NULL, 3, NULL);

    // Task para monitoramento da temperatura do motor (Prioridade 2)
    xTaskCreate(monitor_temperatura_task, "Monitor Temperatura", 2048, NULL, 2, NULL);
    
    // Task para monitoramento do cinto de segurança (Prioridade 2)
    xTaskCreate(monitor_cinto_task, "Monitor Cinto", 2048, NULL, 2, NULL);
    
    // Task para atualização do display (Prioridade 1 - Mais baixa)
    xTaskCreate(display_task, "Display", 2048, NULL, 1, NULL);
}
