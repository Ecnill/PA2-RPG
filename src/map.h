/** @file map.h
 * Header file of Map class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include "mapelement.h"
#include "hero.h"
#include "exception.h"
using namespace std;
/**
 * @brief The possible types of elements on map
 */
enum typeMapObj{
    BARRIER,
    THORN,
    WHISKY,
    SWORD,
    HERO,
    ENEMY
};
/**********************************************************************************************/
/**
 * @brief The Map class is a map of the game world
 * @detailed    it reads data from file;
 *              knows how many items are on it;
 *              moves hero and sets his direction;
 */
class Map{
    public:
        /**
         * @brief Map is is constructor with parameters
         * @param inputArg are arguments from command line
         * @param hero is pointr at hero on map
         */
        Map( const string &inputArg, shared_ptr<Hero> hero );
        /**
         * @brief ~Map is destruktor, it cleans all MapElement type's objects
         */
        ~Map();
        /**
         * @brief getHeight is getter for map's height
         * @return height of map
         */
        int getHeight() const;
        /**
         * @brief getWidth is getter for map's width
         * @return width of map
         */
        int getWidth() const;
        /**
         * @brief getMap is getter for map consists of map elements
         * @return map
         */
        vector<shared_ptr <MapElement>> *getMap() const;
        /**
         * @brief moveHero is moving hero on new position
         * @param newPos is position where hero comes
         */
        void moveHero( int newPos );
        /**
         * @brief setHeroDirection is setter for hero's direction
         * @param newDirection is new direction to set
         */
        void setHeroDirection ( const int &newDirection );
        /**
         * @brief getHeroName is getter for hero's name
         * @return hero's name
         */
        string getHeroName();
        /**
         * @brief getHeroHealth is getter for hero's health
         * @return hero's health
         */
        int getHeroHealth();
        /**
         * @brief getHeroDamage is getter for hero's damage
         * @return hero's damage
         */
        int getHeroDamage();
        /**
         * @brief getHeroDefence is getter for hero's defence
         * @return hero's defence
         */
        int getHeroDefence();
        /**
         * @brief getHero is getter for Hero
         * @return pointer at Hero as a object of class Hero
         */
        shared_ptr<Hero> getHero() const;
        /**
         * @brief getCountEnemies is getter for currient count of the enemies on map
         * @return currient count of the enemies
         */
        int getCountEnemies();
        /**
         * @brief setCountEnemies is setter for decrement, if hero is alive after fight
         */
        void setCountEnemies();
        /**
         * @brief getConutWhisky is getter for currient count of whisky on map
         * @return currient count of whisky
         */
        int getConutWhisky();
        /**
         * @brief getCountSword is getter for currient count of swords on map
         * @return currient count of swords
         */
        int getCountSword();
        /**
         * @brief getHeroPos is getter for currient position (index) of Hero on map
         * @return index of Hero on map
         */
        int getHeroPos();
private:
        int height, width;                          // map size
        vector <shared_ptr <MapElement>> *map;
        shared_ptr <MapElement> hero;
        shared_ptr <Hero> dirHero;
        int heroPos;                                // index hero on the map
        int countEnemies;
        /**
         * @brief createMapObject is method for creation by type on necessary place
         * @param type of element
         * @param index on map
         * @param hr is pointer to Hero for possibility always remember where hero is
         */
        void createMapObject( typeMapObj type, int index, shared_ptr<Hero> hr );
        void clearStrStream( stringstream &ss);

};
/**********************************************************************************************/
#endif // MAP_H
