#pragma once
#include <vector>
#include "Car.h"
#include "Route.h"

class TaxiState
{
public:
	TaxiState();

	std::vector<Car> getCars();

	std::vector<Route> getRoutes();

private:
	std::vector<Car> cars;
	std::vector<Route> routes;
};

