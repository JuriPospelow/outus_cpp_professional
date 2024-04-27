#pragma once
#include <memory>
#include <vector>
#include <string>
#include "modulShape.hpp"
#include "modulFile.hpp"
#include "view.hpp"


//controller
Button bCreateCircle; // view
Circle shapeCircle = Circle(&bCreateCircle); // modul

Button bRemove; // view
// IObserver* shapeRemove = new Remove(&bRemove); // modul

Button bExport2JPEG; // view
JPEG fileJPEG = JPEG(&bExport2JPEG); // modul

Button bImport; // view
// IObserver* fileDoc = new Document(&bImport); // modul

Button bNewCanvas; // view
// IObserver* canvas = new Canvas(&bNewCanvas); // modul