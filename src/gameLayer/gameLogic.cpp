#include <gameLogic.h>
#include <map.h>
#include <imgui.h>
#include <platform/platformInput.h>
#include <filesystem>
#include <cassert>

bool GameState::saveGameState(const GameState& state, const std::string& filename) {
	std::ofstream outFile(filename, std::ios::binary);
	permaAssertComment(outFile.is_open(), "Failed to save file!"); //terminate if file cannot be saved
	std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
	outFile.write(reinterpret_cast<const char*>(&state), sizeof(GameState));
	outFile.close();
	return true;
}

bool GameState::loadGameState(GameState& state, const std::string& filename) {
	std::ifstream inFile(filename, std::ios::binary);
	permaAssertComment(inFile.is_open(), "Failed to load file!"); //terminate if file cannot load
	inFile.read(reinterpret_cast<char*>(&state), sizeof(GameState));
	inFile.close();
	return true;
}



bool GameLogic::init()
{
	map.create();
	return true;
}

bool GameLogic::update(float deltaTime,
	gl2d::Renderer2D &renderer,
	AssetsManager &assetsManager, GameState &state)
{
	bool exitDungeon = false;

#pragma region imgui
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Game Debug");

	ImGui::DragFloat2("Position", &player.pos[0]);
	ImGui::DragFloat("zoom", &zoom);

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

#pragma endregion


	player.resolveConstrains(map);

	//this function should be called last, it is important for collisions to work!
	player.updateMove();


	renderer.currentCamera.zoom = zoom;
	renderer.currentCamera.follow(player.getCenter(),
		deltaTime * 4.f, 0.01, 0.5,
		renderer.windowW, renderer.windowH);


	map.renderMap(renderer, assetsManager);

	renderer.renderRectangle(player.getAABB(), Colors_Red);

	state.playerPosition = player.pos;
	state.zoomSaved = zoom;
	
	renderer.flush();
	return !exitDungeon;
}

void GameLogic::close()
{

}
