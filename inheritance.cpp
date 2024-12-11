Examples for diamond problem in inheritance:
=============================================================
These class structures represent the diamond problem,
where the `final derived class` 
inherits ambiguously 
from two intermediate classes 
that share a common base class.
=============================================================
Create one static object for final-derived class
and call all behaviours
and 
one dynamic object for final-derived class 
and call all behaviours

Define constructors and destructors for all the classes 
Example 4: `Appliance Types`
- `Base Class:` Appliance `{field: power, behavior: operate()}`
- `Derived Class 1:` WashingMachine `{field: drumSize, behavior: wash()}`
- `Derived Class 2:` Dryer `{field: capacity, behavior: dry()}`
- `Final Derived Class:` WasherDryer `{field: comboMode, behavior: autoCycle()}`
=========================================================================================
#include <iostream>

using namespace std;

class Appliance {
private:
    int power;
public:
  void operate() {
        cout << "Operating appliance with power: " << power << endl;
    }
    
    Appliance(int power) {
        this->power = power;  
        cout << "Appliance Constructor:" << endl;
    }

    
    virtual ~Appliance() {
        cout << "Appliance Destructor" << endl;
}

   
  
};

class WashingMachine : virtual public Appliance {
private:
    int drumSize;

public:
     void wash() {
        cout << "Washing with drum size: " << drumSize << endl;
    }

    WashingMachine(int power, int drumSize) : Appliance(power) {
        this->drumSize = drumSize;
        cout << "WashingMachine Constructor called"<< endl;
    }

    virtual ~WashingMachine() {
        cout << "WashingMachine Destructor called" << endl;
    }

   
};

class Dryer : virtual public Appliance {
private:
    int capacity;
public:

    void dry() {
        cout << "Drying with capacity: " << capacity << endl;
    }
   
    Dryer(int power, int capacity) : Appliance(power) {
        this->capacity = capacity;
        cout << "Dryer Constructor called " <<  endl;
    }

   
    virtual ~Dryer() {
        cout << "Dryer Destructor called" << endl;
    }

   
};

class Wdryer : public WashingMachine, public Dryer {
public:
    Wdryer(int power, int drumSize, int capacity)
        : Appliance(power), WashingMachine(power, drumSize), Dryer(power, capacity)
        {
        cout << "Wdryer Constructor called" << endl;
 }

    ~Wdryer() {
        cout << "Wdryer Destructor called" << endl;
    }

    void operateAll() {
        operate();
        wash();
        dry();
    }
};

int main() {
    Wdryer wd1(1020, 10, 5);

    wd1.operateAll();


     cout << "/Dynamic Objects/" << endl;
   Wdryer* WdryerDynamic = new Wdryer(982, 10, 78);   // Derived dynamic object

   WdryerDynamic->operate();              //inherited behavior
   
    delete  WdryerDynamic;

    return 0;
}




====================================================================================

single inheritance using static binding:
=============================================================
Create two static objects for Both Base and Derived class
and call all behaviours
and 
one two dynamic objects for Base and Derived class 
and call all behaviours

Define constructors and destructors for all the classes 


Example 4: `Employee Management`
- `Base Class:` Employee `{field: id, behavior: work()}`
- `Derived Class:` Manager `{field: teamSize, behavior: plan()}`
==================================================================================


#include <iostream>

using namespace std;

class Employee {
private:
    int id; 
public:
 Employee(int empId) : id(empId) {
        cout << "Employee Constructor "<< endl;
    }
 virtual ~Employee() {
        cout << "Employee Destructor" << endl;
    }
void work() {
        cout << "Employee " << id << " is working" << endl;
    }
};

class Manager : public Employee {
private:
    int teamSize; 
public:
    Manager(int empId, int size) : Employee(empId), teamSize(size) {
        cout << "Manager Constructor<"<< endl;
    }
    ~Manager() {
        cout << "Manager Destructor" << endl;
    }
    void plan() {
        cout << "Manager " << id << " is planning for a team of size " << teamSize << endl;
    }
};

int main() {
   
    cout << "/Static Objects/" << endl;
    Employee employeeStatic(189);  // - Base  object
    Manager managerStatic(172, 5); //- Derived  object

    employeeStatic.work();          //  base class behavior
   managerStatic.work();          // inherited behavior
   managerStatic.plan();          // derived class behavior

 
    cout << "/Dynamic Objects/" << endl;
    Employee* employeeDynamic = new Employee(671);      // Base dynamic object
    Employee* managerDynamic = new Manager(982, 10);   // Derived dynamic object

    employeeDynamic ->work();            // base class behavior
   managerDynamic->work();              //inherited behavior
   
    delete employeeDynamic;
    delete  managerDynamic;

    return 0;
}
============================================================================

single inheritance with dynamic binding
=============================================================
one two dynamic/static objects of the Derived class 
pointed by base class pointer
and call all behaviours using Base class pointer 

Override Base Class behaviors to derived class.
Define constructors and destructors for all the classes 
Define all the fields as dynamic fields in each class 

If you use string, use c-string (don't use string class)
        ie. dynamic c-string [dynamic char array]


 Example 4: `Device and Smartphone`
- `Base Class:` `Device`  
  - Fields: `brand`, `model`  
  - Pure Virtual Behaviors: `powerOn()`, `powerOff()`  
- `Derived Class:` `Smartphone`  
  - Fields: `operatingSystem` 
=============================================================

#include <iostream>
#include <cstring> 
using namespace std;

// Base class: Device
class Device {
protected:
    char* brand;
    char* model;

public:
    // Constructor
    Device(const char* b, const char* m) {
        brand = new char[strlen(b) + 1];
        strcpy(brand, b);

        model = new char[strlen(m) + 1];
        strcpy(model, m);
    }

    // Virtual destructor
    virtual ~Device() {
        delete[] brand;
        delete[] model;
    }

    // Pure virtual functions
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;

    // Display function for testing
    virtual void displayInfo() {
        cout << "Device Info: Brand = " << brand << ", Model = " << model << endl;
    }
};

// Derived class: Smartphone
class Smartphone : public Device {
private:
    char* operatingSystem;

public:
    // Constructor
    Smartphone(const char* b, const char* m, const char* os) : Device(b, m) {
        operatingSystem = new char[strlen(os) + 1];
        strcpy(operatingSystem, os);
    }

    // Destructor
    ~Smartphone() override {
        delete[] operatingSystem;
    }

    // Overriding behaviors
    void powerOn() override {
        cout << "Smartphone powered on. Welcome to " << operatingSystem << "!" << endl;
    }

    void powerOff() override {
        cout << "Smartphone powered off. Goodbye!" << endl;
    }

    // Overriding display function
    void displayInfo() override {
        Device::displayInfo();
        cout << "Operating System: " << operatingSystem << endl;
    }
};

int main() {
    // Create dynamic objects of Smartphone, pointed by Device pointers
    Device* device1 = new Smartphone("Apple", "iPhone 13", "iOS");
    Device* device2 = new Smartphone("Samsung", "Galaxy S22", "Android");

    // Call behaviors using Base class pointers
    device1->displayInfo();
    device1->powerOn();
    device1->powerOff();

    cout << endl; // Separator

    device2->displayInfo();
    device2->powerOn();
    device2->powerOff();

    // Cleanup
    delete device1;
    delete device2;

    return 0;
}
