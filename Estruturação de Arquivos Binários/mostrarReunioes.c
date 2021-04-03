#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *arquivo;

struct reuniao {
    int id;
    int dia,mes,ano; // posicoes 0, 1 e 2,respectivamente, do vetor de modificacoes.
    int hora,minuto; // posicoes 3 e 4, respectivamente, do vetor de motificacoes.
    int qtdPessoas; // posicao 5 do vetor de modificacoes.
};

struct reuniao CriarReuniao(int id, int ano, int mes, int dia, int hora, int minuto, int qtdPessoas);
struct reuniao *LerArquivo(FILE *arquivo, char nomeArquivo[]);
void MostrarReunioes(struct reuniao *ponteiro);


int main(void) {
    char nomeArquivoOriginal[] = "original.bin";
    char nomeArquivoCorrigido[] = "corrigido.bin";
    struct reuniao *ponteiro = LerArquivo(arquivo, nomeArquivoCorrigido);

    MostrarReunioes(ponteiro);
    free(ponteiro);
}

struct reuniao CriarReuniao(int id, int ano, int mes, int dia, int hora, int minuto, int qtdPessoas) {
    struct reuniao novaReuniao;
    novaReuniao.id = id;
    novaReuniao.ano = ano;
    novaReuniao.mes = mes;
    novaReuniao.dia = dia;
    novaReuniao.hora = hora;
    novaReuniao.minuto = minuto;
    novaReuniao.qtdPessoas = qtdPessoas;
    return novaReuniao;
}

struct reuniao *LerArquivo(FILE *arquivo, char nomeArquivo[]) {
    int quantidade;
    arquivo = fopen(nomeArquivo, "rb");
    fseek(arquivo, 0, SEEK_END);
    quantidade = ftell(arquivo) / sizeof(struct reuniao);
    fseek(arquivo, 0, SEEK_SET);
    struct reuniao *ponteiro = (struct reuniao *)malloc(sizeof(struct reuniao) * quantidade);
    fread(ponteiro, sizeof(struct reuniao), quantidade, arquivo);
    fclose(arquivo);
    return ponteiro;
}

void MostrarReunioes(struct reuniao *ponteiro) {
    printf("\n-----   Reunioes Agendadas -----\n");
    bool temReuniao = false;
    int i;
    for(i = 0; i < _msize(ponteiro) / sizeof(struct reuniao); i++) {
        temReuniao = true;
        printf("ID: %d   Quantidade de pessoas: %d\n", ponteiro[i].id, ponteiro[i].qtdPessoas);
        printf("Data: %d/%d/%d\n", ponteiro[i].dia, ponteiro[i].mes, ponteiro[i].ano);
        printf("Horario: %d horas e %d minutos\n\n", ponteiro[i].hora, ponteiro[i].minuto);
    }
    if(!temReuniao) {
        printf("Nao existe nenhuma reuniao agendada.\n");
    }
}