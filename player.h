#include <string>
#include <iostream>

using namespace std;

class player{

    public:

        // data members
        int health;
        int damage;
        int stamina;
        int mana;
        string fileContents;

        // constructors
        player();
        player(int, int, int, int);
        ~player();

        // member methods
        int lightAttack(int);
        int strongAttack(int);
        int magicFire(bool);
        int heal(int);
        int writeName(string);

        //  getters & setters
        void setHealth(int);
        int getHealth();
        void setDamage(int);
        int getDamage();
        void setStamina(int);
        int getStamina();
        void setMana(int);
        int getMana();
};
