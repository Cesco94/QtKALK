#include "view.h"
#include "controller.h"
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>


View::View(QWidget *parent, QString name): QWidget(parent), appName(name),time(), date(), timerOra(), timerData(), timerFuso(), timerLuna()
{
  this->setWindowTitle(appName);
  //this->setFixedSize(800,800);

  //LAYOUT CONTENITORE GRIGLIA
  layoutG = new QGridLayout();

  //BOTTONI TIPI
  Orario = new QToolButton(this);
  QPixmap p1(":/icone/clock.png");
  Orario->setIcon(QIcon(p1));
  Orario->setIconSize(QSize(100,100));
  layoutG->addWidget(Orario,0,0);

  Data = new QToolButton(this);
  QPixmap p2(":/icone/cal2.png");
  Data->setIcon(QIcon(p2));
  Data->setIconSize(QSize(100,100));
  layoutG->addWidget(Data,0,1);

  Fuso = new QToolButton(this);
  QPixmap p3(":/icone/plane.png");
  Fuso->setIcon(QIcon(p3));
  Fuso->setIconSize(QSize(100,100));
  layoutG->addWidget(Fuso,0,2);

  Luna = new QToolButton(this);
  QPixmap p4(":/icone/moon.png");
  Luna->setIcon(QIcon(p4));
  Luna->setIconSize(QSize(100,100));
  layoutG->addWidget(Luna,0,3);

  //BOTTONI Stato oggetti + Clear


  clear = new QPushButton("RESET", this);
  clear->setFixedSize(50,50);
  clear->setFont(QFont( "Arial", 8, QFont::Bold));
  clear->setDisabled(true);
  layoutG->addWidget(clear,0,4,Qt::AlignTop);

  time = new QLabel(this);
  timerOra = new QTimer(this);
  time->setFixedSize(150,50);
  time->setStyleSheet(QString("border: 2px solid black"));
  time->setAlignment(Qt::AlignCenter);
  time->setFont(QFont( "Arial", 20, QFont::Bold));
  time->hide();
  layoutG->addWidget(time,2,0);

  date =new QLabel(this);
  timerData = new QTimer(this);
  date->setFixedSize(150,50);
  date->setStyleSheet(QString("border: 2px solid black"));
  date->setAlignment(Qt::AlignCenter);
  date->setFont(QFont( "Arial", 20, QFont::Bold));
  date->hide();
  layoutG->addWidget(date,2,1);

  moon = new QLabel(this);
  timerLuna = new QTimer(this);
  moon->hide();
  layoutG->addWidget(moon,3,3);
  moon2 = new QLabel(this);
  moon2->setFixedSize(150,50);
  moon2->setStyleSheet(QString("border: 2px solid black"));
  moon2->setAlignment(Qt::AlignCenter);
  moon2->setFont(QFont( "Arial", 15, QFont::Bold));
  moon2->hide();
  layoutG->addWidget(moon2,2,3);

  fuso = new QLabel(this);
  timerFuso= new QTimer(this);
  fuso->setFixedSize(150,50);
  fuso->setStyleSheet(QString("border: 2px solid black"));
  fuso->setAlignment(Qt::AlignCenter);
  fuso->setFont(QFont( "Arial", 15, QFont::Bold));
  fuso->hide();
  layoutG->addWidget(fuso,2,2);


  //BOTTONI OPERAZIONI

  //layout Bottoni Orario
  QGridLayout* s=new QGridLayout();
    //somma
    somma = new QToolButton(this);
    QPixmap p5(":/icone/plus.png");
    somma->setIcon(QIcon(p5));
    somma->setIconSize(QSize(25,25));
    somma->setFixedSize(50,50);
    somma->setText("Somma");
    somma->setFont(QFont( "Arial", 7, QFont::Bold));
    somma->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    somma->setDisabled(true);
    s->addWidget(somma,0,0);

    //SUB
    sub = new QToolButton(this);
    QPixmap p6(":/icone/minus.png");
    sub->setIcon(QIcon(p6));
    sub->setIconSize(QSize(25,25));
    sub->setFixedSize(50,50);
    sub->setText("Sottrazione");
    sub->setFont(QFont( "Arial", 6.5, QFont::Bold));
    sub->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    sub->setDisabled(true);
    s->addWidget(sub,0,1);

    //formato
    formato=new QToolButton(this);
    QPixmap f(":/icone/formato.png");
    formato->setIcon(QIcon(f));
    formato->setIconSize(QSize(25,25));
    formato->setFixedSize(50,50);
    formato->setText("Formato");
    formato->setFont(QFont( "Arial", 7, QFont::Bold));
    formato->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    formato->setDisabled(true);;
    s->addWidget(formato,1,0);

  //Layout bottoni Data
    QGridLayout* s2=new QGridLayout();

    giornoSet=new QToolButton(this);
    QPixmap f2(":/icone/giornoset.png");
    giornoSet->setIcon(QIcon(f2));
    giornoSet->setIconSize(QSize(25,25));
    giornoSet->setFixedSize(50,50);
    giornoSet->setText("Giorno\nSettimana");
    giornoSet->setFont(QFont( "Arial", 5.5, QFont::Bold));
    giornoSet->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    giornoSet->setDisabled(true);;
    s2->addWidget(giornoSet,0,0);

    stagione=new QToolButton(this);
    QPixmap f3(":/icone/stagione.jpg");
    stagione->setIcon(QIcon(f3));
    stagione->setIconSize(QSize(25,25));
    stagione->setFixedSize(50,50);
    stagione->setText("Stagione");
    stagione->setFont(QFont( "Arial", 7, QFont::Bold));
    stagione->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    stagione->setDisabled(true);;
    s2->addWidget(stagione,0,1);

    setMese=new QToolButton(this);
    QPixmap r(":/icone/setmese2.png");
    setMese->setIcon(QIcon(r));
    setMese->setIconSize(QSize(25,25));
    setMese->setFixedSize(50,50);
    setMese->setText("Settimana\nMese");
    setMese->setFont(QFont( "Arial", 5.5, QFont::Bold));
    setMese->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setMese->setDisabled(true);;
    s2->addWidget(setMese,1,0);

    setAnno=new QToolButton(this);
    QPixmap q(":/icone/cal.png");
    setAnno->setIcon(QIcon(q));
    setAnno->setIconSize(QSize(25,25));
    setAnno->setFixedSize(50,50);
    setAnno->setText("Settimana\nAnno");
    setAnno->setFont(QFont( "Arial", 5.5, QFont::Bold));
    setAnno->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setAnno->setDisabled(true);;
    s2->addWidget(setAnno,1,1);

    durata=new QToolButton(this);
    QPixmap w(":/icone/data2.png");
    durata->setIcon(QIcon(w));
    durata->setIconSize(QSize(25,25));
    durata->setFixedSize(50,50);
    durata->setText("Durata");
    durata->setFont(QFont( "Arial", 7, QFont::Bold));
    durata->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    durata->setDisabled(true);;
    s2->addWidget(durata,2,0);

    oreStudio=new QToolButton(this);
    QPixmap w2(":/icone/libro.png");
    oreStudio->setIcon(QIcon(w2));
    oreStudio->setIconSize(QSize(25,25));
    oreStudio->setFixedSize(50,50);
    oreStudio->setText("Ore Studio");
    oreStudio->setFont(QFont( "Arial", 6, QFont::Bold));
    oreStudio->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    oreStudio->setDisabled(true);;
    s2->addWidget(oreStudio,2,1);

    //Layout bottoni Luna
      QGridLayout* s3=new QGridLayout();

      prossimaNuova=new QToolButton(this);
      QPixmap z(":/icone/prossimanuova.png");
      prossimaNuova->setIcon(QIcon(z));
      prossimaNuova->setIconSize(QSize(25,25));
      prossimaNuova->setFixedSize(50,50);
      prossimaNuova->setText("Prossima");
      prossimaNuova->setFont(QFont( "Arial", 7, QFont::Bold));
      prossimaNuova->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      prossimaNuova->setDisabled(true);;
      s3->addWidget(prossimaNuova,0,0);

      ultimaNuova=new QToolButton(this);
      QPixmap z1(":/icone/prossimanuova");
      ultimaNuova->setIcon(QIcon(z1));
      ultimaNuova->setIconSize(QSize(25,25));
      ultimaNuova->setFixedSize(50,50);
      ultimaNuova->setText("Ultima");
      ultimaNuova->setFont(QFont( "Arial", 7, QFont::Bold));
      ultimaNuova->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      ultimaNuova->setDisabled(true);;
      s3->addWidget(ultimaNuova,0,1);

      prossimaPiena=new QToolButton(this);
      QPixmap z2(":/icone/prossimapiena.png");
      prossimaPiena->setIcon(QIcon(z2));
      prossimaPiena->setIconSize(QSize(25,25));
      prossimaPiena->setFixedSize(50,50);
      prossimaPiena->setText("Prossima");
      prossimaPiena->setFont(QFont( "Arial", 7, QFont::Bold));
      prossimaPiena->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      prossimaPiena->setDisabled(true);;
      s3->addWidget(prossimaPiena,1,0);

      ultimaPiena=new QToolButton(this);
      QPixmap z3(":/icone/prossimapiena.png");
      ultimaPiena->setIcon(QIcon(z3));
      ultimaPiena->setIconSize(QSize(25,25));
      ultimaPiena->setFixedSize(50,50);
      ultimaPiena->setText("Ultima");
      ultimaPiena->setFont(QFont( "Arial", 7, QFont::Bold));
      ultimaPiena->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      ultimaPiena->setDisabled(true);;
      s3->addWidget(ultimaPiena,1,1);

      //Layout bottoni fuso
        QGridLayout* s4=new QGridLayout();

        dimmiFuso=new QToolButton(this);
        QPixmap a(":/icone/dimmifuso.png");
        dimmiFuso->setIcon(QIcon(a));
        dimmiFuso->setIconSize(QSize(25,25));
        dimmiFuso->setFixedSize(50,50);
        dimmiFuso->setText("Dimmi\nFuso");
        dimmiFuso->setFont(QFont( "Arial", 5.5, QFont::Bold));
        dimmiFuso->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        dimmiFuso->setDisabled(true);;
        s4->addWidget(dimmiFuso,0,0);

        fusoDiff=new QToolButton(this);
        QPixmap a1(":/icone/fusodiff.png");
        fusoDiff->setIcon(QIcon(a1));
        fusoDiff->setIconSize(QSize(25,25));
        fusoDiff->setFixedSize(50,50);
        fusoDiff->setText("Differenza\nFuso");
        fusoDiff->setFont(QFont( "Arial", 5.5, QFont::Bold));
        fusoDiff->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        fusoDiff->setDisabled(true);;
        s4->addWidget(fusoDiff,0,1);

        sommaFuso=new QToolButton(this);
        QPixmap a2(":/icone/opfuso.png");
        sommaFuso->setIcon(QIcon(a2));
        sommaFuso->setIconSize(QSize(25,25));
        sommaFuso->setFixedSize(50,50);
        sommaFuso->setText("Somma\nFuso");
        sommaFuso->setFont(QFont( "Arial", 5.5, QFont::Bold));
        sommaFuso->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        sommaFuso->setDisabled(true);;
        s4->addWidget(sommaFuso,1,1);

        togliFuso=new QToolButton(this);
        QPixmap a3(":/icone/opfuso.png");
        togliFuso->setIcon(QIcon(a3));
        togliFuso->setIconSize(QSize(25,25));
        togliFuso->setFixedSize(50,50);
        togliFuso->setText("Sottrai\nFuso");
        togliFuso->setFont(QFont( "Arial", 5.5, QFont::Bold));
        togliFuso->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        togliFuso->setDisabled(true);;
        s4->addWidget(togliFuso,1,0);



  //CONNECTs

  connect(clear, SIGNAL(clicked(bool)), this, SLOT(ClearButtonClicked()));


  connect(timerOra, SIGNAL(timeout()), this, SLOT(showTime()));
  connect(timerData, SIGNAL(timeout()), this, SLOT(showDate()));
  connect(timerLuna, SIGNAL(timeout()),this,SLOT(showMoon()));
  connect(timerFuso, SIGNAL(timeout()), this, SLOT(showFuso()));

  connect(Orario,SIGNAL(clicked(bool)),this, SLOT(OrarioClicked()));
  connect(Data,SIGNAL(clicked(bool)),this, SLOT(DataClicked()));
  connect(Fuso,SIGNAL(clicked(bool)),this, SLOT(FusoClicked()));
  connect(Luna,SIGNAL(clicked(bool)),this, SLOT(LunaClicked()));

  connect(somma,SIGNAL(clicked(bool)),this,SLOT(SommaButtonClicked()));
  connect(sub,SIGNAL(clicked(bool)),this,SLOT(SubButtonClicked()));
  connect(formato,SIGNAL(clicked(bool)),this,SLOT(formatoclicked()));

  connect(giornoSet,SIGNAL(clicked(bool)),this, SLOT(GiornoSetClicked()));
  connect(stagione,SIGNAL(clicked(bool)),this, SLOT(StagioneClicked()));
  connect(setMese,SIGNAL(clicked(bool)),this,SLOT(setMclicked()));
  connect(setAnno,SIGNAL(clicked(bool)),this,SLOT(setAclicked()));
  connect(durata,SIGNAL(clicked(bool)),this,SLOT(durataClicked()));
  connect(oreStudio,SIGNAL(clicked(bool)),this,SLOT(oreStudioclicked()));

  connect(prossimaNuova, SIGNAL(clicked(bool)),this,SLOT(prossimaNuovaClicked()));
  connect(ultimaNuova, SIGNAL(clicked(bool)),this,SLOT(ultimaNuovaClicked()));
  connect(prossimaPiena, SIGNAL(clicked(bool)),this,SLOT(prossimaPienaClicked()));
  connect(ultimaPiena, SIGNAL(clicked(bool)),this,SLOT(ultimaPienaClicked()));

  connect(dimmiFuso,SIGNAL(clicked(bool)),this,SLOT(dimmiFusoClicked()));
  connect(fusoDiff,SIGNAL(clicked(bool)),this,SLOT(fusoDiffClicked()));
  connect(sommaFuso,SIGNAL(clicked(bool)),this,SLOT(sommaFusoClicked()));
  connect(togliFuso,SIGNAL(clicked(bool)),this,SLOT(togliFusoClicked()));



  //LAYOUT

  layoutG->setColumnMinimumWidth(0,150);
  layoutG->setColumnMinimumWidth(1,150);
  layoutG->setColumnMinimumWidth(2,150);
  layoutG->setColumnMinimumWidth(3,150);

  //Layout orario
  layoutG->addLayout(s,1,0,Qt::AlignTop);
  //Layout data
  layoutG->addLayout(s2,1,1,Qt::AlignLeft);
  //Layout Luna
  layoutG->addLayout(s3,1,3,Qt::AlignTop);
  //Layout fuso
  layoutG->addLayout(s4,1,2,Qt::AlignTop);



  this->setLayout(layoutG);


}

View::~View() {}

void View::setController(Controller* c)
{
    controller = c;
}

//SLOTS
void View::ClearButtonClicked()
{
    if(!Orario->isEnabled())
    {
        this->OrarioClicked();
    }
    else if(!Data->isEnabled())
    {
        this->DataClicked();
    }
    else if(!Fuso->isEnabled())
    {
        this->FusoClicked();
    }
    else//Luna
    {
        this->LunaClicked();
    }

}
void View::formatoclicked()
{
    if(flagformato==true)
        flagformato=false;
    else if(flagformato==false)
            flagformato=true;
}
void View::setMclicked()
{
    int aux=controller->onSetMeseclicked();
    QMessageBox res;
    res.setWindowTitle("Settimana del mese corrente.");
    res.setText("La settimana corrente e' la numero: "+QString::number(aux));
    res.setFont(QFont( "times", 10, QFont::Bold));
    res.exec();

}
void View::setAclicked()
{
    int aux=controller->onSetAnnoclicked();
    QMessageBox res;
    res.setWindowTitle("Settimana dell'anno corrente.");
    res.setText("La settimana corrente e' la numero: "+QString::number(aux));
    res.setFont(QFont( "times", 10, QFont::Bold));
    res.exec();
}
void View::StagioneClicked()
{
    QString s = controller->OnStagioneClicked();
    bool e=controller->getEmis();
    QString emis;
    if(e==1)
        emis="Boreale";
    else
        emis="Australe";

    QMessageBox popup;
    popup.setWindowTitle("Stagione.");
    popup.setText("Stagione in corso nell'emisfero "+emis+" : "+s+".");
    popup.setFont(QFont( "times", 10, QFont::Bold));
    popup.exec();


}
void View::GiornoSetClicked()
{
    QString s=controller->OnGiornoSetClicked();
    QMessageBox popup;
    popup.setWindowTitle("Giorno della settimana.");
    popup.setText("Oggi e' "+s+".");
    popup.setFont(QFont( "times", 10, QFont::Bold));
    popup.exec();

}
void View::showTime()
{

    if(controller->checkOrario())
         {
             QTime t = controller->getTime(flagformato);
             QString text = t.toString("hh:mm:ss");
             time->setText(text);
         }

}
void View::showDate()
{
    if(controller->checkOrario())
    {
        QDate t = controller->getDate();
        QString text = t.toString("dd/MM/yyyy");
        date->setText(text);
    }
}
void View::showMoon()
{
    if(controller->checkOrario())
    {
        QString s = controller->checkFase();
        if (s=="Piena")
        {
            QPixmap p6(":/icone/piena.jpg");
            moon->setPixmap(p6.scaled(150,150,Qt::KeepAspectRatio));
            moon2->setText("Fase\n"+s);

        }
        else if(s=="Novilunio")
        {
            QPixmap p7(":/icone/nuova.jpg");
            moon->setPixmap(p7.scaled(150,150,Qt::KeepAspectRatio));
            moon2->setText("Fase\n"+s);
        }
        else if(s==QString("Crescente"))
        {
            QPixmap p8(":/icone/crescente.jpg");
            moon->setPixmap(p8.scaled(150,150,Qt::KeepAspectRatio));
            moon->setPixmap(p8.scaled(150,150,Qt::KeepAspectRatio));
            moon2->setText("Fase\n"+s);

        }
        else if(s=="Calante")
        {
            QPixmap p9(":/icone/calante.jpg");
            moon->setPixmap(p9.scaled(150,150,Qt::KeepAspectRatio));
            moon2->setText("Fase\n"+s);

        }



    }

}

void View::showFuso(){

    if(controller->checkOrario())
      {
          int z= controller->getFusoZona();
          char f= controller->getFusoFascia();
          QString t1 = QString::number(z);
          QChar r(f);
          QString t2(r);
          fuso->setText("Fascia "+t2+"\n"+"TimeZone "+t1);
      }

}

void View::OrarioClicked()
{


    //Dialog per istanziare
    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Settaggio di un orario."));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Ore: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Minuti: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Secondi: ");
    form.addRow(label3, lineEdit3);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));


    QString s;
    bool sentinella=true;

    if (dialog->exec() == QDialog::Accepted)
    {

        s = s+lineEdit1->text();
        s = s+":"+lineEdit2->text();
        s = s+":"+lineEdit3->text();

        if(timerOra->isActive()) timerOra->stop();
        if(timerData->isActive()) timerData->stop();
        if(timerLuna->isActive()) timerLuna->stop();
        if(timerFuso->isActive()) timerFuso->stop();

        sentinella = controller->OnOrarioClicked(s);
        if (sentinella)
        {
            //TIPO DA DISABILITARE, se si vuole resettare si preme Clear
            Orario->setDisabled(true);
            Data->setEnabled(true);
            Luna->setEnabled(true);
            Fuso->setEnabled(true);

            //BOTTONI DA DISABILITARE
            giornoSet->setDisabled(true);
            stagione->setDisabled(true);
            setMese->setDisabled(true);
            setAnno->setDisabled(true);
            durata->setDisabled(true);
            prossimaNuova->setDisabled(true);
            prossimaPiena->setDisabled(true);
            ultimaNuova->setDisabled(true);
            ultimaPiena->setDisabled(true);
            dimmiFuso->setDisabled(true);
            sommaFuso->setDisabled(true);
            fusoDiff->setDisabled(true);
            togliFuso->setDisabled(true);

            //OPERAZIONI DA ABILITARE
            somma->setEnabled(true);
            sub->setEnabled(true);
            formato->setEnabled(true);
            clear->setEnabled(true);


            if(!(timerOra->isActive()))timerOra->start(100);

            if (date->isVisible()) date->hide();
            if (moon->isVisible()) moon->hide();
            if (moon2->isVisible()) moon2->hide();
            if (fuso->isVisible()) fuso->hide();
            if (time->isHidden()) time->show();
        }
        else
        {
            QMessageBox error;
            error.setWindowTitle("Errore costruzione orario.");
            error.setText("ERRORE:\nRispettare formato corretto.\n[Ore 0-23]\n[Minuti 0-59]\n[Secondi 0-59]");
            error.setFont(QFont( "Arial", 10, QFont::Bold));
            error.exec();

        }
    }



}
void View::DataClicked()
{

    //Dialog per istanziare
    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Settaggio di una data."));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Ore: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Minuti: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Secondi: ");
    form.addRow(label3, lineEdit3);
    QLineEdit *lineEdit4 = new QLineEdit(dialog);
    QString label4 = QString("Giorno*: ");
    form.addRow(label4, lineEdit4);
    QLineEdit *lineEdit5 = new QLineEdit(dialog);
    QString label5 = QString("Mese*: ");
    form.addRow(label5, lineEdit5);
    QLineEdit *lineEdit6 = new QLineEdit(dialog);
    QString label6 = QString("Anno*: ");
    form.addRow(label6, lineEdit6);
    QLineEdit *lineEdit7 = new QLineEdit(dialog);
    QString label7 = QString("Emisfero(1=Boreale;0=Australe): ");
    form.addRow(label7, lineEdit7);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    form.addRow(new QLabel("\n*Campo obbligatorio."));


    QString s;
    bool sentinella=true;

    if (dialog->exec() == QDialog::Accepted)
    {

        s = s+lineEdit1->text();
        s = s+":"+lineEdit2->text();
        s = s+":"+lineEdit3->text();
        s = s+":"+lineEdit4->text();
        s = s+":"+lineEdit5->text();
        s = s+":"+lineEdit6->text();
        s = s+":"+lineEdit7->text();
        if(timerData->isActive()) timerData->stop(); //Per evitare un check del timer durante la distruzione del vecchio oggetto
        if(timerOra->isActive()) timerOra->stop();
        if(timerLuna->isActive()) timerLuna->stop();
        if(timerFuso->isActive()) timerFuso->stop();


        sentinella = controller->OnDataClicked(s);
        if (sentinella)
        {
            //TIPO DA DISABILITARE, se si vuole resettare si preme Clear
            Data->setDisabled(true);
            Orario->setEnabled(true);
            Luna->setEnabled(true);
            Fuso->setEnabled(true);

            //Operazioni da disabilitare
            prossimaNuova->setDisabled(true);
            prossimaPiena->setDisabled(true);
            ultimaNuova->setDisabled(true);
            ultimaPiena->setDisabled(true);
            dimmiFuso->setDisabled(true);
            sommaFuso->setDisabled(true);
            fusoDiff->setDisabled(true);
            togliFuso->setDisabled(true);

            //OPERAZIONI DA ABILITARE
            somma->setEnabled(true);
            sub->setEnabled(true);
            formato->setEnabled(true);
            giornoSet->setEnabled(true);
            stagione->setEnabled(true);
            setMese->setEnabled(true);
            setAnno->setEnabled(true);
            durata->setEnabled(true);
            clear->setEnabled(true);
            oreStudio->setEnabled(true);


            if(!(timerOra->isActive()))timerOra->start(100);
            if(!(timerData->isActive())) timerData->start(100);

            if (moon->isVisible()) moon->hide();
            if (moon2->isVisible()) moon2->hide();
            if (date->isHidden()) date->show();
            if (time->isHidden()) time->show();
        }
        else
        {
            QMessageBox error;
            error.setWindowTitle("Errore costruzione data.");
            error.setText("ERRORE:\nRispettare formato corretto.\n[Ore 0-23]\n[Minuti 0-59]\n[Secondi 0-59]\nGiorno [1-28/29/30/31]\nMese [1-12]\nAnno [1-...]");
            error.setFont(QFont( "Arial", 10, QFont::Bold));
            error.exec();

        }
    }

}
void View::FusoClicked()
{


    //Dialog per istanziare
    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Settaggio di una data con fuso-orario."));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Ore: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Minuti: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Secondi: ");
    form.addRow(label3, lineEdit3);
    QLineEdit *lineEdit4 = new QLineEdit(dialog);
    QString label4 = QString("Giorno*: ");
    form.addRow(label4, lineEdit4);
    QLineEdit *lineEdit5 = new QLineEdit(dialog);
    QString label5 = QString("Mese*: ");
    form.addRow(label5, lineEdit5);
    QLineEdit *lineEdit6 = new QLineEdit(dialog);
    QString label6 = QString("Anno*: ");
    form.addRow(label6, lineEdit6);
    QLineEdit *lineEdit7 = new QLineEdit(dialog);
    QString label7 = QString("Emisfero(1=Boreale;0=Australe):");
    form.addRow(label7, lineEdit7);
    QLineEdit *lineEdit8 = new QLineEdit(dialog);
    QString label8 = QString("Fascia oraria**: ");
    form.addRow(label8, lineEdit8);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    form.addRow(new QLabel("\n*Campo obbligatorio."));
    QLabel* map = new QLabel(dialog);
    QPixmap mappa(":/icone/fusomap.png");
    map->setPixmap(mappa.scaled(600,300,Qt::KeepAspectRatio));
    form.addRow(new QLabel("\n**Rispettare le fasce:"));
    form.addRow(map);




    QString s;
    bool sentinella=true;

    if (dialog->exec() == QDialog::Accepted)
    {

        s = s+lineEdit1->text();
        s = s+":"+lineEdit2->text();
        s = s+":"+lineEdit3->text();
        s = s+":"+lineEdit4->text();
        s = s+":"+lineEdit5->text();
        s = s+":"+lineEdit6->text();
        s = s+":"+lineEdit7->text();
        s = s+":"+lineEdit8->text();

        if(timerOra->isActive()) timerOra->stop();
        if(timerData->isActive()) timerData->stop();
        if(timerLuna->isActive()) timerLuna->stop();
        if(timerFuso->isActive()) timerFuso->stop();


        sentinella = controller->OnFusoClicked(s);
        if (sentinella)
        {
            //TIPO DA DISABILITARE, se si vuole resettare si preme Clear
            Fuso->setDisabled(true);
            Data->setEnabled(true);
            Luna->setEnabled(true);
            Orario->setEnabled(true);

            //Operazioni da disabilitare
            prossimaNuova->setDisabled(true);
            prossimaPiena->setDisabled(true);
            ultimaNuova->setDisabled(true);
            ultimaPiena->setDisabled(true);

            //OPERAZIONI DA ABILITARE
            somma->setEnabled(true);
            sub->setEnabled(true);
            formato->setEnabled(true);
            giornoSet->setEnabled(true);
            stagione->setEnabled(true);
            setMese->setEnabled(true);
            setAnno->setEnabled(true);
            durata->setEnabled(true);
            clear->setEnabled(true);
            oreStudio->setEnabled(true);

            dimmiFuso->setEnabled(true);
            sommaFuso->setEnabled(true);
            fusoDiff->setEnabled(true);
            togliFuso->setEnabled(true);



            if(!(timerOra->isActive()))timerOra->start(100);
            if(!(timerData->isActive())) timerData->start(100);
            if(!(timerFuso->isActive())) timerFuso->start(100);

            if (moon->isVisible()) moon->hide();
            if (moon2->isVisible()) moon2->hide();
            if (date->isHidden()) date->show();
            if (time->isHidden()) time->show();
            if (fuso->isHidden()) fuso->show();
        }
        else
        {
            QMessageBox error;
            error.setWindowTitle("Errore costruzione data con fuso-orario.");
            error.setText("ERRORE:\nRispettare formato corretto.\n[Ore 0-23]\n[Minuti 0-59]\n[Secondi 0-59]\nGiorno [1-28/29/30/31]\nMese [1-12]\nAnno [1-...]");
            error.setFont(QFont( "Arial", 10, QFont::Bold));
            error.exec();

        }
    }

}
void View::LunaClicked()
{

    //Dialog per istanziare
    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Settaggio di una data per calendario lunare."));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Ore: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Minuti: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Secondi: ");
    form.addRow(label3, lineEdit3);
    QLineEdit *lineEdit4 = new QLineEdit(dialog);
    QString label4 = QString("Giorno*: ");
    form.addRow(label4, lineEdit4);
    QLineEdit *lineEdit5 = new QLineEdit(dialog);
    QString label5 = QString("Mese*: ");
    form.addRow(label5, lineEdit5);
    QLineEdit *lineEdit6 = new QLineEdit(dialog);
    QString label6 = QString("Anno*: ");
    form.addRow(label6, lineEdit6);
    QLineEdit *lineEdit7 = new QLineEdit(dialog);
    QString label7 = QString("Emisfero(Boreale;Australe):");
    form.addRow(label7, lineEdit7);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    form.addRow(new QLabel("\n*Campo obbligatorio."));


    QString s;
    bool sentinella=true;

    if (dialog->exec() == QDialog::Accepted)
    {

        s = s+lineEdit1->text();
        s = s+":"+lineEdit2->text();
        s = s+":"+lineEdit3->text();
        s = s+":"+lineEdit4->text();
        s = s+":"+lineEdit5->text();
        s = s+":"+lineEdit6->text();
        s = s+":"+lineEdit7->text();

        if(timerData->isActive()) timerData->stop();
        if(timerOra->isActive()) timerOra->stop();
        if(timerLuna->isActive()) timerLuna->stop();
        if(timerFuso->isActive()) timerFuso->stop();

        sentinella = controller->OnLunaClicked(s);
        if (sentinella)
        {
            //TIPO DA DISABILITARE, se si vuole resettare si preme Clear
            Luna->setDisabled(true);
            Data->setEnabled(true);
            Orario->setEnabled(true);
            Fuso->setEnabled(true);

            dimmiFuso->setDisabled(true);
            sommaFuso->setDisabled(true);
            fusoDiff->setDisabled(true);
            togliFuso->setDisabled(true);

            //OPERAZIONI DA ABILITARE
            somma->setEnabled(true);
            sub->setEnabled(true);
            formato->setEnabled(true);
            giornoSet->setEnabled(true);
            stagione->setEnabled(true);
            setMese->setEnabled(true);
            setAnno->setEnabled(true);
            durata->setEnabled(true);
            prossimaNuova->setEnabled(true);
            prossimaPiena->setEnabled(true);
            ultimaNuova->setEnabled(true);
            ultimaPiena->setEnabled(true);
            clear->setEnabled(true);
            oreStudio->setEnabled(true);



            if(!(timerOra->isActive()))timerOra->start(100);
            if(!(timerData->isActive())) timerData->start(100);
            if(!(timerLuna->isActive())) timerLuna->start(100);


            if(fuso->isVisible()) fuso->hide();
            if (date->isHidden()) date->show();
            if (time->isHidden()) time->show();
            if (moon->isHidden()) moon->show();
            if(moon2->isHidden()) moon2->show();
        }
        else
        {
            QMessageBox error;
            error.setWindowTitle("Errore costruzione data.");
            error.setText("ERRORE:\nRispettare formato corretto.\n[Ore 0-23]\n[Minuti 0-59]\n[Secondi 0-59]\nGiorno [1-28/29/30/31]\nMese [1-12]\nAnno [1-...]");
            error.setFont(QFont( "Arial", 10, QFont::Bold));
            error.exec();

        }
    }

}

void View::SommaButtonClicked()
{

    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Inserire un orario positivo da sommare."));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Ore: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Minuti: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Secondi: ");
    form.addRow(label3, lineEdit3);

    QLineEdit *lineEdit4;
    QLineEdit *lineEdit5;
    QLineEdit *lineEdit6;



    if (!(Data->isEnabled()) || !(Fuso->isEnabled()) || !(Luna->isEnabled() ))
    {
        lineEdit4 = new QLineEdit(dialog);
        QString label4 = QString("Giorni: ");
        form.addRow(label4, lineEdit4);
        lineEdit5 = new QLineEdit(dialog);
        QString label5 = QString("Mesi (4 settimane): ");
        form.addRow(label5, lineEdit5);
        lineEdit6 = new QLineEdit(dialog);
        QString label6 = QString("Anni: ");
        form.addRow(label6, lineEdit6);

    }

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    QString s;
    bool sentinella;
    if (dialog->exec() == QDialog::Accepted)
    {
        if (!(Data->isEnabled()) || !(Fuso->isEnabled()) || !(Luna->isEnabled() ))
        {
            s = s+lineEdit1->text();//ore
            s = s+":"+lineEdit2->text();//min
            s = s+":"+lineEdit3->text();//sec
            s = s+":"+lineEdit4->text();//giorni
            s = s+":"+lineEdit5->text();//mesi
            s = s+":"+lineEdit6->text();//anni
            sentinella=controller->OnSommaButtonClicked(s);
        }


        else //sono in Orario quindi
        {
             s = s+lineEdit1->text();
             s = s+":"+lineEdit2->text();
             s = s+":"+lineEdit3->text();
             sentinella=controller->OnSommaButtonClicked(s);
        }
        if(!sentinella)
        {
            QMessageBox error;
            error.setWindowTitle("Errore operazione.");
            error.setText("ERRORE:\nNon si possono sommare valori negativi.");
            error.setFont(QFont( "Arial", 10, QFont::Bold));
            error.exec();

        }
    }
}

void View::SubButtonClicked()
{

    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Inserire un orario positivo da sottrarre."));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Ore: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Minuti: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Secondi: ");
    form.addRow(label3, lineEdit3);

    QLineEdit *lineEdit4;
    QLineEdit *lineEdit5;
    QLineEdit *lineEdit6;



    if (!(Data->isEnabled()) || !(Fuso->isEnabled()) || !(Luna->isEnabled() ))
    {
        lineEdit4 = new QLineEdit(dialog);
        QString label4 = QString("Giorni: ");
        form.addRow(label4, lineEdit4);
        lineEdit5 = new QLineEdit(dialog);
        QString label5 = QString("Mesi (4 settimane): ");
        form.addRow(label5, lineEdit5);
        lineEdit6 = new QLineEdit(dialog);
        QString label6 = QString("Anni: ");
        form.addRow(label6, lineEdit6);

    }

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    QString s;
    bool sentinella;
    if (dialog->exec() == QDialog::Accepted)
    {
        if (!(Data->isEnabled()) || !(Fuso->isEnabled()) || !(Luna->isEnabled() ))
        {
            s = s+lineEdit1->text();//ore
            s = s+":"+lineEdit2->text();//min
            s = s+":"+lineEdit3->text();//sec
            s = s+":"+lineEdit4->text();//giorni
            s = s+":"+lineEdit5->text();//mesi
            s = s+":"+lineEdit6->text();//anni
            sentinella=controller->OnSubButtonClicked(s);
        }


        else //sono in Orario quindi
        {
             s = s+lineEdit1->text();
             s = s+":"+lineEdit2->text();
             s = s+":"+lineEdit3->text();
             sentinella=controller->OnSubButtonClicked(s);
        }

        if(!sentinella)
        {
            QMessageBox error;
            error.setWindowTitle("Errore operazione.");
            error.setText("ERRORE:\nNon si possono sottrare valori negativi.");
            error.setFont(QFont( "Arial", 10, QFont::Bold));
            error.exec();

        }
    }

}
void View::durataClicked()
{
    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Inserire una data di cui si vogliono conoscere i giorni di differenza"));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Giorno: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Mese: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Anno: ");
    form.addRow(label3, lineEdit3);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    QString s;
    if (dialog->exec() == QDialog::Accepted)
        {
            s = s+lineEdit1->text();
            s = s+":"+lineEdit2->text();
            s = s+":"+lineEdit3->text();

            int aux=controller->OnDurataClicked(s);

            if(aux!=0)
            {
                QMessageBox res;
                res.setWindowTitle("Periodo di differenza ritornato.");
                res.setText("Giorni mancanti alla data selezionata: "+ QString::number(aux));
                res.setFont(QFont( "Arial", 10, QFont::Bold));
                res.exec();

            }
            else //errore
            {
                QMessageBox res;
                res.setWindowTitle("Periodo di differenza ritornato.");
                res.setText("ERRORE:\nInserire una data maggiore della corrente.\nOgni valore deve essere inoltre strettamente positivo.");
                res.setFont(QFont( "Arial", 10, QFont::Bold));
                res.exec();

            }
        }
}
void View::prossimaPienaClicked()
{
    int aux = controller->ProssimaPiena();

    QMessageBox res;
    res.setWindowTitle("Prossima luna piena.");
    res.setText("Prossima luna piena in "+ QString::number(aux)+" giorni.");
    res.setFont(QFont( "Arial", 10, QFont::Bold));
    res.exec();


}

void View::ultimaPienaClicked()
{
    int aux = controller->UltimaPiena();

    QMessageBox res;
    res.setWindowTitle("Ultima luna piena.");
    res.setText("Ultima luna piena e' stata "+ QString::number(aux)+" giorni fa.");
    res.setFont(QFont( "Arial", 10, QFont::Bold));
    res.exec();

}

void View::prossimaNuovaClicked()
{
    int aux = controller->ProssimaNuova();

    QMessageBox res;
    res.setWindowTitle("Prossima luna nuova.");
    res.setText("Prossima luna nuova in "+ QString::number(aux)+" giorni.");
    res.setFont(QFont( "Arial", 10, QFont::Bold));
    res.exec();

}

void View::ultimaNuovaClicked()
{
    int aux = controller->UltimaNuova();

    QMessageBox res;
    res.setWindowTitle("Ultima luna nuova.");
    res.setText("Ultima luna nuova e' stata "+ QString::number(aux)+" giorni fa.");
    res.setFont(QFont( "Arial", 10, QFont::Bold));
    res.exec();

}

void View::dimmiFusoClicked(){

    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Che fuso-orario e' in vigore nella zona..."));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Fascia*: ");
    form.addRow(label1, lineEdit1);
    form.addRow(new QLabel("*Usare lettere maiuscole."));

    QLabel* l = new QLabel(dialog);
    l->setText("Y: Isola Baker, Isola Holland.\nX: Palmyra, Niue.\nW: Hawaii, Polinesia francese.\nV: Alaska.\nU: Canada, USA west.\nT: Messico, USA centro.\nS: CostaRica, Guatemala.\nR:Bahamas, USA east.\nQ:Paraguay, Venezuela.\nP: Argentina, Groenlandia.\nO: Fernando de Noronha, Georgia Australe.\nN: Azzorre.\nZ: RegnoUnito, Islanda.\nA:Italia, Germania.\nB: Egitto, Grecia.\nC: Mosca, Madagascar.\nD: Emirati Arabi, Armenia.\nE: Maldive, India.\nF:Bangladesh, Kazakistan.\nG: Thailandia, Vietnam.\nH: Singapore, HongKong.\nI: Giappone, Korea Sud.\nK: Australia east, Guam.\nL: Isole Salomone, Nuova Caledonia.\nM: Nuova Zelanda, Figi.");
    form.addRow(l);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    if (dialog->exec() == QDialog::Accepted)
        {


            int aux=controller->DimmiFuso(lineEdit1->text());

            QMessageBox res;
            res.setWindowTitle("Risultato ricerca.");
            res.setText("Il fuso-orario qui e': "+ QString::number(aux)+".");
            res.setFont(QFont( "Arial", 10, QFont::Bold));
            res.exec();


        }



}

void View::fusoDiffClicked(){

    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Quale fuso-orario vuoi confrontare?"));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Inserire fuso di arrivo: ");
    form.addRow(label1, lineEdit1);
    QLabel* map = new QLabel(dialog);
    QPixmap mappa(":/icone/fusomap2.png");
    map->setPixmap(mappa.scaled(600,300,Qt::KeepAspectRatio));
    form.addRow(new QLabel("\nLegenda:"));
    form.addRow(map);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    if (dialog->exec() == QDialog::Accepted)
        {


            int aux=controller->fuDiff(lineEdit1->text());

            QMessageBox res;
            res.setWindowTitle("Differenza fuso-orario.");
            res.setText("Differenza tra i due fusi-orari: "+ QString::number(aux)+" ore.");
            res.setFont(QFont( "Arial", 10, QFont::Bold));
            res.exec();


        }




}

void View::sommaFusoClicked(){

    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Di quanto ti vuoi spostare a est?"));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Inserire le ore di cui ci si vuole spostare(0-25): ");
    form.addRow(label1, lineEdit1);
    QLabel* map = new QLabel(dialog);
    QPixmap mappa(":/icone/fusomap2.png");
    map->setPixmap(mappa.scaled(600,300,Qt::KeepAspectRatio));
    form.addRow(new QLabel("\nLegenda:"));
    form.addRow(map);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    if (dialog->exec() == QDialog::Accepted)
    {
        bool sentinella=controller->sumFuso(lineEdit1->text());
        if(!sentinella)
        {
            QMessageBox res;
            res.setWindowTitle("ERRORE");
            res.setText("Il valore inserito non rispetta i limiti richiesti.");
            res.setFont(QFont( "Arial", 10, QFont::Bold));
            res.exec();
        }

    }


}

void View::togliFusoClicked(){

    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Di quanto ti vuoi spostare a ovest?"));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Inserire le ore di cui ci si vuole spostare(0-25): ");
    form.addRow(label1, lineEdit1);
    QLabel* map = new QLabel(dialog);
    QPixmap mappa(":/icone/fusomap2.png");
    map->setPixmap(mappa.scaled(600,300,Qt::KeepAspectRatio));
    form.addRow(new QLabel("\nLegenda:"));
    form.addRow(map);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    if (dialog->exec() == QDialog::Accepted)
    {
        bool sentinella=controller->subFuso(lineEdit1->text());
        if(!sentinella)
        {
            QMessageBox res;
            res.setWindowTitle("ERRORE");
            res.setText("Il valore inserito non rispetta i limiti richiesti.");
            res.setFont(QFont( "Arial", 10, QFont::Bold));
            res.exec();
        }
    }


}

void View::oreStudioclicked()
{
    QDialog* dialog = new QDialog(this);
    QFormLayout form(dialog);

    form.addRow(new QLabel("Inserire la data dell'esame che si vuole dare:"));

    QLineEdit *lineEdit1 = new QLineEdit(dialog);
    QString label1 = QString("Giorno: ");
    form.addRow(label1, lineEdit1);
    QLineEdit *lineEdit2 = new QLineEdit(dialog);
    QString label2 = QString("Mese: ");
    form.addRow(label2, lineEdit2);
    QLineEdit *lineEdit3 = new QLineEdit(dialog);
    QString label3 = QString("Anno: ");
    form.addRow(label3, lineEdit3);
    QLineEdit *lineEdit4 = new QLineEdit(dialog);
    QString label4 = QString("Ore di studio al giorno: ");
    form.addRow(label4, lineEdit4);

    QDialogButtonBox* buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    QString s; QString x;
    if (dialog->exec() == QDialog::Accepted)
    {
        s = s+lineEdit1->text();
        s = s+":"+lineEdit2->text();
        s = s+":"+lineEdit3->text();
        x= s+":"+lineEdit4->text();
        int aux=controller->OnOreStudioClicked(x);
        int aux2=controller->OnDurataClicked(s);
        if (aux!=0 && aux2!=0)
        {
            QMessageBox res;
            res.setWindowTitle("Esame da preparare con:");
            res.setText("Totale delle ore di studio: "+ QString::number(aux)+"\nGiorni mancanti alla data selezionata: "+ QString::number(aux2));
            res.setFont(QFont( "Arial", 10, QFont::Bold));
            res.exec();

        }

        else//errore
        {
            QMessageBox res;
            res.setWindowTitle("Errore.");
            res.setText("ERRORE:\nInserire una data maggiore della corrente.\nOgni valore deve essere inoltre strettamente positivo.");
            res.setFont(QFont( "Arial", 10, QFont::Bold));
            res.exec();
        }
    }
}
