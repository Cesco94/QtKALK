#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QString>


// Forward Declaration
class QPushButton;
class QToolButton;
class QGridLayout;
class Controller;
class QTimer;
class QLabel;
class QDialog;



class View : public QWidget
{
    Q_OBJECT

public:

    explicit View(QWidget *parent = 0, QString name = "Time Calculator");

    virtual ~View();

    void setController(Controller*);

public slots:

    void OrarioClicked();
    void DataClicked();
    void FusoClicked();
    void LunaClicked();

    void ClearButtonClicked();
    void SommaButtonClicked();
    void SubButtonClicked();
    void formatoclicked();
    void showTime();
    void showDate();
    void showMoon();
    void showFuso();

    void GiornoSetClicked();
    void StagioneClicked();
    void setMclicked();
    void setAclicked();
    void durataClicked();
    void oreStudioclicked();

    void prossimaPienaClicked();
    void ultimaPienaClicked();
    void prossimaNuovaClicked();
    void ultimaNuovaClicked();

    void dimmiFusoClicked();
    void fusoDiffClicked();
    void sommaFusoClicked();
    void togliFusoClicked();






private:

    Controller* controller;
    QString appName;

    QGridLayout* layoutG;

    QLabel* time;
    QLabel* date;
    QLabel* moon;
    QLabel* moon2;
    QLabel* fuso;

    QTimer* timerOra;
    QTimer* timerData;
    QTimer* timerFuso;
    QTimer* timerLuna;

    QToolButton* Orario;
    QToolButton* Data;
    QToolButton* Fuso;
    QToolButton* Luna;

    //OPERAZIONI SU OGNI TIPO
    QPushButton* clear;
    QToolButton* somma;
    QToolButton* sub;
    //OPERAZIONI ORARIO
    QToolButton* convore;
    QToolButton* convgiorni;
    QToolButton* formato;
    bool flagformato;
    //OPERAZIONI DATA
    QToolButton* giornoSet;
    QToolButton* stagione;
    QToolButton* setMese;
    QToolButton* setAnno;
    QToolButton* durata;
    QToolButton* oreStudio;
    //OPERAZIONI LUNA
    QToolButton* prossimaPiena;
    QToolButton* prossimaNuova;
    QToolButton* ultimaPiena;
    QToolButton* ultimaNuova;
    //OPERAZIONI FUSO
    QToolButton* dimmiFuso;
    QToolButton* fusoDiff;
    QToolButton* sommaFuso;
    QToolButton* togliFuso;





};

//scrivere le eccezioni per il lancio di somma fuso e togli fuso


#endif // VIEW_H
