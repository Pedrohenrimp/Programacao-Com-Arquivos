#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

FILE *arquivo;

struct Ocorrencia {
    int arquivo; //posição do arquivo na lista de arquivos processados.
    int qtdOcorrencias; //qtd de vezes em que a palavra foi encontrada
    int *linhas; //linhas onde a palavra foi encontrada
    struct Ocorrencia *proximo; //ponteiro para a próxima ocorrência da palavra em outro arquivo
};
struct Palavra {
    char letras[50]; //a palavra em questão
    int qtdOcorrencias; //quantidade de arquivos que possuem a palavra
    struct Ocorrencia *ocorrencias; //lista contendo informações da ocorrência de uma palavra em um arquivo
    struct Palavra *proximo, *anterior;//ponteiro para a próxima palavra encontrada em qualquer arquivo (em ordem alfabética)
};
struct Arquivo {
    char nomeArquivo[50]; //nome de um arquivo texto já processado
    struct Arquivo *proximo; //ponteiro para o nome do próximo arquivo texto
};
struct Indice {
    int qtdArquivos; //quantidade de arquivos de texto lidos até então
    struct Arquivo *arquivos; //lista contendo os nomes dos arquivos texto já processados
    int qtdPalavras;
    struct Palavra *iniciais[26];
    struct Palavra *palavras;//lista contendo todas as palavras já encontrada
};

struct Palavra *CopiarArquivoTexto(struct Indice *indice, struct Palavra *lista, char nomeArquivo[], int posicaoArquivo);
struct Indice *CriarIndice();
struct Arquivo *CriarArquivo(char nomeArquivo[]);
struct Palavra *CriarLista();
struct Ocorrencia *CriarOcorrencia(int posicaoArquivo, int linha);
struct Palavra *CriarPalavra(char letras[], int linha, int posicaoArquivo);
struct Palavra *BuscarPalavra(struct Indice *indice, char palavra[]);
void InserirArquivo(struct Indice *indice, char nomeArquivo[]);
struct Palavra *InserirOrdemAlfabetica(struct Indice *indice, struct Palavra *lista, char palavra[], int linha, int posicaoArquivo);
struct Arquivo *BuscarArquivo(struct Indice *indice, char nomeArquivo[]);
void AtualizarPalavra(struct Palavra *lista, char palavra[], int linha, int posicaoArquivo);
int PosicaoArquivo(struct Arquivo *arquivos, char nomeArquivo[], int qdtArquivos);
struct Ocorrecia *DestruirOcorrencias(struct Ocorrencia *lista);
struct Palavra *DestruirPalavras(struct Palavra *lista);
struct Arquivo *DestruirArquivos(struct Arquivo *lista);
struct Indice *DestruirIndice(struct Indice *indice);


struct Palavra *CopiarArquivoTexto(struct Indice *indice, struct Palavra *lista, char nomeArquivo[], int posicaoArquivo) {
    char palavra[50];
    arquivo = fopen(nomeArquivo, "r");
    if(arquivo != NULL) {
        int linha = 1;
        char caractereAuxiliar = fgetc(arquivo);
        while(caractereAuxiliar != EOF) {
            int i = 0;
            while(caractereAuxiliar != ' ' && caractereAuxiliar != '\n' && caractereAuxiliar != '\r' && caractereAuxiliar != EOF) {
                if(caractereAuxiliar != '.' && caractereAuxiliar != ',' && caractereAuxiliar != '?' && caractereAuxiliar != '!') {
                    palavra[i] = tolower(caractereAuxiliar);
                    caractereAuxiliar = fgetc(arquivo);
                    i++;
                }
                else {
                    break;
                }
            }
            palavra[i] = '\0';
            if(strlen(palavra) > 1) {
                printf("okay");
                if(BuscarPalavra(lista, palavra) == NULL) {
                    lista = InserirOrdemAlfabetica(indice, lista, palavra, linha, posicaoArquivo);
                }
                else {
                    AtualizarPalavra(lista, palavra, linha, posicaoArquivo);
                }
            }
            if(caractereAuxiliar == '\n') {
                linha++;
            }
            palavra[0] = '\0';
            if(caractereAuxiliar != EOF) {
                caractereAuxiliar = fgetc(arquivo);
            }
        }
    }
    fclose(arquivo);
    return lista;
}

struct Indice *CriarIndice() {
    struct Indice *novoIndice = (struct Indice *) malloc(sizeof(struct Indice));
    novoIndice->qtdArquivos = 0;
    novoIndice->qtdPalavras = 0;
    novoIndice->arquivos = NULL;
    novoIndice->palavras = CriarLista();
    int i;
    for(i = 0; i < 26; i++) {
        novoIndice->iniciais[i] = (struct Palavra *) malloc(sizeof(struct Palavra));
        novoIndice->iniciais[i]->letras[0] = (char) ('a' + i);
        novoIndice->iniciais[i]->letras[1] = '\0';
        novoIndice->iniciais[i]->ocorrencias = NULL;
        novoIndice->iniciais[i]->proximo = NULL;
        novoIndice->iniciais[i]->anterior = NULL;
    }
    return novoIndice;
}

struct Arquivo *CriarArquivo(char nomeArquivo[]) {
    struct Arquivo *novoArquivo = (struct Arquivo *) malloc(sizeof(struct Arquivo));
    strcpy(novoArquivo->nomeArquivo, nomeArquivo);
    novoArquivo->proximo = NULL;
    return novoArquivo;
}

struct Palavra *CriarLista() {
    struct Palavra *sentinela = (struct Palavra *) malloc(sizeof(struct Palavra));
    sentinela->anterior = sentinela;
    sentinela->proximo = sentinela;
    return sentinela;
}

struct Ocorrencia *CriarOcorrencia(int posicaoArquivo, int linha) {
    struct Ocorrencia *novaOcorrencia = (struct Ocorrencia *) malloc(sizeof(struct Ocorrencia));
    novaOcorrencia->arquivo = posicaoArquivo;
    novaOcorrencia->linhas = (int *) malloc(sizeof(int));
    novaOcorrencia->linhas[0] = linha;
    novaOcorrencia->qtdOcorrencias = 1;
    novaOcorrencia->proximo = NULL;
    return novaOcorrencia;
}

struct Palavra *CriarPalavra(char letras[], int linha, int posicaoArquivo) {
    struct Palavra *novaPalavra = (struct Palavra *) malloc(sizeof(struct Palavra));
    strcpy(novaPalavra->letras, letras);
    novaPalavra->qtdOcorrencias = 1;
    novaPalavra->ocorrencias = CriarOcorrencia(posicaoArquivo, linha);
    novaPalavra->anterior = NULL;
    novaPalavra->proximo = NULL;
    return novaPalavra;
}

struct Palavra *BuscarPalavra(struct Indice *indice, char palavra[]) {
    int i = palavra[0] - 96;
    struct Palavra *auxiliar = indice->iniciais[i];
    while(tolower(auxiliar->letras[0]) == tolower(palavra[0]) && strcmp(tolower(auxiliar->letras), tolower(palavra)) != 0) {
        auxiliar = auxiliar->proximo;
    }
    if(tolower(auxiliar->letras[0]) == tolower(palavra[0])) {
        return auxiliar;
    }
    return NULL;
}

void InserirArquivo(struct Indice *indice, char nomeArquivo[]) {
    if(indice->qtdArquivos > 0) {
        struct Arquivo *auxiliar = indice->arquivos;
        while(auxiliar != NULL) {
            if(auxiliar->proximo = NULL) {
                auxiliar->proximo = CriarArquivo(nomeArquivo);
                indice->qtdArquivos++;
            }
            auxiliar = auxiliar->proximo;
        }
    }
    else {
        indice->arquivos = CriarArquivo(nomeArquivo);
        indice->qtdArquivos++;
    }
}

struct Palavra *InserirOrdemAlfabetica(struct Indice *indice, struct Palavra *lista, char palavra[], int linha, int posicaoArquivo) {

    struct Palavra *auxiliar = lista->proximo;
    if(auxiliar == lista) {
        struct Palavra *novo = CriarPalavra(palavra, linha, posicaoArquivo);
        novo->proximo = lista;
        novo->anterior = lista->anterior;
        lista->anterior->proximo = novo;
        lista->anterior = novo;
    }
    else {
        bool incluido = false;
        while(auxiliar != lista)
        {
            int ordem = strcmp(palavra, auxiliar->letras);
            if(ordem <= 0)
            {
                struct Palavra *novo = CriarPalavra(palavra, linha, posicaoArquivo);
                novo->proximo = auxiliar;
                novo->anterior = auxiliar->anterior;
                auxiliar->anterior->proximo = novo;
                auxiliar->anterior = novo;
                if(novo->anterior == lista || tolower(novo->anterior->letras[0]) < tolower(novo->letras[0])) {
                    indice->iniciais[(int) tolower(novo->letras[0]) - 96] = novo;
                }
                incluido = true;
                break;
            }
            auxiliar = auxiliar->proximo;
        }
        if(auxiliar == lista || incluido == false)
        {
            struct Palavra *novo = CriarPalavra(palavra, linha, posicaoArquivo);
            novo->proximo = lista;
            novo->anterior = lista->anterior;
            lista->anterior->proximo = novo;
            lista->anterior = novo;
            if(novo->anterior == lista || tolower(novo->anterior->letras[0]) < tolower(novo->letras[0])) {
                indice->iniciais[(int) tolower(novo->letras[0]) - 96] = novo;
            }
        }
    }
    return lista;
}

struct Arquivo *BuscarArquivo(struct Indice *indice, char nomeArquivo[]) {
    struct Arquivo *auxiliar = indice->arquivos;
    while(auxiliar != NULL) {
        if(strcmp(auxiliar->nomeArquivo, nomeArquivo) == 0) {
            return auxiliar;
        }
        auxiliar = auxiliar->proximo;
    }
    return NULL;
}

void AtualizarPalavra(struct Palavra *lista, char palavra[], int linha, int posicaoArquivo) {
    struct Palavra *auxiliar = BuscarPalavra(lista, palavra);
    if(auxiliar != NULL) {
        struct Ocorrencia *auxiliarOcorrencias = auxiliar->ocorrencias;
        while(auxiliarOcorrencias != NULL) {
            if(auxiliarOcorrencias->arquivo == posicaoArquivo) {
                auxiliarOcorrencias->qtdOcorrencias++;
                auxiliarOcorrencias->linhas = realloc(auxiliarOcorrencias->linhas, sizeof(struct Ocorrencia) * auxiliarOcorrencias->qtdOcorrencias);
                auxiliarOcorrencias->linhas[auxiliarOcorrencias->qtdOcorrencias - 1] = linha;
                break;
            }
            else if(auxiliarOcorrencias->proximo == NULL) {
                struct Ocorrencia *novaOcorrencia = CriarOcorrencia(posicaoArquivo, linha);
                auxiliarOcorrencias->proximo = novaOcorrencia;
                break;
            }
            auxiliarOcorrencias = auxiliarOcorrencias->proximo;
        }
    }
}

int PosicaoArquivo(struct Arquivo *arquivos, char nomeArquivo[], int qdtArquivos) {
    int posicao = 0;
    struct Arquivo *auxiliar = arquivos;
    int i;
    for(i = 0; i < qdtArquivos; i++) {
        if(strcmp(nomeArquivo, auxiliar->nomeArquivo) == 0) {
            posicao = i;
            break;
        }
        auxiliar = auxiliar->proximo;
    }
    return posicao;
}

struct Ocorrecia *DestruirOcorrencias(struct Ocorrencia *lista) {
    struct Ocorrencia *auxiliar = lista;
    while(auxiliar != NULL) {
        lista = lista->proximo;
        free(auxiliar->linhas);
        free(auxiliar);
        auxiliar = lista;
    }
    return NULL;
}

struct Palavra *DestruirPalavras(struct Palavra *lista) {
    struct Palavra *auxiliar = lista;
    lista->anterior->proximo = NULL;
    while(auxiliar != NULL) {
        lista = lista->proximo;
        auxiliar->ocorrencias = DestruirOcorrencias(auxiliar->ocorrencias);
        free(auxiliar);
        auxiliar = lista;
    }
    return NULL;
}

struct Arquivo *DestruirArquivos(struct Arquivo *lista) {
    struct Arquivo *auxiliar = lista;
    while(auxiliar != NULL) {
        lista = lista->proximo;
        free(auxiliar);
        auxiliar = lista;
    }
    return NULL;
}

struct Indice *DestruirIndice(struct Indice *indice) {
    DestruirPalavras(indice->palavras);
    DestruirArquivos(indice->arquivos);
    free(indice);
    return NULL;
}