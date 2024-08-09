#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAME_RATE 60
#define ALT 60
#define LARG 60
#define LIN 10
#define COL 300
#define NUM 10
#define SOLO 0
#define VIDAS 3

//STRUCTS:
typedef struct
{
    Vector2 velocidade;
    Vector2 gravidade;
    Vector2 posicao;
    Vector2 tamanho;
    int tentativas;
    int pts;
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

//VARS
char nivel[LIN][COL];
bool fimJogo = true;
static BLOCO bloco[LIN][COL] = {0};
static JOGADOR jogador = {0};
static SCORES top_scores[5] = {0};
//FUNÇÕES:
/*void menu()
{
    //carrega textura
    static Texture2D logo = LoadTexture("logo.png");

    //pega a posição do mouse
	Vector2 mouse = GetMousePosition();

    //botão "play"
	Rectangle play = {
	    (GetScreenWidth() / 2) - MeasureText("Play", 70) / 2,
        GetScreenHeight() / 2,
        MeasureText("Play", 70),
        70 };

    //botão "scoreboard"
	Rectangle scoreBoard = {
	    (GetScreenWidth() / 2) - MeasureText("LeaderBoard", 70) / 2,
        (GetScreenHeight() / 2) + 80,
        MeasureText("LeaderBoard", 70),
        70 };

    //botão "quit"
	Rectangle quit = {
        (GetScreenWidth() / 2) - MeasureText("Quit", 70) / 2,
        (GetScreenHeight() / 2) + 160,
        MeasureText("Quit", 70),
        70 };

    //desenha o fundo azul-escuro
	DrawRectangle(
		0,
		0,
		GetScreenWidth(),
		GetScreenHeight(),
		DARKBLUE);

    //desenha o letreiro do menu
	DrawTexture(logo,
		205,
		GetScreenHeight() / 2 - 269,
		RAYWHITE);

    //muda a cor do botão "play" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, play)) {
		DrawRectangleRec(
			play,
			BLUE
		);
	}


    //muda a cor do botão "scoreBoard" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, scoreBoard))
		DrawRectangleRec(
			scoreBoard,
			BLUE
		);


    //muda a cor do botão "quit" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, quit))
		DrawRectangleRec(
			quit,
			BLUE
		);

    //escreve "Play" acima do botão correspondente
	DrawText(
		"Play",
		(GetScreenWidth() / 2) - MeasureText("Play", 70) / 2,
		GetScreenHeight() / 2,
		70,
		YELLOW
	);

	//escreve "LeaderBoard" acima do botão correspondente
	DrawText(
		"LeaderBoard",
		(GetScreenWidth() / 2) - MeasureText("LeaderBoard", 70) / 2,
		(GetScreenHeight() / 2) + 80,
		70,
		YELLOW
	);

	//escreve "Quit" acima do botão correspondente
	DrawText(
		"Quit",
		(GetScreenWidth() / 2) - MeasureText("Quit", 70) / 2,
		(GetScreenHeight() / 2) + 160,
		70,
		YELLOW
	);

}*/

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

void carrega_fase(char nivel[LIN][COL], int fase)
{
    int lin;
    int col;
    FILE *arq;
    char bloco;
    char arqfase[11] = {'n', 'i', 'v', 'e', 'l', 'x', '.', 't', 'x', 't'};

    arqfase[5] =  fase+0;

    arq = fopen(arqfase, "r");

    if(arq == NULL)
    {
        fclose(arq);
        arqfase[5] = 'x';
        arq = fopen(arqfase, "r");
    }

    for(lin=0; lin<LIN; lin++)
        for(col=0; col<COL; col++)
    {
        fscanf(arq, "%c", &bloco);
        nivel[LIN][COL] = bloco;
    }

    fclose(arq);

    return;
};

/*
void inicia_vars_jogo(char nivel[LIN][COL], int fase)
{
    int lin, col, posx, posy;

    //if(fase!=menu())
        carrega_fase(nivel, fase);

        if(fimJogo == true|| fase == menu())
        {
            jogador.posicao = (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT*7/8};
            jogador.tamanho = (Vector2){SCREEN_WIDTH/10, 20};
            jogador.tentativas = VIDAS;
            jogador.pts = 0;
        }
}*/
void desenha_fase(JOGADOR jogador, BLOCO blocos[], OBSTACULO obstaculos[])
{
    int i;
    int num_blocos = NUM;
    int num_obs = NUM;

    ClearBackground(RAYWHITE);

    //BLOCOS E OBSTACULOS
    for(i=0; i<num_blocos; i++)
    {
        DrawRectangle(blocos[i].posicao.x, blocos[i].posicao.y, LARG, ALT, DARKBLUE);
    }
    for(i=0; i<num_obs; i++)
    {
        DrawRectangle(obstaculos[i].posicao.x, obstaculos[i].posicao.y, LARG, ALT, RED);
    }

    //JOGADOR
    DrawRectangle(jogador.posicao.x, jogador.posicao.y, LARG, ALT, DARKGREEN);
};
//PROGRAMA PRINCIPAL
int main()
{
    BLOCO blocos[10];
    OBSTACULO obstaculos[10];
    JOGADOR jogador;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Inf Dash");
    SetTargetFPS(FRAME_RATE);

     //------------------------------------------
    // CARREGUE SEUS GRÁFICOS AQUI (LoadTexture)
    //-------------------------------------------
    //carrega_fase(arquivo);
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
        desenha_fase(jogador, blocos, obstaculos);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
