/**
 * Room.cpp
 * by Daniel Fedorin
 * Function definitions for Room.h
 */

#include <iostream>
#include <cstring>
#include "room.h"

using namespace std;

Printable::~Printable(){
  delete[] this->description;
  delete[] this->name;
}

void Printable::print(){
  cout << CC_BLD << CC_BLU << (this->name) << CC_CLR << endl;
  cout << (this->description) << endl;
}

void Printable::init(char const* name, char const* description){
  this->description = new char[strlen(description) + 1];
  this->name = new char[strlen(name) + 1];
  strcpy(this->description, description);
  strcpy(this->name, name);
}

void Room::printext(){
  cout << CC_GRN << "Exits: " << CC_CLR;
  for(int i = 0; i < 4; i ++){
    if(this->rooms.count(i) > 0){
      cout << CC_CYN << (DIRS[i]) << CC_CLR << ": " << (this->rooms[i]->name) << " ";
    }
  }
  cout << endl;
}

void Room::printitm(){
  cout << CC_GRN << "Items: " << CC_CLR;
  vector<Item*>::iterator it = this->items.begin();
  while(it != this->items.end()){
    cout << ((*it)->name) << " ";
    it++;
  }
  cout << endl;
}

void Room::delitm(Item* toDelete){
  vector<Item*>::iterator it = this->items.begin();
  while(it != (this->items.end())){
    if((*it) == toDelete) {
      this->items.erase(it);
      return;
    }
    it++;
  }
}
