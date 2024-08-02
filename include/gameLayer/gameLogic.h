#pragma once
#include <map.h>
#include <Entity.h>

//this is an instance of the game.
//This shouldn't load things like textures, those should be load outside
struct GameLogic
{


	Map map;
	Entity player;
	int density;
	int iterations;
	int size;
	bool renderRegions=false;
	//returns false on fail
	bool init();

	//returns false on fail
	bool update(float deltaTime, gl2d::Renderer2D &renderer,
		AssetsManager &assetsManager);

	void close();

	float zoom = 60;

};
