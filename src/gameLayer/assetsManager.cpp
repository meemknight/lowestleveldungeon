#include <assetsManager.h>



void AssetsManager::loadAllAssets()
{

	font.createFromFile(RESOURCES_PATH "font/roboto_black.ttf");
	//todo check for errors (the texture id is 0 if error)

	static const char *tileSetsPaths[] =
	{
		"",
		RESOURCES_PATH "map/Damp Dungeon Tileset.png",
		RESOURCES_PATH "map/map debug tileset.png",
		RESOURCES_PATH "map/Barrel Sprite.png",
		RESOURCES_PATH "items/Item Sprites.png"
	};

	//if you see an error that means you added a sprite but forgot to add
	//a name to it! ^^^^
	static_assert(sizeof(tileSetsPaths) / sizeof(tileSetsPaths[0])
		== TileSets::TILE_SETS_COUNT);

	//this represents the size of one block
	static const int blockSize[] =
	{
		0,
		16,
		16,
		16,
		32,
	};

	//if you see an error that means you added a sprite but forgot to add
	//a block size to it! ^^^^
	static_assert(sizeof(blockSize) / sizeof(blockSize[0])
		== TileSets::TILE_SETS_COUNT);


	//how many blocks are there in the texture atlas
	static const glm::ivec2 textureAtlasSizes[] =
	{
		{},
		{7, 8},
		{0, 1},
		{0, 0},
		{16,23},
	};

	//if you see an error that means you added a sprite but forgot to add
	//am texture atlas size to it! ^^^^
	static_assert(sizeof(textureAtlasSizes) / sizeof(textureAtlasSizes[0])
		== TileSets::TILE_SETS_COUNT);


	for (int i = 0; i < TileSets::TILE_SETS_COUNT; i++)
	{

		const char *name = tileSetsPaths[i];

		if (name[0] != 0)
		{

			tileSets[i].texture.loadFromFileWithPixelPadding(name,
				blockSize[i], true, true
			);

			if (tileSets[i].texture.id == 0)
			{
				//todo (LLGD): report error here
			}
			else
			{
				auto size = tileSets[i].texture.GetSize();

				tileSets[i].atlas =
					gl2d::TextureAtlasPadding(
					textureAtlasSizes[i].x, textureAtlasSizes[i].y,
					size.x, size.y);

			}

		}


	}



}