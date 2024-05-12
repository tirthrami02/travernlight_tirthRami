// Original Code:
void Game::addItemToPlayer(const std::string &recipient, uint16_t itemId)
{
    Player *player = g_game.getPlayerByName(recipient);
    if (!player)
    {
        player = new Player(nullptr);
        if (!IOLoginData::loadPlayerByName(player, recipient))
        {
            return;
        }
    }

    Item *item = Item::CreateItem(itemId);
    if (!item)
    {
        return;
    }

    g_game.internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT);

    if (player->isOffline())
    {
        IOLoginData::savePlayer(player);
    }
}

// My Solution:
// It did not define any library or even there is not any definition of class and it's encapsulated functions.
// There is lot more to add to make it work.
// I am going to implement used class and it's methods in my solution.
// So, I will put general header called 'bits/stdc++.h' that contains most of the C++ functions and writing 'using namespace std' so that I shouldn't write 'std::' everywhere.
// My Code:

// Include necessary header
#include <bits/stdc++.h>
using namespace std;

// make a class named 'Game' with 'addItemToPlayer' method
// I also add arguments in this method as they used in original code.
class Game
{
public:
    void addItemToPlayer(const string &recipient, uint16_t itemId);
};

// make a class named 'Player' with some variables and function assigned as 'public'
// they have been implemented as they have been used in original code
class Player
{
public:
    string name;
    Player(string a)
    {
        this->name = a;
    }
    // creating getPlayerByName method to find player from database using his/her name
    static Player *getPlayerByName(const string &name);
    // creating a method to save player in our database
    void savePlayer();
    // boolean function to check whether player is offline or online
    bool isOffline();
    // use this Item's getInbox() method in our class
    Item *getInbox();
};

// make a class named Item with its used method in original code.
class Item
{
public:
    // creating an 'createItem' method and 'getInbox' method to create a new item with itemID and read inbox messages
    // we can define methods as per our need in the future.
    static Item *CreateItem(uint16_t itemId);
    static Item *getInbox();
};

// make class named 'IOLoginData' with its methods
class IOLoginData
{
public:
    // it takes player as an object and a name as a string as arguments -> work to load players by name on the screen [ I just guessed its functionality :) ]
    static bool loadPlayerByName(Player *player, const string &name);
    // as it name, it saves player as an whole object having object of a player as his argument.
    static void savePlayer(Player *player);
};

// made this class with its method because it has been used in original code.
class GameInstance
{
public:
    static int INDEX_WHEREEVER = -1;
    static int FLAG_NOLIMIT = 0;
    // pointer of a static object that return a pointer linked with object whose name is matches with argument passed in this function
    static Player *getPlayerByName(const string &name);
    // here, we are adding an Item in our dataset having properties like Item * pointer, ItemContainer pointer, index and flag.
    void internalAddItem(Item *itemContainer, Item *item, int index, int flag);
};
// make global object named g_game using class GamaInstance.
// this is the main object of a whole game.
GameInstance g_game;

// our main function from original code where different classes and methods have been used.

void Game::addItemToPlayer(const string &recipient, uint16_t itemId)
{
    // get player by searching name wise. 'recipient' passed as argument to match the name with.
    Player *player = g_game.getPlayerByName(recipient);
    // if player with recipient name is not exists than we create a new player with that name.
    if (!player)
    {
        // make the new Player with that name
        player = new Player(recipient);
        // if loading failed in the process, will get error
        if (!IOLoginData::loadPlayerByName(player, recipient))
        {
            cout << "Failed to load player: " << recipient << endl;
            // now deleting 'player' to save extra space from dynamic memory
            delete player;
            return;
        }
    }
    // now if player was already exists than we will skip above part and execute from below by making an Item object name 'item' and create it with its ID.
    Item *item = Item::CreateItem(itemId);
    // if item has value NULL than we return error inside below if condition
    if (!item)
    {
        cout << "Failed to create item with ID: " << itemId << endl;
        // and if our player ( new / old) is offline we delete his data to optimise memory
        if (player->isOffline())
        {
            delete player; // Clean up if player was dynamically allocated
        }
        return;
    }
    // if creating item and player have been successful than we are adding those data in the main database using below line.
    g_game.internalAddItem(player->getInbox(), item, GameInstance::INDEX_WHEREEVER, GameInstance::FLAG_NOLIMIT);
    // we have the data as player and item, but if our player goes offline, than save his/her data in our database
    if (player->isOffline())
    {
        IOLoginData::savePlayer(player);
        delete player; // Properly delete player to prevent memory leaks
    }
}

// That's how I improved the code in C++.