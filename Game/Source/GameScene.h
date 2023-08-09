#pragma once

#include "Scene.h"
#include "Grid.h"

class Texture;
class Tile;

// GAMEPLAY MAIN MECHANIC
// Fuse Plantas Loucas and PVZ
// The player has Main Plants and Secondary Plants.
// Main Plants can only be placed once, and when they are eaten, can be placed again.
// This ones have special powers, such as:
//		- Allow movement of other plants already placed
//		- Shoot at three lines at the same time
//		- Make sunflowers generate double sun
//		- Boost up plant's power in a region
// Secondary Plants can be placed multiple times, like PVZ ones
// This ones have classic powers, such as:
//		- Generating sun
//		- Shooting one line
//		- Shielding other plants
//
// The Main Plants can be leveled up and evolved

class GameScene : public Scene
{
public:

	GameScene();

	~GameScene() override;

	bool Start() override;

	bool Update(float dt) override;

	bool CleanUp() override;

	void SaveScene() override;

	void LoadScene() override;

private:

	void UpdateGame();

	void DrawGame();

private:

	Texture* garden = nullptr;
	Grid<Tile*>* grid = nullptr;

};
