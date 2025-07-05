#pragma once

#include "Reflect.h"

class GameObject
{
    REFLECTION_BODY(GameObject)

public:
    virtual ~GameObject() = default;

    virtual void Update()
    {
        std::cout << "GameObject " << mName << " updated.\n";
    }

private:
    int mId;
    std::string mName;
};

REGISTER_TYPE_NAME(GameObject, "GameObject")

BEGIN_REGISTER_CLASS(GameObject, void)
    REGISTER_PROPERTY(GameObject, mId)
    REGISTER_METHOD(GameObject, GameObject::Update)
END_REGISTER_CLASS(GameObject)

template<typename T>
T* CreateObject()
{
    ClassInfo* info = TypeRegistry::Get().FindClass(TypeNameMapper::GetName<T>());
    if (!info)
    {
        std::cerr << "Error";
        return nullptr;
    }
    return static_cast<T*>(info->Create());
}

void* CreateObjectByName(const std::string& name)
{
    ClassInfo* info = TypeRegistry::Get().FindClass(name);
    if (!info)
    {
        return nullptr;
    }
    return info->Create();
}