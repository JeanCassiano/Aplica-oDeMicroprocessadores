// Pinos utilizados para comunicacao com o display LCD
// Configuracoes parecidas com as que o professor utilizou em seus exemplos
sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;


// Direcao do fluxo de dados nos pinos selecionados
// Configuracoes parecidas com as que o professor utilizou em seus exemplos
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

void main() {
    unsigned int adcValue;
    float temperature;
    char text[16];  // Array para armazenar o valor formatado como string

    // Configuração do ADC para usar referências externas
    ADCON1 = 0b00001110;  // AN2 como Vref+ e AN3 como Vref-
    ADC_Init();           // Inicializa o módulo ADC
    
    // Configuracao do LCD
    Lcd_Init();  // Inicializa o LCD
    Lcd_Cmd(_LCD_CLEAR);  // Limpa o display
    Lcd_Cmd(_LCD_CURSOR_OFF);  // Desliga o cursor

    Lcd_Out(1, 1, " Temp:"); // Escreve "Temp:" no display LCD 
    while (1) {
        adcValue = ADC_Get_Sample(0);  // Leitura do valor do canal AN0 (RA0)

        // Converte o valor ADC para temperatura (LM35: 10mV/ºC)
        temperature = (adcValue * 5.0 / 1023.0) * 100.0;  // Calcula a temperatura em ºC

        // Usa sprintf para converter o valor float em string
        FloatToStr(temperature, text);
        text[5] = '\0'; // Limita a string para tamanho de 5, assim, fazendo o valor ficar com duas casas decimais apenas

        Lcd_Out(1, 6, text);  // Exibe o valor da temperatura na primeira linha
        Lcd_Chr(1, 12, 223);  // Exibe o simbolo de graus
        Lcd_Out(1, 13, "C");  // Exibe o "C" de Celsius

        Delay_ms(500);  // Pequena pausa para atualizacao
    }
}