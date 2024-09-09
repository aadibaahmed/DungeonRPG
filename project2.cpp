#include <iostream>
#include <cstdlib>
using namespace std;

class Enemy;

class Player {
private: 
  int player_health; 
  int credit;                                                                             //This will store the player's health(100 )and credit balance(0).

public:                                                                                   //This will set the player's health and credit currency.

  Player(int health, int credit) : player_health(health), credit(credit) {}
  void attack(Enemy& enemy);                                                              // this will attack an enemy and reduce their health.
  void damaged(int d) {
    player_health -= d;
  }
  void collect_treasure(int t){
    credit += t;
  }                                                                                      // when the enemy damages the player, it will subtract health.
  void block(){
    player_health += 3;
    cout << "You partially blocked the attack, Your health is now " << player_health << endl;
  }                                                                                            // blocks the enemy and regenerates health :D
  void flee(){
    cout << "You managed to run away" << endl;
  }                                                                                           // runs away from the enemy
  void negotiate(){
    cout << "You offered the enemy 2 credits, and he decided to let you go" << endl;
    credit -= 2;
  }                                                                                           // correctly negotiates and subtracts credits in return.

  void setHealth(int h) {
    player_health = h;                                                                            // sets player health
  }
  void setCredit(int c) {  
    credit = c;                                                                                // sets player credit
  }
  int getHealth() const{ return player_health; }                                              // gets the player health
  int getCredit() const{ return credit; }                                                     // gets player credit

  void print_stats() const{
    cout << "Player Health: " << player_health << endl;                                            // prints the players stats when called.
    cout << "You have: " << credit << " credits." << endl;
  }
};

class Enemy {		                                                                            //This class will be the base for all the enemies that appear in the                                                                                                       game.
protected:
int health;
int attack_power;

public:
  Enemy(int h, int ap) : health(h), attack_power(ap) { 

}                                                                                                //This is a overload constructor that will set the health and                                                                                                   attack power of the enemy.  
  void healthLoss(int d){ 
  health -= d;
    if (health < 0){
      health = 0;
    }
}                                                                                          // When the enemy is attacked by the player, the health reduces.
  int get_attack_power() const{
    return attack_power;  
  }

  virtual ~Enemy() = default;                                                                // this is a destructor.
  virtual void attack(Player& player1) = 0;                                                 // attacks players with their set attack damage.
  virtual void enemy_info() const = 0;                                                       // prints enemy stats
  int getHealth() const { return health; }                                                  //returns enemy health
  bool Alive() const {
    return health > 0;
  }
};

class Zombie : public Enemy {
public: 
  Zombie() : Enemy(30,5) { }

  void attack(Player& player1) override{
    cout << "Zombie bites the player!" << endl;
  }                                                                                   // will describe the attack and implement it.

  void enemy_info() const override{
    cout << "Zombie has " << health << " health and " << attack_power << " attack power." << endl;
  }
};

class Creeper : public Enemy {
public: 
  Creeper() : Enemy(20,8) { }
  void attack(Player& player1) override{
    cout << "Creeper explodes near you!" << endl;
  }                                                                                  // will describe the attack and implement it.
  void enemy_info() const override{
    cout << "Creeper has " << health << " health and " << attack_power << " attack power." << endl;
  }
};
class Mechon: public Enemy {
public: 
  Mechon() : Enemy(50,10) { }
  void attack(Player& player1) override{
    cout << "Mechon attacks you with a sword!" << endl;
  }                                                                                 // will describe the attack and implement it.
  void enemy_info() const override{
    cout << "Mechon has " << health << " health and " << attack_power << " attack power." << endl;
  }
};
class Event {                                                                        // this class provides the events that will occur in the game. It has options                                                                                         from treasures and enemies that will spawn in the                                                                                                                     dungeon for the player to interact with.                                                                                                
public:
  virtual ~Event() {}
  virtual void playEvent(Player& player1) = 0;
};
class enemyAppears : public Event{                                                  // this class will spawn an enemy in the dungeon. It is derived from the event                                                                                         class.
public:
  void playEvent(Player& player1) override{

    Enemy* spawnEnemy = nullptr;                                                     // creates an enemy pointer.
    
    int randomEnemy = rand() % 3;                                                     // generates a random number between 0 and 2.
    if(randomEnemy == 0){
      spawnEnemy = new Mechon();                                                      // specific enemies are spawned according to the random number given.
      cout << "A mechon has spawned!" << endl;
    }
    else if(randomEnemy == 1){
      spawnEnemy = new Zombie();
      cout << "A zombie has spawned!" << endl;
    }
    else{
      spawnEnemy = new Creeper();
      cout << "A creeper has spawned!" << endl;
    }

    spawnEnemy->enemy_info();                                                                // prints enemy stats. This creates a battle scene in which the enemies                                                                                              attack and the player is given choices to implement. This goes on until                                                                                              the player dies or the enemy is defeated.
    while(spawnEnemy->Alive() && player1.getHealth() > 0){

      player1.damaged(spawnEnemy->get_attack_power());

      if(player1.getHealth() > 0){
        
        spawnEnemy->attack(player1); 

        string choice;
        cout << "Do you want to attack, block, flee, or negotiate?" << endl;
        cin >> choice;

        if(choice == "attack"){
          cout << "You attacked the enemy!" << endl;
          spawnEnemy->healthLoss(20);
          spawnEnemy->enemy_info();
        }
        else if (choice == "block"){
          cout << "You chose to block the enemy!" << endl; 
          player1.block();
        }
        else if ( choice == "flee"){
          cout << "You chose to flee from the enemy!" << endl;
          spawnEnemy->healthLoss(100);
          player1.flee();
        }
        else if (choice == "negotiate"){
          cout << "You chose to negotiate with the enemy!" << endl;
          player1.negotiate();
          spawnEnemy->healthLoss(100);
        }
        else{
          cout << "Please choose a valid option." << endl;
        }
      }
    }
    
    delete spawnEnemy;
  }
};
class treasureAppears : public Event{
public:
  void playEvent(Player &player1) override{                                                                // another event that can occur is fidning treasure. This                                                                                                         class is derived from the event class, it generates a random                                                                                                         number from 1-10 and adds it to the player's credit balance.
    
    int randomTreasure = rand() % 10 +1;
    
    cout << "You found " << randomTreasure << " credits!" << endl;
    
    player1.collect_treasure(randomTreasure);                                                        // the player collects the credits.
  }
};

class mainGame{                                                                                                                    // this class is the main game                                                                                                                   class. It will handle the game loop and the events                                                                                                                                       that occur in the dungeon.
private:
  Player player1;                                                                                                                     // the player is asked to move                                                                                                                   around with w,a,s,d and each time they move they                                                                                   will encounter an event according to the random number generated. Either it                                                                                                                             will generate a treasure or an enemy.
  int goal;
public:
  mainGame(int StartHealth, int StartCredit, int credits_needed): player1(StartHealth, StartCredit), goal(credits_needed){
    player1.setHealth(StartHealth);
    player1.setCredit(StartCredit);
    srand(time(0));
  }
  void play(){ 
    while(player1.getHealth() > 0){
      player1.print_stats();

      char transverse;
      cout << "Enter 'W'to move foward, 'A' to move left, 'D' to move right, 'S' to move back" << endl;
      cin >> transverse;
      if(transverse == 'W' || 'w'){
        cout << "Player 1 has moved forward 10 steps" << endl;
      }
      else if(transverse == 'A'||'a'){
        cout << "Player 1 has turned left"  << endl;
      }
      else if(transverse == 'D'||'d'){
        cout << "Player 1 has turned right"  << endl;
      }
      else if(transverse == 'S'||'s'){
        cout << "Player 1 has turned around"  << endl;
      }
      Event* playerEvent;

      int newEvent = rand() % 2;
      if(newEvent == 0){
        playerEvent = new enemyAppears();
      }
      else{
        playerEvent = new treasureAppears();
      }
      playerEvent->playEvent(player1);
      delete playerEvent;

      if(player1.getCredit() >= goal){
        player1.print_stats();
        cout << "YOU HAVE ESCAPED THE DUNGEON! :D" << endl;
        break;
      }
      else if(player1.getHealth() <= 0){
        cout << "You died :( " << endl;
      }
  
    }
  
  }

};


int main() {                                                                                                   // The player is welcomed and it starts the game.
  srand(time(0));
  cout << "Welcome to escape the Dungeon!" << endl;
  cout << "In this game, you will move around a dungeon, experience enemies, and collect credits to escape." << endl;

  mainGame game(100,0,20);
  game.play();
  return 0;
}