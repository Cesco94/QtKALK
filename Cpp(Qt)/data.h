#ifndef DATA_H
#define DATA_H
#include<orario.h>
#include<string>

using std::string;
class data : public orario {
private:

    //Eredita int sec;
    int giorno;
    int mese;
    int anno;
    bool emisfero; //1 boreale, 0 australe

public:
    data(); //costruttore 1 gennaio 2000 alle 00:00:00
    data(int, int, int,int =0,int=0,int=0,bool =1); //giorno, mese, anno,ore,minuti,secondi, emisfero
    data(const data&);
    //OPERAZIONI EREDITATE

    //OPERAZIONI IN OVERRIDING
    virtual void SommaSec(int);
    virtual void SommaMin(int);
    virtual void SommaOra(int);

    virtual void TogliSec(int);
    virtual void TogliMin(int);
    virtual void TogliOra(int);

    virtual data* SommaOrario(const orario&) const;
    virtual data* SubOrario(const orario&) const;

    virtual void reset();
    //RIDEFINIZIONE

    int durata(const data&) const;//ritorna un intero che è la differenza in giorni tra le due date

    //UTILITA'

    int giorniMese(int) const; //ritorna i giorni del mese passato al metodo
    int getGiorno() const;
    int getMese() const;
    int getAnno() const;
    bool getEmisfero() const;

    int oreDiStudio(const data&,int);

    virtual void cambiaGiorno(int);
    virtual void cambiaMese(int);
    virtual void cambiaAnno(int);
    void cambiaEmis(bool);
    bool operator>(const data&) const;

    //OPERAZIONI AGGIUNTIVE
    int countgiorni() const;
    static bool bisestile(int);
    string giornoSettimana() const;
    string stagione() const;
    virtual void avanzaUnGiorno();
    virtual void indietroUnGiorno();
    virtual void avanzaTotGiorni(int);
    virtual void indietroTotGiorni(int);
    int settimanaanno() const;
    int settimanamese() const;
};


std::ostream& operator<<(std::ostream&,const data&);
#endif // DATA_H
