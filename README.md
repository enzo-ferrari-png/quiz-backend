# Gerenciador de Perguntas - Quiz de TI

## Projeto Prático em C

Sistema desenvolvido em linguagem C para cadastrar e organizar perguntas que futuramente poderão ser utilizadas em um quiz de orientação sobre cursos da área de Tecnologia da Informação.

O sistema permite gerenciar perguntas relacionadas aos cursos:

- **CC** — Ciência da Computação
- **ES** — Engenharia de Software
- **ADS** — Análise e Desenvolvimento de Sistemas

Nesta etapa, o projeto é voltado apenas para o **gerenciamento das perguntas**. O sistema não realiza o quiz, não calcula pontuação e não indica qual curso combina com o usuário.

## Integrantes

- Lucas Silva Marques
- Matheus dos Santos Chaves
- Estephane Barreto
- Enzo ferrari
- Lucas Oliveira Fernandes da Silva
- Rafael Ramos de Lana

## Funcionalidades

O programa possui as seguintes funcionalidades:

1. Cadastrar pergunta
2. Listar todas as perguntas
3. Consultar perguntas por categoria
4. Consultar perguntas por curso
5. Atualizar pergunta
6. Excluir pergunta
0. Sair

As perguntas são armazenadas no arquivo `perguntas.csv`, utilizando ponto e vírgula (`;`) para separar os campos.

Cada pergunta possui:

- Código
- Texto
- Categoria
- Curso
- Resposta (`SIM` ou `NAO`)

O sistema também possui validações para cursos (`CC`, `ES` e `ADS`), respostas (`SIM` e `NAO`), códigos e entradas inválidas.

## Tecnologias e conceitos utilizados

- Linguagem C
- `struct`
- Funções
- `switch`
- Estruturas de repetição e condicionais
- Manipulação de arquivos
- Arquivos CSV
- `fopen()` e `fclose()`
- `fprintf()` e `fgets()`
- `strtok()`
- `strcpy()` e `strcmp()`

## Arquivos

- `main.c` — código-fonte do programa
- `perguntas.csv` — arquivo utilizado para armazenar as perguntas
- `README.md` — documentação do projeto

## Como compilar

Com o GCC instalado, abra o terminal na pasta do projeto e execute:

```bash
gcc main.c -o quiz
```

## Como executar

### Windows

```bash
quiz.exe
```

### Linux / macOS

```bash
./quiz
```

O arquivo `perguntas.csv` deve estar na mesma pasta do programa para que os dados sejam lidos e armazenados corretamente.





