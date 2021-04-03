#include "gerarArquivoDat.c"

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
        printf("4) Encerrar o Programa.\n");

        printf("\nDigite uma das opcoes:\n");
        scanf(" %d", &opcaoMenu);

        switch (opcaoMenu)
        {
        case 1:
            printf("\nDigite o nome do arquivo:\n");
            scanf(" %s", nomeArquivoTexto);
            if(BuscarArquivo(indice, nomeArquivoTexto) == NULL) {
                InserirArquivo(indice, nomeArquivoTexto);
                CopiarArquivoTexto(indice->palavras, nomeArquivoTexto, PosicaoArquivo(indice->arquivos, nomeArquivoTexto, indice->qtdArquivos));
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
            // Falta ser Implementado.
            break;
        case 4:
            printf("\nEncerrando o Programa...\n");
            DestruirIndice(indice);
            printf("Programa Encerrado!\n");
            continuar = false;
            break;
        }
    }
}