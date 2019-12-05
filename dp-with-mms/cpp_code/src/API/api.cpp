//! \file api.cpp

#include "api.h"
#include <cstdlib>
#include <iostream>

/** @details mazeWidth function requests maze width from API and returns
 * maze width information. Response becomes a constant string to verify response was received from API
 * @return int mazeWidth returns integer with maze width for analysis
 */
int fp::API::mazeWidth() {
    std::cout << "mazeWidth" << std::endl;
    std::string response;
    std::cin >> response;
    return atoi(response.c_str());
}

/** @details mazeHeight function requests maze height from API and returns 
 * maze height information. Response becomes constant string to verify response was received from API
 * @return int mazeHeight returns integer with maze height for analysis
 */
int fp::API::mazeHeight() {
    std::cout << "mazeHeight" << std::endl;
    std::string response;
    std::cin >> response;
    return atoi(response.c_str());
}

/** @details wallFront function checks for wall infront of robot based on current heading response becomes a constant string to verify response was received from API
 * @return API wallFront returns boolean to identify if forward path is clear or blocked.
 * True is returned if wall is present.
 */
bool fp::API::wallFront() {
    std::cout << "wallFront" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @details wallRight function checks for wall to right of robot based on current heading response becomes a constant string to verify response was received from API.
 * @return API wallRight returns boolean to identify if right path is clear or blocked.
 * True is returned if wall is present.
 */
bool fp::API::wallRight() {
    std::cout << "wallRight" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @details wallLeft function checks for wall to left of robot based on current heading response becomes a constant string to verify response was received from API.
 * @return API wallLeft returns boolean to identify if left path is clear or blocked.
 * True is returned if wall is present.
 */
bool fp::API::wallLeft() {
    std::cout << "wallLeft" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @details moveForward function moves robot position forward if path is clear response is constant string to verify response was received from API after
 * action is completed.
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

/** @details turnRight function rotates robot clockwise if rotation is needed response is constant string to verify response was received from API after
 * action is completed.
 */
void fp::API::turnRight() {
    std::cout << "turnRight" << std::endl;
    std::string ack;
    std::cin >> ack;
}

/** @details turnLeft function rotates robot counter-clockwise if rotation is needed response is constant string to verify response was received from API after
 * action is completed.
 */
void fp::API::turnLeft() {
    std::cout << "turnLeft" << std::endl;
    std::string ack;
    std::cin >> ack;
}

/** @details setWall function sets wall in system memory at the location and direction around
 * current position
 * @param x: Current X position
 * @param y: Current Y position
 * @param direction: Desired heading
 */
void fp::API::setWall(int x, int y, char direction) {
    std::cout << "setWall " << x << " " << y << " " << direction << std::endl;
}

/** @details clearWall function clears wall at specified position.
 * @param x: Current X position
 * @param y: Current Y position
 * @param direction: Desired heading
 */
void fp::API::clearWall(int x, int y, char direction) {
    std::cout << "clearWall " << x << " " << y << " " << direction << std::endl;
}

/** @details setColor function defines wall color for specified wall position. This can be used to
 * identify discovered walls during movement.
 * @param x: Current X position
 * @param y: Current Y position
 * @param color: Desired heading
 */
void fp::API::setColor(int x, int y, char color) {
    std::cout << "setColor " << x << " " << y << " " << color << std::endl;
}

/** @details clearColor function removes defined wall color at specific location.
 * @param x: Current X position
 * @param y: Current Y position
 */
void fp::API::clearColor(int x, int y) {
    std::cout << "clearColor " << x << " " << y << std::endl;
}

/** @details clearAllColor function removes defined wall color at all locations.
 */
void fp::API::clearAllColor() {
    std::cout << "clearAllColor" << std::endl;
}

/** @details setText function uses API feature to write text at specific x,y cell position.
 * Can be used to number specific cells or assign weight values if weighted search methods are used.
 * @param x: x-location
 * @param y: y-location
 * @param text: String text to be written in cell position X,Y
 */
void fp::API::setText(int x, int y, const std::string& text) {
    std::cout << "setText " << x << " " << y << " " << text << std::endl;
}

/** @details clearText function uses API feature to clear text at specific x,y cell position.
 */
void fp::API::clearText(int x, int y) {
    std::cout << "clearText " << x << " " << y << std::endl;
}

/** @details clearAllText function uses API feature to clear text at all cell position.
 */
void fp::API::clearAllText() {
    std::cout << "clearAllText" << std::endl;
}

/** @details wasReset function uses API feature to reset maze simulator. Can be used
 * in case of crash to reset path search and restart from beginning.
 * Function will provide response when process is completed.
 * @return boolean true if system reset was completed
 */
bool fp::API::wasReset() {
    std::cout << "wasReset" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

/** @details ackReset function resets ack response from API. Used for verification when API
 * functions are completed.
 */
void fp::API::ackReset() {
    std::cout << "ackReset" << std::endl;
    std::string ack;
    std::cin >> ack;
}