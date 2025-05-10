#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char marca[21];
    char modelo[31];
    int ano;
    int memoria;
    float preco;
} Smartphone;

int carregarArquivo(Smartphone smartphones[], int *n);
void inserirOrdenado(Smartphone smartphones[], int *n, Smartphone novo);
void exibirTodos(Smartphone smartphones[], int n);
void exibirPorMarca(Smartphone smartphones[], int n);
void exibirPorPreco(Smartphone smartphones[], int n);
void inserirNovo(Smartphone smartphones[], int *n);
void removerPorMemoria(Smartphone smartphones[], int *n);
void salvarEmArquivo(Smartphone smartphones[], int n);
void menu();

int main() {
    Smartphone smartphones[MAX];
    int n = 0;
    carregarArquivo(smartphones, &n);

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: exibirTodos(smartphones, n); break;
            case 2: exibirPorMarca(smartphones, n); break;
            case 3: exibirPorPreco(smartphones, n); break;
            case 4: inserirNovo(smartphones, &n); salvarEmArquivo(smartphones, n); break;
            case 5: removerPorMemoria(smartphones, &n); salvarEmArquivo(smartphones, n); break;
            case 6: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while(opcao != 6);

    return 0;
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Exibir todos os registros\n");
    printf("2. Exibir registros por marca\n");
    printf("3. Exibir registros por faixa de preço\n");
    printf("4. Inserir novo registro\n");
    printf("5. Remover registros por memória\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}

int carregarArquivo(Smartphone smartphones[], int *n) {
    FILE *f = fopen("smartphones.txt", "r");
    if (!f) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    Smartphone temp;
    while (fscanf(f, " %20[^\n]%*c %30[^\n]%*c %d %d %f",
                  temp.marca, temp.modelo, &temp.ano,
                  &temp.memoria, &temp.preco) == 5) {
        inserirOrdenado(smartphones, n, temp);
    }

    fclose(f);

    if (*n < 30) {
        printf("Aviso: O arquivo deve conter pelo menos 30 registros. Encontrados: %d\n", *n);
    }

    return 1;
}

void inserirOrdenado(Smartphone smartphones[], int *n, Smartphone novo) {
    int i = *n - 1;
    while (i >= 0 && smartphones[i].preco > novo.preco) {
        smartphones[i + 1] = smartphones[i];
        i--;
    }
    smartphones[i + 1] = novo;
    (*n)++;
}

void exibirTodos(Smartphone smartphones[], int n) {
    if (n == 0) {
        printf("Não há registros para exibir.\n");
        return;
    }

    printf("\n----- LISTA DE SMARTPHONES -----\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | %s | %d | %d GB | R$%.2f\n",
               i+1,
               smartphones[i].marca,
               smartphones[i].modelo,
               smartphones[i].ano,
               smartphones[i].memoria,
               smartphones[i].preco);
    }
    printf("--------------------------------\n");
}

void exibirPorMarca(Smartphone smartphones[], int n) {
    char marca[21];
    printf("Digite a marca: ");
    fgets(marca, sizeof(marca), stdin);
    marca[strcspn(marca, "\n")] = '\0';

    int encontrados = 0;
    printf("\n----- SMARTPHONES DA MARCA %s -----\n", marca);
    for (int i = 0; i < n; i++) {
        if (strcmp(smartphones[i].marca, marca) == 0) {
            printf("%s | %s | %d | %d GB | R$%.2f\n",
                   smartphones[i].marca,
                   smartphones[i].modelo,
                   smartphones[i].ano,
                   smartphones[i].memoria,
                   smartphones[i].preco);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum smartphone da marca %s encontrado.\n", marca);
    }
    printf("--------------------------------\n");
}

void exibirPorPreco(Smartphone smartphones[], int n) {
    float min, max;
    printf("Digite o preço mínimo: ");
    scanf("%f", &min);
    printf("Digite o preço máximo: ");
    scanf("%f", &max);
    getchar();

    int encontrados = 0;
    printf("\n----- SMARTPHONES ENTRE R$%.2f E R$%.2f -----\n", min, max);
    for (int i = 0; i < n; i++) {
        if (smartphones[i].preco >= min && smartphones[i].preco <= max) {
            printf("%s | %s | %d | %d GB | R$%.2f\n",
                   smartphones[i].marca,
                   smartphones[i].modelo,
                   smartphones[i].ano,
                   smartphones[i].memoria,
                   smartphones[i].preco);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum smartphone encontrado nessa faixa de preço.\n");
    }
    printf("--------------------------------\n");
}

void inserirNovo(Smartphone smartphones[], int *n) {
    if (*n >= MAX) {
        printf("Erro: Capacidade máxima atingida!\n");
        return;
    }

    Smartphone novo;
    printf("Marca: ");
    fgets(novo.marca, sizeof(novo.marca), stdin);
    novo.marca[strcspn(novo.marca, "\n")] = '\0';

    printf("Modelo: ");
    fgets(novo.modelo, sizeof(novo.modelo), stdin);
    novo.modelo[strcspn(novo.modelo, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &novo.ano);

    printf("Memória (GB): ");
    scanf("%d", &novo.memoria);

    printf("Preço: ");
    scanf("%f", &novo.preco);
    getchar();

    inserirOrdenado(smartphones, n, novo);
    printf("Smartphone inserido com sucesso!\n");
}

void removerPorMemoria(Smartphone smartphones[], int *n) {
    int limite;
    printf("Remover smartphones com memória inferior a (GB): ");
    scanf("%d", &limite);
    getchar();

    int removidos = 0;
    int j = 0;
    for (int i = 0; i < *n; i++) {
        if (smartphones[i].memoria >= limite) {
            smartphones[j++] = smartphones[i];
        } else {
            removidos++;
        }
    }
    *n = j;

    if (removidos > 0) {
        printf("%d registros com menos de %d GB foram removidos.\n", removidos, limite);
    } else {
        printf("Nenhum smartphone com menos de %d GB encontrado.\n", limite);
    }
}

void salvarEmArquivo(Smartphone smartphones[], int n) {
    FILE *f = fopen("smartphones.txt", "w");
    if (!f) {
        printf("Erro ao salvar no arquivo!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n%s\n%d\n%d\n%.2f\n",
            smartphones[i].marca,
            smartphones[i].modelo,
            smartphones[i].ano,
            smartphones[i].memoria,
            smartphones[i].preco);
    }

    fclose(f);
    printf("Alterações salvas no arquivo.\n");
}