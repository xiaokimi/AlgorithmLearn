#pragma once

template<typename T>
T add(T a, T b)
{
    return a + b;
}

template<int N>
struct factorial {
    constexpr static int value = N * factorial<N - 1>::value;
};

template<>
struct factorial<0> {
    constexpr static int value = 1;
};