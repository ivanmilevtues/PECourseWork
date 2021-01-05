#include "MenuItem.h"
#include "Car.h"
#include "Route.h"
#include "Menu.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>

class CreateCar : public MenuItem {
public:
	CreateCar(bool isActive) : MenuItem("Add new car", 1, isActive) {
	}

	OperationStatus handle(TaxiState& state) {
		std::string brand, model;
		unsigned int years, maximumLoadInKg;
		unsigned short numberOfSeats;
		float lph;

		system("cls");
		std::cout << "Create new car" << std::endl;

		std::cout << "Enter brand name:";
		getline(std::cin, brand);

		std::cout << std::endl << "Enter model name:";
		getline(std::cin, model);

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
		return OperationStatus::Continue;
	}
};


class CreateRoute : public MenuItem {
public:
	CreateRoute(int id) : MenuItem("Add new route", id, false)
	{}

	OperationStatus handle(TaxiState& state) {
		std::string routeName;
		int dailyDrives;

		system("cls");
		std::cout << "Pick name for the route" << std::endl;
		getline(std::cin, routeName);
		std::cout << "How many times the route will be done in a day" << std::endl;
		std::cin >> dailyDrives;

		Route route = Route(routeName, dailyDrives);
		std::cout << "New route added" << std::endl;
		do {
			int x, y;
			std::cout << "Input route's point x and y axis" << std::endl;
			std::cin >> x >> y;
			route.addPoint(Point(x, y));
			std::cout << "Point created!" << std::endl;
			std::cout << "Press q to quit. To continue press any other key." << std::endl;
		} while (_getch() != 'q');

		state.getRoutes()->push_back(route);
		return OperationStatus::Continue;
	}
};

class ExitMenu : public MenuItem {
public:
	ExitMenu(int id) : MenuItem("Exit", id, false) 
	{}

	OperationStatus handle(TaxiState& state) {
		return OperationStatus::ExitMenu;
	}
};


class PickRouteForTaxi : public MenuItem {
	Car& car;
	Route& route;
public:
	PickRouteForTaxi(Car& car, Route& route, int index, std::string message, bool isActive) : MenuItem(message, index, isActive), car(car), route(route)
	{}

	OperationStatus handle(TaxiState& state) {
		system("cls");
		car.setRoute(route);
		std::cout << "Route " << route.getName() << " selected for taxi: '" << car.getModel() << "'" << std::endl;
		std::cout << "For this route "<< car.calculateNeededPetrol() << " liters will be needed.";
		std::cout << "Press any key to continue" << std::endl;
		_getch();
		return OperationStatus::ExitMenu;
	}
};

class ListRoutesForTaxi : public MenuItem {
	Car& car;
public:
	ListRoutesForTaxi(Car& car, int index, std::string message, bool isActive) : MenuItem(message, index, isActive), car(car)
	{}

	OperationStatus handle(TaxiState& state) {
		system("cls");
		int id = 1;
		std::vector<MenuItem*> pickRoute;
		for (int id = 0; id < state.getRoutes()->size(); id++) {
			Route& route = state.getRoutes()->at(id);
			MenuItem* item = new PickRouteForTaxi(car, route, id + 1, route.getName(), id == 0);
			pickRoute.push_back(item);
			delete item;
		}
		Menu(pickRoute, state).show();
		return OperationStatus::ExitMenu;
	}
};

class ListTaxis : public MenuItem {
public:
	ListTaxis(int id) : MenuItem("Add route to taxi", id, false) {}

	OperationStatus handle(TaxiState& state) {
		system("cls");
		std::vector<MenuItem*> pickTaxi;
		for (int index = 0; index < state.getCars()->size(); index++) {
			Car& car = state.getCars()->at(index);
			MenuItem * menuItem = new ListRoutesForTaxi(car, index + 1,
				car.getBrand() + car.getModel(), index == 0); // the first element should be active
			pickTaxi.push_back(menuItem); 
			delete menuItem;
		}
		Menu(pickTaxi, state).show();
		return OperationStatus::Continue;
	}
};

class SaveToFile : public MenuItem {
public:
	SaveToFile(int id) : MenuItem("Save current configuration to file", id, false) {}

	OperationStatus handle(TaxiState& state) {
		system("cls");
		std::string fileName;
		std::ofstream file;
		std::cout << "Enter filename to save the configuration in" << std::endl;
		std::cin >> fileName;
		file.open(fileName);
		for (std::vector<Car>::iterator it = state.getCars()->begin(); it != state.getCars()->end(); it++) {
			file << *it;
		}

		for (std::vector<Route>::iterator it = state.getRoutes()->begin(); it != state.getRoutes()->end(); it++) {
			file << *it;
		}

		return OperationStatus::Continue;
	}
};

class LoadFromFile : public MenuItem {
public:
	LoadFromFile(int id) : MenuItem("Load configuration from file", id, false) {}

	OperationStatus handle(TaxiState& state) {
		system("cls");
		enum class ReadState
		{
			Car = 0,
			Route = 1,
			Point = 2
		};
		ReadState readState = ReadState::Car; // This should be always the first state in the file
		std::string fileName, line;
		std::ifstream file;
		std::cout << "Enter filename to load configuration from" << std::endl;
		std::cin >> fileName;
		file.open(fileName);
		Car* car = NULL;
		Route* route = NULL;
		Point* point = NULL;
		while (std::getline(file, line)) {
			if (!line.compare("Car:")) {
				readState = ReadState::Car;
				car = new Car();
				continue;
			}
			else if (!line.compare("Route:")) {
				readState = ReadState::Route;
				route = new Route();
				continue;
			}
			std::istringstream iss(line);
			switch (readState) {
			case ReadState::Car:
				iss >> *car;
				state.getCars()->push_back(*car);
				delete car;
				break;
			case ReadState::Route:
				iss >> *route;
				state.getRoutes()->push_back(*route);
				readState = ReadState::Point;
				delete route;
				break;
			case ReadState::Point:
				point = new Point();
				iss >> *point;
				state.getRoutes()->back().addPoint(*point);
				delete point;
				break;
			}
		}
		return OperationStatus::Continue;
	}
};