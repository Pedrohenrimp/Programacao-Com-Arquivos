#include "copiarArquivosTexto.c"

void GerarArquivoDat(struct Indice *indice, char nomeArquivo[]) {
    FILE *arquivo;
    struct Palavra *auxiliarPalavras = indice->palavras->proximo;
    struct Arquivo *auxiliarArquivos = indice->arquivos;
    int totalPalavras = indice->qtdPalavras;
    int totalArquivos = indice->qtdArquivos;
    arquivo = fopen(nomeArquivo, "wb");
    fwrite(&totalArquivos, sizeof(int), 1, arquivo);
    int i, j, k;
    for(i = 0; i < totalArquivos; i++) {
        int tamanhoNomeArquivo = strlen(auxiliarArquivos->nomeArquivo);
        fwrite(&tamanhoNomeArquivo, sizeof(int), 1, arquivo);
        fwrite(&auxiliarArquivos->nomeArquivo, sizeof(char), tamanhoNomeArquivo, arquivo);
        auxiliarArquivos = auxiliarArquivos->proximo;
    }
    fwrite(&totalPalavras, sizeof(int), 1, arquivo);
    for(i = 0; i < totalPalavras; i++) {
        int tamanhoPalavra = strlen(auxiliarPalavras->letras);
        int totalOcorrencias = auxiliarPalavras->qtdOcorrencias;
        fwrite(&tamanhoPalavra, sizeof(int), 1, arquivo);
        fwrite(&auxiliarPalavras->letras, sizeof(char), tamanhoPalavra, arquivo);
        fwrite(&totalOcorrencias, sizeof(int), 1, arquivo);
        
        struct Ocorrencia *auxiliarOcorrencias = auxiliarPalavras->ocorrencias;
        for(j = 0; j < totalOcorrencias; j++) {
            fwrite(&auxiliarOcorrencias->arquivo, sizeof(int), 1, arquivo);
            fwrite(&auxiliarOcorrencias->qtdOcorrencias, sizeof(int), 1, arquivo);
            for(k = 0; k < auxiliarOcorrencias->qtdOcorrencias; k++) {
                fwrite(&auxiliarOcorrencias->linhas[k], sizeof(int), 1, arquivo);
            }
            auxiliarOcorrencias = auxiliarOcorrencias->proximo;
        }
        auxiliarPalavras = auxiliarPalavras->proximo;
    }
    fclose(arquivo);
}

