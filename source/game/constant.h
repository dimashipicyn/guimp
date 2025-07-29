#pragma once

#include "core/math/point.h"

constexpr const int WindowWidth = 800;
constexpr const int WindowHeight = 600;
constexpr const int WindowCenterW = WindowWidth / 2;
constexpr const int WindowCenterH = WindowHeight / 2;

constexpr const int CellSize = 40;

constexpr const Point Srv { CellSize, 0 };
constexpr const Point Sdv { 0, CellSize };

constexpr int MapWidth = 20;
constexpr int MapHeight = 20;

constexpr int Cw = int(CellSize / 2);
constexpr int Ch = int(Cw / 2);

constexpr Point RightBasis { Cw, Ch };
constexpr Point LeftBasis { -Cw, Ch };