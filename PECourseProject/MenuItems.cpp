#include "MenuItem.h"
#include "Car.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>

class AddCarMenuItem : public MenuItem {
public:
	AddCarMenuItem(bool isActive) : MenuItem("Add new car", 1, isActive) {
	}

	void handle(vector<Car> cars) {
		std::string brand, model;
		unsigned int years, maximumLoadInKg;
		unsigned short numberOfSeats;
		float lph;

		system("cls");
		std::cout << "Create new car" << std::endl;

		std::cout << "Enter brand name:";
		std::cin >> brand;

		std::cout << std::endl << "Enter model name:";
		std::cin >> model;

		std::cout << std::endl << "Enter how old the car is:";
		std::cin >> years;

		std::cout << std::endl << "Enter the number of seats:";
		std::cin >> numberOfSeats;

		std::cout << std::endl << "Enter the maximum load in kg:";
		std::cin >> maximumLoadInKg;

		std::cout << std::endl << "Enter the lph rate for the car:";
		std::cin >> lph;

		cars.push_back(Car(brand, model, years, numberOfSeats, maximumLoadInKg, lph));
		cout << "A new car was added.";
	
		getch();
	}
};