#ifndef CONTROLLER_H
#define CONTROLLER_H

//Forward Declaration
class Model;
class QString;
class QTime;
class QDate;

class Controller {

public:

  Controller(Model* m);

  virtual ~Controller();

  bool OnOrarioClicked(QString) const;
  bool OnDataClicked(QString) const;

  bool OnFusoClicked(QString) const;
  bool OnLunaClicked(QString) const;

  void OnClearButtonClicked() const;
  bool OnSommaButtonClicked(QString) const;
  bool OnSubButtonClicked(QString) const;
  QTime getTime(bool) const;
  QDate getDate() const;
  bool getEmis() const;
  int getFusoZona() const;
  char getFusoFascia() const;

  bool checkOrario() const;
  QString checkFase() const;

  QString OnStagioneClicked() const;
  QString OnGiornoSetClicked() const;

  int onSetMeseclicked() const;
  int onSetAnnoclicked() const;
  int OnDurataClicked(QString) const;
  int OnOreStudioClicked(QString) const;

  int ProssimaPiena() const;
  int ProssimaNuova() const;
  int UltimaPiena() const;
  int UltimaNuova() const;

  int DimmiFuso(QString) const;
  int fuDiff(QString) const;
  bool sumFuso(QString) const;
  bool subFuso(QString) const;


private:
  Model* model;
};
#endif // CONTROLLER_H
