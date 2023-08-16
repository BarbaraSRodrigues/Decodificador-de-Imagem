# Decodificador-de-Imagem
Trabalho feito para a disciplina de Processamento de Imagens. Pega as imagens codificadas e faz a decodificação delas de acordo com a codificação feita. Essa codificação consiste em trabalhar com os bits menos significativos

## Objetivo
O objetivo desse atividade é explorar os conceitos de cores e de codificação e decodificação utilizados nos formatos de imagens.
## Problema
O termo esteganografia deriva da junção das palavras gregas estegano que significa “esconder ou mascarar”, e grafia, que significa “escrita”. Portanto, esteganografia pode ser compreendida como a arte de esconder informações, tornando-as ocultas, assim como a criptografia. O
objetivo desta técnica é que esses dados não sejam percebidos por terceiros; ou seja, a presença de mensagens escondidas dentro de arquivos é simplesmente desconhecida. Somente o receptor
da mensagem tem conhecimento de sua existência, assim como da maneira como extraí-la.
Apesar de parecer, a esteganografia e a criptografia são duas áreas com objetivos bastante
diferentes. Enquanto o segundo tem o propósito de impedir que as pessoas saibam o conteúdo
de uma mensagem, o primeiro se baseia em evitar que as pessoas saibam que a mensagem
escondida existe. Ou seja, na criptografia, os receptores sabem da existência das mensagens,
porém não conseguem, a princípio, lê-las; a esteganografia tenta fazer com que os receptores
não percebam que há uma mensagem naquele meio (imagem, texto, etc.).
Existem várias formas de esconder mensagens ou arquivos em imagens. Uma das técnicas
possíveis é modificar alguns bits (menos relevantes) dos pixels da imagem, com as informações
que se quer esconder. Por exemplo, a modificação do bit menos significativo de uma banda
(red) de um pixel de uma imagem colorida não é perceptível ao olho humano. A esteganoanálise
dessa modificação, no entanto, não é difícil de se realizar a partir da comparação do arquivo
original e do arquivo modificado. O ruído, calculado como a diferença desses dois arquivos é a mensagem codificada.

## Descrição:

Um arquivo está escondido na imagem .PPM. O arquivo escondido está codificado nos pixels da imagem da seguinte forma:

- O binário dos códigos ASCII do nome original do arquivo (finalizado pelo caractere zero)
- O binário do tamanho do arquivo (em quatro bytes)
- E os bytes do arquivo.

Os bits (zero ou um) das representações binárias estão armazenados, modificando as bandas R, G e B dos pixels em sequência. Por exemplo, considerando a imagem colorida:<br>
|r1 g1 b1| |r2 g2 b2| |r3 g3 b3| |r4 g4 b4| |r5 g5 b5| |r6 g6 b6| |r7 g7 b7| |r8 g8 b8| |r9 g9 b9| |r10 g10 b10| |r11 g11 b11| |r12 g12 b12|

Seja 'A', a primeira letra do nome do arquivo (cujo código ASCII binário é 01000001). Na codificação do arquivo, a letra 'A' modifica as seguintes bandas dos pixels iniciais (identificados em letras maiúsculas e com cores).<br>
|R1 g1 b1| |r2 G2 b2| |r3 g3 B3| |R4 g4 b4| |r5 G5 b5| |r6 g6 B6| |R7 g7 b7| |r8 G8 b8| |r9 g9 b9| |r10 g10 b10| |r11 g11 b11| |r12 g12 b12|

Onde:

- R1 = r1 & 0xFE, codifica o bit zero (0)
- G2 = g2 | 0x01, codifica o bit um (1)
- B3 = b3 & 0xFE, codifica o bit zero (0)
- R4 = r4 & 0xFE, codifica o bit zero (0)
- G5 = g5 & 0xFE, codifica o bit zero (0)
- B6 = b6 & 0xFE, codifica o bit zero (0)
- R7 = r7 & 0xFE, codifica o bit zero (0)
- G8 = g8 | 0x01, codifica o bit um (1)

A operação R1 = r1 & 0xFE, que executa um and-bit-a-bit com a máscara 0xFE, tem o efeito de transformar o último bit da banda R para zero. De forma simétrica, a operação G2 = g2 | 0x01, que executa um or-bit-a-bit com a máscara 0x01, tem o efeito de transformar o último bit da banda G para um, e assim sucessivamente.

Depois da codificação do nome do arquivo, os quatro bytes seguintes definem a quantidade de bytes do arquivo, e dessa forma, a quantidade de pixels que estão modificados no restante da imagem.

**Exemplo:**<br>

**Arquivo original:**<br>
P3<br>
#C r e a t e d w i t h GIMP<br>
10 10<br>
255<br>
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>
0 0 0 140 26 26 197 40 40 197 40 40 140 26 26 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>
0 0 0 197 40 40 209 43 43 209 43 43 197 40 40 40 140 26 59 197 40 59 197 40 40 140 26 0 0 0<br>
0 0 0 197 40 40 209 43 43 166 53 144 85 61 197 61 197 85 63 209 43 63 209 43 59 197 40 0 0 0<br>
0 0 0 140 26 26 197 40 40 85 61 197 43 63 209 61 198 90 63 209 43 63 209 43 59 197 40 0 0 0<br>
0 0 0 0 0 0 0 0 0 40 59 197 43 63 209 53 147 166 61 197 85 59 197 40 40 140 26 0 0 0<br>
0 0 0 0 0 0 0 0 0 26 40 140 40 59 197 40 59 197 26 40 140 0 0 0 0 0 0 0 0 0<br>
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>

**Arquivo modificado:**<br>
P3<br>
#CREATOR: Image P r o c e s s i n g u s i n g C=A n s i = ByDu<br>
#<br>
10 10<br>
255<br>
0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0<br>
0 1 0 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 1 1 0 0 0 1 0<br>
0 0 0 141 26 26 197 40 40 197 40 40 140 26 26 0 1 0 0 0 1 1 0 0 0 1 0 0 0 0<br>
0 0 0 197 40 40 209 43 42 209 43 43 197 41 40 40 140 27 58 197 40 59 197 40 40 140 26 0 0 0<br>
0 0 0 197 40 40 208 43 43 166 52 144 85 61 196 60 197 85 63 208 43 63 209 42 58 197 40 0 0 0<br>
0 0 0 140 26 26 197 40 40 85 61 196 42 63 209 61 198 90 63 209 42 62 209 43 59 196 40 0 0 0<br>
0 0 0 0 0 0 0 0 0 40 59 197 43 62 209 53 147 166 60 197 85 59 196 40 40 140 26 0 0 0<br>
0 0 0 0 0 0 0 0 0 26 40 140 40 59 196 40 59 197 26 40 140 0 0 0 1 0 0 0 0 0<br>
0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0<br>
1 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>

Para incluir o arquivo de nome ’A.txt’, com os seguintes 2 bytes:
42

Cuja codificação(nome, tamanho e os bytes) em binário é:<br>
A( 41 ) 01000001 . ( 2E) 00101110<br>
2 t ( 74 ) 01110100 x ( 78 ) 01111000 t ( 74 ) 01110100 ( 0 ) 00000000 // nome<br>
3 ( 0 ) 00000000 ( 0 ) 00000000 ( 0 ) 00000000 ( 2 ) 00000010 // tamanho<br>
4 4 ( 34 ) 00110100 2 ( 32 ) 00110010 // bytes<br>

Pode-se observar ainda que, considerando esse esquema de codificação, para que um arquivo possa ser escondido numa imagem, o número de pixels da imagem deve ser suficiente para a codificação do arquivo. Sejam:

- TN (Tamanho do Nome) = o número de letras do nome do arquivo somado de um (caractere zero no fim do nome);
- TA (Tamanho do arquivo) = quatro bytes usados para codificar o tamanho do arquivo;
- NB (Número de bytes) = número de bytes do arquivo a ser ocultado;
- nlinhas = número de linhas da imagem;
- ncolunas = número de colunas da imagem.

Assim, o arquivo só pode ser esteganografado na imagem se:<br>
8 × (TN + TA + NA) ≤ nlinhas × ncolunas.

No exemplo anterior, TN = 6, TA = 4, NB = 2, o que soma 12 * 8 pixels que foram afetados, ou seja, 96 pixels da imagem com 100 pixels (10 linhas e 10 colunas) foram modificados para codificar o arquivo.

Considerando esse esquema de codificação do arquivo na imagem, esse
