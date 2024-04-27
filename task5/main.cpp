#include <string>

#include "controller.hpp"

struct _MenuBarShape {
    Button* _bCreateCircle = &bCreateCircle;
    Button* _bRemove = &bRemove;
    // ... another shape buttons
} MenuBarShape;

struct _MenuBarFile {
    Button* _bExport2JPEG = &bExport2JPEG;
    Button* _bImport = &bImport;
    Button* _bNewDocument = &bNewCanvas;
    // .. . another file buttons
} MenuBarFile;

struct Menu {
    _MenuBarShape* menuShape =  &MenuBarShape;
    _MenuBarFile* menuFile = &MenuBarFile;
};

int main()
{

    Menu menu;
    menu.menuShape->_bCreateCircle->click();
    menu.menuShape->_bRemove->click();
    menu.menuFile->_bExport2JPEG->click();
    menu.menuFile->_bImport->click();
    menu.menuFile->_bNewDocument->click();

    return 0;
}
