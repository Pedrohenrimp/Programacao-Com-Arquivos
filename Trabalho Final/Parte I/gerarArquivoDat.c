#include "copiarArquivoDat.c"

void GerarArquivoDat(struct Palavra *lista, char nomeArquivo[]) {
    FILE *arquivo;
    struct Palavra *auxiliar = lista->proximo;
    int totalPalavras = ContarPalavras(lista);
    arquivo = fopen(nomeArquivo, "wb");
    fwrite(&totalPalavras, sizeof(int), 1, arquivo);
    int i;
    for(i = 0; i < totalPalavras; i++) {
        int tamanhoPalavra = strlen(auxiliar->letras);
        fwrite(&tamanhoPalavra, sizeof(int), 1, arquivo);
        fwrite(&auxiliar->letras, sizeof(char), tamanhoPalavra, arquivo);
        fwrite(&auxiliar->qtdOcorrencias, sizeof(int), 1, arquivo);
        fwrite(auxiliar->linhas, sizeof(int), auxiliar->qtdOcorrencias, arquivo);
        auxiliar = auxiliar->proximo;
    }
    fclose(arquivo);
}

