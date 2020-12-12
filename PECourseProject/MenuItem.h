#include <iostream>
#include <string>


using namespace std;

class MyClass
{
public:
	MyClass(string message);

	virtual void handle() = 0;

private:
	string message;
};