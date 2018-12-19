#include "lax_friedrichs.h"
#include <cmath>

Lax_Friedrichs::Lax_Friedrichs(double Tfin,double inf, double sup,int nb_cell, double dx_crit, int n_fonc,double Eps)
{
    m_Tfin = Tfin;
    m_dx_crit = dx_crit;
    m_nFonc = n_fonc;
    m_Eps=Eps;

    a =2.;// coefficient pour la fonction a*u

    m_tmp = new Maillage(inf,sup,nb_cell);
    m_M = new Maillage(inf,sup,nb_cell);
    init_maill();
}

void Lax_Friedrichs::solve()
{
    double t=0;
    double dt;
    double Dx;
    std::vector<double> f_tmp;
    while(t<m_Tfin){
        this->Raffinement();
        dt=get_dt();
        t=t+dt;
        f_tmp.reserve(m_M->getNbCell());
        f_tmp.resize(m_M->getNbCell());
        for( int i=0;i<m_M->getNbCell();i++){ //calcul les valeurs de f_i
            f_tmp.at(i) =fonc(m_M->getValueCell(i));
        }
        for(int i=1; i<(m_M->getNbCell() - 1); i++)
        {
            double val;
            Dx=m_M->getDxCell(i);
            val=0.5*(m_M->getValueCell(i+1)+m_M->getValueCell(i-1))-0.5*dt/Dx*(f_tmp.at(i+1)-f_tmp.at(i-1));
            m_tmp->setValueCell(i, val);
        }
        std::swap(m_tmp, m_M);//Echange les deux maillages

    }
}

void Lax_Friedrichs:: Raffinement(){
    for(int i=0; i<m_M->getNbCell()-1 ;i++){
        if(std::abs(m_M->getValueCell(i)-m_M->getValueCell(i+1))>m_Eps && m_M->getDxCell(i)>m_dx_crit){// on raffine le maillage sous certaines conditions
            double Val_i=m_M->getValueCell(i);
            m_M->add_position(Val_i,i);
            m_tmp->add_position(Val_i,i);

            i++;
        }
    }

}

//Initialisation du maillage et choix de la fonction initiale

void Lax_Friedrichs::init_maill()
{
    if(m_nFonc==0){
        for(int i=0; i<m_M->getNbCell();i++){
            double mil;
            mil=m_M->getBinfCell(i)+m_M->getDxCell(i)*0.5;
            m_M->setValueCell(i,std::sin(2.*mil*M_PI));
        }
    }
    else{

        for(int i=0; i<m_M->getNbCell();i++){
            double mil;
            mil=m_M->getBinfCell(i)+m_M->getDxCell(i)*0.5;
            if(mil<-0.5 || mil>0.5){
                m_M->setValueCell(i,0);
            }
            else{
                m_M->setValueCell(i,1);
            }
        }
    }
}

//Choix de la fonction

double Lax_Friedrichs::fonc(double x)
{
    if(m_nFonc==0){
        return x*x*0.5;
    }
    else{
        return a*x;
    }
}

double Lax_Friedrichs::get_dt()
{
    double dx_min=m_M->getDxCell(0);
    double u_max=m_M->getValueCell(0);
    for (int i=1;i<m_M->getNbCell(); i++){
        if(u_max<m_M->getValueCell(i)){
            if(m_nFonc==0){
                u_max=m_M->getBsupCell(i);
            }
            else{
                u_max=a;
            }
        }
        if(dx_min>m_M->getDxCell(i)){
            dx_min=m_M->getDxCell(i);
        }
    }
    return dx_min/u_max;

}
double Lax_Friedrichs::get_Dx(){
    double dx_min=m_M->getDxCell(0);
    double u_max=m_M->getValueCell(0);
    for (int i=1;i<m_M->getNbCell(); i++){
            if(dx_min>m_M->getDxCell(i)){
            dx_min=m_M->getDxCell(i);
        }
    }
    return dx_min;


}

void Lax_Friedrichs::saveMaillage()
{
    std::ofstream myfile;
    std::ofstream myfile2;
    myfile.open("outY",std::ios::trunc);
    myfile2.open("outX",std::ios::trunc);


    for(int i=0; i<m_M->getNbCell(); ++i)
    {
        myfile <<m_M->getValueCell(i);
        myfile2 << m_M->getBinfCell(i) + m_M->getDxCell(i)/2.;
        if(i<m_M->getNbCell() - 1)
        {
            myfile2 << " ";
            myfile << " ";
        }
    }
    myfile << std::endl;
    myfile2 << std::endl;
    myfile.close();
    myfile2.close();
}
