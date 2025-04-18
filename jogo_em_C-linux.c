#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

// Protótipos das funções
void menuPrincipal();
void menuJogoDaVelha();
void menuJokenpo();
void jogarJogoDaVelha(int modo);
void jogarJokenpo(int modo);
void limparBuffer();
void limparTela();
void pausar();

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    menuPrincipal();
    return 0;
}

// Função para limpar a tela (Linux)
void limparTela() {
    system("clear");
}

// Função para pausar a execução (Linux)
void pausar() {
    printf("Pressione Enter para continuar...");
    while(getchar() != '\n'); // Espera Enter
}

// Menu principal
void menuPrincipal() {
    int opcao;
    
    do {
        limparTela();
        printf("=== MENU PRINCIPAL ===\n\n");
        printf("1. Jogo da Velha\n");
        printf("2. Jokenpo (Pedra, Papel, Tesoura)\n");
        printf("3. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                menuJogoDaVelha();
                break;
            case 2:
                menuJokenpo();
                break;
            case 3:
                printf("\nSaindo... Obrigado por jogar!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
    } while(opcao != 3);
}

// Menu do Jogo da Velha
void menuJogoDaVelha() {
    int opcao;
    
    do {
        limparTela();
        printf("=== JOGO DA VELHA ===\n\n");
        printf("1. Jogador vs Jogador\n");
        printf("2. Jogador vs Maquina\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                jogarJogoDaVelha(1); // Modo Jogador vs Jogador
                break;
            case 2:
                jogarJogoDaVelha(2); // Modo Jogador vs Máquina
                break;
            case 3:
                return; // Volta ao menu principal
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
    } while(opcao != 3);
}

// Menu do Jokenpo
void menuJokenpo() {
    int opcao;
    
    do {
        limparTela();
        printf("=== JOKENPO (PEDRA, PAPEL, TESOURA) ===\n\n");
        printf("1. Jogador vs Jogador\n");
        printf("2. Jogador vs Maquina\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                jogarJokenpo(1); // Modo Jogador vs Jogador
                break;
            case 2:
                jogarJokenpo(2); // Modo Jogador vs Máquina
                break;
            case 3:
                return; // Volta ao menu principal
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
    } while(opcao != 3);
}

// Função para jogar Jogo da Velha
void jogarJogoDaVelha(int modo) {
    char tabuleiro[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    int jogador = 1, linha, coluna, escolha;
    char marca;
    bool jogoTerminado = false;
    bool empate = false;
    
    do {
        limparTela();
        printf("=== JOGO DA VELHA ===\n\n");
        
        // Imprime o tabuleiro
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                printf(" %c ", tabuleiro[i][j]);
                if(j < 2) printf("|");
            }
            printf("\n");
            if(i < 2) printf("-----------\n");
        }
        
        // Verifica se o jogo terminou
        // Verifica linhas
        for(int i = 0; i < 3; i++) {
            if(tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
                jogoTerminado = true;
                printf("\nJogador %d venceu!\n", (tabuleiro[i][0] == 'X') ? 1 : 2);
                break;
            }
        }
        
        // Verifica colunas
        if(!jogoTerminado) {
            for(int j = 0; j < 3; j++) {
                if(tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j]) {
                    jogoTerminado = true;
                    printf("\nJogador %d venceu!\n", (tabuleiro[0][j] == 'X') ? 1 : 2);
                    break;
                }
            }
        }
        
        // Verifica diagonais
        if(!jogoTerminado) {
            if((tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) ||
               (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])) {
                jogoTerminado = true;
                printf("\nJogador %d venceu!\n", (tabuleiro[1][1] == 'X') ? 1 : 2);
            }
        }
        
        // Verifica empate
        if(!jogoTerminado) {
            empate = true;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                        empate = false;
                        break;
                    }
                }
                if(!empate) break;
            }
            
            if(empate) {
                jogoTerminado = true;
                printf("\nEmpate!\n");
            }
        }
        
        if(jogoTerminado) {
            pausar();
            return;
        }
        
        // Lógica do jogo
        marca = (jogador == 1) ? 'X' : 'O';
        
        if(jogador == 2 && modo == 2) { // Jogada da máquina
            do {
                escolha = rand() % 9 + 1;
                linha = (escolha - 1) / 3;
                coluna = (escolha - 1) % 3;
            } while(tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O');
            
            printf("\nMaquina escolheu a posicao %d\n", escolha);
            sleep(1); // Pequena pausa para o jogador ver a jogada da máquina
        } else { // Jogada do jogador
            printf("\nJogador %d, escolha uma posicao (1-9): ", jogador);
            scanf("%d", &escolha);
            limparBuffer();
            
            if(escolha < 1 || escolha > 9) {
                printf("Posicao invalida! Tente novamente.\n");
                pausar();
                continue;
            }
            
            linha = (escolha - 1) / 3;
            coluna = (escolha - 1) % 3;
            
            if(tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O') {
                printf("Posicao ja ocupada! Tente novamente.\n");
                pausar();
                continue;
            }
        }
        
        tabuleiro[linha][coluna] = marca;
        jogador = (jogador == 1) ? 2 : 1;
        
    } while(!jogoTerminado);
}

// Função para jogar Jokenpo
void jogarJokenpo(int modo) {
    int jogador1, jogador2;
    char opcoes[3][10] = {"Pedra", "Papel", "Tesoura"};
    
    do {
        limparTela();
        printf("=== JOKENPO (PEDRA, PAPEL, TESOURA) ===\n\n");
        
        // Jogador 1 escolhe
        printf("Jogador 1, escolha:\n");
        printf("1. Pedra\n");
        printf("2. Papel\n");
        printf("3. Tesoura\n");
        printf("0. Voltar\n");
        printf("\nEscolha: ");
        scanf("%d", &jogador1);
        limparBuffer();
        
        if(jogador1 == 0) return;
        if(jogador1 < 1 || jogador1 > 3) {
            printf("Opcao invalida! Tente novamente.\n");
            pausar();
            continue;
        }
        
        // Jogador 2 escolhe (ou máquina)
        if(modo == 1) { // Jogador vs Jogador
            printf("\nJogador 2, escolha:\n");
            printf("1. Pedra\n");
            printf("2. Papel\n");
            printf("3. Tesoura\n");
            printf("\nEscolha: ");
            scanf("%d", &jogador2);
            limparBuffer();
            
            if(jogador2 < 1 || jogador2 > 3) {
                printf("Opcao invalida! Tente novamente.\n");
                pausar();
                continue;
            }
        } else { // Jogador vs Máquina
            jogador2 = rand() % 3 + 1;
            printf("\nMaquina escolheu: %s\n", opcoes[jogador2-1]);
        }
        
        // Mostra as escolhas
        printf("\nJogador 1: %s\n", opcoes[jogador1-1]);
        if(modo == 1) {
            printf("Jogador 2: %s\n", opcoes[jogador2-1]);
        }
        
        // Determina o vencedor
        if(jogador1 == jogador2) {
            printf("\nEmpate!\n");
        } else if((jogador1 == 1 && jogador2 == 3) || // Pedra > Tesoura
                  (jogador1 == 2 && jogador2 == 1) || // Papel > Pedra
                  (jogador1 == 3 && jogador2 == 2)) { // Tesoura > Papel
            printf("\nJogador 1 venceu!\n");
        } else {
            if(modo == 1) {
                printf("\nJogador 2 venceu!\n");
            } else {
                printf("\nMaquina venceu!\n");
            }
        }
        
        printf("\nJogar novamente? (1-Sim / 0-Nao): ");
        scanf("%d", &jogador1);
        limparBuffer();
        
    } while(jogador1 == 1);
}

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
