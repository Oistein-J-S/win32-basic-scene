#pragma once

#include "resource.h"

void DrawTraficlight(int xPos, int yPos, int scale, int state , HDC hdc);
void createRoad(HDC hdc, int xStart, int yStart, int xEnd, int yEnd);
void createCars(HDC hdc, int xPos, int yPos, int angle);
bool isTooClose(int coordinate, int limitCoordinate);