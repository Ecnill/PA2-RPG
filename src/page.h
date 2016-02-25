/** @file screencontroller.h
 * Header file and implementation family of classes:
 * ScreenPage -> MenuPage, CreateHeroPage, MapPage
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
 */
#ifndef PAGE_H
#define PAGE_H
#include <utility>
#include <vector>
#include <string>
#include "data.h"
using namespace std;
#define C_WIDTH 40                  // width size of camera, for shows part of map on screen
#define C_HEIGHT 20                 // height
/**********************************************************************************************/
/**
 * @brief The ScreenPage class
 * @detailed The Parent abstruct class of possible pages to show on screen
 */
class ScreenPage{
    public:
        /**
         * @brief ~ScreenPage is virtual destruktor
         */
        virtual ~ScreenPage(){}
         /**
         * @brief show is abstruct method to show pages on screen by descendant classes
         */
        virtual void show() const = 0;
};
/**********************************************************************************************/
/**
 * @brief The MenuPage class
 * @detailed Descendant class of ScreenPage, shows menu page
 */
class MenuPage : public  ScreenPage {
    public:
        /**
         * @brief MenuPage is constructor with parameters
         * @param md is menu data to show
         */
        MenuPage( const MenuData &md ) : md(md) { }
        /**
         * @brief show is method for show menu on screen
         * @detailed using nrurses functions
         */
        void show() const {
            attron(COLOR_PAIR(1));
            printw("========= MENU =========\n");
            for( int i = 0; i < (int)md.getMenuItems().size(); ++i ){
                if ( md.getCurrentMenuItem() == i) {
                    attron(COLOR_PAIR(2));
                } else {
                    attron(COLOR_PAIR(1));
                }
                printw("   %s  \n", md.getMenuItems()[i].c_str());
            }
            attron(COLOR_PAIR(1));
            printw ("========================\n");
        }
    private:
        MenuData md;
};
/**********************************************************************************************/
/**
 * @brief The MessagePage class
 * @detailed Descendant class of ScreenPage, shows message page
 */
class MessagePage : public ScreenPage {
    public:
         /**
         * @brief MessagePage
         * @brief MenuPage is constructor with parameters
         * @param msd is message data to show
         */
        MessagePage( const MessageData &msd ) : msd(msd) {}
        /**
         * @brief show is method for show message on screen
         */
        void show() const {
            printw("============================================\n");
            printw("%s", msd.getMessage().c_str());
            printw("============================================\n");
        }
    private:
        MessageData msd;
};
/**********************************************************************************************/
/**
 * @brief The CreateHeroPage class
 * @detailed Descendant class of ScreenPage, shows hero creation menu page
 */
class CreateHeroPage : public ScreenPage {
    public:
        /**
         * @brief CreateHeroPage is constructor with parameters
         * @param chd is creation hero's data to show
         */
        CreateHeroPage ( CreateHeroData &chd ) : chd(chd){}
        /**
         * @brief show is method for show creation menu of hero on screen
         */
        void show() const {
            printw("===============HERO CREATION=======================\n");
            for ( int i = 0; i < (int)chd.getSkills().size(); ++i ){
                 if ( chd.getCurrSkill() == i ){
                     attron(COLOR_PAIR(2));
                     printw( "%s: %d + -\n", chd.getSkills()[i].first.c_str(), chd.getSkills()[i].second );
                 } else{
                    attron(COLOR_PAIR(1));
                    printw( "%s: %d\n", chd.getSkills()[i].first.c_str(), chd.getSkills()[i].second );
                 }
            }
            attron(COLOR_PAIR(1));
            printw("\nLeft points: %d\n", chd.getPoints());
            printw("===================================================\n");
            printw("Use '+' (or '>') and '-' (or '<') keys to augment or diminish the Hero skills.\nPress ENTER to continue a game or ESC to come back at the Main Menu.\n\n");
        }
    private:
        CreateHeroData chd;
};
/**********************************************************************************************/
/**
 * @brief The MapPage class
 * @detailed Descendant class of ScreenPage, shows hero creation menu page
 */
class MapPage : public ScreenPage{
    public:
         /**
         * @brief MapPage is constructor with parameters
         * @param mpd is map data to show
         */
        MapPage ( const MapData &mpd) : mpd(mpd) {}
        /**
         * @brief show is method for show map and all hero's and game's states on screen
         */
        void show() const{
            Map *map = mpd.getMap();
//            int w = mpd.getHeroIndex() % map->getWidth();
//            int h = mpd.getHeroIndex() / map->getWidth();
//            printw("I'm on (%d, %d)\n", h, w);
            attron(A_BOLD);
            printw("%s\n", map->getHeroName().c_str() );
            attroff(A_BOLD);
            if ( map->getHeroHealth() < 0 ){
                printw("  Health:  0\n" );
            }else {
                printw("  Health:  %d\n", map->getHeroHealth() );
            }
            printw("  Damage:  %d\n", map->getHeroDamage() );
            printw("  Defence: %d\n", map->getHeroDefence() );
            printw("\nInventory:\n");
            printw("  Whisky: %d\n", map->getConutWhisky());
            printw("  Swords: %d\n", map->getCountSword());
            printw("\n\nEnemies to kill: ");
            attron(A_BOLD);
            printw("%d\n\n", map->getCountEnemies() );
            attroff(A_BOLD);
            string howTo = "\nUse arrows or WASD to move on.\nPress 'q' to show your task.\n'1' key to drink whisky (+health).\n'2' to equip sword (+damage).\n";
            howTo += "'L' to show map legend.\n\nPress ESC come back to main menu.\n";
            printw("%s\n", howTo.c_str());
            string border = "##";
            for (int i = 0; i < C_WIDTH && i < map->getWidth(); ++i ){
                border += '#';
            }
            int width = map->getWidth();
            int height = map->getHeight();
            int cX = 0, cY = 0;
            cX = mpd.getHeroIndex() % width - C_WIDTH/2;
            cY = mpd.getHeroIndex() / width - C_HEIGHT/2;
            if ( cX+C_WIDTH > width ){
                cX = width - C_WIDTH;
            }
            if ( cY+C_HEIGHT > height ){
                cY = height - C_HEIGHT;
            }
            if ( cX < 0 ) {
                cX = 0;
            }
            if ( cY < 0 ){
                cY = 0;
            }
            int posX = 35;
            int posY = 0;
            move(posY, posX);
            printw( "%s\n", border.c_str() );
            int tmpY = 0;
            for ( int y = cY; y < cY+C_HEIGHT && y < height; ++y ){
                move( posY+1+tmpY, posX);
                printw("#");
                for ( int x = cX; x < cX+C_WIDTH && x < width; x++ ){
                    char sym = (*map->getMap())[x+y*width]->getSymbol();
                    if ( sym == 'v' || sym == '<' ||
                         sym == '>' || sym == '^'){
                        attron(COLOR_PAIR(3));
                    }
                    else if (sym == 'e' ){
                        attron(COLOR_PAIR(4));
                    }
                    else if ( ( sym == 'w' ) || ( sym == 's' ) ){
                        attron(COLOR_PAIR(5));
                    }
                    printw("%c", sym );
                    attron(COLOR_PAIR(1));
                }
                printw("#\n");
                tmpY++;
            }
            move(posY+1+tmpY, posX);
            printw( "%s\n", border.c_str() );
        }
    private:
        MapData mpd;
};
/**********************************************************************************************/
#endif // PAGE_H
