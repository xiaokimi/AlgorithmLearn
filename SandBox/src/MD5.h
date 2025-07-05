#pragma once

#include <string>

constexpr int BLOCK_SIZE = 64;

constexpr int S11 = 7;
constexpr int S12 = 12;
constexpr int S13 = 17;
constexpr int S14 = 22;
constexpr int S21 = 5;
constexpr int S22 = 9;
constexpr int S23 = 14;
constexpr int S24 = 20;
constexpr int S31 = 4;
constexpr int S32 = 11;
constexpr int S33 = 16;
constexpr int S34 = 23;
constexpr int S41 = 6;
constexpr int S42 = 10;
constexpr int S43 = 15;
constexpr int S44 = 21;

class MD5
{
public:
    MD5() = default;

    void Update(const uint8_t* buffer, size_t len);
    void FinalHash();
    void Reset();

    std::string ToString() const;
private:
    void Transform(const uint8_t* block);
    void Decode(uint32_t* output, const uint8_t* input, size_t len);
    void Encode(uint8_t* output, const uint32_t* input, size_t len);

private:
    uint32_t F(uint32_t x, uint32_t y, uint32_t z)
    {
        return (x & y) | ((~x) & z);
    }

    uint32_t G(uint32_t x, uint32_t y, uint32_t z)
    {
        return (x & z) | (y & (~z));
    }

    uint32_t H(uint32_t x, uint32_t y, uint32_t z)
    {
        return x ^ y ^ z;
    }

    uint32_t I(uint32_t x, uint32_t y, uint32_t z)
    {
        return y ^ (x | (~z));
    }

    void FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
    {
        a = LeftRotate(a + F(b, c, d) + x + ac, s) + b;
    }

    void GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
    {
        a = LeftRotate(a + G(b, c, d) + x + ac, s) + b;
    }

    void HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
    {
        a = LeftRotate(a + H(b, c, d) + x + ac, s) + b;
    }

    void II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
    {
        a = LeftRotate(a + I(b, c, d) + x + ac, s) + b;
    }

    uint32_t LeftRotate(uint32_t x, int n)
    {
        return (x << n) | (x >> (32 - n));
    }

private:
    uint32_t mState[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
    uint8_t mBuffer[BLOCK_SIZE] = { 0 };
    uint64_t mBitsCount = 0;

    bool bFinished = false;
    uint8_t mDigest[16] = { 0 };
};