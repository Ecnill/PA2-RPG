/** @file hero.h
 * Header file of Hero class.
 * Header and implementation of Chuck class.
 *
 *  @author Julia Ostrokomorets <ostroiul@fit.cvut.cz>
*/
#ifndef HERO_H
#define HERO_H
#include <cstdlib>
#include <time.h>
#include "mapelement.h"
#define MIN_DAMAGE 20
/**********************************************************************************************/
/**
 * @brief The Hero class is descendant class of Entity
 * @detailed it uses for create hero; describes behaviour of hero on map
 */
class Hero : public Entity{
    public:
        /**
         * @brief Hero is implicit constructor
         * @detailed uses for create Chuck the Hero
         */
        Hero();
        /**
         * @brief Hero is constructor with parameters
         * @detailed uses for create custom Hero, parametrs are base entity's skills
         * @param name
         * @param health
         * @param damage
         * @param defence
         */
        Hero( const string &name, const int &health, const int &damage, const int &defence );
        /**
         * @brief ~Hero is virtual destruktor
         * @detailed for correct clean of this class and its descendants
         */
        virtual ~Hero(){}
        /**
         * @brief collide is behaviour hero when he collides some other object on game map
         * @param elem is object on map
         * @param map is game map
         * @param to is position where hero goes
         * @return true or false, if hero can or cannot move on this position
         */
        bool collide(shared_ptr<MapElement> elem, vector<shared_ptr<MapElement> > *map, int to);
        /**
         * @brief getSymbol is getter for symbol of objects on map
         * @return symbol
         */
        char getSymbol() const;
        /**
         * @brief getName is getter for name of hero
         * @return name
         */
        string getName();
        /**
         * @brief setDirection is setter for hero direction on map
         * @param dir is new direction for setting
         */
        void setDirection( int dir);
        /**
         * @brief getConutWhisky
         * @return count of whisky hero has
         */
        int getConutWhisky();
        /**
         * @brief getCountSword
         * @return count of sword hero has
         */
        int getCountSword();
        /**
         * @brief useWhisky is method for drinking whisky (adding health skill)
         */
        void useWhisky ();
        /**
         * @brief useSword is method for equipping sword (adding damage skill)
         */
        void useSword();
    protected:
        string name;
    private:
        int direction;
        int whisky;
        int sword;
};
/**********************************************************************************************/
/**
 * @brief The Chuck class
 */
class Chuck : public Hero{
    public:
        /**
         * @brief Chuck is implicit constructor, it sets base skills for Chuck the hero
         */
        Chuck(){
            health = 10000;
            damage = 10000;
            defence = 10000;
            name = "Chuck Norris";
        }
};
/**********************************************************************************************/
#endif // HERO_H
