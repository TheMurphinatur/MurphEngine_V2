
#include "../MurphEngine/Middleware/Bleach_New/BleachNew.h"
#include "GameApplication/GameApplication.h"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    BLEACH_INIT_LEAK_DETECTOR();
    GameApplication application;
    application.InitializeGameScene();
    application.Run();
     
    BLEACH_DUMP_AND_DESTROY_LEAK_DETECTOR();
    return 0;
}