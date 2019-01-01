#include "fusoorario.h"

std::map<int,char> creamap()
{
    std::map<int,char> f;
    f[-12]='Y';
    f[-11]='X';
    f[-10]='W';
    f[-9]='V';
    f[-8]='U';
    f[-7]='T';
    f[-6]='S';
    f[-5]='R';
    f[-4]='Q';
    f[-3]='P';
    f[-2]='O';
    f[-1]='N';
    f[0]='Z';
    f[1]='A';
    f[2]='B';
    f[3]='C';
    f[4]='D';
    f[5]='E';
    f[6]='F';
    f[7]='G';
    f[8]='H';
    f[9]='I';
    f[10]='K';
    f[11]='L';
    f[12]='M';

    return f;
}
std::map<int,char> fusoorario::fasce=creamap();


fusoorario::fusoorario() : zona(0) {}
fusoorario::fusoorario(int fascia) : data(), zona(fascia) {if(fascia>12 || fascia<-12) throw overflow_error();}
fusoorario::fusoorario(data oggi,int fascia) : data(oggi), zona(fascia) {if(fascia>12 || fascia<-12) throw overflow_error();}
fusoorario::fusoorario(int g,int m,int a,bool e ,int fascia) : data(g,m,a,e),zona(fascia) {if(fascia>12 || fascia<-12) throw overflow_error();}
fusoorario::fusoorario(const fusoorario & f) : data(f), zona(f.getZona()) {}
char fusoorario::getFascia() const
{
    return fasce[zona];
}
int fusoorario::getZona() const
{
    return zona;
}

int fusoorario::dimmiFuso(char z)
{
    bool ok=true;
    int aux=0;
  for(int i=-12;i<13 && ok==true;i++)
  {
      if(fasce[i]==z)
      {
          ok=false;
          aux=i;
       }
  }
  return aux;
}



int fusoorario::fusodiff(const fusoorario& fuso) const
{
    if(zona>fuso.zona)
    {
        return zona-fuso.zona;
    }
    else
    {
        if(zona==fuso.zona)
            return 0;
        else
            return fuso.zona-zona;
    }
}

//aggiornamento del fuso orario
void fusoorario::sommafuso(int fuso)
{
    if(zona+fuso>12)
    {
        fuso=zona+fuso-12;
        int zonaprec=zona;
        zona=-12+fuso-1;
        data::TogliOra(-zona+zonaprec);

    }
    else
    {
        zona=zona+fuso;
        data::SommaOra(fuso);
    }
}

void fusoorario::toglifuso(int fuso)
{
    if(zona-fuso<-12)
    {
        fuso=-zona+fuso-12;
        int zonaprec=zona;
        zona=12-fuso+1;
        data::SommaOra(zona-zonaprec);
    }
    else
    {
        zona=zona-fuso;
        data::TogliOra(fuso);
    }
}
std::ostream& operator<<(std::ostream& os, const fusoorario& f)
{
    os <<data(f)<<std::endl;
    os <<"Fascia:"<<" "<< f.getFascia()<<std::endl;
    return os;
}
fusoorario* fusoorario::SommaOrario(const orario& o1) const
{
    fusoorario* d1=new fusoorario(*this);
    if(d1->getSecTot()+o1.getSecTot()>=86400)
    {
        d1->avanzaUnGiorno();
        d1->aggiornaSec((d1->getSecTot()+o1.getSecTot())%86400);
    }
    else
    {
        d1->aggiornaSec(d1->getSecTot()+o1.getSecTot());
    }
    return d1;
}
fusoorario* fusoorario::SubOrario(const orario& o1) const
{
    if (o1.getSecTot()==0) return new fusoorario(*this);
    fusoorario* d1=new fusoorario(*this);
    if(d1->getSecTot()-o1.getSecTot()<0)
    {
        if(d1->getSecTot()==0)
        {
            d1->indietroUnGiorno();
            d1->aggiornaSec(86400-(o1.getSecTot()));

        }
        else
        {
            d1->indietroUnGiorno();
            d1->aggiornaSec(86400-(o1.getSecTot()%d1->getSecTot()));

        }
    }
    else
        d1->aggiornaSec(d1->getSecTot()-o1.getSecTot());

    return d1;

}

void fusoorario::reset()
{
    data::reset();
   zona=0;
}
