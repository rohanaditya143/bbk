#include <iostream>
#include <vector>
#include <ctime>
#include <bsoncxx/builder/stream/document.hpp>
#include <optional>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
using namespace std;

class Car;
class Customer;

class User {
    public:
        User(string name, int ID,string password)
            : name(name), ID(ID), password(password) {}
        virtual void returnCar(Car& car) =0;
        virtual void showInfo() const =0;
        virtual void rentCar(const Car& car) =0;
         virtual int getID() const = 0;

    protected:
        string name;
        int ID;
        string password;
};

class Car{
    public:
        Car(int ID, string model, string condition, string otherDetails)
            :ID(ID), model(model), condition(condition), otherDetails(otherDetails) {}

        void rentCar(User& user) ;
        void returnCar(User& user);

         string getOtherDetails() const {
            return otherDetails;
        }
        string getCondition() const {
            return condition;
        }

       
        string getModel() const {
            return model;
        }


        time_t getDueDate() const{
            cout << "Due Date: " << dueDate << endl;
            return dueDate;
        }

      
        void showInfo() const {
            cout << "ID: "<< ID << "Model: " << model << ", Condition: " << condition << ", Other Details: " << otherDetails << endl;
        }

        bool isRented() const {
            return rented;
        }

        void setID(const int newID) {
             ID = newID;
        }

        void setModel(const string& newModel) {
             model = newModel;
        }
         void setCondition(const string& newCondition) {
             condition = newCondition;
        }

        void setOtherDetails(const string& newOtherDetails) {
             otherDetails = newOtherDetails;
        }


        int getID() const ;

    private:
      string condition;
        string otherDetails;
        bool rented;
        time_t dueDate;
        int ID;
        string model;
        

};

void Car::rentCar(User& user) {
    rented = true;
    dueDate =time(0) + 7*24*60*60;
    user.rentCar(*this);
    cout<<"car rented succesfully , thank you "<<endl;
}

void Car::returnCar(User& user){
   if(rented==true){
    rented = false;
    user.returnCar(*this);
   }else{
    cout << "No cars to return"<< endl;
   }
}

class Customer : public User{
    public:
        Customer(string name, int ID, string password, int rentedCars = 0, int fineDue = 0, int customerRecord =50)
            :User(name, ID, password), rentedCars(rentedCars), fineDue(fineDue), customerRecord(customerRecord) {}

        void returnCar(Car& car) override;
        void showInfo() const override;
        void rentCar(const Car& car) override;

        void clearDue();
        int getID() const override;

        string getName() const {
            return name;
        }

        string getPassword() const {
            return password;
        }

        int getFineDue() const {
            return fineDue;
        }
        int getRentedCars() const {
            cout << "Rented Cars: " << rentedCars << endl;
            return rentedCars;
        }

        int getCustomerRecord() const {
            cout << "Customer Record: " << customerRecord << endl;
            return customerRecord;
        }


        void setRentedCars(const int newRentedCars) {
             rentedCars = newRentedCars;
        }

        void setFineDue(const int newFineDue) {
             fineDue = newFineDue;
        }

        void setCustomerRecord(const int newCustomerRecord) {
             customerRecord = newCustomerRecord;
        }

        void setID(const int newID) {
             ID = newID;
        }
        void setName(const string newName) {
             name = newName;
        }

        void setPassword(const string newPassword) {
             password = newPassword;
        }

        

    private:
        int rentedCars;
        int fineDue;
        int customerRecord;
};

int Customer::getID() const {
    return ID;
}

void Customer::rentCar(const Car& car)  {
    if(car.isRented()){
        if (rentedCars <3 && customerRecord >= 30){
            rentedCars++;
            cout << "Car rented successfully" << rentedCars << endl;
        }
        else{
            cout << "Cannot rent more cars or insufficient customerRecord" << endl;
        }
    }else{
        cout << "Car not available" << endl;
    }
    
}

void Customer::returnCar(Car& car) {
    rentedCars--;
    if (time(0) > car.getDueDate()) {
        fineDue += (time(0) - car.getDueDate()) / (24 * 60 * 60) * 10;  //fine of 10 ruppes per day
    }
}

void Customer::showInfo() const {
    cout << "Customer Name: " << name << ", ID: " << ID << ", Customer Record: " << customerRecord << endl;
}

void Customer::clearDue() {
    fineDue = 0;
}

class Employee : public User {
public:
    Employee(string name, int ID, string password,int rentedCars = 0, int fineDue = 0, int employeeRecord = 70)
        : User(name, ID, password),rentedCars(rentedCars), fineDue(fineDue), employeeRecord(employeeRecord) {}

    void returnCar(Car& car) override;
    void showInfo() const override;
    void rentCar(const Car& car) override;

    void clearDue();
    int getID() const override;


    string getPassword() const {
        return password;
    }


    string getName() const {
        return name;
    }

    int getFineDue() const {
        return fineDue;
    }


    int getRentedCars() const {
        cout << "Rented Cars: " << rentedCars << endl;
        return rentedCars;
    }


    int getEmployeeRecord() const {
        cout << "Employee Record: " << employeeRecord << endl;
        return employeeRecord;
    }

        
        void setPassword(const string newPassword) {
             password = newPassword;
        }


        void setName(const string newName) {
             name = newName;
        }
        void setRentedCars(const int newRentedCars) {
             rentedCars = newRentedCars;
        }

        void setFineDue(const int newFineDue) {
             fineDue = newFineDue;
        }

        void setEmployeeRecord(const int newEmployeeRecord) {
             employeeRecord = newEmployeeRecord;
        }
        void setID(const int newID) {
             ID = newID;
        }



private:
int fineDue;
    int employeeRecord;
    int rentedCars;
    
};

void Employee::rentCar(const Car& car) {
    if(car.isRented()){
        if (rentedCars < 2 && employeeRecord >= 40) {
        rentedCars++;
        cout << "Car rented successfully with a 15% discount!" << endl;
    } else {
        cout << "Cannot rent more cars or insufficient employee record." << endl;
    }
    }else{
        cout << "Car not Available" << endl;
    }
    
}

void Employee::returnCar(Car& car) {
    rentedCars--;
    if (time(0) > car.getDueDate()) {
        fineDue += (time(0) - car.getDueDate()) / (24 * 60 * 60) * 10;  //fine of 10 ruppes per day
    }
}

void Employee::showInfo() const {
    cout << "Employee Name: " << name << ", ID: " << ID << ", Employee Record: " << employeeRecord << endl;
}

void Employee::clearDue() {
    fineDue = 0;
}

class Manager : public User {
public:
    Manager(string name, int ID, string password)
        : User(name, ID, password) {}

    void showInfo() const override;
    int getID() const override;
};



void Manager::showInfo() const {
    cout << "Manager Name: " << name << ", ID: " << ID << endl;
}


int Manager::getID() const {
    return ID;
}

int Car::getID() const {
    return ID;
}
int Employee::getID() const {
    return ID;
}

class Database {
public:
    Database(const string& connectionString);


    void addCustomer(const Customer& customer);
    void updateCustomer(const Customer& customer);
    void deleteCustomer(const Customer& customer);
    bool searchCustomer(const Customer& customer);

    void showAllCars() const;
    void showAllCustomers() const;
    void showAllEmployees() const;

    bool verifyCustomer(int customerId, const string& password) const;
    bool verifyEmployee(int employeeId, const string& password) const;
    bool verifyManager(int managerId, const string& password) const;


    void addCar(const Car& car);
    void updateCar(const Car& car);
    void deleteCar(const Car& car);
    bool searchCar(const Car& car);

    void addEmployee(const Employee& employee);
    void updateEmployee(const Employee& employee);
    void deleteEmployee(const Employee& employee);
    bool searchEmployee(const Employee& employee);

    

    void clearCollection(const string& collectionName);


private:
    mongocxx::instance instance;
    mongocxx::client client;      
    mongocxx::database db;        


    
    bsoncxx::document::value createCarDocument(const Car& car) const;
    bsoncxx::document::value createCustomerDocument(const Customer& customer) const;
    bsoncxx::document::value createEmployeeDocument(const Employee& employee) const;
};



Database::Database(const string& connectionString)
    : client(mongocxx::uri(connectionString)), db(client["carRentalDB"]) {
    // Initialize MongoDB
    if (!client) {
        cerr << "Error: Failed to connect to the database." << endl;
    }
    else{
        cout << "Connected to the database successfully!" << endl;
    }
}


bsoncxx::document::value Database::createCarDocument(const Car& car) const {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;
    using bsoncxx::builder::stream::finalize;

    return document{}
        << "model" << car.getModel()
        << "id" << car.getID()
        << "condition" << car.getCondition()
        << "otherDetails" << car.getOtherDetails()
        << "rented" << car.isRented()
        << "dueDate" << bsoncxx::types::b_date{chrono::system_clock::from_time_t(car.getDueDate())}
        << bsoncxx::builder::stream::finalize;
}


bsoncxx::document::value Database::createCustomerDocument(const Customer& customer) const {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;
    using bsoncxx::builder::stream::finalize;

    return document{}
        << "name" << customer.getName()
        << "id" << customer.getID()
        << "password" << customer.getPassword()
        << "rentedCars" << customer.getRentedCars()
        << "fineDue" << customer.getFineDue()
        << "customerRecord" << customer.getCustomerRecord()
        << bsoncxx::builder::stream::finalize;
}

bsoncxx::document::value Database::createEmployeeDocument(const Employee& employee) const {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::open_document;
    using bsoncxx::builder::stream::close_document;
    using bsoncxx::builder::stream::finalize;

    return document{}
        << "name" << employee.getName()
        << "id" << employee.getID()
        << "password" << employee.getPassword()
        << "rentedCars" << employee.getRentedCars()
        << "fineDue" << employee.getFineDue()
        << "employeeRecord" << employee.getEmployeeRecord()
        << bsoncxx::builder::stream::finalize;
}

// Add a car to the database
void Database::addCar(const Car& car) {
    auto collection = db["cars"];
    auto document = createCarDocument(car);
    collection.insert_one(document.view());
}


void Database::updateCar(const Car& car) {
    auto collection = db["cars"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << car.getID() << bsoncxx::builder::stream::finalize;
    auto update = createCarDocument(car);
    collection.update_one(filter.view(), update.view());
}


void Database::deleteCar(const Car& car) {
    auto collection = db["cars"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << car.getID() << bsoncxx::builder::stream::finalize;
    collection.delete_one(filter.view());
}


bool Database::searchCar(const Car& car) {
    auto collection = db["cars"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << car.getID() << bsoncxx::builder::stream::finalize;

    auto result = collection.find_one(filter.view());
    if (result) {
        bsoncxx::document::view document = result->view();
        return true;
    } else {
        cout << "couldn't find this car in the database" << endl;
        return false;
    }
}


void Database::addCustomer(const Customer& customer) {
    auto collection = db["customers"];
    auto document = createCustomerDocument(customer);
    collection.insert_one(document.view());
}


void Database::updateCustomer(const Customer& customer) {
    auto collection = db["customers"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << customer.getID() << bsoncxx::builder::stream::finalize;
    auto update = createCustomerDocument(customer);
    collection.update_one(filter.view(), update.view());
}

void Database::deleteCustomer(const Customer& customer) {
    auto collection = db["customers"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << customer.getID() << bsoncxx::builder::stream::finalize;
    collection.delete_one(filter.view());
}

bool Database::searchCustomer(const Customer& customer) {
    auto collection = db["customers"];
    auto filter = bsoncxx::builder::stream::document{} << "ID" << customer.getID() << bsoncxx::builder::stream::finalize;

    auto result = collection.find_one(filter.view());
    if (result) {
        bsoncxx::document::view document = result->view();
        return true;
    } else {
        cout << "Couldn't find the Customer in the database " << endl;
        return false;
    }
}

void Database::addEmployee(const Employee& employee) {
    auto collection = db["employees"];
    auto document = createEmployeeDocument(employee);
    collection.insert_one(document.view());
}

void Database::updateEmployee(const Employee& employee) {
    auto collection = db["employees"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << employee.getID() << bsoncxx::builder::stream::finalize;
    auto update = createEmployeeDocument(employee);
    collection.update_one(filter.view(), update.view());
}

void Database::deleteEmployee(const Employee& employee) {
    auto collection = db["employees"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << employee.getID() << bsoncxx::builder::stream::finalize;
    collection.delete_one(filter.view());
}

bool Database::searchEmployee(const Employee& employee) {
    auto collection = db["employees"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << employee.getID() << bsoncxx::builder::stream::finalize;

    auto result = collection.find_one(filter.view());
    if (result) {
        bsoncxx::document::view document = result->view();
        return true;
    } else {
        cout << "Couldn't find the employee in the database " << endl;
        return false;
    }
}

void Database::showAllCars() const {
    auto collection = db["cars"];
    auto cursor = collection.find({});
    for (auto&& doc : cursor) {
        cout << bsoncxx::to_json(doc) << endl;
    }
}

void Database::showAllCustomers() const {
    auto collection = db["customers"];
    auto cursor = collection.find({});
    for (auto&& doc : cursor) {
        cout << bsoncxx::to_json(doc) << endl;
    }
}

void Database::showAllEmployees() const {
    auto collection = db["employees"];
    auto cursor = collection.find({});
    for (auto&& doc : cursor) {
        cout << bsoncxx::to_json(doc) << endl;
    }
}

bool Database::verifyCustomer(int customerId, const string& password) const {
    auto collection = db["customers"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << customerId << "password" << password << bsoncxx::builder::stream::finalize;

    auto result = collection.find_one(filter.view());
    return result ? true : false;
}

bool Database::verifyEmployee(int employeeId, const string& password) const {
    auto collection = db["employees"];
    auto filter = bsoncxx::builder::stream::document{} << "id" << employeeId << "password" << password << bsoncxx::builder::stream::finalize;

    auto result = collection.find_one(filter.view());
    return result ? true : false;
}

bool Database::verifyManager(int managerId, const string& password) const {
    const int knownManagerId = 1;
    const string knownManagerPassword = "manager123";

    return (managerId == knownManagerId) && (password == knownManagerPassword);
}

int main() {

    string atlasConnectionString = "mongodb+srv://havishrayavarapu:Havish@cluster0.zanhlil.mongodb.net/";
    Database database(atlasConnectionString);

    Car car1(1,"BMW X5", "Average", "Blue");
    Car car2(2,"Chevrolet Corvette", "Excellent", "black");
    Car car3(3,"Honda Civic", "Average", "violet");
    Car car4(4,"Ford Mustang", "Excellent", "red");
    Car car5(5,"Toyota Camry", "Fair", "black");


    Customer customer1("Havish", 1, "pass123",0, 10, 20);
    Customer customer2("Nalini", 2, "pass789", 0, 5, 40);
    Customer customer3("Rohan", 3, "pass101", 3, 15, 80);
    Customer customer4("Vijay", 4, "pass202", 2, 8, 55);
    Customer customer5("Yashwanth", 5, "pass303", 1, 5, 65);

    Employee employee1("Nishanth", 11, "empPass", 2, 24, 70);
    Employee employee2("Karthik", 12, "empPass123", 1, 16, 80);
    Employee employee3("Roshan", 13, "empPass456", 3, 27, 90);
    Employee employee4("Haneeswar", 14, "passabc", 3, 22, 30);
    Employee employee5("Nikhitha", 15, "empPass789", 0, 29, 60);

    int newID;
    
    vector<Customer> customers;
    
    int customerId;
    string customerPassword;

    int updateCustomerID;
    Customer customerToUpdate(" ",0," ",0,0,0);

    string newName,newPassword;
    int newRentedCars, newFineDue, newCustomerRecord;


    vector<Employee> employees;

    vector<Car> cars;

    int carID;

    string carModel;
    int updateCarID;

    string newModel, newCondition, newOtherDetails;
    Car carToUpdate(0, " "," "," ");

    int employeeId;
    string employeePassword;

    int updateEmployeeID;
    Employee employeeToUpdate(" ",0," ",0,0,0);

    
    int newEmployeeRecord;

    customers.push_back(customer1);
    customers.push_back(customer2);
    customers.push_back(customer3);
    customers.push_back(customer4);
    customers.push_back(customer5);

    employees.push_back(employee1);
    employees.push_back(employee2);
    employees.push_back(employee3);
    employees.push_back(employee4);
    employees.push_back(employee5);


    cars.push_back(car1);
    cars.push_back(car2);
    cars.push_back(car3);
    cars.push_back(car4);
    cars.push_back(car5);

    
    int choice;
    do {
        
        cout << "Girls car rental system\n";
        cout << "1. Customer\n";
        cout << "2. Employee\n";
        cout << "3. Manager\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                 
                  cout << "Enter Customer ID: ";
                  cin >> customerId;
                  cout << "Enter Customer Password: ";
                  cin >> customerPassword;

                  
                  if (database.verifyCustomer(customerId, customerPassword)) {
                    cout << "Customer Login Successful!\n";
                    int customerChoice;
                    cout << "\n** Car Rental System Customer Menu**\n";
                    cout << "1. Show profile\n";
                    cout << "2. Rent Car\n";
                    cout << "3. Return Car\n";
                    cout << "4. Rented Cars\n";
                    cout << "5. Customer Record\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> customerChoice;

                    switch(customerChoice) {
                        case 1:
                            for (const auto& customer : customers) {
                                if (customer.getID() == customerId) {
                                    customer.showInfo();
                                    break;  
                                }
                            }
                            break;

                        case 2:
                            database.showAllCars() ;
                            
                            cout << "select your car id: ";
                            cin >> carID;
                            for ( auto& car : cars) {
                               if (car.getID() == carID) {
                                 for( auto& customer : customers) {
                                    if(customer.getID() == customerId)
                                       car.rentCar(customer);
                                       cout << "car rented successfully";
                                   break;  
                                }
                             }
                            }
                            break;
                            
                            break;

                        case 3:
                            cout << "select your car id that you wanted to return: ";
                            cin >> carID;
                            for ( auto& car : cars) {
                               if (car.getID() == carID) {
                                 for( auto& customer : customers) {
                                    if(customer.getID() == customerId){
                                       car.returnCar(customer);
                                    }
                                       
                                   break;  
                                }
                             }
                            }
                            
                            break;

                        case 4:
                            for (const auto& customer : customers) {
                                if (customer.getID() == customerId) {
                                    customer.getRentedCars();
                                    break;  
                                }
                            }
                            break;
                            
                            break;

                        case 5:
                            for (const auto& customer : customers) {
                                if (customer.getID() == customerId) {
                                    customer.getCustomerRecord();
                                    break;  
                                }
                            }
                            break;
                    
                        case 0:
                            
                            break;

                        default:
                           cout << "Invalid choice. Please enter a valid option.\n"; 
                           break;
                    }
                    
                  } else {
                    cout << "Invalid Customer ID or Password. Login failed.\n";
                  }

                 break;
                  
                  
            
            case 2:

                  cout << "Enter Employee ID: ";
                  cin >> employeeId;
                  cout << "Enter Employee Password: ";
                  cin >> employeePassword;
                  if (database.verifyEmployee(employeeId, employeePassword)) {
                    cout << "Employee Login Successful!\n";
                    int employeeChoice;
                    cout << "\n** Car Rental System Employee Menu**\n";
                    cout << "1. Show profile\n";
                    cout << "2. Rent Car\n";
                    cout << "3. Return Car\n";
                    cout << "4. Rented Cars\n";
                    cout << "5. Employee Record\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> employeeChoice;

                    switch(employeeChoice) {
                        case 1:
                            for (const auto& employee : employees) {
                                if (employee.getID() == employeeId) {
                                    employee.showInfo();
                                    break; 
                                }
                            }break;

                        case 2:
                            database.showAllCars() ;
                            
                            cout << "select your car id: ";
                            cin >> carID;
                            for ( auto& car : cars) {
                               if (car.getID() == carID) {
                                 for( auto& employee : employees) {
                                    if(employee.getID() == employeeId)
                                       car.rentCar(employee);
                                       cout << "car rented successfully";
                                   break; 
                                }
                             }
                            }
                            break;
                            
                            break;

                        case 3:
                            
                            cout << "select your car id that you wanted to return: ";
                            cin >> carID;
                            for ( auto& car : cars) {
                               if (car.getID() == carID) {
                                 for( auto& employee : employees) {
                                    if(employee.getID() == employeeId){
                                       car.returnCar(employee);
                                    }
                                       
                                   break;  
                                }
                             }
                            }
                            break;

                        case 4:
                            for (const auto& employee : employees) {
                                if (employee.getID() == employeeId) {
                                    employee.getRentedCars();
                                    break;  
                                }
                            }
                            break;

                        case 5:
                            for (const auto& employee : employees) {
                                if (employee.getID() == employeeId) {
                                    employee.getEmployeeRecord();
                                    break;  
                                }
                            }break;

                        case 0:
                         
                        break;

                        default:
                           cout << "Invalid choice. Please enter a valid option.\n";
                           break;
                    }  
                    
                  } else {
                    cout << "Invalid Employee ID or Password. Login failed.\n";
                  }

                  break;
                    

            case 3:
                int managerId;
                string managerPassword;

                cout << "Enter Manager ID: ";
                cin >> managerId;
                cout << "Enter Manager Password: ";
                cin >> managerPassword;

                if (database.verifyManager(managerId, managerPassword)) {
                  cout << "Manager Login Successful!\n";

                  int managerChoice;
                  cout << "\n** Car Rental System manager Menu**\n";
                  cout << "1. show all cars\n";
                  cout << "2. show all customers\n";
                  cout << "3. show all employees\n";
                  cout << "4. database operations for cars\n";
                  cout << "5. database operations for customers\n";
                  cout << "6. database operations for employee\n";
                  cout << "0. Exit\n";
                  cout << "Enter your choice: ";
                  cin >> managerChoice;

                  switch(managerChoice) {
                    case 1:
                        database.showAllCars();
                        break;

                    case 2:
                        database.showAllCustomers();
                        break;

                    case 3:
                        database.showAllEmployees();
                        break;

                    case 4:
                        int carOperation;
                           cout << "\n** Car Rental System manager operations**\n";
                           cout << "1. update car\n";
                           cout << "2. add a car\n";
                           cout << "3. delete a car\n";
                           cout << "0. Exit\n";
                           cout << "Enter your choice: ";
                           cin >> carOperation;

                           switch(carOperation){
                            case 1:
                                  
                                  cout << "Enter the ID of the car to update: ";
                                  cin >> updateCarID ;

                                  

                                  carToUpdate.setID(updateCarID);

                                  if (database.searchCar(carToUpdate)) {
                                   // Car found, proceed with update
                                     

                                     cout << "Enter the new model: ";
                                     cin >> newModel;

                                     cout << "Enter the new condition: ";
                                     cin >> newCondition;

                                     cout << "Enter the new other details: ";
                                     cin >> newOtherDetails;

                                     carToUpdate.setModel(newModel);
                                     carToUpdate.setCondition(newCondition);
                                     carToUpdate.setOtherDetails(newOtherDetails);

                                     database.updateCar(carToUpdate);
                                     cout << "Car details updated successfully!\n";
                                  } else {
                                     cout << "Car not found. Update failed.\n";
                                  }
                                  break;
                               
                                
                            case 2:
                                 {
                                     cout << "Enter the ID of the new car: ";
                                     cin >> newID;

                                     cout << "Enter the model of the new car: ";
                                     cin >> newModel;

                                     cout << "Enter the condition of the new car: ";
                                     cin >> newCondition;

                                     cout << "Enter the otherDetails of the new car: ";
                                     cin >> newOtherDetails;

                                     carToUpdate.setID(newID);
                                     carToUpdate.setModel(newModel);
                                     carToUpdate.setCondition(newCondition);
                                     carToUpdate.setOtherDetails(newOtherDetails);

                                     database.addCar(carToUpdate);
                                     cout << "New car added to the database!\n";
                                 }
                                 break;

                            case 3:
                                 {
                                     cout << "Enter the ID of the car to delete: ";
                                     cin >> updateCarID;


                                     for (const auto& car : cars) {
                                          if (car.getID() == updateCarID) {
                                            
                                            database.deleteCar(car);
                                            cout << "Car deleted from the database!\n";

                                          }
                                          
                                     }
                                 }
                                 break;

                            case 0:
                                 
                                break;

                            default:
                                cout << "Invalid choice. Please enter a valid option.\n";
                                break;
                           }
                        break;

                     case 5:
                        int customerOperation;
                           cout << "\n** Car Rental System manager operations**\n";
                           cout << "1. update customer\n";
                           cout << "2. add a customer\n";
                           cout << "3. delete a customer\n";
                           cout << "0. Exit\n";
                           cout << "Enter your choice: ";
                           cin >> customerOperation;

                           switch(customerOperation){
                            case 1:
                                  
                                  cout << "Enter the ID of the customer to update: ";
                                  cin >> updateCustomerID;

                                  customerToUpdate.setID(updateCustomerID);

                                  if (database.searchCustomer(customerToUpdate)) {
                                       
                                      string newName,newPassword;
                                      int newRentedCars, newCustomerFine, updateCustomerRecord;

                                      cout << "Enter the new name: ";
                                      cin >> newName;
                                      for (const auto& customer : customers) {
                                          if (customer.getID() == updateCustomerID) {
                                             newPassword=customer.getPassword();
                                          }
                                      }
                                      cout << "Enter the new number of rented cars: ";
                                      cin >> newRentedCars;
                                      cout << "Enter the new value of fine_due: ";
                                      cin >> newFineDue;
                                      cout << "Enter the new value of customer record value: ";
                                      cin >> updateCustomerRecord;

                                      customerToUpdate.setName(newName);
                                      customerToUpdate.setPassword(newPassword);
                                      customerToUpdate.setRentedCars(newRentedCars);
                                      customerToUpdate.setFineDue(newFineDue);
                                      customerToUpdate.setCustomerRecord(newCustomerRecord);

                                      database.updateCustomer(customerToUpdate);
                                      cout << "Customer details updated successfully!\n";
                                  } else {
                                      cout << "Customer not found. Update failed.\n";
                                  }
                                  break;
                                
                            case 2:
                                  {

                                     cout << "Enter the name of the new customer: ";
                                     cin.ignore(); 
                                     getline(cin, newName);


                                     cout << "Enter the id of the new customer: ";
                                     cin >> newID;

                                     cout << "Enter the password of the new customer: ";
                                     cin >> newPassword;

                                     cout << "Enter the number of rented cars for the new customer: ";
                                     cin >> newRentedCars;

                                     cout << "Enter the fine due for the new customer: ";
                                     cin >> newFineDue;

                                     cout << "Enter the customer record for the new customer: ";
                                     cin >> newCustomerRecord;

                                      customerToUpdate.setID(newID);
                                      customerToUpdate.setName(newName);
                                      customerToUpdate.setPassword(newPassword);
                                      customerToUpdate.setRentedCars(newRentedCars);
                                      customerToUpdate.setFineDue(newFineDue);
                                      customerToUpdate.setCustomerRecord(newCustomerRecord);

                                     database.addCustomer(customerToUpdate);
                                     cout << "New customer added to the database!\n";
                                  }
                                  break;

                            case 3:
                                  {
                                     cout << "Enter the ID of the customer to delete: ";
                                     cin >> updateCustomerID;

                                     for (const auto& customer : customers) {
                                          if (customer.getID() == updateCustomerID) {
                                            
                                            database.deleteCustomer(customer);
                                            cout << "Customer deleted from the database!\n";
                                          }
                                          
                                     }

                                  }
                                  break;

                            case 0:
                                 
                                break;

                            default:
                                cout << "Invalid choice. Please enter a valid option.\n";
                                break;
                           }
                        break;
                     case 6:
                              int employeeOperation;
                           cout << "\n** Car Rental System manager operations**\n";
                           cout << "1. update employee\n";
                           cout << "2. add a employee\n";
                           cout << "3. delete a employee\n";
                           cout << "0. Exit\n";
                           cout << "Enter your choice: ";
                           cin >> employeeOperation;

                              switch(employeeOperation){
                                case 1:
                                
                                cout << "Enter the ID of the employee to update: ";
                                cin >> updateEmployeeID;

                                employeeToUpdate.setID(updateEmployeeID);

                                if (database.searchEmployee(employeeToUpdate)) {
                                     
                                     cout << "Enter the new name: ";
                                     cin >> newName;
                                      for (const auto& employee : employees) {
                                          if (employeeToUpdate.getID() == updateEmployeeID) {
                                             newPassword=employeeToUpdate.getPassword();
                                          }
                                      }

                                     cout << "Enter the new number of rented cars: ";
                                     cin >> newRentedCars;

                                     cout << "Enter the new fine due: ";
                                     cin >> newFineDue;

                                     cout << "Enter the new employee record: ";
                                     cin >> newEmployeeRecord;

                                      employeeToUpdate.setName(newName);
                                      employeeToUpdate.setPassword(newPassword);
                                      employeeToUpdate.setRentedCars(newRentedCars);
                                      employeeToUpdate.setFineDue(newFineDue);
                                      employeeToUpdate.setEmployeeRecord(newEmployeeRecord);
 
                                     database.updateEmployee(employeeToUpdate);
                                     cout << "Employee details updated successfully!\n";
                                } else {
                                     cout << "Employee not found. Update failed.\n";
                                }
                                
                                break;

                            case 2:
                                {

                                     cout << "Enter the name of the new employee: ";
                                     cin.ignore(); 
                                     getline(cin, newName);

                                     cout << "Enter the id of the new employee: ";
                                     cin >> newID;

                                     cout << "Enter the password of the new employee: ";
                                     cin >> newPassword;

                                     cout << "Enter the number of rented cars for the new employee: ";
                                     cin >> newRentedCars;

                                     cout << "Enter the fine due for the new employee: ";
                                     cin >> newFineDue;

                                     cout << "Enter the employee record for the new employee: ";
                                     cin >> newEmployeeRecord;

                                      employeeToUpdate.setName(newName);
                                      employeeToUpdate.setID(newID);
                                      employeeToUpdate.setPassword(newPassword);
                                      employeeToUpdate.setRentedCars(newRentedCars);
                                      employeeToUpdate.setFineDue(newFineDue);
                                      employeeToUpdate.setEmployeeRecord(newEmployeeRecord);

                                     database.addEmployee(employeeToUpdate);
                                     cout << "New employee added to the database!\n";
                                }
                                break;

                            case 3:
                                {
                                     cout << "Enter the ID of the employee to delete: ";
                                     cin >> updateEmployeeID;

                                     for (const auto& employee : employees) {
                                          if (employee.getID() == updateEmployeeID) {
                                            database.deleteEmployee(employee);
                                            cout << "Employee deleted from the database!\n";
                                          }
                                     }
                                }
                                break;

                            case 0: 
                               break;

                            default:
                               cout << "Invalid choice for Database Operations.\n";
                               break;
                           }

                        break;

                    case 0:
                        break;

                    default:
                        cout << "Invalid choice for Database Operations.\n";
                        break;

                  }
                } else {
                    cout << "Invalid Manager ID or Password. Login failed.\n";
                }

            
        }
       

    } while (choice != 0);

    return 0;
}