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
		glm::ivec2{1,1}, // wall
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
	};

	//if you see an error that means you added a block but forgot to add
	//a tile set colidable flag for it! ^^^^
	static_assert(sizeof(colidable) / sizeof(colidable[0])
		== Blocks::BLOCKS_COUNT);

	return colidable[block];
}
