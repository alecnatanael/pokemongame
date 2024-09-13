#include <stdio.h>
#include <stdlib.h>
#include "pokemon.h"
#include <stdbool.h>


int main(void) {

    bool fim_jogo = false; 
    bool fim_luta = false; 
    bool vez = true; // true = vez do jogador 1, false = vez do jogador 2
    int opcao1 = 1; // contador de qual pokemon o jogador 1 vai usar
    int opcao2 = 1; // contador de qual pokemon o jogador 2 vai usar
    int vencedor = 0;



    // Abrir o arquivo de entrada:
    FILE* entrada=fopen("entrada.txt", "r+t");
    if (entrada==NULL){
        printf("Erro ao tentar abrir o arquivo de entrada!\n");
        exit(1);
    }

    // Ler quantos pokemons cada jogador tem:
    ler_quantidades(entrada);

    // Declarar estruturas para armazenar o pokemon de cada jogador (p1 e p2) com seus atributos a cada rodada; 
    struct pokemon* p1 = malloc(sizeof(struct pokemon));
    struct pokemon* p2 = malloc(sizeof(struct pokemon));


    // Selecionar os primeiros pokemons para cada jogador
    pokemon_player1(entrada, p1, opcao1);
    pokemon_player2(entrada, p2, opcao2);
    

    // Ação do Jogo
    while (!fim_jogo) {   
        
        // printf("%s %.2f\n", p1->nome, p1->vida);
        // printf("%s %.2f\n", p2->nome, p2->vida);

        fim_luta = false; // reseta o indicator de fim de batalha

        // Ação de cada batalha
        while (!fim_luta)
        {

            if (vez){ // Na vez do jogador 1
                ataque(p1, p2); // p2 sofre o ataque
                vez = false; // troca a vez
            } else { // Na vez do jogador 2
                ataque(p2, p1); // p1 sofre o a ataque
                vez = true; // troca a vez
            }

            // printf("%s %.2f\n", p1->nome, p1->vida);
            // printf("%s %.2f\n", p2->nome, p2->vida);
            
            if (p1->vida <= 0) { // Se p1 é derrotado

                printf("%s venceu %s\n", p2->nome, p1->nome);
                //vez = false;
                opcao1++; 
                fim_luta = true;

                if (qtd_player1 - opcao1 < 0) { // Se acabam as opções de pokemon para o jogador 1
                    vencedor = 2;
                    fim_jogo = true; // fim de jogo
                } else { // Se ainda há opção de pokemón
                    pokemon_player1(entrada, p1, opcao1); // trocar pokemon do jogador 1
                }

            } else if (p2->vida <= 0) { // Se p2 é derrotado

                printf("%s venceu %s\n", p1->nome, p2->nome);
                //vez = true;
                opcao2++;
                fim_luta = true;

                if (qtd_player2 - opcao2 < 0) { // Se acabam as opções de pokemon para o jogador 2
                    vencedor = 1;
                    fim_jogo = true; // fim de jogo
                } else { // Se ainda há opção de pokemón
                    pokemon_player2(entrada, p2, opcao2); // trocar pokemon do jogador 2
                }

            }

        }   
    }

    // Verificar e revelar vencedor
    if (vencedor == 1) {
        printf("Jogador 1 venceu!\n");
        printf("Pokemons sobreviventes:\n");
        imprime_restantes(entrada, vencedor, opcao1);
        printf("Pokemons derrotados:\n");
        imprime_derrotados(entrada, vencedor, opcao1);
    } else if (vencedor == 2) {
        printf("Jogador 2 venceu!\n");
        printf("Pokemons sobreviventes:\n");
        imprime_restantes(entrada, vencedor, opcao2);
        printf("Pokemons derrotados:\n");
        imprime_derrotados(entrada, vencedor, opcao2);
    }

    
    
    free(p1);
    free(p2);
    fclose(entrada);
    return 0;
}