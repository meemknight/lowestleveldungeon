#include "blocks.h"

glm::ivec2 getBlockUV(Block block)
{

	permaAssert(block < Blocks::BLOCKS_COUNT);
	permaAssert(block >= 0);

	//we will create a computed goto here

	static glm::ivec2 UVs[] = {
		glm::ivec2{7,7}, // none (an empty portion of the tile set)
		glm::ivec2{0,4}, // floor1
		glm::ivec2{1,4}, // floor2
		glm::ivec2{1,1}, // wall front down
		glm::ivec2{0,0}, // Lava from debug tileset
		glm::ivec2{1,0}, // water
		glm::ivec2{0,1}, // wall edge left
		glm::ivec2{2,1}, // wall edge right
		glm::ivec2{1,0}, // wall front up 
		glm::ivec2{0,0}, // Barrel
		glm::ivec2{3,5}, // inner wall
		glm::ivec2{4,1}, // wall left corner
		glm::ivec2{1,2}, // wall edge front
		glm::ivec2{7,7}, // render 2 edges when two adjacent blocks in X axis are floors
		glm::ivec2{7,7}, // render 2 edges when two adjacent blocks in Y axis are floors
		glm::ivec2{4,0}, 
		glm::ivec2{3,0},
		glm::ivec2{0,0}, // for the right corner where there is a wall_front_up to the right
		glm::ivec2{3,1}, // wall right corner
		glm::ivec2{4,5}, // wall corner 
		glm::ivec2{2,0}, // wall_edge_wall_left
		glm::ivec2{7,7}, // wall_edge_wall_both
		glm::ivec2{3,7}, // wall_edge_corner_three
	};

	//if you see an error that means you added a block but forgot to add
	//an uv to it! ^^^^
	static_assert(sizeof(UVs) / sizeof(UVs[0]) == Blocks::BLOCKS_COUNT);

	return UVs[block];
}

int getTileSetIndex(Block block)
{
	permaAssert(block < Blocks::BLOCKS_COUNT);
	permaAssert(block >= 0);

	//we will create a computed goto here

	static int tileSetsIndexes[] = {
		TileSets::none,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::debugTileSet,
		TileSets::debugTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::barrel,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::none,
		TileSets::none,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::dungeonTileSet,
		TileSets::none,
		TileSets::dungeonTileSet,
	};

	//if you see an error that means you added a block but forgot to add
	//a tile set for it! ^^^^
	static_assert(sizeof(tileSetsIndexes) / sizeof(tileSetsIndexes[0]) 
		== Blocks::BLOCKS_COUNT);

	return tileSetsIndexes[block];
}

int isBlockColidable(Block block)
{
	permaAssert(block < Blocks::BLOCKS_COUNT);
	permaAssert(block >= 0);

	//we will create a computed goto here
	static bool colidable[] = {
		0,
		0,
		0,
		1,
		0,
		0,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
	};

	//if you see an error that means you added a block but forgot to add
	//a tile set colidable flag for it! ^^^^
	static_assert(sizeof(colidable) / sizeof(colidable[0])
		== Blocks::BLOCKS_COUNT);

	return colidable[block];
}
