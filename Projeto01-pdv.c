#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    int dia;
    int mes;
    int ano;
}Valid;

typedef struct {
    char nome[12];
    float valor;
    float quantidade;
    int codigo;
    char undMed[10];
    Valid validade;
}Produto;

void pdv_cabecalho();
void pdv_cadastrar(FILE *arquivo, int *pContador, Produto *pProdutos);
void pdv_remover(FILE *arquivo, int *pContador);
void pdv_alterar();
void pdv_exibir(Produto *pProdutos, int *pContador);
void pdv_buscar();
void pdv_atualizar(FILE *arquivo, int *pContador, Produto *pProdutos);
void pdv_sair(Produto *pProdutos, int *pContador);
void pdv_erro();
void flush_in();

int main() {
    FILE *arquivo;
    Produto *pProdutos;
    int *pContador, contador = 0;
    pContador = &contador;

    int digito = 0;
    do {
        printf("     %d produtos armazenados\n", *pContador);
        pdv_cabecalho();
        scanf("%d", &digito);
        flush_in();
        switch(digito) {
            case 1: /* cadastrar */ {
                pdv_cadastrar(arquivo, pContador, pProdutos);
                break;
            }
            case 2: /* remover */ {
                break;
            }
            case 3: /* modificar */ {
                break;
            }
            case 4: /* exibir */ {
                pdv_exibir(pProdutos, pContador);
                system("pause");
                system("cls");
                break;
            }
            case 5: /* buscar */ {
                break;
            }
            case 6: /* atualizar */ {
                pdv_atualizar(arquivo, pContador, pProdutos);
                break;
            }
            case 7: /*sair*/ {
                pdv_sair(pProdutos, pContador);
                break;
            }
            default: /* erro */ {
                pdv_erro();
                break;
            }
        }
    } while(digito != 7);
    
    return 0;
}

void pdv_cabecalho() {
    printf("- - - - - - - - - - - - - - - -\n");
    printf("- - - - - SISTEMA PDV - - - - -\n");
    printf("- - - - - - - - - - - - - - - -\n\n");
    
    printf("Digite:\n");
    printf("(1) - Para cadastrar um produto\n");
    printf("(2) - Para remover um produto\n");
    printf("(3) - Para alterar um produto\n");
    printf("(4) - Para exibir os produtos cadastrados\n");
    printf("(5) - Para buscar um produto\n");
    printf("(6) - Para atualizar a base de dados\n");
    printf("(7) - Para sair do programa\n\n");
}

void pdv_cadastrar(FILE *arquivo, int *pContador, Produto *pProdutos) {
    system("cls");
    printf("\x1b[36m" " [ CADASTRO DE PRODUTO ] \n" "\x1b[0m");
    
    Produto pdv;
    arquivo = fopen("log-pdv.txt", "a+");

    if(arquivo == NULL) {
    printf("Erro ao ler arquivo!");
    } else {
    do {
        printf("\nDigite o nome do produto: ");
        scanf("%[^\n]", pdv.nome);
        fprintf(arquivo, "%s\t", pdv.nome);

        flush_in();
        printf("Digite a quantidade do produto: ");
        scanf("%f", &pdv.quantidade);
        fprintf(arquivo, "%f\t", pdv.quantidade);

        flush_in();
        printf("Digite a unidade de medida do produto: ");
        scanf("%[^\n]", &pdv.undMed);

        flush_in();
        printf("Digite o preco do produto: ");
        scanf("%f", &pdv.valor);
        fprintf(arquivo, "%s\t%.2f\t", pdv.undMed, pdv.valor);

        flush_in();
        printf("Digite a validade do produto(dd mm aaaa): ");
        scanf("%d %d %d", &pdv.validade.dia, &pdv.validade.mes, &pdv.validade.ano);
        fprintf(arquivo, "%d\t%d\t%d\t", pdv.validade.dia, pdv.validade.mes, pdv.validade.ano);

        flush_in();
        printf("Digite o codigo do produto: ");
        scanf("%d", &pdv.codigo);
        fprintf(arquivo, "%d", pdv.codigo);
        flush_in();
        
        fprintf(arquivo, "\n");      

        printf("\e[0;32m" "\n\nProduto cadastrado com sucesso\nDeseja cadastrar outro produto? (s/n): " "\x1b[0m");

        } while(getch() == 's');
        system("cls");        
    } fclose(arquivo);
}

void pdv_exibir(Produto *pProdutos, int *pContador) {
    for(int i = 0; i < *pContador; i++)
            printf("    [%d]    Produto: %s    Qtd: %f/%s R$ %f	%d/%d/%d	%d\n", i, pProdutos[i].nome, pProdutos[i].quantidade, pProdutos[i].undMed, pProdutos[i].valor, pProdutos[i].validade.dia, pProdutos[i].validade.mes, pProdutos[i].validade.ano, pProdutos[i].codigo);
}

void pdv_atualizar(FILE *arquivo, int *pContador, Produto *pProdutos) {
    arquivo = fopen("log-pdv.txt", "r");
        char ch;
        int contador = 0;
        if(arquivo) {
            while(!feof(arquivo)) {
                ch = fgetc(arquivo);
                if(ch == '\n')
                    contador++;
            }
        } 
        *pContador = contador;

        pProdutos = (Produto*)calloc(*pContador, sizeof(Produto));
        
        for(int i = 0; i < *pContador; i++) {
            fscanf(arquivo, "%s\t%f\t%s\t%f\t%d\t%d\t%d\t%d\n", pProdutos[i].nome, &pProdutos[i].quantidade, pProdutos[i].undMed, &pProdutos[i].valor, &pProdutos[i].validade.dia, &pProdutos[i].validade.mes, &pProdutos[i].validade.ano, &pProdutos[i].codigo);
        }

    fclose(arquivo);
    system("cls");
    printf("\e[0;32m" "  [ BASE DE DADOS ATUALIZADA ] \n" "\x1b[0m");
}

void pdv_sair(Produto *pProdutos, int *pContador) {
    free(pProdutos);
    free(pContador);
    system("cls");
    printf("\x1b[36m" "\nObrigado por usar nosso programa\nAte a proxima!\n\n" "\x1b[0m");
    system("pause");
}

void pdv_erro() {
    system("cls");
    printf("\x1b[31m" "       [ OPCAO INVALIDA ]       \n" "\x1b[0m");
}

void flush_in() {
    char ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}