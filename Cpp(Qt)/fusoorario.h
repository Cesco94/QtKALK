#ifndef FUSOORARIO_H
#define FUSOORARIO_H
#include"data.h"
#include<map>

class fusoorario : public data
{
private:
    //Eredita sec, giorno, mese, anno
    int zona; //+ o - ore
    static std::map<int,char> fasce;

public:

    //COSTRUTTORI
    fusoorario();
    fusoorario(int);
    fusoorario(data,int =0);
    fusoorario(int,int,int,bool=1,int =0);
    fusoorario(const fusoorario&);
    //OPERAZIONI EREDITATE: INUTILE FARE OVERLOADING
    /*
    virtual void SommaSec(int);
    virtual void SommaMin(int);
    virtual void SommaOra(int);

    virtual void TogliSec(int);
    virtual void TogliMin(int);
    virtual void TogliOra(int);


    */
    virtual fusoorario* SommaOrario(const orario&) const;
    virtual fusoorario* SubOrario(const orario&) const;
    virtual void reset();
    //Di utilità
    char getFascia() const;
    int getZona() const;
    //OPERAZIONI AGGIUNTIVE
    static int dimmiFuso(char) ; //passo una fascia e voglio sapere il loro fusoorario
    int fusodiff(const fusoorario&) const; //differenza in ore tra fuso locale e fuso del parametro
    void sommafuso(int); //aggiornamento campi dati al cambio di fuso usando un intero per le ore
    void toglifuso(int); //


};

std::ostream& operator<<(std::ostream&, const fusoorario&);
#endif // FUSOORARIO_H
