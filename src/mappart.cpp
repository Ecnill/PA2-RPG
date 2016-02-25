/** @file mappart.cpp
 * Implementation od MapPart class
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
 */
#include "mappart.h"
/**********************************************************************************************/
MapPart::MapPart() {
    activeMap = false;
    showLegend = false;
    isDead = false;
    isWin = false;
    data = shared_ptr<MapData>(nullptr);
}
/*********************************************************/
GameCondition MapPart::handleKey( const int &ch){
    currPos = getMap()->getHeroPos();
    showLegend = false;
    activeMap = true;
    int oldPos = currPos;
    getMap()->setHeroDirection(ch);
    int width = getMap()->getWidth();
    int height = getMap()->getHeight();
    shared_ptr<Hero> hero = getMap()->getHero();
    int hlth = hero->getHealth();
    if ( ( isDead == true) || (isWin == true) ) {
        return MAINMENU;
    }
    if ( hero->getHealth() < 0 ){
        activeMap = false;
        isDead = true;
    }
    if ( map->getCountEnemies() == 0 ){
        activeMap = false;
        isWin = true;
    }
    if ( ch == 27){
        return MAINMENU;
    }
    else if ( ch == KEY_UP || ch == 'w'){
        if ( currPos >= width ){
            currPos -= width;
        }
    }
    else if ( ch == KEY_DOWN || ch == 's' ){
        if ( (currPos + width) < ( height * width ) ){
            currPos += width;
        }
    }
    else if ( ch == KEY_LEFT || ch == 'a' ){
        if ( (currPos % width ) != 0 ){
            currPos--;
        }
    }
    else if ( ch == KEY_RIGHT || ch == 'd' ){
        if ( ((currPos+1) % width ) != 0 ){
            currPos++;
        }
    }
    else if ( ch == 'q' ){
        activeMap = false;
    }
    else if ( ch == '1' ){
        hero->useWhisky();
    }
    else if ( ch == '2' ){
        hero->useSword();
    }
    else if ( ch == 'l' || ch == 'L' ){
        activeMap = false;
        showLegend = true;
    }
    shared_ptr<MapElement> mapElem =  getMap()->getMap()->at(currPos);
    if ( !(currPos != oldPos && hero->collide( mapElem, getMap()->getMap(), currPos) ) ){
        if ( ( hlth > hero->getHealth() ) && (hero->getHealth() > 0) && ( mapElem->getSymbol() != '!') ){
            map->setCountEnemies();
        }
        currPos = oldPos;

    }else{
        getMap()-> moveHero(currPos);
    }
    return getCondition();
}
/*********************************************************/
shared_ptr<ScreenData> MapPart::getScreenData(){
    if ( activeMap == true){
        if ( data.get() == nullptr ){
            MapData *mD = new MapData(getMap().get(), currPos);
            data = shared_ptr<MapData>(mD);
        }
    }
    else {
        shared_ptr<MessageData> ms = nullptr;
        string msg = "";
        msg.clear();
        if (  isWin == true){
            msg = "Congratulation, you win!\n";
            ms = shared_ptr<MessageData>(new MessageData ( msg ) );
        }
        else if ( isDead == true ){
            msg = "Sorry, you died\n";
            ms = shared_ptr<MessageData>(new MessageData ( msg ) );
        }
        else if ( showLegend == true ){
            msg = "e = enemy you have to kill;\nw = whisky you can drink to augment your health;\ns = sword you can use to augment your damage;\n";
            msg += "! = thorn, be careful, it's pain for you;\n# = barrier you cannot pass. Really. I don't fool you.\n\n(Press any key to continue...)\n";
            ms = shared_ptr<MessageData>(new MessageData ( msg ) );
        }
       else {
            ms = shared_ptr<MessageData> (new MessageData ( arguments[1].c_str() ) );
        }
        return ms;
    }
    return data;
}
/*********************************************************/
shared_ptr<Map> MapPart::getMap(){
    if (map == NULL) {
        map =  shared_ptr<Map>( new Map( arguments[0], this->createHero() ) );
    }
    return map;
}
/*********************************************************/
