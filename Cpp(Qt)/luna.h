#ifndef LUNA_H
#define LUNA_H
#include "data.h"
#include<cstdlib>
class luna : public data
{
private:

    //Eredita i campi dati di fusoorario

    //Nuovo CampoDati
    string fase; //Esprime la visibilità in percentuale della luna

public:

    //Costruttore che assegna a fase la percentuale di visibilità della luna a partire dalla data
    luna();
    luna(const data&); //a partire da una data già instanziata
    luna(int, int, int); //passando giorno/mese/anno
    luna(const luna&);
    //DA RIDEFINIRE

    virtual void avanzaUnGiorno();
    virtual void indietroUnGiorno();
    virtual void avanzaTotGiorni(int);
    virtual void indietroTotGiorni(int);

    virtual void SommaSec(int);
    virtual void SommaMin(int);
    virtual void SommaOra(int);

    virtual void TogliSec(int);
    virtual void TogliMin(int);
    virtual void TogliOra(int);

    virtual luna* SommaOrario(const orario&) const;
    virtual luna* SubOrario(const orario&) const;

    virtual void reset();

    virtual void cambiaGiorno(int);
    virtual void cambiaMese(int);
    virtual void cambiaAnno(int);

    //OPERAZIONI AGGIUNTIVE

    string getFase() const;

    int epatta() const; //Metodo che restituisce Epatta lunare dell'anno corrente

    //Metodi che ritornano quanti giorni mancano alla prossima luna piena/nuova o quanti ne sono trascorsi

    int prossimaPiena()const;
    int prossimaNuova() const;
    int ultimaPiena() const;

    //Metodo principale su cui si basa tutto il calcolo del calendario lunare:
    int ultimaNuova() const; //Metodo che ritorna i giorni trascorsi dall'ultima luna nuova ossie "l'eta' della luna in giorni"

    //Metodi che dicono in che fase si è
    bool crescente()const;
    bool calante()const;
    bool piena()const;
    bool nuova()const;

};
std::ostream& operator<<(std::ostream&,const luna&);
#endif // LUNA_H
