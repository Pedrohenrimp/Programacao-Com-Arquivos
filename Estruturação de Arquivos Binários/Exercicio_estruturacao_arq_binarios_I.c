#include <stdio.h>
#include <stdbool.h>

struct reuniao {
    int id;
    int dia,mes,ano; // posicoes 0, 1 e 2,respectivamente, do vetor de modificacoes.
    int hora,minuto; // posicoes 3 e 4, respectivamente, do vetor de motificacoes.
    int qtdPessoas; // posicao 5 do vetor de modificacoes.
};

void GerarArquivoCorrigido(FILE *arquivoTexto, FILE *arquivoOriginal, FILE *arquivoCorrigido, char *campo);
void IncluirReuniao(struct reuniao *reuniao, FILE *arquivoTexto, FILE *arquivoCorrigido);
struct reuniao *ModificarReuniao(struct reuniao *reuniao, FILE *arquivoTexto, char *campo);

int main(void) {
    FILE *arqTexto, *arqOriginal, *arqCorrigido;
    char nomeArqTexto[] = "correcoes.txt";
    char nomeArqOriginal[] = "original.bin";
    char nomeArqCorrigido[] = "corrigido.bin";

    char campo[20] = "";

    arqTexto = fopen(nomeArqTexto, "r");
    arqOriginal = fopen(nomeArqOriginal, "rb");
    arqCorrigido = fopen(nomeArqCorrigido, "wb");

    GerarArquivoCorrigido(arqTexto, arqOriginal, arqCorrigido, campo);

    fclose(arqTexto);
    fclose(arqOriginal);
    fclose(arqCorrigido);
}

void GerarArquivoCorrigido(FILE *arquivoTexto, FILE *arquivoOriginal, FILE *arquivoCorrigido, char *campo) {
    if(arquivoTexto!= NULL) {
        struct reuniao *reuniao = (struct reuniao *)malloc(sizeof(struct reuniao));
        struct reuniao *reuniaoAuxiliar = (struct reuniao *)malloc(sizeof(struct reuniao));
        fread(reuniaoAuxiliar, sizeof(struct reuniao), 1, arquivoOriginal);
        char operacao;
        int id;
        bool modificar = false;
        while (!feof(arquivoOriginal)) {
            fscanf(arquivoTexto, "%d %c", &id, &operacao);
            if(!feof(arquivoTexto)) {
                if(modificar && operacao != 'M') {
                    fwrite(reuniao, sizeof(struct reuniao), 1, arquivoCorrigido);
                    fread(reuniaoAuxiliar, sizeof(struct reuniao), 1, arquivoOriginal);
                    modificar = false;
                    reuniao->id = id;
                    
                }
                if(!modificar) {
                    while(reuniaoAuxiliar->id < id) {
                        fwrite(reuniaoAuxiliar, sizeof(struct reuniao), 1, arquivoCorrigido);
                        fread(reuniaoAuxiliar, sizeof(struct reuniao), 1, arquivoOriginal);
                        if(feof(arquivoOriginal)) {
                            break;
                        }
                    }
                }
                if(operacao == 'I') {
                    reuniao->id = id;
                    if(reuniaoAuxiliar->id == reuniao->id) {
                        printf("\nA reuniao de id %d ja existe! Nao foi possivel incluir.\n", reuniao->id);
                        fscanf(arquivoTexto, "%d %d %d %d %d %d", &reuniao->dia, &reuniao->mes, &reuniao->ano, &reuniao->hora, &reuniao->minuto, &reuniao->qtdPessoas);
                    }
                    else {
                        IncluirReuniao(reuniao, arquivoTexto, arquivoCorrigido);
                    }
                }
                else if(operacao == 'M') {
                    reuniao->id = id;
                    if(reuniaoAuxiliar->id == reuniao->id) {
                        reuniao = ModificarReuniao(reuniao, arquivoTexto, campo);
                        modificar = true;
                    }
                    else {
                        reuniao = ModificarReuniao(reuniao, arquivoTexto, campo);
                        printf("\nA reuniao de id %d nao existe! Nao foi possivel modificar.\n", reuniao->id);
                    }
                }
                else if(operacao == 'E') {
                    reuniao->id = id;
                    if(reuniaoAuxiliar->id > reuniao->id) {
                        printf("\nA reuniao de id %d nao existe! Nao foi possivel excluir.\n", reuniao->id);
                    }
                    else {
                        fread(reuniaoAuxiliar, sizeof(struct reuniao), 1, arquivoOriginal);
                    }
                }   
            }
            else {
                fwrite(reuniaoAuxiliar, sizeof(struct reuniao), 1, arquivoCorrigido);
                fread(reuniaoAuxiliar, sizeof(struct reuniao), 1, arquivoOriginal);
            }
        }
        free(reuniao);
        free(reuniaoAuxiliar);
    }
}

void IncluirReuniao(struct reuniao *reuniao, FILE *arquivoTexto, FILE *arquivoCorrigido) {
    fscanf(arquivoTexto, "%d %d %d %d %d %d", &reuniao->dia, &reuniao->mes, &reuniao->ano, &reuniao->hora, &reuniao->minuto, &reuniao->qtdPessoas);
    fwrite(reuniao, sizeof(struct reuniao), 1, arquivoCorrigido);
}

struct reuniao *ModificarReuniao(struct reuniao *reuniao, FILE *arquivoTexto, char *campo) {
    fscanf(arquivoTexto, "%s", campo);
    if(strcmp(campo, "HORA") == 0) {
        fscanf(arquivoTexto, "%d", &reuniao->hora);
    }
    else if(strcmp(campo, "MINUTO") == 0) {
        fscanf(arquivoTexto, "%d", &reuniao->minuto);
    }
    else if(strcmp(campo, "DIA") == 0) {
        fscanf(arquivoTexto, "%d", &reuniao->dia);
    }
    else if(strcmp(campo, "MES") == 0) {
        fscanf(arquivoTexto, "%d", &reuniao->mes);
    }
    else if(strcmp(campo, "ANO") == 0) {
        fscanf(arquivoTexto, "%d", &reuniao->ano);
    }
    else if(strcmp(campo, "PESSOAS") == 0) {
        fscanf(arquivoTexto, "%d", &reuniao->qtdPessoas);
    }
    return reuniao;
}