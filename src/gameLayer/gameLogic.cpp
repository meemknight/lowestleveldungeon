#include <gameLogic.h>
#include <imgui.h>
#include <platform/platformInput.h>


bool GameLogic::init()
{
	density=58; iterations=8; size=100;
	map.create(density,iterations, size);
	inventory.create(40);

	return true;
}

bool GameLogic::update(float deltaTime,
	gl2d::Renderer2D &renderer, glui::RendererUi &uirenderer,
	AssetsManager &assetsManager)
{
	bool exitDungeon = false;

#pragma region imgui
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Game Debug");

	ImGui::DragFloat2("Position", &player.pos[0]);
	ImGui::DragFloat("zoom", &zoom);
	ImGui::SliderInt("Density", &density, 0, 100);
	ImGui::SliderInt("Iterations", &iterations, 0, 20);
	ImGui::SliderInt("Size", &size, 0, 1000);
	if (ImGui::Button("Regenerate Map"))
	{
		map.create(density,iterations,size);
	}
	if (ImGui::Button(player.checkCollisions ? "COLLISION ON" : "COLLISION OFF"))
    {
        player.checkCollisions = !player.checkCollisions;  // Toggle the state
    }
    if(ImGui::Button(renderRegions ? "Render Tiles": "Render Regions"))
    {
    	renderRegions= !renderRegions;
    }
	if (ImGui::Button("Exit"))
	{
		exitDungeon = true;
	}

	ImGui::End();
#pragma endregion

#pragma region input
	glm::vec2 move = {};
	if (platform::isButtonHeld(platform::Button::A))
	{
		move.x -= 1;
	}
	if (platform::isButtonHeld(platform::Button::D))
	{
		move.x += 1;
	}
	if (platform::isButtonHeld(platform::Button::W))
	{
		move.y -= 1;
	}
	if (platform::isButtonHeld(platform::Button::S))
	{
		move.y += 1;
	}

	if (glm::length(move) != 0)
	{
		move = glm::normalize(move);
		move *= deltaTime * 6.f; //player speed
	}

	player.pos += move;

	if(platform::isButtonReleased(platform::Button::I))
	{
		//toggle inventory
	}
#pragma endregion

	player.resolveConstrains(map);

	//this function should be called last, it is important for collisions to work!
	player.updateMove();


	renderer.currentCamera.zoom = zoom;
	renderer.currentCamera.follow(player.getCenter(),
		deltaTime * 4.f, 0.01, 0.5,
		renderer.windowW, renderer.windowH);

	renderer.clearScreen({10.0f/255.0f,17.0f/255.0f,29.0f/255.0f, 10.0f});
	if(!renderRegions)
	{
	map.renderMap(renderer, assetsManager);
	}
	else
	{	
	map.renderRegions(renderer);
	}
	renderer.renderRectangle(player.getAABB(), Colors_Red);


uirenderer.Begin(1);
	//	uirenderer.SetAlignModeFixedSizeWidgets({100,platform::getFrameBufferSizeY() -200});
//uirenderer.Text("", Colors_White);

		//uirenderer.SetAlignModeFixedSizeWidgets({100,50});
		uirenderer.BeginMenu("quickslots", Colors_White, {});
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

	return !exitDungeon;
}

void GameLogic::close()
{

}
