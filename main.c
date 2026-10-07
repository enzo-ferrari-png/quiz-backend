#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "perguntas.csv"

typedef struct {
    int id;
    char texto[250];
    char categoria[50];
    char curso[10];
    char resposta[4];
} Pergunta;

/* Limpa o restante da entrada do teclado */
void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Remove o \n lido pelo fgets */
void removerEnter(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

/* Verifica se o curso é CC, ES ou ADS */
int cursoValido(char curso[]) {
    return strcmp(curso, "CC") == 0 ||
           strcmp(curso, "ES") == 0 ||
           strcmp(curso, "ADS") == 0;
}

/* Verifica se a resposta é SIM ou NAO */
int respostaValida(char resposta[]) {
    return strcmp(resposta, "SIM") == 0 ||
           strcmp(resposta, "NAO") == 0;
}

/* Procura uma pergunta pelo ID e devolve sua posição no arquivo */
int encontrarPergunta(int id, Pergunta *resultado) {
    FILE *arquivo;
    char linha[400];
    char *campo;
    int idArquivo;

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        campo = strtok(linha, ";");
        if (campo == NULL) {
            continue;
        }

        idArquivo = atoi(campo);

        if (idArquivo == id) {
            resultado->id = idArquivo;

            campo = strtok(NULL, ";");
            if (campo != NULL)
                strcpy(resultado->texto, campo);

            campo = strtok(NULL, ";");
            if (campo != NULL)
                strcpy(resultado->categoria, campo);

            campo = strtok(NULL, ";");
            if (campo != NULL)
                strcpy(resultado->curso, campo);

            campo = strtok(NULL, ";\n");
            if (campo != NULL)
                strcpy(resultado->resposta, campo);

            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

/* Cadastra uma nova pergunta */
void cadastrarPergunta() {
    FILE *arquivo;
    Pergunta p;

    printf("\n===== CADASTRAR PERGUNTA =====\n");

    printf("Codigo: ");
    if (scanf("%d", &p.id) != 1) {
        printf("Codigo invalido!\n");
        limparEntrada();
        return;
    }
    limparEntrada();

    if (p.id <= 0) {
        printf("O codigo deve ser maior que zero!\n");
        return;
    }

    if (encontrarPergunta(p.id, &p)) {
        printf("Ja existe uma pergunta com esse codigo!\n");
        return;
    }

    printf("Pergunta: ");
    fgets(p.texto, sizeof(p.texto), stdin);
    removerEnter(p.texto);

    if (strlen(p.texto) == 0) {
        printf("A pergunta nao pode estar vazia!\n");
        return;
    }

    /* Evita quebrar o formato do CSV */
    if (strchr(p.texto, ';') != NULL) {
        printf("A pergunta nao pode conter ';'.\n");
        return;
    }

    printf("Categoria: ");
    fgets(p.categoria, sizeof(p.categoria), stdin);
    removerEnter(p.categoria);

    if (strlen(p.categoria) == 0) {
        printf("A categoria nao pode estar vazia!\n");
        return;
    }

    if (strchr(p.categoria, ';') != NULL) {
        printf("A categoria nao pode conter ';'.\n");
        return;
    }

    printf("Curso (CC/ES/ADS): ");
    fgets(p.curso, sizeof(p.curso), stdin);
    removerEnter(p.curso);

    if (!cursoValido(p.curso)) {
        printf("Curso invalido! Use CC, ES ou ADS.\n");
        return;
    }

    printf("Resposta (SIM/NAO): ");
    fgets(p.resposta, sizeof(p.resposta), stdin);
    removerEnter(p.resposta);

    if (!respostaValida(p.resposta)) {
        printf("Resposta invalida! Use SIM ou NAO.\n");
        return;
    }

    arquivo = fopen(ARQUIVO, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para cadastro!\n");
        return;
    }

    fprintf(arquivo, "%d;%s;%s;%s;%s\n",
            p.id, p.texto, p.categoria, p.curso, p.resposta);

    fclose(arquivo);

    printf("Pergunta cadastrada com sucesso!\n");
}

/* Lista todas as perguntas */
void listarPerguntas() {
    FILE *arquivo;
    Pergunta p;
    char linha[400];
    char *campo;
    int encontrou = 0;

    printf("\n===== TODAS AS PERGUNTAS =====\n");

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Nenhuma pergunta cadastrada ou arquivo inexistente.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        campo = strtok(linha, ";");
        if (campo == NULL)
            continue;

        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.curso, campo);

        campo = strtok(NULL, ";\n");
        if (campo != NULL)
            strcpy(p.resposta, campo);

        printf("\n[%d] %s\n", p.id, p.texto);
        printf("Categoria: %s | Curso: %s | Resposta: %s\n",
               p.categoria, p.curso, p.resposta);

        encontrou = 1;
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhuma pergunta encontrada.\n");
    }
}

/* Consulta perguntas por categoria */
void consultarPorCategoria() {
    FILE *arquivo;
    Pergunta p;
    char linha[400];
    char categoria[50];
    char *campo;
    int encontrou = 0;

    printf("\n===== CONSULTAR POR CATEGORIA =====\n");
    printf("Categoria desejada: ");
    fgets(categoria, sizeof(categoria), stdin);
    removerEnter(categoria);

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Erro: arquivo de perguntas nao encontrado.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        campo = strtok(linha, ";");
        if (campo == NULL)
            continue;

        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.curso, campo);

        campo = strtok(NULL, ";\n");
        if (campo != NULL)
            strcpy(p.resposta, campo);

        if (strcmp(p.categoria, categoria) == 0) {
            printf("[%d] %s - %s - %s\n",
                   p.id, p.texto, p.curso, p.resposta);
            encontrou = 1;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhuma pergunta encontrada nessa categoria.\n");
    }
}

/* Consulta perguntas por curso */
void consultarPorCurso() {
    FILE *arquivo;
    Pergunta p;
    char linha[400];
    char curso[10];
    char *campo;
    int encontrou = 0;

    printf("\n===== CONSULTAR POR CURSO =====\n");
    printf("Curso (CC/ES/ADS): ");
    fgets(curso, sizeof(curso), stdin);
    removerEnter(curso);

    if (!cursoValido(curso)) {
        printf("Curso invalido! Use CC, ES ou ADS.\n");
        return;
    }

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Erro: arquivo de perguntas nao encontrado.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        campo = strtok(linha, ";");
        if (campo == NULL)
            continue;

        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.curso, campo);

        campo = strtok(NULL, ";\n");
        if (campo != NULL)
            strcpy(p.resposta, campo);

        if (strcmp(p.curso, curso) == 0) {
            printf("[%d] %s - %s - %s\n",
                   p.id, p.texto, p.categoria, p.resposta);
            encontrou = 1;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhuma pergunta encontrada para esse curso.\n");
    }
}

/* Atualiza uma pergunta usando um arquivo temporario */
void atualizarPergunta() {
    FILE *arquivo;
    FILE *temporario;
    Pergunta p;
    char linha[400];
    char *campo;
    int id;
    int encontrou = 0;

    printf("\n===== ATUALIZAR PERGUNTA =====\n");

    printf("Codigo da pergunta: ");
    if (scanf("%d", &id) != 1) {
        printf("Codigo invalido!\n");
        limparEntrada();
        return;
    }
    limparEntrada();

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Erro: arquivo de perguntas nao encontrado.\n");
        return;
    }

    temporario = fopen("temporario.csv", "w");

    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        campo = strtok(linha, ";");
        if (campo == NULL)
            continue;

        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.curso, campo);

        campo = strtok(NULL, ";\n");
        if (campo != NULL)
            strcpy(p.resposta, campo);

        if (p.id == id) {
            encontrou = 1;

            printf("Nova pergunta: ");
            fgets(p.texto, sizeof(p.texto), stdin);
            removerEnter(p.texto);

            printf("Nova categoria: ");
            fgets(p.categoria, sizeof(p.categoria), stdin);
            removerEnter(p.categoria);

            printf("Novo curso (CC/ES/ADS): ");
            fgets(p.curso, sizeof(p.curso), stdin);
            removerEnter(p.curso);

            printf("Nova resposta (SIM/NAO): ");
            fgets(p.resposta, sizeof(p.resposta), stdin);
            removerEnter(p.resposta);

            if (strlen(p.texto) == 0 ||
                strlen(p.categoria) == 0 ||
                !cursoValido(p.curso) ||
                !respostaValida(p.resposta) ||
                strchr(p.texto, ';') != NULL ||
                strchr(p.categoria, ';') != NULL) {

                printf("Dados invalidos. Atualizacao cancelada.\n");
                fclose(arquivo);
                fclose(temporario);
                remove("temporario.csv");
                return;
            }
        }

        fprintf(temporario, "%d;%s;%s;%s;%s\n",
                p.id, p.texto, p.categoria, p.curso, p.resposta);
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) {
        remove("temporario.csv");
        printf("Pergunta nao encontrada.\n");
        return;
    }

    remove(ARQUIVO);

    if (rename("temporario.csv", ARQUIVO) != 0) {
        printf("Erro ao substituir o arquivo original.\n");
        return;
    }

    printf("Pergunta atualizada com sucesso!\n");
}

/* Exclui uma pergunta usando um arquivo temporario */
void excluirPergunta() {
    FILE *arquivo;
    FILE *temporario;
    Pergunta p;
    char linha[400];
    char *campo;
    int id;
    int encontrou = 0;

    printf("\n===== EXCLUIR PERGUNTA =====\n");

    printf("Codigo da pergunta: ");
    if (scanf("%d", &id) != 1) {
        printf("Codigo invalido!\n");
        limparEntrada();
        return;
    }
    limparEntrada();

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Erro: arquivo de perguntas nao encontrado.\n");
        return;
    }

    temporario = fopen("temporario.csv", "w");

    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        campo = strtok(linha, ";");
        if (campo == NULL)
            continue;

        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo != NULL)
            strcpy(p.curso, campo);

        campo = strtok(NULL, ";\n");
        if (campo != NULL)
            strcpy(p.resposta, campo);

        if (p.id == id) {
            encontrou = 1;
        } else {
            fprintf(temporario, "%d;%s;%s;%s;%s\n",
                    p.id, p.texto, p.categoria,
                    p.curso, p.resposta);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) {
        remove("temporario.csv");
        printf("Pergunta nao encontrada.\n");
        return;
    }

    remove(ARQUIVO);

    if (rename("temporario.csv", ARQUIVO) != 0) {
        printf("Erro ao substituir o arquivo original.\n");
        return;
    }

    printf("Pergunta excluida com sucesso!\n");
}

/* Menu principal */
int main() {
    int opcao;

    do {
        printf("\n=========================================\n");
        printf("   GERENCIADOR DE PERGUNTAS - QUIZ TI\n");
        printf("=========================================\n");
        printf("1 - Cadastrar pergunta\n");
        printf("2 - Listar todas as perguntas\n");
        printf("3 - Consultar perguntas por categoria\n");
        printf("4 - Consultar perguntas por curso\n");
        printf("5 - Atualizar pergunta\n");
        printf("6 - Excluir pergunta\n");
        printf("0 - Sair\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida! Digite um numero.\n");
            limparEntrada();
            continue;
        }

        limparEntrada();

        switch (opcao) {
            case 1:
                cadastrarPergunta();
                break;
            case 2:
                listarPerguntas();
                break;
            case 3:
                consultarPorCategoria();
                break;
            case 4:
                consultarPorCurso();
                break;
            case 5:
                atualizarPergunta();
                break;
            case 6:
                excluirPergunta();
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida! Escolha uma opcao do menu.\n");
        }

    } while (opcao != 0);

    return 0;
}
