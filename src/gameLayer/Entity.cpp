#include <Entity.h>


bool aabb(glm::vec4 b1, glm::vec4 b2)
{
	if (((b1.x - b2.x < b2.z)
		&& b2.x - b1.x < b1.z
		)
		&& ((b1.y - b2.y < b2.w)
		&& b2.y - b1.y < b1.w
		)
		)
	{
		return 1;
	}
	return 0;
}

void Entity::resolveConstrains(Map &mapData)
{
	bool upTouch = 0;
	bool downTouch = 0;
	bool leftTouch = 0;
	bool rightTouch = 0;

	float distance = glm::length(lastPos - pos);
	const float BLOCK_SIZE = 1.f;

	if (distance < BLOCK_SIZE)
	{
		if(checkCollisions== true)
		{
		checkCollisionBrute(pos,
			lastPos,
			mapData,
			upTouch,
			downTouch,
			leftTouch,
			rightTouch
		);
		}
	}
	else
	{
		glm::vec2 newPos = lastPos;
		glm::vec2 delta = pos - lastPos;
		delta = glm::normalize(delta);
		delta *= 0.9 * BLOCK_SIZE;

		do
		{
			newPos += delta;
			glm::vec2 posTest = newPos;
			if(checkCollisions==true)
			{
			checkCollisionBrute(newPos,
				lastPos,
				mapData,
				upTouch,
				downTouch,
				leftTouch,
				rightTouch);
			}
			if (newPos != posTest)
			{
				pos = newPos;
				goto end;
			}

		} while (glm::length((newPos + delta) - pos) > 1.0f * BLOCK_SIZE);

		if(checkCollisions==true)
		{
		checkCollisionBrute(pos,
			lastPos,
			mapData,
			upTouch,
			downTouch,
			leftTouch,
			rightTouch);
		}
	}

end:

	//clamp the player inside the map

	if (pos.x < 0) { pos.x = 0; }
	if (pos.x + dimensions.x > (mapData.size.x) * BLOCK_SIZE)
	{ pos.x = ((mapData.size.x) * BLOCK_SIZE) - dimensions.x; }

	if (pos.y < 0) { pos.y = 0; }
	if (pos.y + dimensions.y > (mapData.size.y) * BLOCK_SIZE)
	{ pos.y = ((mapData.size.y) * BLOCK_SIZE) - dimensions.y; }
	

}

void Entity::updateMove()
{

	if (lastPos.x - pos.x < 0)
	{
		movingRight = -1;
	}
	else if (lastPos.x - pos.x > 0)
	{
		movingRight = 0;
	}

	lastPos = pos;

}

glm::vec2 Entity::getCenter()
{
	return pos + dimensions / 2.f;
}

//AABB works like this: {X, Y, Width, Height}

glm::vec4 Entity::getAABB()
{
	return {pos, dimensions};
}

void Entity::checkCollisionBrute(glm::vec2 &pos,
	glm::vec2 lastPos, Map &mapData,
	bool &upTouch, bool &downTouch, bool &leftTouch, bool &rightTouch)
{
	glm::vec2 delta = pos - lastPos;
	const float BLOCK_SIZE = 1.f;

	if (
		(pos.y < -dimensions.y)
		|| (pos.x < -dimensions.x)
		|| (pos.y > mapData.size.y * BLOCK_SIZE)
		|| (pos.x > mapData.size.x * BLOCK_SIZE)
		)
	{
		return;
	}


	glm::vec2 newPos = performCollision(mapData, {pos.x, lastPos.y}, {dimensions.x, dimensions.y}, {delta.x, 0},
		upTouch, downTouch, leftTouch, rightTouch);
	pos = performCollision(mapData, {newPos.x, pos.y}, {dimensions.x, dimensions.y}, {0, delta.y},
		upTouch, downTouch, leftTouch, rightTouch);

}

glm::vec2 Entity::performCollision(Map &mapData, glm::vec2 pos, glm::vec2 size, glm::vec2 delta, bool &upTouch, bool &downTouch, bool &leftTouch, bool &rightTouch)
{
	int minX = 0;
	int minY = 0;
	int maxX = mapData.size.x;
	int maxY = mapData.size.y;

	const float BLOCK_SIZE = 1.f;

	minX = (pos.x - abs(delta.x) - BLOCK_SIZE) / BLOCK_SIZE;
	maxX = ceil((pos.x + abs(delta.x) + BLOCK_SIZE + size.x) / BLOCK_SIZE);

	minY = (pos.y - abs(delta.y) - BLOCK_SIZE) / BLOCK_SIZE;
	maxY = ceil((pos.y + abs(delta.y) + BLOCK_SIZE + size.y) / BLOCK_SIZE);

	minX = std::max(0, minX);
	minY = std::max(0, minY);
	maxX = std::min(mapData.size.x, maxX);
	maxY = std::min(mapData.size.y, maxY);

	for (int y = minY; y < maxY; y++)
		for (int x = minX; x < maxX; x++)
		{
			if (isBlockColidable(mapData.getBlockUnsafe(x, y)))
			{
				if (aabb({pos,dimensions}, 
					{x * BLOCK_SIZE, y * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE}))
				{
					if (delta.x != 0)
					{
						if (delta.x < 0) // moving left
						{
							leftTouch = 1;
							pos.x = x * BLOCK_SIZE + BLOCK_SIZE;
							goto end;
						}
						else
						{
							rightTouch = 1;
							pos.x = x * BLOCK_SIZE - dimensions.x;
							goto end;
						}
					}
					else
					{
						if (delta.y < 0) //moving up
						{
							upTouch = 1;
							pos.y = y * BLOCK_SIZE + BLOCK_SIZE;
							goto end;
						}
						else
						{
							downTouch = 1;
							pos.y = y * BLOCK_SIZE - dimensions.y;
							goto end;
						}
					}

				}
			}

		}

end:
	return pos;

}



