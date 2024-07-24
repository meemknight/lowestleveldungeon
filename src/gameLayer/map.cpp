#include "map.h"

gl2d::Color4f colorArray[] = {Colors_Red, Colors_Green, Colors_Blue, Colors_White, Colors_Yellow, Colors_Magenta, Colors_Turqoise, Colors_Orange,Colors_Purple, Colors_Gray};

void Map::create(int density, int iterations,int s)
{
	*this = {};


	//todo (LLGD): we will have to implement this... :))

	blocks.resize(s * s);
	visitedTile.resize(s*s);
	
	size = {s,s};

 	this->randomNoiseMap(density);
 	this->cellularAutomaton(iterations);

 	for(int x =0; x< size.x; x++)
 	{
 		for(int y=0; y< size.y; y++)
 		{
 			if(blocks[x + y * size.x]==  Blocks::floor2 || blocks[x + y * size.x] ==  Blocks::floor1)
 			{
 				floorTiles.push_back({x,y});
 			}
 		}
 	}

 	while(!floorTiles.empty())
 	{
 	
 		glm::ivec2 pos = *floorTiles.begin();
 		if(visitedTile[pos.x + pos.y * size.x] != true)
 		{	
 				regions.resize(regions.size()+1);
 				getRegion(*floorTiles.begin() );
 				randomNoiseFluids(70,60);
 		 		//regions.push_back( getRegion(*floorTiles.begin() ));
 		 }
 		cellularAutomatonEnv();
 		 //floorTiles.erase(floorTiles.begin());


 	}

 	// for(int i=0; i<regions.size(); i++)
 	// {
 	// 	spawnBodies(regions[i]);
 	// }



	// for (int x = 0; x < size.x; x++)
	// 	for (int y = 0; y < size.y; y++)
	// 	{
	// 		blocks[x + y * size.x] = Blocks::floor1;
	// 	}

	// blocks[12] = Blocks::floor2;

	// getBlockUnsafe(5, 3) = Blocks::wall_front_down;
	// getBlockUnsafe(5, 5) = Blocks::wall_front_down;
	// getBlockUnsafe(5, 6) = Blocks::wall_front_down;
	// getBlockUnsafe(6, 6) = Blocks::wall_front_down;
	// getBlockUnsafe(6, 7) = Blocks::wall_front_down;
	// getBlockUnsafe(1, 2) = Blocks::wall_front_down;
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

void Map::renderRegions(gl2d::Renderer2D &renderer)
{
	std::cout<<regions.size()<<"\n";
	for (int x = 0; x < regions.size(); x++)
	{
		
		
		for (int y = 0; y < regions[x].tiles.size(); y++)
		{
			renderer.renderRectangle({regions[x].tiles[y].x,regions[x].tiles[y].y,1,1}, colorArray[x%9]);

		}

	}
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
					//renderer.renderRectangle({x,y,1,1}, Colors_White);
				}

			};

		}


	}


}

int Map::withinMapBounds(int x, int y, int width, int height)
{
	 return x >= 0 && x < width && y >= 0 && y < height;
}

void Map::randomNoiseMap(int density)
{
	
	 for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            int random_number = rand() % 100;
            if (random_number > density) {
                blocks[x + y * size.x] = Blocks::floor2;
            } else {
              blocks[x + y * size.x] = Blocks::wall_front_down;
            }
        }
    }
}

void Map::randomNoiseFluids(int chance, int density)
{
	Map::region* currRegion = &regions[regions.size()-1];
	
	int gen = rand() % 100;
	if(gen>chance)
		{
			 for (int x = 0; x <currRegion->tiles.size(); x++) {
	

		            int random_number = rand() % 100;
		            if (random_number > density) {

		            
		            	blocks[currRegion->tiles[x].x + currRegion->tiles[x].y * size.x] = Blocks::lava;
		            } else {
		            
		            	blocks[currRegion->tiles[x].x + currRegion->tiles[x].y * size.x] = Blocks::floor2;
		            }
		        
		    }

	    }
}

void Map::cellularAutomatonEnv()
{
	std::vector<Block> temp_blocks;
	for(uint x=0; x<3; x++)
	{	
		temp_blocks = blocks;

		for(int y=0; y< size.y; y++)
		{
			for(int x=0; x<size.x; x++)
			{
				if(blocks[y+x * size.x] != Blocks::wall_front_down)
				{
				uint neighbor_wall_count = this->getNeighbourTiles(temp_blocks,x,y);

				
				if( neighbor_wall_count >4)
				{
					blocks[y+x * size.x] = Blocks::floor2;

				}
				else
				{	
					blocks[y+x * size.x] = Blocks::lava;

			
				}
				}
			}
		}
	}

}


void Map::cellularAutomaton(int iterations)
{
	std::vector<Block> temp_blocks;
	for(uint x=0; x<iterations; x++)
	{	
		temp_blocks = blocks;

		for(int y=0; y< size.y; y++)
		{
			for(int x=0; x<size.x; x++)
			{
				uint neighbor_wall_count = this->getNeighbourWalls(temp_blocks,x,y);

				
				if( neighbor_wall_count >4)
				{
					blocks[y+x * size.x] = Blocks::wall_front_down;

				}
				else
				{
					blocks[y+x * size.x] = Blocks::floor2;

			
				}
			}
		}
	}

}

uint Map::getNeighbourWalls(std::vector<Block>& temp_blocks, int x, int y)
{	
	uint walls=0;
	Block tileType = (int)blocks[x + y * size.x];
	for(int b=y-1; b<=y+1; b++)
				{
					for(int a= x-1; a<=x+1; a++)
					{
						if(withinMapBounds(a,b,size.x,size.y))
						{
							if(b!=y || a!=x)
							{
								
								if(temp_blocks[b + a * size.x] == Blocks::wall_front_down)
								{
									walls++;
								}
								
							}
						}
						else
						{
							walls++;
						}
					}
				}

	return walls;
}

uint Map::getNeighbourTiles(std::vector<Block>& temp_blocks, int x, int y)
{	
	uint walls=0;
	Block tileType = (int)blocks[x + y * size.x];
	for(int b=y-1; b<=y+1; b++)
				{
					for(int a= x-1; a<=x+1; a++)
					{
						if(withinMapBounds(a,b,size.x,size.y))
						{
							if(b!=y || a!=x)
							{
								
								if(temp_blocks[b + a * size.x] != Blocks::lava)
								{
									walls++;
								}
								
							}
						}
					
					}
				}

	return walls;
}

void Map :: getRegion(glm::ivec2 startPos)
{
	
	Block tileType = (int)blocks[startPos.x + startPos.y * size.x]; //to get the starting tiletype of the starting tile

	
	//currentRegion.tiles.push_back(startPos);
	getRegionTiles(startPos,startPos, tileType);
	

}

void Map:: getRegionTiles(glm::ivec2 pos, glm::ivec2 lastPos, Block tileType)
{
	if(withinMapBounds(pos.x,pos.y,size.x,size.y))
	{		
		if(blocks[pos.x + pos.y * size.x] == tileType && visitedTile[pos.x + pos.y * size.x] != true)
		{
			regions[regions.size()-1].tiles.push_back(pos);

			
			for(size_t x=0; x< floorTiles.size(); x++)
			{
			
				if(floorTiles[x] == pos)
				{
					
					// to delete the floor tiles of the same region so that it isn't called for from the loop in create function  
					floorTiles.erase(floorTiles.begin() +x);
					break;
				}
				
			}

			visitedTile[pos.x + pos.y * size.x] = true;	

			//size_t lastFloorIdx = tiles.size()-1;
			 std::vector<glm::ivec2>::iterator it = regions[regions.size()-1].tiles.end() - 1;
        
  
       		size_t lastFloorIdx = std::distance(regions[regions.size()-1].tiles.begin(), it);
       	

			getRegionTiles({pos.x, pos.y - 1}, regions[regions.size()-1].tiles[lastFloorIdx], tileType); // for the tile above
			getRegionTiles({pos.x, pos.y + 1},regions[regions.size()-1].tiles[lastFloorIdx], tileType); // for the tile below
			getRegionTiles({pos.x + 1, pos.y},regions[regions.size()-1].tiles[lastFloorIdx], tileType); // for the tile to the right
			getRegionTiles({pos.x - 1, pos.y},regions[regions.size()-1].tiles[lastFloorIdx], tileType); 			
		}
		else
		{
			if(blocks[pos.x + pos.y * size.x] != tileType)
			{
				regions[regions.size()-1].edgeTiles.push_back(lastPos);  //sets  the tile in the previous iteration / call as an edge tile because the current one is not floor
			}
			return;
		}

	}

}

// CODE BELOW NOT WORKING YET!!


void Map::connectRegions()
{
	uint8_t chance = 50;

	for(uint16_t i=0; i<regions.size(); i++)
	{
		std::vector<uint> distToRegions; 
		uint8_t random_number = rand() % 101;
		if(random_number>chance)
		{
			std::vector<glm::ivec4> ends = findExtremeEnds(regions[i]);
			
		}
		else
		{
			continue;
		}
	}

}
std::vector<glm::ivec4> Map::findExtremeEnds(Map::region area)
{
	std::vector<glm::ivec4> extremeEnds(2);
	uint xLeast=size.x; uint xMax =0; uint yLeast = size.y; uint yMax=0;
	uint i=0;
	for(  i=0; i<area.edgeTiles.size(); i++)
	{
		
		if(area.edgeTiles[i].x < xLeast)	// top most position
		{
			xLeast= area.edgeTiles[i].x; 
			extremeEnds[0].x = area.edgeTiles[i].x;
			extremeEnds[0].y = area.edgeTiles[i].y;
		
		}
		if(area.edgeTiles[i].x > xMax) //bottom most point
		{
			xMax= area.edgeTiles[i].x;  
			extremeEnds[0].z = area.edgeTiles[i].x;
			extremeEnds[0].w = area.edgeTiles[i].y;
			
		}
		if(area.edgeTiles[i].y < yLeast)	// left most
		{
			yLeast= area.edgeTiles[i].y;
			extremeEnds[1].x = area.edgeTiles[i].x;
			extremeEnds[1].y = area.edgeTiles[i].y;
			
		}
		if(area.edgeTiles[i].y > yMax) // right most
		{
			yMax= area.edgeTiles[i].y;
			extremeEnds[1].z = area.edgeTiles[i].x;
			extremeEnds[1].w = area.edgeTiles[i].y;
			
		}
	}


	return extremeEnds;
}

void Map::spawnBodies(Map::region area)
{
	uint8_t chance = 50;

	uint8_t random_number = rand() % 151;
	std::cout<<"In Spawn Bodies"<<std::endl;
	if(random_number <= 50)
	{
		return;
	}
	else if(random_number > 50 && random_number <=100)
	{
		// generate water body
		std::vector<glm::ivec4> ends = findExtremeEnds(area);

		for(int i=ends[1].x; i< ends[1].z; i++)
		{
			for(int y=ends[0].y; y<ends[0].w; y++)
			{
			int random_number = rand() % 100;
            if (random_number > 50) {
                blocks[i + y * size.x] = Blocks::floor2;
            } else {
              blocks[i + y * size.x] = Blocks::lava;
            }
			}
		}
	}
	

}