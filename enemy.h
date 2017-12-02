#pragma once
#include <iostream>
#include <string>

using namespace std;


class enemy{

    public:

        // data members
        int health;
        int damage;
        int stamina;
        int mana;
        string fileContents;

        // constructors
        enemy();
        enemy(int, int, int, int);
        ~enemy();

        // member methods
        int lightAttack(int);
        int strongAttack(int);
        void isBurning(bool);
        void jump();
        void readFromFile(string);

        // getters & setters
        void setHealth(int);
        int getHealth();
        void setDamage(int);
        int getDamage();
        void setStamina(int);
        int getStamina();
        void setMana(int);
        int getMana();

};
