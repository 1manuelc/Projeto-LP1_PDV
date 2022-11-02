#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    int dia;
    int mes;
    int ano;
}Valid;

typedef struct {
    char nome[20];
    float preco;
    float quantidade;
    int codigo;
    char undMed[5];
    Valid validade;
}Produto;

/* FALTA pdv_remover e pdv_buscar */

void pdv_cabecalho(int quant) {
    if(quant != 0)
        printf("\e[0;32m" "     %d produtos no sistema\n" "\x1b[0m", quant);
    else
        printf("     %d produtos no sistema\n", quant);
    printf("- - - - - - - - - - - - - - - -\n");
    printf("- - - - - SISTEMA PDV - - - - -\n");
    printf("- - - - - - - - - - - - - - - -\n\n");
    
    printf("Digite:\n");
    printf("(0) - Para sair do programa\n");
    printf("(1) - Para cadastrar um produto\n");
    printf("(2) - Para remover um produto\n");
    printf("(3) - Para alterar um produto\n");
    printf("(4) - Para exibir os produtos cadastrados\n");
    printf("(5) - Para salvar a base de dados\n");
    printf("(6) - Para atualizar a base de dados\n");
    printf("(7) - Para buscar um produto\n");
}

int pdv_cadastrar(Produto **produtos, int quant, int tam) {
    system("cls");

    printf("\x1b[36m" "Cadastro de Produto\n\n" "\x1b[0m");
    
    if(quant < tam) {
        Produto *novoProd = (Produto*)malloc(sizeof(Produto));

        printf("\nDigite o nome do produto: ");
        scanf("%20[^\n]", novoProd->nome);

        printf("\nDigite o preco do produto: ");
        scanf("%f", &novoProd->preco);
        getchar();

        printf("\nDigite a quantidade do produto no estoque: ");
        scanf("%f", &novoProd->quantidade);
        getchar();

        printf("\nDigite a unidade de medida do produto: ");
        scanf("%5[^\n]", novoProd->undMed);

        printf("\nDigite o codigo do produto: ");
        scanf("%d", &novoProd->codigo);
        getchar();

        printf("Digite a data de validade do produto em dd mm aaaa: ");
        scanf("%d%d%d", &novoProd->validade.dia, &novoProd->validade.mes, &novoProd->validade.ano);

        produtos[quant] = novoProd;

        return 1;
    } else {
        printf("\nImpossivel novo cadastro, memoria cheia!");
        return 0;
    }
    system("cls");
}

void pdv_exibir(Produto **produtos, int quant) {
    system("cls");
    printf("\x1b[36m""\nLista de Produtos\n""\x1b[0m");

    printf("\n_________________________________________________________________________________________________________________\n\n");

    for(int i = 0; i < quant; i++) {
        printf("[%d] - ", i + 1);
        printf("Nome: %s\t", produtos[i]->nome);
        printf("Valor/%s: R$ %.2f\t", produtos[i]->undMed, produtos[i]->preco);
        printf("Estoque: %.0f%s\t", produtos[i]->quantidade, produtos[i]->undMed);
        printf("Validade: %d/%d/%d\t", produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
        printf("Codigo: %d\n\n", produtos[i]->codigo);
    }
    
    printf("_________________________________________________________________________________________________________________\n\n");
}

void pdv_alterar(Produto **produtos, int quant) {
    system("cls");
    pdv_exibir(produtos, quant);

    int id, escolha;
    printf("\n\nDigite o codigo do produto que deseja alterar : ");
    scanf("%d", &id);
    getchar();
    id--;

    if(id >= 0 && id < quant) {
        Produto *novoProd = (Produto*)malloc(sizeof(Produto));

        printf("\nDigite o nome do produto: ");
        scanf("%20[^\n]", novoProd->nome);

        printf("\nDigite o preco do produto: ");
        scanf("%f", &novoProd->preco);
        getchar();

        printf("\nDigite a quantidade do produto no estoque: ");
        scanf("%f", &novoProd->quantidade);
        getchar();

        printf("\nDigite a unidade de medida do produto: ");
        scanf("%5[^\n]", novoProd->undMed);

        printf("\nDigite o codigo do produto: ");
        scanf("%d", &novoProd->codigo);
        getchar();

        printf("Digite a data de validade do produto em dd mm aaaa: ");
        scanf("%d%d%d", &novoProd->validade.dia, &novoProd->validade.mes, &novoProd->validade.ano);

        produtos[id] = novoProd;
    } else {
        system("cls");
        printf("       Codigo invalido!\n");
    }
}

void pdv_salvar(Produto **produtos, int quant, char arq[]) {
    FILE *file = fopen(arq, "w");

    if(file) {
        fprintf(file, "%d\n", quant);
        
        for(int i = 0; i < quant; i++) {
            fputs(produtos[i]->nome, file);
            fputc('\n', file);
            fputs(produtos[i]->undMed, file);
            fputc('\n', file);
            fprintf(file, "%f\n", produtos[i]->preco);
            fprintf(file, "%f\n", produtos[i]->quantidade);
            fprintf(file, "%d\n", produtos[i]->codigo);
            fprintf(file, "%d %d %d\n", produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
        }fclose(file);
    } else
        printf("\n\tNao foi possivel abrir/criar o arquivo!\n");
    
    system("cls");
    printf("    [ Base de dados salva ]\n");
}

int pdv_atualizar(Produto **produtos, char arq[]) {
    FILE *file = fopen(arq, "r");
    int quant = 0, i;
    Produto *novo = malloc(sizeof(Produto));

    if(file) {
        fscanf(file, "%d\n", &quant);

        for(i = 0; i < quant; i++) {
            fscanf(file, "%20[^\n]\n", novo->nome);
            fscanf(file, "%5[^\n]\n", novo->undMed);
            fscanf(file, "%f\n", &novo->preco);
            fscanf(file, "%f\n", &novo->quantidade);
            fscanf(file, "%d\n", &novo->codigo);
            fscanf(file, "%d %d %d\n", &novo->validade.dia, &novo->validade.mes, &novo->validade.ano);
            produtos[i] = novo;
            novo = malloc(sizeof(Produto));
        } fclose(file);
    } else
        printf("\n\tNao foi possivel abrir/criar arquivo!\n");
    
    system("cls");
    printf("  [ Base de dados atualizada ]\n");
    return quant;
}

void pdv_erro() {
    system("cls");
    printf("\x1b[31m" "       [ OPCAO INVALIDA ]       \n" "\x1b[0m");
}

void pdv_sair(Produto **produtos, int quant) {
    for(int i = 0; i < quant; i++)
        free(produtos[i]);
    free(produtos);

    system("cls");
    printf("\x1b[36m" "\nObrigado por usar nosso programa\nAte a proxima!\n\n" "\x1b[0m");
}

int main() {
    int opcao, quant = 0, tam = 100;
    Produto *produtos[tam];
    char arquivo[] = {"pdv-log.txt"};
    do {
        pdv_cabecalho(quant);
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: /*cadastrar*/
                quant += pdv_cadastrar(produtos, quant, tam);
                break;
            case 2: /*remover*/
                break;
            case 3: /*alterar*/
                pdv_alterar(produtos, quant);
                break;
            case 4: /*exibir*/
                pdv_exibir(produtos, quant);
                system("pause");
                system("cls");
                break;
            case 5: /*salvar arquivo*/
                pdv_salvar(produtos, quant, arquivo);
                break;
            case 6: /*ler arquivo*/
                quant = pdv_atualizar(produtos, arquivo);
                break;
            case 7: /*buscar*/
                break;
            default:
                if(opcao != 0) {
                    pdv_erro();
                }
        }
    }while(opcao != 0);

    pdv_sair(produtos, quant);

    system("pause");
    return 0;
}