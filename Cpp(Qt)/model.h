#ifndef MODEL_H
#define MODEL_H

#include "luna.h"
#include "fusoorario.h"

class Model
{
private:
    orario* o;

public:
    Model();
    ~Model();

    void CreaOrario(int,int,int);
    void CreaData(int, int, int,bool, int, int, int);
    void CreaFuso(int, int, int,bool, int, int, int, int);
    void CreaLuna(int, int, int,bool, int, int, int);

    void clear();
    int cambiaformato() const;

    int Ore() const;
    int Min() const;
    int Sec() const;

    int Giorno() const;
    int Mese() const;
    int Anno() const;
    bool Emisfero() const;

    char getFascia() const;
    int getZona() const;

    void Somma(int, int, int, int, int, int);
    void Sub(int, int, int, int, int, int);

    bool checking() const;

    string Fase() const;
    string Stagione() const;
    string GiornoSettimana() const;
    int settimanaMese() const;
    int settimanaAnno() const;
    int getDurata(int,int,int) const;
    int getOreStudio(int,int,int,int) const;

    int ProsNuova();
    int ProsPiena();
    int UltimNuova();
    int UltimPiena();

    int DimFuso(char)const;
    int fDiff(int) const;
    void sommaFuso(int);
    void sottraiFuso(int);

};

#endif // MODEL_H
