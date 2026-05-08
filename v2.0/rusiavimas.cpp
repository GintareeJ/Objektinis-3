#include "rusiavimas.h"
/**
 * @brief Funkciju studentu rusiavimui realizavimas.
 */
bool DidPav(const Studentas &A, const Studentas &B) { return A.pavarde() < B.pavarde(); }
bool DidVar(const Studentas &A, const Studentas &B) { return A.vardas() < B.vardas(); }
bool DidVid(const Studentas &A, const Studentas &B) { return A.rez() < B.rez(); }
bool DidMed(const Studentas &A, const Studentas &B) { return A.rez2() < B.rez2(); }

bool MazPav(const Studentas &A, const Studentas &B) { return A.pavarde() > B.pavarde(); }
bool MazVar(const Studentas &A, const Studentas &B) { return A.vardas() > B.vardas(); }
bool MazVid(const Studentas &A, const Studentas &B) { return A.rez() > B.rez(); }
bool MazMed(const Studentas &A, const Studentas &B) { return A.rez2() > B.rez2(); }
