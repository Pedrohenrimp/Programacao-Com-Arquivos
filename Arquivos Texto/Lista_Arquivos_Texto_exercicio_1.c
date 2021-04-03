#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>


struct elemento {
    char caractere;
    int quantidade;
    struct elemento *anterior, *proximo;
};

struct elementoVetor {
    char caractere;
    int quantidade;
};

#define Troca(A,B) {struct elementoVetor t = A; A = B; B = t;}

struct elemento *CriarLista();
struct elemento *CriarElemento(char caractere);
struct elemento *InserirFinal(struct elemento *lista, char caractere);
struct elemento *BuscarElemento(struct elemento *lista, char caractere);
bool AtualizarElemento(struct elemento *lista, char caractere);
int TamanhoLista(struct elemento *lista);
void QuickSort(struct elementoVetor *vet, int prim, int ult);
struct elementoVetor *VetorElementos(struct elemento *lista);
void MostrarElementos(struct elementoVetor *ponteiro);
struct elemento *DestruirLista(struct elemento *lista);


int main(void) {
    char nomeArquivo[50];
    printf("Digite o Nome do Arquivo que deseja analisar:\n");
    scanf(" %s", nomeArquivo);

    struct elemento *lista = CriarLista();
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if(arquivo != NULL) {
        char caractereAuxiliar = fgetc(arquivo);
        while(caractereAuxiliar != EOF) {
            if(BuscarElemento(lista, caractereAuxiliar) == NULL) {
                lista = InserirFinal(lista, caractereAuxiliar);
            }
            else {
                AtualizarElemento(lista, caractereAuxiliar);
            }
            caractereAuxiliar = fgetc(arquivo);
        }
    }
    fclose(arquivo);
    struct elementoVetor *vetor = VetorElementos(lista);
    MostrarElementos(vetor);
    DestruirLista(lista);
    free(vetor);
}

struct elemento *CriarLista()
{
    struct elemento *sentinela = (struct elemento *) malloc(sizeof(struct elemento));
    sentinela->anterior = sentinela;
    sentinela->proximo = sentinela;
    return sentinela;
}

struct elemento *CriarElemento(char caractere)
{
    struct elemento *resposta = (struct elemento *) malloc(sizeof(struct elemento));
    resposta->caractere = caractere;
    resposta->quantidade = 1;
    resposta->anterior = NULL;
    resposta->proximo = NULL;
    return resposta;
}

struct elemento *InserirFinal(struct elemento *lista, char caractere)
{
    struct elemento *novo = CriarElemento(caractere);
    novo->proximo = lista;
    novo->anterior = lista->anterior;
    lista->anterior->proximo = novo;
    lista->anterior = novo;
    return lista;
}

struct elemento *BuscarElemento(struct elemento *lista, char caractere) {
    struct elemento *auxiliar = lista->proximo;
    while(auxiliar != lista && auxiliar->caractere != caractere) {
        auxiliar = auxiliar->proximo;
    }
    if(auxiliar != lista) {
        return auxiliar;
    }
    return NULL;
}

bool AtualizarElemento(struct elemento *lista, char caractere) {
    struct elemento *auxiliar = BuscarElemento(lista, caractere);
    if(auxiliar != NULL) {
        auxiliar->quantidade++;
        return true;
    }
    return false;
}

int TamanhoLista(struct elemento *lista)
{
    int tamanho = 0;
    struct elemento *auxiliar = lista->proximo;
    while(auxiliar != lista)
    {
        tamanho++;
        auxiliar = auxiliar->proximo;
    }
    return tamanho;
}

void QuickSort(struct elementoVetor *vet, int prim, int ult)
{
    int i, j, pivo ,acabou = 0;
    if (prim < ult) 
    {
        pivo = vet[prim].quantidade;
        i = prim, j = ult + 1;
        while (acabou == 0) 
        {
            do
                j--;
            while (vet[j].quantidade > pivo);
            do
                i++;
            while (vet[i].quantidade < pivo);

            if (i > j)
                acabou = 1;
            else Troca(vet[i], vet[j]);
        }

        Troca(vet[prim], vet[j]);
        QuickSort(vet, prim, j - 1);
        QuickSort(vet, j + 1, ult);
   }
}

struct elementoVetor *VetorElementos(struct elemento *lista) {
    int tamanhoLista = TamanhoLista(lista);
    struct elemento *auxiliar = lista->proximo;
    struct elementoVetor *ponteiro = (struct elementoVetor *) malloc(sizeof(struct elementoVetor) * tamanhoLista);
    int i;
    for(i = 0; i < tamanhoLista; i++) {
        ponteiro[i].caractere = auxiliar->caractere;
        ponteiro[i].quantidade = auxiliar->quantidade;
        auxiliar = auxiliar->proximo;
    }
    return ponteiro;
}

void MostrarElementos(struct elementoVetor *ponteiro) {
    int tamanhoVetor = _msize(ponteiro) / sizeof(struct elementoVetor);
    printf(" %d", tamanhoVetor);
    QuickSort(ponteiro, 0, tamanhoVetor - 1);
    int i;
    for(i = tamanhoVetor; i > 0; i--) {
        printf("\nCaractere: %c \nQuantidade: %d\n", ponteiro[i].caractere, ponteiro[i].quantidade);
    }
}

struct elemento *DestruirLista(struct elemento *lista) {
    struct elemento *auxiliar = lista;
    lista->anterior->proximo = NULL;
    while(auxiliar != NULL) {
        lista = lista->proximo;
        free(auxiliar);
        auxiliar = lista;
    }
    return NULL;
}

/*Faça um programa que analise a quantidade de vezes que cada caractere
 (qualquer caractere com código acima de 32) aparece em um arquivo texto.
 O programa deve perguntar o nome do arquivo a ser lido e mostrar o resultado
 em ordem descrente de acordo com a quantidade de aparições.*/
