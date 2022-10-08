#pragma once
#include <vector>

#include "Move.h"
#include "Disc.h"

class Tower
{
    const int GROUND_X = 300;
    const int GROUND_Y = 600;
    const int MAX_FRAMES = 30;
    const int DISC_HEIGHT = 20;
    const int DISC_MIN_WIDTH = 50;
    const int DISC_MAX_WIDTH = 200;
    const int PEG_WIDTH = 10;
    const int PEG_START_X = GROUND_X + 0.5f * DISC_MAX_WIDTH - 0.5f * PEG_WIDTH;
    const int PEG_START_Y = 300;
    const int PEG_SEPARATION = DISC_MAX_WIDTH + 20;

    const Color DISC_COLORS[6] = { YELLOW,PINK,LIME,SKYBLUE,RED,PURPLE };
public:
    void Init(int discs, int startIndex);

    inline bool IsMoveInProgress()const { return m_MoveInProgress; }
    void BeginMove(const Move& move);
    void Update();
    void Draw();

protected:
    void Reset();
    const int GetDiscWidth(int value)const;
private:
    bool m_MoveInProgress = false;
    int m_FrameCounter=0;
    int m_StartX = 0;
    int m_CurrX = 0;
    int m_EndX = 0;
    int m_StartY = 0;
    int m_CurrY = 0;
    int m_EndY = 0;

    Disc m_CurrentDisc;
    Move m_CurrMove;

    int m_MaxDiscs = 0;
    std::vector<std::vector<Disc>> m_Towers;
};