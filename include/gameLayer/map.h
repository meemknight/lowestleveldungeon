#pragma once
#include <blocks.h>
#include <vector>
#include <assetsManager.h>

#include <stdlib.h>


// namespace Regions
// {
// 	enum
// 	{
// 		normal=0,
// 		hard,
// 		demons
// 	};
// }
// using regionType = int;



struct Map
{

	void create(int, int, int);

	//functions for generating the map
	struct region
	{
		 
		//regionType type = Regions::normal;
		std::vector<glm::ivec2> tiles;
		std::vector<glm::ivec2> edgeTiles;
	};
	
	int withinMapBounds(int x, int y, int width, int height);
	void randomNoiseMap(int density);
	void cellularAutomaton(int iterations);
	uint getNeighbourWalls(std::vector<Block>& temp_blocks, int x, int y);

	void setWalls();

	void randomNoiseFluids(int chance, int density);

	uint getNeighbourTiles(std::vector<Block>& temp_blocks, int x, int y);
	void getRegion(glm::ivec2 startPos);
	void getRegionTiles(glm::ivec2 pos, glm::ivec2 lastPos, Block tileType);

	void connectRegions();	
	std::vector<glm::ivec4> findExtremeEnds(Map::region area);

	void spawnBodies(region);
	uint distance(glm::ivec2, glm::ivec2);

	//=========
	std::vector<Block> blocks;
	std::vector<float> blocksRotation;
	std::vector<Block> wallEdges;
	glm::ivec2 size = {}; 

	std::vector<glm::ivec2> floorTiles;
	std::vector<bool> visitedTile;
	std::vector<region> regions;

	//won't check for bounds!
	Block &getBlockUnsafe(int x, int y);

	//returns null ptr if fails
	Block *getBlockSafe(int x, int y);


	void renderMap(gl2d::Renderer2D &renderer,
		AssetsManager &assetManager);
	void renderRegions(gl2d::Renderer2D &renderer);


};