// Arthur Marques 12321BCC036, João Vitor Aguiar 12321BCC009, Otavio Senne 12321BCC027


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_LINHAS 585881

struct cep{
    char cep[10];
    char sigla[3];
    char cidade[50];
    char endereco[100];
};

void shellsort(struct cep *vetor, int n){
    int i, j, h = 1;
    struct cep aux;

    do{
        h = h*3 +1;
    } while (h<n);

    do{
        h = h/3;
        for (i = h; i<n; i++){
            aux = vetor[i];
            j = i;
            while(strcmp(vetor[j-h].cep,aux.cep)>0){
                vetor[j] = vetor[j-h];
                j-=h;
                if(j<h) break;
            }
            vetor[j] = aux;
        }
    }while(h!=1);
}


void buscaBinaria (struct cep *vetor, int esquerda, int direita, char *chave){
     if (esquerda > direita) {
        printf("O CEP informado nao foi encontrado. Tente outro: ");

        char novoCEP[10];
        scanf("%s", novoCEP);
        buscaBinaria (vetor, 0, N_LINHAS - 1, novoCEP);
        return;
    }

    int meio = (esquerda + direita)/2;

    if (strcmp(vetor[meio].cep, chave)==0){
        printf("\nCEP: %s\n", vetor[meio].cep);
        printf("Cidade: %s - %s\n", vetor[meio].cidade, vetor[meio].sigla);
        printf("Endereco: %s\n", vetor[meio].endereco);
        return;
    }
    else if(strcmp(vetor[meio].cep, chave)>0){
        buscaBinaria(vetor, esquerda, meio - 1, chave);
    }
    else{
        buscaBinaria(vetor, meio + 1, direita, chave);
    }
}




int main()
{
    int i = 0;
    FILE *arquivo = fopen("cep.txt", "r");
    if (arquivo == NULL){
        printf("error");
    }


    struct cep *vetor = (struct cep*) malloc(sizeof(struct cep)*N_LINHAS);
    if (vetor == NULL){
        printf("Memória insuficiente");
    }


    while(fscanf(arquivo, "%[^;]; %[^;]; %[^;]; %[^\n]\n",
                  vetor[i].cep, vetor[i].sigla, vetor[i].cidade, vetor[i].endereco) != EOF){
        i++;
    }

    fclose(arquivo);

    shellsort(vetor, N_LINHAS);

    printf("Indique o CEP a ser buscado (EX: 12345-78): ");
    char CEP[10];
    scanf("%s", CEP);
    buscaBinaria(vetor, 0, N_LINHAS - 1, CEP);

    free(vetor);

}