#include "copiarArquivoDat.c"

int main(void) {
    bool continuar = true;
    int opcaoMenu;
    char nomeArquivoTexto[50];
    char nomeArquivoDat[] = "indice.dat";

    struct Indice *indice = CriarIndice();

    while(continuar) {
        printf("\n\n---------------     Menu     ---------------\n");
        printf("1) Processar um Arquivo Texto.\n");
        printf("2) Salvar Indice Atual.\n");
        printf("3) Ler um Arquivo de Indice.\n");
        printf("4) Buscar no Indice\n");
        printf("5) Encerrar o Programa.\n");

        printf("\nDigite uma das opcoes:\n");
        scanf(" %d", &opcaoMenu);

        switch (opcaoMenu)
        {
        case 1:
            printf("\nDigite o nome do arquivo:\n");
            scanf(" %s", nomeArquivoTexto);
            if(BuscarArquivo(indice, nomeArquivoTexto) == NULL) {
                InserirArquivo(indice, nomeArquivoTexto);
                CopiarArquivoTexto(indice, indice->palavras, nomeArquivoTexto, PosicaoArquivo(indice->arquivos, nomeArquivoTexto, indice->qtdArquivos));
                printf("ok");
                printf("\nProcessamento realizado com sucesso!\n");
            }
            else {
                printf("\nO arquivo ja havia sido processado. Nao foi possivel realizar uma nova leitura.\n");
            }
            break;
        case 2:
            GerarArquivoDat(indice, nomeArquivoDat);
            printf("\nIndice gerado com sucesso!\n");
            break;
        case 3:
            DestruirIndice(indice);
            indice = CriarIndice();
            indice->palavras = CopiarArquivoDat(indice, indice->palavras, nomeArquivoDat);
            break;
        case 4:
            printf("Escolha o Tipo de Busca:\n");
            printf("1) Busca Simples\n");
            printf("2) Busca Composta\n");
            scanf(" %d", &opcaoMenu);

            char palavra[50];
            if(opcaoMenu == 1) {
                printf("Digite a Palavra que deseja Buscar:\n");
                scanf(" %s", palavra);
                struct Palavra *resposta = BuscarPalavra(indice, palavra);
                if(resposta != NULL) {
                    ImprimirPalavra(indice, resposta);
                }
                else {
                    printf("Palavra nao encontrada no Indice!\n");
                }
            }
            else if(opcaoMenu == 2) {
                printf("Escolha o Operador de Busca:\n");
                printf("1) E\n");
                printf("2) OU\n");
                scanf(" %d", &opcaoMenu);
                char palavra1[50], palavra2[50];
                printf("Digite a Primeira Palavra que deseja Buscar:\n");
                scanf(" %s", palavra1);
                printf("Digite a Segunda Palavra que deseja Buscar:\n");
                scanf(" %s", palavra2);
                if(opcaoMenu == 1) {
                    ImprimirBuscaComposta(indice, palavra1, palavra2, 1);
                }
                else if(opcaoMenu == 2) {
                    ImprimirBuscaComposta(indice, palavra1, palavra2, 2);
                }
                else {
                    printf("Opcao Invalida!\n");
                }
                
            }
            else {
                printf("Opcao Invalida!\n");
            }
            break;
        case 5:
            printf("\nEncerrando o Programa...\n");
            DestruirIndice(indice);
            printf("Programa Encerrado!\n");
            continuar = false;
            break;
        }
    }
}