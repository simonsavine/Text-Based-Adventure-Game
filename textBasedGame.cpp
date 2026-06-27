#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Player;

struct Enemy {

    int health;
    int damage;
    string name;

    Enemy (int h, int d, string n) : health(h), damage(d), name(n) {}

    // could the bus error be related to attack being virtual!?!

    virtual void attack(Player* player) = 0;

    virtual void randomCrit() = 0;

    virtual void dmgReset() = 0;

    string getName() { return name; }

    int getHealth() { return health; }

    int getDamage() { return damage; }

    virtual ~Enemy() {}

    virtual bool die(Player* player) = 0;
};

struct Player {

    int playerHealth;
    int playerDmg;
    string playerName;

    Player(int health = 150, int dmg = 5, string n = "") : playerHealth(health), playerDmg(dmg), playerName(n) {}

    void setName(const string& name) { playerName = name; }

    string getName() { return playerName; }

    void randomCrit() {
        srand(time(0));

        if (rand() % 100 < 25) {
            cout << playerName << " lands a CRITICAL HIT! " << endl;
            playerDmg *= 2;
        }

        else {
            playerDmg = 5;
        }
        
    }

    void attack(Enemy* enemy) {

        randomCrit();

        enemy->health -= playerDmg;

        cout << "You strike the " << enemy->name;
        cout << " and it now has " << enemy->getHealth() << " health! ";
        cout << "It is now the " << enemy->name << "'s turn to attack! " << endl;
    }

    void kill(Enemy* enemy) {

        // if player attack results in enemy dying, print out a msg

        if (enemy->health <= 0) {
            cout << "You have killed the " << enemy->getName() << endl;
        }
    }

    int takeDmg(Enemy* enemy) {

        playerHealth -= enemy->damage;

        cout << "The " << enemy->name << " hits you for " << enemy->damage << " damage!" << endl;

        return playerHealth;
    }

    bool die() {

        cout << "You have died, " << playerName << ". The land is doomed... Rest and live to save the world on another day! " << endl;
        cout << endl;
        return playerHealth <= 0;
    }

};

struct Goblin: public Enemy {

    Goblin(int h = 10, int d = 5, string n = "Goblin") : Enemy(h, d, n) {}

    string getName() { return name; }

    int getHealth() { return health; }

    int getDmg() { return damage; }

    void randomCrit() {
        srand(time(0));

        if (rand() % 100 < 90) {
            cout << "Goblin lands a CRITICAL HIT! " << endl;
            damage *= 2;
        }

        else {
            damage = 5;
        }
        
    }

    void dmgReset() {
        damage = 5;
    }

    void attack(Player* player) {

        randomCrit();

        player->takeDmg(this);

    }

    bool die(Player* player) {

        if (health <= 0) { cout << player->getName() << " has slayed the Goblin! Congratulations!" << endl; }

        return 0;
    }

};

struct Troll: public Enemy {

    Troll(int h = 15, int d = 8, string n = "Troll") : Enemy(h, d, n) {}

    string getName() { return name; }

    int getHealth() { return health; }

    int getDmg() { return damage; }

    void randomCrit() {
        srand(time(0));

        if (rand() % 100 < 10) {
            cout << "Troll lands a CRITICAL HIT! " << endl;
            damage *= 2;
        }

        else {
            damage = 8;
        }
    }

    void dmgReset() {
        damage = 8;
    }

    void attack(Player* player) {

        randomCrit();

        player->takeDmg(this);
    }

    bool die(Player* player) {

        if (health <= 0) {cout << player->getName() << " has slayed the Troll! Congratulations!" << endl;}

        return 0;
    }


};

struct Dragon: public Enemy {

    Dragon(int h = 30, int d = 20, string n = "Dragon") : Enemy(h, d, n) {}

    string getName() { return name; }

    int getHealth() { return health; }

    int getDmg() { return damage; }


    void randomCrit() {
        srand(time(0));

        if (rand() % 100 < 10) {
            cout << "Dragon lands a CRITICAL HIT! " << endl;
            damage *= 2;
        }

        else {
            damage = 20;
        }
    }

    void dmgReset() {
        damage = 20;
    }

    void attack(Player* player) {

        randomCrit();

        player->takeDmg(this);
    }

    bool die(Player* player) {

        if (health <= 0) {cout << player->getName() << " has slayed the Dragon! Congratulations!" << endl;}

        return 0;
    }

};

struct GameLoop {

    Player* player = new Player;
    Enemy* enemy;

    void randomEncounter(Player* player) {

        int roll = rand() % 100;

        if (roll < 50) {
            cout << player->getName() << " encounters a goblin, time to attack!" << endl;
            
            enemy = new Goblin();

            // set enemy type to Goblin
        }
        
        else if (roll < 85) {
            cout << player->getName() << " encounters a troll, time to attack!" << endl;

            enemy = new Troll();

            // set enemy type to Troll
        }

        else {
            cout << player->getName() << " encounters a dragon, time to attack!" << endl;

            enemy = new Dragon();

            // set enemy type to Dragon
        }
    }

    // function to start the game

    void story() {

        cout << endl;

        cout << "In a strange land where reality and fiction collide, you are a lone adventurer on a quest to rid ";
        cout << " this world of evil and malice.. " << endl;
        cout << endl;
        cout << "What is your name, brave adventurer? ";

        string name;

        cin >> name;

        cout << endl;

        cout << "Type c to move: ";

        char startInp;
        
        cin >> startInp;

        cout << endl;

        // random monsters appear along the way

        while (startInp != 'c') {
            cout << "Invalid input, try again: " << endl;
            cin >> startInp;
        }

        cout << endl;

        player->setName(name);

        randomEncounter(player);

        cout << "What are you going to do now? Type 'e' to exit or 'a' to attack: " << endl;

        char attack;

        while (attack != 'e') {

            cin >> attack;

            if (attack == 'e') {
                cout << endl;
                cout << "Ah, I see you are a coward.. " << endl;
                return;
            }

            if (attack != 'a') {
                cout << "Wrong input, try again: " << endl;
            }

            else {

                cout << endl;

                // player attacks enemy and changes enemy health!

                if (enemy->health > 0) {

                    // player side
                    player->attack(enemy);
                    cout << endl;

                    // enemy side

                    enemy->attack(player);
                    enemy->dmgReset();

                    cout << endl;
                    cout << player->getName() << " has " << player->playerHealth << " health remaining.. " << endl;
                    cout << "Type a to attack: " << endl;

                }

                else {
                    enemy->die(player);

                    cout << endl;

                    delete enemy;

                    enemy = nullptr;
                    randomEncounter(player);
                }


                if (player->playerHealth <= 0) {
                    cout << endl;

                    player->die();
                    delete player;
                    
                    return;
                }

            }
        }
    }
};

int main() {

    srand(time(0));

    GameLoop gm;

    gm.story();

    return 0;
}
