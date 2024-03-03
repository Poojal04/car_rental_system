#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;
string usernameglobal="manager";
int passwordglobal=123456;
int fineRate=5000;
int totalfine=0;
class Car {
private:
    string model;
    string registrationNumber;
    string condition;
    int rentCost;
    bool isAvailable;
    int returnDays;  
    
    string towhom; 

public:
    // Public constructor to initialize Car object
    Car(const string& mdl, const string& regNum, const string& cond, int cost, bool available,const string&whom, int days )
        : model(mdl), registrationNumber(regNum), condition(cond), rentCost(cost), isAvailable(available),towhom(whom), returnDays(days) {}
 bool checkAvailability() const {
        return isAvailable;
    }
    string getRegistrationNumber(){
        return registrationNumber;}
     string gettowhom()const {
    return towhom;}
    int getreturnday() const {
    return returnDays;}
    string getCondition(){
        return condition;
    }
    string getModel(){
        return model;
    }
   static vector<Car> readCarData() {
    vector<Car> cars;
    ifstream file("car.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string mdl, regNum, cond,towhom;
        int cost, available, days;

        getline(ss, mdl, ',');
        getline(ss, regNum, ',');
        getline(ss, cond, ',');
        char comma;
        ss >> cost>>comma ;
        ss>> available >> comma;
        getline(ss, towhom, ',');
        ss>>days;
        Car car(mdl, regNum, cond, cost, available,towhom, days);
        cars.push_back(car);
    }

    file.close();
    return cars;
}
     int getRentCost(){
        return rentCost;
     }
    
    void displayDetailsIfAvailable() const {
            cout << "Model: " << model << "\n";
            cout << "Registration Number: " << registrationNumber << "\n";
            cout << "Condition: " << condition << "\n";
            cout << "Rent Cost: $" << rentCost << "\n";
            cout << "Is Available: Yes\n";
            cout << "-------------------------\n";
        
    }
   static void writeCarData( vector<Car>& cars) {
    ofstream file("car.txt");
    for (auto& car : cars) {
        file << car.getModel() << "," << car.getRegistrationNumber() << ","
             << car.getCondition() << "," << car.getRentCost() << ","
             << car.checkAvailability() << "," << car.gettowhom() << ","
             << car.getreturnday()<< endl;
    }
    file.close();
}
    

};

class User {
protected:
    string username;
    string password;
    string ID;

public:
   User() {}
    User(const std::string& uname, const std::string& pwd, const std::string& id)
        : username(uname), password(pwd), ID(id) {}
         void clearfine_dues(int finepaying,int totalfine ,string filename,string username)
    {
  ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line)) {
         stringstream ss(line);
    string uname, password, id;
    int customerRecord, fineDue;
    char comma;

    // Read each field separated by commas
    getline(ss, uname, ',');
    getline(ss, password, ',');
    getline(ss, id, ',');
    ss >> customerRecord >> comma >> fineDue;
        if (uname == username) {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," << customerRecord << "," << fineDue-finepaying<< endl;
            
            updated = true;
        } else {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
    }
};
class Employee:public User{
private:
    int fineDue;
    int employeeRecord;

public:
    Employee(const string& uname, const string& pwd, const string& id,
             int fine, int record, int details)
        : User(uname, pwd, id), fineDue(fine), employeeRecord(record) {}

    Employee() {}
    string getUsername() const {
        return username;
    }
    string getPassword(){
    return password;}
    string getID(){
        return ID; }
    int getFineDue(){
        return fineDue;
    }
    int getEmployeeRecord(){
        return employeeRecord;
    }
    bool authenticate(const string& enteredPassword) const {
        return (password == enteredPassword);
    }
    static vector<Employee> readEmployeeData() {
        vector<Employee> employees;
        ifstream file("employee.txt");
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            Employee employee;
            getline(ss,employee.username, ',');
            getline(ss,employee.password, ',');
            getline(ss,employee.ID, ',');
            char comma;
            ss >>  employee.employeeRecord >>comma>> employee.fineDue ;

            employees.push_back(employee);
        }

        file.close();
        return employees;
    }

    static void writeEmployeeData(const vector<Employee>& employees) {
        ofstream file("employee.txt");
        for (const auto& employee : employees) {
            file << employee.username << ","
                 << employee.password << ","
                 << employee.ID << ","
                 << employee.employeeRecord << ","
                 << employee.fineDue << "\n";
        }
        file.close();
    }
    void viewEmployeeDetails()
{
        cout << "Username: " <<username << "\n";
        cout << "Password: " << password<< "\n";
        cout << "ID" << ID<< "\n";
        cout << "Employee Record: " <<employeeRecord<< "\n";
        cout << "FINE: " <<fineDue<< "\n";
    
}
   
};
class Manager : public User {
public:
    Manager(const std::string& uname, const std::string& pwd, const std::string& id)
        : User(uname, pwd, id) {}

    Manager() {}

    void registerNewCustomer() const;
    void registerNewEmployee() const;
     static void updateCustomerDetails(const string& usernameToUpdate, const string& filename,
                                   const string& newPassword, int newCustomerRating, int newFine) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string username, password,id;
        int  customerRating, fine;

        getline(ss, username, ',');
        getline(ss, password, ',');
 getline(ss, id, ',');
        char comma;
        ss >> customerRating >> comma >> fine;
        if (username == usernameToUpdate) {
            // Update the line with new information
           
            tempFile << username << "," << newPassword << "," << id << ","
                     << newCustomerRating << "," << newFine << endl;
            updated = true;
        } else {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
static void updateEmployeeDetails(const string& usernameToUpdate, const string& filename,
                                   const string& newPassword, int newEmployeeRating, int newFine) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string username, password,id;
        int  employeeRating, fine;

        getline(ss, username, ',');
        getline(ss, password, ',');
 getline(ss, id, ',');
        char comma;
        ss >> employeeRating >> comma >> fine;
        if (username == usernameToUpdate) {
            tempFile << username << "," << newPassword << "," << id << ","
                     << newEmployeeRating << "," << newFine << endl;
            updated = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

    static void deleteEmployee(const string& usernameToDelete, const string& filename) {
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");

        if (!inFile || !tempFile) {
            cerr << "Error opening files." << endl;
            return;
        }

        string line;
        bool deleted = false;

        while (getline(inFile, line)) {
             stringstream ss(line);
            string username, password,id;
            int  employeeRating, fine;

           getline(ss,username, ',');
getline(ss,password, ',');
getline(ss,id, ',');

char comma;
ss >> employeeRating>>comma>>fine;


            if (username == usernameToDelete) {
                // Skip this line (delete it)
                deleted = true;
            } else {
                // Write the original line to the temporary file
                tempFile << line << endl;
            }
        }

        inFile.close();
        tempFile.close();

        // If a line was deleted, replace the original file with the temporary file
        if (deleted) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        } else {
            remove("temp.txt"); // Delete the temporary file if no deletion was made
        }
    }                                   
 static void deleteCustomer(const string& usernameToDelete, const string& filename) {
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");

        if (!inFile || !tempFile) {
            cerr << "Error opening files." << endl;
            return;
        }

        string line;
        bool deleted = false;

        while (getline(inFile, line)) {
             stringstream ss(line);
            string username, password,id;
            int  customerRating, fine;

           getline(ss,username, ',');
getline(ss,password, ',');
getline(ss,id, ',');

char comma;
ss >> customerRating>>comma>>fine;


            if (username == usernameToDelete) {
                // Skip this line (delete it)
                deleted = true;
            } else {
                // Write the original line to the temporary file
                tempFile << line << endl;
            }
        }

        inFile.close();
        tempFile.close();

        // If a line was deleted, replace the original file with the temporary file
        if (deleted) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        } else {
            remove("temp.txt"); // Delete the temporary file if no deletion was made
        }
    }
     static void addCustomer(const string& filename, const string& newUsername, const string& newPassword,
                            int newID, int newCustomerRating, int newFine) {
        ofstream file(filename, ios::app);
        file << newUsername << "," << newPassword << "," << newID << ","
             << newCustomerRating << "," << newFine << endl;
        file.close();
    }
    static void addEmployee(const string& filename, const string& newUsername, const string& newPassword,
                            int newID, int newEmployeeRating, int newFine) {
        ofstream file(filename, ios::app);
        file << newUsername << "," << newPassword << "," << newID << ","
             << newEmployeeRating << "," << newFine << endl;
        file.close();
    }
    void updateDetails(string carname,string filename,string regno,string newCondition, int newCost,int  newAvailable,string newToWhom,int newReturnDays)
    {
        ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line)) {
        stringstream ss(line);
      string model, regNum, condition, towhom;
int cost, available, days;

getline(ss, model, ',');
getline(ss, regNum, ',');
getline(ss, condition, ',');
char comma;
ss >> cost >>comma>> available>>comma;

getline(ss, towhom, ',');
ss >> days;

        if (model == carname) {
            // Update the line with new information
            tempFile << model << "," << regno << "," << newCondition << "," << newCost << ","
                     << newAvailable << "," << newToWhom <<","<<newReturnDays<< endl;
            updated = true;
        } else {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
    }
};
class Customer : public User {
private:
    int fineDue;
    int customerRecord;

public:
    Customer(const string& uname, const string& pwd, const string& id,
             int fine, int record, int details)
        : User(uname, pwd, id), fineDue(fine), customerRecord(record) {}

    Customer() {}
    string getUsername() const {
        return username;
    }
    string getPassword(){
    return password;}
   string getID(){
        return ID;
    }
    int getFineDue(){
        return fineDue;
    }
    int getCustomerRecord(){
        return customerRecord;
    }
    bool authenticate(const string& enteredPassword) const {
        return (password == enteredPassword);
    }
    static vector<Customer> readCustomerData() {
        vector<Customer> customers;
        ifstream file("customer.txt");
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            Customer customer;
            getline(ss, customer.username, ',');
            getline(ss, customer.password, ',');
            getline(ss, customer.ID, ',');
            char comma;
            ss >> customer.customerRecord >>comma>>customer.fineDue ;

            customers.push_back(customer);
        }

        file.close();
        return customers;
    }

    static void writeCustomerData(const vector<Customer>& customers) {
        ofstream file("customer.txt");
        for (const auto& customer : customers) {
            file << customer.username << ","
                 << customer.password << ","
                 << customer.ID << ","
                 << customer.customerRecord << ","
                 << customer.fineDue << "\n";
        }
        file.close();
    }
    void viewCustomerDetails()
{
        cout << "Username: " <<username << "\n";
        cout << "Password: " << password<< "\n";
        cout << "ID" << ID<< "\n";
        cout << "Customer Record: " <<customerRecord<< "\n";
       cout << "FINE: " <<fineDue<< "\n";
    
}
};
void Manager::registerNewEmployee() const {
      vector<Employee> employees = Employee::readEmployeeData();
    cout << "Enter username: ";
    string username;
    cin >> username;

  
    auto it = find_if(employees.begin(), employees.end(),
                      [username](const Employee& c) { return c.getUsername() == username; });

    if (it !=employees.end()) {
        cout << "This username already exists. Try Again.\n";
    } else {
        string password;
        cout << "Enter password: "<<endl;
        cin >> password;

        string confirmPassword;
        cout << "Confirm password: "<<endl;
        cin >> confirmPassword;

        if (password == confirmPassword) {
            Employee newEmployee(username, password, to_string(employees.size()+1), 0, 5, 0);
            employees.push_back(newEmployee);
            Employee::writeEmployeeData(employees);
            cout << "Registration successful! Please log in again.\n";
        } else {
            cout << "Password and Confirm Password do not match. Registration failed.\n";
        }
    }
}
void Manager::registerNewCustomer() const {
      vector<Customer> customers = Customer::readCustomerData();
    cout << "Enter username: "<<endl;
    string username;
    cin >> username;

  
    auto it = find_if(customers.begin(), customers.end(),
                      [username](const Customer& c) { return c.getUsername() == username; });

    if (it != customers.end()) {
        cout << "This username already exists. Try Again.\n";
    } else {
        string password;
        cout << "Enter password: "<<endl;
        cin >> password;

        string confirmPassword;
        cout << "Confirm password: "<<endl;
        cin >> confirmPassword;

        if (password == confirmPassword) {
            Customer newCustomer(username, password, to_string(customers.size()+1), 0, 5, 0);
            customers.push_back(newCustomer);
            Customer::writeCustomerData(customers);
            cout << "Registration successful! Please log in again.\n";
        } else {
            cout << "Password and Confirm Password do not match. Registration failed.\n";
        }
    }
}
void return_request(const string& filename, const string& carname, const string& newCondition, bool newAvailability, const string& newToWhom) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }
    string line;
    bool updated = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string model, regNum, condition, towhom;
        int cost, available, days;

       getline(ss, model, ',');
getline(ss, regNum, ',');
getline(ss, condition, ',');
char comma;
ss >> cost >>comma>> available>>comma;
getline(ss, towhom, ',');
ss >>days;

        if (model == carname) {
            // Update the line with new information
            tempFile << model << "," << regNum << "," << newCondition << "," << cost << ","
                     << newAvailability << "," << newToWhom <<"," << days <<  endl;
            updated = true;
        } else {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void rent_request(const string& filename, const string& carname, bool newAvailability, const string& newToWhom,int daysrequired) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
      string model, regNum, condition, towhom;
int cost, available, days;

getline(ss, model, ',');
getline(ss, regNum, ',');
getline(ss, condition, ',');
char comma;
ss >> cost >>comma>> available>>comma;

getline(ss, towhom, ',');
ss >> days;

        if (model == carname) {
            // Update the line with new information
            tempFile << model << "," << regNum << "," << condition << "," << cost << ","
                     << newAvailability << "," << newToWhom <<","<<daysrequired<< endl;
            updated = true;
        } else {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void updateCustomerInfo(const string& filename, const string& username, int newCustomerRecord,int fine) {
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line)) {
         stringstream ss(line);
    string uname, password, id;
    int customerRecord, fineDue;
    char comma;

    // Read each field separated by commas
    getline(ss, uname, ',');
    getline(ss, password, ',');
    getline(ss, id, ',');
    ss >> customerRecord >> comma >> fineDue;
//    if(fine!=0)
//    fineDue+=fine;
        if (uname == username) {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," << customerRecord+newCustomerRecord << "," << fineDue+fine<< endl;
            
            updated = true;
        } else {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // 1Delete the temporary file if no update was made
    }
}
void updateEmployeeInfo(const string& filename, const string& username, int newEmployeeRecord,int fine) {
   
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line)) {
         stringstream ss(line);
    string uname, password, id;
    int employeeRecord, fineDue;
    char comma;

    // Read each field separated by commas
    getline(ss, uname, ',');
    getline(ss, password, ',');
    getline(ss, id, ',');
    ss >> employeeRecord >> comma >> fineDue;
    // /cout<<newEmployeeRecord;
//    if(fine!=0)
//    fineDue=fine;
        if (uname == username) {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," << employeeRecord+newEmployeeRecord << "," << fineDue+fine<< endl;
            
            updated = true;
        } else {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    } else {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void carupdate(vector <Car> &cars,string model)
{
    try{
            for (auto& car : cars) {
                if (car.getModel() == model) {
                    // Assuming new values are entered by the user
                    string newCondition, newToWhom,regno;
                    int newCost, newAvailable, newReturnDays;
                    newAvailable=car.checkAvailability();
                    newReturnDays=car.getreturnday();
                    regno=car.getRegistrationNumber();
                    newToWhom=car.gettowhom();
                    newCondition=car.getCondition();
                    newCost=car.getRentCost();
                    cout<<"Press 1 to update condition and press 2 to update the Rent per day and 3 to exit from this operation"<<endl;
                    int choose;
                    cin>>choose;
                    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
                    if(choose==1){
                    cout << "Enter the new condition (Good/Excellent/Damaged): "<<endl;
                    cin >> newCondition;}
                    else if(choose==2){
                    cout << "Enter the new cost: "<<endl;
                    cin >> newCost;
                    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }}
                    else{
                     return;
                    }
                    Manager manager;
                    manager.updateDetails(model,"car.txt",regno,newCondition, newCost, newAvailable, newToWhom, newReturnDays);
                    break;
                }
            }
            carupdate(cars,model);}
            catch(const std::exception& e) {
        // Handle exceptions here, you can print an error message or log the exception.
        std::cerr << "Error occurred " << e.what() << std::endl;
    }
}
void Carchange(int operation)
{
   try{

if (operation == 1) {
     vector<Car> cars = Car::readCarData();
    // Update
    string model;
    cout << "Enter the model of the car you want to update: "<<endl;
    cin >> model;

    // Check if the car exists
    auto it = find_if(cars.begin(), cars.end(), [model]( Car& car) {
        return car.getModel() == model;
    });

    if (it != cars.end()) {
        carupdate(cars,model);
    } else {
        cout << "Car not found!" << endl;
    }
} else if (operation == 2) {
     vector<Car> cars = Car::readCarData();
    // Delete
    string modelToDelete;
    cout << "Enter the model of the car you want to delete: "<<endl;
    cin >> modelToDelete;

    // Check if the car exists
    auto it = find_if(cars.begin(), cars.end(), [modelToDelete](Car& car) {
        return car.getModel() == modelToDelete;
    });

    if (it != cars.end()) {
        // Erase the car from the vector
        cars.erase(it);

        // Write the updated car data back to the file
        Car::writeCarData(cars);
    } else {
        cout << "Car not found!" << endl;
    }
} else if (operation == 3) {
     vector<Car> cars = Car::readCarData();
    // Add
    string newCondition, newToWhom, regno, CarName;
    int newCost, newAvailable, newReturnDays;

    cout << "Enter Car Name: "<<endl;
    cin >> CarName;

    // Check if the car with the same name already exists
    auto it = find_if(cars.begin(), cars.end(), [CarName]( Car& car) {
        return CarName == car.getModel();
    });

    if (it != cars.end()) {
        cout << "Car with this name already exists!" << endl;
    } else {
        cout << "Enter New Registration No: "<<endl;
        cin >> regno;

        cout << "Enter the new condition (Good/Excellent/Damaged): "<<endl;
        cin >> newCondition;
        cout << "Enter the new cost: "<<endl;
        cin >> newCost;
        if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
        newAvailable = 1;
        newToWhom = "None";
        cout << "Enter the new return days: "<<endl;
        cin >> newReturnDays;

        Car newCar(CarName, regno, newCondition, newCost, newAvailable, newToWhom, newReturnDays);
        cars.push_back(newCar);
        Car::writeCarData(cars);
    }
}
 else if (operation == 4) {
    // Search
     vector<Car> cars = Car::readCarData();
    cout << "Enter the car name to search: "<<endl;
    string carname;
    cin >> carname;
    int d = 0;
    for (auto& car : cars) {
        if (car.getModel() == carname) {
            car.displayDetailsIfAvailable();
            d++;
        }
    }
    if (d == 0)
        cout << "Car is not present" << endl;
} else {
    cout << "Invalid operation!" << endl;
    return;
}}
 catch(const std::exception& e) {
        // Handle exceptions here, you can print an error message or log the exception.
        std::cerr << "Error occurred " << e.what() << std::endl;
    }
}
void modifyCustomer(int operation)
{
   try{
    Manager manager;

    if (operation == 1) {
         vector<Customer> customers = Customer::readCustomerData();
        // Update
        string username;
        cout << "Enter the username of the customer you want to update: "<<endl;
        cin >> username;

        // Check if the customer exists
        auto it = find_if(customers.begin(), customers.end(), [username](const Customer& customer) {
            return username == customer.getUsername();
        });

        if (it != customers.end()) {
            // Assuming new values are entered by the user
            string newPassword;
            int newCustomerRating, newFine;
            cout << "Enter the new password: "<<endl;
            cin >> newPassword;
            cout << "Enter the new customer rating: "<<endl;
            cin >> newCustomerRating;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            cout << "Enter the new fine: "<<endl;
            cin >> newFine;
if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            Manager::updateCustomerDetails(username, "customer.txt", newPassword, newCustomerRating, newFine);
        } else {
            cout << "Customer not found!" << endl;
        }
    } else if (operation == 2) {
         vector<Customer> customers = Customer::readCustomerData();
        // Delete
        string username;
        cout << "Enter the username of the customer you want to delete: ";
        cin >> username;

        // Check if the customer exists
        auto it = find_if(customers.begin(), customers.end(), [username](const Customer& customer) {
            return username == customer.getUsername();
        });

        if (it != customers.end()) {
            Manager::deleteCustomer(username, "customer.txt");
        } else {
            cout << "Customer not found!" << endl;
        }
    } else if (operation == 3) {
         vector<Customer> customers = Customer::readCustomerData();
        // Add
        string newUsername, newPassword;
        int newID, newCustomerRating, newFine;
        cout << "Enter the new username: "<<endl;
        cin >> newUsername;

        // Check if the customer already exists
        auto it = find_if(customers.begin(), customers.end(), [newUsername](const Customer& customer) {
            return newUsername == customer.getUsername();
        });

        if (it != customers.end()) {
            cout << "Customer with this username already exists!" << endl;
        } else {
            cout << "Enter the new password: "<<endl;
            cin >> newPassword;
            cout << "Enter the new ID: "<<endl;
            cin >> newID;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            cout << "Enter the new customer rating: "<<endl;
            cin >> newCustomerRating;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            cout << "Enter the new fine: "<<endl;
            cin >> newFine;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }

            Manager::addCustomer("Customer.txt", newUsername, newPassword, newID, newCustomerRating, newFine);
        }
    } else if (operation == 4) {
         vector<Customer> customers = Customer::readCustomerData();
        // Search
        cout << "Enter the customer to search: "<<endl;
        string name;
        cin >> name;
        int c = 0;

        for (auto& customer : customers) {
            if (name == customer.getUsername()) {
                customer.viewCustomerDetails();
                c++;
            }
        }

        if (c == 0)
            cout << "Customer is not present in the database" << endl;
    } else {
        cout << "Invalid operation!" << endl;
        return;
    }}
    catch(const std::exception& e) {
        // Handle exceptions here, you can print an error message or log the exception.
        std::cerr << "Error occurred " << e.what() << std::endl;
    }
}

void modifyEmployee(int operation)
{
    try{
    Manager manager;
vector<Employee> employees = Employee::readEmployeeData();
    if (operation == 1) {
        // Update
        string username;
        cout << "Enter the username of the employee you want to update: "<<endl;
        cin >> username;

        // Check if the employee exists
        auto it = find_if(employees.begin(), employees.end(), [username](const Employee& employee) {
            return username == employee.getUsername();
        });

        if (it != employees.end()) {
            // Assuming new values are entered by the user
            string newPassword;
            int newEmployeeRating, newFine;
            cout << "Enter the new password: "<<endl;
            cin >> newPassword;
            cout << "Enter the new Employee rating: "<<endl;
            cin >> newEmployeeRating;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            cout << "Enter the new fine: "<<endl;
            cin >> newFine;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            Manager::updateEmployeeDetails(username, "employee.txt", newPassword, newEmployeeRating, newFine);
        } else {
            cout << "Employee not found!" << endl;
        }
    } else if (operation == 2) {
        // Delete
        string username;
        cout << "Enter the username of the employee you want to delete: ";
        cin >> username;

        // Check if the employee exists
        auto it = find_if(employees.begin(), employees.end(), [username](const Employee& employee) {
            return username == employee.getUsername();
        });

        if (it != employees.end()) {
            Manager::deleteEmployee(username, "employee.txt");
        } else {
            cout << "Employee not found!" << endl;
        }
    } else if (operation == 3) {
        // Add
        string newUsername, newPassword;
        int newID, newEmployeeRating, newFine;
        cout << "Enter the new username: "<<endl;
        cin >> newUsername;

        // Check if the employee already exists
        auto it = find_if(employees.begin(), employees.end(), [newUsername](const Employee& employee) {
            return newUsername == employee.getUsername();
        });

        if (it != employees.end()) {
            cout << "Employee with this username already exists!" << endl;
        } else {
            cout << "Enter the new password: "<<endl;
            cin >> newPassword;
            cout << "Enter the new ID: ";
            cin >> newID;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            cout << "Enter the new Employee rating: "<<endl;
            cin >> newEmployeeRating;
            if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            cout << "Enter the new fine: "<<endl;
            cin >> newFine;
if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
            Manager::addEmployee("employee.txt", newUsername, newPassword, newID, newEmployeeRating, newFine);
        }
    } else if (operation == 4) {
        // Search
        cout << "Enter the employee to search: "<<endl;
        string name;
        cin >> name;
        
        int c = 0;

        for (auto& employee : employees) {
            if (name == employee.getUsername()) {
                employee.viewEmployeeDetails();
                c++;
            }
        }

        if (c == 0)
            cout << "Employee with this name doesn't exist" << endl;
    } else {
        cout << "Invalid operation!" << endl;
        return;
    }}
    catch(const std::exception& e) {
        // Handle exceptions here, you can print an error message or log the exception.
        std::cerr << "Error occurred " << e.what() << std::endl;
    }
    }

int viewAvailableCars(vector<Car>& cars)
{
     
     int count=0;
      cout << "Available Cars:\n";
                    for (auto& car : cars) {
                            if(car.checkAvailability()){
                            car.displayDetailsIfAvailable();
                            count++;
                            }
                        
                    }
                    if(count==0){
                        cout<<"Sorry no car to Rent"<<endl;}
                    return count;
}
int CarsTaken(vector<Car>& cars,string username)
{int t=0;
                    for (auto& car : cars) {
                            if(car.gettowhom()==username){
                            car.displayDetailsIfAvailable();
                            t++;
                            }} 
                            return t;                  
}
void customeroptions(vector<Customer>& customers,vector<Car>& cars,string username,string password)
{
    try{
    cout<<"Type 1 to display all available cars and rent a car ,2 to return a car ,3 to clear dues ,4 to exit user: "<<endl;
    int operation;
    cin>>operation; if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }

    if(operation==1)
    {
      int a= viewAvailableCars(cars);
      if(a!=0)
     {
         vector<Customer> customers=Customer::readCustomerData();
       cout<<"Do you want to rent a car?(YES or NO)"<<endl;
      string s;
      cin>>s;
     if(s=="YES"){
         
      int customercheck;
                    for (auto& customer : customers) {
                            if(username==customer.getUsername()){
                            customercheck=customer.getCustomerRecord();
                            }
                        }
                    cout<<"Customer can rent "<<" "<<customercheck<<"  no of cars"<<endl;
                   
                        cout<<"Enter CarName"<<endl;
                        string carname;
                        cin>>carname;
                          auto it = find_if(cars.begin(), cars.end(),
                           [carname](Car& c) -> bool { return ((c.getModel() == carname)&& (c.checkAvailability()==1)); });
                            

    if (it != cars.end()) {
                        cout<<"How many days you want the car for"<<endl;
                        int daysrequired;
                        cin>>daysrequired;
                        rent_request("car.txt", carname, 0,username,daysrequired);
    }
    else{
        cout<<"This Car has already been rented"<<endl;
    }}
    else
    cout<<"Sure"<<endl;
                    
    }}
    else if(operation==2)
    {  vector<Customer> customers=Customer::readCustomerData();
     vector<Car> cars = Car::readCarData();
                      int totalcost=0;
                      int totalfine=0;
                     cout<<"CarsRented by you  :"<<endl;
                     int p=CarsTaken(cars,username);
                     if(p!=0){
                        cout<<"Name of car you are returning"<<endl;
                        string carname;
                        cin>>carname;
                          auto it = find_if(cars.begin(), cars.end(),
                           [carname](Car& c) -> bool { return ((c.getModel() == carname)); });
                           if(it!=cars.end()){
                        cout<<"Condition of returning the car(Good,Excellent,Damaged)"<<endl;
                        string condition;

                        cin>>condition;
                        for (auto& customer : customers) {
                            if(username==customer.getUsername()){
                             totalfine+=customer.getFineDue();
                            }
                        }
                        for(auto& car: cars){
                            if(carname==car.getModel()){
                            if(condition==car.getCondition())
                            updateCustomerInfo("customer.txt", username,0,0);
                            else if(condition=="Damaged"&&car.getCondition()=="Excellent")
                            updateCustomerInfo("customer.txt", username,-2,0);
                            else if(car.getCondition()=="Damaged"&&(condition=="Excellent"))
                            updateCustomerInfo("customer.txt", username,2,0);
                            else if(car.getCondition()=="Damaged"&&(condition=="Good"))
                            updateCustomerInfo("customer.txt", username,1,0);
                            else if(car.getCondition()=="Good"&&(condition=="Excellent"))
                            updateCustomerInfo("customer.txt", username,1,0);
                            else
                            updateCustomerInfo("customer.txt", username,-1,0);
                            }
                        }
                    return_request("car.txt", carname, condition, 1, "None");
                    cout<<"Enter number of days after which you are returning"<<endl;
                    int days;
                    cin>>days;
                    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
                    for ( auto& car : cars) {
                            if(carname==car.getModel()){
                                totalcost=days*car.getRentCost();
                                if(days-car.getreturnday()>0){
                                totalfine=(days-car.getreturnday())*fineRate;
                                }
                                }}
                    
                    updateCustomerInfo("customer.txt", username,0,totalfine);
                    cout<<"Cost to pay for this car  "<<totalcost<<endl;
                    cout<<"Fine to pay for this car  "<<totalfine<<endl;
    }}
    else
    cout<<"This car is not rented by you"<<endl;}
    else if(operation==3)
    {  vector<Customer> customers=Customer::readCustomerData();
        cout<<"Fine till date :"<<endl;
        for (auto& customer : customers) {
                            if(username==customer.getUsername()){
                             cout<<customer.getFineDue();
                            }
                        }
                        cout<<endl;
        cout<<"Fine you are paying now "<<endl;
                    int finepaying;
                    cin>>finepaying;
                    Customer customer;
                    customer.clearfine_dues(finepaying,totalfine,"customer.txt",username);
    }
    else{
      return;
    }
      customeroptions(customers, cars,username, password);
}
catch (const std::exception& e) {
        // Handle exceptions here, you can print an error message or log the exception.
        std::cerr << "Error occurred " << e.what() << std::endl;
    }
}
void employeeoptions(vector<Employee>&employees,vector<Car>& cars,string username,string password)
{
    //  vector<Car> cars = Car::readCarData();
    //   vector<Customer> customers = Customer::readCustomerData();
    try {
    cout<<"Type 1 to display all available cars and rent a car ,2 to return a car ,3 to clear dues ,4 to exit user  ";
    int operation;
    cin>>operation;
    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
     if(operation==1)
    {   vector<Employee> employees=Employee::readEmployeeData();
        viewAvailableCars(cars);
      int a= viewAvailableCars(cars);
       if(a==0)
      return;
      cout<<"Do you want to rent a car?(YES or NO) "<<endl;
      string s;
      cin>>s;
     if(s=="YES"){
        int employeecheck;
                    for (auto& employee : employees) {
                            if(username==employee.getUsername()){
                            employeecheck=employee.getEmployeeRecord();
                            }
                        }
                    cout<<"Employee can rent "<<" "<<employeecheck<<"  no of cars"<<endl;
                        cout<<"Enter CarName: ";
                        string carname;
                        cin>>carname;
                         auto it = find_if(cars.begin(), cars.end(),
                           [carname](Car& c) -> bool { return (c.getModel() == carname&& c.checkAvailability()==1); });
    if (it != cars.end()) {
                       
                        cout<<"How many days you want the car for? ";
                        int daysrequired;
                        cin>>daysrequired;
                        rent_request("car.txt", carname, 0,username,daysrequired);
    }
    else
    cout<<"Cannot rent this Car."<<endl;
                    
    }}
    else if(operation==2)
    {
          vector<Employee> employees=Employee::readEmployeeData();
             vector<Car> cars=Car::readCarData();
  int totalcost=0;
                      int totalfine=0;
                      cout<<"CarsRented by you  :";
                     int p=CarsTaken(cars,username);
                    if(p!=0){
                        cout<<"Name of car you are returning  ";
                        string carname;
                        cin>>carname;
                         auto it = find_if(cars.begin(), cars.end(),
                           [carname](Car& c) -> bool { return ((c.getModel() == carname)); });
                           if(it!=cars.end()){
                        cout<<"Condition of returning the car(Good,Excellent,Damaged): ";
                        string condition;

                        cin>>condition;
                     for(auto& car: cars){
                        if(carname==car.getModel()){
                            if(condition==car.getCondition())
                            updateEmployeeInfo("employee.txt", username,0,0);
                            else if(condition=="Damaged"&&car.getCondition()=="Excellent")
                             updateEmployeeInfo("employee.txt", username,-2,0);
                             else if(car.getCondition()=="Damaged"&&(condition=="Excellent"))
                             updateEmployeeInfo("employee.txt", username,2,0);
                             else if(car.getCondition()=="Damaged"&&(condition=="Good"))
                              updateEmployeeInfo("employee.txt", username,1,0);
                              else if(car.getCondition()=="Good"&&(condition=="Excellent"))
                              updateEmployeeInfo("employee.txt", username,1,0);
                              else
                               updateEmployeeInfo("employee.txt", username,-1,0);
                        }
                        }
                        
                    return_request("car.txt", carname, condition, 1, "None");
                    cout<<"Enter number of days after which you are returning: ";
                    int days;
                    cin>>days;
                    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
                    for ( auto& car : cars) {
                            if(carname==car.getModel()){
                                totalcost=days*car.getRentCost();
                                if(days-car.getreturnday()>0){
                                totalfine=(days-car.getreturnday())*fineRate;
                                }
                               
                            }}
                    
                    updateEmployeeInfo("employee.txt", username,0,totalfine);
                    cout<<" Cost to pay: "<<totalcost*0.85<<endl;
                    cout<<" Fine to pay: "<<totalfine<<endl;
                           }
                           else
                           cout<<"This car is not rented by you "<<endl;
                   
    }}
    else if(operation==3)
    {  vector<Employee> employees=Employee::readEmployeeData();
        cout<<"Fine till date "<<endl;
          for (auto& employee : employees) {
                            if(username==employee.getUsername()){
                             cout<<employee.getFineDue()<<endl;
                            }
                        }
 cout<<"Fine you are paying now";
                    int finepaying;
                    cin>>finepaying;
                    Employee employee;
                    employee.clearfine_dues(finepaying,totalfine,"employee.txt",username);
    }
    else {
       return; 
    }
    employeeoptions(employees,cars,username,password);
}
catch (const std::exception& e) {
        // Handle exceptions here, you can print an error message or log the exception.
        std::cerr << "Error occurred " << e.what() << std::endl;
    }
}


void updateoperations()
{try{
            cout<<"Enter 1 to make change in Car Database,2 to make change in Customer DataBase ,3 to make change in Employee DataBase,4 to return back "<<endl;
       int choice;
       cin>>choice;
       if(choice==4)
       return;
       cout<<"Enter 1 for update,2 for delete,3 for add ,4 for Search "<<endl;
       int operation;
       cin>>operation;
       if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        throw invalid_argument("Invalid input. Please enter a valid option.");
    }
       if(choice==1){
       
       Carchange(operation);   
        }   
      else if(choice==2){
         modifyCustomer(operation);  
        }
       else if(choice==3)
         {
       modifyEmployee(operation); 
       }
       
       updateoperations();
}
catch (const std::exception& e) {
        // Handle exceptions here, you can print an error message or log the exception.
        std::cerr << "Error occurred " << e.what() << std::endl;
    }

}
void login()
{
      vector<Car> cars = Car::readCarData();
      vector<Customer> customers = Customer::readCustomerData();
      vector<Employee> employees=Employee::readEmployeeData();
    cout << "Enter 1 for customer, 2 for employee, and 3 for manager, 4 for logout :"<<endl;
    int verification;
    cin >> verification;
     string username;
    if (verification == 1) {
        cout << "Are you already registered? (Type YES if already registered or NO)  "<<endl;
        string answer;
        cin >> answer;
      
        if (answer == "YES") {
            cout << "Enter username: "<<endl;
            
            cin >> username;

            vector<Customer> customers = Customer::readCustomerData();
            auto it = find_if(customers.begin(), customers.end(),
                              [username](const Customer& c) { return c.getUsername() == username; });

            if (it != customers.end()) {
                cout << "Enter password: "<<endl;
                string password;
                cin >> password;
                
                if (it->authenticate(password)) {
                    cout << "Login successful! Welcome, " << it->getUsername() << "!\n";
                    customeroptions(customers, cars,username,password);
                 
                    }

             else {
                    cout << "Incorrect password. Please try again.\n";
                }} 
             else {
                cout << "Username not found. Please register.\n";
            }}
            else
            {
                 Manager manager;
            manager.registerNewCustomer();
            }
        
    } else if (verification == 3) {
        cout<<"Enter username to access datbases(For this Assignment I have 1 manager whose username is manager) : "<<endl;
        string uname;
        cin>>uname;
        if(uname==usernameglobal)
        {
            int pass;
            cout<<"Enter password to access datbases(For this Assignment I have 1 manager whose password is 123456) : "<<endl;
            cin>>pass;
            if(passwordglobal==pass){
           updateoperations();
           }
        else
            cout<<"  Authentication failed  "<<endl;
        }
        else
        cout<<"Wrong username"<<endl;
       

    }
    else if(verification==2)
    {
        cout << "Are you already registered? (Type YES if already registered or NO)"<<endl;
        string answer;
        cin >> answer;

        if (answer == "YES") {
            cout << "Enter username: "<<endl;
            
            cin >> username;

            vector<Employee> employees = Employee::readEmployeeData();
            auto it = find_if(employees.begin(), employees.end(),
                              [username](const Employee& c) { return c.getUsername() == username; });

            if (it != employees.end()) {
                cout << "Enter password: "<<endl;
                string password;
                cin >> password;

                if (it->authenticate(password)) {
                    cout << "Login successful! Welcome, " << it->getUsername() << "!\n";
                     employeeoptions(employees, cars,username,password);
                    }
                    else {
                    cout << "Incorrect password. Please try again.\n";
                }}
             else {
                cout << "Username not found. Please register.\n";
            }}
            else
            {
                 Manager manager;
            manager.registerNewEmployee();
            }
    }
else{
    return ;
}
login();
}
int main() {
    login();
    
     return 0;
}
