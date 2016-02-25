/** @file hero.cpp
 * Implementation od Hero class
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
 */
#include "hero.h"
/**********************************************************************************************/
Hero::Hero(){
    direction = 0;
    whisky = 0;
    sword = 0;
}
/*********************************************************/
Hero::Hero( const string &name, const int &health, const int &damage, const int &defence ){
    this->name = name;
    this->health = health;
    this->damage = damage;
    this->defence = defence;
    direction = 0;
    whisky = 0;
    sword = 0;
}
bool Hero::collide(shared_ptr<MapElement> elem, vector<shared_ptr<MapElement> > *map, int to){
    if( elem->getSymbol() == '.' ){
        return true;
    }
    if (  dynamic_cast<Sword*>(elem.get()) ){
        map->at(to) = shared_ptr<MapElement>(new MapElement);
        sword++;
        return true;
    }
    if ( dynamic_cast<Thorn*>(elem.get()) ){
        map->at(to) = shared_ptr<MapElement>(new MapElement);
        health -= 20;
        return true;
    }
    if ( dynamic_cast<Whisky*>(elem.get()) ){
        map->at(to) = shared_ptr<MapElement>(new MapElement);
        whisky++;
        return true;
    }
    if ( Enemy *en = dynamic_cast<Enemy*>(elem.get()) ){       //damage +  random - defence
        int heroHlth = getHealth();
        int heroDmg = getDamage();
        int heroDfc = getDefence();
        int enHlth = en->getHealth();
        int enDmg = en->getDamage();
        int enDfc = en->getDefence();
        int heroFight = 0, enemyFigth = 0;
        srand (time(NULL));
        while ( heroHlth > 0 && enHlth > 0 ){
            enemyFigth = enDmg + 2*( rand() % enDmg ) - heroDfc;
            if ( enemyFigth < 0 ) {
                enemyFigth = MIN_DAMAGE;
            }
            heroHlth -= enemyFigth;
            heroFight = heroDmg + ( rand() % heroDmg ) - enDfc;
            if ( heroFight < 0 ) {
                heroFight = MIN_DAMAGE - 10;
            }
            enHlth -= heroFight;
        }
        if ( enHlth < 0 && heroHlth > 0) {
            map->at(to) = shared_ptr<MapElement>(new MapElement);
        }
        health = heroHlth;
        if ( heroHlth > 0 ){
            defence += en->getDamage() / 5 ;
        }
        return false;
    }
    return false;
}
/*********************************************************/
char Hero::getSymbol() const{
    switch(direction){
        case KEY_DOWN:
        case 's':       return 'v';
        case KEY_UP:
        case 'w':       return '^';
        case KEY_LEFT:
        case 'a':       return '<';
        case KEY_RIGHT:
        case 'd':       return '>';
    }
    return 'v';
}
/*********************************************************/
string Hero::getName(){
    return name;
}
/*********************************************************/
void Hero::setDirection( int dir){
    direction = dir;
}
/*********************************************************/
int Hero::getConutWhisky(){
    return whisky;
}
/*********************************************************/
int Hero::getCountSword(){
    return sword;
}
/*********************************************************/
void Hero::useWhisky (){
    if ( whisky > 0 ){
        whisky--;
        Entity::health += 50;
    }
}
/*********************************************************/
void Hero::useSword(){
    if ( sword > 0 ){
        sword--;
        damage += 20;
    }
}
