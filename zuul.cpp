/**
 * Zuul.cpp
 * By Daniel Fedorin
 * Main class of the zuul game, contains helper functions for Zuul.
 */
#include <iostream>
#include <cstring>
#include "room.h"

using namespace std;

void strupper(char* str);
void delitm(Item* itm, vector<Item*>* delFrom);
int dirtoindex(char* dir);
int wordlen(char*, int start);
Room* createrooms(vector<Room*> &rooms, vector<Item*> &items);
Item* finditm(char const* name, vector<Item*>* items);

int main(){
  vector<Item*> items;
  vector<Room*> cleanRooms;
  vector<Item*> cleanItems;
  Room* currentRoom = createrooms(cleanRooms, cleanItems);
  bool playing = true;
  char input[100];
  currentRoom->print();
  while(playing){
    while(cin.peek() == '\n') cin.ignore();
    cin.get(input, 100, '\n');

    //Parse command
    int commandlen = wordlen(input, 0);
    char* command = new char[commandlen + 1];
    command[commandlen] = '\0';
    strncpy(command, input, commandlen);
    strupper(command);


    if(strcmp(command, "QUIT") == 0){
      playing = false;
    } else if(strcmp(command, "GO") == 0){
      int arglen = wordlen(input, commandlen + 1);
      char* dir = new char[arglen + 1];
      dir[arglen] = '\0';
      strncpy(dir, input + commandlen + 1, arglen);
      strupper(dir);

      int diri = dirtoindex(dir);
      if(diri == -1) {
	       cout << "No such direction." << endl;
      } else if(currentRoom->rooms.count(diri) == 0) {
	       cout << "No exit in this direction." << endl;
      } else {
	       cout << "OK." << endl;
	       currentRoom = currentRoom->rooms[diri];
      }

      delete[] dir;
    } else if(strcmp(command, "ROOM") == 0){
      currentRoom->print();
    } else if(strcmp(command, "ITEMS") == 0){
      currentRoom->printitm();
    } else if(strcmp(command, "EXITS") == 0) {
      currentRoom->printext();
    } else if(strcmp(command, "PICKUP") == 0){
      int arglen = wordlen(input, commandlen + 1);
      char* itm = new char[arglen + 1];
      itm[arglen] = '\0';
      strncpy(itm, input + commandlen + 1, arglen);
      strupper(itm);

      Item* topick = finditm(itm, &(currentRoom->items));
      if(topick == NULL) cout << "No such item." << endl;
      else {
        items.push_back(topick);
        currentRoom->delitm(topick);
        cout << "Picked Up " << topick->name << endl;
      }
      delete[] itm;
    } else if(strcmp(command, "DROP") == 0){
      int arglen = wordlen(input, commandlen + 1);
      char* itm = new char[arglen + 1];
      itm[arglen] = '\0';
      strncpy(itm, input + commandlen + 1, arglen);
      strupper(itm);

      Item* topick = finditm(itm, &items);
      if(topick == NULL) cout << "No such item." << endl;
      else {
        currentRoom->items.push_back(topick);
        delitm(topick, &items);
        cout << "Dropped " << topick->name << endl;
      }
      delete[] itm;
    } else if(strcmp(command, "INSPECT") == 0){
      int arglen = wordlen(input, commandlen + 1);
      char* itm = new char[arglen + 1];
      itm[arglen] = '\0';
      strncpy(itm, input + commandlen + 1, arglen);
      strupper(itm);

      Item* topick = finditm(itm, &items);
      if(topick == NULL) cout << "No such item." << endl;
      else {
        topick->print();
      }
      delete[] itm;
    } else if(strcmp(command, "INVENTORY") == 0) {
      cout << CC_GRN << "Inventory: " << CC_CLR;
      vector<Item*>::iterator it = items.begin();
      while(it != items.end()){
        cout << ((*it)->name) << " ";
        it++;
      }
      cout << endl;
    } else if(strcmp(command, "HELP") == 0) {
      cout << CC_GRN << "Find all the items!" << endl;
      cout << CC_CYN << "Commands: QUIT, GO, ROOM, ITEMS, EXITS, PICKUP, DROP, INSPECT, INVENTORY, HELP" << endl;
      cout << CC_BLU << "Commands are not case sensitive!" << CC_CLR << endl;
    } else {
      cout << "Unrecognized Command." << endl;
    }

    if(items.size() == 5){
      cout << CC_GRN << "You found all the \"Necessary Items\"! You Win!" << CC_CLR << endl;
      cout << CC_BLU << "(I needed some way to end the game so..)" << CC_CLR << endl;
      playing = false;
    }

    delete[] command;
  }

  for(vector<Room*>::iterator i = cleanRooms.begin(); i != cleanRooms.end(); i++){
    // cout << "[Cleanup] Deleting Room " << ((*i)->name) << endl;
    delete (*i);
  }

  for(vector<Item*>::iterator i = cleanItems.begin(); i != cleanItems.end(); i++){
    // cout << "[Cleanup] Deleting Item " << ((*i)->name) << endl;
    delete (*i);
  }


  return 0;
}

void strupper(char* str){
  int len = strlen(str);
  for(int i = 0; i < len; i++){
    str[i] = toupper(str[i]);
  }
}

int dirtoindex(char* dir){
  strupper(dir);
  for(int i = 0; i < 4; i ++){
    if(strcmp(dir, DIRS[i]) == 0) return i;
  }
  return -1;
}

Room* createrooms(vector<Room*> &rooms, vector<Item*> &items) {
  Room* home = new Room();
  home->init("Home", "Oh so messy.");
  rooms.push_back(home);
  Room* wtrfl = new Room();
  wtrfl->init("Waterfall", "Why is it in your back yard?");
  rooms.push_back(wtrfl);
  Room* rn = new Room();
  rn->init("Right neighbor's house", "This one likes left twix");
  rooms.push_back(rn);
  Room* ln = new Room();
  ln->init("Left neighbor's house", "This one likes right twix");
  rooms.push_back(ln);
  Room* str1 = new Room();
  str1->init("The street", "It's a street. duh.");
  rooms.push_back(str1);
  Room* str2 = new Room();
  str2->init("The street", "It's a street. duh.");
  rooms.push_back(str2);
  Room* bff = new Room();
  bff->init("BFF's House", "Stop using that term!");
  rooms.push_back(bff);
  Room* bs = new Room();
  bs->init("Blacksmith?", "This map makes no sense!");
  rooms.push_back(bs);
  Room* md1 = new Room();
  md1->init("Meadow", "A beautiful meadow.");
  rooms.push_back(md1);
  Room* tb = new Room();
  tb->init("Troll Bridge", "He's feeling generous");
  rooms.push_back(tb);
  Room* er = new Room();
  er->init("End of the rainbow", "There's no pot of gold...");
  rooms.push_back(er);
  Room* uv = new Room();
  uv->init("Unicorn Valley", "Our map guy is drunk...");
  rooms.push_back(uv);
  Room* uv2 = new Room();
  uv2->init("Unicorn Valley", "Our map guy is drunk...");
  rooms.push_back(uv2);
  Room* md2 = new Room();
  md2->init("Meadow", "This one's also pretty.");
  rooms.push_back(md2);
  Room* md3 = new Room();
  md3->init("Meadow", "Pretty");
  rooms.push_back(md3);
  
  home->rooms[2] = wtrfl;
  wtrfl->rooms[0] = home;
  home->rooms[1] = rn;
  rn->rooms[3] = home;
  home->rooms[3] = ln;
  ln->rooms[1] = home;
  home->rooms[0] = str1;
  str1->rooms[2] = home;
  str1->rooms[0] = str2;
  str2->rooms[2] = str1;
  str2->rooms[0] = bff;
  bff->rooms[2] = str2;
  bff->rooms[3] = bs;
  bs->rooms[1] = bff;
  str1->rooms[1] = md1;
  md1->rooms[3] = str1;
  md1->rooms[1] = tb;
  tb->rooms[3] = md1;
  tb->rooms[0] = uv;
  uv->rooms[2] = tb;
  tb->rooms[1] = er;
  er->rooms[3] = tb;
  er->rooms[0] = uv2;
  uv2->rooms[2] = er;
  uv2->rooms[0] = md3;
  md3->rooms[2] = uv2;
  uv2->rooms[3] = uv;
  uv->rooms[1] = uv2;
  uv->rooms[0] = md2;
  md2->rooms[2] = uv;
  md2->rooms[1] = md3;
  md3->rooms[3] = md2;
  
  Item* riverRock = new Item();
  riverRock->init("River_Rock", "A river rock.");
  wtrfl->items.push_back(riverRock);
  items.push_back(riverRock);
  Item* rake = new Item();
  rake->init("Rake", "For your yard.");
  bs->items.push_back(rake);
  items.push_back(rake);
  Item* gc = new Item();
  gc->init("Gold_Coin", "The troll's charm.");
  tb->items.push_back(gc);
  items.push_back(gc);
  Item* u = new Item();
  u->init("Unicorn", "...Why?");
  uv2->items.push_back(u);
  items.push_back(u);
  Item* hl = new Item();
  hl->init("Heart_Locket", "<3");
  bff->items.push_back(hl);
  items.push_back(hl);

  return home;
}

int wordlen(char* array, int start){
  int index = start;
  int length = strlen(array);
  while(index < length && array[index] != ' ') index++;
  return (index - start);
}

Item* finditm(char const* name, vector<Item*>* items){
  vector<Item*>::iterator it = items->begin();
  while(it != (items->end())){
    char* uppercaseName = new char[strlen((*it)->name)];
    strcpy(uppercaseName, (*it)->name);
    strupper(uppercaseName);
    if(strcmp(uppercaseName, name) == 0) {
      delete[] uppercaseName;
      return (*it);
    }
    delete[] uppercaseName;
    it++;
  }
  return NULL;
}

void delitm(Item* itm, vector<Item*>* delFrom){
  vector<Item*>::iterator it = delFrom->begin();
  while(it != delFrom->end()){
    if(*it == itm) {
      delFrom->erase(it);
      return;
    }
    it++;
  }
}
