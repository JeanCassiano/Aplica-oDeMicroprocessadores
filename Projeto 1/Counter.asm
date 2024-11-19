ORG 0H                ; Início do código na posição 0H
MOV P1, #0FFH         ; Desliga o display de 7 segmentos (todos segmentos apagados)
MOV DPTR, #DISPLAY_CODES ; Aponta o DPTR para o início da tabela de códigos de exibição dos números
MOV R0, #0            ; Inicializa o contador em 0 (primeiro número a ser exibido)
MOV DELAY_TIME, #0    ; Inicializa o valor do delay como zero

; Loop principal com verificação de botões
MAIN:
    ACALL CHECK_BUTTONS        ; Verifica continuamente se algum dos botões está pressionado
    ; Se nenhum botão for pressionado, o código fica parado nesta rotina

    ; Quando é detectado que um botão foi pressionado, exibe o número atual no display de 7 segmentos e realiza a contagem
    MOV A, R0                  ; Carrega o valor do contador (0-9) no acumulador
    MOVC A, @A+DPTR            ; Usa o valor no acumulador como índice na tabela para obter o código de exibição do número
    MOV P1, A                  ; Exibe o número no display de 7 segmentos

    ACALL DELAY                ; Aguarda o tempo de delay configurado antes de continuar

    INC R0                     ; Incrementa o contador para o próximo número
    CJNE R0, #10, MAIN         ; Verifica se o contador chegou a 10; se não, continua o loop

    MOV R0, #0                 ; Reinicia o contador para 0 após atingir 9
    SJMP MAIN                  ; Repete o loop principal

; Rotina de verificação de botões (CHECK_BUTTONS)
; Esta rotina define o tempo de delay com base no botão pressionado
CHECK_BUTTONS:
    JNB P2.0, SET_DELAY_250MS   ; Se SW0 (P2.0) for pressionado, configura o delay para 0,25 segundos
    JNB P2.1, SET_DELAY_1S      ; Se SW1 (P2.1) for pressionado, configura o delay para 1 segundo
    SJMP CHECK_BUTTONS          ; Se nenhum botão estiver pressionado, repete a verificação continuamente

; Configura o delay para 0,25 segundos
SET_DELAY_250MS:
    MOV DELAY_TIME, #5          ; Define o delay para 0,25 segundos (5 ciclos de 50 ms cada)
    RET                         ; Retorna para o loop principal

; Configura o delay para 1 segundo
SET_DELAY_1S:
    MOV DELAY_TIME, #20         ; Define o delay para 1 segundo (20 ciclos de 50 ms cada)
    RET                         ; Retorna para o loop principal


; Sub-rotina de delay usando o Timer 0 (DELAY)
; Esta sub-rotina gera um atraso controlado pelo Timer 0 baseado no valor de DELAY_TIME
DELAY:
    MOV R2, DELAY_TIME          ; Carrega o número de ciclos de delay necessários em R2
DELAY_LOOP:
    MOV TMOD, #01H              ; Configura Timer 0 no modo 1 (16-bit timer)
    MOV TH0, #3CH               ; Carrega o valor alto para o Timer, ajustado para ~50 ms
    MOV TL0, #0B0H              ; Carrega o valor baixo para o Timer 
    SETB TR0                    ; Inicia o Timer 0
WAIT_DELAY:
    JNB TF0, WAIT_DELAY         ; Espera o transbordo do Timer 
    CLR TR0                     ; Para o Timer

    CLR TF0                     ; Limpa a flag de transbordo do Timer 0

    DJNZ R2, DELAY_LOOP         ; Decrementa R2 e repete o loop até que o número de ciclos esteja completo
    RET                         ; Retorna ao loop principal após o delay

; Tabela de códigos do display de 7 segmentos para os números de 0 a 9
; Cada valor define a combinação de segmentos que forma o dígito correspondente
DISPLAY_CODES:
    DB 0C0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H, 80H, 90H

; Área de dados
DELAY_TIME: DB 00H              ; Armazena o número de ciclos de delay

END
