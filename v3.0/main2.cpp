#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include "studentas.h"
#include "rusiavimas.h"
#include "pasirinkimai.h"

using std::cin;
using std::string;
using std::cout;
using namespace std::chrono;

/**
 * @brief Pagrindine programos funkcija.
 *
 * Cia paleidziama visa programa,
 * rodomas meniu ir kvieciamos
 * kitos funkcijos.
 *
 * @return programos pabaigos kodas
 */
int main() {
double suma1=0; //visam programos vykdymui
double suma2=0; //duomenu nuskaitymui
double suma3=0; //duomenu rusiavimui ekrane
double suma4=0; //duomenu rusiavimui faile
double suma5=0; //duomenu spausdinimui ekrane
double suma6=0; //duomenu spausdinimui faile
int spausd;
int b;
bool skaitytaIsFailo = false;

std::string CVfd;
std::string CVfr="rezultatas.txt";
string pavardes[] = { "Kazlauskas", "Petrauskas", "Jankauskas", "Vaitkus", "Kazlauskaite", "Petrauskaite", "Jankauskaite", "Vaitkute" };
string vardai[] = { "Jonas", "Petras", "Mantas", "Lukas", "Tomas", "Ieva", "Aiste", "Monika", "Greta", "Laura" };
int pavN = sizeof(pavardes) / sizeof(pavardes[0]);
int vardN = sizeof(vardai) / sizeof(vardai[0]);
std::vector<std::string> pavardesVec(pavardes, pavardes + pavN);
std::vector<std::string> vardaiVec(vardai, vardai + vardN);

std::vector<Studentas> studentai;
std::vector<Studentas> vargsiukai;
std::vector<Studentas> kietiakai;
srand(time(nullptr)); //kad kiekviena karta butu generuojami skirtingi pazymiai

    auto start1 = high_resolution_clock::now(); 

    //meniu
    int m = 0;
    while (m != 6) {
        cout << "Pasirinkite, kokiu budu norite, kad programa vykdytu uzduoti (1 - duomenu irasymas ranka, 2 - generuoti tik pazymius, 3 - generuoti studentu vardus, pavardes ir pazymius, 4 - nuskaityti duomenis is failo,  5 - generuoti failus, 6 - baigti darba): " << std::endl;
        while(true){
        try{
        cin >> m;
        if(std::cin.fail()) 
           throw std::invalid_argument("Ivesta reiksme nera skaicius");
        if (m<1||m>6) 
            throw std::out_of_range("Tokio pasirinkimo nera");

        break;
        }
        catch (const std::exception& e) {
        cout << "Klaida: " << e.what() << std::endl;
        cin.clear();
        cin.ignore(10000, '\n'); //pasirenkamas didelis skaicius, kad tikrai butu isvalyta ivedimo reiksme
    }
        }
        if(m==1) 
        {
        try
        {
            PirmasP(studentai, b);
        }
         catch (const std::exception& e)
            {
                cout<< "Klaida: "<<e.what()<<std::endl;
            }
        }
        if(m==2) 
        {
        try
        {
            AntrasP(studentai, b);
        }
         catch (const std::exception& e)
            {
                cout<< "Klaida: "<<e.what()<<std::endl;
            }
        }
        if(m==3) 
        {
            try
            {
                {TreciasP(studentai, pavardesVec, vardaiVec, b);}
            }
            catch(const std::exception& e)
            {
                std::cout<<"Klaida: "<< e.what() <<std::endl;
            }
        }
        if(m==4) 
        {
    cout << "Pasirinkite faila:\n";
    cout << "1 - studentai10000.txt\n";
    cout << "2 - studentai100000.txt\n";
    cout << "3 - studentai1000000.txt\n";

    std::ios::sync_with_stdio(false);
    cin.tie(nullptr); //del greitesnio duomenu spausdinimo

    int pasirinkimas;
    while(true)
    {
        try {
            cin>>pasirinkimas;
        if (cin.fail())
            throw std::invalid_argument("Ivestas ne skaicius\n");

        if (pasirinkimas != 1 && pasirinkimas!= 2&& pasirinkimas!=3)
            throw std::out_of_range("Galimi tik 1, 2 arba 3\n");

        break;
    }
    catch (const std::exception& e) {
        cout << "Klaida: " << e.what() << "bandykite dar karta:\n"<<std::endl;
        cin.clear();
        cin.ignore(10000, '\n'); //pasirenkamas didelis skaicius, kad tikrai butu isvalyta ivedimo reiksme
    }
    }
    if (pasirinkimas==1)
    {
        CVfd = "studentai10000.txt";
        studentai.reserve(10000);
    }
    else if (pasirinkimas == 2)
    {
       CVfd = "studentai100000.txt";
       studentai.reserve(100000);
    }
    else if (pasirinkimas == 3)
    {
        CVfd = "studentai1000000.txt";
        studentai.reserve(1000000);
    }   
     try
    {
        KetvirtasP(studentai, CVfd, CVfr, suma2, suma3, suma4, suma5, suma6, spausd, skaitytaIsFailo, b);
    }
    catch (const std::exception& e)
    {
        cout<< "Klaida: "<<e.what()<<std::endl;
    }
        }
    if(m==5) 
    {
       try
    {
        PenktasP();
    }
        catch (const std::exception& e)
        {
            cout<< "Klaida: "<<e.what()<<std::endl;
        }
    }
    
    if (m == 6) cout << "Baigiamas darbas.\n";
    
    } 
    auto end1 = high_resolution_clock::now();
    suma1 += duration<double>(end1 - start1).count();

cout<<"\nProgramos vykdymo laikas: "<<suma1<<"s"<<std::endl;
if(skaitytaIsFailo){
cout<<"Programos duomenu nuskaitymo is failo laikas: "<<suma2<<"s"<<std::endl;
if(spausd==1)
{
   cout<<"Programos duomenu rusiavimo laikas: "<<suma3<<"s"<<std::endl;
   cout<<"Programos duomenu spausdinimo laikas: "<<suma5<<"s"<<std::endl;
}
if(spausd==0)
{
   cout<<"Programos duomenu rusiavimo laikas: "<<suma4<<"s"<<std::endl;
   cout<<"Programos duomenu spausdinimo faile laikas: "<<suma6<<"s"<<std::endl;
}
}
  return 0;
}
