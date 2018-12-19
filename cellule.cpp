#include "cellule.h"

//Constructeurs de cellule
Cellule::Cellule():a(-1.),b(1.), uin(0.){
}

Cellule::Cellule(double inf, double sup, double valeur){
    a=inf;
    b=sup;
    uin = valeur;
}

Cellule::Cellule(const Cellule &c){
    a = c.a;
    b = c.b;
    uin = c.uin;
}

//retourne la valeur de la cellule
double Cellule::getValue() const
{
    return uin;
}

//modifie la valeur de la cellule
void Cellule::setValue(double v)
{
    uin = v;
}

//retourne la borne inf de la cellule
double Cellule::getBinf() const
{
    return a;
}

//modifie la borne inf de la cellule
void Cellule::setBinf(double inf)
{
    a = inf;
}

//Retourne la borne sup de la cellule

double Cellule::getBsup() const
{
    return b;
}

//modifie la borne sup de la cellule
void Cellule::setBsup(double sup)
{
    b=sup;
}

//Surcharge del'operateur d'affichage
std::ostream &operator<<(std::ostream &os, const Cellule &C)
{
    os << "[" << C.getBinf() << "," << C.getValue() << "," << C.getBsup() << "]";
    return os;
}
