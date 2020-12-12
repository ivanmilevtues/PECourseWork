#include <iostream>
#include <string>


using namespace std;

class MenuItem
{
public:
	MenuItem(string message, int id, bool isActive);

	template <typename T>
	void handle(T parameter);

	void setActive(bool active);

	friend ostream& operator<<(ostream& os, const MenuItem& dt);

private:
	int id;
	string message;
	bool isActive;
};
