# TrabalhoRA1ProgImperativa

Este programa em C implementa um sistema simples para gerenciar informações sobre smartphones. O sistema lê registros de um arquivo texto, armazena-os em memória de forma ordenada por preço e permite ao usuário realizar diversas operações sobre esses dados.

## Explicação do Código

### Estruturas e Constantes

```c
#define MAX 100  // Define o número máximo de registros

typedef struct {
    char marca[21];     // Marca com até 20 caracteres + nulo
    char modelo[31];    // Modelo com até 30 caracteres + nulo
    int ano;            // Ano de fabricação
    int memoria;        // Capacidade de memória em GB
    float preco;        // Preço em reais
} Smartphone;           // Estrutura para armazenar dados de smartphones
```

### Função Principal (main)

A função `main()` inicializa o vetor de smartphones, carrega os dados do arquivo e apresenta um menu de opções em loop até que o usuário escolha sair:

```c
int main() {
    Smartphone smartphones[MAX];  // Vetor para armazenar os registros
    int n = 0;                    // Contador de registros
    carregarArquivo(smartphones, &n);  // Carrega dados do arquivo

    int opcao;
    do {
        menu();                   // Exibe o menu
        scanf("%d", &opcao);      // Lê opção escolhida
        getchar();                // Limpa o buffer de entrada

        switch(opcao) {           // Executa a opção escolhida
            case 1: exibirTodos(smartphones, n); break;
            case 2: exibirPorMarca(smartphones, n); break;
            case 3: exibirPorPreco(smartphones, n); break;
            case 4: inserirNovo(smartphones, &n); salvarEmArquivo(smartphones, n); break;
            case 5: removerPorMemoria(smartphones, &n); salvarEmArquivo(smartphones, n); break;
            case 6: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while(opcao != 6);          // Continua até escolher sair

    return 0;
}
```

### Funções de Gerenciamento de Dados

#### Carregamento de Arquivo

```c
int carregarArquivo(Smartphone smartphones[], int *n) {
    FILE *f = fopen("smartphones.txt", "r");  // Abre o arquivo para leitura
    if (!f) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    Smartphone temp;
    // Lê cada registro e insere de forma ordenada
    while (fscanf(f, " %20[^\n]%*c %30[^\n]%*c %d %d %f",
                  temp.marca, temp.modelo, &temp.ano,
                  &temp.memoria, &temp.preco) == 5) {
        inserirOrdenado(smartphones, n, temp);
    }

    fclose(f);
    
    // Verifica se atinge o mínimo de registros requerido
    if (*n < 30) {
        printf("Aviso: O arquivo deve conter pelo menos 30 registros. Encontrados: %d\n", *n);
    }
    
    return 1;
}
```

#### Inserção Ordenada

```c
void inserirOrdenado(Smartphone smartphones[], int *n, Smartphone novo) {
    int i = *n - 1;
    // Desloca elementos maiores para inserir na posição correta
    while (i >= 0 && smartphones[i].preco > novo.preco) {
        smartphones[i + 1] = smartphones[i];
        i--;
    }
    smartphones[i + 1] = novo;  // Insere na posição correta
    (*n)++;                    // Incrementa contador
}
```

#### Exibir Todos os Registros

```c
void exibirTodos(Smartphone smartphones[], int n) {
    if (n == 0) {
        printf("Não há registros para exibir.\n");
        return;
    }
    
    printf("\n----- LISTA DE SMARTPHONES -----\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | %s | %d | %d GB | R$%.2f\n",
               i+1, smartphones[i].marca, smartphones[i].modelo,
               smartphones[i].ano, smartphones[i].memoria, smartphones[i].preco);
    }
    printf("--------------------------------\n");
}
```

#### Exibir Por Marca

```c
void exibirPorMarca(Smartphone smartphones[], int n) {
    char marca[21];
    printf("Digite a marca: ");
    fgets(marca, sizeof(marca), stdin);           // Lê marca
    marca[strcspn(marca, "\n")] = '\0';           // Remove \n do final

    int encontrados = 0;
    printf("\n----- SMARTPHONES DA MARCA %s -----\n", marca);
    for (int i = 0; i < n; i++) {
        if (strcmp(smartphones[i].marca, marca) == 0) {   // Compara strings
            printf("%s | %s | %d | %d GB | R$%.2f\n",
                   smartphones[i].marca, smartphones[i].modelo,
                   smartphones[i].ano, smartphones[i].memoria, smartphones[i].preco);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("Nenhum smartphone da marca %s encontrado.\n", marca);
    }
    printf("--------------------------------\n");
}
```

#### Exibir Por Faixa de Preço

```c
void exibirPorPreco(Smartphone smartphones[], int n) {
    float min, max;
    printf("Digite o preço mínimo: ");
    scanf("%f", &min);
    printf("Digite o preço máximo: ");
    scanf("%f", &max);
    getchar();  // Limpa buffer

    int encontrados = 0;
    printf("\n----- SMARTPHONES ENTRE R$%.2f E R$%.2f -----\n", min, max);
    for (int i = 0; i < n; i++) {
        if (smartphones[i].preco >= min && smartphones[i].preco <= max) {
            printf("%s | %s | %d | %d GB | R$%.2f\n",
                   smartphones[i].marca, smartphones[i].modelo,
                   smartphones[i].ano, smartphones[i].memoria, smartphones[i].preco);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("Nenhum smartphone encontrado nessa faixa de preço.\n");
    }
    printf("--------------------------------\n");
}
```

#### Inserir Novo Registro

```c
void inserirNovo(Smartphone smartphones[], int *n) {
    if (*n >= MAX) {
        printf("Erro: Capacidade máxima atingida!\n");
        return;
    }
    
    Smartphone novo;
    // Lê dados do novo smartphone
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
    getchar();  // Limpa buffer

    inserirOrdenado(smartphones, n, novo);  // Insere mantendo ordenação
    printf("Smartphone inserido com sucesso!\n");
}
```

#### Remover Por Memória

```c
void removerPorMemoria(Smartphone smartphones[], int *n) {
    int limite;
    printf("Remover smartphones com memória inferior a (GB): ");
    scanf("%d", &limite);
    getchar();  // Limpa buffer

    int removidos = 0;
    int j = 0;
    // Compacta o vetor removendo elementos com memória inferior ao limite
    for (int i = 0; i < *n; i++) {
        if (smartphones[i].memoria >= limite) {
            smartphones[j++] = smartphones[i];  // Mantém se memória >= limite
        } else {
            removidos++;  // Conta removidos
        }
    }
    *n = j;  // Atualiza contador
    
    if (removidos > 0) {
        printf("%d registros com menos de %d GB foram removidos.\n", removidos, limite);
    } else {
        printf("Nenhum smartphone com menos de %d GB encontrado.\n", limite);
    }
}
```

#### Salvar em Arquivo

```c
void salvarEmArquivo(Smartphone smartphones[], int n) {
    FILE *f = fopen("smartphones.txt", "w");  // Abre para escrita
    if (!f) {
        printf("Erro ao salvar no arquivo!\n");
        return;
    }

    // Escreve cada registro no formato esperado
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n%s\n%d\n%d\n%.2f\n",
            smartphones[i].marca, smartphones[i].modelo,
            smartphones[i].ano, smartphones[i].memoria, smartphones[i].preco);
    }

    fclose(f);
    printf("Alterações salvas no arquivo.\n");
}
```

## Funcionalidades

O programa oferece as seguintes operações:

1. **Exibir todos os registros**: Mostra todos os smartphones cadastrados, ordenados por preço.
2. **Exibir por marca**: Filtra smartphones de uma marca específica fornecida pelo usuário.
3. **Exibir por faixa de preço**: Mostra smartphones cujos preços estão entre valores mínimo e máximo definidos pelo usuário.
4. **Inserir novo registro**: Adiciona um novo smartphone ao sistema, mantendo a ordenação por preço.
5. **Remover por memória**: Remove todos os smartphones com memória inferior a um valor definido pelo usuário.
6. **Sair**: Encerra o programa.

## Arquivo de Entrada

O programa lê os dados do arquivo `smartphones.txt`, que deve ter o seguinte formato:
```
Marca1
Modelo1
AnoFabricacao1
MemoriaGB1
Preco1
Marca2
Modelo2
AnoFabricacao2
MemoriaGB2
Preco2
...
```

Conforme o requisito do trabalho, o arquivo deve conter no mínimo 30 registros.

## Compilação e Execução

Para compilar o programa, use:
```
gcc -o smartphones main.c
```

Para executar:
```
./smartphones
```

Certifique-se de que o arquivo `smartphones.txt` esteja no mesmo diretório do executável.
