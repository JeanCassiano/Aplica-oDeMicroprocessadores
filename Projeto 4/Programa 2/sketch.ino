#include <Arduino.h>
#include "driver/ledc.h"

// Definições de configuração do PWM
#define TIMER_PWM LEDC_TIMER_0                   // Utiliza o primeiro timer do LEDC
#define MODO_PWM LEDC_LOW_SPEED_MODE             // Modo de baixa velocidade para o PWM
#define RESOLUCAO_PWM LEDC_TIMER_8_BIT           // Resolução de 8 bits para a amplitude do PWM
#define FREQUENCIA_PWM 5000                      // Frequência do PWM configurada para 5 kHz

// Estrutura para gerenciar as configurações e operações de cada LED
struct Led {
    uint8_t pin;                                 // Pino GPIO ao qual o LED está conectado
    ledc_channel_t channel;                     // Canal LEDC utilizado
    int intensidade;                            // Intensidade atual do LED
    int passo;                                  // Passo de incremento/decremento da intensidade

    // Configura o canal PWM para este LED específico
    void setup() {
        ledc_channel_config_t config = {
            .gpio_num = pin,
            .speed_mode = MODO_PWM,
            .channel = channel,
            .timer_sel = TIMER_PWM,
            .duty = 0,
            .hpoint = 0
        };
        ledc_channel_config(&config);
    }

    // Atualiza a intensidade do LED baseada no valor do passo
    void update() {
        intensidade += passo;
        // Inverte o passo ao alcançar os limites de intensidade (0 ou 255)
        if (intensidade > 255 || intensidade < 0) {
            passo = -passo;
            intensidade += passo;
        }
        ledc_set_duty(MODO_PWM, channel, intensidade);
        ledc_update_duty(MODO_PWM, channel);
    }
};

// Instâncias para cada LED com configurações específicas de pino e passo
Led leds[] = {
    {25, LEDC_CHANNEL_0, 0, 10}, // Vermelho com incremento rápido
    {26, LEDC_CHANNEL_1, 0, 5},  // Verde com incremento médio
    {27, LEDC_CHANNEL_2, 0, 15}  // Azul com incremento mais rápido
};

// Configuração inicial do sistema
void setup() {
    Serial.begin(115200); // Inicia a comunicação serial
    // Configura o timer do PWM com as definições especificadas
    ledc_timer_config_t config_timer_pwm = {
        .speed_mode = MODO_PWM,
        .duty_resolution = RESOLUCAO_PWM,
        .timer_num = TIMER_PWM,
        .freq_hz = FREQUENCIA_PWM,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&config_timer_pwm);

    // Configura cada LED chamando o método setup de cada instância
    for (auto &led : leds) {
        led.setup();
    }
}

// Loop principal de execução
void loop() {
    // Atualiza cada LED e imprime a intensidade atual no monitor serial
    for (auto &led : leds) {
        led.update();
    }

    // Exibe os valores atuais das intensidades dos LEDs
    Serial.printf("Ciclo de Trabalho (Vermelho, Verde, Azul): %d, %d, %d\n",
                  leds[0].intensidade, leds[1].intensidade, leds[2].intensidade);
    
    delay(100); // Introduz um delay para tornar a transição visualmente perceptível
}
