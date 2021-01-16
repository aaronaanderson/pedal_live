#include <iostream>
#include "ApplicationBase.hpp"

int main(){
    ApplicationBase app;
    while(app.advanceFrame()){
        app.update();
    }
}//app should call its deconstructor after this line and clean itself up