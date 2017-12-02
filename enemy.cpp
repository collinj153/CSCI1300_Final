#include <iostream>
#include <string>
#include <cstdlib> // random numbers
#include <ctime>   // random numbers
#include <fstream> // file stream
#include <sstream> // string streaming
#include "enemy.h"



using namespace std;

// Default constructor
enemy::enemy(){
    health = 100;
    damage = 10;
    stamina = 20;
    mana = 50;
}
// Constructor with four parameters
enemy::enemy(int newHealth, int newDamage, int newStamina, int newMana){
    health = newHealth;
    damage = newDamage;
    stamina = newStamina;
    mana = newMana;
}
// Enemy destructor
enemy::~enemy(){
    health = 1; // sets health greater than 0
}

// GETTERS & SETTERS
void enemy::setHealth(int newHealth){
    health = newHealth;
    return;
}
int enemy::getHealth(){
    return health;
}
void enemy::setDamage(int newDamage){
    damage = newDamage;
    return;

}
int enemy::getDamage(){
    return damage;
}
void enemy::setStamina(int newStamina){
    stamina = newStamina;
    return;
}
int enemy::getStamina(){
    return stamina;
}
void enemy::setMana(int newMana){
    mana = newMana;
    return;
}
int enemy::getMana(){
    return mana;
}

// Light attack
int enemy::lightAttack(int playerHealth){

    int dieRoll, j = 0, i = 7;

    while(j < i){ // extra random     // Creates a random die roll multiple times for added randomness
        dieRoll = rand() % 12 + 1;
        j++;
    }
    cout << " Enemy die Roll is..." << dieRoll << endl;

    if(dieRoll >= 3){ // If the die roll was greater than 3
        cout << " Enemy dealt " << damage << " damage to player\n" << endl;
        playerHealth -= damage; // The player health variable is subtracted by the damage of the enemy
    }
    else if(dieRoll == 1){ // If the die roll was a 1, the enemy will attack itself
        cout << " Enemy became confused and beefed it.\n" << endl;
        cout << " " << damage << " damage was dealt to enemy!\n" << endl;
        health -= damage;
    }
    else{ // If the die roll was anything else (a 2), the enemy will miss
        cout << " Missed!\n" << endl;
    }
    return playerHealth;
}

// This function the same exact layout as the light attack,
// just with added damage (more risk too in fear of attacking yourself)
int enemy::strongAttack(int playerHealth){

    stamina -= 4;
    int dieRoll, j = 0, i = 4;

    while(j < i){ // extra random
        dieRoll = rand() % 12 + 1;
        j++;
    }
    cout << " Enemy die Roll is..." << dieRoll << endl;

    if(dieRoll >= 3){
        cout << " Enemy dealt " << (damage+3) << " damage to player.\n" << endl;
        playerHealth -= (damage+3);
    }
    else if(dieRoll == 1){
        cout << " Enemy became confused and beefed it. \n" << endl;
        cout << " " << (damage+3) << " damage was dealt to enemy. \n" << endl;
        playerHealth -= (damage+3);
    }
    else{
        cout << " Missed!\n" << endl;
    }
    return playerHealth;
}
// This function determines whether thew enemy has the burning status or not
void enemy::isBurning(bool burningS){
    if(burningS == true){ // If the burningStatus variable is true
        health -= 7; // The enemy takes 7 damage
        cout << " 7 BURNING damage has been done to enemy!\n";
    }
    return;
}
// The enemy attempts a jump (makes the game easier for the player)
void enemy::jump(){
    cout << " Enemy attempts to jump and... nothing happens!\n";
    return;
}
// This function will create a test object and populate its parameters with
// data read from a file
void enemy::readFromFile(string filename){
    cout << " Now reading content from enemy stats file...\n";
    string line, healthStr, damageStr, staminaStr, manaStr; // to hold the strings from the file
    int healthF, damageF, staminaF, manaF; // to hold the integer conversions
    ifstream inFile(filename.c_str()); // creates an inFile stream
    while(inFile.is_open()){ // While that file is open, do this code
        while(getline(inFile, line)){
            istringstream c(line);              // Puts the first line in the text file into a string stream
            getline(c, healthStr, ',');        // The next few lines of code will be parsing the text file into
            istringstream convert(healthStr); // individual strings, which will then be streamed to be able to
            convert >> healthF;              // convert to ints. I had issues with 'stoi' as I had to include a comment
            getline(c, damageStr, ',');     // in my compiler settings to get it to work. Not ideal. So I found you can stream and convert.
            istringstream convert2(damageStr);
            convert2 >> damageF;
            getline(c, staminaStr, ',');
            istringstream convert3(staminaStr);
            convert3 >> staminaF;
            getline(c, manaStr);
            istringstream convert4(manaStr);
            convert4 >> manaF;

        }
        inFile.close(); // Closes the file
    }
    enemy test = enemy(healthF, damageF, staminaF, manaF); // Populates the test object with the variables we pulled from the text file
    cout << " This enemy has the stats: \n";
    cout << " HEALTH: " << test.health << "\n";
    cout << " ATTACK POWER: " << test.damage << "\n";
    cout << " STAMINA: " << test.stamina << "\n";
    cout << " MANA: " << test.mana << "\n\n\n\n\n";

}
