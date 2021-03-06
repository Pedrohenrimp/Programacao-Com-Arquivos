#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *arquivo;

struct reuniao {
    char assunto[20];
    int ano, mes, dia, hora, minuto;
};

struct reuniao CriarReuniao(char assunto[], int ano, int mes, int dia, int hora, int minuto);
void EscreverNoAquivo(struct reuniao *reuniao, FILE *arquivo);
struct reuniao *LerArquivo(FILE *arquivo);
void MostrarReunioes(struct reuniao *ponteiro, int ano, int mes, int dia);


int main(void) {
    struct reuniao *ponteiro = (struct reuniao *) malloc(sizeof(struct reuniao));
    int opcao, dia, mes, ano, hora, minuto;
    char assunto[20];
    printf("Escolha a Opcao desejada:\n");
    printf("1) Registar Reuniao\n");
    printf("2) Mostrar Reunioes Agendadas\n");
    scanf(" %d", &opcao);
    switch (opcao)
    {
    case 1:
        printf("\nDigite o assunto da Reuniao:\n");
        scanf(" %[^\n]", assunto);
        fflush(stdin);
        printf("Digite o ano que deseja agendar:\n");
        scanf(" %d", &ano);
        fflush(stdin);
        printf("Digite o mes do ano que deseja agendar:\n");
        scanf(" %d", &mes);
        fflush(stdin);
        printf("Digite o dia do mes que deseja agendar:\n");
        scanf(" %d", &dia);
        fflush(stdin);
        printf("Digite a hora que deseja agendar:\n");
        scanf(" %d", &hora);
        fflush(stdin);
        printf("Digite o minuto da hora que deseja agendar:\n");
        scanf(" %d", &minuto);
        fflush(stdin);
        struct reuniao novaReuniao = CriarReuniao(assunto, ano, mes, dia, hora, minuto);
        EscreverNoAquivo(&novaReuniao, arquivo);
        break;
    
    case 2:
        printf("Digite o ano das reunioes que deseja mostrar:\n");
        scanf(" %d", &ano);
        fflush(stdin);
        printf("Digite o mes do ano das reunioes que deseja mostrar:\n");
        scanf(" %d", &mes);
        fflush(stdin);
        printf("Digite o dia do mes das reunioes que deseja mostrar:\n");
        scanf(" %d", &dia);
        fflush(stdin);
        MostrarReunioes(LerArquivo(arquivo), ano, mes, dia);
        break;
    }
    free(ponteiro);
}

struct reuniao CriarReuniao(char assunto[], int ano, int mes, int dia, int hora, int minuto) {
    struct reuniao novaReuniao;
    strcpy(novaReuniao.assunto, assunto);
    novaReuniao.ano = ano;
    novaReuniao.mes = mes;
    novaReuniao.dia = dia;
    novaReuniao.hora = hora;
    novaReuniao.minuto = minuto;
    return novaReuniao;
}

void EscreverNoAquivo(struct reuniao *reuniao, FILE *arquivo) {
    arquivo = fopen("agenda.bin", "ab");
    fwrite(reuniao, sizeof(struct reuniao), 1, arquivo);
    fclose(arquivo);
}


struct reuniao *LerArquivo(FILE *arquivo) {
    int quantidade;
    arquivo = fopen("agenda.bin", "rb");
    fseek(arquivo, 0, SEEK_END);
    quantidade = ftell(arquivo) / sizeof(struct reuniao);
    fseek(arquivo, 0, SEEK_SET);
    struct reuniao *ponteiro = (struct reuniao *)malloc(sizeof(struct reuniao) * quantidade);
    fread(ponteiro, sizeof(struct reuniao), quantidade, arquivo);
    fclose(arquivo);
    return ponteiro;
}

void MostrarReunioes(struct reuniao *ponteiro, int ano, int mes, int dia) {
    printf("\n-----   Reunioes Agendadas em %d/%d/%d   -----\n", dia, mes, ano);
    bool temReuniao = false;
    int i;
    for(i = 0; i < _msize(ponteiro) / sizeof(struct reuniao); i++) {
        if(ponteiro[i].ano == ano && ponteiro[i].mes == mes && ponteiro[i].dia == dia) {
            temReuniao = true;
            printf("Assunto: %s\n", ponteiro[i].assunto);
            printf("Horario: %d horas e %d minutos\n\n", ponteiro[i].hora, ponteiro[i].minuto);
        }
    }
    if(!temReuniao) {
        printf("Nao existe nenhuma reuniao agendada nesta data.\n");
    }
}

/*Fa??a um programa no qual o usu??rio possa registrar os
dias e hor??rios das suas reuni??es. O programa deve ter um menu com duas op????es: 1- Registrar
uma reuni??o; 2- Mostrar reuni??es agendadas. Ao registrar uma nova reuni??o, o programa deve
perguntar a data (dia, m??s e ano), o hor??rio (hora e minuto) e o assunto da reuni??o (string com
20 caracteres) e escrever no final de um arquivo bin??rio (???agenda.bin???). Ao consultar as reuni??es
agendadas, o usu??rio deve informar o dia desejado. O programa ent??o vai abrir o arquivo e
mostrar na tela os hor??rios e os assuntos das reuni??es agendadas no dia especificado.*/