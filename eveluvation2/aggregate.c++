#include <iostream>
#include <iomanip>

using namespace std;

// Constants
const int MAX_LAB_TESTS = 100;

// *****LabTest.h*****
class LabTest {
    friend class LabTestManager;
    private:
        string TestID;
        double ResultValue;
    public:
        bool GreaterThan(const LabTest& other);
        bool LessThan(const LabTest& other);
        // Getters-Setters
        string GetTestID();
        double GetResultValue();
};

// *****LabTestManager.h*****
class LabTestManager {
    friend class LabTestAggregator;
    friend int main();
    private:
        LabTest tests[MAX_LAB_TESTS];
        int numLabTests;
    public:
        int findIndexById(string TestID);
        void create();
        void displayAll();
        void editById();
        void deleteById();
        LabTestManager();
};

// *****LabTestAggregator.h*****
class LabTestAggregator {
    public:
        int findMin(LabTestManager& manager);
        int findMax(LabTestManager& manager);
        int findSecondMin(LabTestManager& manager);
        int findSecondMax(LabTestManager& manager);
};

// *****Menu.h*****
void printMenu();

// *****Main.cpp*****
int main() {
    LabTestManager manager;
    LabTestAggregator aggregator;

    int choice;
    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.create(); break;
            case 2: manager.displayAll(); break;
            case 3: manager.editById(); break;
            case 4: manager.deleteById(); break;
            case 5:
                cout << "LabTest with Min Result: " 
                     << manager.tests[aggregator.findMin(manager)].GetTestID() 
                     << " with ResultValue " 
                     << manager.tests[aggregator.findMin(manager)].GetResultValue() << endl;
                break;
            case 6:
                cout << "LabTest with Max Result: " 
                     << manager.tests[aggregator.findMax(manager)].GetTestID() 
                     << " with ResultValue " 
                     << manager.tests[aggregator.findMax(manager)].GetResultValue() << endl;
                break;
            case 7:
                cout << "LabTest with 2nd Min Result: " 
                     << manager.tests[aggregator.findSecondMin(manager)].GetTestID() 
                     << " with ResultValue " 
                     << manager.tests[aggregator.findSecondMin(manager)].GetResultValue() << endl;
                break;
            case 8:
                cout << "LabTest with 2nd Max Result: " 
                     << manager.tests[aggregator.findSecondMax(manager)].GetTestID() 
                     << " with ResultValue " 
                     << manager.tests[aggregator.findSecondMax(manager)].GetResultValue() << endl;
                break;
            case 9: cout << "Exiting the system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please enter a valid number.\n";
        }
    } while (choice != 9);

    return 0;
}

// *****LabTestManager.cpp*****
void LabTestManager::create() {
    if (numLabTests >= MAX_LAB_TESTS) {
        cout << "Error: Maximum lab test limit reached.\n";
        return;
    }

    string TestID;
    double ResultValue;

    cout << "Enter LabTest TestID: ";
    cin >> TestID;

    if (findIndexById(TestID) != -1) {
        cout << "Error: TestID already exists.\n";
        return;
    }

    cout << "Enter Result Value: ";
    cin >> ResultValue;

    tests[numLabTests].TestID = TestID;
    tests[numLabTests].ResultValue = ResultValue;
    numLabTests++;

    cout << "LabTest created successfully.\n";
}

void LabTestManager::displayAll() {
    if (numLabTests == 0) {
        cout << "No lab tests available.\n";
        return;
    }

    cout << "------------------------------------------------\n";
    cout << "|   TestID   |   Result Value                  |\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < numLabTests; i++) {
        cout << "| " << setw(10) << tests[i].TestID << " | "
             << setw(14) << tests[i].ResultValue << " |\n";
    }
    cout << "------------------------------------------------\n";
}

int LabTestManager::findIndexById(string TestID) {
    for (int i = 0; i < numLabTests; i++) {
        if (tests[i].TestID == TestID) return i;
    }
    return -1;
}

void LabTestManager::editById() {
    string TestID;
    cout << "Enter LabTest TestID to edit: ";
    cin >> TestID;

    int index = findIndexById(TestID);
    if (index == -1) {
        cout << "Error: TestID not found.\n";
        return;
    }

    cout << "Current Result Value: " << tests[index].ResultValue << "\n";
    cout << "Enter New Result Value: ";
    cin >> tests[index].ResultValue;

    cout << "LabTest updated successfully.\n";
}

void LabTestManager::deleteById() {
    string TestID;
    cout << "Enter LabTest TestID to delete: ";
    cin >> TestID;

    int index = findIndexById(TestID);
    if (index == -1) {
        cout << "Error: TestID not found.\n";
        return;
    }

    for (int i = index; i < numLabTests - 1; i++) {
        tests[i] = tests[i + 1];
    }
    numLabTests--;

    cout << "LabTest deleted successfully.\n";
}

LabTestManager::LabTestManager() : numLabTests(0) {}

// *****LabTest.cpp*****
bool LabTest::GreaterThan(const LabTest& other) { return (ResultValue > other.ResultValue); }
bool LabTest::LessThan(const LabTest& other) { return (ResultValue < other.ResultValue); }
string LabTest::GetTestID() { return TestID; }
double LabTest::GetResultValue() { return ResultValue; }





-----------------------------------------------------------------------------------------------------------------------------
//*****LabTestAggregator.cpp**************


int LabTestAggregator::findMin(LabTestManager& manager) {
    int minIndex = 0;
    for (int i = 1; i < manager.numLabTests; i++) {
        if (manager.tests[i].LessThan(manager.tests[minIndex])) {
            minIndex = i;
        }
    }
    return minIndex;
}

int LabTestAggregator::findMax(LabTestManager& manager) {
    int maxIndex = 0;
    for (int i = 1; i < manager.numLabTests; i++) {
        if (manager.tests[i].GreaterThan(manager.tests[maxIndex])) {
            maxIndex = i;
        }
    }
    return maxIndex;
}


int LabTestAggregator::findSecondMin(LabTestManager& manager) {
    int minIndex = findMin(manager);
    int secondMinIndex = (minIndex == 0) ? 1 : 0;

    for (int i = 0; i < manager.numLabTests; i++) {
        if (i != minIndex && manager.tests[i].LessThan(manager.tests[secondMinIndex])) {
            secondMinIndex = i;
        }
    }
    return secondMinIndex;
}


int LabTestAggregator::findSecondMax(LabTestManager& manager) {
    int maxIndex = findMax(manager);
    int secondMaxIndex = (maxIndex == 0) ? 1 : 0;

    for (int i = 0; i < manager.numLabTests; i++) {
        if (i != maxIndex && manager.tests[i].GreaterThan(manager.tests[secondMaxIndex])) {
            secondMaxIndex = i;
        }
    }
    return secondMaxIndex;
}
