/** @file screencontroller.h
 * Header file and implementation of  ScreenController class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
 */
#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H
#include <memory>
#include <ncurses.h>
#include "data.h"
#include "page.h"
using namespace std;
/**********************************************************************************************/
/**
 * @brief       The ScreenController class
 * @detailed    turn on and off necessary functions from ncurses.h for graphic support;
 *              processes currient data to show it on screen.
 */
class ScreenController{
    public:
        /**
         * @brief processData acceptes currient page and shows it
         * @param sd is screen data
         */
        void processData( shared_ptr<ScreenData> sd ){
            shared_ptr<ScreenPage> sp = getScreenPage(sd);
            sp->show();
        }
        /**
         * @brief graphicDriverOn is turn on and open all ncurses' functions
         */
        void graphicDriverOn(){
            initscr();                                  // initialization of ncurses
            clear();
            keypad(stdscr,TRUE);                        // turn on catch from keyboard
            start_color();                              // turn on colors
            curs_set(0);                                // turn off
            init_pair(1, COLOR_CYAN, COLOR_BLACK );     // numb of color pair, text, background
            init_pair(2, COLOR_BLACK, COLOR_CYAN);
            init_pair(3, COLOR_WHITE, COLOR_BLACK );
            init_pair(4, COLOR_RED, COLOR_BLACK );
            init_pair(5, COLOR_YELLOW, COLOR_BLACK );
        }
        /**
         * @brief graphicDriverOff is turn off and close all ncurses' functions
         */
        void graphicDriverOff(){
            refresh();
            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
            attroff(COLOR_PAIR(3));
            attroff(COLOR_PAIR(4));
            attroff(COLOR_PAIR(5));
            endwin();
        }
    private:
        /**
         * @brief getScreenPage is getter for currient page that has to show on the screen
         * @param sd is data to show on screeen
         * @return currient page
         */
        shared_ptr<ScreenPage> getScreenPage( shared_ptr<ScreenData> sd ) const{
            switch ( sd->type){
                case MENU:{
                    shared_ptr <MenuPage> mp ( new MenuPage ( static_cast<MenuData&>(*sd) ) );
                     return mp;
                }
                case MESSAGE:{
                    shared_ptr<MessagePage> ms ( new MessagePage ( static_cast<MessageData&>(*sd) ) );
                    return ms;
                }
                case MAP:{
                    shared_ptr <MapPage> mp ( new MapPage (static_cast<MapData&>(*sd) ) );
                    return mp;
                }
                case CREATEHERO:{
                    shared_ptr<CreateHeroPage> cp( new CreateHeroPage (static_cast<CreateHeroData&>(*sd) ) );
                    return cp;
                }
                default:{
                    break;
                }
            }
            //This should not shown, program have to choose one of case-screens
            MessageData errorMess ( "Undefined screenPage\n" );
            shared_ptr<MessagePage> ms ( new MessagePage ( errorMess ) );
            return ms;
         }
};
/**********************************************************************************************/
#endif // SCREENCONTROLLER_H
