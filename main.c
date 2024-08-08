#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAME_RATE 60
#define ALT 60
#define LARG 60
#define LIN 10
#define COL 300
#define NUM_BLOCOS 10
#define NUM_OBS 10
#define SOLO 0
char nivel[LIN][COL];
//STRUCTS:
typedef struct
{
    Vector2 velocidade;
    Vector2 gravidade;
    Vector2 posicao;
    int tentativas;
}JOGADOR;

typedef struct
{
    Vector2 posicao;
}BLOCO;

typedef struct
{
    Vector2 posicao;
}OBSTACULO;

typedef struct
{
    char nome[20];
    int pontos;
}SCORES;
//FUNÇÕES:
void menu()
{
    ClearBackground(RAYWHITE);
    DrawText("Inf Dash", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 100, 20, BLACK);
    DrawText("1. Jogar", SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 50, 20, DARKGRAY);
    DrawText("2. LeaderBoard", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, 20, DARKGRAY);
    DrawText("3. Sair", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 50, 20, DARKGRAY);
}

void atualiza_jogador(JOGADOR *jogador)
{
    jogador->velocidade.x = 9.0f;
    jogador->posicao.x += jogador->velocidade.x;

    //GRAVIDADE
    jogador->velocidade.y += 1.8f;

    if(IsKeyPressed(KEY_SPACE) && jogador->posicao.y == SOLO)
    {
        jogador -> velocidade.y = -25;
    }

    jogador->posicao.y += jogador->velocidade.y;

};

void carrega_fase(char arq[])
{
    FILE *arquivo;
    int lin;
    int col;


    if((arq = fopen(arq, "r"))==NULL)
    {
        return 0;
    }


    for(lin=0; lin<LIN; lin++)
    {
        for(col=0; col<COL; col++)
        {
            nivel[lin][col] = fgetc(arq);
        }
        fgetc(arq);
    }

    fclose(arq);
};

void desenha_fase(JOGADOR jogador, BLOCO blocos[], OBSTACULO obstaculos[])
{
    int i;
    int num_blocos = NUM_BLOCOS;
    int num_obs = NUM_OBS;

    ClearBackground(RAYWHITE);

    for(i=0; i<num_blocos; i++)
    {
        DrawRectangle(blocos[i].posicao.x, blocos[i].posicao.y, LARG, ALT, DARKBLUE);
    }
    for(i=0; i<num_obs; i++)
    {
        DrawRectangle(obstaculos[i].posicao.x, obstaculos[i].posicao.y, LARG, ALT, RED);
    }

    DrawRectangle(jogador.posicao.x, jogador.posicao.y, LARG, ALT, DARKGREEN);
};
//PROGRAMA PRINCIPAL
int main()
{
    char arquivo[100];
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Inf Dash");
    SetTargetFPS(FRAME_RATE);

     //------------------------------------------
    // CARREGUE SEUS GRÁFICOS AQUI (LoadTexture)
    //-------------------------------------------
    carrega_fase(arquivo);
    while (!WindowShouldClose())
    {

        //-----------------------------
        // ATUALIZE SUAS VARIÁVEIS AQUI
        //-----------------------------
        atualiza_jogador(&jogador);//AINDA CORRIGINDO

        BeginDrawing();
        ClearBackground(RAYWHITE);
        //-----------------------------
        // DESENHE SEU JOGO AQUI
        //-----------------------------
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
