#pragma once
#include <map.h>
#include <Entity.h>
#include <string>
#include <fstream>

// Forward declaration of GameState
struct GameState;

//this is an instance of the game.
//This shouldn't load things like textures, those should be load outside
struct GameLogic
{


	Map map;
	Entity player;

	//returns false on fail
	bool init();

	//returns false on fail
	bool update(float deltaTime, gl2d::Renderer2D &renderer,
		AssetsManager &assetsManager, GameState& state);

	void close();

	float zoom = 60;

};

//This instance handles file saving and reading 
//Saves player position and zoom.
struct GameState {
	GameLogic gameLogic;
	int playerScore;
	glm::vec2 playerPosition;
	float zoomSaved;
	bool saveGameState(const GameState& state, const std::string& filename);
	bool loadGameState(GameState& state, const std::string& filename);

};



