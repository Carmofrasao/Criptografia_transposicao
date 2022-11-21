#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <locale.h>

int main(int argc, char * argv[]){
    setlocale(LC_ALL, "Portuguese_Brasil");
    
    if(argc < 2){
        printf("Para descriptografar seu texto:\n./descriptografa -e <nome do arquivo> -s <arquivo de saida>\n");
        return 0;
    }

    char * entrada = argv[2];
    char * saida = argv[4];

    struct stat sb;
    if (stat(entrada, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    FILE * texto_cifrado = fopen(entrada, "r");
    if(!texto_cifrado){
        perror("Erro na abertura de arquivo");
        exit(-1);
    }

    FILE * texto_decifrado = fopen(saida, "w");
    if(!texto_decifrado){
        perror("Erro na abertura de arquivo");
        exit(-1);
    }

    char * texto = calloc(1, sb.st_size);
    if(!texto){
        perror("Erro na alocação de memoria");
        exit(-1);
    }
    char * result = calloc(1/6, sb.st_size);
    if (!result){
        perror("Erro na alocação de memoria");
        exit(-1);
    }
    
    int i = 0;
    char c;
    // Lendo o arquivo com o texto cifrado
    c = fgetc(texto_cifrado);
    while (!feof(texto_cifrado)){
        texto[i] = c;
        c = fgetc(texto_cifrado);
        i++;
    };

    // Descriptografando
    for (int l = 0; l < i-3; l+=3){
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

    fprintf(texto_decifrado, "%s\n", result);
    
    fclose(texto_cifrado);
    fclose(texto_decifrado);
    free(texto);
    free(result);

    return 0;
}