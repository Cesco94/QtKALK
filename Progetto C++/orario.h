#ifndef ORARIO_H
#define ORARIO_H
#include<iostream>
#include "overflow_error.h"

using std::cout;


class orario
{
private:
    int sec;

public:

    //COSTRUTTORI
    orario(); //mezzanotte
    orario(int);//ora
    orario(int o, int);//ora,min
    orario(int,int,int);//ora,min,sec

    //POTREBBERO NON ESSERE RICHIESTI, NESSUN CAMPO PUNTATORE
    //Costruttori copia profonda
    orario(const orario&);
    //DISTRUTTORE
    virtual ~orario();
    //OPERATORE D'ASSEGNAZIONE
    orario& operator=(const orario&);

    //OPERAZIONI
    virtual void SommaSec(int);
    virtual void SommaMin(int);
    virtual void SommaOra(int);

    virtual void TogliSec(int);
    virtual void TogliMin(int);
    virtual void TogliOra(int);

    static int ConvertiInOredate(int ,int );

    virtual void reset();

    //SOMMA E SUB TRA ORARI
    virtual orario* SommaOrario(const orario&) const;
    virtual orario* SubOrario(const orario&) const;

    //METODI DI UTILIZZO FACILITATO PER OPERAZIONI
    bool operator >(const orario&) const;
    int getOra() const;
    int getMin() const;
    int getSec() const;
    int getSecTot() const;
    void aggiornaSec(int);

    //METODO DEL CAMBIO DI VISUALIZZAZIONE DELL'ORA
    int formato() const;

};

std::ostream& operator<<(std::ostream&,const orario&);
#endif // ORARIO_H
/*
 * Riscrivere somma orario e sub orario in modo che facciano side effect
*/
