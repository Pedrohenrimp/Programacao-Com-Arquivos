#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE *arquivo;

struct Palavra {
    //caracteres que formam a palavra (pode ser utilizado std::string de C++)
    char letras[50];
    int qtdOcorrencias;
    //vetor dinâmico (pode ser utilizado std::vector de C++ em substituição a esses 2 últimos campos)
    int *linhas;
    struct Palavra *anterior, *proximo;
};

struct Palavra *CriarLista();
struct Palavra *CriarPalavra(char letras[], int linha);
struct Palavra *InserirOrdemAlfabetica(struct Palavra *lista, char palavra[], int linha);
struct Palavra *BuscarPalavra(struct Palavra *lista, char palavra[]);
void AtualizarPalavra(struct Palavra *lista, char palavra[], int linha);
struct Palavra *DestruirLista(struct Palavra *lista);
void ListarPalavras(struct Palavra *lista);
struct Palavra *CopiarArquivoTexto(struct Palavra *lista, char nomeArquivo[]);
void ListarPalavras(struct Palavra *lista);
int ContarPalavras(struct Palavra *lista);




struct Palavra *CopiarArquivoTexto(struct Palavra *lista, char nomeArquivo[]) {
    char palavra[50];
    arquivo = fopen(nomeArquivo, "r");
    if(arquivo != NULL) {
        int linha = 1;
        char caractereAuxiliar = fgetc(arquivo);
        while(caractereAuxiliar != EOF) {
            int i = 0;
            while(caractereAuxiliar != ' ' && caractereAuxiliar != '\n' && caractereAuxiliar != '\r' && caractereAuxiliar != EOF) {
                if(caractereAuxiliar != '.' && caractereAuxiliar != ',' && caractereAuxiliar != '?' && caractereAuxiliar != '!') {
                    palavra[i] = caractereAuxiliar;    
                    caractereAuxiliar = fgetc(arquivo);
                    i++;
                }
                else {
                    break;
                }
            }
            palavra[i] = '\0';
            if(strlen(palavra) > 1) {
                if(BuscarPalavra(lista, palavra) == NULL) {
                    lista = InserirOrdemAlfabetica(lista, palavra, linha);
                }
                else {
                    AtualizarPalavra(lista, palavra, linha);
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

struct Palavra *CriarLista()
{
    struct Palavra *sentinela = (struct Palavra *) malloc(sizeof(struct Palavra));
    sentinela->anterior = sentinela;
    sentinela->proximo = sentinela;
    return sentinela;
}

struct Palavra *CriarPalavra(char letras[], int linha)
{
    struct Palavra *resposta = (struct Palavra *) malloc(sizeof(struct Palavra));
    strcpy(resposta->letras, letras);
    resposta->qtdOcorrencias = 1;
    resposta->linhas = (int *) malloc(sizeof(int));
    resposta->linhas[0] = linha;
    resposta->anterior = NULL;
    resposta->proximo = NULL;
    return resposta;
}

struct Palavra *InserirOrdemAlfabetica(struct Palavra *lista, char palavra[], int linha)
{
    
    struct Palavra *auxiliar = lista->proximo;
    if(auxiliar == lista) {
        struct Palavra *novo = CriarPalavra(palavra, linha);
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
                struct Palavra *novo = CriarPalavra(palavra, linha);
                novo->proximo = auxiliar;
                novo->anterior = auxiliar->anterior;
                auxiliar->anterior->proximo = novo;
                auxiliar->anterior = novo;
                incluido = true;
                break;
            }
            auxiliar = auxiliar->proximo;
        }    
        if(auxiliar == lista || incluido == false)
        {
            struct Palavra *novo = CriarPalavra(palavra, linha);
            novo->proximo = lista;
            novo->anterior = lista->anterior;
            lista->anterior->proximo = novo;
            lista->anterior = novo;
        }
    }
    return lista;   
}

struct Palavra *BuscarPalavra(struct Palavra *lista, char palavra[]) {
    struct Palavra *auxiliar = lista->proximo;
    while(auxiliar != lista && strcmp(auxiliar->letras, palavra) != 0) {
        auxiliar = auxiliar->proximo;
    }
    if(auxiliar != lista) {
        return auxiliar;
    }
    return NULL;
}

void AtualizarPalavra(struct Palavra *lista, char palavra[], int linha) {
    struct Palavra *auxiliar = BuscarPalavra(lista, palavra);
    if(auxiliar != NULL) {
        auxiliar->qtdOcorrencias++;
        auxiliar->linhas = (int *) realloc(auxiliar->linhas, sizeof(int) * auxiliar->qtdOcorrencias);
        auxiliar->linhas[auxiliar->qtdOcorrencias - 1] = linha;
    }
}

struct Palavra *DestruirLista(struct Palavra *lista) {
    struct Palavra *auxiliar = lista;
    lista->anterior->proximo = NULL;
    while(auxiliar != NULL) {
        lista = lista->proximo;
        free(lista->linhas);
        free(auxiliar);
        auxiliar = lista;
    }
    return NULL;
}

void ListarPalavras(struct Palavra *lista)
{
    struct Palavra *auxiliar = lista->proximo;
    while(auxiliar != lista)
    {
        printf("%s: %d ocorrencia(s).\n", auxiliar->letras, auxiliar->qtdOcorrencias);
        auxiliar = auxiliar->proximo;
    }
}

int ContarPalavras(struct Palavra *lista)
{
    int qtdPalavras = 0;
    struct Palavra *auxiliar = lista->proximo;
    while(auxiliar != lista)
    {
        qtdPalavras++;
        auxiliar = auxiliar->proximo;
    }
    return qtdPalavras;
}