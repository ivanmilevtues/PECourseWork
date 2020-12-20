#include "TaxiState.h"

TaxiState::TaxiState()
{
}

std::vector<Car>* TaxiState::getCars()
{
	return &this->cars;
}

std::vector<Route>* TaxiState::getRoutes()
{
	return &this->routes;
}
