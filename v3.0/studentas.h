#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <vector>
#include <iostream>
#include <iomanip>

class Studentas : public Zmogus {
private:
    std::vector<int> paz;
    double rez_ = 0.0;
    double rez2_ = 0.0;

public:
//default konstruktorius
    Studentas() {}
//konstruktorius
    Studentas(const std::string& v, const std::string& p, const std::vector<int>& pazymiai)
        : Zmogus(v, p), paz(pazymiai) {}

//destruktorius
~Studentas() override { 
        vard.clear();
        pavard.clear();
        paz.clear();
        rez_=0.0;
        rez2_=0.0; 
    }
//copy k.
    Studentas(const Studentas& other)
        : Zmogus(other),
          paz(other.paz),
          rez_(other.rez_),
          rez2_(other.rez2_) {}
//move k.
    Studentas(Studentas&& other) noexcept
        : Zmogus(std::move(other)),  
          paz(std::move(other.paz)),
          rez_(other.rez_),
          rez2_(other.rez2_) {
        other.rez_ = 0.0;
        other.rez2_ = 0.0;
          }
//copy assigment k.
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            paz = other.paz;
            rez_ = other.rez_;
            rez2_ = other.rez2_;
        }
        return *this;
    }
//move assigment k.
    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            Zmogus::operator=(std::move(other));
            paz = std::move(other.paz);
            rez_ = other.rez_;
            rez2_ = other.rez2_;
        }
        other.rez_ = 0.0;
        other.rez2_ = 0.0;
        return *this;
    }
//padaro studentas isvestine klase
    void abstract() const override {}
//getteriai
    const std::vector<int>& pazymiai() const { return paz; }
    std::vector<int>& pazymiaiRef() { return paz; }
    double rez() const { return rez_; }
    double rez2() const { return rez2_; }
//setteriai
    void addPazymys(int p) { paz.push_back(p); }
    void clearPazymiai() { paz.clear(); }
    void setPazymiai(const std::vector<int>& p) { paz = p; }
    void setRez(double r) { rez_ = r; }
    void setRez2(double r) { rez2_ = r; }

 friend std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.vard 
       << std::left << std::setw(15) << s.pavard;

    for (auto p : s.paz) {
        os << p << " ";
    }
    
    if (s.rez_ > 0) {
        os << std::fixed << std::setprecision(2) << " | Vid: " << s.rez_;
    }
    if (s.rez2_ > 0) {
        os << std::fixed << std::setprecision(2) << " | Med: " << s.rez2_;
    }
    
    return os;
}

friend std::istream& operator>>(std::istream& is, Studentas& s)
{
    std::string v, p;

    is >> v >> p;

    s.setVardas(v);
    s.setPavarde(p);

    int paz;
    s.clearPazymiai();

    while (is >> paz) {
        s.addPazymys(paz);

        if (is.peek() == '\n')
            break;
    }

    return is;
}

};

#endif