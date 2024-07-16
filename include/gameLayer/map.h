#pragma once
#include <blocks.h>
#include <vector>
#include <assetsManager.h>



struct Map
{

	void create();


	std::vector<Block> blocks;
	glm::ivec2 size = {};


	//won't check for bounds!
	Block &getBlockUnsafe(int x, int y);

	//returns null ptr if fails
	Block *getBlockSafe(int x, int y);


	void renderMap(gl2d::Renderer2D &renderer,
		AssetsManager &assetManager);


};