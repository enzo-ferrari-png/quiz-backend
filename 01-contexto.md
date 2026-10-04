# Passos 1 a 3 — Contexto, minimundo e requisitos

Marco M1. Copiem para `entregas/01-contexto.md`.

## 1. Introdução e contexto

Em um parágrafo: o que é o Tech Trivia e qual o objetivo deste banco.

Escopo. Listem só o que o banco faz e o que fica de fora.

| O banco faz:
Armazenar as 50 perguntas
enunciado
alternativas
resposta correta, se houver
categoria da pergunta
Organizar as perguntas por categorias, por exemplo:
IA básica
criatividade
estratégia
colaboração
situações profissionais
Fornecer os dados para o JavaScript quando o quiz precisar carregá-los.
Facilitar a alteração das perguntas sem precisar modificar diretamente o código da página.


 | O banco não faz:
 deixar a página bonita → CSS
criar botões/interface → HTML
fazer o botão "Começar Quiz" funcionar → JavaScript
passar para a próxima pergunta → JavaScript
detectar que o usuário clicou em uma alternativa → JavaScript
mostrar/esconder as telas → JavaScript
calcular o perfil do usuário se essa lógica estiver no JavaScript.
decidir como a interface deve ser visualmente → design/CSS


Usuários. Quem usa o sistema e o que cada um faz com os dados. Não criem tabela de usuário se nenhum requisito pedir cadastro, senha ou sessão.

| Usuário | 

O que faz: 
|Clica em Começar Quiz
Lê a pergunta
Escolhe uma alternativa
Clica em Próxima
Repete até terminar
Recebe o resultado/perfil no final

| Quem cadastra perguntas:
A equipe que desenvolveu o sistema.

## 2. Minimundo

Um ou dois parágrafos, na voz de quem encomenda o sistema. É deste texto que saem as entidades e as regras. Cubram pergunta, categoria, fonte, publicador, idioma e alternativas, inclusive a possibilidade de mais de duas alternativas no futuro.

Em 1–2 parágrafos, escrito na voz de quem está encomendando o sistema, cobrindo:

perguntas;
categorias;
fontes;
publicadores;
idiomas;
alternativas;
possibilidade de futuramente ter mais de duas alternativas.

Somos uma escola e queremos um gerador de questões de Biologia para treino. Cada questão possui um código estável, um título, um enunciado e uma explicação do gabarito, sendo esses três textos obrigatórios. Cada questão pertence a um único assunto e possui um único nível de dificuldade, definido por um conjunto controlado. As questões possuem alternativas identificadas por letras e uma única alternativa correta. No futuro, queremos permitir diferentes quantidades de alternativas sem precisar alterar a estrutura da questão.

Cada questão possui uma única referência, que pode ser um capítulo de livro ou artigo, contendo título, URL e idioma. Uma mesma referência pode ser utilizada por várias questões e cada referência é publicada por uma editora. O idioma pertence a um conjunto controlado. Para facilitar a busca, uma questão pode possuir zero ou mais palavras-chave, e uma mesma palavra-chave pode ser utilizada em várias questões.

> 

## 3. Requisitos e regras de negócio

Cada RD01–RD11 e cada RA01–RA07 entra numa linha. Não deixem código de fora.

| Código | Texto do requisito | Tipo |
|---|---|---|
| RD01 | Toda questão tem código estável, título, enunciado e explicação, todos obrigatórios. Enunciado e explicação podem ser longos. | regra de negócio |
| RD02 | Toda questão pertence a exatamente um assunto. Não há dois assuntos com o mesmo nome. | regra de negócio |
| RD03 | Toda questão tem exatamente um nível de dificuldade, de um conjunto controlado com código e descrição. | regra de negócio |
| RD04 | Toda questão tem alternativas identificadas por letra, cada uma com texto. A mesma letra não se repete na mesma questão. | regra de negócio |
| RD05 | Exatamente uma alternativa de cada questão é a correta. | regra de negócio |
