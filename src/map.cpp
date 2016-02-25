/** @file map.cpp
 * Implementation od Game class
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
 */
#include "map.h"
/**********************************************************************************************/
Map::Map( const string &inputArg, shared_ptr<Hero> hero ){
    fstream in ( inputArg.c_str() );
    countEnemies = 0;
    map = new vector<shared_ptr<MapElement>>();
    shared_ptr <Hero> hr = hero;
    string line;
    stringstream ss;
    getline(in, line);                          // read map size at first
    size_t bracket1 = line.find_first_of("[");
    size_t comma = line.find_first_of(",");
    size_t bracket2 = line.find_last_of("]");
    if ( bracket1 == string::npos || comma == string::npos || bracket2 == string::npos ){
        throw Exception ("Error in syntax (missing '[', ',' or ']') at map size");
    }
    ss << line.substr(bracket1+1, comma-bracket1-1);
    ss >> height;
    clearStrStream ( ss );
    ss << line.substr(comma+1, bracket2-comma-1);
    ss >> width;
    clearStrStream ( ss );
    string aboutKeyMess = "\n\nPlease check your files.\n\nPress ENTER to come back to Main Menu.\nPress any key to EXIT the Game.\n";
    string errorMess = "";
    errorMess.clear();
    if ( (height < 0) ||  (width < 0) ){
        errorMess =  "Error in map size" + aboutKeyMess;
        throw Exception ( errorMess );
    }
    for ( int i = 0; i < height*width; ++i ){
        (*map).push_back(shared_ptr <MapElement>(new MapElement));
    }
    int countHero = 0;
    while ( getline(in, line) ){                    // read all map elements
       size_t quote1 = line.find_first_of("\"");
       if ( quote1 == string::npos ){
           continue;
       }
       size_t quote2 = line.find_first_of("\"", quote1+1);
       if ( quote1 == string::npos || quote2 == string::npos  ){
           errorMess = "Error in syntax (missing \" at object type)" + aboutKeyMess;
           throw Exception ( errorMess );
       }
       string type = line.substr(quote1+1, quote2-quote1-1);
       bracket1 = line.find_first_of("[", quote2+1);
       comma = line.find_first_of(",", bracket1+1);
       bracket2 = line.find_first_of("]", comma+1);
       if ( bracket1 == string::npos || comma == string::npos || bracket2 == string::npos ){
           errorMess = "Error in syntax (missing '[', ',' or ']') at object size" + aboutKeyMess;
           throw Exception ( errorMess );
       }
       int w = 0, h = 0;
       ss << line.substr(bracket1+1, comma-1);
       ss >> h;
       clearStrStream ( ss );
       ss << line.substr(comma+1, bracket2-comma-1);
       ss >> w;
       clearStrStream ( ss );
       int index = w+h*width;
       if ( (*map)[index]->getSymbol() != '.' ){
           errorMess = "Object can't be on same position as another one" + aboutKeyMess;
           throw Exception ( errorMess );
       }
       if ( (h < 0) ||  (w < 0) || (index > width*height) ){
           errorMess = "Object can't be out of map bounds" +  aboutKeyMess;
           throw Exception ( errorMess );
       }
       typeMapObj tp;
       if ( type == "barrier"){
           tp = BARRIER;
       }
       else if ( type == "whisky" ) {
           tp = WHISKY;
       }
       else if (type == "sword" ) {
           tp = SWORD;
       }else if ( type == "thorn" ){
           tp = THORN;
       }
       else if ( type == "enemy" ){
           tp = ENEMY;
           bracket1 = line.find_first_of("(");
           bracket2 = line.find_first_of(")");
           comma = line.find_first_of(",", bracket1);
           size_t comma2 = line.find_first_of(",", comma+1);
           if ( bracket1 == string::npos || comma == string::npos || bracket2 == string::npos || comma2 == string::npos ){
               errorMess = "Error in syntax (missing '(', ',' or ')') at enemy creation" + aboutKeyMess;
               throw Exception ( errorMess );
           }
           int hlth = 0, dmg = 0, dfnc = 0;
           ss << line.substr(bracket1+1, comma-1);
           ss >> hlth;
           clearStrStream ( ss );
           ss << line.substr( comma+1, comma2-1);
           ss >> dmg;
           clearStrStream ( ss );
           ss << line.substr( comma2+1, bracket2-1);
           ss >> dfnc;
           clearStrStream ( ss );
           if ( hlth <= 0 || dmg <= 0 || dfnc <= 0){
               errorMess = "Enemies can't have characteristics <= 0" + aboutKeyMess;
               throw Exception ( errorMess );
           }
           shared_ptr <Enemy> en (new Enemy);
           (*map)[index] = en;
           en->setHealth(hlth);
           en->setDamage(dmg);
           en->setDefence(dfnc);
           countEnemies++;
       }else if ( type == "hero"){
           if ( countHero > 0 ){
               errorMess = "There can be only one hero" + aboutKeyMess;
               throw Exception ( errorMess );
           }
           tp = HERO;
           countHero++;
       }
       else {
           errorMess = "Unknown object type" + aboutKeyMess;
           throw Exception ( errorMess );
       }
       createMapObject( tp, index, hr );
    }
    in.close();
}
void Map::clearStrStream( stringstream &ss){
    ss.str("");
    ss.clear();
}
/*********************************************************/
Map::~Map(){
    delete map;
}
/*********************************************************/
void Map::createMapObject( typeMapObj type, int index, shared_ptr<Hero> hr ){
    switch( type){
        case BARRIER: {
            shared_ptr <Barrier> br( new Barrier );
            (*map)[index] = br;
            return;
        }
        case THORN:{
            shared_ptr <Thorn> th ( new Thorn );
            (*map)[index] = th;
            return;
        }
        case WHISKY:{
            shared_ptr<Whisky> ws ( new Whisky );
            (*map)[index] = ws;
            return;
        }
        case SWORD:{
            shared_ptr <Sword> sw ( new Sword );
            (*map)[index] = sw;
            return;
        }
        case HERO:{
            (*map)[index] = hr;
            hero = hr;
            heroPos = index;
            dirHero = hr;
            return;
        }
        default: return;
    };
}
/*********************************************************/
int Map::getHeight() const{
    return height;
}
/*********************************************************/
int Map::getWidth() const{
    return width;
}
/*********************************************************/
int Map::getCountEnemies(){
    return countEnemies;
}
/*********************************************************/
void Map::setCountEnemies(){
    countEnemies--;
}
/*********************************************************/
vector<shared_ptr<MapElement> > *Map::getMap() const{
    return map;
}
/*********************************************************/
void Map::moveHero( int newPos ){
    (*map)[heroPos] = (*map)[newPos];
    (*map)[newPos] = hero;
    heroPos = newPos;
    hero = (*map)[newPos];
}
/*********************************************************/
void Map::setHeroDirection ( const int &newDirection ) {
    dirHero->setDirection( newDirection );
}
/*********************************************************/
string Map::getHeroName(){
    return dirHero->getName();
}
/*********************************************************/
int Map::getHeroHealth(){
    return dirHero->getHealth();
}
/*********************************************************/
int Map::getHeroDamage(){
    return dirHero->getDamage();
}
/*********************************************************/
int Map::getHeroDefence(){
 return dirHero->getDefence();
}
/*********************************************************/
int Map::getConutWhisky(){
    return dirHero->getConutWhisky();
}
/*********************************************************/
int Map::getCountSword(){
    return dirHero->getCountSword();
}
/*********************************************************/
shared_ptr<Hero> Map::getHero() const{
    return dirHero;
}
/*********************************************************/
int Map::getHeroPos(){
    return heroPos;
}
