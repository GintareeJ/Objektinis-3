#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <list>
#include <deque>
#include <vector>

#include "pasirinkimai.h"
#include "rusiavimas.h"
#include "studentas.h"

using namespace std;
using namespace std::chrono;
/**
 * @brief Apskaiciuoja studentu galutinius balus.
 * @param studentai studentu konteineris
 * @param b skaiciavimo budas
 */
void Skaiciavimai(std::vector<Studentas>& studentai, int b)
{
    if (b == 0)
    {
        for (auto& s : studentai)
        {
            auto& paz = s.pazymiaiRef();
            if (paz.size() < 2) continue;
            double suma = 0.0;
            for (size_t j = 0; j < paz.size() - 1; j++)
            {
                suma += paz[j];
            }

            double galutinis = suma / (paz.size() - 1) * 0.4 + paz.back() * 0.6;
            s.setRez(galutinis);
        }
    }
    else
    {
        for (auto& s : studentai)
        {
            auto& paz = s.pazymiaiRef();
            if (paz.size() < 2) continue;
            std::sort(paz.begin(), paz.end() - 1);
            int nd = paz.size() - 1;
            double med;
            if (nd % 2 == 1) med = paz[nd / 2];
            else med = (paz[nd / 2 - 1] + paz[nd / 2]) / 2.0;

            double galutinis = med * 0.4 + paz.back() * 0.6;
            s.setRez2(galutinis);
        }
    }
}
/**
 * @brief Isveda studentu rezultatus.
 * @param studentai studentu konteineris
 * @param b skaiciavimo budas
 */
void Spausdinimas(std::vector<Studentas>& studentai, int& b)
{
    if (b == 0)
    {
        cout << std::left << std::setw(15) << "Pavarde"<< std::left << std::setw(15) << "Vardas"<< std::left << std::setw(15) << "Galutinis (Vid.)" << "\n";
        cout << "-----------------------------------------------\n";
        for (const auto& s : studentai) {
            cout << std::left << std::setw(15) << s.pavarde()<< std::left << std::setw(15) << s.vardas()<< std::fixed << std::setprecision(2) << s.rez()<< "\n";
        }
        cout << "-----------------------------------------------\n";
    }
    else
    {
        cout << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(15) << "Vardas"<< std::left << std::setw(15) << "Galutinis (Med.)" << "\n";
        cout << "-----------------------------------------------\n";
        for (const auto& s : studentai) {
            cout << std::left << std::setw(15) << s.pavarde()<< std::left << std::setw(15) << s.vardas()<< std::fixed << std::setprecision(2) << s.rez2()<< "\n";
        }
        cout << "-----------------------------------------------\n";
    }
}
/**
 * @brief Nuskaito studento varda ir pavarde.
 * @param s studentas
 * @return true jei ivestis pavyko
 */
bool VardasPavarde(Studentas& s)
{
    std::string v, p;
    while (true) {
        try {
            cout << "Iveskite studento varda (0 - baigti): ";
            cin >> v;
            if (v == "0")
                return false;
            for (char c : v) {
                if (!isalpha(c)) {
                    throw std::invalid_argument("Varda gali sudaryti tik raides.");
                }
            }
            s.setVardas(v);
            break;
        }
        catch (const std::exception& e) {
            cout << "Klaida: " << e.what() << " Bandykite dar karta:\n" << endl;
        }
    }
    while (true) {
        try {
            cout << "Iveskite pavarde: ";
            cin >> p;

            for (char c : p) {
                if (!isalpha(c)) {
                    throw std::invalid_argument("Pavarde gali sudaryti tik raides.");
                }
            }

            s.setPavarde(p);
            break;
        }
        catch (const std::exception& e) {
            cout << "Klaida: " << e.what() << " Bandykite dar karta:\n" << endl;
        }
    }

    return true;
}
/**
 * @brief Sugeneruoja atsitiktinius pazymius.
 */
void RandPaz(std::vector<Studentas>& studentai, Studentas& s, int& kiek)
{
    if (kiek == 0) {
        cout << "Pazymiai bus generuojami automatiskai, iveskite pazymiu kieki (min 2): ";
        while (true) {
            cin >> kiek;
            if (cin.fail()) {
                cout << "Iveskite skaiciu!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            if (kiek < 2) {
                cout << "Pazymiu kiekis turi buti ne mazesnis nei 2, bandykite dar karta:\n";
                continue;
            }
            break;
        }
    }
    s.clearPazymiai();
    for (int i = 0; i < kiek; i++)
    {
        s.addPazymys(rand() % 10 + 1);
    }

    studentai.push_back(std::move(s));
}
/**
 * @brief Leidzia pasirinkti vidurki arba mediana.
 */
int kinta()
{
    int a;
    while (true) {   
            cout << "Pasirinkite, kaip norite, kad butu skaiciuojamas galutinis balas - Vid (0) arba Med (1):" << std::endl;
            cin>>a; 
            if (cin.fail()) 
            { 
                cout << "Iveskite skaiciu: \n"; 
                cin.clear(); 
                cin.ignore(10000, '\n'); //pasirenkamas didelis sk, kad ivedimo reiksme tikrai butu isvalyta
                continue; 

            }
            if (a!=0&&a!=1) { 
                cout << "Skaicius turi buti 1 arba 0: \n"; 
                continue; }

                break;
            }
    return a;
}
/**
 * @brief Leidzia pasirinkti rusiavimo lauka.
 */
int kintrus(int& rus)
{
    int x;
    while (true) { 
            cout<<"Pasirinkite, pagal ka norite, jog butu suriuosatas studentu sarasas: 0 - vardas, 1 - pavarde, 2 - galutinis rez. (vid. arba med.)"<<std::endl;
            cin>>x; 
            if (cin.fail()) 
            { 
                cout << "Iveskite skaiciu: \n"; 
                cin.clear(); 
                cin.ignore(10000, '\n'); 
                continue; 
            }
            if (x!=0&&x!=1&&x!=2) { 
                cout << "Skaicius turi buti 2, 1 arba 0: \n"; 
                continue;
            }

            break;
        }
        return rus=x;
}
/**
 * @brief Leidzia pasirinkti rusiavimo tvarka.
 */
int kintr(int& r)
{
    int x;
  while (true) { 
    cout<<"Ar norite, jog jusu pasirinkimas butu surusiuotas didejanciai (0) ar mazejanciai (1)?"<<std::endl;
    cin>>x; 
    if (cin.fail()) 
    { 
        cout << "Iveskite skaiciu: \n"; 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        continue; 
    }
        if (x!=0&&x!=1) { 
        cout << "Skaicius turi buti 1 arba 0: \n"; 
        continue; }
                        
        break;
    }
    return r=x;
}
/**
 * @brief Pirmas meniu pasirinkimas.
 * Duomenys vedami ranka.
 */
void PirmasP(std::vector<Studentas>& studentai, int& b)
{
    while (true) {
        Studentas s;
        bool buvonulis = false;

        // jei vartotojas įveda 0 → baigiam
        if(!VardasPavarde(s)) break;

        int p;
        cout << "Iveskite pazymius (0 - baigti), paskutinis egzaminas (min 2): ";

        while (true)
        {
            cin >> p;

            if (cin.fail()) {
                cout << "Iveskite skaiciu: \n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (p == 0) {
                buvonulis = true;

                if (s.pazymiai().size() < 2) {
                    cout << "Reikia ivesti bent 2 pazymius (paskutinis - egzaminas), veskite dar karta: \n";
                    continue;
                }

                break;
            }

            if (p < 1 || p > 10) {
                cout << "Pazymys turi buti tarp 1 ir 10, veskite dar karta: \n";
                cin.ignore(10000, '\n');
                continue;
            }

            s.addPazymys(p);

            if (!buvonulis)
            {
                cout << "Ivedimas turi buti uzbaigtas 0.\n";
                buvonulis = true;
            }
        }

        studentai.push_back(std::move(s));
    }

    b = kinta();
    Skaiciavimai(studentai, b);
    Spausdinimas(studentai, b);
    studentai.clear();
}
/**
 * @brief Antras meniu pasirinkimas.
 */
void AntrasP(std::vector<Studentas>& studentai, int& b)
{
    int kiek = 0;
    while (true) {
        Studentas s;
        if(!VardasPavarde(s)) break;
        RandPaz(studentai, s, kiek);
    }
    b = kinta();
    Skaiciavimai(studentai, b);
    Spausdinimas(studentai, b);
    studentai.clear();
}
/**
 * @brief Trecias meniu pasirinkimas.
 */
void TreciasP(std::vector<Studentas>& studentai, const std::vector<std::string>& pavardes, const std::vector<std::string>& vardai, int& b)
{
    int skiek;
    int kiek = 0;
    int vardN = vardai.size();
    int pavN = pavardes.size();

    cout << "Sudentu vardai ir pavardes bus generuojami automatiskai, iveskite studentu kieki: ";
    while (true) {
        cin >> skiek;
        if (cin.fail()) {
            cout << "Iveskite skaiciu!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        break;
    }

    for (int i = 0; i < skiek; i++)
    {
        Studentas s;

        std::string v = vardai[rand() % vardN];
        std::string p;
        if (v.back() == 's') {
            do { p = pavardes[rand() % pavN]; } while (p.back() != 's');
        } else {
            do { p = pavardes[rand() % pavN]; } while (p.back() == 's');
        }
        s.setVardas(v);
        s.setPavarde(p);

        RandPaz(studentai, s, kiek);
    }
    b = kinta();
    Skaiciavimai(studentai, b);
    Spausdinimas(studentai, b);
    studentai.clear();
}
/**
 * @brief Ketvirtas meniu pasirinkimas.
 * Skaitymas is failo.
 */
void KetvirtasP(std::vector<Studentas>& studentai, const std::string& CVfd, const std::string& CVfr, double& suma2, double& suma3, double& suma4, double& suma5, double& suma6, int& spausd, bool& skaitytaIsFailo, int& b)
{
    skaitytaIsFailo = true;

    try {
        auto start2 = high_resolution_clock::now();
        NuskaitytiIsFailoBendras(studentai, CVfd);
        auto end2 = high_resolution_clock::now();
        suma2 = duration<double>(end2 - start2).count();
    }
    catch (const std::exception& e) {
        cerr << "Klaida: " << e.what() << "\n";
        return;
    }

    b = kinta();
    SkaiciavimaiBendras(studentai, b);

    int r;
    int rus;

    while (true) {
        cout << "Pasirinkite, kur norite, kad butu spausdinami duomenys (0 - faile, 1 - ekrane): " << endl;
        cin >> spausd;

        if (cin.fail()) {
            cout << "Iveskite skaiciu: \n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (spausd != 0 && spausd != 1) {
            cout << "Skaicius turi buti 1 arba 0: \n";
            continue;
        }
        break;
    }

    b = kinta();
    rus = kintrus(rus);
    r = kintr(r);

    if (spausd == 1)
    {
        auto start3 = high_resolution_clock::now();
        RusiuotiBendras(studentai, b, r, rus);
        auto end3 = high_resolution_clock::now();
        suma3 = duration<double>(end3 - start3).count();

        auto start5 = high_resolution_clock::now();

        if (b == 0)
        {
            cout << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas" << left << setw(15) << "Galutinis (Vid.)" << "\n";
            cout << "-----------------------------------------------\n";
            for (const auto& s : studentai) {
                cout << left << setw(15) << s.pavarde() << left << setw(15) << s.vardas()<< fixed << setprecision(2) << s.rez() << "\n";
            }
            cout << "-----------------------------------------------\n";
        }
        else
        {
            cout << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas" << left << setw(15) << "Galutinis (Med.)" << "\n";
            cout << "-----------------------------------------------\n";
            for (const auto& s : studentai) {
                cout << left << setw(15) << s.pavarde() << left << setw(15) << s.vardas()<< fixed << setprecision(2) << s.rez2() << "\n";
            }
            cout << "-----------------------------------------------\n";
        }

        auto end5 = high_resolution_clock::now();
        suma5 = duration<double>(end5 - start5).count();
    }
    else
    {
        auto start4 = high_resolution_clock::now();
        RusiuotiBendras(studentai, b, r, rus);
        auto end4 = high_resolution_clock::now();
        suma4 = duration<double>(end4 - start4).count();

        auto start6 = high_resolution_clock::now();
        SpausdintiIFaila(CVfr, studentai, b);
        auto end6 = high_resolution_clock::now();
        suma6 = duration<double>(end6 - start6).count();
    }

    studentai.clear();
}
/**
 * @brief Sugeneruoja studentu faila.
 */
void GeneruotiStudentuFaila(const std::string& failoPav, int studentuKiekis, int ndKiekis)
{
    std::ofstream fr(failoPav);
    if (!fr.is_open()) {
        throw std::runtime_error("Nepavyko sukurti failo");
    }

    //spausdiname antraste
    fr << std::left << std::setw(20) << "Vardas" << std::left << std::setw(20) << "Pavarde";

    for (int i = 1; i <= ndKiekis; i++) {
        fr << std::left << std::setw(8) <<("ND" + std::to_string(i));
    }
    fr << std::left << std::setw(8) << "Egz." << "\n";

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> pazymys(1, 10);

    for (int i = 1; i <= studentuKiekis; i++) {
        fr << std::left << std::setw(20) <<("VardasNR" + std::to_string(i))<< std::left << std::setw(20) <<("PavardeNR" + std::to_string(i));
        for (int j = 0; j < ndKiekis; j++) {
            fr << std::left << std::setw(8) << pazymys(gen);
        }
        fr << std::left << std::setw(8) << pazymys(gen) << "\n";
    }

    fr.close();
}
/**
 * @brief Penktas meniu pasirinkimas.
 * Atlieka konteineriu testus.
 */
void PenktasP()
{
    int b;
    int rus;
    int r;
    int ndKiekis=5;
    rus = kintrus(rus);
    r = kintr(r);
    b = kinta();
    
    cout << "\n100000 irasu\n";
    TestuotiKonteineri<std::vector<Studentas>>("vector", "studentai100000.txt", 100000, ndKiekis, b, r, rus, 3);

    cout << "\n1000000 irasu\n";
    TestuotiKonteineri<std::vector<Studentas>>("vector", "studentai1000000.txt", 1000000, ndKiekis, b, r, rus, 3);
}

/**
 * @brief Rusiuoja list konteineri.
 */
void RusiuotiBendras(std::list<Studentas>& studentai, int b, int r, int rus) //jei list
{
    if (b == 0) {
        if (rus == 0) {
            if (r == 0) studentai.sort(DidVar);
            else studentai.sort(MazVar);
        }
        else if (rus == 1) {
            if (r == 0) studentai.sort(DidPav);
            else studentai.sort(MazPav);
        }
        else {
            if (r == 0) studentai.sort(DidVid);
            else studentai.sort(MazVid);
        }
    }
    else {
        if (rus == 0) {
            if (r == 0) studentai.sort(DidVar);
            else studentai.sort(MazVar);
        }
        else if (rus == 1) {
            if (r == 0) studentai.sort(DidPav);
            else studentai.sort(MazPav);
        }
        else {
            if (r == 0) studentai.sort(DidMed);
            else studentai.sort(MazMed);
        }
    }
}
/**
 * @brief Padalina studentus i dvi grupes.
 */
void PadalintiStudentusBendras2(std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai, int b) // pagal antra strategija, jei list
{
    vargsiukai.clear();

    for (auto it = studentai.begin(); it != studentai.end();) {
        if (b == 0) {
            if (it->rez() < 5.0) 
            {
                vargsiukai.push_back(std::move(*it));
                it=studentai.erase(it);
            }
         else
         {
            ++it;
         }
        } 
        else {
            if (it->rez2() < 5.0) 
            {
                vargsiukai.push_back(*it);
                it=studentai.erase(it);
            }
         else
         {
            ++it;
         }
        }
    }
}
