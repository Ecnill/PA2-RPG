/** @file data.h
 * Header file and implementation family of classes:
 * ScreenData class -> MenuData class, MessageData class, MapData class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef DATA_H
#define DATA_H
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include "map.h"
using namespace std;
/**********************************************************************************************/
/**
 * @brief The Modes of screen data
 */
enum  ScreenDataType{
    MENU,               //<Show menu
    MESSAGE,            //<Show message
    MAP,                //<Show map
    CREATEHERO          //<Show creation of hero
};
/**********************************************************************************************/
/**
 * @brief The ScreenData class
 * @detailed The Parent class of possible data to show on screen
 */
class ScreenData{
    public:
        /**
         * @brief ~ScreenData is virtual destruktor
         * @detailed for correct clean of this class and its descendants
         */
        virtual ~ScreenData() {}
        ScreenDataType type;           //This type changes by descendant classes
        /**
         * @brief start
         * @detailed empty virtual method for inheritance by descendant classes
         */
        virtual void start(){}
};
/**********************************************************************************************/
/**
 * @brief The MenuData class
 * @detailed Descendant class of ScreenData, uses for forming of menu data
 */
class MenuData : public ScreenData {
    public:
        /**
         * @brief MenuData is constructor with parameters
         * @param menuItems has elements of menu
         * @param curr is position of choicing menu
         */
        MenuData( const vector<string> &menuItems, const int &curr ) {
            ScreenData::type = MENU;
            this->menuItems = menuItems;
            if ( curr < 0 ){
                currentMenuItem = 0;
            }else if ( curr > (int)menuItems.size() ){
                currentMenuItem = menuItems.size();
            }else{
                currentMenuItem = curr;
            }
        }
        /**
         * @brief getMenuItems is getter of menu items
         * @return elements of menu
         */
        vector<string> getMenuItems() const{
            return menuItems;
        }
        /**
         * @brief getCurrentMenuItem is getter of currient position in menu
         * @return currient position in menu
         */
        int getCurrentMenuItem() const{
            return currentMenuItem;
        }
    private:
        vector<string> menuItems;
        int currentMenuItem;
};
/**********************************************************************************************/
/**
 * @brief The MessageData class
 * @detailed Descendant class of ScreenData, uses for forming of message data
 */
class MessageData : public ScreenData {
    public:
        /**
         * @brief MessageData is constructor with parameters
         * @param fileName is name of file to read text of message from
         */
        MessageData ( const char *fileName ){
            fstream in (fileName);
            string textMess, line;
            while ( getline ( in, line) ){
                textMess += line;
                textMess += "\n";
            }
            ScreenData::type = MESSAGE;
            text = textMess;
            in.close();
        }
        /**
         * @brief MessageData is constructor with parameters
         * @param textMess is string to read text of message from
         */
        MessageData( const string &textMess){
            ScreenData::type = MESSAGE;
            text = textMess;
        }
        /**
         * @brief getMessage is getter of text of message
         * @return  message text
         */
        string getMessage() const{
            return text;
        }
    private:
        string text;
};
/**********************************************************************************************/
/**
 * @brief The MapData class
 * @detailed Descendant class of ScreenData, uses for forming of map data
 */
class MapData : public ScreenData{
    public:
         /**
         * @brief MapData is constructor with parameters
         * @param map is map to show
         * @param heroIndex os possition where should be hero on the map
         */
        MapData( Map *map, const int &heroIndex) : map(map), hero(heroIndex) {
            ScreenData::type = MAP;
        }
        /**
         * @brief getMap is getter of map
         * @return map
         */
        Map * getMap() const{
            return map;
        }
        /**
         * @brief getHeroIndex is getter of currient position of the Hero on the map
         * @return Hero position
         */
        const int &getHeroIndex() const{
            return hero;
        }
private:
        Map * map;
        const int &hero;
};
/**********************************************************************************************/
/**
 * @brief The CreateHeroData class
 * @detailed Descendant class of ScreenData, uses for forming of hero creation data
 */
class CreateHeroData : public ScreenData{
    public:
    /**
         * @brief CreateHeroData is constructor with parameters
         * @param skills are hero parametrs, consist of health, damage and defence
         * @param curr  is current skill to work with
         * @param points are how many skills can user augment
         */
        CreateHeroData( const vector<pair<string,int>> skills, const int &curr, const int &points ){
            ScreenData::type = CREATEHERO;
            this->skills = skills;
            this->points = points;
            if ( curr < 0 ){
                currSkill = 0;
            }else if ( curr > (int)skills.size() ){
                currSkill = skills.size();
            }else{
                currSkill = curr;
            }
        }
        /**
         * @brief getSkills is getter of hero skills
         * @return hero skills
         */
        vector<pair<string,int>> getSkills() const{
            return skills;
        }
        /**
         * @brief getCurrSkill is getter of currient position on menu
         * @return currient position
         */
        int getCurrSkill() const{
            return currSkill;
        }
        /**
         * @brief getPoints is getter of points
         * @return currient count of points
         */
        int getPoints() const{
            return points;
        }
    private:
        vector<pair<string,int>> skills;
        int points;
        int currSkill;
};
/**********************************************************************************************/
#endif // DATA_H
