#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// QUESTÃO 1

char *em_comum(char v1[], char v2[]) {

    printf("O comprimento de v1 eh %lu\n", strlen(v1));
    printf("O comprimento de v2 eh %lu\n", strlen(v2));

    char *v3 = malloc(sizeof(char)*(strlen(v1)+ strlen(v2)));

    printf("%i\n", v3);
    int k=0;
    for (int i=0; v1[i]!='\0'; i++) {
        for (int j=0; v2[j]!='\0'; j++) {
            if (v1[i] == v2[j]) {
                //*v3 = v1[i];
                //v3++;
                v3[k] = v1[i];
                k++;
            }
        }
    }
    printf("%i\n", v3);

    //*v3 = '\0'; // muda o ponteiro
    v3[k] = '\0'; // muda k posições depois de onde marca o ponteiro (mas este continua a apontar o início da string!)

    return v3;

}

// QUESTÃO 4

bool palindromo() {
    FILE* palavra = fopen("palavra.txt", "r+t");
    if (palavra==NULL) {
        printf("arquivo nao encontrado");
        return false;
    }

    char p[256];
    fscanf(palavra, "%s", &p);
    int j = strlen(p)-1;

    for (int i=0; i<j; i++) {
        if (p[i] != p[j]) {
            fclose(palavra);
            return false;
        }
        j--;
    }
    
    fclose(palavra);
    return true;
}


int main (void) {


    // QUESTÃO 1

    char v1[] = "abcmdefg";
    char v2[] = "gfedcbak";
    
    //printf("%i\n", em_comum(v1, v2));

    char *v3 = em_comum(v1, v2);

    
    int i=0;
    while(v3[i] /* *v3 */ != '\0') {
        //printf("%c", *v3); 
        //v3++; // muda o ponteiro
        printf("%c", v3[i]); // pega o valor i posições a frente do ponteiro
        i++;
    }
    printf("\n");
    

    // QUESTÃO 2

    float numeros[] = {3.14, 5.16, 99.0, 86.9, 50.0, 34.3, 25.3, 27.5, -1.3};
    
    i = 0;
    int intervalo1 = 0;
    int intervalo2 = 0;
    int intervalo3 = 0;
    int intervalo4 = 0;
    
    while (0.0 <= numeros[i] && numeros[i] <= 100.0) {
        
        if (numeros[i] <= 25.0) {
            intervalo1++;
        } else if (26.0 <= numeros[i] && numeros[i] <= 50.0) {
            intervalo2++;
        } else if (51.0 <= numeros[i] && numeros[i] <= 75.0) {
            intervalo3++;
        } else if (76.0 <= numeros[i]) {
            intervalo4++;
        }
        i++;
    }
    
    printf("[0-25]: %i\n[26-50]: %i\n[51-75]: %i\n[76-100]: %i\n", intervalo1, intervalo2, intervalo3, intervalo4);


    // QUESTÃO 3

    FILE *venda = fopen("vendas.txt", "r+t");
    if (venda == NULL) {
        printf("nda");
        return 0;
    }

    int idproduto[10];
    int qtdprod[10];
    float precos[10];  
    i=0;

    while (!feof(venda))
    {
        fscanf(venda ,"%d %d %f", &idproduto[i], &qtdprod[i], &precos[i]);
        // printf("%d %d %f\n", idproduto[i], qtdprod[i], precos[i]);
        i++;
    }

    float faturamento = 0;
    for (int j=0; j<10; j++) {
        faturamento += qtdprod[j]*precos[j];
    }
    printf("%.2f\n", faturamento);

    fclose(venda);


    // QUESTÃO 4

    if (palindromo()) {
        printf("sim\n");
    } else {
        printf("nao\n");
    }


    return 0;
}