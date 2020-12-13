// PECourseProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
    �������� ����������, ����� �� �������� ���������� �� ��������� �������.
    ������� �� ������ �� �����, �����, ������, ����� ������ �, � ����� ��������������� �
    ����� ������ �� ������ ����. ���� ���� �������� ������� �������� � �����.
    �� �������� ������ �� �� ���� ��������� �� �����  � ����� ��������� � ����� � ����� ����
    �� ��� �� �������.

    ������������ �� ��� ���������� �� ��������� �� ���������� ���� �������� ��������� ������� � ��������(10 �����).
    �� ��� ���������� �� ����� �� ��������� ������� �� ����� �� �� ������ ������� � �� ������� ���������� ����� ������ �� �� ������ �� ���������� �� �������� �������� (10 �����).
    ��������� (���-����� 3 ����� ��� ������������) ������ �� ��������� �������� �������. ��������� �� private ��������� �� ������������ �� ����������� �� ���������� �������. ������ �� ��� ���-����� ��� ������������, public getters/setters �� private ��������� �� ������������ (30 �����).
    ���������� � �� ���������� �������� �� �������� ����� (10 �����).
    �� �� ����������� ���������� <<, ����� �� �� �������� �� ��������� �� ������� (10 �����). ������� �� �� ����� � ���������� ��� ���� (20 �����).
    ��������� �� �� ������ � UML ���� �������� (10 �����).
     ������������ ������� �� �� �������� ���������, ���� ����.
*/

#include <iostream>
#include <conio.h>
#include "MenuItem.h"
#include "MenuItems.cpp"

int menu(TaxiState state) {
    std::vector<MenuItem *> items;
    items.push_back(new AddCarMenuItem(true));
    items.push_back(new AddRouteMenuItem(false));
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

int main()
{
    TaxiState state;
    menu(state);
    return 0;
}
