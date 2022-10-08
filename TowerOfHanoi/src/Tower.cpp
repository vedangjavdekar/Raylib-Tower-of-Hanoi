#include "Tower.h"
#include "extras/easings.h"

void Tower::Init(int discs, int startIndex)
{
	Reset();
	m_MaxDiscs = discs;
	m_Towers.push_back(std::vector<Disc>());
	m_Towers.push_back(std::vector<Disc>());
	m_Towers.push_back(std::vector<Disc>());

	for (int i = discs; i > 0; i--)
	{
		m_Towers[startIndex-1].push_back(Disc(i, DISC_COLORS[i % 6]));
	}
}

void Tower::BeginMove(const Move& move)
{
	if (move.from == -1 && move.to == -1)
	{
		return;
	}

	m_CurrMove = move;
	m_MoveInProgress = true;
	m_FrameCounter = 0;
	m_CurrentDisc = m_Towers[m_CurrMove.from - 1].back();

	const int discWidth = GetDiscWidth(m_CurrentDisc.GetValue());
	m_StartX = PEG_START_X + 0.5f * PEG_WIDTH + (m_CurrMove.from-1) * PEG_SEPARATION - 0.5f * discWidth;
	m_StartY =  GROUND_Y - m_Towers[m_CurrMove.from-1].size() * DISC_HEIGHT;
	m_CurrX = m_StartX;
	m_CurrY = m_StartY;

	m_Towers[m_CurrMove.from - 1].pop_back();

	m_EndX = PEG_START_X + 0.5f * PEG_WIDTH + (m_CurrMove.to-1) * PEG_SEPARATION - 0.5f * discWidth;
	m_EndY = GROUND_Y - (m_Towers[m_CurrMove.to - 1].size() + 1) * DISC_HEIGHT;
}

void Tower::Update()
{
	if (!m_MoveInProgress)
	{
		return;
	}
	
	m_FrameCounter++;
	m_CurrX = EaseCubicInOut(m_FrameCounter, m_StartX, m_EndX - m_StartX, MAX_FRAMES);
	m_CurrY = EaseCubicInOut(m_FrameCounter, m_StartY, m_EndY - m_StartY, MAX_FRAMES);

	if (m_FrameCounter == MAX_FRAMES)
	{
		m_Towers[m_CurrMove.to - 1].push_back(m_CurrentDisc);
		m_MoveInProgress = false;
	}
}

void Tower::Draw()
{
	DrawRectangle(GROUND_X, GROUND_Y, 3 * PEG_SEPARATION, 50, DARKGRAY);
	for (int i = 0; i < 3; ++i)
	{
		DrawRectangle(PEG_START_X + i * PEG_SEPARATION, PEG_START_Y, PEG_WIDTH, GROUND_Y - PEG_START_Y, DARKGRAY);
	}

	for (int i = 0; i < m_Towers.size(); ++i)
	{
		for (int j = m_Towers[i].size() - 1; j >= 0; j--)
		{
			const int discWidth = GetDiscWidth(m_Towers[i][j].GetValue());
			DrawRectangle(PEG_START_X + 0.5f * PEG_WIDTH + i * PEG_SEPARATION - 0.5f * discWidth, GROUND_Y - (j + 1) * DISC_HEIGHT, discWidth, DISC_HEIGHT, m_Towers[i][j].GetColor());
		}
	}

	if (m_MoveInProgress)
	{
		DrawText(TextFormat("Current Move: (%d -> %d)", m_CurrMove.from, m_CurrMove.to), 500, 150, 20, BLUE);
		const int discWidth = GetDiscWidth(m_CurrentDisc.GetValue());
		DrawRectangle(m_CurrX,m_CurrY,discWidth,DISC_HEIGHT,m_CurrentDisc.GetColor());
	}
}

void Tower::Reset()
{
	m_CurrMove.from = -1;
	m_CurrMove.to = -1;
	m_MoveInProgress = false;
	m_Towers.clear();
}

const int Tower::GetDiscWidth(int value) const
{
	float percent = ((float)value) / ((float)m_MaxDiscs);
	return DISC_MIN_WIDTH + ceil(percent * (DISC_MAX_WIDTH - DISC_MIN_WIDTH));
}
