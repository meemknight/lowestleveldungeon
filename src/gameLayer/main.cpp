#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <gameLogic.h>
#include <glui/glui.h>

static gl2d::Renderer2D renderer;
static GameLogic game;
static AssetsManager assetsManager;
static glui::RendererUi uirenderer;

//todo (LLGD): you will change this... :))
static bool inGame = 0;

bool initGame()
{

	renderer.create();
	uirenderer.SetAlignModeFixedSizeWidgets({0,150});

	assetsManager.loadAllAssets();

	return true;
}


bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h
	
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion


	if (inGame)
	{

		if (!game.update(deltaTime, 
			renderer, assetsManager))
		{
			game.close();
			inGame = 0;
		}

	}
	else
	{

		uirenderer.Begin(1);

		uirenderer.Text("Lowest Level Dungeon XD", Colors_White);
		
		//todo (LLGD): add a nice texture here for the button.
		if (uirenderer.Button("Play", Colors_White))
		{
			inGame = true;
			game.init();

		}

		uirenderer.BeginMenu("Load game...", Colors_White, {});
		{
			uirenderer.Text("Ther's nothing here :((", Colors_White);


		}
		uirenderer.EndMenu();

		uirenderer.End();


		uirenderer.renderFrame(renderer, assetsManager.font, 
			platform::getRelMousePosition(),
			platform::isLMousePressed(), 
			platform::isLMouseHeld(), platform::isLMouseReleased(),
			platform::isButtonReleased(platform::Button::Escape), 
			platform::getTypedInput(), deltaTime);


		renderer.flush();

	}

	


	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{


}
