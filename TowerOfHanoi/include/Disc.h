#pragma once
#include "raylib.h"

class Disc
{
public:
    Disc(){}
    Disc(int value,Color color) :m_Value(value),m_Color(color) {}
    int GetValue() const { return m_Value; };
    Color GetColor() const { return m_Color; };
private:
    Color m_Color = WHITE;
    int m_Value = 0;
};