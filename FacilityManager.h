#ifndef FACILITY_MANAGER_H
#define FACILITY_MANAGER_H

#include <vector>
#include <string>
#include <iostring>
#include "Facility.h"
#include "HashTable.h"

using namespace std;
class FacilityManager{
private:
  vector<Facility> facilities;
  HashTable hashTable;
  string trim(const string& value) const;
  string normalizeID(const string& value) const;
  bool validFacilityID(const string& id) const;

public:
  FacilityManager();
  void loadFromFile(const string& filename);
  void displayFacilities(ostream& output) const;
  void searchFacilityByID(
    const string& id,
    ostream& output);
  int getFacilityCount() const;
};

#endif
