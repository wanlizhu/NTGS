#pragma once

#include <NTGS/Core/Config.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include <assert.h>
#include <iostream>
#include <atomic>
#include <typeinfo>


namespace NTGS {

#define ENUM_BASE(E) reinterpret_cast<std::underlying_type<ENUMTYPE>::type&>(E) 
#define ENUM_CAST(V) reinterpret_cast<ENUMTYPE&>(V)
#define ENUM_CAST2(V) static_cast<ENUMTYPE>(V)
#define DEFINE_ENUM_OPERATORS(ENUMTYPE) \
extern "C++" {\
    inline ENUMTYPE& operator|=(ENUMTYPE& a, ENUMTYPE b) noexcept { return ENUM_CAST(ENUM_BASE(a) |= ENUM_BASE(b)); } \
    inline ENUMTYPE& operator&=(ENUMTYPE& a, ENUMTYPE b) noexcept { return ENUM_CAST(ENUM_BASE(a) &= ENUM_BASE(b)); } \
    inline ENUMTYPE& operator^=(ENUMTYPE& a, ENUMTYPE b) noexcept { return ENUM_CAST(ENUM_BASE(a) ^= ENUM_BASE(b)); } \
    inline constexpr ENUMTYPE operator|(ENUMTYPE  a, ENUMTYPE b) noexcept { ENUM_CAST2(ENUM_BASE(a) |  ENUM_BASE(b)); } \
    inline constexpr ENUMTYPE operator&(ENUMTYPE  a, ENUMTYPE b) noexcept { ENUM_CAST2(ENUM_BASE(a) &  ENUM_BASE(b)); } \
    inline constexpr ENUMTYPE operator^(ENUMTYPE  a, ENUMTYPE b) noexcept { ENUM_CAST2(ENUM_BASE(a) ^  ENUM_BASE(b)); } \
    inline constexpr ENUMTYPE operator~(ENUMTYPE  a) noexcept { ENUM_CAST2(~ENUM_BASE(a)); } \
}

    class NonCopyable {
    protected:
        constexpr NonCopyable() = default;
        ~NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    template<typename T>
    class Singleton : NonCopyable {
    public:
        static T* GetInstance() {
            std::call_once(Once, [&](){ GlobalInstance.reset(new T()); });
            return GlobalInstance.get();
        }

    private:
        static std::unique_ptr<T> GlobalInstance;
        static std::once_flag Once;
    };

    template<typename T>
    std::unique_ptr<T> Singleton<T>::GlobalInstance;

    template<typename T>
    class IDGenerator {
    public:
        static inline SIZE GetID() const { return GlobalCounter++; }

    private:
        static std::atomic<SIZE> GlobalCounter;
    };

    template<typename T>
    std::atomic<SIZE> IDGenerator<T>::GlobalCounter = 0;
}