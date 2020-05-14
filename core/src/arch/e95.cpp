#include "e95.h"

E95c::E95c(int sz)
{
    this->sz = sz;
}

void E95c::setup() const
{
    SPI.begin();
    pinMode(CS, OUTPUT);
    digitalWrite(CS, HIGH);
}

uint8_t E95c::read(uint16_t address) const
{
    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

    digitalWrite(CS, LOW);

    SPI.transfer(3); // READ
    SPI.transfer(address >> 8);
    SPI.transfer(address);

    uint8_t result = SPI.transfer(0);

    digitalWrite(CS, HIGH);

    SPI.endTransaction();

    return result;
}

void E95c::write(uint16_t address, uint8_t data) const
{
    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

    digitalWrite(CS, LOW);
    SPI.transfer(WREN);
    digitalWrite(CS, HIGH);

    digitalWrite(CS, LOW);

    SPI.transfer(2); // WRITE
    SPI.transfer(address >> 8);
    SPI.transfer(address);

    SPI.transfer(data);

    digitalWrite(CS, HIGH);

    SPI.endTransaction();
}

void E95c::dump() const
{

}