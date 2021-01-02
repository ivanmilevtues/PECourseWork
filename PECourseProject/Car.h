#pragma once
#include <iostream>
#include <string>
#include "Route.h"

class Car
{
public:
	Car(); // use only for populating data with istream
	Car(std::string brand, std::string model, unsigned int years, unsigned short numberOfSeats, unsigned int maximumLoadInKg, float lph);

	void setBrand(std::string brand);
	void setModel(std::string model);
	void setYears(unsigned int years);
	void setNumberOfSeats(unsigned int numberOfSeats);
	void setMaximumLoadInKg(unsigned int maximumLoadInKg);
	std::string getBrand();
	std::string getModel();
	unsigned int getYears();
	unsigned short getNumberOfSeats();
	unsigned int getMaximumLoadInKg();
	float getLph();
	float calculateNeededPetrol();
	void setRoute(Route route);
	friend std::ostream& operator<<(std::ostream& os, const Car& car);
	friend std::ofstream& operator<<(std::ofstream& os, const Car& car);

	friend std::istream& operator>>(std::istream& is, Car& car);

private:
	std::string brand;
	std::string model;
	unsigned int years;
	unsigned short numberOfSeats;
	unsigned int maximumLoadInKg;
	float lph;
	Route route;
};
