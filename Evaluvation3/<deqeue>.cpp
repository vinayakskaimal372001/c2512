#include <iostream>
#include <iomanip>

using namespace std;

#include<deque>
#include<algorithm>
#include<string>

// ---SurgeryManager.cpp----
class SurgeryManager{
    private:
        deque<string>SurgeryIDs;
        deque<int>Durations;
    
    public:
        int findIndexById(string& SurgeryID);
        void create();
        void displayAll();
        void editById();
        void deleteById();

};

void printMenu() {
    cout << "\n=== Surgery Management Module ===\n";
    cout << "1. Create Surgery\n";
    cout << "2. Display All Surgery\n";
    cout << "3. Edit Surgery\n";
    cout << "4. Delete Surgery\n";
    cout << "5. Exit\n";
}

// main.cpp

int main(){
    SurgeryManager manager;
    int choice; //user choice

     do {
        printMenu(); // Display menu
        cout << "Enter your choice: ";
        cin >> choice;

        // Menu-driven functionality
        switch (choice) {
            case 1: manager.create();    break;
            case 2: manager.displayAll();  break;
            case 3: manager.editById();      break;
            case 4: manager.deleteById();    break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

// SurgeryManager.cpp

// Creates a new hospital duration and stores details in arrays. 

void SurgeryManager::create(){
    
    string SurgeryID;
    int Duration;

    cout << "Enter Surgery SurgeryID : ";
    cin >> SurgeryID;

    // Ensure Surgery SurgeryID is unique
    if (findIndexById(SurgeryID) != -1) {
        cout << "Error: Surgery SurgeryID already exists. Please use a unique SurgeryID.\n";
        return;
    }

    cout << "Enter Durations : ";
    cin >> Duration;

    SurgeryIDs.push_back(SurgeryID);
    Durations.push_back(Duration);

    cout << "Surgery created successfully.\n";
}

//  brief Displays all existing surgerys in a tabular format.

    void SurgeryManager::displayAll() {
    if (SurgeryIDs.empty()){
        cout << "No Surgery available to display.\n";
        return;
    }

    cout << "------------------------- \n";
    cout << "|   SURGERYID | Duration |\n";
    cout << "--------------------------\n";
    for (auto ITER = SurgeryIDs.begin() ; ITER != SurgeryIDs.end() ; ITER++) {
        cout << "| " << setw(10) << SurgeryIDs[ITER] << " | "
             << setw(9) << Durations[ITER] << " |\n";
    }
    cout << "--------------------------\n";
}

// Finds the index of a surgery duration by surgeryid.
// return Index of the surgery  if found, -1 otherwise.

int SurgeryManager::findIndexById(string& SurgeryID) {
    auto iter = find(SurgeryIDs.begin(),SurgeryIDs.end(),SurgeryID);
    if(iter != SurgeryIDs.end()){
        return distance(SurgeryIDs.begin(),iter);
    }
    return -1;
}

// Edits an existing hospital duration by SurgeryID.

void SurgeryManager::editById() {
    string SurgeryID;
    cout << "Enter Surgery SurgeryID to edit: ";
    cin >> SurgeryID;

    int index = findIndexById(SurgeryID);
    if (index == -1) {
        cout << "Error: Surgery SurgeryID not found.\n";
        return;
    }

    cout << "Current Details - Duration: " << Durations[index] << "\n";

    cout << "Enter New Duration: ";
    cin >> Durations[index];

    cout << "Surgey updated successfully.\n";
}

// Deletes an existing Surgery by SurgeryID.

void SurgeryManager::deleteById() {
    string SurgeryID;
    cout << "Enter Surgery SurgeryID to delete: ";
    cin >> SurgeryID;

    int index = findIndexById(SurgeryID);
    if (index == -1) {
        cout << "Error: Surgery SurgeryID not found.\n";
        return;
    }

    SurgeryIDs.erase(SurgeryIDs.begin()+index);
    Durations.erase(Durations.begin()+index);

    cout << "Surgery deleted successfully.\n";
}
