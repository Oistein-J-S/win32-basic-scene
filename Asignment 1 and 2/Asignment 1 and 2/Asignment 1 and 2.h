#pragma once

#include "resource.h"

void DrawTraficlight(int xPos, int yPos, int scale, int state , HDC hdc);
void createRoad(HDC hdc, int xStart, int yStart, int xEnd, int yEnd);
bool isTooClose(int coordinate, int limitCoordinate);