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

template<typename T>
inline void MenuItem::handle(T parameter)
{
	throw "Unimplmented method";
}

ostream& operator<<(ostream& os, const MenuItem& item)
{
	os << item.isActive ? "> " : "  ";
	os << item.id << ". " << item.message;
	return os;
}
