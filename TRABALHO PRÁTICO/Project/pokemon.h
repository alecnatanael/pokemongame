#include <stdio.h>
#include <math.h>
#include <string.h>

/* VARIÁVEIS GLOBAIS */

// Quantidade de pokemons ativos para cada jogador:
const int qtd_player1;
const int qtd_player2;


// Estrutura para armazenar todos os atributos de um pokemon
struct pokemon
{
    char nome[30];
    float ataque;
    float defesa;
    float vida;
    char tipo[10];
};



/* FUNÇÕES */


// Função para ler as quantidades de pokemons de cada jogador encontradas na primeira linha do arquivo
void ler_quantidades(FILE * entrada) {

    fscanf(entrada, "%d %d", &qtd_player1, &qtd_player2);

}


// Função que retorna a estrutura com todos os atributos do pokemon 1
struct pokemon pokemon_player1(FILE * entrada, struct pokemon player, int opcao) {

    // contadores
    int linha = 0;
    char ch;

    // reseta o ponteiro para o início do arquivo:
    rewind(entrada);

    // Técnica para pular linhas até a linha onde estão os atributos do pokemon desejado:
    while (linha != opcao){
        while((ch = fgetc(entrada)) != EOF){
            if(ch=='\n') break;
        }
        ++linha;
    }
    
   // Ler os atributos do pokemon e copia-os para a estrutura struct pokemon p1:
   fscanf(entrada, "%s %f %f %f %s", &player.nome, &player.ataque, &player.defesa, &player.vida, &player.tipo);

    
    return player;
}


// Função que retorna a estrutura com todos os atributos do pokemon 2
struct pokemon pokemon_player2(FILE * entrada, struct pokemon player, int opcao) {

    // contadores
    int linha = 0;
    char ch;

    // reseta o ponteiro para o início do arquivo:
    rewind(entrada);

    // Técnica para pular linhas até a linha onde estão os atributos do pokemon desejado:
    while (linha != opcao+qtd_player1){
        while((ch = fgetc(entrada)) != EOF){
            if(ch=='\n') break;
        }
        ++linha;
    }

    // Ler os atributos do pokemon e copia-os para a estrutura struct pokemon p2:
    fscanf(entrada, "%s %f %f %f %s", &player.nome, &player.ataque, &player.defesa, &player.vida, &player.tipo);


    return player;
}


// Função para gerenciar a dinâmica dos tipos de pokemon
int compara_tipos(struct pokemon atacante, struct pokemon defensor) {
    int op = 0;
    if (strcmp(atacante.tipo, "eletrico")==0) {
        if (strcmp(defensor.tipo, "agua")==0) {
            op = 1;
        } else if (strcmp(defensor.tipo, "pedra")==0) {
            op = -1;
        }

    } else if (strcmp(atacante.tipo, "agua")==0) {
        if (strcmp(defensor.tipo, "fogo")==0) {
            op = 1;
        } else if (strcmp(defensor.tipo, "eletrico")==0) {
            op = -1;
        }

    } else if (strcmp(atacante.tipo, "fogo")==0) {
        if (strcmp(defensor.tipo, "gelo")==0) {
            op = 1;
        } else if (strcmp(defensor.tipo, "agua")==0) {
            op = -1;
        }

    } else if (strcmp(atacante.tipo, "gelo")==0) {
        if (strcmp(defensor.tipo, "pedra")==0) {
            op = 1;
        } else if (strcmp(defensor.tipo, "fogo")==0) {
            op = -1;
        }

    } else if (strcmp(atacante.tipo, "pedra")==0) {
        if (strcmp(defensor.tipo, "eletrico")==0) {
            op = 1;
        } else if (strcmp(defensor.tipo, "gelo")==0) {
            op = -1;
        }

    }

    return op;
}


// Função que gerencia o ataque de um pokemon a outro 
struct pokemon ataque(struct pokemon atacante, struct pokemon defensor) {


    if (compara_tipos(atacante, defensor) == 0) {
        if (atacante.ataque > defensor.defesa /*+1*/) {
            defensor.vida -= atacante.ataque - defensor.defesa;
        } else {
            defensor.vida -= 1.0;
        }

    } else if (compara_tipos(atacante, defensor) == 1) {
        atacante.ataque += atacante.ataque*0.2;
        if (atacante.ataque > defensor.defesa /*+1*/) {
            defensor.vida -= (atacante.ataque - defensor.defesa);
        } else {
            defensor.vida -= 1.0;
        }

    } else if (compara_tipos(atacante, defensor) == -1) {
        atacante.ataque -= atacante.ataque*0.2;
        if (atacante.ataque > defensor.defesa /*+1*/) {
            defensor.vida -= (atacante.ataque - defensor.defesa);
        } else {
            defensor.vida -= 1.0;
        }

    }

    return defensor;
}

// Função para imprimir na tela o nome dos pokémons sobreviventes
void imprime_restantes(FILE * entrada, int vencedor, int opcao) {

    rewind(entrada); // reinicia a leitura do arquivo

    int linha = 0;
    char ch;
    char nome[30];

    if (vencedor == 1) {

        while (qtd_player1-opcao >= 0){ // Pula o leitor até a linha onde está o nome a ser lido
            while (linha != opcao){
                while((ch = fgetc(entrada)) != EOF) {
                    if(ch=='\n') break;
                }
                ++linha;
            }
            opcao += 1; // Atualiza para o próximo nome
            fscanf(entrada, "%s", &nome); // lê o nome
            printf("%s\n", nome);
        }          

    } else if (vencedor == 2) {

        while (qtd_player2-opcao >= 0){
            while (linha != opcao+qtd_player1) {
                while((ch = fgetc(entrada)) != EOF){
                    if(ch=='\n') break;
                }
                ++linha;
            }
            
            fscanf(entrada, "%s", &nome);
            printf("%s\n", nome);
            opcao += 1;
        }

    }
}

// Função para imprimir na tela, o nome de todos os pokémons derrotados durante a partida
void imprime_derrotados(FILE * entrada, int vencedor, int opcao) {
    
    rewind(entrada); // reinicia a leitura do arquivo

    int linha = 0;
    char ch;
    char nome[30];
    int c = 1;

    if (vencedor == 2) {
        // Se o jogador 2 vence, todos os pokemons da lista antes do selecionado estão derrotados
        while (qtd_player1+opcao > c){ 
            while (linha != c){ // Pula o leitor até a linha onde está o nome a ser lido
                while((ch = fgetc(entrada)) != EOF) {
                    if(ch=='\n') break;
                }
                ++linha;
            }
    
            fscanf(entrada, "%s", &nome); // Lê o nome e imprime logo em seguida
            printf("%s\n", nome);
            c++;
        }

    } else if (vencedor == 1) {
        // Caso o jogador 1 vença, é preciso ler os pokemons do jogador 2 e os pokemons do jogador 1 anteriores ao selecionado
        
        // Pokémons do jogador 1:
        while (c < opcao) {
            while (linha != c) {
                while((ch = fgetc(entrada)) != EOF){
                    if(ch=='\n') break;
                }
                ++linha;
            }
            fscanf(entrada, "%s", &nome);
            printf("%s\n", nome);
            c++;
        }    
        
        c = 1;

        // Pokémons do Jogador 2:
        while (qtd_player2 >= c) {
            while (linha != c+qtd_player1) {
                while((ch = fgetc(entrada)) != EOF){
                    if(ch=='\n') break;
                }
                ++linha;
            }
            c++;
            fscanf(entrada, "%s", &nome);
            printf("%s\n", nome);
        }

    }

}