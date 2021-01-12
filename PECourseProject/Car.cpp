#include "Car.h"
#include <fstream>


// This should be used only for istream population of the object.
Car::Car()
{
}

Car::Car(std::string brand, std::string model, unsigned int years, unsigned short numberOfSeats, unsigned int maximumLoadInKg, float lph)
{
	this->brand = brand;
	this->model = model;
	this->years = years;
	this->numberOfSeats = numberOfSeats;
	this->maximumLoadInKg = maximumLoadInKg;
	this->lph = lph;
}

void Car::setBrand(std::string brand)
{
	this->brand = brand;
}

void Car::setModel(std::string model)
{
	this->model = model;
}

void Car::setYears(unsigned int years)
{
	this->years = years;
}

void Car::setNumberOfSeats(unsigned int numberOfSeats)
{
	this->numberOfSeats = numberOfSeats;
}

void Car::setMaximumLoadInKg(unsigned int maximumLoadInKg)
{
	this->maximumLoadInKg = maximumLoadInKg;
}

std::string Car::getBrand()
{
	return this->brand;
}

std::string Car::getModel()
{
	return this->model;
}

unsigned int Car::getYears()
{
	return this->years;
}

unsigned short Car::getNumberOfSeats()
{
	return this->numberOfSeats;
}

unsigned int Car::getMaximumLoadInKg()
{
	return this->maximumLoadInKg;
}

float Car::getLph()
{
	return this->lph;
}

float Car::calculateNeededPetrol()
{
	float routeLength = route.getLength() * route.getNumberOfDailyDrives();
	return routeLength * lph / 100;
}

void Car::setRoute(Route route)
{
	this->route = route;
}

Route * Car::getRoute()
{
	if (this->route.getName().length() != 0) {
		return &this->route;
	}
	return NULL;
}

std::ostream& operator<<(std::ostream& os, const Car& car)
{
	os << car.brand << " " << car.model << " " << car.years << " "
		<< car.numberOfSeats << " " << car.maximumLoadInKg << " " << car.lph << std::endl
		<< car.route << std::endl;
	return os;
}

std::ofstream& operator<<(std::ofstream& os, const Car& car)
{
	os << "Car:" << std::endl << car.brand << " " << car.model << " " << car.years << " "
		<< car.numberOfSeats << " " << car.maximumLoadInKg << " " << car.lph << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Car& car)
{
	is >> car.brand >> car.model >> car.years >> car.numberOfSeats >> car.maximumLoadInKg >> car.lph;
	return is;
}
