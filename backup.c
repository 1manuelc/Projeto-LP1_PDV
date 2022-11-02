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
    float preco;
    float quantidade;
    int codigo;
    char undMed[10];
    Valid validade;
}Produto;

void pdv_cabecalho();
void pdv_cadastrar(int *pContador);
void pdv_remover(int *pContador);
void pdv_alterar();
void pdv_exibir(int *pContador);
void pdv_buscar();
void pdv_atualizar(int *pContador);
void pdv_sair(int *pContador);
void pdv_erro();
void flush_in();

int main() {
    int qtdProd, digito = 0;
    do {
        printf("     %d produtos armazenados\n", qtdProd);
        pdv_cabecalho();
        scanf("%d", &digito);
        flush_in();
        switch(digito) {
            case 1: /* cadastrar */ {
                pdv_cadastrar(pContador);
                break;
            }
            case 2: /* remover */ {
                break;
            }
            case 3: /* modificar */ {
                break;
            }
            case 4: /* exibir */ {
                pdv_exibir(pContador);
                system("pause");
                system("cls");
                break;
            }
            case 5: /* buscar */ {
                break;
            }
            case 6: /* atualizar */ {
                pdv_atualizar(pContador);
                break;
            }
            case 7: /*sair*/ {
                pdv_sair(pContador);
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

void pdv_cadastrar(int *pContador) {
    system("cls");
    printf("\x1b[36m" " [ CADASTRO DE PRODUTO ] \n" "\x1b[0m");
    FILE *arquivo;
    Produto pdv;

    do {
        arquivo = fopen("logs/log-pdv-nomes.txt", "a+");
        printf("\nDigite o nome do produto: ");
        scanf("%[^\n]", pdv.nome);
        fprintf(arquivo, "%s\n", pdv.nome);
        fclose(arquivo);
        flush_in();

        arquivo = fopen("logs/log-pdv-quantidades.txt", "a+");
        printf("Digite a quantidade do produto: ");
        scanf("%f", &pdv.quantidade);
        fprintf(arquivo, "%f\n", pdv.quantidade);
        fclose(arquivo);
        flush_in();

        arquivo = fopen("logs/log-pdv-undmeds.txt", "a+");
        printf("Digite a unidade de medida do produto: ");
        scanf("%[^\n]", pdv.undMed);
        fprintf(arquivo, "%s\n", pdv.undMed);
        fclose(arquivo);
        flush_in();

        arquivo = fopen("logs/log-pdv-precos.txt", "a+");
        printf("Digite o preco do produto: ");
        scanf("%f", &pdv.preco);
        fprintf(arquivo, "%f\n", pdv.preco);
        fclose(arquivo);
        flush_in();

        arquivo = fopen("logs/log-pdv-validades.txt", "a+");
        printf("Digite a validade do produto(dd mm aaaa): ");
        scanf("%d %d %d", &pdv.validade.dia, &pdv.validade.mes, &pdv.validade.ano);
        fprintf(arquivo, "%d\t%d\t%d\n", pdv.validade.dia, pdv.validade.mes, pdv.validade.ano);
        fclose(arquivo);
        flush_in();

        arquivo = fopen("logs/log-pdv-codigos.txt", "a+");
        printf("Digite o codigo do produto: ");
        scanf("%d", &pdv.codigo);
        fprintf(arquivo, "%d\n", pdv.codigo);
        fclose(arquivo);
        flush_in();

        printf("\e[0;32m" "\n\nProduto cadastrado com sucesso\nDeseja cadastrar outro produto? (s/n): " "\x1b[0m");

        } while(getch() == 's');
        system("cls");
}

void pdv_exibir(int *pContador) {
    for(int i = 0; i < *pContador; i++) {
        printf("    [%d]    \n", i);
    } /* falta implementar impressao dos elementos de Produto */
}

void pdv_atualizar(int *pContador) {
    FILE *arquivo;
    arquivo = fopen("logs/log-pdv-undmeds.txt", "r");
        char ch;
        int contador = 0;
        if(arquivo) {
            while(!feof(arquivo)) {
                ch = fgetc(arquivo);
                if(ch == '\n')
                    contador++;
            }
        }
    fclose(arquivo);
    *pContador = contador;

    system("cls");
    printf("\e[0;32m" "  [ BASE DE DADOS ATUALIZADA ] \n" "\x1b[0m");
}

void pdv_sair(int *pContador) {
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