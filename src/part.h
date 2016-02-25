/** @file part.h
 * Header file and implementation family of classes:
 * GamePart class -> CreateHeroPart class.
 *                -> MenuPart class -> HeroesPart class, AboutPart, ExitPart, UnusablePart, MainMenu.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef MENUPART_H
#define MENUPART_H
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <ncurses.h>
#include "data.h"
#define C_SKILL_POINTS 200          // skill points user can allocate
#define C_MIN_SKILLS    50          // skills game begins with
using namespace std;
/**********************************************************************************************/
/**
 * @brief The possible types of Game condition
 */
enum GameCondition{
    GAMECHUCK,
    GAMEHERO,
    CUSTUMHERO,
    ABOUT,
    HEROES,
    MAINMENU,
    ERROR,
    EXIT
};
/**********************************************************************************************/
/**
 * @brief The GamePart class is parent of all possible parts of the game
 * @detailed It is an abstruct class, top of classes' hierarchy
 */
class GamePart{
    public:
        /**
         * @brief ~GamePart is virtual destruktor
         */
        virtual ~GamePart(){}
        /**
         * @brief handleKey is abstruct method for inheritance by descendant classes
         * @param ch is value of pressed key
         * @return condition of the game
         */
        virtual GameCondition handleKey ( const int &ch ) = 0;
         /**
         * @brief getScreenData is abstruct method for inheritance by descendant classes
         * @return screen data to show
         */
        virtual shared_ptr<ScreenData>getScreenData() = 0;
};
/**********************************************************************************************/
/**
 * @brief The CreateHeroPart class
 * @detailed Descendant class of GamePart, uses for creation custom hero
 */
class CreateHeroPart: public GamePart {
    public:
        /**
         * @brief CreateHeroPart is implicit constructor, set skills for hero game begins with
         */
        CreateHeroPart( ) {
            currSkill = 0;
            points = C_SKILL_POINTS;
            skills.push_back(make_pair("Health",  C_MIN_SKILLS));
            skills.push_back(make_pair("Damage",  C_MIN_SKILLS));
            skills.push_back(make_pair("Defence", C_MIN_SKILLS));
        }
        /**
         * @brief handleKey is method for control keys and change hero's skills
         * @param ch is value of pressed key
         * @return condition of game chooses by key
         */
        GameCondition handleKey ( const int &ch ){
            if ( ch == KEY_UP ){
                if ( currSkill > 0)
                    currSkill--;
                else {
                    currSkill = skills.size() - 1;
                }
            }
            else if ( ch == KEY_DOWN ){
                if ( currSkill < (int)skills.size() - 1 ){
                    currSkill++;
               }
                else {
                    currSkill = 0;
                }
            }
            else if ( ch == '+' || ch == '>' ){
                if ( points != 0){
                    int i = currSkill;
                    points -= 10;
                    skills[i].second += 10;
                }
            }
            else if ( ch == '-' || ch == '<' ){
                int i = currSkill;
                if ( skills[i].second > 50){
                    points += 10;
                    skills[i].second -= 10;
                }
            }
            else if ( ch == '\n' ){
                return GAMEHERO;
            }
            else if ( ch == 27){
                return MAINMENU;
            }
            return CUSTUMHERO;
        }
        /**
         * @brief getSkills is getter for hero's skills
         * @return skills
         */
        vector<pair<string, int>> getSkills() const{
            return skills;
        }
        /**
        * @brief getScreenData is getter of hero creation data
        * @return creation data
        */
        shared_ptr<ScreenData>getScreenData() {
            shared_ptr<CreateHeroData> md ( new CreateHeroData ( skills, currSkill, points  ) );
            return md;
        }
    private:
        int points;
        int currSkill;
        vector<pair<string, int>> skills;       //health, damage, defence
};
/**********************************************************************************************/
/**
 * @brief The MenuPart class
 * @detailed Descendant class of GamePart, uses for forming of Game menus
 */
class MenuPart : public GamePart{
    public:

        /**
         * @brief ~MenuPart is virtual destruktor
         * @detailed for correct clean of this class and its descendants
         */
        virtual ~MenuPart(){}
        /**
         * @brief handleKey
         * @param ch
         * @return
         */
        virtual GameCondition handleKey( const int &ch ){
            if ( ch == KEY_DOWN ){
                if ( currentItem < (int)getMenuItems().size() - 1 ){
                    currentItem++;
               }
                else {
                    currentItem = 0;
                }
            }
            if ( ch == KEY_UP ){
                if ( currentItem > 0)
                    currentItem--;
                else {
                    currentItem = getMenuItems().size() - 1;
                }
            }
            if ( ch == 27 ){
                return MAINMENU;
            }
            return getCondition();
        }
        /**
         * @brief getMenuItems if getter of menu items
         * @return items of menu
         */
        virtual vector<string> getMenuItems() const {
            vector<string> menu;
            menu.push_back("MENU");
            return menu;                                            // this shouldn't returnd in this class
        }
         /**
         * @brief getCondition is getter of currient game condition
         * @return Main menu condition
         */
        virtual GameCondition getCondition() const{
            return MAINMENU;
        }
         /**
         * @brief getScreenData is getter of main menu data
         * @return main menu data
         */
        virtual shared_ptr<ScreenData> getScreenData(){
            shared_ptr<MenuData> md ( new MenuData ( getMenuItems(), currentItem ) );
            return md;
        }
    protected:
        int currentItem;
};
/**********************************************************************************************/
/**
 * @brief The HeroesPart class
 * @detailed Descendant class of MenuPart, uses for forming of Heros' Menu of the Game
 */
class HeroesPart : public MenuPart{
    public:
        /**
         * @brief HeroesPart is implicit constructor,creation Hero Menu Items
         */
        HeroesPart(){
            MenuPart::currentItem = 0;
            heroesName.push_back("Chuck Norris");
            heroesName.push_back("New Hero");
        }
        /**
         * @brief getMenuItems is getter of Hero Menu Items
         * @return items of hero menu
         */
        vector<string> getMenuItems() const{
            return heroesName;
        }
         /**
         * @brief handleKey is method for control keys and change game condition
         * @param ch is value of pressed key
         * @return condition of game (existed hero or new hero) chooses by key
         */
        GameCondition  handleKey( const int &ch ){
            if ( ch == '\n'){
                switch(currentItem){
                    case 0: {
                        return GAMECHUCK;
                    }
                    case 1:{
                        return CUSTUMHERO;
                    }
                }
            }
            return MenuPart::handleKey(ch);
        }
        /**
         * @brief getCondition is getter of currient game condition
         * @return game condition of Heroes menu part
         */
        GameCondition getCondition() const{
            return HEROES;
        }
    private:
        vector<string> heroesName;
};
/**********************************************************************************************/
/**
 * @brief The AboutPart class
 * @detailed Descendant class of MenuPart, uses for forming of About Part of the Game
 */
class AboutPart : public MenuPart {
    public:
        /**
         * @brief getScreenData is getter of screen data
         * @return message data with About text
         */
        virtual shared_ptr<ScreenData> getScreenData(){
            shared_ptr<MessageData> ms ( new MessageData ( "examples/about.txt" ) );
            return ms;
        }
};
/**********************************************************************************************/
/**
 * @brief The ExitPart class
 * @detailed Descendant class of MenuPart, uses for forming of Exit Part of the Game
 */
class ExitPart : public MenuPart {
    public:
        /**
         * @brief getScreenData is getter of screen data
         * @return message data with Goodbye text
         */
        virtual shared_ptr<ScreenData> getScreenData(){
            string bb = "Goodbye!\n";
            shared_ptr<MessageData> ms ( new MessageData ( bb ) );
            return ms;
        }
};
/**********************************************************************************************/
/**
 * @brief The ErrorPart class
 * @detailed Descendant class of GamePart, uses for forming of Error Part of the Game (if exception something catches, wrong map and so on)
 */
class ErrorPart : public GamePart{
    public:
        /**
         * @brief ErrorPart is implicit constructor
         * @detailed Use it once, for case if Game::getGamePart doesn't get part of game
         */
        ErrorPart (){
            str = "This part shouldn't shown.\n";
        }
        /**
         * @brief ErrorPart is constructor with parameters
         * @param str is message of error
         * @detailed use it for output all error messages about wrong map
         */
        ErrorPart ( string str){
            this->str = str;
        }
        /**
         * @brief getScreenData is getter of screen data
         * @return message data with reason of error
         */
        virtual shared_ptr<ScreenData> getScreenData(){
            shared_ptr<MessageData> ms ( new MessageData ( str ) );
            return ms;
        }
        /**
         * @brief handleKey is method for control keys and change condition of game
         * @param ch is value of pressed key
         * @return condition of Main Menu or Exit
         */
        virtual GameCondition handleKey ( const int &ch ){
            if ( ch == '\n') {
                return MAINMENU;
            }
            return EXIT;
        }
    private:
        string str;
};
/**********************************************************************************************/
/**
 * @brief The MainMenu class
 * @detailed Descendant class of MenuPart, uses for forming of Error Main Menu Part of the Game
 */
class MainMenu : public MenuPart {
    public:
         /**
         * @brief MainMenu is implicit constructor, creation Menu Items
         */
        MainMenu()  {
            menuItems.push_back("New Game");
            menuItems.push_back("About");
            menuItems.push_back("Exit");
            MenuPart::currentItem = 0;
        }
        /**
        * @brief handleKey
        * @param ch
        * @return
        */
       virtual GameCondition handleKey( const int &ch ){
            if (ch == '\n'){
                switch(currentItem){
                    case 0: return HEROES;
                    case 1: return ABOUT;
                    case 2: return EXIT;
                    default: break;
                }
            }
            return MenuPart::handleKey(ch);
        }
        /**
         * @brief getMenuItems is getter of menu items
         * @return items of menu
         */
        vector<string> getMenuItems() const{
            return menuItems;
        }
        /**
         * @brief getCondition is getter of currient game condition
         * @return condition of main menu
         */
        GameCondition getCondition() const{
            return MAINMENU;
        }
    private:
        vector<string> menuItems;
};
/**********************************************************************************************/
#endif // MENUPART_H
