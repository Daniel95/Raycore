#pragma once

#include "Core/Application.h"

class Game : public Engine::Application
{
public:
    Game();
    ~Game();

	virtual void OnStart() override;
private:

protected:

};
