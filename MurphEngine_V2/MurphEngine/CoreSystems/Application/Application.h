#pragma once
#include "Application.h"
class MurphEngine;

class Application
{
protected:
    MurphEngine* m_pEngine;

public:
    Application();
    virtual ~Application();
    virtual bool Update([[maybe_unused]]double deltaTime);
};


