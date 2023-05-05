#include <Application.hpp>

int main (int argc, char** argv) 
{
    RB::Logger::Enable(512);
    std::unique_ptr<Application> app;
    
    app.reset(CreateApplication());
    app->Run();

    RB::Logger::Disable();    
    return 0;
}