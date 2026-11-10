#include "HashTable.h"
HashTable::HashTable(int size){
  capacity = size;
  entries = 0;
  collisions = 0;
  table.rezise(capacity);
}
int HashTable::hashFunction(const string& key) const{
  unsigned long hash = 0;
  for(char c : key){
    hash = hash * 31 + c;
  }
  return hash % capacity;
}
bool HashTable::insert(const Facilty& facility){
  int index = hashFunction(facility.id);
  for(const Facility& current : table[index]){
    if(current.id == facility.id){
      return false;
    }
  }
  if(!table[index].empty()){
    collisions++;
  }
  table[index].push_back(facility);
  entries++;
  return true;
}
Facility* HashTable::search(const string& id){
  int index = hashFunction(id);
  for(Facility& facility : table[index]){
    if(facility.id == id){
      return &facility;
    }
  }
  return nullptr;
}

bool HashTable::contains(const string& id){
  return search(id) != nullptr;
}int HashTable::getCapacity() const{
  return capacity;
}int HashTable::getEntries() const{
  return entries;
}int HashTable::getCollisions() const{
  return collisions;
}
