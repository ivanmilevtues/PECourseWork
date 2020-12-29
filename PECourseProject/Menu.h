#pragma once
#include "MenuItem.h"
#include <vector>

class Menu
{
	std::vector<MenuItem*> items;
	Menu* upperLevelMenu;
	TaxiState& state;

public:
	Menu(std::vector<MenuItem*>& items, TaxiState& state): items(items), upperLevelMenu(NULL), state(state) {
	}

	Menu(std::vector<MenuItem*>& items, TaxiState& state, Menu * upperLevelMenu) : items(items), upperLevelMenu(upperLevelMenu), state(state) {
	}

	void show();
};

