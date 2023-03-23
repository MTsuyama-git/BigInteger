#pragma once
#include <cstdint>
#include <string>
#include <iostream>

#define CHUNK_TYPE uint8_t
#define CHUNK_SIZE sizeof(CHUNK_TYPE)
#define CHUNK_BITS (CHUNK_SIZE * 8)
#define CHUNK_MAX  ((1 << CHUNK_BITS)-1)

typedef enum
{
    Endian_Little,
    Endian_Big,
}Endian;

class AtomicOutput
{
private:
public:
    CHUNK_TYPE carry;
    CHUNK_TYPE output;
private:
public:
    AtomicOutput(const CHUNK_TYPE&, const CHUNK_TYPE&);
};

class BigInteger
{
private:
CHUNK_TYPE* __body = nullptr;
size_t __body_length = 0;
static const char __c_table[16];
Endian __endian;

public:
private:
static AtomicOutput& carry_l_chunk(const int&, const CHUNK_TYPE&);
public:
BigInteger(Endian endian = Endian::Endian_Little);
BigInteger(uint8_t, Endian endian = Endian::Endian_Little);
BigInteger(int, Endian endian = Endian::Endian_Little);
static std::string encode(const uint8_t &);
static uint8_t decode(const uint8_t &);
operator std::string() const;
friend std::ostream& operator<<(std::ostream& out, const BigInteger&);
friend BigInteger& operator<<(BigInteger&, const int&);
};