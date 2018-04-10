#include "model.h"

Model::Model(): o()
{
}

Model::~Model() { delete o; }
bool Model::checking() const{
    if (dynamic_cast<orario*>(o)) return true;
    else return false;
}

void Model::clear() {

    if(checking()) o->reset();

}
int Model::cambiaformato() const
{
    return o->formato();
}
void Model::CreaOrario(int ore, int min, int sec){

    orario* aux=new orario(ore,min,sec);
    if (o) delete o;
    o=aux;

}

void Model::CreaData(int g, int m, int a,bool e, int ore, int min, int sec){


    data* aux=new data(g,m,a,ore,min,sec,e);
    if (o) delete o;
    o=aux;
}
void Model::CreaFuso(int g, int m, int a,bool e, int ore, int min, int sec, int fascia){

    fusoorario* aux=new fusoorario(data(g,m,a,ore,min,sec,e),fascia);
    if (o) delete o;
    o=aux;
}
void Model::CreaLuna(int g, int m, int a,bool e, int ore, int min, int sec){

    luna* aux=new luna(data(g,m,a,ore,min,sec,e));
    if (0) delete o;
    o=aux;
}


int Model::Ore() const{
    return o->getOra();
}
int Model::Min()const {
    return o->getMin();
}
int Model::Sec()const {
    return o->getSec();
}

int Model::Anno()const{
    return dynamic_cast<data*>(o)->getAnno();
}
int Model::Giorno()const{
    return dynamic_cast<data*>(o)->getGiorno();
}
int Model::Mese()const{
    return dynamic_cast<data*>(o)->getMese();
}
bool Model::Emisfero() const
{
    return dynamic_cast<data*>(o)->getEmisfero();
}
void Model::Somma(int ore, int min, int sec, int giorni, int mesi, int anni){

    if(ore>23 || min>59 || sec>59)
    {
        o->SommaOra(ore);
        o->SommaMin(min);
        o->SommaSec(sec);
    }
   else
    {
        orario* aux=o;
        o=aux->SommaOrario(orario(ore,min,sec));
        delete aux;
    }
    data* aux=dynamic_cast<data*>(o);
    if(aux)
    {
        aux->avanzaTotGiorni(giorni);

        aux->avanzaTotGiorni(mesi*28);

        aux->cambiaAnno(dynamic_cast<data*>(o)->getAnno()+anni);
    }

}
void Model::Sub(int ore, int min, int sec, int giorni, int mesi, int anni){

    if(ore>23 || min>59 || sec>59)
    {
        o->TogliOra(ore);
        o->TogliMin(min);
        o->TogliSec(sec);
    }
    else
    {
        orario* aux1=o;
        o=aux1->SubOrario(orario(ore,min,sec));
        delete aux1;
    }

    data* aux=dynamic_cast<data*>(o);
    if(aux)
    {
       int countgiorni = aux->countgiorni()+365*(aux->getAnno()-1)+((aux->getAnno()-1)/4);//giorni trascorsi dall-anno 1

       if(countgiorni-giorni >=1)
       {
           aux->indietroTotGiorni(giorni);

       }
       else
       {
           aux->cambiaGiorno(1);
           aux->cambiaMese(1);
           aux->cambiaAnno(1);
       }

       if(countgiorni - (mesi*28) >=1)
       {
           aux->indietroTotGiorni(mesi*28);

       }
       else
       {
           aux->cambiaGiorno(1);
           aux->cambiaMese(1);
           aux->cambiaAnno(1);
       }

       if(aux->getAnno()-anni<=0)
        {
           aux->cambiaGiorno(1);
           aux->cambiaMese(1);
           aux->cambiaAnno(1);

        }
        else
        {
            aux->cambiaAnno(aux->getAnno()-anni);
        }

    }
}

string Model::Fase() const{
    return dynamic_cast<luna*>(o)->getFase();
}
char Model::getFascia() const
{
    return dynamic_cast<fusoorario*>(o)->getFascia();

}
int Model::getZona() const
{
    return dynamic_cast<fusoorario*>(o)->getZona();
}

string Model::Stagione() const{
    return dynamic_cast<data*>(o)->stagione();

}
string Model::GiornoSettimana() const{
    return dynamic_cast<data*>(o)->giornoSettimana();

}
int Model::settimanaMese() const
{
    return dynamic_cast<data*>(o)->settimanamese();
}

int Model::settimanaAnno() const
{
    return dynamic_cast<data*>(o)->settimanaanno();
}
int Model::getDurata(int giorno,int mese,int anno) const
{
    data* aux = dynamic_cast<data*>(o);
    if(giorno==aux->getGiorno() && mese==aux->getMese() && anno==aux->getAnno())
        return 0;
   return aux->durata(data(giorno,mese,anno));
}
int Model::ProsNuova(){

    return dynamic_cast<luna*>(o)->prossimaNuova();


}

int Model::ProsPiena(){

    return dynamic_cast<luna*>(o)->prossimaPiena();

}

int Model::UltimNuova(){

    return dynamic_cast<luna*>(o)->ultimaNuova();

}

int Model::UltimPiena(){

    return dynamic_cast<luna*>(o)->ultimaPiena();

}
int Model::getOreStudio(int giorno,int mese,int anno,int ore) const
{
    data*aux=dynamic_cast<data*>(o);

    if(giorno<=aux->getGiorno() && mese<=aux->getMese() && anno<=aux->getAnno())
        return 0;

    return aux->oreDiStudio(data(giorno,mese,anno),ore);
}

int Model::DimFuso(char s)const{

    return fusoorario::dimmiFuso(s);

}
int Model::fDiff(int s) const{
    return dynamic_cast<fusoorario*>(o)->fusodiff(fusoorario(s));
}
void Model::sommaFuso(int s)
{
    dynamic_cast<fusoorario*>(o)->sommafuso(s);

}

void Model::sottraiFuso(int s)
{
   dynamic_cast<fusoorario*>(o)->toglifuso(s);
}
