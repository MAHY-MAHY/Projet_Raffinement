#ifndef LAX_FRIEDRICHS_H
#define LAX_FRIEDRICHS_H

#include <string>
#include <fstream>
#include <iostream>

#include "maillage.h"
#include "cellule.h"

class Lax_Friedrichs
{
private:
    Maillage *m_M;
    Maillage *m_tmp;
    double m_Tfin;
    int m_nFonc;
    double m_dx_crit;
    double a;
    double m_Eps;


public:
    Lax_Friedrichs(double Tfin,double inf, double sup,int nb_cell, double dx_crit, int n_fonc, double m_Eps);
    void Raffinement();
    void solve();
    void saveMaillage();

private:
    void init_maill();
    double fonc(double x);
    double get_dt();
    double get_Dx();
};

#endif // LAX_FRIEDRICHS_H

