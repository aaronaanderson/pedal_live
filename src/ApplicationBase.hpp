#ifndef ApplicationBase_hpp
#define ApplicationBase_hpp

/*
  This is a base class to handle/hide interactions with 
  external libraries.
  

  This class should hide run-time recompile complexities
*/


struct ApplicationData;
class ApplicationBase{
    public:
    ApplicationBase();
    ~ApplicationBase();

    virtual void update();
    virtual bool advanceFrame();
    private:
    
    ApplicationData* appData;
};
#endif