#include <BigInteger.hpp>
#include <stdlib.h>

const char BigInteger::__c_table[16] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f'};

BigInteger::BigInteger(Endian endian) : __endian(endian)
{
}

BigInteger::BigInteger(uint8_t value, Endian endian) : __endian(endian)
{
    __body_length = 1;
    __body = new CHUNK_TYPE[__body_length];
    if (endian == Endian::Endian_Little)
    {
        __body[0] = value << 8 * (CHUNK_SIZE - 1);
    }
    else
    {
        __body[0] = value;
    }
}

BigInteger::BigInteger(int value, Endian endian) : __endian(endian)
{
    __body_length = (sizeof(int) / CHUNK_SIZE) + ((sizeof(int) % CHUNK_SIZE == 0) ? 0 : 1);
    __body = new CHUNK_TYPE[__body_length];

    if (endian == Endian::Endian_Little)
    {
        for (size_t i = 0; i < (sizeof(int) / CHUNK_SIZE); ++i)
        {
            __body[i] = value & CHUNK_MAX;
            value >>= CHUNK_BITS;
        }
        if ((sizeof(int) % CHUNK_SIZE) > 0)
        {
            __body[__body_length - 1] = value & CHUNK_MAX;
        }
    }
    else
    {
        for (size_t i = 0; i < (sizeof(int) / CHUNK_SIZE); ++i)
        {
            __body[i] = (value >> (((sizeof(int) / CHUNK_SIZE) - i - 1) * CHUNK_BITS)) & CHUNK_MAX;
        }
        if ((sizeof(int) % CHUNK_SIZE) > 0)
        {
            __body[__body_length - 1] = (value & CHUNK_MAX);
        }
    }
}

BigInteger::operator std::string() const
{
    return "";
}

std::string BigInteger::encode(const uint8_t &ch)
{
    return std::string{__c_table[(ch >> 4) & 0xF], __c_table[(ch)&0xF]};
}

uint8_t BigInteger::decode(const uint8_t &v)
{
    if ('0' <= v && v <= '9')
    {
        return v - '0';
    }
    else if ('A' <= v && v <= 'F')
    {
        return 10 + v - 'A';
    }
    else if ('a' <= v && v <= 'f')
    {
        return 10 + v - 'a';
    }
    return 0;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &bi)
{
    for (size_t i = 0; i < bi.__body_length; ++i)
    {
        out << BigInteger::encode(bi.__body[i]);
    }
    out << std::flush;
    return out;
}

BigInteger &operator<<(BigInteger &bi, const int &value)
{
    int additional_bytes = (value / 8) + ((value % 8 == 0) ? 0 : 1);
    CHUNK_TYPE *__new_body = new CHUNK_TYPE[bi.__body_length + additional_bytes];
    std::copy(bi.__body, bi.__body + bi.__body_length, __new_body);
    delete[] bi.__body;
    bi.__body = __new_body;
    bi.__body_length += additional_bytes;
    return bi;
}