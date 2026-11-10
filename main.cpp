#include <iostream>
#include <string>
#include <limits>

#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "FacilityManager.h"

using namespace std;

void displayMenu()
{
    cout << "\n=====================================\n";
    cout << " SMART CAMPUS NAVIGATION SYSTEM\n";
    cout << "=====================================\n";
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
    cout << "=====================================\n";
    cout << "Enter choice: ";
}

int main(int arcg, char* arcv[])
{
    FacilityManager facilityManager;
    CampusGraph campusGraph;
    DepartmentTree departmentTree;

    // Load facility and department data
    facilityManager.loadFromFile("data/facilities.txt");
    departmentTree.loadFromFile("data/departments.txt");
    
    campusGraph.loadBuildings("data/buildings.txt");
    campusGraph.loadConnections("data/connections.txt");
    int choice;

    while(true)
    {
        displayMenu();

        if(!(cin >> choice))
        {
            cout << "\nInvalid menu input.\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        switch(choice)
        {
            case 1:
            {
                facilityManager.displayFacilities(cout);
                break;
            }

            case 2:
            {
                string facilityID;

                cout
                << "Enter Facility ID: ";

                getline(cin, facilityID);

                facilityManager.searchFacilityByID(
                    facilityID,
                    cout
                );

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

                cout
                << "Enter starting building: ";

                getline(cin, building);

                if(building.empty())
                {
                    cout
                    << "Building name cannot be blank."
                    << endl;
                }
                else
                {
                    campusGraph.tryBFS(building);
                }

                break;
            }

            case 6:
            {
                string departmentName;
                string parentName;
                string errorMessage;

                cout
                << "Department name: ";

                getline(cin, departmentName);

                if(departmentName.empty())
                {
                    cout
                    << "Department name can't be blank."
                    << endl;

                    break;
                }

                if(departmentTree.isEmpty())
                {
                    parentName = "NONE";
                }
                else
                {
                    cout
                    << "Parent department: ";

                    getline(cin, parentName);
                }

                if(
                    departmentTree.addDepartment(
                        departmentName,
                        parentName,
                        errorMessage
                    )
                )
                {
                    cout
                    << "Department added successfully."
                    << endl;
                }
                else
                {
                    cout
                    << errorMessage
                    << endl;
                }

                break;
            }

            case 7:
            {
                string departmentName;

                cout
                << "Enter department name: ";

                getline(cin, departmentName);

                departmentTree.displayDepartmentSearch(
                    departmentName,
                    cout
                );

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
                cout
                << "Exiting program..."
                << endl;

                return 0;
            }

            default:
            {
                cout
                << "Invalid menu choice."
                << endl;
                break;
            }
        }
    }
    return 0;
}
