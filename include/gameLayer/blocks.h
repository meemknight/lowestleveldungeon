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
		lava,
		water,
		wall_edge_left,
		wall_edge_right,
		wall_front_up,
		barrel,
		inner_wall,
		wall_left_corner,
		wall_edge_front,
		wall_edge_X_axis,
		wall_edge_Y_axis,
		wall_edge_corner_r,
		wall_edge_corner_l,
		wall_edge_wall_right,
		wall_right_corner,
		wall_corner,
		wall_edge_wall_left,
		wall_edge_wall_both,
		wall_edge_corner_three,
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
		debugTileSet,
		barrel,
		TILE_SETS_COUNT
	};
}


glm::ivec2 getBlockUV(Block block);
int getTileSetIndex(Block block);
int isBlockColidable(Block block);