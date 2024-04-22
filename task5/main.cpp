#include <string>

#include "controller.hpp"

struct MenuBarShape {
    Button* bCreateCircle;
    Button* bRemove;
    // ... another shape buttons
};

struct MenuBarFile {
    Button* bExport2JPEG;
    Button* bImport;
    Button* bNewDocument;
    // .. . another file buttons
};

struct Menu {
    MenuBarShape* menuShape = new MenuBarShape();
    MenuBarFile* menuFile = new MenuBarFile();
};

int main()
{

    Menu menu;
    menu.menuShape->bCreateCircle->click(); // in main
    menu.menuShape->bRemove->click(); // in main
    menu.menuFile->bExport2JPEG->click();
    menu.menuFile->bImport->click();
    menu.menuFile->bNewDocument->click();

    return 0;
}
