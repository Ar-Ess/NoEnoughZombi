#include "Tile.h"
#include "Render.h"
#include "GameDefs.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Init(Point position)
{
	this->position = position;
}

void Tile::Draw(bool debug, Render* render)
{
	if (debug) render->DrawRectangle({ { (position * TILE_SIZE) + Point(TILE_OFFSET) + Point(0, TILE_SIZE / 2)}, TILE_SIZE, TILE_SIZE / 2 }, {170, 170, 0, 200});
}
