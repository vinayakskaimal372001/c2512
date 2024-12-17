// Coding Question: 1.1
/*
    Employee {id, age, name} //id, age, name are value objects 
    Employee e1(101,22,"Athira"),e2(102,23,"Bhagya");
    cout << e1 << endl; //101 22 Athira
    cout << e2 << endl; //102 23 Bhagya
    e1.swap(e2);
    cout << e1 << endl; //102 23 Bhagya
    cout << e2 << endl; //101 22 Athira
    */

#include<iostream>
#include <algorithm>
using namespace std;
#include<string>

class Employee{
public:    
    int id;
    int age;
    string name;
public:
    Employee(int v_id, int v_age,string v_name):id(v_id),age(v_age),name(v_name){
    }

    friend ostream& operator << (ostream& os, Employee&);
};

ostream& operator << (ostream& os, Employee& obj){
    os << obj.id <<" " << obj.age << " "<< obj.name;
    return os;
}

int main(){
    Employee e1(101,22,"Athira"),e2(102,23,"Bhagya");
    cout << "e1: " << e1 << endl;
    cout << "e2: " <<  e2 << endl;
    std::swap(e1,e2);
    cout << "after swap"<< endl;
    cout << "e1: " <<  e1 << endl;
    cout << "e2: " <<  e2 << endl;

    return 0;
}
