/** @file game.h
 * Header file of Game class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef GAME_H
#define GAME_H
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>
#include "data.h"
#include "part.h"
#include "mappart.h"
using namespace std;
/**********************************************************************************************/
/**
 * @brief       The Game class
 * @detailed    This class represents the game aplication.
 *              It starts and finishes the Game;
 *              loads input files for building map and show a quest;
 *              chooses a part of Game, which is running.
 */
class Game{
  public:
    /**
     * @brief Game is constructor with parameters from command line
     * @param argc is count of command's line arguments
     * @param argv is char array of arguments
     * @throw exception if user doesn't load exactly two files (for map and quest) for correct game running
     */
    Game ( int argc, char **argv );
    /**
     * @brief getInpuArg is getter of command line arguments, which have formed in constructor
     * @return arguments from command line
     */
    vector<string> getInpuArg() const;
    /**
     * @brief start the Game by show actual data on screen
     * @return screen data
     */
    shared_ptr<ScreenData> start();
    /**
     * @brief gameStopped finished games if user chooses EXIT part in menu
     * @return finish or not finish
     */
    bool gameStopped();
    /**
     * @brief handleKey is method for control keys and choose currient Game Part, change condition
     * @param ch is value of pressed key
     * @return one of possible data to show on screen
     */
    shared_ptr<ScreenData> handleKey(const int &ch );
    /**
     * @brief getGamePart is calling from handleKey to get currient Game Part by condition
     * @param condition is for choosing necessary Game Part
     * @return Part of the Game by condition
     */
    shared_ptr<GamePart> getGamePart( const GameCondition &condition);
  private:
    GameCondition currentCondition;
    shared_ptr<MainMenu> mainMenu;
    shared_ptr<CreateHeroPart> createHero;
    shared_ptr<GamePart> currentPart;
    vector<string> arguments;
};
/**********************************************************************************************/
#endif // GAME_H
