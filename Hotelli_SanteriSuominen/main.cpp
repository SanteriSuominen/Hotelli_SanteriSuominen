#include <iostream>
#include <fstream>
#include <string>
#include "Hotel.h"
// mainiss‰ ei muuta tarvitse kutsua kuin hotel classia ja sielt‰ process funktio jossa on main logiikka
int main()
{
    Hotel hotel = Hotel(); // luodaan hotelli ohjelma
    
    hotel.process(); // k‰ynnistett‰‰n hotelli ohjelma
    return 0;
}
