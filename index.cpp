#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include <cctype>
#include <algorithm>
using namespace std;

class Employee
{
private:
  static int nextId_;
  string name_;
  int age_;
  char gender_;
  int id_;
  string field_;
  int salary_;
  string position_;
  vector<string> skills_;
  static const string idFile_;

public:
  static void initializeNextId()
  {
    ifstream idFile(idFile_);
    if (idFile.is_open())
    {
      idFile >> nextId_;
      idFile.close();
    }
    else
    {
      nextId_ = 1001;
    }
  }

  static void updateNextId()
  {
    ofstream idFile(idFile_, ios::trunc);
    idFile << nextId_;
    idFile.close();
  }

  Employee(string name, int age, char gender, string field, int salary, string position, vector<string> skills) : name_(name), age_(age), gender_(gender), field_(field), salary_(salary), position_(position), skills_(skills)
  {
    this->id_ = nextId_++;
    updateNextId();
    cout << "Employee Id is: " << this->id_;
  };
  void printDetails(fstream &file)
  {
    file << id_ << "|";
    file << name_ << "|";
    file << age_ << "|";
    file << gender_ << "|";
    file << field_ << "|";
    file << salary_ << "|";
    for (string skill : skills_)
    {
      file << skill << " ";
    }
    file << "|";
    file << "\n";
  }

  friend void addEmployee(fstream &file);
  friend void getDetails(fstream &file, int id);
};
void getDetails(fstream &file, int id)
{
  file.clear();
  file.seekg(0, ios::beg);
  string name_;
  int age_;
  char gender_;
  int id_;
  string field_;
  int salary_;
  string position_;
  vector<string> skills_;
  string line;
  while (getline(file, line))
  {
    int line_count = 0;
    stringstream ss(line);
    string token;
    vector<string> tokens;
    while (getline(ss, token, '|'))
    {
      tokens.push_back(token);
    }
    if (tokens.size() >= 1 && stoi(tokens[0]) == id)
    {
      if (tokens.size() >= 7)
      {
        id_ = stoi(tokens[0]);
        age_ = stoi(tokens[2]);
        gender_ = tokens[3][0];
        name_ = tokens[1];
        field_ = tokens[4];
        salary_ = stoi(tokens[5]);
        position_ = tokens[6];
      }
      cout << "Employee Loaded:\n";
      cout << name_ << " | " << age_ << " | " << gender_ << " | " << id_ << " | "
           << field_ << " | " << salary_ << " | " << position_;
      for (string skill : skills_)
      {
        cout << skill << " ";
      }
      cout << "\n";
    }
  }
}
class TechEmployee : public Employee
{
public:
  TechEmployee(string name, int age, char gender, string field, int salary, string position, vector<string> skills) : Employee(name, age, gender, field, salary, position, skills)
  {
  }
};
class ManagementEmployee : public Employee
{
public:
  ManagementEmployee(string name, int age, char gender, string field, int salary, string position, vector<string> skills) : Employee(name, age, gender, field, salary, position, skills)
  {
  }
};
void addEmployee(fstream &file)
{
  string name;
  int age;
  char gender;
  string field;
  int salary;
  string position;
  vector<string> skills;
  cout << "Enter the name of the employee : ";
  cin >> name;
  if (name.size() <= 1)
  {
    cout << "The name is too short";
    return;
  }
  cout << "Enter the age of the employee : ";
  cin >> age;
  if (age < 18)
  {
    cout << "The age is less than 18 : ";
    return;
  }
  cout << "Enter gender of the employee |M|F|O : ";
  cin >> gender;
  if (gender != 'M' && gender != 'F' && gender != 'O')
  {
    cout << "Enter only M|F|O";
    return;
  }
  cout << "Enter the field of the employee : ";
  cin >> field;
  if (field != "Tech" && field != "Management")
  {
    cout << "Enter only Tech or Management : ";
    return;
  }
  cout << "Enter the salary of the employee : ";
  cin >> salary;
  if (salary < 10000)
  {
    cout << "The salary is less than 10000 !";
    return;
  }
  cout << "Enter the position of the employee : ";
  cin >> position;
  cout << "For spaces use '-' " << endl;
  cout << "Enter the skills of the employee (enter '.' to stop) : ";
  string skill;
  while (true)
  {
    cin >> skill;
    if (skill == ".")
      break;
    skills.push_back(skill);
  }
  if (field == "Tech")
  {
    TechEmployee t1(name, age, gender, field, salary, position, skills);
    t1.printDetails(file);
  }
  else
  {
    ManagementEmployee m1(name, age, gender, field, salary, position, skills);
    m1.printDetails(file);
  }
}
int Employee::nextId_ = 1001;
const string Employee::idFile_ = "id.txt";
int main()
{
  Employee::initializeNextId();
  fstream myfile;
  string action;
  cout << "Please select the action you would like to perform (add, get-details): ";
  cin >> action;
  transform(action.begin(), action.end(), action.begin(), ::tolower);

  if (action == "add")
  {
    myfile.open("employee.txt", ios::app);
    if (myfile.is_open())
    {
      addEmployee(myfile);
      myfile.close();
    }
  }
  else if (action == "get-details")
  {
    int id;
    cout << "Enter ID of employee";
    cin >> id;
    myfile.open("employee.txt", ios::in);
    if (myfile.is_open())
    {
      getDetails(myfile, id);
    }
  }
  return 0;
}