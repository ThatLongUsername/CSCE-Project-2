#include <iostream>
#include <string>
#include <limits>

#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "FacilityManager.h"

using namespace std;

void displayMenu()
{
    cout << "\n========== SMART CAMPUS SYSTEM ==========\n";
    cout << "1. View all facilities\n";
    cout << "2. Search facility by ID\n";
    cout << "3. View campus graph\n";
    cout << "4. Display graph counts and degrees\n";
    cout << "5. Find reachable buildings (BFS)\n";
    cout << "6. Add department\n";
    cout << "7. Search department\n";
    cout << "8. Display department hierarchy\n";
    cout << "9. Run preorder traversal\n";
    cout << "10. Exit\n";
    cout << "=========================================\n";
    cout << "Enter choice: ";
}

int main()
{
    FacilityManager facilityManager;
    CampusGraph campusGraph;
    DepartmentTree departmentTree;

    // Load files
    facilityManager.loadFromFile("data/facilities.txt");
    departmentTree.loadFromFile("data/departments.txt");

    // Buildings
    campusGraph.addingBuildings("Library");
    campusGraph.addingBuildings("Student Union");
    campusGraph.addingBuildings("Science Building");
    campusGraph.addingBuildings("Engineering Building");
    campusGraph.addingBuildings("Business Building");
    campusGraph.addingBuildings("Gym");
    campusGraph.addingBuildings("Observatory");

    // Connections
    campusGraph.connectingBuilding("Library", "Student Union");
    campusGraph.connectingBuilding("Library", "Business Building");
    campusGraph.connectingBuilding("Student Union", "Science Building");
    campusGraph.connectingBuilding("Student Union", "Gym");
    campusGraph.connectingBuilding("Science Building", "Engineering Building");
    campusGraph.connectingBuilding("Business Building", "Gym");

    int choice;

    while (true)
    {
        displayMenu();

        if (!(cin >> choice))
        {
            cout << "Invalid input.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            facilityManager.displayFacilities(cout);
            break;
        }

        case 2:
        {
            string id;

            cout << "Enter Facility ID: ";
            getline(cin, id);

            facilityManager.searchFacilityByID(id, cout);

            break;
        }

        case 3:
        {
            campusGraph.showGraph();
            break;
        }

        case 4:
        {
            campusGraph.showGraphStats();
            break;
        }

        case 5:
        {
            string building;

            cout << "Enter starting building: ";
            getline(cin, building);

            campusGraph.tryBFS(building);

            break;
        }

        case 6:
        {
            string departmentName;
            string parentName;
            string error;

            cout << "Department name: ";
            getline(cin, departmentName);

            if (departmentName.empty())
            {
                cout << "Department name can't be blank.\n";
                break;
            }

            if (departmentTree.isEmpty())
            {
                parentName = "NONE";
            }
            else
            {
                cout << "Parent department: ";
                getline(cin, parentName);
            }

            if (departmentTree.addDepartment(
                    departmentName,
                    parentName,
                    error))
            {
                cout << "Department added successfully.\n";
            }
            else
            {
                cout << error << endl;
            }

            break;
        }

        case 7:
        {
            string name;

            cout << "Enter department name: ";
            getline(cin, name);

            departmentTree.displayDepartmentSearch(name,
                                                   cout);

            break;
        }

        case 8:
        {
            departmentTree.displayHierarchy(cout);

            break;
        }

        case 9:
        {
            departmentTree.displayPreorder(cout);

            break;
        }

        case 10:
        {
            cout << "Exiting program.\n";
            return 0;
        }

        default:
        {
            cout << "Invalid menu option.\n";
            break;
        }
        }
    }

    return 0;
}
