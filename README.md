# Base Defense Game

Este jogo é o projeto final de uma disciplina do curso BTI na UFRN, utilizando C++ e a biblioteca SFML. O objetivo do jogo é proteger sua base contra os inimigos enquanto coleta munição e sobrevive por um determinado período de tempo.

## Descrição

O jogador assume o papel de um soldado que deve defender a sua base em um ambiente 2D. Inimigos aparecem aleatoriamente pelo mapa, avançando e atirando em direção ao jogador, que está protegido enquanto estiver dentro da base. O jogador precisa defender a sua base atirando nos inimigos e coletando a munição deixada por eles quando derrotados. O objetivo é sobreviver durante 80 segundos, derrotando os inimigos antes que eles destruam a base ou derrotem o soldado.

## Funcionalidades

- Movimentação do jogador
- Disparo de projéteis
- Geração aleatória de Inimigos
- Coleta de Munição
- Regeneração da base
- Sistema de Pausa
- Gerenciamento de tempo
- Dificuldade baseada no tempo restante

## Instruções

![base-defense-game-img](https://github.com/user-attachments/assets/dee2b1c2-2c27-4aae-acb3-13799f9dab98)

### Como jogar

- **Movimentação do jogador:** Use as teclas **W**, **A**, **S**, **D** para mover o personagem pela tela.
- **Pausar o jogo:** Pressione a tecla **P** para pausar ou despausar o jogo.
- **Atirar:** Utilize o botão esquerdo do mouse para disparar projéteis contra os inimigos.

## Tecnologias Utilizadas

- **C++**: Linguagem de programação utilizada para o desenvolvimento do jogo.
- **Git**: Sistema de controle de versão usado para gerenciar o código-fonte do projeto.

## Dependências

- **Compilador g++**
- **Biblioteca SFML v2.5.1**
- **Servidor x11 (linux)**

## Instalação e Compilação

Para clonar o repositório utilize os seguintes comandos:
```bash
git clone https://github.com/SebastiaoFellipe/Base-Defense-Game.git
cd Base-Defense-Game
```

### Linux

Execute os seguintes comandos para instalar as dependências necessárias:
```bash
sudo apt-get update
sudo apt-get install build-essential libsfml-dev xserver-xorg-core
```

Para compilar utilize o arquivo Makefile incluído no repositório. Execute o seguinte comando na raiz do projeto para gerar o executável:
```bash
make
```

Certifique-se de que o servidor X11 está em execução e use o comando:
```bash
export DISPLAY=:0
```

Para rodar o jogo, execute:
```bash
./BaseDefenseGame
```

## Windows

O tutorial de instalação no Windows ainda não está finalizado. No entanto, você pode tentar baixar as dependências por conta própria seguindo os passos abaixo:

1. **Baixar e instalar o MinGW**
- Certifique-se de incluir o compilador `g++` para compilar o código em C++.

2. **Baixar a biblioteca SFML**
- Baixe e extraia o arquivo da SFML.
- Coloque a pasta extraída na raiz do projeto e renomeie-a para `sfml`.

3. **Instalar o Make**
- Instale o `Make` para poder utilizar o makefile do projeto.

4. **Configurar o Makefile**
- Faça as seguintes alterações no makefile para que o compilador encontrar o caminho da biblioteca SFML.
  - Na variável `FLAGS`, substitua `-I/usr/local/include` por `-Isfml/include`.
  - No inicio da variável `LIBS`, adicione `-Lsfml/lib`.
  - Substitua o comando da regra `clean` por:
    ```batch
    del /Q "%BUILD_DIR%\*.o" "%TARGET%.exe"
    ```

---
Para compilar utilize o arquivo Makefile incluído no repositório. Execute o seguinte comando na raiz do projeto para gerar o executável:
```bash
make
```

Para rodar o jogo, execute:
```bash
./BaseDefenseGame.exe
```

Se tiver dificuldades ou problemas durante o processo de instalação, você pode procurar por tutoriais específicos para cada dependência ou  Linux, onde o tutorial de instalação está completo.


## Autor

- [@SebastiaoFellipe](https://github.com/SebastiaoFellipe)

## Licença

Este projeto está licenciado sob a [Licença MIT](https://choosealicense.com/licenses/mit/)