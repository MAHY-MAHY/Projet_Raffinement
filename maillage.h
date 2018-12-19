#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <vector>
#include <iostream>

#include "cellule.h"

class Maillage
{
public:
    Maillage();
    Maillage(double binf, double bsup, int nb_cell);
    Maillage(const Maillage &m); //par recopie


    // MÉTHODES DE MODIFICATION
    // Ajout a une position
    void add_position(double valeur, int position);
    // Retrait a une position
    void remove_position(int position);
    // METHDOES DE CONSULTATION
    int consult_position(int position, int & valeur) const;
    // SURCHARGE D’OPERATEUR
    // Donner la valeur de u_i^n dans maille d’indice=position
    double operator[] (int position);

    int getNbCell() const;
    double getBinfCell(int i) const;
    double getBsupCell(int i) const;
    double getDxCell(int i) const;
    double getValueCell(int i) const;
    void setValueCell(int i, double val);

friend std::ostream & operator<<(std::ostream &os, const Maillage &M);

protected:
    int nb_cellules;
    // Nombre de cellules du maillage.
    std::vector<Cellule*> m_V;
};


#endif // MAILLAGE_H
