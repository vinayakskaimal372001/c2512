#include<iostream>
#include <algorithm>
#include <string>
#include <memory>  
#include <vector>  
using namespace std;

class Employee{
public:
    unique_ptr<int>id;
    unique_ptr<int>age;
    unique_ptr<string>name;

public:
    Employee(int v_id,int v_age, string v_name)
    :id(make_unique<int>(v_id)),age(make_unique<int>(v_age)),name(make_unique<string>(v_name)){}

    virtual void printDetails(){
        cout << *id << " " << *age << " " << *name;
    }

    virtual void swap(Employee& other){
        std::swap(id,other.id);
        std::swap(age,other.age);
        std::swap(name,other.name);
    }
    
    friend istream& operator >>(istream& in, Employee&);
    friend ostream& operator <<(ostream& os, Employee&);
};
istream& operator >>(istream& in, Employee& e){
    cout << "enter id, age, name...";
    in >> *e.id >>*e.age >> *e.name;
    return in;
}

ostream& operator <<(ostream& os, Employee& e){
    e.printDetails();
    return os;
}

class Programmer:public Employee{
    public:
        unique_ptr<string[]>tasks;
        unique_ptr<int>taskCount;
    
    public:
        Programmer(int v_id,int v_age,string v_name,string* v_tasks, int v_taskCount)
        :Employee(v_id,v_age,v_name),taskCount(make_unique<int>(v_taskCount)){
            tasks = make_unique<string[]>(*taskCount);
            for(int i=0; i < *taskCount; i++){
                tasks[i]=v_tasks[i];          
            }
        }

        void swap(programmer& other){
            std::swap(tasks,other.tasks);
            std::swap(taskCount,other.taskCount);


            Employee::swap(other);
        }

        printDetails() override{
            Employee::printDetails();
            cout << "Tasks: ";
            for(int i; i < *taskCount; i++){
                cout << tasks[i]<<" ";
            }
        }

        friend istream& operator >>(istream& in, Programmer&);
        friend ostream& operator<<(ostream& os, Programmer& p);
};

istream& operator >>(istream& in, Programmer& p){
    in >> static_cast<Employee&>(p);  // Read basic employee details
    cout << "Enter number of tasks: ";
    in >> *p.taskCount;
    p.tasks = make_unique<string[]>(*p.taskCount);
    cout << "Enter tasks: ";
    for (int i = 0; i < *p.taskCount; ++i) {
        in >> p.tasks[i];
    }
    return in;
}

ostream& operator<<(ostream& os, Programmer& p) {
    p.printDetails();
    return os;  
}

int main() {
    int N;
    cout << "Enter number of programmers: ";
    cin >> N;

    vector<unique_ptr<Employee>> programmers;
    for (int i = 0; i < N; ++i) {
        cout << "Enter details for Programmer " << i + 1 << endl;
        unique_ptr<Programmer> p = make_unique<Programmer>(0, 0, "", nullptr, 0);
        cin >> *p; 
        programmers.push_back(move(p));
    }

    for (size_t i = 0; i < programmers.size(); ++i) {
        cout << "Programmer " << i + 1 << ": " << *programmers[i] << endl;
    }

    return 0;
}
