// COLLIN JONES
// CSCI 1300
// NICHOLAS FARROW & DR KNOX
// FINAL PROJECT
// (DESCRIPTION AND USE IN .word FILE)

#include "enemy.cpp"
#include "player.cpp"
#include <cstdlib> // random #
#include <ctime>   // random #
#include <iostream>// "cin, cout"
#include <string>

using namespace std;

// Helper function that just displays the entire MAIN menu
void showMainMenu(){

    cout << " MAIN MENU: \n";
    cout << " 1. Fight\n";
    cout << " 2. Quit\n";
    cout << " 3. Wright your username to a text file\n";
    cout << " 4. Read Enemy Stats from File\n";
    return;

}

// Helper function that displays the entire FIGHT menu.
// Also gets the important variables from both the player and
// enemy classes.
void showFightMenu(player Player, enemy Enemy){

    cout << " \n FIGHT! \n";

    cout << " ------------------" << "         -----------------\n";
    cout << " PLAYER STATS: " << "       --    ENEMY STATS: \n";
    cout << " Health: " << Player.getHealth() << "          VS    Health: " << Enemy.getHealth() << "\n";
    cout << " Attack Power: " << Player.getDamage() << "     --    Attack Power: " << Enemy.getDamage() << "\n";
    cout << " Stamina: " << Player.getStamina() << "                Stamina: " << Enemy.getStamina() << "\n";
    cout << " Mana: " << Player.getMana() << "                   Mana: " << Enemy.getMana() << "\n";
    cout << " ------------------" << "         -----------------" << endl;
    cout << " What do you do?\n";
    cout << " 1. Light Attack (0 STAMINA)\n";
    cout << " 2. Strong Attack (4 STAMINA)\n";
    cout << " 3. Fire Attack (10 MANA) (Applies Burning Damage for 3 turns)\n";
    cout << " 4. Heal (5 MANA)\n";
    cout << " 5. Back to main menu" << endl;

    return;

}

int main(){

    srand(time(NULL));           // call only ONCE otherwise both Enemy and Player will generate the same random number
    bool quitMainMenu = false;  // bool controlling the MAIN menu
    bool enemyBurning = false; // bool controlling the Enemy Burning status
    int mainMenuOption, fightMenuOption;   // integer user choice for MAIN menu and FIGHT menu.
    int currentEnemyHealth, playerHealth; // integer Health for both enemy and player(used for updating their own data members)
    int enemyDieRoll; // Controls the opponents choice (random)
    int i = 0;

    while(!quitMainMenu){ // while the quitMainMenu bool is false, do this

        enemy Leeroy = enemy(100, 5, 20, 50);         // First enemy object
        enemy Fredrick = enemy(150, 10, 20, 50);     // Second enemy object
        player Collin = player(100, 10, 20, 50);    // Health, Damage, Stamina, Mana
        enemy enemyObject[2] = {Leeroy, Fredrick}; // ARRAY OF OBJECTS
        int enemyIndex = 0;                       // controls which enemy you are CURRENTLY fighting

        bool quitFightMenu = false; // Must be set otherwise you may never return to fight menu without an infinite loop
        showMainMenu();            // Calls the showMainMenu function which displays the main menu
        cout << " > ";
        cin >> mainMenuOption;   // Asks user for their MAIN menu input

        switch(mainMenuOption){ // Switch statement that takes in the variable mainMenuOption and decides which case to proceed with

            case 1: // If Case 1, then the user enters the FIGHT menu
                while(!quitFightMenu){

                    // This is so that if the enemy health is depleted, the index of the object array will be increased by one to fight the second enemy
                    if(enemyObject[0].health <= 0){
                        enemyObject[0].~enemy(); // Destructor that resets the enemy health to 1 (so it doesn't get caught in this if conditional for the second time.
                        cout << " First enemy defeated! Moving on the the second...\n";
                        enemyIndex += 1;
                    }
                    // This is so that if You die then you return to the main menu
                    if(Collin.health <= 0){
                        cout << " You have died! Now returning to main menu...\n\n\n\n\n\n\n";
                        break;
                    }
                    // On the impossible occasion that the second enemy is defeated, nothing interesting happens and you return to the main menu
                    if(enemyObject[1].health <= 0){
                        cout << " Last enemy has died! YOU WON! Now returning to main menu...\n\n\n\n\n\n\n" << endl;
                        break;
                    }
                    // displays the fight menu to the user
                    showFightMenu(Collin, enemyObject[enemyIndex]);
                    cout << " > ";
                    cin >> fightMenuOption;

                    switch(fightMenuOption){
                        // Case 1 is the 'Light Attack' option. If the user selects this,
                        // then the light attack member method is called passing the health of
                        // the current enemy through
                        // it returns the modified health (health minus the amount of damage of attack)
                        // and sets that equal to the enemy health variable in main.
                        // Then is sets that new health to the enemy
                        case 1:
                            currentEnemyHealth = Collin.lightAttack(enemyObject[enemyIndex].getHealth());
                            enemyObject[enemyIndex].setHealth(currentEnemyHealth);
                            break;
                        case 2:
                            if(Collin.stamina <= 0){ // If the use has no stamina, they cannot perform this action
                                cout << " Not enough STAMINA to perform this action.\n";
                                cout << " \n ENEMIES TURN \n";
                                break;
                            }
                            // Same as light attack
                            currentEnemyHealth = Collin.strongAttack(enemyObject[enemyIndex].getHealth());
                            enemyObject[enemyIndex].setHealth(currentEnemyHealth);
                            break;
                        case 3:
                            i = 0; // resets the burning damage index to 0
                            if(Collin.mana <= 0){ // if the user has no mana, they cannot perform this action
                                cout << " Not enough MANA to perform this action.\n";
                                cout << " \n ENEMIES TURN \n";
                                break;
                            }
                            // This one actually is more interesting, as it applies
                            // a 3 turned burning damage the enemy
                            // I had to create a bool that controlled the burning damage somehow
                            enemyBurning = Collin.magicFire(enemyBurning);
                            break;
                        case 4:
                            if(Collin.mana <= 0){ // If the use has no mana, they cannot perform this action
                                cout << " Not enough MANA to perform this action.\n";
                                cout << " \n ENEMIES TURN \n";
                                break;
                            }
                            // This method is very simple, all it does it return health to use
                            // granted the have enough stamina
                            // The enemy health is used so that if you roll a really low number
                            // Then you end up missing your heal and healing them
                            currentEnemyHealth = Collin.heal(enemyObject[enemyIndex].getHealth());
                            enemyObject[enemyIndex].setHealth(currentEnemyHealth);
                            break;

                        case 5:
                            // If the user chose number 5, then the switch statement is broken and the previous while loop is
                            // entered. while(!QUITMENU)
                            cout << "\n\n\n\n\n\n\n";
                            quitFightMenu = true; // Sets the bool controlling the Fight menu to true (quit)
                            break;

                    }
                    // Depending on what the index is at (initialized after performing fire attack)
                    // This will execute and keep the burning status up for 3 turns
                    if(i < 3){
                        enemyObject[enemyIndex].isBurning(enemyBurning);
                        i++;
                    }

                    // ENEMIES MOVE
                    if(fightMenuOption != 5){ // This is so that if the user EXITS the fight menu, then the 'enemy' doesn't retaliate as you're leaving

                        enemyDieRoll = rand() % 3 + 1; // Enemy has three options available (Light, Strong, and Jump)
                                                      // This will create a random number that the enemy will use to chose an action

                        switch(enemyDieRoll){
                            // If the enemy rolled a 1
                            case 1:
                                cout << " Enemy attempts a light attack! \n";                             // This is the same sequence of events as the players attack
                                playerHealth = enemyObject[enemyIndex].lightAttack(Collin.getHealth());
                                Collin.setHealth(playerHealth);
                                break;
                            // If the enemy rolled a 2
                            case 2:
                                if(enemyObject[enemyIndex].stamina <= 0){
                                    cout << " Enemy attempts a strong attack but failed due to lack of STAMINA!\n";
                                    cout << " \n ENEMIES TURN \n";
                                    break;
                                }
                                cout << " Enemy attempts a strong attack! \n";
                                playerHealth = enemyObject[enemyIndex].strongAttack(Collin.getHealth());
                                Collin.setHealth(playerHealth);
                                break;
                            // if the enemy rolled a 3
                            case 3:
                                if(enemyObject[enemyIndex].mana <= 0){
                                    cout << " Enemy attempted an arcane jump and failed due to lack of MANA!\n";
                                    break;
                                }
                                enemyObject[enemyIndex].jump();
                                break;
                        }
                    }
                }
                    // END ENEMY MOVE

                break;
            case 2: // user wants to quit
                quitMainMenu = true;
                break;
            case 3: // user wants to write to text file
                Collin.writeName("userName.txt");
                break;
            case 4: // user wants to read the enemy stats from a file
                cout << "\n Now creating test object...\n";
                enemy Test = enemy();
                Test.readFromFile("enemyStats.txt");
                cout << "\n File successfully loaded and read into test object.\n\n\n\n\n\n\n";

        }
    }
    return 0;
}
