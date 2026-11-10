#include "Faciliy.h"
Facility::Facility() // finction with no info in it
{
}
Facility::Facility( // functuon with info entered
  const string& facilityID,
  const string& facilityName,
  const string& buildingName,
  const string& facilityCategory)
{
  id = facilityID;
  name = facilityName;
  building = buildingName;
  category = facilityCategory;
}
