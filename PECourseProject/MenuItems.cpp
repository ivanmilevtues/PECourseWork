#include "MenuItem.h"
#include "Car.h"
#include "Route.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <vector>

class CreateCar : public MenuItem {
public:
	CreateCar(bool isActive) : MenuItem("Add new car", 1, isActive) {
	}

	void handle(TaxiState& state) {
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

		state.getCars()->push_back(Car(brand, model, years, numberOfSeats, maximumLoadInKg, lph));
		std::cout << "A new car was added.";	
	}
};


class CreateRoute : public MenuItem {
public:
	CreateRoute(bool isActive) : MenuItem("Add new route", 2, isActive)
	{}

	void handle(TaxiState& state) {
		std::string routeName;

		system("cls");
		std::cout << "Pick name for the route" << std::endl;
		std::cin >> routeName;
		Route route = Route(routeName);
		state.getRoutes()->push_back(route);
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

class ExitMenuItem : public MenuItem {
public:
	ExitMenuItem() : MenuItem("Exit", 4, false) 
	{}

	void handle(TaxiState& state) {
		exit(0);
	}
};


class PickRouteForTaxi : public MenuItem {
	Car car;
	Route route;
public:
	PickRouteForTaxi(Car& car, Route& route, int index, std::string message, bool isActive) : MenuItem(message, index, isActive), car(car), route(route) {
	}

	void handle(TaxiState& state) {
		system("cls");
		car.setRoute(route);
		std::cout << "Press any key to continue" << std::endl;
		_getch();
	}
};

class ListRoutesForTaxi : public MenuItem {
	Car car;
public:
	ListRoutesForTaxi(Car& car, int index, std::string message, bool isActive) : MenuItem(message, index, isActive), car(car) {
	}

	void handle(TaxiState& state) {
		system("cls");
		int id = 1;
		std::vector<MenuItem*> pickRoute;
		for (std::vector<Route>::iterator it = state.getRoutes()->begin(); it != state.getRoutes()->end(); it++, id++) {
			pickRoute.push_back(new PickRouteForTaxi(car, (*it), id, (*it).getName(), id == 1));
		}
		MenuItem::createMenu(pickRoute, state);
	}
};

class ListTaxis : public MenuItem {
public:
	ListTaxis() : MenuItem("Add route to taxi", 3, false)
	{}

	void handle(TaxiState& state) {
		system("cls");
		std::vector<MenuItem *> pickTaxi;
		int index = 1;
		for (std::vector<Car>::iterator it = state.getCars()->begin(); it != state.getCars()->end(); it++, index++) {
			pickTaxi.push_back(new ListRoutesForTaxi(*it, index, (*it).getBrand() + (*it).getModel(), index == 1));
		}

		MenuItem::createMenu(pickTaxi, state);
	}
};
