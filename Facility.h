#ifndef FACILITY_H
#define FACILITY_H
#include <string>
using namespace std;
struct Facility{
  string id;
  string name;
  string building;
  string category;
  Facility();

  Facility(
    const string& id,
    const string& name,
    const string& building,
    const string& category
  );
};
#endif
