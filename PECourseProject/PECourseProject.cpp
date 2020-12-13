// PECourseProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
    Създайте приложение, което да поддържа информация за маршрутни таксита.
    Данните за колите са марка, модел, години, колко местна е, с каква товароподемност и
    колко разход на гориво иска. Тези коли покриват някакви маршрути в града.
    За маршрута трябва да се знае възловите му точки  и колко километра е дълъг и колко пъти
    на ден се обикаля.

    Приложението да има възможност за въвеждане на произволен брой различни маршрутни таксита и маршрути(10 точки).
    Да има възможност за избор на маршрутни таксита на което да се задава маршрут и да извежда информация колко гориво да се зареди за извършване не дневната обиколка (10 точки).
    Класовете (най-малко 3 класа при реализацията) трябва да капсулира всичките детайли. Използват се private инстанции на променливите за съхраняване на различните детайли. Трябва да има най-малко два конструктора, public getters/setters за private инстанции на променливите (30 точки).
    Необходимо е да извършвате проверка на входните данни (10 точки).
    Да се предефинира операцията <<, която да се използва за извеждане на данните (10 точки). Данните да се четат и съхраняват във файл (20 точки).
    Класовете да се опишат с UML клас диаграма (10 точки).
     Задължително данните да се въвеждат динамично, чрез меню.
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
