/**
 * Room.h
 * by Daniel Fedorin
 * Contains three classes - one printable, with a name and description,
 * a Room class that extends printable and adds three methods - print exits and print items,
 * and delete item function,
 * and an Item, also printable, that has no special features.
 */
#pragma once
#include <vector>
#include <map>

#define CC_BLD "\033[1m"
#define CC_BLU "\033[34m"
#define CC_GRN "\033[32m"
#define CC_CLR "\033[0m"
#define CC_CYN "\033[36m"

using namespace std;

const char* const DIRS[] = { "NORTH", "EAST", "SOUTH", "WEST" };

class Printable {
 public:
  ~Printable();
  char* description;
  char* name;
  void print();
  void init(char const* name, char const* description);

};

class Item: public Printable {
 
};

class Room: public Printable { 
 public:
  void printext();
  void printitm();
  void delitm(Item* toDelete);
  map<char,Room*> rooms;
  vector<Item*> items;
};

