 //1.3 Programmer { string* tasks; int taskCount; } : Employee | tasks is the multiple tasks - array of task 
        // swap function overloadable
        // here, create the dynamic programmer object assigned to employee pointer.
        // field 'tasks' is dynamic memoery.
        // operator << overloadable, swap is overridden.


#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Employee {
public:
    int* id;         
    int* age;         
    string* name; 

public:
    Employee(int v_id, int v_age, string v_name) {
        id = new int(v_id);          
        age = new int(v_age);        
        name = new string(v_name);  
    }

    virtual ~Employee() {
        delete id;    
        delete age;   
        delete name; 
    }

    virtual void printDetails() {
        cout << *id << " " << *age << " " << *name; 
    }

    virtual void swap(Employee& other) {
        std::swap(id, other.id);  
        std::swap(age, other.age);
        std::swap(name, other.name);
    }

    friend ostream& operator<<(ostream& os,Employee& );
};


class Programmer : public Employee {
public:
    string* tasks;  
    int taskCount;  

public:
    Programmer(int v_id, int v_age, string v_name, string* v_tasks, int v_taskCount)
        : Employee(v_id, v_age, v_name), taskCount(v_taskCount) {
        tasks = new string[taskCount];   
        for (int i = 0; i < taskCount; i++) {
            tasks[i] = v_tasks[i];  
        }
    }

    ~Programmer() {
        delete[] tasks;
    }

    void swap(Programmer& other){
        std::swap(taskCount, other.taskCount);
        std::swap(tasks, other.tasks);
        
        Employee::swap(other);
    }

    void printDetails() override {
        Employee::printDetails(); 
        cout << " Tasks: ";
        for (int i = 0; i < taskCount; i++) {
            cout << tasks[i]<<" ";  
        }
    }

    friend ostream& operator<<(ostream& os, Programmer& );
};

ostream& operator<<(ostream& os, Employee& e) {
    e.printDetails();
    return os; 
}

ostream& operator<<(ostream& os,Programmer& p) {
    p.printDetails();
    return os;  
}

int main() {
    // Create task array for Programmer 1
    string tasks1[] = {"Task10", "Task11", "Task12"};
    Employee* p1 = new Programmer(101, 22, "Athira", tasks1, 3);

    // Create task array for Programmer 2
    string tasks2[] = {"Task20", "Task21", "Task22"};
    Employee* p2 = new Programmer(102, 23, "Bhagya", tasks2, 3);

    cout << "p1: " << *p1 << endl;  
    cout << "p2: " << *p2 << endl; 

    p1->swap(*p2);

    cout << "after swap" << endl;
    cout << "p1: " << *p1 << endl;  
    cout << "p2: " << *p2 << endl;  

    delete p1;
    delete p2;

    return 0;
}
