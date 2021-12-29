#include "copiarArquivosTexto.c"

void ImprimirPalavra(struct Indice *indice, struct Palavra *palavra) {
    struct Ocorrencia *auxiliar = palavra->ocorrencias;
    printf("\nPalavra: %s\n", palavra->letras);
    int i, j;
    for(i = 0; i < palavra->qtdOcorrencias; i++) {
        struct Arquivo *arqAux = indice->arquivos;
        for(j = 0; j < auxiliar->arquivo; j++) {
            arqAux = arqAux->proximo;
        }
        printf("\nNome do Arquivo: %s\n", arqAux->nomeArquivo);
        printf("Linhas de Ocorrencia:");
        for(j = 0; j < auxiliar->qtdOcorrencias; j++) {
            printf(" %d", auxiliar->linhas[j]);
        }
        printf("\n");
    }
}

bool ContemValor(int *vetor, int x, int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i] == x) {
            return true;
        }
    }
    return false;
}

void ImprimirBuscaComposta(struct Indice *indice, char palavra1[], char palavra2[], int operador) {
    struct Palavra *primPalavra = BuscarPalavra(indice, palavra1);
    struct Palavra *segPalavra = BuscarPalavra(indice, palavra2);
    if(operador == 1) {
        struct Ocorrencia *auxiliar1 = primPalavra->ocorrencias;
        struct Ocorrencia *auxiliar2 = segPalavra->ocorrencias;
        int i, j, k;
        for(i = 0; i < primPalavra->qtdOcorrencias; i++) {
            for(j = 0; j < segPalavra->qtdOcorrencias; j++) {
                if(auxiliar1->arquivo == auxiliar2->arquivo) {
                    struct Arquivo *arqAux = indice->arquivos;
                    for(k = 0; k < auxiliar1->arquivo; k++) {
                        arqAux = arqAux->proximo;
                    }
                    printf("\nNome do Arquivo: %s\n", arqAux->nomeArquivo);
                }
                auxiliar2 = auxiliar2->proximo;
            }
            auxiliar1 = auxiliar1->proximo;
        }
    }
    if(operador == 2) {
        struct Ocorrencia *auxiliar1 = primPalavra->ocorrencias;
        struct Ocorrencia *auxiliar2 = segPalavra->ocorrencias;
        int *vetor = (int *) malloc(sizeof(int) * primPalavra->qtdOcorrencias);
        int i, j;
        for(i = 0; i < primPalavra->qtdOcorrencias; i++) {
            struct Arquivo *arqAux = indice->arquivos;
            for(j = 0; j < auxiliar1->arquivo; j++) {
                arqAux = arqAux->proximo;
            }
            printf("\nNome do Arquivo: %s\n", arqAux->nomeArquivo);
            vetor[i] = auxiliar1->arquivo;
            auxiliar1 = auxiliar1->proximo;
        }
        for(i = 0; i < segPalavra->qtdOcorrencias; i++) {
            struct Arquivo *arqAux = indice->arquivos;
            for(j = 0; j < auxiliar2->arquivo; j++) {
                arqAux = arqAux->proximo;
            }
            if(!ContemValor(vetor, auxiliar2->arquivo, primPalavra->qtdOcorrencias)) {
                printf("\nNome do Arquivo: %s\n", arqAux->nomeArquivo);
            }
            auxiliar2 = auxiliar2->proximo;
        }
    }
}
