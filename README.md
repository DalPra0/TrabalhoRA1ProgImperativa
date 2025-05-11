# TrabalhoRA1ProgImperativa

Este programa em C implementa um sistema simples para gerenciar informações sobre smartphones. O sistema lê registros de um arquivo texto, armazena-os em memória de forma ordenada por preço e permite ao usuário realizar diversas operações sobre esses dados.

## Funcionalidades

O programa oferece as seguintes operações:

1. **Exibir todos os registros**: Mostra todos os smartphones cadastrados, ordenados por preço.
2. **Exibir por marca**: Filtra smartphones de uma marca específica fornecida pelo usuário.
3. **Exibir por faixa de preço**: Mostra smartphones cujos preços estão entre valores mínimo e máximo definidos pelo usuário.
4. **Inserir novo registro**: Adiciona um novo smartphone ao sistema, mantendo a ordenação por preço.
5. **Remover por memória**: Remove todos os smartphones com memória inferior a um valor definido pelo usuário.
6. **Sair**: Encerra o programa.

## Estrutura do Programa

### Estrutura do Smartphone

```c
#define MAX 100

typedef struct {
    char marca[21];
    char modelo[31];
    int ano;
    int memoria;
    float preco;
} Smartphone;
```

### Função Principal

```c
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
```

### Menu

```c
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
```

## Arquivo de Entrada

O programa lê os dados do arquivo `smartphones.txt`, que deve conter os registros neste formato:

```
Marca1
Modelo1
Ano1
Memoria1
Preco1
Marca2
Modelo2
Ano2
Memoria2
Preco2
...
```

Se o arquivo não existir, ele será criado automaticamente ao salvar novos dados.

## Compilação e Execução

Para compilar o programa:

```bash
gcc -o smartphones main.c
```

Para executar:

```bash
./smartphones
```

Certifique-se de que o arquivo `smartphones.txt` esteja no mesmo diretório do executável.

---
