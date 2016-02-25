/** @file mappart.h
 * Header file of MapPart class.
 * Header and implementation of ChuckPart class.
 * Header and implementation of HeroPart class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef MAPPART_H
#define MAPPART_H
#include <fstream>
#include "part.h"
using namespace std;
/**********************************************************************************************/
/**
 * @brief The MapPart is abstruct class
 * @detailed Descendant class of GamePart, uses for building map
 */
class MapPart : public GamePart{
    public:
         /**
         * @brief MapPart is implicit constructor
         */
        MapPart();
        /**
         * @brief getCondition is abstruct method
         * @return nothing
         */
        virtual GameCondition getCondition() = 0;
        /**
         * @brief handleKey is abstruct method
         * @param ch
         * @return nothing
         */
        virtual GameCondition handleKey( const int &ch);
        /**
         * @brief createHero
         * @return
         */
        virtual shared_ptr<Hero> createHero() = 0;
        /**
         * @brief getScreenData is getter od currient screen data
         * @return nothing
         */
        shared_ptr<ScreenData> getScreenData();
        /**
         * @brief getMap is getter of Map
         * @return map
         */
        shared_ptr<Map> getMap();
    protected:
        vector<string> arguments;
    private:
        bool activeMap;
        bool showLegend;
        bool isDead;
        bool isWin;
        shared_ptr<Map> map;
        shared_ptr<MapData> data;
        int currPos;
};
/**********************************************************************************************/
/**
 * @brief The ChuckPart class
 * @detailed Descendant class of MapPart, main hero in game
 */
class ChuckPart : public MapPart{
    public:
        /**
         * @brief ChuckPart is is constructor with parameters
         * @param arg are arguments from command line to build map and show quest
         */
        ChuckPart( vector<string> &arg ){
            MapPart::arguments = arg;
        }
        /**
         * @brief getCondition is getter of currient condition
         * @return condition of Chuck Game
         */
        GameCondition getCondition(){
            return GAMECHUCK;
        }
        /**
         * @brief createHero makes Chuck the hero
         * @return point on hero
         */
        shared_ptr<Hero> createHero(){
            shared_ptr<Chuck> chuck ( new Chuck );
            return chuck;
        }
};
/**********************************************************************************************/
/**
 * @brief The HeroPart class
 * @detailed Descendant class of MapPart, custom hero in game
 */
class HeroPart : public MapPart{
    public:
        /**
         * @brief HeroPart is is constructor with parameters
         * @param arg are arguments from command line to build map and show quest
         * @param skills are setting by user hero's parametrs
         */
        HeroPart ( vector<string> &arg, vector<pair<string, int>> skills){
            MapPart::arguments = arg;
            for ( int i = 0; i < (int)skills.size(); ++i ){
                if (  skills[i].first == "Health" ){
                    health =  skills[i].second;
                }
                else if ( skills[i].first == "Damage" ){
                    damage = skills[i].second;
                }
                else if ( skills[i].first == "Defence"){
                    defence = skills[i].second;
                }
            }
        }
        /**
         * @brief getCondition is getter of currient condition
         * @return condition of custom Game
         */
        GameCondition getCondition(){
           return GAMEHERO;
        }
        /**
         * @brief createHero makes custom hero
         * @return point on hero
         */
        shared_ptr<Hero> createHero(){
            shared_ptr<Hero> hero ( new Hero ("The Best Hero ever", health, damage, defence) );
            return hero;
        }
    private:
        int health, damage, defence;
};
#endif // MAPPART_H
