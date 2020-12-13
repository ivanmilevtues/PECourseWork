#include "MenuItem.h"

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
