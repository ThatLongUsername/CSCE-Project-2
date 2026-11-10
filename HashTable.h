#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <vector>
#include <string>
#include "Facility.h"

using namespace std;
class HashTable{
private:
  vector<vector<Facility>> table;

  int capacity;
  int entries;
  int collisions;
  int hashFunction(const string& key) const;
public:
  HashTable(int size = 101);
  bool insert(const Facility& facility);
  Facility* search(const string& id);
  bool contains(const string& id);
  int getCapacity() const;
  int getEntries() const;
  int getCollisions() const;
};
#endif
