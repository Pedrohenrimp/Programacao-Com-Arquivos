#include "gerarArquivoDat.c"

struct Palavra *CopiarArquivoDat(struct Palavra *lista, char nomeArquivo[]) {
    FILE *arquivo;
    if(arquivo != NULL) {
        arquivo = fopen(nomeArquivo, "rb");
        int qtdOcorrencias, totalPalavras, tamanhoPalavra;
        char palavra[50];
        fseek(arquivo, 0, SEEK_END);
        int tamanhoArquivo = ftell(arquivo);
        fseek(arquivo, 0, SEEK_SET);
        fread(&totalPalavras, sizeof(int), 1, arquivo);

        while(ftell(arquivo) != tamanhoArquivo) {
            fread(&tamanhoPalavra, sizeof(int), 1, arquivo);
            fread(&palavra, sizeof(char), tamanhoPalavra, arquivo);
            palavra[tamanhoPalavra] = '\0';
            fread(&qtdOcorrencias, sizeof(int), 1, arquivo);
            int *linhas = (int *) malloc(sizeof(int) * qtdOcorrencias);
            int i;
            for(i = 0; i < qtdOcorrencias; i++) {
                fread(&linhas[i], sizeof(int), 1, arquivo);
            }
            lista = InserirOrdemAlfabetica(lista, palavra, linhas[0]);
            for(i = 1; i < qtdOcorrencias; i++) {
                AtualizarPalavra(lista, palavra, linhas[i]);
            }
            free(linhas);
        }
        fclose(arquivo);
        return lista;
    }
    else {
        return NULL;
    }
}