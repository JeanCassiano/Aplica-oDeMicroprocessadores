# Atividade 03 - Questões Pós-Aula

## Jean Carlos Pereira Cassiano - NUSP: 13864008 <br> Giovanna de Freitas Velasco - NUSP: 13676346

### Questão 8

*No simulador EdSim51, digite e execute (clicando em "Assm") as instruções abaixo:*

```assembly
MOV R0, #22h
MOV 00h, #22h
```

*Qual a diferença entre as duas instruções acima? Tente refletir porque possuem ciclos
de máquina diferentes se a operação é realizada na mesma posição de memória RAM
(00h ou R0 usa o mesmo espaço).*


```assembly
MOV A, #22h
MOV ACC, #22h
```

*Qual a diferença entre as duas instruções acima? Tente refletir sobre a diferença de usar
A ou ACC e sobre porque possuem ciclos de máquina diferentes se a operação realizada
é a mesma.*

Para a primeira parte, temos que a instrução `MOV R0, #22h` move o valor imediato 22h para o registrador R0, que é um registrador interno do microcontrolador. A operação é direta e rápida, exigindo apenas 1 microssegundo para ser executada. Já a instrução `MOV 00h, #22h` move o valor imediato 22h para o endereço de memória 00h, que é o primeiro byte da memória RAM interna. Como essa operação envolve acesso à memória, ela é mais lenta e requer 2 microssegundos para ser completada.

Para a segunda parte, a instrução `MOV A, #22h` Move o valor imediato 22h para o acumulador A. Esta operação é rápida e direta, exigindo apenas 1 microssegundo para ser executada. Para a segunda instrução, `MOV ACC, #22h`, instrução realiza a mesma operação, movendo 22h para o acumulador. Contudo, o uso do nome alternativo ACC pode causar um pequeno overhead na execução, resultando em 2 microssegundos para completar a operação.

### Questão 9

*A figura abaixo mostra um microcontrolador genérico de 8 bits com 4 registradores internos à CPU, os quais são: Instruction Register (IR), Program Counter (PC), Accumulator (ACC) e Data Pointer (DPTR).*

![image](https://github.com/user-attachments/assets/269efebd-f418-4adf-b7bc-aa73fc20f76e)

*Baseado na figura, responda às questões com verdadeiro (V) ou falso (F):*

(V) Trata-se de um microcontrolador de arquitetura Harvard. <br>
(F) A memória EEPROM é de 4Kbytes e armazena as instruções que comandam o microcontrolador.<br>
(F) A memória SRAM é de 512 bytes e armazena dados voláteis.<br>
(F) O registrador IR tem a função de armazenar a instrução lida da memória SRAM.<br>
(V) Para esse microcontrolador, o registrador IR deve ser de 8 bits.<br>
(V) O registrador PC armazena o endereço da instrução lida da memória EEPROM.<br>
(F) Para esse microcontrolador, o registrador PC deve ser de 10 bits.<br>
(V) Para esse microcontrolador, o registrador ACC deve ser de 8 bits.<br>
(F) O registrador DPTR é um ponteiro que aponta para a última instrução lida da memória.<br>
(F) Para esse microcontrolador, o registrador DPTR deve ser de 10 bits.
