# Atividade 02 - Questões Pós-Aula

## Jean Carlos Pereira Cassiano - NUSP: 13864008 <br> Giovanna de Freitas Velasco - NUSP: 13676346

### Questão 3
*Recorra ao exemplo do microcontrolador aplicado ao controle de um elevador que foi apresentado em aula, disponível nas transparências do Cap. 1. De acordo com seu ponto de vista, quais as vantagens de se utilizar um microcontrolador para aquele tipo de aplicação e qual deve ser o “perfil” de um microcontrolador ideal para aquela aplicação do elevador em termos de capacidade da CPU (baixa, média ou alta), quantidade de bits  no barramento, e precisão no tratamento das informações (operação somente com inteiros ou ponto flutuante?)*

Um microcontrolador ideal para o controle de um elevador deve ter uma CPU de capacidade baixa a média, com barramento de 8 ou 16 bits, e operar predominantemente com inteiros. As vantagens incluem baixo custo, simplicidade de implementação, baixo consumo de energia, tamanho compacto, e alta confiabilidade.


### Questão 4

*Quanto às portas paralelas de um microcontrolador:*

( ) São somente de entrada.

( ) São somente de saída.

( ) Cada palavra (A, B, C, P1, P2, P3…) pode ser configurada como entrada ou saída.

(X) Cada bit pode ser configurado como entrada ou saída.

( ) Cada palavra (A, B, C... P1, P2, P3…) pode ser configurada como entrada, saída ou
bidirecional.

( ) Cada bit pode ser configurado como entrada, saída ou bidirecional

### Questão 5

*Assinale V para verdadeiro e F para falso nas afirmações abaixo:*

(V) No modelo de Von Neumann, o microprocessador segue as instruções armazenadas na memória ROM (programas), lê as entradas e envia comandos sobre os canais de saída, alterando as informações contidas na memória RAM.

(F) Os registradores Special Function Registers localizam-se sempre internos à CPU.

(F) O ciclo de máquina é composto pelo ciclo de busca mais o ciclo de execução, cada qual demorando um pulso de clock.

(V) A instrução “CLR A” não possui operando e gasta apenas 1 ciclo de máquina

(V) A arquitetura Von Neumann é considerada uma arquitetura mais simples do que a arquitetura Harvard porque utiliza o mesmo barramento para o tráfego de dados e de instruções.

(V) A técnica de pipeline é impossível de ser utilizada em computadores de arquitetura Von Neumann.


### Questão 6

*Indique quais afirmativas se aplicam a uma instrução CISC e quais a uma instrução RISC:*

➔ *Os programas são mais complexos:* RISC, visto que menos instruções disponíveis resultam em programas mais complexos.

➔ *A maioria das instruções tem a mesma duração:* RISC, já que as instruções são simples e geralmente executadas em um ciclo de clock, exceto as de "salto".

➔ *Mais instruções disponíveis:* CISC, ele possui um conjunto de instruções mais amplo e complexo.

➔ *Programas menores:* CISC visto que é necessário um menor número de instruções necessárias para realizar uma tarefa, resultando em programas menores

➔ *Utiliza menos espaço na memória de programa:* RISC, devido à maior densidade de instruções, menos espaço é necessário.

➔ *Processamento de cada instrução é mais lento:* CISC, as instruções possuem durações diferentes.

➔ *Microcontroladores PIC, AVR, ARM:* RISC.

➔ *Tempo de execução das instruções depende da frequência do clock:* CISC


### Questão 7


*Questão 7 - Abaixo é apresentado o diagrama de um microcontrolador. Qual a arquitetura utilizada e como chegamos a essa conclusão? Quantas portas I/O bidirecional e quantas linhas (bits/pinos) são endereçados de forma individual neste microcontrolador, com base neste diagrama?*

![image](https://github.com/user-attachments/assets/8dd0a735-4720-401a-a811-e821e7c135ea)


Trata-se de uma arquitetura Von Neumann, visto que a CPU se comunica tanto com a memória de programa (FLASH) quanto com a memória de dados (RAM) através de um único barramento. Isso é indicado pelo "BUS CONTROL" que conecta tanto a memória RAM quanto a memória FLASH à CPU.
O diagrama mostra um bloco denominado "4 I/O PORTS", indicando que existem 4 portas de entrada/saída (P0, P1, P2, P3) que são bidirecionais.
Cada uma dessas 4 portas I/O geralmente possui 8 bits, dado que as portas em microcontroladores são normalmente endereçadas por byte. Assim, se cada porta possui 8 pinos, ao todo seriam 32 pinos (4 portas x 8 bits/pinos por porta) que podem ser endereçados de forma individual.
