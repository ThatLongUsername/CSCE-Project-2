#include "FacilityManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

FacilityManager::FacilityManager()
{
}

string FacilityManager::trim(const string& value) const
{
    size_t start = value.find_first_not_of(" \t\r\n");

    if(start == string::npos)
    {
        return "";
    }

    size_t end = value.find_last_not_of(" \t\r\n");

    return value.substr(start,
                        end - start + 1);
}

string FacilityManager::normalizeID(
    const string& value) const
{
    string result = trim(value);

    for(char& c : result)
    {
        c = toupper(c);
    }

    return result;
}

bool FacilityManager::validFacilityID(
    const string& id) const
{
    if(id.length() != 4)
    {
        return false;
    }

    if(id[0] != 'F')
    {
        return false;
    }

    for(int i = 1; i < 4; i++)
    {
        if(!isdigit(id[i]))
        {
            return false;
        }
    }

    return true;
}

void FacilityManager::loadFromFile(
    const string& filename)
{
    ifstream file(filename);

    if(!file)
    {
        cout << "Error opening "
             << filename
             << endl;

        return;
    }

    int accepted = 0;
    int rejected = 0;

    string line;

    while(getline(file, line))
    {
        line = trim(line);

        if(line.empty())
        {
            continue;
        }

        if(line[0] == '#')
        {
            continue;
        }

        stringstream ss(line);

        string id;
        string name;
        string building;
        string category;

        getline(ss,id,'|');
        getline(ss,name,'|');
        getline(ss,building,'|');
        getline(ss,category);

        id = normalizeID(id);

        if(!validFacilityID(id))
        {
            rejected++;
            continue;
        }

        Facility facility(
            id,
            trim(name),
            trim(building),
            trim(category));

        if(hashTable.insert(facility))
        {
            facilities.push_back(facility);
            accepted++;
        }
        else
        {
            rejected++;
        }
    }

    cout
    << filename
    << ": "
    << accepted
    << " accepted, "
    << rejected
    << " rejected "
    << "(hash capacity "
    << hashTable.getCapacity()
    << ", entries "
    << hashTable.getEntries()
    << ", collisions "
    << hashTable.getCollisions()
    << ")"
    << endl;
}

void FacilityManager::displayFacilities(
    ostream& output) const
{
    for(const Facility& facility : facilities)
    {
        output
        << facility.id << " | "
        << facility.name << " | "
        << facility.building << " | "
        << facility.category
        << endl;
    }

    output
    << "Total Facilities: "
    << facilities.size()
    << endl;
}

void FacilityManager::searchFacilityByID(
    const string& enteredID,
    ostream& output)
{
    string id = normalizeID(enteredID);

    if(!validFacilityID(id))
    {
        output
        << "Invalid format: F followed by exactly three digits."
        << endl;

        return;
    }

    Facility* found =
        hashTable.search(id);

    if(found == nullptr)
    {
        output
        << "Not found: no facility with ID "
        << id
        << endl;

        return;
    }

    output
    << "Found: "
    << found->name
    << " | "
    << found->building
    << " | "
    << found->category
    << endl;
}

int FacilityManager::getFacilityCount() const
{
    return facilities.size();
}
