#include "MenuItem.h"
#include <conio.h>

MenuItem::MenuItem(std::string message, int id, bool isActive)
{
	this->message = message;
	this->id = id;
	this->isActive = isActive;
}

void MenuItem::setActive(bool isActive)
{
	this->isActive = isActive;
}

void MenuItem::createMenu(std::vector<MenuItem*>& items, TaxiState state)
{
    int selected = 0;
    while (true)
    {
        system("cls");
        for (std::vector<MenuItem*>::iterator it = items.begin(); it < items.end(); it++) {
            std::cout << *(*it) << std::endl;
        }

        char click = _getch();
        switch (click) {
        case 'w':
            if (selected < 1) {
                items.at(0)->setActive(false);
                selected = items.size();
            }
            else {
                items.at(selected)->setActive(false);
            }
            selected--;
            items.at(selected)->setActive(true);
            break;
        case 's':
            if (selected >= items.size() - 1) {
                items.at(items.size() - 1)->setActive(false);
                selected = -1;
            }
            else {
                items.at(selected)->setActive(false);
            }
            selected++;
            items.at(selected)->setActive(true);
            break;
        case '\r':
        case '\n':
            items.at(selected)->handle(state);
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const MenuItem& item)
{
	if (item.isActive)
	{
		os << "> " << item.id << ". " << item.message;
	}
	else
	{
		os << "  " << item.id << ". " << item.message;
	}
	return os;
}