#include "controller.h"
#include "model.h"
#include <QString>
#include <QTime>
#include <QDate>
#include <QStringList>

Controller::Controller(Model* m): model(m) {}

Controller::~Controller(){}

bool Controller::checkOrario() const {
    return (model->checking());
}

void Controller::OnClearButtonClicked() const
{
  model->clear();
}
bool Controller::OnSommaButtonClicked(QString n) const
{   
    QStringList list = n.split(":");
    int ore = list.operator[](0).toInt();
    int min = list.operator[](1).toInt();
    int sec = list.operator[](2).toInt();
    if(ore<0 || min<0 || sec<0) return false;

    int giorni,mesi, anni =0;
    if(list.size()>3)
    {
         giorni = list.operator[](3).toInt();
         mesi = list.operator[](4).toInt();
         anni = list.operator[](5).toInt();
        if(giorni<0 || mesi<0|| anni<0) return false;
    }
    //Se non ho mai ritornato false vuol dire che posso passare i dati al model
    model->Somma(ore,min,sec,giorni,mesi,anni);
    return true;

}
bool Controller::OnSubButtonClicked(QString n) const
{
    QStringList list = n.split(":");
    int ore = list.operator[](0).toInt();
    int min = list.operator[](1).toInt();
    int sec = list.operator[](2).toInt();
    if(ore<0 || min<0 || sec<0) return false;

    int giorni,mesi,anni=0;
    if(list.size()>3)
    {
         giorni = list.operator[](3).toInt();
         mesi = list.operator[](4).toInt();
         anni = list.operator[](5).toInt();
        if(giorni<0 || mesi<0|| anni<0) return false;
    }
    //Non ho mai ritornato false quindi chiamo operazione
    model->Sub(ore,min,sec,giorni,mesi,anni);
    return true;
}
bool Controller::OnOrarioClicked(QString s) const
{
    bool aux = true;
    try
    {
        QStringList list = s.split(":");
        int ore = list.operator[](0).toInt();
        int min = list.operator[](1).toInt();
        int sec = list.operator[](2).toInt();
        model->CreaOrario(ore,min,sec);
    }
    catch(overflow_error)
    {
        aux = false;
    }
    return aux;
}

bool Controller::OnDataClicked(QString s) const
{
    bool aux = true;
    try
    {
        QStringList list = s.split(":");
        int ore = list.operator[](0).toInt();
        int min = list.operator[](1).toInt();
        int sec = list.operator[](2).toInt();
        int g = list.operator[](3).toInt();
        int m = list.operator[](4).toInt();
        int a = list.operator[](5).toInt();
        bool e;
        if(list.operator[](6)=="Boreale" || list.operator[](6)=="boreale" )
            e=1;
        else if(list.operator[](6)=="Australe" || list.operator[](6)=="Australe")
                e=1;
        model->CreaData(g,m,a,e,ore,min,sec);
    }
    catch(overflow_error)
    {
        aux = false;
    }
    return aux;
}
bool Controller::OnFusoClicked(QString s) const
{
    bool aux = true;
    try
    {
        QStringList list = s.split(":");
        int ore = list.operator[](0).toInt();
        int min = list.operator[](1).toInt();
        int sec = list.operator[](2).toInt();
        int g = list.operator[](3).toInt();
        int m = list.operator[](4).toInt();
        int a = list.operator[](5).toInt();
        bool e;
        if(list.operator[](6)=="Boreale" || list.operator[](6)=="boreale" )
            e=1;
        else if(list.operator[](6)=="Australe" || list.operator[](6)=="Australe")
                e=1;
        int fascia =list.operator[](7).toInt();
        model->CreaFuso(g,m,a,e,ore,min,sec,fascia);
    }
    catch(overflow_error)
    {
        aux = false;
    }
    return aux;
}
bool Controller::OnLunaClicked(QString s) const
{
    bool aux = true;
    try
    {
        QStringList list = s.split(":");
        int ore = list.operator[](0).toInt();
        int min = list.operator[](1).toInt();
        int sec = list.operator[](2).toInt();
        int g = list.operator[](3).toInt();
        int m = list.operator[](4).toInt();
        int a = list.operator[](5).toInt();
        bool e;
        if(list.operator[](6)=="Boreale" || list.operator[](6)=="boreale" )
            e=1;
        else if(list.operator[](6)=="Australe" || list.operator[](6)=="Australe")
                e=1;

        model->CreaLuna(g,m,a,e,ore,min,sec);
    }
    catch(overflow_error)
    {
        aux = false;
    }
    return aux;
}

QTime Controller::getTime(bool formato) const {
    int ore;
    if(formato==true)
        ore = model->Ore();
    else
        ore= model->cambiaformato();
    int min = model->Min();
    int sec = model->Sec();
    QTime t(ore,min,sec);
    return t;
}
QDate Controller::getDate()const{
    int giorno = model->Giorno();
    int mese = model->Mese();
    int anno = model->Anno();
    QDate d(anno,mese,giorno);
    return d;
}
bool Controller::getEmis() const
{
    return model->Emisfero();
}
QString Controller::checkFase()const{
    return  QString::fromStdString(model->Fase());
}
int Controller::getFusoZona() const
{
    return model->getZona();
}
char Controller::getFusoFascia() const
{
    return model->getFascia();
}

QString Controller::OnStagioneClicked() const
{
    return QString::fromStdString(model->Stagione());

}
QString Controller::OnGiornoSetClicked() const
{

    return QString::fromStdString(model->GiornoSettimana());

}
int Controller::onSetMeseclicked() const
{
    return model->settimanaMese();
}
int Controller::onSetAnnoclicked() const
{
    return model->settimanaAnno();
}
int Controller::OnDurataClicked(QString s) const
{
    QStringList list = s.split(":");
    int giorno = list.operator[](0).toInt();
    int mese = list.operator[](1).toInt();
    int anno = list.operator[](2).toInt();

    //Se non ho passato un valore o tutti ritorno 0
    if(giorno<=0 || mese<=0 || anno<=0) return 0;

    //altrimenti ritorno giusto
    return model->getDurata(giorno,mese,anno);
}

int Controller::ProssimaPiena() const{

    return model->ProsPiena();

}
int Controller::ProssimaNuova() const{

    return model->ProsNuova();

}
int Controller::UltimaPiena() const{

    return model->UltimPiena();

}
int Controller::UltimaNuova() const{

    return model->UltimNuova();

}
int Controller::OnOreStudioClicked(QString s) const
{
    QStringList list = s.split(":");
    int giorno = list.operator[](0).toInt();
    int mese = list.operator[](1).toInt();
    int anno = list.operator[](2).toInt();
    int ore = list.operator[](3).toInt();
    //Se non ho passato un valore o tutti ritorno 0
    if(giorno<=0 || mese<=0 || anno<=0) return 0;

    //altrimenti ritorno giusto
    return model->getOreStudio(giorno,mese,anno,ore);
}

int Controller::DimmiFuso(QString s)const{
    return model->DimFuso(s[0].toLatin1());
}
int Controller::fuDiff(QString s) const{
    return model->fDiff(s.toInt());

}
bool Controller::sumFuso(QString s) const
{
    if(s.toInt()<0 || s.toInt()>25 )
        return false;
    else
    {
        model->sommaFuso(s.toInt());
        return true;
    }

}

bool Controller::subFuso(QString s) const
{
    if(s.toInt()<0 || s.toInt()>25 )
        return false;
    else
    {
        model->sottraiFuso(s.toInt());
        return true;
    }
}
