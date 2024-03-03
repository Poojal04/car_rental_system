# Car Rental Management System

A comprehensive Car Rental Management System built in C++ to streamline car rental operations.

There are three databses:
They will be there in the zip file by the name Customer.txt,Car.txt,employee.txt

1.Car:This has several rows where each row store the data of one Car.

Database is stored in the format:
**model,RegistrationNumber,condition,cost_per_day,available,to_whom_Car_is_rented,return_Days**

It has its getter functions as member class and other essential member classes like writeCarData,ReadCarData,etc.

2.Customer:This has several rows where each row store the data of one Customer.
Database is stored in the format:
**username,password,ID,customerRecord,Total FineDue**

It has its getter functions and other member functions.

3.Employee:This has several rows where each row store the data of one Employee.
Database is stored in the format:
**username,password,ID,EmployeeRecord,Total FineDue**
It has its getter functions and other member functions.

Defensive Programming:
1.I have used **try catch block** whenever the input is string instead of int in integer variable input.
2.Understandable variable name and functions.

## Assumptions

1.All the inputs are taken using cin so space should not be there between entered string.

2.Unique attribute for Customer/Employee is their name by which I am updating/deleting.

3.Unique attribute for Car is CarName.

4.In my program there is only one manager whose username and id I have declared as global variable as working in all the cases are same so there is no database for managers.For authentication of manager:
**Username:manager, password:123456.**

5.The customer/employee pays the amount of rent(not including fine) of a particular car whenever he/she returns the corresponding car.

So, clear dues function is for fine only.fine is impose per day .The cost of the car is also imposed per day.

Fine_rate is declared as constant global variable which is **5000**.When the car is getting returned then
total cost:No of days after which car is returned*Cost/day

**total fine:(No of days after which car is returned-no of days car was expected to return )*Fine_Rate[Extra days after return days*Fine_rate]**

6.The customer and employee will honestly tell the number of days for which they have rented the car and the condition in which they are returning while returning a car.

7.Based on the change in condition of car, the customer/employee rating will be updated.

8.The customer/employee will never pay the extra fine as that will make the fine attribute negative - a negative fine attribute would essentially mean that he has paid more fine so in future, he needs to pay less.

9.Condition for car is string which can take three string as input (Damaged/Good/Excellent).

10.The customer/employee rating will change if condition is changed .If condition is improved then rating will increase and if condition of car decreses then rating also decreases.

11.If car is available then it will be 1 else 0.If car is not rented then "towhom" attribute will store "None".A Customer/Employee can rent atmost cars equal to customer/employee rating.

12.For registering a new user,password is asked .**Default values set are:fine=0,average customer rating=5,id=total no of elements+1.**

13.When I add a new Car ,I assume it is not rented to anyone and is available.

14.The enterd strings case should be followed.It is case sensitive.

## User Options

## Employee/Customer Options

To access employee-specific functionalities, follow these steps:

1. Enter 1 to display all available cars and rent a car.
2. Enter 2 to return a rented car.
3. Enter 3 to clear dues.
4. Enter 4 to exit the Employee/Customer interface.

## Update Operations(Manager)

To make changes to the database, follow these steps:

1. Enter 1 to make changes in the Car Database.
2. Enter 2 to make changes in the Customer Database.
3. Enter 3 to make changes in the Employee Database.
4. Enter 4 to return back to the main menu.

For each database(customer,employee,car), choose an operation:(Manager)

1. Enter 1 for update.
2. Enter 2 for delete.
3. Enter 3 for add.
4. Enter 4 for search.

## Compiling and Executing

Compile the source code using g++ -std=c++11 main.cpp -o car_rental_system
Run the executable using ./car_rental_system
