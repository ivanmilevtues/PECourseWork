#include "Menu.h"
#include <conio.h>

void Menu::show() {
    int selected = 0;
    MenuItem::operationStatus handleResult = MenuItem::operationStatus::Continue;
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
            handleResult = items.at(selected)->handle(state);
            break;
        }
        if (handleResult == MenuItem::operationStatus::ExitMenu) {
            break;
        }
    }
}