#pragma once

#include <iostream>

using DelegateType = void(*)(int x, int y);

void ArtilleryAction(int x, int y)
{
    std::cout << "Drop a bomb on the (" << x << ", " << y << ") position." << std::endl;
}

class Scout
{
public:
    Scout(DelegateType delegate) : mDelegate(delegate) {}

    void FindInformation()
    {
        (*mDelegate)(rand(), rand());
    }

private:
    DelegateType mDelegate;
};
