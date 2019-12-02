#include "api.h"
#include <cstdlib>
#include <iostream>

/** @brief Function mazeWidth() interacts with mms simulator to query mazeWidth and returns a int format of the returned value
 * @return int mazeWidth as returned from mms simulator
 */
int fp::API::mazeWidth() {
    std::cout << "mazeWidth" << std::endl;
    std::string response;
    std::cin >> response;
    return atoi(response.c_str());
}

/** @brief Function mazeHeight() interacts with mms simulator to query mazeHeight and returns a int format of the returned value
 * @return int mazeHeight as returned from mms simulator
 */
int fp::API::mazeHeight() {
    std::cout << "mazeHeight" << std::endl;
    std::string response;
    std::cin >> response;
    return atoi(response.c_str());
}

/** @brief Function wallFront() interacts with mms simulator to query if a wall is present in front of the mouse. 
 * This takes into account the direction of the mouse.
 * @return bool True if a wall is present else false.
 */
bool fp::API::wallFront() {
    std::cout << "wallFront" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @brief Function wallRight() interacts with mms simulator to query if a wall is present to the right of the mouse. 
 * This takes into account the direction of the mouse.
 * @return bool True if a wall is present else false.
 */
bool fp::API::wallRight() {
    std::cout << "wallRight" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @brief Function wallLeft() interacts with mms simulator to query if a wall is present to the left of the mouse. 
 * This takes into account the direction of the mouse.
 * @return bool True if a wall is present else false.
 */
bool fp::API::wallLeft() {
    std::cout << "wallLeft" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @brief Function moveForward() interacts with mms simulator to send a command to move the robot forward in it's current heading direction.
 * @return void
 */
void fp::API::moveForward() {
    std::cout << "moveForward" << std::endl;
    std::string response;
    std::cin >> response;
    if (response != "ack") {
        std::cerr << response << std::endl;
        throw;
    }
}

/** @brief Function turnRight() interacts with mms simulator to send a command to turn the robot 90 deg clockwise direction.
 * @return void
 */
void fp::API::turnRight() {
    std::cout << "turnRight" << std::endl;
    std::string ack;
    std::cin >> ack;
}

/** @brief Function turnLeft() interacts with mms simulator to send a command to turn the robot 90 deg anti-clockwise direction.
 * @return void
 */
void fp::API::turnLeft() {
    std::cout << "turnLeft" << std::endl;
    std::string ack;
    std::cin >> ack;
}

/** @brief Function setWall() interacts with mms simulator to send a command to set the wall at (x,y) cell in direction specified.
 * @param x x-location of the mouse in the maze
 * @param y y-location of the mouse in the maze
 * @param direction This direction is according to world-coordinates. ie. North means true North(upwards), etc.
 * @return void
 */
void fp::API::setWall(int x, int y, char direction) {
    std::cout << "setWall " << x << " " << y << " " << direction << std::endl;
}

/** @brief Function clearWall() interacts with mms simulator to send a command to clear wall at (x,y) cell in direction specified.
 * @param x x-location of the mouse in the maze
 * @param y y-location of the mouse in the maze
 * @param direction This direction is according to world-coordinates. ie. North means true North(upwards), etc.
 * @return void
 */
void fp::API::clearWall(int x, int y, char direction) {
    std::cout << "clearWall " << x << " " << y << " " << direction << std::endl;
}

/** @brief Function setColor() interacts with mms simulator to send a command to set a color at (x,y) cell.
 * @param x x-location of the mouse in the maze
 * @param y y-location of the mouse in the maze
 * @param color This is the color that needs to set at the specified location
 * @return void
 */
void fp::API::setColor(int x, int y, char color) {
    std::cout << "setColor " << x << " " << y << " " << color << std::endl;
}

/** @brief Function clearColor() interacts with mms simulator to send a command to clear color at (x,y) cell.
 * @param x x-location of the mouse in the maze
 * @param y y-location of the mouse in the maze
 * @return void
 */
void fp::API::clearColor(int x, int y) {
    std::cout << "clearColor " << x << " " << y << std::endl;
}

/** @brief Function clearAllColor() interacts with mms simulator to send a command to clear color throughout the maze.
 * @return void
 */
void fp::API::clearAllColor() {
    std::cout << "clearAllColor" << std::endl;
}

/** @brief Function setText() interacts with mms simulator to send a command to set a color at (x,y) cell.
 * @param x x-location of the mouse in the maze
 * @param y y-location of the mouse in the maze
 * @param text This is the text that needs to set at the specified location
 * @return void
 */
void fp::API::setText(int x, int y, const std::string& text) {
    std::cout << "setText " << x << " " << y << " " << text << std::endl;
}

/** @brief Function clearText() interacts with mms simulator to send a command to clear text at (x,y) cell.
 * @param x x-location of the mouse in the maze
 * @param y y-location of the mouse in the maze
 * @return void
 */
void fp::API::clearText(int x, int y) {
    std::cout << "clearText " << x << " " << y << std::endl;
}

/** @brief Function clearAllText() interacts with mms simulator to send a command to clear texts throughout the maze.
 * @return void
 */
void fp::API::clearAllText() {
    std::cout << "clearAllText" << std::endl;
}

/** @brief Function wasReset() interacts with mms simulator to send a command to query whether the maze was reset or not in the mms simulator.
 * @return bool True is maze was reset else false
*/
bool fp::API::wasReset() {
    std::cout << "wasReset" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @brief Function ackReset() interacts with mms simulator to check if the maze reset was acknoledged by the mms simulator or not.
 * @return void 
*/
void fp::API::ackReset() {
    std::cout << "ackReset" << std::endl;
    std::string ack;
    std::cin >> ack;
}