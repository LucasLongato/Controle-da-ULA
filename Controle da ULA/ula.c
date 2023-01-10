#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO 124

struct saida_controle_ULA_t {
    int bits[3];
};



struct saida_controle_ULA_t controle_ULA (int opcode[6], int funct[6]) {
    // TODO -> Trabalho consiste em implementar essa funÃ§Ã£o
    // O retorno devem ser os bits de controle da ULA de acordo com os campos opcode e funct

    // ***********************************
    // ImplementaÃ§Ã£o incorreta de exemplo:
    // ***********************************
    struct saida_controle_ULA_t saida;
    saida.bits[2] = 0;
    saida.bits[1] = 0;
    saida.bits[0] = 0;
    
     //opcode
    //verifica se é R
    if(opcode[0] == 0 && opcode[1] == 0 && opcode[2] == 0 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 0){
        //verifica se é add
        if(funct[0] == 0 && funct[1] == 0 && funct[2] == 0 && funct[3] == 0 && funct[4] == 0 && funct[5] == 1){
            saida.bits[2] = 0;
            saida.bits[1] = 1;
            saida.bits[0] = 0;
        }
        //verifica se é sub
        if(funct[0] == 0 && funct[1] == 1 && funct[2] == 0 && funct[3] == 0 && funct[4] == 0 && funct[5] == 1){
            saida.bits[2] = 1;
            saida.bits[1] = 1;
            saida.bits[0] = 0;
        }
        //verifica se é and
        if(funct[0] == 0 && funct[1] == 0 && funct[2] == 1 && funct[3] == 0 && funct[4] == 0 && funct[5] == 1){
            saida.bits[2] = 0;
            saida.bits[1] = 0;
            saida.bits[0] = 0;
        }
        //verifica se é or
        if(funct[0] == 1 && funct[1] == 0 && funct[2] == 1 && funct[3] == 0 && funct[4] == 0 && funct[5] == 1){
            saida.bits[2] = 0;
            saida.bits[1] = 0;
            saida.bits[0] = 1;
        }
        //verifica se é slt
        if(funct[0] == 0 && funct[1] == 1 && funct[2] == 0 && funct[3] == 1 && funct[4] == 0 && funct[5] == 1){
            saida.bits[2] = 1;
            saida.bits[1] = 1;
            saida.bits[0] = 1;
        }
    //verifica se é lw
    }else if(opcode[0] == 1 && opcode[1] == 1 && opcode[2] == 0 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 1){
        saida.bits[2] = 0;
        saida.bits[1] = 1;
        saida.bits[0] = 0;
    //verifica se é sw
    }else if(opcode[0] == 1 && opcode[1] == 1 && opcode[2] == 0 && opcode[3] == 1 && opcode[4] == 0 && opcode[5] == 1){
        saida.bits[2] = 0;
        saida.bits[1] = 1;
        saida.bits[0] = 0;
    //verifica se é beq
    }else if(opcode[0] == 0 && opcode[1] == 0 && opcode[2] == 1 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 0){
        saida.bits[2] = 0;
        saida.bits[1] = 1;
        saida.bits[0] = 1;
    }
    // verifica se e j
    else if(opcode[0] == 0 && opcode[1] == 1 && opcode[2] == 0 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 0){
        saida.bits[2] = 0;
        saida.bits[1] = 0;
        saida.bits[0] = 0;
    }

    return saida;
    
}



void processar_linha (char *linha, int opcode[6], int funct[6]) {
    char opcode_char[6];
    char funct_char[6];
    sscanf(linha, "%c%c%c%c%c%c %c%c%c%c%c%c"
                , &opcode_char[5]
                , &opcode_char[4]
                , &opcode_char[3]
                , &opcode_char[2]
                , &opcode_char[1]
                , &opcode_char[0]
                
                , &funct_char[5]
                , &funct_char[4]
                , &funct_char[3]
                , &funct_char[2]
                , &funct_char[1]
                , &funct_char[0]);

    opcode[5] = opcode_char[5] - 48;
    opcode[4] = opcode_char[4] - 48;
    opcode[3] = opcode_char[3] - 48;
    opcode[2] = opcode_char[2] - 48;
    opcode[1] = opcode_char[1] - 48;
    opcode[0] = opcode_char[0] - 48;

    funct[5] = funct_char[5] - 48;
    funct[4] = funct_char[4] - 48;
    funct[3] = funct_char[3] - 48;
    funct[2] = funct_char[2] - 48;
    funct[1] = funct_char[1] - 48;
    funct[0] = funct_char[0] - 48;

    return;
}


int main(int argc, char **argv) {
    // ***************************************************************************
    // VerificaÃ§Ãµes
    // ***************************************************************************
    if (argc != 2) {
        printf("Uso correto: <programa> <entrada>\n");
        exit(1);
    }
    FILE *entrada = fopen(argv[1], "r");
    if (entrada == 0x0) {
        printf("Falha de leitura! O arquivo %s existe?\n", argv[1]);
        exit(1);
    }

    // ***************************************************************************
    // Leitura e processamento
    // ***************************************************************************
    char linha[TAMANHO_MAXIMO];
    int opcode[6];
    int funct[6];

    /* Primeira instruÃ§Ã£o */
    fgets(linha, TAMANHO_MAXIMO, entrada);
    while (!feof(entrada))
    {
        /* ObtÃ©m campos de controle */
        processar_linha(linha, opcode, funct);

        /* ObtÃ©m bits de controle da ULA */
        struct saida_controle_ULA_t tmp = controle_ULA(opcode, funct);
        printf("%d%d%d\n", tmp.bits[2], tmp.bits[1], tmp.bits[0]);

        /* PrÃ³xima instruÃ§Ã£o */
        linha[0] = '\0';
        fgets(linha, TAMANHO_MAXIMO, entrada);
        
    }

    /*********** Ãšltimo processamento ***********/
    if (strlen (linha) > 12) {
        /* ObtÃ©m campos de controle */
        processar_linha(linha, opcode, funct);

        /* ObtÃ©m bits de controle da ULA */
        struct saida_controle_ULA_t tmp = controle_ULA(opcode, funct);
        printf("%d%d%d\n", tmp.bits[2], tmp.bits[1], tmp.bits[0]);

    }


    // ***************************************************************************
    // Encerramento
    // ***************************************************************************
    return 0;
}