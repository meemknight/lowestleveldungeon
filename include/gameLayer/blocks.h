#pragma once
#include <platformTools.h>
#include <gl2d/gl2d.h>


namespace Blocks
{
	//todo (LLGD): add blocks here, and use good names, like WallTop, WallLeft
	enum
	{
		none = 0,
		floor1,
		floor2,
		wall_front_down,
		BLOCKS_COUNT

	};
}

using Block = int;

namespace TileSets
{
	enum
	{
		none = 0,
		dungeonTileSet,
		TILE_SETS_COUNT
	};
}


glm::ivec2 getBlockUV(Block block);
int getTileSetIndex(Block block);
int isBlockColidable(Block block);