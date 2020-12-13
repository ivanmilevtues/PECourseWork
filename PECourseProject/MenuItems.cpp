#include "MenuItem.h"
#include "Car.h"
#include "Route.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>

class AddCarMenuItem : public MenuItem {
public:
	AddCarMenuItem(bool isActive) : MenuItem("Add new car", 1, isActive) {
	}

	void handle(TaxiState state) {
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

		state.getCars().push_back(Car(brand, model, years, numberOfSeats, maximumLoadInKg, lph));
		std::cout << "A new car was added.";	
	}
};


class AddRouteMenuItem : public MenuItem {
public:
	AddRouteMenuItem(bool isActive) : MenuItem("Add new route", 2, 3)
	{}

	void handle(TaxiState state) {
		Route route = Route();
		state.getRoutes().push_back(route);

		system("cls");
		std::cout << "New route added" << std::endl;
		do {
			int x, y;
			std::cout << "Input route's point x and y axis" << std::endl;
			std::cin >> x >> y;
			route.addPoint(Point(x, y));
			std::cout << "Point created!" << std::endl;
			std::cout << "Press q to quit. To continue press any other key." << std::endl;
		} while (_getch() != 'q');
	}
};