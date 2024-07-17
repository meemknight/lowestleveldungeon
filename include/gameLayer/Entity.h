#pragma once
#include <glm/vec2.hpp>
#include <map.h>

struct Entity
{
	//top left corner!!
	glm::vec2 pos;

	//last position is used to calculate colisions
	glm::vec2 lastPos = {};

	glm::vec2 dimensions = {0.9,0.9};

	//used to display the sprite
	bool movingRight = 0;

	void resolveConstrains(Map &mapData);


	//should be called only once per frame
	void updateMove();

	glm::vec2 getCenter();

	//AABB works like this: {X, Y, Width, Height}
	glm::vec4 getAABB();
	
private:
	void checkCollisionBrute(glm::vec2 &pos, glm::vec2 lastPos, Map &mapData,
		bool &upTouch, bool &downTouch, bool &leftTouch, bool &rightTouch);
	glm::vec2 performCollision(Map &mapData, glm::vec2 pos, glm::vec2 size, glm::vec2 delta,
		bool &upTouch, bool &downTouch, bool &leftTouch, bool &rightTouch);
};


//pos and size on on every component
//AABB works like this: {X, Y, Width, Height}
bool aabb(glm::vec4 b1, glm::vec4 b2);

