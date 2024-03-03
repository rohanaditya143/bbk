# Car Rental Management System

## Overview
This Car Rental Management System is a comprehensive solution designed to facilitate the management of car rentals. Built using C++ and integrating MongoDB for data persistence, the system offers functionalities for customers, employees, and managers to rent cars, return cars, and manage user and car records effectively.

## Features
- *Customer Management:* Customers can rent cars, return them, and view their rental records.
- *Employee Management:* Employees have the capability to rent cars with special discounts, return cars, and access their rental records.
- *Car Management:* Add, update, and delete car records. Cars can be rented and returned, with their availability status being tracked.
- *Database Integration:* Utilizes MongoDB to store and manage user (customer and employee) and car data securely.
- *Authentication:* Verifies customer, employee, and manager credentials to ensure secure access to the system.

## Prerequisites
- MongoDB server (local or cloud)
- MongoDB C++ Driver installed and configured with your C++ development environment
- C++17 compiler

## Setup and Installation
1. *MongoDB Setup:*
   - Ensure that MongoDB is installed and running on your system. You can use MongoDB Atlas for a cloud-based setup.
   - Create a database named carRentalDB and collections customers, employees, and cars.
2. *Environment Setup:*
   - Make sure you have a C++17 compatible compiler.
   - Install the MongoDB C++ Driver. Follow the official MongoDB C++ Driver [installation guide](https://mongodb.github.io/mongo-cxx-driver/mongocxx-v3/installation/).

3. *Configuration:*
   - Update the MongoDB connection string in the main function to point to your MongoDB instance.

## Usage
Compile the project using your C++ compiler. For example, if you are using g++, you can compile the project as follows:

g++ -o carRentalSystem main.cpp -std=c++17 -lmongocxx -lbsoncxx ## Key Features
- *User Authentication*: Supports login for customers, employees, and managers with ID and password verification.
- *Car Management*: Allows adding, updating, deleting, and viewing cars in the database, with details such as model, condition, and rental status.
- *User Profiles*: Customers and employees can view their profiles, rent and return cars, and check their rental records. Customers have a rental limit based on their records, and employees have similar restrictions.
- *Managerial Functions*: Managers can perform database operations, including adding, updating, and deleting records for cars, customers, and employees.
- *Database Integration*: Utilizes MongoDB for data storage and retrieval, demonstrating CRUD operations within a C++ application.

## Classes and Their Functions
- *User*: An abstract base class representing a system user with common attributes and virtual functions for car rental activities.
- *Customer & Employee*: Derived from User, these classes implement specific functionalities such as renting and returning cars, with additional attributes like rental history and fines.
- *Car*: Represents a car in the system, with attributes for identification, model, condition, rental status, and other details.
- *Manager*: A special user with extended privileges for managing the database and system operations.
- *Database*: Handles connections and operations with the MongoDB database, including CRUD operations and user verification.

## MongoDB Integration
The system uses the MongoDB C++ Driver for interacting with the database. It showcases connecting to a database, creating BSON documents, and performing queries to manage data effectively.

## Conclusion
This project exemplifies an object-oriented application using C++ that integrates with a NoSQL database for managing a car rental system. It demonstrates key concepts such as inheritance, polymorphism, database management, and system design principles.
