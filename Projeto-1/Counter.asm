; Jean Carlos Pereira Cassiano - NUSP: 1864008
; Giovanna de Freitas Velasco - NUSP: 13676346

ORG 0H                ; Início do código
MOV P1, #0FFH         ; Desliga o display de 7 segmentos
MOV DPTR, #DISPLAY_CODES ; Aponta para a tabela de códigos
MOV R0, #0            ; Inicializa o contador em 0
MOV DELAY_TIME, #0    ; Inicializa o delay como zero

; Loop principal com verificação de botões
MAIN:
    ACALL CHECK_BUTTONS        ; Verifica continuamente os botões
    ; Se nenhum botão for pressionado, o código não faz nada

    ; Exibe o número no display e realiza a contagem
    MOV A, R0                  ; Carrega o número atual no acumulador
    MOVC A, @A+DPTR            ; Busca o código de exibição na tabela de códigos
    MOV P1, A                  ; Exibe o número no display de 7 segmentos
    
    ACALL DELAY                ; Chama a sub-rotina de delay
    INC R0                     ; Incrementa o contador
    CJNE R0, #10, MAIN         ; Continua até 9, reinicia em 0
    MOV R0, #0                 ; Reinicia a contagem
    SJMP MAIN                  ; Volta ao loop principal

; Verifica qual botão está pressionado
CHECK_BUTTONS:
    JNB P2.0, SET_DELAY_250MS   ; Se SW0 (P2.0) for pressionado, vai para delay de 0,25 segundos
    JNB P2.1, SET_DELAY_1S      ; Se SW1 (P2.1) for pressionado, vai para delay de 1 segundo
    SJMP CHECK_BUTTONS          ; Se nenhum botão estiver pressionado, continua verificando

; Configura o delay para 0,25 segundos (SW0)
SET_DELAY_250MS:
    MOV DELAY_TIME, #5          ; 5 ciclos de 50 ms = 0,25 segundos
    RET                         ; Retorna para continuar no loop principal

; Configura o delay para 1 segundo (SW1)
SET_DELAY_1S:
    MOV DELAY_TIME, #20         ; 20 ciclos de 50 ms = 1 segundo
    RET                         ; Retorna para continuar no loop principal

; Sub-rotina de delay utilizando Timer 0
DELAY:
    MOV R2, DELAY_TIME          ; Carrega o tempo de delay (multiplicador)
DELAY_LOOP:
    MOV TMOD, #01H              ; Configura Timer 0 no modo 1 (16-bit timer)
    MOV TH0, #3CH               ; Parte alta do Timer (ajustado para cerca de 50 ms)
    MOV TL0, #0B0H              ; Parte baixa do Timer (ajustado para cerca de 50 ms)
    SETB TR0                    ; Inicia o Timer 0
WAIT_DELAY:
    JNB TF0, WAIT_DELAY         ; Espera até que TF0 seja setado (transbordo do Timer 0)
    CLR TR0                     ; Para o Timer 0
    CLR TF0                     ; Limpa a flag TF0
    DJNZ R2, DELAY_LOOP         ; Decrementa R2 e repete até que R2 chegue a zero
    RET                         ; Retorna após o delay

; Tabela de códigos do display de 7 segmentos para números de 0 a 9
DISPLAY_CODES:
    DB 0C0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H, 80H, 90H

; Área de dados
DELAY_TIME: DB 00H              ; Inicialmente, sem delay configurado

END
