#pragma once

#include "Rect.h"

class Render;

class Tile
{
public:

	Tile();

	~Tile();

	void Init(Point position);

	void Draw(bool debug, Render* render);

private:

	Point position;

};