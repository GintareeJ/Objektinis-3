#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

class Zmogus
{
protected:
    std::string vard;
    std::string pavard;

public:
//default konstruktorius
    Zmogus() = default;
//konstruktorius
    Zmogus(const std::string& v, const std::string& p) : vard(v), pavard(p) {}
//default destruktorius
virtual ~Zmogus() { 
        vard.clear();
        pavard.clear();
}
 // copy constructor
Zmogus(const Zmogus& other)
    : vard(other.vard),
      pavard(other.pavard) {}

// move constructor
Zmogus(Zmogus&& other) noexcept
    : vard(std::move(other.vard)),
    pavard(std::move(other.pavard))
{
    other.vard.clear();
    other.pavard.clear();
}

// copy assignment
Zmogus& operator=(const Zmogus& other)
{
    if (this != &other) {
        vard = other.vard;
        pavard = other.pavard;
}

    return *this;
}

// move assignment
Zmogus& operator=(Zmogus&& other) noexcept
{
    if (this != &other) {

        vard = std::move(other.vard);
        pavard = std::move(other.pavard);

        other.vard.clear();
        other.pavard.clear();
    }
    return *this;
}

//padaro klase abstrakcia
    virtual void abstract() const = 0;
//getteriai
    const std::string& vardas() const { return vard; }
    const std::string& pavarde() const { return pavard; }
//setteriai
    void setVardas(const std::string& v) { vard = v; }
    void setPavarde(const std::string& p) { pavard = p; }

};

#endif