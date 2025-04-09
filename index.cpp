#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Employee
{
private:
  string name_;
  int age_;
  char gender_;
  int id_;
  string field_;
  int salary_;
  string position_;
  vector<string> skills_;

public:
  Employee(string name, int age, char gender, int id, string field, int salary, string position, vector<string> skills) : name_(name), age_(age), gender_(gender), id_(id), field_(field), salary_(salary), position_(position), skills_(skills) {};
  virtual void getDetails()
  {
    cout << name_ << endl;
    cout << age_ << endl;
    cout << gender_ << endl;
    cout << id_ << endl;
    cout << field_ << endl;
    cout << salary_ << endl;
    for (string skill : skills_)
    {
      cout << skill << " ";
    }
  }
};
class TechEmployee : public Employee
{
public:
  TechEmployee(string name, int age, char gender, int id, string field, int salary, string position, vector<string> skills) : Employee(name, age, gender, id, field, salary, position, skills)
  {
  }
};
class ManagementEmployee : public Employee
{
public:
  ManagementEmployee(string name, int age, char gender, int id, string field, int salary, string position, vector<string> skills) : Employee(name, age, gender, id, field, salary, position, skills)
  {
  }
};

int main()
{
  TechEmployee Nishant("Nishant", 19, 'M', 101, "Tech", 20000, "Intern", {"C++", "DSA", "Problem Solving"});
  Nishant.getDetails();
  return 0;
}