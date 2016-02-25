/** @file game.cpp
 * Implementation od Game class
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
 */
#include "game.h"
/**********************************************************************************************/
Game::Game ( int argc, char **argv ){
    //don't need to add argv[0], because first argument is run file
    if ( argc != 3 ){
        throw Exception ("Please run game with these two files: MAP=examples/map.txt and QUEST=examples/quest.txt\n");
    }
    fstream mapFile (argv[1]);
    fstream questFile (argv[2]);
    if ( (mapFile.is_open() == false) || (mapFile.good() == false) ){
        throw Exception ("Missing map file.\n");
    }
    if ( (questFile.is_open() == false) || (questFile.good() == false) ){
        throw Exception ("Missing quest file.\n");
    }
    arguments.push_back(argv[1]);
    arguments.push_back(argv[2]);
    mapFile.close();
    questFile.close();
    mainMenu = NULL;
    createHero = NULL;
    currentCondition = MAINMENU;
    currentPart = getGamePart ( currentCondition );
}
/*********************************************************/
shared_ptr<ScreenData> Game::start(){
    return currentPart->getScreenData();
}
/*********************************************************/
shared_ptr<ScreenData> Game::handleKey( const int &ch ){
    GameCondition condition = currentCondition;
    try{
        condition  = currentPart->handleKey(ch);
    } catch ( Exception &exc ){
        condition = currentCondition = ERROR;
        currentPart = shared_ptr<ErrorPart>  ( new ErrorPart ( exc.getMessage() ) );
    }
    if ( condition != currentCondition ){
        currentCondition = condition;
        currentPart = getGamePart(currentCondition);
    }
    return currentPart->getScreenData();
}
/*********************************************************/
shared_ptr<GamePart> Game::getGamePart( const GameCondition &condition){
    if ( condition == MAINMENU ){
        if ( mainMenu == NULL ){
            mainMenu = shared_ptr<MainMenu>( new MainMenu() );
        }
        return mainMenu;
    }
    if ( condition == ABOUT ){
        shared_ptr<AboutPart> ab ( new AboutPart );
        return ab;
    }
    if ( condition == HEROES ){
        shared_ptr<HeroesPart> hp ( new HeroesPart );
        return hp;
    }
    if ( condition == CUSTUMHERO){
        createHero = shared_ptr<CreateHeroPart> ( new CreateHeroPart() );
        return createHero;
    }
    if ( condition == GAMECHUCK ){
        shared_ptr<ChuckPart> cp ( new ChuckPart ( arguments ) );
        return cp;
    }
    if ( condition == GAMEHERO ){
        shared_ptr<HeroPart> hp ( new HeroPart ( arguments, createHero->getSkills()) );
        return hp;
    }
    if ( condition == EXIT ){
        shared_ptr<ExitPart> ex ( new ExitPart );
        return ex;
    }
    shared_ptr<ErrorPart> unusableScreen ( new ErrorPart );
    return unusableScreen;
}
/*********************************************************/
bool Game::gameStopped(){
    return ( currentCondition == EXIT );
}
/*********************************************************/
