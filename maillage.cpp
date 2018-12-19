#include "maillage.h"

//Constructeurs de maillage
Maillage::Maillage()
{
    nb_cellules=0;
}

Maillage::Maillage(double binf, double bsup, int nb_cell)
{
    double dx;
    dx=(bsup-binf)/static_cast<double>(nb_cell);
    nb_cellules=nb_cell;
    for (int i=0;i<nb_cell;i++){
        Cellule *tmp =new Cellule(binf + i*dx,binf + (i+1)*dx,0);
        m_V.push_back(tmp);
        if(i==nb_cell-1){
            tmp->setBsup(bsup);

        }
    }

}
Maillage :: Maillage(const Maillage &m){
    nb_cellules=m.nb_cellules;
}

//Ajoute une cellule au maillage
void Maillage::add_position(double valeur, int position)
{
    if(nb_cellules == 0)
    {
        Cellule *tmp = new Cellule(0., 1., valeur);
        m_V.push_back(tmp);
        nb_cellules++;
        return;
    }

    double inf = m_V.at(position)->getBinf();
    double mid = ( inf + m_V.at(position)->getBsup()) / 2.;
    m_V.at(position)->setBinf(mid);

    Cellule *tmp = new Cellule(inf, mid, valeur);

    m_V.insert(m_V.begin() + position, 1, tmp);
    nb_cellules++;
}

//Enleve une cellule au maillage
void Maillage::remove_position(int position)
{
    double inf = m_V.at(position)->getBinf();
    //Supprime la cellule alloué
    delete m_V.at(position);

    //Supprime la case du tableau
    m_V.erase( m_V.begin() + position);

    m_V.at(position)->setBinf(inf);
    nb_cellules--;
}

//retourne la valeur de la cellule ou -42 si la position n'est pas dans le maillage
double Maillage::operator[](int position)
{
    if( (position < 0) || (position >= nb_cellules) )
        return -42.;
    return m_V.at(position)->getValue();
}

// retourne le nombre de cellule du maillage
int Maillage::getNbCell() const
{
    return nb_cellules;
}

//retourne la borne inf de la cellule i du maillage
double Maillage::getBinfCell(int i) const
{
    return m_V.at(i)->getBinf();
}

//retourne la borne sup de la cellule i du maillage
double Maillage::getBsupCell(int i) const
{
    return m_V.at(i)->getBsup();
}

//retourne la taille de la cellule i
double Maillage::getDxCell(int i) const
{
    return getBsupCell(i)-getBinfCell(i);
}

//retourne la valeur de la cellule i
double Maillage::getValueCell(int i) const
{
    return m_V.at(i)->getValue();
}

//modifie la valeur de la cellule i
void Maillage::setValueCell(int i, double val)
{
    m_V.at(i)->setValue(val);
}

// surcharge de l'operateur affichage
std::ostream &operator<<(std::ostream &os, const Maillage &M)
{
    for (int i=0; i<M.nb_cellules; ++i)
    {
        os << *M.m_V.at(i) << std::endl;
    }


    return os;
}
