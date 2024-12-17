// //1.4 
//     // replace dynamic fields as smart pointers 
//     // prove that Employee virtual destructor is not needed.
//     // create the dynamic programmer object assigned to employee smart pointer

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>  
#include <vector>  
using namespace std;

class Employee {
public:
    unique_ptr<int> id;      
    unique_ptr<int> age;    
    unique_ptr<string> name; 

public:
    Employee(int v_id, int v_age, string v_name)
        : id(make_unique<int>(v_id)), age(make_unique<int>(v_age)), name(make_unique<string>(v_name)) {}

    virtual void printDetails()  {
        cout << *id << " " << *age << " " << *name;
    }

    virtual void swap(Employee& other) {
        std::swap(id, other.id);
        std::swap(age, other.age);
        std::swap(name, other.name);
    }

    friend ostream& operator<<(ostream& os,  Employee& e);
};

class Programmer : public Employee {
public:
    unique_ptr<string[]> tasks;  
    unique_ptr<int>taskCount;  

public:
    Programmer(int v_id, int v_age, string v_name, string* v_tasks, int v_taskCount)
        : Employee(v_id, v_age, v_name), taskCount(make_unique<int>(v_taskCount)) {
        tasks = make_unique<string[]>(*taskCount);
        for (int i = 0; i < *taskCount; ++i) {
            tasks[i] = v_tasks[i]; 
        }
    }

    void swap(Programmer& other) {
        std::swap(tasks, other.tasks);
        std::swap(taskCount, other.taskCount);
        
        Employee::swap(other);
    }

    void printDetails() override {
        Employee::printDetails();
        cout << " Tasks: ";
        for (int i = 0; i < *taskCount; ++i) {
            cout << tasks[i] << " ";
        }
    }

    friend ostream& operator<<(ostream& os,  Programmer& p);
};

ostream& operator<<(ostream& os,  Employee& e) {
    e.printDetails();
    return os; 
}

ostream& operator<<(ostream& os, Programmer& p) {
    p.printDetails();
    return os;  
}

int main() {
    // Create task array for Programmer 1
    string tasks1[] = {"Task1", "Task2", "Task3"};
    unique_ptr<Employee> p1 = make_unique<Programmer>(101, 22, "Athira", tasks1, 3);

    // Create task array for Programmer 2
    string tasks2[] = {"TaskA", "TaskB", "TaskC"};
    unique_ptr<Employee> p2 = make_unique<Programmer>(102, 23, "Bhagya", tasks2, 3);

    cout << "p1: " << *p1 << endl;  
    cout << "p2: " << *p2 << endl;  

    p1->swap(*p2); 

    cout << "after swap" << endl;
    cout << "p1: " << *p1 << endl;  
    cout << "p2: " << *p2 << endl;  


    return 0;
}
