#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>

using namespace std;

struct Employee
{
    int empID;
    string firstname;
    string lastname;
    int storeID;
    int salary;
    string daysWorked;
    int totalDaysWorked;
    string salesTotal;
    double totalSales;
    double bonus;

    bool operator <(const Employee &another) {
        return this->totalSales > another.totalSales;
    }

    void printEmployee(){
        cout << this->empID << endl;
        cout << this->firstname << endl;
        cout << this->lastname << endl;
        cout << this->storeID << endl;
        cout << this->salary << endl;
        cout << this->totalDaysWorked << endl;
        cout << this->totalSales << endl << endl;
    }
};

vector<int> stringToVector(string str){
    vector<int> v;
    stringstream ss(str);
    int temp;
    while (ss >> temp)
        v.push_back(temp);
    return v;
}

int stringToInteger(string str){
    stringstream ss(str);
    int temp;
    ss >> temp;
    return temp;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


int getTotalSales(string totalSales){
    vector<int> sales = stringToVector(totalSales);
    double total = 0;
    for(int i = 0; i < 12; i++){
        total += (double)sales[i];
    }
    return total;
}

void sortEmployees(Employee e[], int n){
    sort(e, e+n);
}

void printReport(Employee e[], int n, const string filename){
    cout << "Printing output file" << endl;
    ofstream myfile;
    myfile.open (filename.c_str());

    for(int i = 0; i < 5000; i++){
        myfile << fixed << setprecision(2);
        myfile << e[i].empID << ", ";
        myfile << e[i].firstname << ", ";
        myfile << e[i].lastname << ", ";
        myfile << (double)e[i].salary << ", ";
        myfile << e[i].totalDaysWorked << ", ";
        myfile << e[i].totalSales << ", ";
        myfile << e[i].bonus << endl;
    }

	myfile << "Top 10 Highest Sales" << endl;
	for(int i = 0; i < 10; i++){
		myfile << "empID: " << e[i].empID << "\t\t" << "totalSales: " << e[i].totalSales << endl;
	}

	myfile << "\nTop 10 Lowest Sales" << endl;
	for(int i = 4999; i >= 4990; i--){
		myfile << "empID: " << e[i].empID << "\t\t" << "totalSales: " << e[i].totalSales << endl;
	}

	double totalSales = 0;
	double totalBonus = 0;
	for(int i = 0; i < 5000; i++){
		totalSales += e[i].totalSales;
		totalBonus += e[i].bonus;
	}

	myfile << "\nAverage Sales across the company: " << totalSales/5000 << endl;
	myfile << "Total Sales overall: " << totalSales << endl;
	myfile << "Total bonuses overall: " << totalBonus << endl;

    myfile.close();
}

int main(int argc, char const *argv[])
{
    srand((unsigned)time(0));
	string line;
    cout << "Reading data" << endl;
    string in_filename = "data.txt";
    ifstream myfile;
    myfile.open(in_filename.c_str());

    if( !myfile.is_open()) {
        cout << "File "<< in_filename <<" not found." << endl;
        exit(-1);
    }
    Employee employees[5000];
    for(int i=0; i < 5000; i++) {
    	getline(myfile, line);
        istringstream iss(line);
        string empID;
        string storeID;
        string salary;
        string totalDaysWorked;

		getline(iss, empID, ',');
        employees[i].empID = stringToInteger(empID);

        getline(iss, employees[i].firstname, ',');
        trim(employees[i].firstname);
        getline(iss, employees[i].lastname, ',');
        trim(employees[i].lastname);

        getline(iss, storeID, ',');
        trim(storeID);
        employees[i].storeID = stringToInteger(storeID);
        employees[i].storeID;

        getline(iss, salary, ',');
        trim(salary);
        employees[i].salary = stringToInteger(salary);
        employees[i].salary;

        getline(iss, totalDaysWorked, ',');
        trim(totalDaysWorked);
        employees[i].totalDaysWorked = stringToInteger(totalDaysWorked);
        employees[i].totalDaysWorked;

        getline(iss, employees[i].salesTotal, ',');
    	trim(employees[i].salesTotal);
        employees[i].totalSales = getTotalSales(employees[i].salesTotal);
    }

    sortEmployees(employees, 5000);
    for (int i = 0; i < 5000; ++i)
    {
        employees[i].bonus = (0.001 * employees[i].salary) * (0.001*(employees[i].totalSales - employees[4999].totalSales));
    }
    string out_filename = "results.txt";
    printReport(employees, 5000, out_filename);

    return 0;
}
