#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Car.h"
#include "TaxiState.h"

class MenuItem
{
public:
	enum class operationStatus
	{
		ExitMenu = 0, Continue = 1
	};

	MenuItem(std::string message, int id, bool isActive);

	void setActive(bool active);

	virtual operationStatus handle(TaxiState& parameter) = 0;

	friend std::ostream& operator<<(std::ostream& os, const MenuItem& dt);

private:
	int id;
	std::string message;
	bool isActive;
};