#pragma once
#include <gl2d/gl2d.h>
#include <blocks.h>

struct TileSet
{
	gl2d::Texture texture;
	gl2d::TextureAtlasPadding atlas;
};

//this structu will load all the assets at the begining of the game.
//so idealy it shouldn't do much other than hold them
struct AssetsManager
{
	
	TileSet tileSets[TileSets::TILE_SETS_COUNT];
	gl2d::Font font;

	void loadAllAssets();


};