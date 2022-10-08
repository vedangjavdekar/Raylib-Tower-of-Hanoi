#include "raylib.h"
#include "Solver.h"
#include "Tower.h"

int main()
{
	const int screenWidth = 1280;
	const int screenHeight = 720;

	int discs = 3;
	const int minDiscs = 3;
	const int maxDiscs = 10;

	Solver& solver = Solver::GetInstance();
	solver.GenerateMoves(discs);

	Tower tower;
	tower.Init(discs, 1);

	InitWindow(screenWidth, screenHeight, "Tower Of Hanoi");
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	const int instructionWidth = MeasureText("Press SPACE to go to next move. R to restart.", 20);
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------

		if (IsKeyPressed(KEY_RIGHT))
		{
			if (discs + 1 <= maxDiscs)
			{
				discs++;
				solver.GenerateMoves(discs);
				tower.Init(discs, 1);
			}
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			if (discs - 1 >= minDiscs)
			{
				discs--;
				solver.GenerateMoves(discs);
				tower.Init(discs, 1);
			}
		}

		if (IsKeyPressed(KEY_R))
		{
			solver.GenerateMoves(discs);
			tower.Init(discs, 1);
		}

		if (IsKeyPressed(KEY_SPACE))
		{
			if (!tower.IsMoveInProgress())
			{
				Move move = solver.GetNextMove();
				tower.BeginMove(move);
			}
		}
		tower.Update();
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText(TextFormat("Current Number of Discs: %d \t Use Left/Right Arrow Keys to increase/decrease.", discs), 20, 20, 20, DARKGRAY);
		solver.DrawMoves();

		tower.Draw();
		DrawText("Press SPACE to go to next move. R to restart.", 0.5f * (screenWidth - instructionWidth), screenHeight - 30, 20, DARKGRAY);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}