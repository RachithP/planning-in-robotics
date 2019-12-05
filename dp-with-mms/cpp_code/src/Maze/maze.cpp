//! \file maze.cpp

#include "maze.h"
#include <iostream>
#include "../API/api.h"
#include "../Direction/direction.h"

/** @brief Maze class constructor implementation
	* @details Set the default maze structure with boundary filled with walls.
    * This establishes a perimeter around the maze area. This area will be populated
    * by maze walls as the maze feature runs. Walls are set in the North, East, South,
    * and West directions.
*/
fp::Maze::Maze()
{
	for(int x=0; x<WIDTH; ++x){
		for(int y=0; y<HEIGHT; ++y){
			
			maze_[x][y] = 0; // Default value set to be 0 -> all booleans are non-active
			
			if(x==0){
				setWall(x, y, fp::Direction::WEST);
			}
			if(y==0){
				setWall(x, y, fp::Direction::SOUTH);
			}
			if(x==WIDTH-1){
				setWall(x, y, fp::Direction::EAST);
			}
			if(y==HEIGHT-1){
				setWall(x, y, fp::Direction::NORTH);
			}
		}
	}
}


/** @brief Reads presence of wall in maze file from given position and current robot heading.
 * @details Function readwall evalutates the provided X and Y coordinate position with current heading for the presence of
 * a wall in each direction and sets it in the maze simulator by calling sim API. \n In each heading direction case, setWall is
 * called to set wall in maze. The 4 cases are North, South, East, or West heading of the simulation mouse/robot.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @param curr_direction current robot's heading direction
 * @return void
 */
 void fp::Maze::readWall(int x, int y, char curr_direction)
{
	switch(curr_direction){
		case fp::Direction::NORTH : if(API::wallFront()){// Here, API wallfront, right, left, considers robot's orientation before returning the values.
									setWall(x, y, fp::Direction::NORTH);
								};
								if(API::wallRight()){
									setWall(x, y, fp::Direction::EAST);
								};
								if(API::wallLeft()){
									setWall(x, y, fp::Direction::WEST);
								};
								break;
		case fp::Direction::EAST : if(API::wallFront()){
									setWall(x, y, fp::Direction::EAST);
								};
								if(API::wallRight()){
									setWall(x, y, fp::Direction::SOUTH);
								};
								if(API::wallLeft()){
									setWall(x, y, fp::Direction::NORTH);
								};
								break;
		case fp::Direction::SOUTH : if(API::wallFront()){
									setWall(x, y, fp::Direction::SOUTH);
								};
								if(API::wallRight()){
									setWall(x, y, fp::Direction::WEST);
								};
								if(API::wallLeft()){
									setWall(x, y, fp::Direction::EAST);
								};
								break;
		case fp::Direction::WEST : if(API::wallFront()){
									setWall(x, y, fp::Direction::WEST);
								};
								if(API::wallRight()){
									setWall(x, y, fp::Direction::NORTH);
								};
								if(API::wallLeft()){
									setWall(x, y, fp::Direction::SOUTH);
								};
								break;
	}
}

/** @brief Function setWall() uses simulator API to set wall in required direction in the simulator. Called during readwall function.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @param direction direction at (x,y) where the wall needs to be set
 * @return void
 */
void fp::Maze::setWall(int x, int y, char direction)
{
	switch(direction){
		case fp::Direction::NORTH : maze_[x][y] |= 1; API::setWall(x, y, fp::Direction::NORTH); break;// Here, API set wall considers north as true north, etc.
		case fp::Direction::EAST  : maze_[x][y] |= 2; API::setWall(x, y, fp::Direction::EAST) ; break;
		case fp::Direction::SOUTH : maze_[x][y] |= 4; API::setWall(x, y, fp::Direction::SOUTH); break;
		case fp::Direction::WEST  : maze_[x][y] |= 8; API::setWall(x, y, fp::Direction::WEST) ; break;
	}
}

/** @brief Function isWall() uses stored wall data in the maze to output boolean indicating presence/absence of wall in a certain direction.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @param direction direction at (x,y) where the wall needs to be checked
 * @return bool true-if wall is present, else false
 */
bool fp::Maze::isWall(int x, int y, char direction)
{
	switch(direction){
		case fp::Direction::NORTH : return ((maze_[x][y] & 1) != 0) ; break;
		case fp::Direction::EAST  : return ((maze_[x][y] & 2) != 0) ; break;
		case fp::Direction::SOUTH : return ((maze_[x][y] & 4) != 0) ; break;
		case fp::Direction::WEST  : return ((maze_[x][y] & 8) != 0) ; break;
	}
	
	return false;	
}

/** @brief Function isCellValid() checks if the coordinates x,y are not out of bounds of the map. Used during algorithm execution.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @return bool true if cell is valid else false
 */
bool fp::Maze::isCellValid(int x, int y)
{
	if( x<0 or y<0 or x>WIDTH-1 or y>HEIGHT-1) return false;
	return true;
}

/** @brief Function setVisited() sets the visited status of the cell x,y. Used during algorithm execution.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @param status true if visited else false
 * @return void
 */
void fp::Maze::setVisited(int x, int y, bool status)
{
	if(not status){
		maze_[x][y]  &= (255-16);
	}
	else maze_[x][y] |= 16;
}

/** @brief Function isVisited() checks the visited status of the cell x,y. Used during algorithm execution.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @return void
 */
bool fp::Maze::isVisited(int x, int y)
{
	return ( (maze_[x][y] & 16) != 0 );
}

/** @brief Function isGoal() checks whether the input locations is one of the goal locations. Used during algorithm execution.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @return bool True if there x,y is one of the goal locations else false
 */
bool fp::Maze::isGoal(int x, int y)
{
	if( x==GLX and (y==GLY or y==GUY) ) return true;
	if( x==GUX and (y==GLY or y==GUY) ) return true;
	
	return false;
}

/** @brief Function getValue() returns the value of unsigned char stored in each cell. Used for debugging.
 * @param x x-location of the cell
 * @param y y-location of the cell
 * @return unsigned char value stored at x,y cell
 */ 
unsigned char fp::Maze::getValue(int x, int y)
{
	return maze_[x][y];
}

/** @brief Function colorCenter() colors the centers of the map. In this case, centers are the goal locations.
 * @param color indicates the color chosen for the center
 * @return void
 */
void fp::Maze::colorCenter(char color){
	for(int x=GLX; x<=GUX; ++x){
		for(int y=GLY; y<=GUY; ++y){
			API::setColor(x, y, color);
		}
	}
}

/** @brief Function textCenter() writes texts on the centers of the map. In this case, centers are the goal locations.
 * @param text indicates the text character chosen for the center
 * @return void
 */
void fp::Maze::textCenter(std::string text){
	for(int x=GLX; x<=GUX; ++x){
		for(int y=GLY; y<=GUY; ++y){
			API::setText(x, y, text);
		}
	}
}

/** @brief Function printMaze() prints the maze on the terminal for debugging purposes.
 * @return void
 */
void fp::Maze::printMaze()
{
	for(int y=HEIGHT-1; y>=0; --y){
		for(int x=0; x<WIDTH; ++x){
			std::cout << static_cast<int>(maze_[x][y]) << " ";
		}
		std::cout << std::endl;
	}
}

/** @brief Maze class destructor implementation
* @details deletes any pointers if created as attributes.
*/
fp::Maze::~Maze()
{
}