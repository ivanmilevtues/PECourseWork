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
		std::string brand, model, errorMessage;
		unsigned int years, maximumLoadInKg;
		unsigned short numberOfSeats;
		float lph;

		system("cls");
		std::cout << "Create new car" << std::endl;

		do {
			std::cout << errorMessage << "Enter brand name:";
			getline(std::cin, brand);
			errorMessage = "Brand name cannot be empty! ";
		} while (brand.size() == 0);
		errorMessage = "";

		do {
			std::cout << std::endl << errorMessage << "Enter model name:";
			getline(std::cin, model);
			errorMessage = "Model name cannot be empty! ";
		} while (model.size() == 0);
		errorMessage = "";

		do {
			std::cout << std::endl << errorMessage << "Enter how old the car is:";
			std::cin >> years;
			errorMessage = "Car age cannot be bigger than 100 and less than 0! ";
		} while (years > 100 || years < 0);
		errorMessage = "";

		do {
			std::cout << std::endl << errorMessage << "Enter the number of seats:";
			std::cin >> numberOfSeats;
			errorMessage = "The number of seats cannot be less than 2 and bigger than 100! ";
		} while (numberOfSeats < 2 || numberOfSeats > 100);
		errorMessage = "";

		do {
			std::cout << std::endl << errorMessage << "Enter the maximum load in kg:";
			std::cin >> maximumLoadInKg;
			errorMessage = "The maximum load cannot be less or equal than 0! ";
		} while (maximumLoadInKg <= 0);
		errorMessage = "";

		do {
			std::cout << std::endl << "Enter the lph rate for the car:";
			std::cin >> lph;
			errorMessage = "The lph cannot be less than or equal to 0 !";
		} while (lph <= 0);

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
		std::string routeName, errorMessage;
		int dailyDrives;

		system("cls");
		do {
			std::cout << errorMessage << "Pick name for the route:" << std::endl;
			getline(std::cin, routeName);
			errorMessage = "The route name cannot be empty! ";
		} while (routeName.size() == 0);
		errorMessage = "";

		do {
			std::cout << errorMessage << "How many times the route will be done in a day" << std::endl;
			std::cin >> dailyDrives;
			errorMessage = "The number of daily drives cannot be less than or equal to 0! ";
		} while (dailyDrives <= 0);

		Route route = Route(routeName, dailyDrives);
		std::cout << "New route added" << std::endl;
		do {
			double lat, lng;
			std::cout << "Input route's point latitude and longtitude" << std::endl;
			std::cin >> lat >> lng;
			route.addPoint(Point(lat, lng));
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