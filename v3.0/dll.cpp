#include <iostream>
#include "Dll.h"

extern "C" __declspec(dllexport)
void ParodytiDLLPranesima()
{
    std::cout << "DLL failas sekmingai panaudotas programoje.\n";
}