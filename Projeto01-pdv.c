#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# define TELA_LIMPAR system("cls")
#else
# define TELA_LIMPAR puts("\x1b[H\x1b[2J")
#endif

# define TELA_PAUSAR printf("Digite enter para continuar..."); getchar();
# define ANSI_VERDE "\e[0;32m"
# define ANSI_AZUL "\x1b[36m"
# define ANSI_VERMELHO "\x1b[31m"
# define ANSI_RESET "\x1b[0m"

typedef struct valid Valid;
typedef struct produto Produto;

struct valid {
    int dia;
    int mes;
    int ano;
};

struct produto {
    char nome[20];
    float preco;
    float quantidade;
    int codigo;
    char undMed[5];
    Valid validade;
};

void pdv_cabecalho(int quant);
int pdv_cadastrar(Produto **produtos, int quant, int tam);
void pdv_exibir(Produto **produtos, int quant);
int pdv_remover(Produto **produtos, int quant);
void pdv_alterar(Produto **produtos, int quant);
void pdv_salvar(Produto **produtos, int quant, char arq[]);
int pdv_atualizar(Produto **produtos, char arq[]);
void pdv_buscar(Produto **produtos, int quant, int tam);
void pdv_erro();
void pdv_sair(Produto **produtos, int quant);

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
                quant += pdv_remover(produtos, quant);
                break;
            case 3: /*alterar*/
                pdv_alterar(produtos, quant);
                TELA_LIMPAR;
                break;
            case 4: /*exibir*/
                pdv_exibir(produtos, quant);
                TELA_PAUSAR;
                TELA_LIMPAR;
                break;
            case 5: /*salvar arquivo*/
                pdv_salvar(produtos, quant, arquivo);
                break;
            case 6: /*ler arquivo*/
                quant = pdv_atualizar(produtos, arquivo);
                break;
            case 7: /*buscar*/
                pdv_buscar(produtos, quant, tam);
                break;
            default:
                if(opcao != 0) {
                    pdv_erro();
                }
        }
    }while(opcao != 0);

    pdv_sair(produtos, quant);

    TELA_PAUSAR;
    return 0;
}

void pdv_cabecalho(int quant) {
    if(quant != 0)
        printf(ANSI_VERDE "     %d produtos no sistema\n" ANSI_RESET, quant);
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
    TELA_LIMPAR;

    printf(ANSI_AZUL "Cadastro de Produto\n\n" ANSI_RESET);
    
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
        TELA_LIMPAR;
        printf(ANSI_VERDE "     [ Produto cadastrado ]\n" ANSI_RESET);
        return 1;
    } else {
        printf(ANSI_VERMELHO "\nImpossivel novo cadastro, memoria cheia!" ANSI_RESET);
        TELA_LIMPAR;
        return 0;
    }
}

void pdv_buscar(Produto **produtos, int quant, int tam) {
    TELA_LIMPAR;
    int opcao, ocorrencias = 0;

    Produto *buscaProd = (Produto*)malloc(sizeof(Produto));

    do {
        ocorrencias = 0;
        printf(ANSI_AZUL "Deseja pesquisar por:\n" ANSI_RESET);
        printf("(0) - Sair\n");
        printf("(1) - Nome\n");
        printf("(2) - Unidade de medida\n");
        printf("(3) - Preco\n");
        printf("(4) - Quantidade em estoque\n");
        printf("(5) - Validade\n");
        printf("(6) - Codigo\n");
            scanf("%d", &opcao);
            getchar();

        switch(opcao) {
            case 1:
                    TELA_LIMPAR;
                    printf("Digite o nome: ");
                    scanf("%20[^\n]", buscaProd->nome);
                    getchar();

                    printf("\n_________________________________________________________________________________________________________________\n\n");

                    for(int i = 0; i < quant; i++) {
                        if(strcmp(buscaProd->nome, produtos[i]->nome) == 0) {
                            printf("[%d] - ", i + 1);
                            printf(ANSI_VERDE "Nome: %s\t" ANSI_RESET, produtos[i]->nome);
                            printf("Valor/%s: R$ %.2f\t", produtos[i]->undMed, produtos[i]->preco);
                            printf("Estoque: %.0f%s\t", produtos[i]->quantidade, produtos[i]->undMed);
                            printf("Validade: %d/%d/%d\t", produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
                            printf("Codigo: %d\n\n", produtos[i]->codigo);
                            ocorrencias++;
                        } 
                    }

                    if(ocorrencias == 0)
                                printf(ANSI_VERMELHO "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    else
                        printf(ANSI_VERDE "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    
                    printf("\n_________________________________________________________________________________________________________________\n\n");
                    
                    TELA_PAUSAR;
                    TELA_LIMPAR;
                break;
            case 2:
                    TELA_LIMPAR;
                    printf("Digite a unidade de medida: ");
                    scanf("%5[^\n]", buscaProd->undMed);
                    getchar();

                    printf("\n_________________________________________________________________________________________________________________\n\n");

                    for(int i = 0; i < quant; i++) {
                        if(strcmp(buscaProd->undMed, produtos[i]->undMed) == 0) {
                            printf("[%d] - ", i + 1);
                            printf("Nome: %s\t", produtos[i]->nome);
                            printf("Valor/" ANSI_VERDE "%s" ANSI_RESET ": R$ %.2f\t", produtos[i]->undMed, produtos[i]->preco);
                            printf("Estoque: %.0f%s\t", produtos[i]->quantidade, produtos[i]->undMed);
                            printf("Validade: %d/%d/%d\t", produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
                            printf("Codigo: %d\n\n", produtos[i]->codigo);
                            ocorrencias++;
                        }
                    }

                    if(ocorrencias == 0)
                                printf(ANSI_VERMELHO "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    else
                        printf(ANSI_VERDE "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    
                    printf("\n_________________________________________________________________________________________________________________\n\n");

                    TELA_PAUSAR;
                    TELA_LIMPAR;
                break;
            case 3:
                    TELA_LIMPAR;
                    printf("Digite o preco: ");
                    scanf("%f", &buscaProd->preco);
                    getchar();

                    printf("\n_________________________________________________________________________________________________________________\n\n");

                    for(int i = 0; i < quant; i++) {
                        if(buscaProd->preco == produtos[i]->preco) {
                            printf("[%d] - ", i + 1);
                            printf("Nome: %s\t", produtos[i]->nome);
                            printf("Valor/%s: " ANSI_VERDE "R$ %.2f\t" ANSI_RESET, produtos[i]->undMed, produtos[i]->preco);
                            printf("Estoque: %.0f%s\t", produtos[i]->quantidade, produtos[i]->undMed);
                            printf("Validade: %d/%d/%d\t", produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
                            printf("Codigo: %d\n\n", produtos[i]->codigo);
                            ocorrencias++;
                        }
                    }
                    
                    if(ocorrencias == 0)
                                printf(ANSI_VERMELHO "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    else
                        printf(ANSI_VERDE "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);

                    printf("\n_________________________________________________________________________________________________________________\n\n");
                    
                    TELA_PAUSAR;
                    TELA_LIMPAR;
                break;
            case 4:
                    TELA_LIMPAR;

                    printf("Digite a quantidade em estoque: ");
                    scanf("%f", &buscaProd->quantidade);
                    getchar();
                    
                    printf("\n_________________________________________________________________________________________________________________\n\n");

                    for(int i = 0; i < quant; i++) {
                        if(buscaProd->quantidade == produtos[i]->quantidade) {
                            printf("[%d] - ", i + 1);
                            printf("Nome: %s\t", produtos[i]->nome);
                            printf("Valor/%s: R$ %.2f\t", produtos[i]->undMed, produtos[i]->preco);
                            printf(ANSI_VERDE "Estoque: %.0f%s\t" ANSI_RESET, produtos[i]->quantidade, produtos[i]->undMed);
                            printf("Validade: %d/%d/%d\t", produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
                            printf("Codigo: %d\n\n", produtos[i]->codigo);
                            ocorrencias++;
                        }
                    }
                    
                    if(ocorrencias == 0)
                                printf(ANSI_VERMELHO "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    else
                        printf(ANSI_VERDE "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);

                    printf("\n_________________________________________________________________________________________________________________\n\n");
                    
                    TELA_PAUSAR;
                    TELA_LIMPAR;
                break;
            case 5:
                    TELA_LIMPAR;

                    printf("Digite a validade dd mm aaaa: ");
                    scanf("%d%d%d", &buscaProd->validade.dia, &buscaProd->validade.mes, &buscaProd->validade.ano);
                    getchar();

                    printf("\n_________________________________________________________________________________________________________________\n\n");

                    for(int i = 0; i < quant; i++) {
                        if(buscaProd->validade.dia == produtos[i]->validade.dia ||
                        buscaProd->validade.mes == produtos[i]->validade.mes ||
                        buscaProd->validade.ano == produtos[i]->validade.ano) {
                            printf("[%d] - ", i + 1);
                            printf("Nome: %s\t", produtos[i]->nome);
                            printf("Valor/%s: R$ %.2f\t", produtos[i]->undMed, produtos[i]->preco);
                            printf("Estoque: %.0f%s\t", produtos[i]->quantidade, produtos[i]->undMed);
                            printf(ANSI_VERDE "Validade: %d/%d/%d\t" ANSI_RESET, produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
                            printf("Codigo: %d\n\n", produtos[i]->codigo);
                            ocorrencias++;
                        }
                    } 
                    
                    if(ocorrencias == 0)
                                printf(ANSI_VERMELHO "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    else
                        printf(ANSI_VERDE "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    
                    printf("\n_________________________________________________________________________________________________________________\n\n");
                    
                    TELA_PAUSAR;
                    TELA_LIMPAR;
                break;
            case 6:
                    TELA_LIMPAR;

                    printf("Digite o codigo: ");
                    scanf("%d", &buscaProd->codigo);
                    getchar();

                    printf("\n_________________________________________________________________________________________________________________\n\n");

                    for(int i = 0; i < quant; i++) {
                        if(buscaProd->codigo == produtos[i]->codigo) {
                            printf("[%d] - ", i + 1);
                            printf("Nome: %s\t", produtos[i]->nome);
                            printf("Valor/%s: R$ %.2f\t", produtos[i]->undMed, produtos[i]->preco);
                            printf("Estoque: %.0f%s\t", produtos[i]->quantidade, produtos[i]->undMed);
                            printf("Validade: %d/%d/%d\t", produtos[i]->validade.dia, produtos[i]->validade.mes, produtos[i]->validade.ano);
                            printf(ANSI_VERDE "Codigo: %d\n\n" ANSI_RESET, produtos[i]->codigo);
                            ocorrencias++;
                        }
                    } 
                    
                    if(ocorrencias == 0)
                                printf(ANSI_VERMELHO "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    else
                        printf(ANSI_VERDE "%d ocorrencias encontradas\n" ANSI_RESET, ocorrencias);
                    
                    printf("\n_________________________________________________________________________________________________________________\n\n");
                    
                    TELA_PAUSAR;
                    TELA_LIMPAR;
                break;
            default:
                if(opcao != 0) {
                    printf(ANSI_VERMELHO "Opcao invalida\n" ANSI_RESET);
                    TELA_PAUSAR;
                }
                break;
        }
    }while(opcao != 0);
    free(buscaProd);
    TELA_LIMPAR;
}

void pdv_exibir(Produto **produtos, int quant) {
    TELA_LIMPAR;
    printf(ANSI_AZUL "\nLista de Produtos\n" ANSI_RESET);

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

int pdv_remover(Produto **produtos, int quant) {
    pdv_exibir(produtos, quant);
    int id;

    printf("Escolha um produto pelo id para remover: ");
    scanf("%d", &id);
    id--;
    getchar();

    if(id >= 0 && id <= quant - 1) {
        free(produtos[id]);
        if(id <= quant - 1)
            produtos[id] = produtos[id - 1];
        TELA_LIMPAR;
        printf(ANSI_VERDE "      [ Produto removido ]\n" ANSI_RESET);
        return -1;
    } else {
        TELA_LIMPAR;
        printf(ANSI_VERMELHO "        [ ID INVALIDO ]\n" ANSI_RESET);
        return 0;
    }
}

void pdv_alterar(Produto **produtos, int quant) {
    TELA_LIMPAR;
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
        TELA_LIMPAR;
        printf(ANSI_VERMELHO "      [ Codigo invalido ]\n" ANSI_RESET);
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
        printf(ANSI_VERMELHO "\n\tNao foi possivel abrir/criar o arquivo!\n" ANSI_RESET);
    
    TELA_LIMPAR;
    printf(ANSI_VERDE "    [ Base de dados salva ]\n" ANSI_RESET);
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
        printf(ANSI_VERMELHO "\n\tNao foi possivel abrir/criar arquivo!\n" ANSI_RESET);
    
    TELA_LIMPAR;
    printf(ANSI_VERDE "  [ Base de dados atualizada ]\n" ANSI_RESET);
    return quant;
}

void pdv_erro() {
    TELA_LIMPAR;
    printf(ANSI_VERMELHO "       [ OPCAO INVALIDA ]       \n" ANSI_RESET);
}

void pdv_sair(Produto **produtos, int quant) {
    for(int i = 0; i < quant; i++)
        free(produtos[i]);

    TELA_LIMPAR;
    printf(ANSI_AZUL "\nObrigado por usar nosso programa\nAte a proxima!\n\n" ANSI_RESET);
}