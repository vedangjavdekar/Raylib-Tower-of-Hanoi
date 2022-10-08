#pragma once 
#include <list>
#include "Move.h"

class Solver
{
public:
	static Solver& GetInstance();

	void GenerateMoves(int discs);
	Move GetNextMove();

	inline bool AreMovesLeft()const { return m_Moves.size() > 0; }

	void DrawMoves();
protected:
	void Hanoi(int discs, int start, int end);
	void AddMove(int from, int to);
private:
	std::list<Move> m_Moves;
};

