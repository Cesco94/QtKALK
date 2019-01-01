#include "orario.h"

//COSTRUTTORI
orario::orario() : sec(0) {}
orario::orario(int o)
{
    if(o<0 || o>23)
       throw overflow_error();
    else
        sec=o*3600;
}

orario::orario(int o,int m)
{
    if(o<0 || o>23 || m<0 || m>59)
        throw overflow_error();
    else
        sec=o*3600+m*60;
}
orario::orario(int o,int m,int s)
{
    if(o<0 || o>23 || m<0 || m>59 || s<0 || s>59)
        throw overflow_error();
    else
        sec=o*3600+m*60+s;
}

void orario::reset(){
    sec =0;
}
//ricordarsi di scrivere i catch appositi nel main
//REGOLA DEL 3
orario::orario(const orario& o) : sec(o.getSecTot()) {}

orario::~orario() {}


//OPERAZIONI

void orario::SommaSec(int s)
{
    if (s<0) throw overflow_error();
    if(sec+s>=86400)
    {
        int aux=(sec+s)%86400;
        sec=aux;
    }
    else
    {
        sec+=s;
    }
}
void orario::SommaMin(int m)
{
    if (m<0) throw overflow_error();
    if(sec+m*60>=86400)
    {
        int aux=(sec+m*60)%86400;
        sec=aux;
    }
    else
       sec+=m*60;
}
void orario::SommaOra(int o)
{
    if (o<0) throw overflow_error();
    if(sec+o*3600>=86400)
    {
        int aux=(sec+o*3600)%86400;
        sec=aux;
    }
    else
        sec+=o*3600;
}

void orario::TogliSec(int s)
{
    if (s<0) throw overflow_error();
    if(s==0) return;
    if(sec>0)
    {
        if(sec-s<0)
        {
            int aux=s%sec;
            sec=86400-aux;
        }
        else
            sec-=s;

    }
    else//secondi a zero
    {
        int aux=s%86400;
        sec=86400-aux;
    }
}

void orario::TogliMin(int m)
{
    if (m<0) throw overflow_error();
    if(m==0) return;
    if(sec>0)
    {

        if(sec-m*60<0)
        {
            int aux=m*60%sec;
            sec=86400-aux;
            }
        else
            sec-=m*60;
    }
    else
    {
        int aux=m*60%86400;
        sec=86400-aux;

    }
}

void orario::TogliOra(int o)
{
    if (o<0) throw overflow_error();
    if(o==0) return;
    if(sec>0)
    {
        if(sec-o*3600<0)
        {
            int aux=o*3600%sec;
            sec=86400-aux;
        }
        else
        sec-=o*3600;

    }
    else
    {
        int aux=o*3600%86400;
        sec=86400-aux;

    }
}

int orario::ConvertiInOredate(int giorni,int ore)//modificarla passando anche le ore lavorative
{
    if(giorni<=0)
        throw overflow_error();
    else
        return giorni*ore;
}

int orario::formato() const
{
    if(getOra()>12)
        return getOra()%12;
    else
        return getOra();
}

//SOMMA TRA ORARI
orario* orario::SommaOrario(const orario & o1) const
{
    if(o1.getSecTot()==0) return new orario(*this);
    orario* o2=new orario();
    if(sec+o1.getSecTot()>=86400)
        o2->sec=(sec+o1.getSecTot())%86400;
    else
        o2->sec=sec+o1.getSecTot();
  return o2;
}
orario* orario::SubOrario(const orario & o1) const
{
    if(o1.getSecTot()==0) return new orario(*this);
    orario* o2=new orario();
    if(o1>*this)
    {
        if(sec==0)
        {
            o2->sec=86400-(o1.getSecTot());
        }
        else
        {
            o2->sec=86400-(o1.getSecTot()%sec);

        }

    }
    else
        o2->sec=sec-o1.getSecTot();
    return o2;
}

int orario::getOra() const
{
    return sec/3600;
}
int orario::getMin() const
{
    return (sec/60)%60;
}
int orario::getSec() const
{
    return sec%60;
}

int orario::getSecTot() const
{
    return sec;
}


void orario::aggiornaSec(int s)
{
    sec=s;
}

bool orario::operator >(const orario& o1) const
{
    if(getSecTot()> o1.getSecTot())
        return true;
    else
        return false;
}


std::ostream& operator<<(std::ostream& os,const orario& o1)
{
    return os << o1.getOra()<<":"<<o1.getMin()<<":"<<o1.getSec();
}


