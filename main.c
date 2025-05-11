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

    if (carregarArquivo(smartphones, &n)) {
        printf("Arquivo carregado com sucesso. Total de %d smartphones.\n", n);
    }

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
            case 6: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 6);

    return 0;
}

void menu() {
    printf("\n===== MENU =====\n");
    printf("1. Exibir todos os smartphones\n");
    printf("2. Exibir smartphones por marca\n");
    printf("3. Exibir smartphones por faixa de preço\n");
    printf("4. Inserir novo smartphone\n");
    printf("5. Remover smartphones por memória\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}

int carregarArquivo(Smartphone smartphones[], int *n) {
    FILE *arquivo = fopen("smartphones.txt", "r");
    if (!arquivo) {
        printf("Arquivo smartphones.txt não encontrado. Será criado ao salvar os dados.\n");
        *n = 0;
        return 0;
    }

    *n = 0;
    Smartphone temp;
    char linha[100];

    while (!feof(arquivo)) {
        if (!fgets(temp.marca, sizeof(temp.marca), arquivo)) break;
        temp.marca[strcspn(temp.marca, "\n")] = '\0';

        if (!fgets(temp.modelo, sizeof(temp.modelo), arquivo)) break;
        temp.modelo[strcspn(temp.modelo, "\n")] = '\0';

        if (!fgets(linha, sizeof(linha), arquivo)) break;
        temp.ano = atoi(linha);

        if (!fgets(linha, sizeof(linha), arquivo)) break;
        temp.memoria = atoi(linha);

        if (!fgets(linha, sizeof(linha), arquivo)) break;
        temp.preco = atof(linha);

        inserirOrdenado(smartphones, n, temp);
    }

    fclose(arquivo);
    return 1;
}

void inserirOrdenado(Smartphone smartphones[], int *n, Smartphone novo) {
    if (*n >= MAX) {
        printf("Erro: Capacidade máxima de smartphones atingida!\n");
        return;
    }

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
        printf("Não há smartphones cadastrados.\n");
        return;
    }

    printf("\n===== LISTA DE SMARTPHONES =====\n");
    printf("%-5s %-20s %-30s %-6s %-8s %-10s\n",
           "Índice", "Marca", "Modelo", "Ano", "Memória", "Preço (R$)");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-5d %-20s %-30s %-6d %-8d R$ %-10.2f\n",
               i,
               smartphones[i].marca,
               smartphones[i].modelo,
               smartphones[i].ano,
               smartphones[i].memoria,
               smartphones[i].preco);
    }
    printf("------------------------------------------------------------------------------------------------\n");
}

void exibirPorMarca(Smartphone smartphones[], int n) {
    char marca[21];
    printf("Digite a marca que deseja buscar: ");
    fgets(marca, sizeof(marca), stdin);
    marca[strcspn(marca, "\n")] = '\0';

    int encontrados = 0;
    printf("\n===== SMARTPHONES DA MARCA %s =====\n", marca);
    printf("%-5s %-20s %-30s %-6s %-8s %-10s\n",
           "Índice", "Marca", "Modelo", "Ano", "Memória", "Preço (R$)");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (strcasecmp(smartphones[i].marca, marca) == 0) {
            printf("%-5d %-20s %-30s %-6d %-8d R$ %-10.2f\n",
                   i,
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
    printf("------------------------------------------------------------------------------------------------\n");
}

void exibirPorPreco(Smartphone smartphones[], int n) {
    float min, max;
    printf("Digite o preço mínimo (R$): ");
    scanf("%f", &min);
    printf("Digite o preço máximo (R$): ");
    scanf("%f", &max);
    getchar();

    int encontrados = 0;
    printf("\n===== SMARTPHONES ENTRE R$ %.2f E R$ %.2f =====\n", min, max);
    printf("%-5s %-20s %-30s %-6s %-8s %-10s\n",
           "Índice", "Marca", "Modelo", "Ano", "Memória", "Preço (R$)");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (smartphones[i].preco >= min && smartphones[i].preco <= max) {
            printf("%-5d %-20s %-30s %-6d %-8d R$ %-10.2f\n",
                   i,
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
    printf("------------------------------------------------------------------------------------------------\n");
}

void inserirNovo(Smartphone smartphones[], int *n) {
    if (*n >= MAX) {
        printf("Erro: Capacidade máxima de smartphones atingida!\n");
        return;
    }

    Smartphone novo;

    printf("Digite os dados do novo smartphone:\n");
    printf("Marca: ");
    fgets(novo.marca, sizeof(novo.marca), stdin);
    novo.marca[strcspn(novo.marca, "\n")] = '\0';

    printf("Modelo: ");
    fgets(novo.modelo, sizeof(novo.modelo), stdin);
    novo.modelo[strcspn(novo.modelo, "\n")] = '\0';

    printf("Ano de fabricação: ");
    scanf("%d", &novo.ano);
    getchar();

    printf("Capacidade de memória (GB): ");
    scanf("%d", &novo.memoria);
    getchar();

    printf("Preço (R$): ");
    scanf("%f", &novo.preco);
    getchar();

    inserirOrdenado(smartphones, n, novo);
    printf("\nSmartphone adicionado com sucesso!\n");
    printf("Dados: %s %s, %d, %d GB, R$ %.2f\n",
           novo.marca, novo.modelo, novo.ano, novo.memoria, novo.preco);
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
            if (i != j) {
                smartphones[j] = smartphones[i];
            }
            j++;
        } else {
            removidos++;
        }
    }

    *n = j;

    if (removidos > 0) {
        printf("%d smartphone(s) com memória inferior a %d GB foram removidos.\n", removidos, limite);
    } else {
        printf("Nenhum smartphone com memória inferior a %d GB encontrado.\n", limite);
    }
}

void salvarEmArquivo(Smartphone smartphones[], int n) {
    FILE *arquivo = fopen("smartphones.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar os dados!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%s\n%s\n%d\n%d\n%.2f\n",
                smartphones[i].marca,
                smartphones[i].modelo,
                smartphones[i].ano,
                smartphones[i].memoria,
                smartphones[i].preco);
    }

    fclose(arquivo);
    printf("Dados salvos no arquivo smartphones.txt com sucesso!\n");
}
