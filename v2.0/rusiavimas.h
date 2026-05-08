#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include "studentas.h"

/**
 * @brief Funkcijos studentu rusiavimui.
 */
/**
 * @brief Rusiuoja pagal pavarde didejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool DidPav(const Studentas& A, const Studentas& B);
/**
 * @brief Rusiuoja pagal varda didejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool DidVar(const Studentas& A, const Studentas& B);
/**
 * @brief Rusiuoja pagal vidurki didejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool DidVid(const Studentas& A, const Studentas& B);
/**
 * @brief Rusiuoja pagal mediana didejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool DidMed(const Studentas& A, const Studentas& B);

/**
 * @brief Rusiuoja pagal pavarde mazejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool MazPav(const Studentas& A, const Studentas& B);
/**
 * @brief Rusiuoja pagal varda mazejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool MazVar(const Studentas& A, const Studentas& B);
/**
 * @brief Rusiuoja pagal vidurki mazejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool MazVid(const Studentas& A, const Studentas& B);
/**
 * @brief Rusiuoja pagal mediana mazejancia tvarka.
 * @param A pirmas studentas
 * @param B antras studentas
 * @return true jei A turi buti anksciau
 */
bool MazMed(const Studentas& A, const Studentas& B);

#endif