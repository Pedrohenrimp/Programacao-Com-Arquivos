#include "gerarArquivoDat.c"

int main(void) {
    bool continuar = true;
    int opcaoMenu;
    char palavra[50];
    char nomeArquivoTexto[50];
    char nomeArquivoDat[] = "indice.dat";
    struct Palavra *lista2 = CriarLista();
    struct Palavra *lista1 = CriarLista();

    while(continuar) {
        printf("---------------     Menu     ---------------\n");
        printf("1) Criar indice para palavras de um arquivo.\n");
        printf("2) Utilizar indice para realizar buscas.\n");
        printf("3) Encerrar o Programa.\n");

        printf("\nDigite uma das opcoes:\n");
        scanf(" %d", &opcaoMenu);

        switch (opcaoMenu)
        {
        case 1:
            printf("\nDigite o nome do arquivo:\n");
            scanf(" %s", nomeArquivoTexto);
            lista1 = CopiarArquivoTexto(lista1, nomeArquivoTexto);
            GerarArquivoDat(lista1, nomeArquivoDat);
            printf("\nArquivo indice.dat gerado com sucesso!\n");
            break;
        
        case 2:
            lista2 = CopiarArquivoDat(lista2, nomeArquivoDat);
            printf("\nDigite a palavra que deseja buscar:\n");
            scanf(" %s", palavra);
            struct Palavra *auxiliar = BuscarPalavra(lista2, palavra);
            if(auxiliar != NULL) {
                printf("\nPalavra: %s", auxiliar->letras);
                printf("Quantidade de Ocorrencias: %d\n", auxiliar->qtdOcorrencias);
                printf("Linhas de Ocorrencia:");
                int i;
                for(i = 0; i < auxiliar->qtdOcorrencias; i++) {
                    printf(" %d", auxiliar->linhas[i]);
                }
                printf("\n");
            }
            else {
                printf("\nA palavra %s nao foi encontrada no arquivo %s.\n", palavra, nomeArquivoDat);
            }
            break;
        case 3:
            printf("\nEncerrando o Programa...\n");
            DestruirLista(lista1);
            DestruirLista(lista2);
            printf("Programa Encerrado!\n");
            continuar = false;
            break;
        }
    }
}