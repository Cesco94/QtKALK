#include "data.h"

using std::endl;

data::data() : orario(),giorno(1) , mese(1), anno(2000), emisfero(1)
{

}

data::data(int g, int m, int a, int o, int min,int s, bool emis) : orario(o,min,s),giorno(g),mese(m),anno(a),emisfero(emis) {


    if(m<1||m>12)
        throw overflow_error();

    //Controllo del giorno
    if(g<1||g>giorniMese(m)) //così si lancia errore anche per il 30 Febbraio ad esempio
        throw overflow_error();

    //Controllo anno, va bene qualsiasi anno, tranne i negativi
    if(a<=0)
        throw overflow_error();

}
void data::reset(){
    aggiornaSec(0);
    giorno=mese=emisfero=1;
    anno=2000;
}

int data::oreDiStudio(const data& d,int ore)
{
    if(ore<0)
        throw overflow_error();
    else
    {
        int dur=durata(d);
        return ConvertiInOredate(dur,ore);
    }
}

data::data(const data& d) : orario(d) , giorno(d.getGiorno()), mese(d.getMese()),
    anno(d.getAnno()), emisfero(d.getEmisfero()) {}
std::ostream& operator<<(std::ostream& os,const data& d1)
{
    string s;
    if(d1.getEmisfero()==1)
        s="Boreale";
    else
        s="Australe";
    os << d1.getGiorno() <<"/"<<d1.getMese()<<"/"<<d1.getAnno()<<"["<<s<<"]"<<endl;
    os << orario(d1.getOra(),d1.getMin(),d1.getSec());
    return os;
}
int data::getGiorno() const{
    return giorno;
}
int data::getMese() const {
    return mese;
}
int data::getAnno() const {
    return anno;
}
bool data::getEmisfero() const {
    return emisfero;
}
int data::countgiorni() const
{
    int count=giorno;
    for(int i=1;i<mese;i++)
    {
       count=count+ giorniMese(i);
    }

    return count;
}
bool data::bisestile(int a)
{
    if(a<=0) throw overflow_error();

    if(a%4==0)
    {
        if(a%100==0)
        {
            if(a%400==0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

int data::giorniMese(int m) const {

    if(m<1||m>12) throw overflow_error();

    if(m==2)
        {
            if(bisestile(anno))
                return 29;
            else
                return 28;
        }
        if(m<8 && m%2!=0)
            return 31;
        else if(m<8 && m%2==0)
                return 30;
            else if(m>8 && m%2!=0)
                    return 30;
                else
                    return 31;
}

void data::avanzaUnGiorno(){
    if(giorno<giorniMese(mese)) giorno++;
    else if (mese<12) {giorno=1;mese++;}
    else {giorno=1; mese=1;anno++;}
}
void data::indietroUnGiorno(){
    if (giorno>1) giorno--;
    else if (mese==1){anno--;mese=12;giorno=31;} //era il 1 gennaio quindi vado anche indietro di un anno
    else {
        mese--; //e' il primo di un mese che non è gennaio
        giorno = giorniMese(mese); //mese è diminuito, devo sapere se casco nel 30 o nel 31 o nel 28/29
    }
}

string data::giornoSettimana() const
{
    int count=anno+(anno-1)/4-(anno-1)/100+(anno-1)/400+countgiorni();
    count=count%7;
    switch(count)
    {
        case(0):
            return "Sabato";
            
        case(1):
            return "Domenica";
            
        case(2):
            return "Lunedi'";
            
        case(3):
            return "Martedi'";
            
        case(4):
            return "Mercoledi'";
            
        case(5):
            return "Giovedi'";
            
        case(6):
            return "Venerdi'";
            
    }
    return 0;
}

string data::stagione() const
{
    int aux=countgiorni();
    if(aux<79 || aux>355)
    {
        if(emisfero==1)
            return "Inverno";
        else
            return "Estate";
    }
    else if(aux>=79 && aux<172)
    {
        if(emisfero==1)
            return "Primavera";
        else
            return "Autunno";
    }
    else if(aux>=172 && aux<263)
    {
        if(emisfero==1)
            return "Estate";
        else
            return "Inverno";
    }
    else if(aux>=263 && aux<355)
    {
        if(emisfero==1)
            return "Autunno";
        else
            return "Primavera";
    }

    return 0;

}

int data::settimanaanno() const
{
    data aux(1,1,anno,1);
    string firstday=aux.giornoSettimana();
    int x=0;
    if (firstday=="Lunedi'") x=1;
    else if (firstday=="Martedi'") x=2;
    else if (firstday=="Mercoledi'") x=3;
    else if (firstday=="Giovedi'") x=4;
    else if (firstday=="Venerdi'") x=5;
    else if (firstday=="Sabato") x=6;
    else if (firstday=="Domenica") x=7;
    switch(x)
    {
    case(1):
        if (countgiorni()<8) return 1;
        else {
            if(countgiorni()%7==0)
                return (countgiorni()/7);
            else
                return (countgiorni()/7+1);
        }
        
    case(2):
        if(countgiorni()<7) return 1;
        else {
            if((countgiorni()-6)%7==0)
                return ((countgiorni()-6)/7+1);
            else
                return ((countgiorni()-6)/7+2);
        }
        
    case(3):
        if(countgiorni()<6) return 1;
        else {
            if((countgiorni()-5)%7==0)
                return ((countgiorni()-5)/7+1);
            else
                return ((countgiorni()-5)/7+2);
        }
        
    case(4):
        if(countgiorni()<5) return 1;
        else {
            if((countgiorni()-4)%7==0)
                return ((countgiorni()-4)/7+1);
            else
                return ((countgiorni()-4)/7+2);
        }
        
    case(5):
        if(countgiorni()<4) return 1;
        else {
            if((countgiorni()-3)%7==0)
                return ((countgiorni()-3)/7+1);
            else
                return ((countgiorni()-3)/7+2);
        }
        
    case(6):
        if(countgiorni()<3) return 1;
        else {
            if((countgiorni()-2)%7==0)
                return ((countgiorni()-2)/7+1);
            else
                return ((countgiorni()-2)/7+2);
        }
        
    case(7):
        if(countgiorni()<2) return 1;
        else {
            if((countgiorni()-1)%7==0)
                return ((countgiorni()-1)/7+1);
            else
                return ((countgiorni()-1)/7+2);
        }
        
        }
    return 0;
}

int data::settimanamese() const
{
    data aux(*this);
    aux.cambiaGiorno(1);
    string firstday=aux.giornoSettimana();//primo giorno del mese
    int x=0;
    if (firstday=="Lunedi'") x=1;
    else if (firstday=="Martedi'") x=2;
    else if (firstday=="Mercoledi'") x=3;
    else if (firstday=="Giovedi'") x=4;
    else if (firstday=="Venerdi'") x=5;
    else if (firstday=="Sabato") x=6;
    else if (firstday=="Domenica") x=7;
    switch(x)
    {
    case(1):
        if (giorno<8) return 1;
        else{
            if(giorno%7==0)
                return (giorno/7);
            else{
                return (giorno/7+1);
                }
        }
        break;
    case(2):
        if(giorno<7) return 1;
        else{
            if((giorno-6)%7==0)
                return ((giorno-6)/7+1);
            else
                return ((giorno-6)/7+2);
        }
        break;
    case(3):
        if(giorno<6) return 1;
        else{
            if((giorno-5)%7==0)
                return ((giorno-5)/7+1);
            else
                return ((giorno-5)/7+2);
        }
        break;
    case(4):
        if(giorno<5) return 1;
        else{
            if((giorno-4)%7==0)
                return ((giorno-4)/7+1);
            else
                return ((giorno-4)/7+2);
        }
        break;
    case(5):
        if(giorno<4) return 1;
        else{
            if((giorno-3)%7==0)
                return ((giorno-3)/7+1);
            else
                return ((giorno-3)/7+2);
        }
        break;
    case(6):
        if(giorno<3) return 1;
        else{
            if((giorno-2)%7==0)
                return ((giorno-2)/7+1);
            else
                return ((giorno-2)/7+2);
        }
        break;
    case(7):
        if(giorno<2) return 1;
        else{
            if((giorno-1)%7==0)
                return ((giorno-1)/7+1);
            else
                return ((giorno-1)/7+2);
        }
        break;
        }
    return 0;
}


//OVERRIDING


void data::SommaSec(int s){

   if(s<0) throw overflow_error();

    //Bisogna tener conto che potrei voler sommare più di 86400 secondi, quindi devo prima avanzare di tot giorni

    //NOTA BENE: Sec è privato in orario,quindi devo usare getSec per leggerlo. Per poi modificarlo ho dovuto
    //           aggiungere una funzione aggiornaSec() che possa cambiare sec
    if (s>=86400)
    {
        while (s>=86400)
        {
            avanzaUnGiorno(); //avanzo e tolgo quel giorno aggiunto
            s = s-86400;
        }
        //all'uscita s varrà i secondi rimasti, tolti i giorni, quindi sara' che s<86400
        if(getSecTot()+s>=86400) //potrei comunque sforare sommando
        {
            int aux=(getSecTot()+s)%86400;
            aggiornaSec(aux);
            avanzaUnGiorno(); //quindi avanzo ulteriormente
        }
        else
        {
            int aux = getSecTot()+s; //altrimenti sommo e basta
            aggiornaSec(aux);
        }
    }
    else //caso in cui i secondi da sommare inizialmente sono meno di un giorno
    {
        if(getSecTot()+s>=86400) //posso comunque sforare
        {
            int aux=(getSecTot()+s)%86400;
            aggiornaSec(aux);
            avanzaUnGiorno();
        }
        else
        {
            int aux = getSecTot()+s;
            aggiornaSec(aux);
        }

    }
}

void data::SommaMin(int m){

    if(m<0) throw overflow_error();

    //Stesso discorso se tento di sommare più di 1440 minuti (che fanno 1 giorno)

    if(m>=1440){
        while (m>=1440){
            avanzaUnGiorno();
            m = m-1440;
        }
        //all'uscitoa m varra' i minuti rimasti, tolti i giorni
        if(getSecTot()+m*60>=86400)
        {
            int aux=(getSecTot()+m*60)%86400;
            aggiornaSec(aux);
            avanzaUnGiorno();
        }
        else
        {
            int aux = getSecTot()+m*60;
            aggiornaSec(aux);
        }
    }
    else //caso in cui i minuti sono meno di 1440 quindi di un giorno
    {
        if(getSecTot()+m*60>=86400)
        {
            int aux=(getSecTot()+m*60)%86400;
            aggiornaSec(aux);
            avanzaUnGiorno();
        }
        else
        {
            int aux = getSecTot()+m*60;
            aggiornaSec(aux);
        }
    }


}
void data::SommaOra(int o){

    if (o<0) throw overflow_error();

    //Stesso discorso se tento di sommare piu' di 24 ore
    if (o>=24){
        while (o>=24){
            avanzaUnGiorno();
            o=o-24;
        }
        if(getSecTot()+o*3600>=86400)
        {
            int aux=(getSecTot()+o*3600)%86400;
            aggiornaSec(aux);
            avanzaUnGiorno();
        }
        else
        {
            int aux = getSecTot()+o*3600;
            aggiornaSec(aux);
        }
    }
    else //caso in cui le ore sono meno di 24
    {
        if(getSecTot()+o*3600>=86400)
        {
            int aux=(getSecTot()+o*3600)%86400;
            avanzaUnGiorno();
            aggiornaSec(aux);
        }
        else
        {
            int aux = getSecTot()+o*3600;
            aggiornaSec(aux);
        }
    }

}

void data::TogliSec(int s){

    if(s<0) throw overflow_error();
    if(s==0) return;

    //Bisogna tener conto se si tolgono piu' di 86400 secondi, se cosi' fosse bisogna ciclare indietroUnGiorno()
    //fino a che non finisci i giorni da togliere
    if(s>=86400)//s è maggior della grandezza di un giorno/i
    {
        while(s>=86400)
        {
            indietroUnGiorno();
            s=s-86400;
        }
        if(getSecTot()-s<0)//caso di sforamento giorno attuale se s maggiore del campo sec del giorno attuale
        {
            indietroUnGiorno();
            s=s-getSecTot();
            aggiornaSec(86400-s);
        }
        else
        {
            aggiornaSec(getSecTot()-s);
        }
    }
    else //caso in cui s<86400
    {
        if(getSecTot()-s<0)//caso di sforamento giorno attuale se s maggiore del campo sec del giorno attuale
        {
            indietroUnGiorno();
            s=s-getSecTot();
            aggiornaSec(86400-s);
        }
        else
        {
            aggiornaSec(getSecTot()-s);
        }
    }
}
void data::TogliMin(int m){

    if(m<0) throw overflow_error();
    if(m==0) return;

    if(m>=1440)
    {
        while(m>=1440)
        {
            indietroUnGiorno();
            m=m-1440;
        }
        if(getSecTot()-m*60<0)
        {
            indietroUnGiorno();
            int aux=m*60-getSecTot();
            aggiornaSec(86400-aux);
        }
        else
        {
            aggiornaSec(getSecTot()-m*60);
        }
    }
    else
    {
        if(getSecTot()-m*60<0)
        {
            indietroUnGiorno();
            int aux=m*60-getSecTot();
            aggiornaSec(86400-aux);

        }
        else
        {
            aggiornaSec(getSecTot()-m*60);
        }
    }

}
void data::TogliOra(int o){

    if (o<0) throw overflow_error();
    if(o==0) return;

    if(o>=24)
    {
        while(o>=24)
        {
            indietroUnGiorno();
            o=o-24;
        }
        if(getSecTot()-o*3600<0)//caso di sforamento giorno attuale se s maggiore del campo sec del giorno attuale
        {
            indietroUnGiorno();
            int aux=o*3600-getSecTot();
           aggiornaSec(86400-aux);
        }
        else
        {
            aggiornaSec(getSecTot()-o*3600);
        }
    }
    else
    {
        if(getSecTot()-o*3600<0)//caso di sforamento giorno attuale se s maggiore del campo sec del giorno attuale
        {
            indietroUnGiorno();
            int aux=o*3600-getSecTot();
            aggiornaSec(86400-aux);

        }
        else
        {
            aggiornaSec(getSecTot()-o*3600);
        }
    }

}

data* data::SommaOrario(const orario& o1) const
{
    data* d1=new data(*this);
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

data* data::SubOrario(const orario& o1) const
{
    if (o1.getSecTot()==0) return new data(*this);
    data* d1=new data(*this);
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

void data::avanzaTotGiorni(int n){

    if(n<0) throw overflow_error();
    if (n==0) return;

    //caso "base" in cui devo avanzare di meno giorni di quelli che mancano alla fine del mese corrente
    if ((giorniMese(mese)-giorno)>=n){
        giorno = giorno + n;
    }
    //se invece devo avanzare oltre, potrei dover cambiare anche più di un mese
    else {
        int aux = giorniMese(mese)-giorno; //giorni per cambiare mese(aux sicuramente minore stretto di n)
        n = n -aux; //li tolgo a n, come se fossi all'ultimo giorno del mese (qui n è sicuramente >0)
        if(mese==12){
            mese=1; //avanzo
            anno++;
        }
        else {
            mese++;
        }
        while (n){
            if(n<=giorniMese(mese))
            {
                giorno = n; //non ho più mesi da andare avanti
                n =0; //finiti giorni da procedere (sentinella while)
            }
            else//caso in cui devo andare avanti
            {
                n = n - giorniMese(mese); //tolgo i giorni del mese che devo saltare
                if(mese==12){//avanzo al mese dopo
                    mese=1;
                    anno++;
                }
                else {
                    mese++;
                }
            }
        }
    }
}
void data::indietroTotGiorni(int n){

    if(n<0) throw overflow_error();

    if(n==0) return;

    if(n==giorno)
    {
        if(mese==1)
        {
            anno--;
            mese=12;
            giorno=giorniMese(mese);
        }
        else
        {
            mese--;
            giorno=giorniMese(mese);

        }
    }
    //caso base in cui non torno indietro di neanche un mese
    else if(n<giorno){
        giorno = giorno-n;
    }
    //se invece devo andare indietro di 1 o più mesi
    else
    {
        n = n-giorno; //tolgo i giorni del mese in cui sono
        if (mese==1){
            anno--;
            mese=12;
        }
        else{
            mese--;
        }
        while (n){
            if(n<=giorniMese(mese))
            {
                giorno = giorniMese(mese)-n;
                n =0;
            }
            else
            {
                n = n - giorniMese(mese);
                if (mese==1){
                    anno--;
                    mese=12;
                }
                else{
                    mese--;
                }
            }
        }
    }
}
bool data::operator>(const data& d1) const
{
    if(d1.anno>anno)
    {
        return false;
    }
    else
    {
        if(d1.anno==anno)
        {
            if(d1.mese>mese)
                {
                    return false;
                }
            else
            {
                if(mese==d1.mese)
                {
                    if(d1.giorno>giorno)
                        {
                            return false;
                        }
                    else
                        {
                            if(d1.giorno==giorno)
                            {
                                if(getSecTot()>d1.getSecTot())
                                    return true;
                                else
                                    return false;
                            }
                            else
                            {
                                return true;
                            }
                        }
                }
                else
                    return true;
            }
        }
        else
        {
            return true;
        }
    }
    return 0;
}

int data::durata(const data& d1) const
{
int year; //variabile di differenza anni
int day=0;//giorni di differenza
if(*this>d1)// caso in cui passo una data piu'piccola
{
year=anno-d1.anno;
if(year>1)// ci sono piu anni di differenza
{
for(int i=0;i<year-1;++i)
{
if(bisestile(year))
day+=366;
else
day+=365;
}
int annocorrente;
int ultimoanno;
if(bisestile(d1.anno))//giorni che mancano alla fine dell'anno della data passata
ultimoanno=366-countgiorni();
else
ultimoanno=365-countgiorni();
annocorrente=countgiorni();//giorni passati dall'inizio dell'anno corrente

day=day+annocorrente+ultimoanno;
}
else if(year==1)//c'e' solo un anno di differenza
{
int annocorrente;
int ultimoanno;
if(bisestile(d1.anno))//giorni per arrivare a fine anno data passata
ultimoanno=366-d1.countgiorni();
else
ultimoanno=365-d1.countgiorni();
annocorrente=countgiorni();// giorni passati da inizio anno data corrente

day=day+annocorrente+ultimoanno;
}
else//siamo nello stesso anno, si fa una differenza
{
day=countgiorni()-d1.countgiorni();
}
}
else //caso in cui la data passata e' piu' grande
{
year=d1.anno-anno;

if(year>1)//le date sono in anni diversi
{
for(int i=0;i<year-1;++i)
{
if(bisestile(year))
day+=366;
else
day+=365;
}
int annocorrente;
int ultimoanno;
if(bisestile(anno))
annocorrente=366-countgiorni();
else
annocorrente=365-countgiorni();
ultimoanno=d1.countgiorni();

day=day+annocorrente+ultimoanno;
}
else if(year==1)
{
int annocorrente;
int ultimoanno;
if(bisestile(anno))
annocorrente=366-countgiorni();
else
annocorrente=365-countgiorni();
ultimoanno=d1.countgiorni();

day=day+annocorrente+ultimoanno;
}
else
{
day=d1.countgiorni()-countgiorni();
}
}
return day;
}

void data::cambiaGiorno(int g){

    if(g<1|| g>giorniMese(mese))
        throw overflow_error();
    else
        giorno=g;
}

void data::cambiaMese(int m){

    if(m<1||m>12)
        throw overflow_error();
    else
        mese=m;

}
void data::cambiaAnno(int a){

    if(a<=0)
        throw overflow_error();
    else
        anno=a;

}
void data::cambiaEmis(bool e){
    emisfero = e;
}

