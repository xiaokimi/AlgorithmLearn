#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

class TypeInfo;
class PropertyInfo;
class MethodInfo;
class ClassInfo;

class TypeInfo
{
public:
    virtual ~TypeInfo() = default;
    virtual const std::string& GetName() const = 0;
    virtual size_t GetSize() const = 0;
};

template<typename T>
class PrimitiveTypeInfo : public TypeInfo
{
public:
    PrimitiveTypeInfo(const std::string& name) : mTypeName(name) {}

    const std::string& GetName() const override
    {
        return mTypeName;
    }

    size_t GetSize() const override
    {
        return sizeof(T);
    }

private:
    std::string mTypeName;
};

class ClassInfo : public TypeInfo
{
public:
    ClassInfo(const std::string& name, size_t size, ClassInfo* super = nullptr)
        : mClassName(name), mClassSize(size), mSuperClass(super) { }

    const std::string& GetName() const override
    {
        return mClassName;
    }

    size_t GetSize() const override
    {
        return mClassSize;
    }

    void AddProperty(const std::string& name, PropertyInfo* property)
    {
        mProperties[name] = property;
    }

    void AddMethod(const std::string& name, MethodInfo* method)
    {
        mMethods[name] = method;
    }

    void SetCreateFunction(std::function<void* ()> creator)
    {
        mCreateInstance = creator;
    }

    void* Create() const
    {
        if (mCreateInstance)
        {
            return mCreateInstance();
        }
        return nullptr;
    }

    PropertyInfo* FindProperty(const std::string& name) const
    {
        auto iter = mProperties.find(name);
        if (iter != mProperties.end())
        {
            return iter->second;
        }

        if (mSuperClass)
        {
            return mSuperClass->FindProperty(name);
        }
        return nullptr;
    }

    MethodInfo* FindMethod(const std::string& name) const
    {
        auto iter = mMethods.find(name);
        if (iter != mMethods.end())
        {
            return iter->second;
        }

        if (mSuperClass)
        {
            return mSuperClass->FindMethod(name);
        }
        return nullptr;
    }

private:
    std::string mClassName;
    size_t mClassSize;
    ClassInfo* mSuperClass;
    std::unordered_map<std::string, PropertyInfo*> mProperties;
    std::unordered_map<std::string, MethodInfo*> mMethods;
    std::function<void* ()> mCreateInstance;
};

class PropertyInfo
{
public:
    PropertyInfo(const std::string& name, size_t offset, TypeInfo* typeInfo)
        : mName(name), mOffset(offset), mPropType(typeInfo) { }

    const std::string& GetName() const
    {
        return mName;
    }

    size_t GetOffset() const
    {
        return mOffset;
    }

    TypeInfo* GetTypeInfo() const
    {
        return mPropType;
    }

    template<typename T>
    T GetValue(void* instance) const
    {
        return *reinterpret_cast<T*>(static_cast<char*>(instance) + mOffset);
    }

    template<typename T>
    void SetValue(void* instance, const T& value) const
    {
        *reinterpret_cast<T*>(static_cast<char*>(instance) + mOffset) = value;
    }

private:
    std::string mName;
    size_t mOffset;
    TypeInfo* mPropType;
};

class MethodInfo
{
public:
    using MethodPtr = std::function<void(void*)>;

    MethodInfo(const std::string& name, MethodPtr method)
        : mName(name), mMethodImpl(method) { }

    void Invoke(void* instance) const
    {
        if (mMethodImpl)
        {
            mMethodImpl(instance);
        }
    }

private:
    std::string mName;
    MethodPtr mMethodImpl;
};

class TypeRegistry
{
public:
    static TypeRegistry& Get()
    {
        static TypeRegistry instance;
        return instance;
    }

    ClassInfo* RegisterClass(const std::string& name, size_t size, ClassInfo* super = nullptr)
    {
        if (mClasses.find(name) != mClasses.end())
        {
            return mClasses[name].get();
        }

        auto info = std::make_unique<ClassInfo>(name, size, super);
        auto* ptr = info.get();
        mClasses[name] = std::move(info);
        return ptr;
    }

    ClassInfo* FindClass(const std::string& name) const
    {
        auto iter = mClasses.find(name);
        if (iter != mClasses.end())
        {
            return iter->second.get();
        }
        return nullptr;
    }

    template<typename T>
    TypeInfo* RegisterPrimitive(const std::string& name)
    {
        if (mPrimitives.find(name) != mPrimitives.end())
        {
            return mPrimitives[name].get();
        }

        auto info = std::make_unique<PrimitiveTypeInfo<T>>(name);
        auto* ptr = info.get();
        mPrimitives[name] = std::move(info);
        return ptr;
    }

    TypeInfo* FindType(const std::string& name) const
    {
        if (ClassInfo* info = FindClass(name))
        {
            return info;
        }

        auto iter = mPrimitives.find(name);
        if (iter != mPrimitives.end())
        {
            return iter->second.get();
        }
        return nullptr;
    }

private:
    TypeRegistry()
    {
        RegisterPrimitive<int>("int");
        RegisterPrimitive<float>("float");
        RegisterPrimitive<double>("double");
        RegisterPrimitive<bool>("bool");
        RegisterPrimitive<std::string>("string");
    }

private:
    std::unordered_map<std::string, std::unique_ptr<ClassInfo>> mClasses;
    std::unordered_map<std::string, std::unique_ptr<TypeInfo>> mPrimitives;
};

class TypeNameMapper
{
public:
    template<typename T>
    static const char* GetName()
    {
        if constexpr (std::is_same_v<T, int>) return "int";
        else if constexpr (std::is_same_v<T, float>) return "float";
        else if constexpr (std::is_same_v<T, double>) return "double";
        else if constexpr (std::is_same_v<T, bool>) return "bool";
        else if constexpr (std::is_same_v<T, std::string>) return "string";
        else return "unknown";
    }
};

#define REGISTER_TYPE_NAME(TYPE, NAME) \
    template<> \
    const char* TypeNameMapper::GetName<TYPE>() { return NAME; }

REGISTER_TYPE_NAME(int, "int")
REGISTER_TYPE_NAME(float, "float")
REGISTER_TYPE_NAME(double, "double")
REGISTER_TYPE_NAME(bool, "bool")
REGISTER_TYPE_NAME(std::string, "string")
REGISTER_TYPE_NAME(char, "char")
REGISTER_TYPE_NAME(short, "short")
REGISTER_TYPE_NAME(long, "long")
REGISTER_TYPE_NAME(unsigned int, "uint")
REGISTER_TYPE_NAME(unsigned char, "uchar")

#define REFLECTION_BODY(CLASS)                                                                  \
    friend class CLASS##_ReflectionInfo;                                                        \


#define BEGIN_REGISTER_CLASS(CLASS, SUPER)                                                      \
class CLASS##_ReflectionInfo                                                                    \
{                                                                                               \
public:                                                                                         \
    CLASS##_ReflectionInfo()                                                                    \
    {                                                                                           \
        using ClassType = CLASS;                                                                \
        using SuperType = SUPER;                                                                \
        auto* registry = &TypeRegistry::Get();                                                  \
                                                                                                \
        ClassInfo* superInfo = nullptr;                                                         \
        if (!std::is_same_v<SuperType, void>)                                                   \
        {                                                                                       \
            superInfo = registry->FindClass(#SUPER);                                            \
            if (!superInfo)                                                                     \
            {                                                                                   \
                std::cerr << "SuperClass " << #SUPER <<                                         \
                    " not register for " << #CLASS << "\n";                                     \
            }                                                                                   \
        }                                                                                       \
                                                                                                \
        mClassInfo = registry->RegisterClass(#CLASS, sizeof(ClassType), superInfo);             \
        mClassInfo->SetCreateFunction([]() {                                                    \
            return static_cast<void*>(new ClassType());                                         \
        });                                                                                     \
                                                                                                \
        Init();                                                                                 \
    }                                                                                           \
                                                                                                \
private:                                                                                        \
    void Init();                                                                                \
                                                                                                \
private:                                                                                        \
    ClassInfo* mClassInfo;                                                                      \
};                                                                                              \
                                                                                                \
static CLASS##_ReflectionInfo __CLASS##_ReflectionInfo__;                                       \
                                                                                                \
void CLASS##_ReflectionInfo::Init()                                                             \
{

#define REGISTER_PROPERTY(CLASS, PROPERTY)                                                      \
{                                                                                               \
    using ClassType = CLASS;                                                                    \
    using PropType = decltype(ClassType::PROPERTY);                                             \
                                                                                                \
    const char* typeName = TypeNameMapper::GetName<PropType>();                                 \
    auto* propType = TypeRegistry::Get().FindType(typeName);                                    \
    if (!propType)                                                                              \
    {                                                                                           \
        std::cerr << "Type " << typeName << " not found for property " <<                       \
            #PROPERTY << "\n";                                                                  \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        size_t offset = offsetof(ClassType, PROPERTY);                                          \
        mClassInfo->AddProperty(#PROPERTY, new PropertyInfo(#PROPERTY, offset, propType));      \
    }                                                                                           \
}

#define REGISTER_METHOD(CLASS, METHOD)                                                          \
    mClassInfo->AddMethod(#METHOD, new MethodInfo(#METHOD, [](void* instance) {                 \
        static_cast<CLASS*>(instance)->METHOD();                                                \
    }));

#define END_REGISTER_CLASS(CLASS)                                                               \
}