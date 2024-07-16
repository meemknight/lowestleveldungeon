#include "map.h"

void Map::create()
{
	*this = {};


	//todo (LLGD): we will have to implement this... :))

	blocks.resize(10 * 10);

	size = {10,10};


	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
		{
			blocks[x + y * size.x] = Blocks::floor1;
		}

	blocks[12] = Blocks::floor2;

	getBlockUnsafe(5, 3) = Blocks::wall_front_down;
	getBlockUnsafe(5, 5) = Blocks::wall_front_down;
	getBlockUnsafe(5, 6) = Blocks::wall_front_down;
	getBlockUnsafe(6, 6) = Blocks::wall_front_down;
	getBlockUnsafe(6, 7) = Blocks::wall_front_down;

}

Block &Map::getBlockUnsafe(int x, int y)
{
	return blocks[x + y * size.x];
}

Block *Map::getBlockSafe(int x, int y)
{
	if (x < 0 || y < 0 || x >= size.x || y >= size.y)
	{
		return nullptr;
	}

	return &blocks[x + y * size.x];
}


void Map::renderMap(gl2d::Renderer2D &renderer,
	AssetsManager &assetManager)
{


	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{

			Block b = getBlockUnsafe(x, y);

			if (b)
			{

				int tileSet = getTileSetIndex(b);
				auto uv = getBlockUV(b);

				auto tile = assetManager.tileSets[tileSet];

				if (tile.texture.id)
				{
					renderer.renderRectangle({x,y,1,1},
						 tile.texture,
						 Colors_White,
						{},
						0,
						 tile.atlas.get(uv.x, uv.y)
						);
				}

			};

		}


	}


}
