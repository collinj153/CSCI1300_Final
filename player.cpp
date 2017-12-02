#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include "player.h"


using namespace std;

// CONSTRUCTORS
//--------------
// default
player::player(){
    health = 100;
    damage = 10;
    stamina = 20;
    mana = 50;
}
player::player(int newHealth, int newDamage, int newStamina, int newMana){
    health = newHealth;
    damage = newDamage;
    stamina = newStamina;
    mana = newMana;
}
player::~player(){
    health = 1; // reset player health to break infinite loop
}

// GETTERS & SETTERS
//-------------------
void player::setHealth(int newHealth){
    health = newHealth;
    return;
}
int player::getHealth(){
    return health;
}
void player::setDamage(int newDamage){
    damage = newDamage;
    return;
}
int player::getDamage(){
    return damage;
}
void player::setStamina(int newStamina){
    stamina = newStamina;
    return;
}
int player::getStamina(){
    return stamina;
}
void player::setMana(int newMana){
    mana = newMana;
    return;
}
int player::getMana(){
    return mana;
}
// METHODS
//--------

// Light attack function which I briefly discussed in
// main.cpp. This function will take in the enemies health as a
// parameter. A die will be rolled (several times to randomize
// the die roll between the player and enemy) and based on the roll,
// (ie, 2 will miss, 1 will backfire, 3-12 will hit), it will determine
// which action to proceed with. If it hits the enemy, then the variable
// we passed in will me subtracted by the amount of damage the player can do.
// it returns the enemies health.
int player::lightAttack(int enemyHealth){

    int dieRoll, j = 0, i = 10;

    while(j < i){ // extra random
        dieRoll = rand() % 12 + 1;
        j++;
    }
    cout << "\n\n\n\n\n Your die Roll is... " << dieRoll << endl;

    if(dieRoll >= 3){
        cout << " You dealt " << damage << " damage to enemy.\n" << endl;
        enemyHealth -= damage;
    }
    else if(dieRoll == 1){
        cout << " You became confused and beefed it.\n" << endl;
        cout << " " << damage << " damage was dealt to player." << endl;
        health -= damage;
    }
    else{
        cout << " Missed!" << endl;
    }
    return enemyHealth;
}
// This function the same exact layout as the light attack,
// just with added damage (more risk too in fear of attacking yourself)
int player::strongAttack(int enemyHealth){

    cout << "\n\n\n\n\n 4 STAMINA was used in strong attack.\n";
    stamina -= 4;
    int dieRoll, j = 0, i = 5;

    while(j < i){ // extra random
        dieRoll = rand() % 12 + 1;
        j++;
    }
    cout << " Your die Roll is..." << dieRoll << endl;

    if(dieRoll >= 3){
        cout << " You dealt " << (damage+3) << " damage to enemy." << endl;
        enemyHealth -= (damage+3);
    }
    else if(dieRoll == 1){
        cout << " You became confused and beefed it.\n" << endl;
        cout << " " << (damage+3) << " damage was dealt to player." << endl;
        health -= (damage+3);
    }
    else{
        cout << " Missed!" << endl;
    }
    return enemyHealth;
}
// This function behaves similarly to light and strong attack
// (in the sense that the die rolls work the same), except that
// this function will take in a bool that controls the enemies burning status.
// if the die roll is a hit, then the bool is set to true and returned.
// otherwise it will miss or backfire (except the player will only receive
// a burst of damage).
int player::magicFire(bool statusBurning){
    cout << "\n\n\n\n\n 10 MANA was used for performing Fire Attack.\n";
    mana -= 10;
    int dieRoll = 0;

    for(int i = 0; i< 10; i++){
        dieRoll = rand() % 12 + 1;
    }
    cout << " Your die Roll is..." << dieRoll << endl;

    if(dieRoll >= 3){
        cout << " You applied burning damage to the enemy for three turns.\n";
        statusBurning = true;
    }
    else if(dieRoll == 1){
        cout << " You became confused and beefed it.\n" << endl;
        cout << " " << (damage-5) << " damage was dealt to player." << endl;
        health -= (damage-5);
    }
    else{
        cout << " Missed!" << endl;
    }
    return statusBurning;

}
// the heal function behaves similarly to the light and strong attack
// (in the sense that the die rolls work the same). The enemies health
// is the parameter for this function because if the player misses, then
// then they will heal the enemy by some. Returns the enemy health.
int player::heal(int enemyHealth){
    cout << "\n\n\n\n\n\n 5 MANA was used for performing Heal.\n";
    mana -= 5;

    int dieRoll = 0;
    for(int i = 0; i< 10; i++){
        dieRoll = rand() % 12 + 1;
    }

    cout << " Your die Roll is..." << dieRoll << endl;

    if(dieRoll >= 3){
        cout << " You healed yourself for 15 health.\n";
        health += 15;
    }
    else if(dieRoll == 1){
        cout << " Your heal missed you and healed the enemy!\n" << endl;
        cout << " " << " 15 HEALTH was returned to the enemy." << endl;
        enemyHealth += 3;
    }
    else{
        cout << " Heal missed!" << endl;
    }
    return enemyHealth;
}
// The write name function will just take in the name of a file,
// ask the user for their name, and write that name to the file.
int player::writeName(string fileName){


    cout << " Please enter your name: \n";
    cout << " > ";
    cin >> fileContents;

    ofstream outFile(fileName.c_str());
    while(outFile.is_open()){
        outFile << fileContents << "\n";
        outFile.close();
    }
    cout << " File was successfully written to.\n";
    cout << " Now returning to main menu...\n\n\n\n\n\n\n\n\n" << endl;
    return 0;

}

