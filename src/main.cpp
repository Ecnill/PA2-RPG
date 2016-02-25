#include <memory>
#include <iostream>
#include "screencontroller.h"
#include "game.h"
/**********************************************************************************************/
int main( int argc, char **argv ){

    shared_ptr<Game> game;
    try{
        game = shared_ptr<Game> (new Game ( argc, argv ) ) ;
    } catch ( Exception &exc){
        cout << exc;
        return EXIT_FAILURE;
    }
    shared_ptr<ScreenController> sc ( new ScreenController );
    sc->graphicDriverOn();
    sc->processData( game->start() );
    int key = 0;

    do{
        key = getch();
        clear();
        sc->processData( game->handleKey(key) );
        refresh();
    } while( game->gameStopped() == false );
    getch();
    sc->graphicDriverOff();

    return EXIT_SUCCESS;
}
