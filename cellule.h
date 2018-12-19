#include <iostream>
#ifndef cellule_h
#define cellule_h

class Cellule{
  friend class Maillage;
public:
  Cellule();
  Cellule(const Cellule &c);
  Cellule(double inf, double sup, double valeur);

  double getValue() const;
  void setValue(double v);

  double getBinf() const;
  void setBinf(double inf);

  double getBsup() const;
  void setBsup(double sup);


private:
  double a,b;
  double uin;


};

std::ostream &operator<<(std::ostream &os, const Cellule &C);

#endif
