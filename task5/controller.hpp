#pragma once
#include <memory>
#include <vector>
#include <string>
#include "modulShape.hpp"
#include "modulFile.hpp"
#include "view.hpp"


//controller
Button* bCreateCircle = new Button(); // view
IObserver* shapeCircle = new Circle(bCreateCircle); // modul

Button* bCreateTriangle = new Button(); // view
IObserver* shapeTriangle = new Triangle(bCreateTriangle); // modul

Button* bExport2JPEG = new Button(); // view
IObserver* fileJPEG = new JPEG(bExport2JPEG); // modul