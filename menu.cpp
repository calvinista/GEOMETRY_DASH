#include "raylib.h"

void drawMenu();

const int screenWidth = 1200;
const int screenHeight = 900;

int main(void) {

    InitWindow(screenWidth, screenHeight, "Menu");
    SetTargetFPS(60);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(RAYWHITE);

		drawMenu();

		EndDrawing();
	}
}

void drawMenu() {

    //carrega textura
    static Texture2D logo = LoadTexture("logo.png");

    //pega a posi��o do mouse
	Vector2 mouse = GetMousePosition();

    //bot�o "play"
	Rectangle play = {
	    (GetScreenWidth() / 2) - MeasureText("Play", 70) / 2,
        GetScreenHeight() / 2,
        MeasureText("Play", 70),
        70 };

    //bot�o "scoreboard"
	Rectangle scoreBoard = {
	    (GetScreenWidth() / 2) - MeasureText("LeaderBoard", 70) / 2,
        (GetScreenHeight() / 2) + 80,
        MeasureText("LeaderBoard", 70),
        70 };

    //bot�o "quit"
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

    //muda a cor do bot�o "play" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, play)) {
		DrawRectangleRec(
			play,
			BLUE
		);
	}


    //muda a cor do bot�o "scoreBoard" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, scoreBoard))
		DrawRectangleRec(
			scoreBoard,
			BLUE
		);


    //muda a cor do bot�o "quit" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, quit))
		DrawRectangleRec(
			quit,
			BLUE
		);

    //escreve "Play" acima do bot�o correspondente
	DrawText(
		"Play",
		(GetScreenWidth() / 2) - MeasureText("Play", 70) / 2,
		GetScreenHeight() / 2,
		70,
		YELLOW
	);

	//escreve "LeaderBoard" acima do bot�o correspondente
	DrawText(
		"LeaderBoard",
		(GetScreenWidth() / 2) - MeasureText("LeaderBoard", 70) / 2,
		(GetScreenHeight() / 2) + 80,
		70,
		YELLOW
	);

	//escreve "Quit" acima do bot�o correspondente
	DrawText(
		"Quit",
		(GetScreenWidth() / 2) - MeasureText("Quit", 70) / 2,
		(GetScreenHeight() / 2) + 160,
		70,
		YELLOW
	);

}
