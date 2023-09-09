# Campo-minado-lab2

## Jogo realizado na linguagem C para a matéria de Laboratório de Programação 2, da Universidade Federal de Santa Maria
Para a construção do jogo, foi usada a biblioteca SDL

# IMPLEMENTAÇÕES

## Matriz alocada dinamicamente;
## Jogador consegue alterar o tamanho do campo, variando de 12 x 12 até 18 x 18;

## Bot consegue jogar, (o testei várias vezes, ocorreram alguns bugs algumas vezes, mas, na maioria das vezes ele funcionou normalmente).

# Lógica de funcionamento do Bot
- Procura por célula a qual tem certeza que não é bomba;
- Se não encontrar, procura por célula que tem certeza que é bomba, se encontrar, a marca com uma bandeira;
- Se não encontrar, sorteia uma célula totalmente ao acaso para abrir;
- Para sortear, ele cria uma lista encadeada com as informações de linhas e colunas das células que ainda não foram abertas e não são bandeiras.

# Para compilar o trabalho
- Para a construção, utilizei o Visual Studio 2022;
- Utilizei a biblioteca SDL2, a qual, os arquivos já estão contidos neste diretório;
- Para a configuração do SDL no Visual Studio, recomendo este vídeo: https://www.youtube.com/watch?v=13AEnd8XB70&t=6s;
- Lembrando que os arquivos já estão presentes no diretório, será necessário, apenas, linkar corretamente os caminhos;
- Será necessário incluir o diretório header, como Aditional Includes, o qual estará presente em C:\{caminho}\Campo minado\Campo minado\header
- Trabalho feito em Windows, passo a passo para funcionamento em Windows, também;


