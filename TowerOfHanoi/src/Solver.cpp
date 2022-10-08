#include "Solver.h"
#include "raylib.h"

Solver& Solver::GetInstance()
{
	static Solver instance;
	return instance;
}

void Solver::GenerateMoves(int discs)
{
	m_Moves.clear();
	Hanoi(discs, 1, 3);
}

Move Solver::GetNextMove()
{
	if (m_Moves.size() > 0)
	{
		Move move = m_Moves.front();
		m_Moves.pop_front();
		return move;
	}

	return Move{ -1,-1 };
}

void Solver::DrawMoves()
{
	const int startX = 20;
	const int startY = 90;
	const int separation = 30;
	int i = 0;
	DrawText("MOVES:", 20, 60, 20, GRAY);
	for (const auto& m : m_Moves)
	{
		DrawText(TextFormat("(%d -> %d)", m.from, m.to), startX, startY + i * separation, 20, GRAY);
		i++;
	}
}

void Solver::Hanoi(int discs, int start, int end)
{
	if (discs == 1)
	{
		AddMove(start, end);
		return;
	}

	int other = 6 - (start + end);

	Hanoi(discs - 1, start, other);

	AddMove(start, end);

	Hanoi(discs - 1, other, end);
}

void Solver::AddMove(int from, int to)
{
	m_Moves.push_back(Move{ from,to });
}
