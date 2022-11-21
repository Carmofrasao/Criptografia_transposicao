#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct stat sb;

int main(int argc, char * argv[]){

    if(argc < 2){
        printf("Para criptografar seu texto:\n./criptografa -e <nome do arquivo> -s <arquivo de saida>\n");
        return 0;
    }

    char * entrada = argv[2];
    char * saida = argv[4];

    if (stat(entrada, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    FILE * texto_claro = fopen(entrada, "r");
    if(!texto_claro){
        perror("Erro na abertura de arquivo");
        exit(-1);
    }

    FILE * texto_cifrado = fopen(saida, "w");
    if(!texto_cifrado){
        perror("Erro na abertura de arquivo");
        exit(-1);
    }

    char * texto = calloc(1, sb.st_size);
    if(!texto){
        perror("Erro na alocação de memoria");
        exit(-1);
    }
    char * result = calloc(1, sb.st_size);
    if (!result){
        perror("Erro na alocação de memoria");
        exit(-1);
    }
    
    int i = 0;
    char c;
    // Lendo o arquivo com o texto claro
    c = fgetc(texto_claro);
    while (!feof(texto_claro)){
        texto[i] = c;
        c = fgetc(texto_claro);
        i++;
    };

    // Criptografando
    for (int l = 0; l < i; l+=3){
        if(texto[l] < 126 && texto[l] >= 33){
            result[l] = texto[l+2];
            result[l+2] = texto[l];
        } else {
            result[l] = texto[l];
            result[l+2] = texto[l+2];
        } 
    }

    for (int l = 1; l < i; l+=3){
        result[l] = texto[l];
    }

    fprintf(texto_cifrado, "%s\n", result);

    fclose(texto_claro);
    fclose(texto_cifrado);
    free(texto);
    free(result);

    return 0;
}