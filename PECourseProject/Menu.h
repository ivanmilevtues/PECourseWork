#pragma once
#include "MenuItem.h"
#include <vector>

class Menu
{
	std::vector<MenuItem*> items;
	TaxiState& state;

public:
	Menu(std::vector<MenuItem*>& items, TaxiState& state): items(items), state(state) {
	}

	void show();
};

