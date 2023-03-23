#include <iostream>

#include <BigInteger.hpp>

int main(int argc, char** argv)
{
    BigInteger bi(65535, Endian::Endian_Little);
    std::cout << bi << std::endl;

    return 0;
}