/** @file mapelement.h
 * Header file and implementation family of classes:
 * MapElement class -> Barrier class, Whisky class, Sword class,
 * Entity class -> Enemy class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef MAPELEMENT_H
#define MAPELEMENT_H
#include <memory>
#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;
/**********************************************************************************************/
/**
 * @brief The possible types of Heroes in the Game
 */
enum HeroType{
    CHUCK,
    NEWHERO
};
/**********************************************************************************************/
/**
 * @brief The MapElement class
 * @detailed The Parent class of possible elements on map
 */
class MapElement{
    public:
        /**
         * @brief ~MapElement is virtual destruktor
         * @detailed for correct clean of this class and its descendants
         */
        virtual ~MapElement(){}
        /**
         * @brief getSymbol is virtual method for inheritance by descendant classes
         * @return symbol of empty place on map
         */
        virtual char getSymbol() const{
            return '.';
        }
};
/**********************************************************************************************/
/**
 * @brief The Barrier class
 */
class Barrier : public MapElement{
    public:
        /**
         * @brief getSymbol is getter for symbol on map
         * @return symbol of barrier on map
         */
        char getSymbol() const{
            return '#';
        }
};
/**********************************************************************************************/
/**
 * @brief The Thorn class
 */
class Thorn : public MapElement {
    public:
        /**
         * @brief getSymbol is getter for symbol on map
         * @return symbol of thorn on map
         */
        char getSymbol() const{
            return '!';
        }
};
/**********************************************************************************************/
/**
 * @brief The Whisky class
 */
class Whisky : public MapElement{
    public:
        /**
         * @brief getSymbol is getter for symbol on map
         * @return symbol of whisky on map
         */
        char getSymbol() const{
            return 'w';
        }
};
/**********************************************************************************************/
/**
 * @brief The Sword class
 */
class Sword : public MapElement{
    public:
        /**
         * @brief getSymbol is getter for symbol on map
         * @return symbol of sword on map
         */
        char getSymbol() const{
            return 's';
        }
};
/**********************************************************************************************/
/**
 * @brief The Entity class is paretn class for classes Hero and Enemy
 * @detailed Hero ane Enemy have the same skills as health, defence and damage
 */
class Entity : public MapElement{
    public:
        /**
         * @brief Entity is implicit constructor
         */
        Entity() : health(0), defence(0), damage(0){}
        /**
         * @brief ~Entity is virtual destruktor
         * @detailed for correct clean of this class and its descendants
         */
        virtual ~Entity(){}
        /**
         * @brief getSymbol is getter for symbol on map
         * @return symbol of entity on map ('v' as hero, 'e' as enemy)
         */
        virtual char getSymbol() const { return MapElement::getSymbol(); }
        /**
         * @brief getHealth is getter for health of entity
         * @return health of entity
         */
        int getHealth() const{
            return health;
        }
        /**
         * @brief getDamage is getter for damage of entity
         * @return damage of entity
         */
        int getDamage() const{
            return damage;
        }
        /**
         * @brief getDefence is getter for defence of entity
         * @return defence of entity
         */
        int getDefence() const{
            return defence;
        }
    protected:
        int health;
        int defence;
        int damage;
};
/**********************************************************************************************/
/**
 * @brief The Enemy class
 * @detailed Enemy has health, defence and damage skills from parent class Entity
 */
class Enemy : public Entity {
    public:
        /**
         * @brief getSymbol is getter for symbol on map
         * @return symbol of enemy on map
         */
        char getSymbol() const{
            return 'e';
        }
        /**
         * @brief setDamage is setter for enemy's damage
         * @param dmg  is damage to set
         */
        void setDamage( int dmg ){
            damage = dmg;
        }
        /**
         * @brief setDefence  is setter for enemy's defence
         * @param dfnc is defence to set
         */
        void setDefence( int dfnc ){
            defence = dfnc;
        }
        /**
         * @brief setHealth  is setter for enemy's health
         * @param hlth  is health to set
         */
        void setHealth (int hlth ){
            health = hlth;
        }
};
#endif // MAPELEMENT_H
