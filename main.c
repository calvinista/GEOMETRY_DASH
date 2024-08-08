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
void drawMenu() {

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
