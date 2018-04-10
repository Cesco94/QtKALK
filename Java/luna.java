public class luna extends data {
	
	
	private String fase; //Esprime la visibilita' in percentuale della luna
	
	//Costruttori
	public luna()
	{
	  super(); //data default
		if (piena()) fase = "Piena";
		  else if (nuova()) fase = "Novilunio";
		  else if(crescente()) fase = "Crescente";
		  else if (calante()) fase = "Calante";
	}
	
	public luna(data oggi) throws overflow_error
	{
		super(oggi);
		
		 if (piena()) fase = "Piena";
		 else if (nuova()) fase = "Novilunio";
		 else if(crescente()) fase = "Crescente";
		 else if (calante()) fase = "Calante";
	}
	
	
	public luna(int g,int m,int a) throws overflow_error
	{
		super(g,m,a, true);
		
		if (piena()) fase = "Piena";
		else if (nuova()) fase = "Novilunio";
		else if(crescente()) fase = "Crescente";
		else if (calante()) fase = "Calante";
	}
	
	public luna(luna l)
	{
		super(l);
		fase=l.getFase();
	}
	
	public String getFase() 
	{
	  return fase;
	}
	
	public void reset()
	{
	
	  try
	  {
		  aggiornaSec(0);
		  cambiaAnno(2000);
		  cambiaMese(1);
		  cambiaGiorno(1);
		  cambiaEmis(true);
	  }
	  catch(overflow_error e) {e.getReason();}//non lancera' mai
	
	  if (piena()) fase = "Piena";
	  else if (nuova()) fase = "Novilunio";
	  else if(crescente()) fase = "Crescente";
	  else if (calante()) fase = "Calante";
	
	}
	
	
	
	public int epatta()
	{
	
	
	  if(getAnno()==2000) return 24;
	  int epatta = 24;
	  if (getAnno()>2000)
	  {
	      for (int i =2000; i<=getAnno(); i++)
	      {
	          epatta = epatta +11;
	          if (epatta>30) epatta = epatta -30;
	      }
	  }
	  if (getAnno()<2000)
	  {
	      for (int i=2000; i>=getAnno(); i--)
	      {
	          epatta = epatta - 11;
	          if (epatta<0)
	          {
	              epatta = 30 +epatta;
	          }
	      }
	  }
	
	  //In questo punto epatta e' l'Epatta dell'anno corrente
	  //MA se la data e' prima del 1 Marzo, l'epatta e' quella dell'anno precedente
	  if (getMese()<=2) //Gennaio o Febbraio
	  {
	      epatta = epatta - 11;
	      if (epatta<0)
	      {
	          epatta = 30 +epatta;
	      }
	  }
	  //In questo punto epatta vale l'Epatta dell'anno corrente
	  //OPPURE se sono prima del 1 Marzo, sono entrato nell'ultimo if
	  //Quindi epatta � l'Epatta dell'anno precedente
	
	  return epatta;
	}
	
	public int ultimaNuova() 
	{
	
	  //data + capomese + epatta = giorno della fase lunare
	  //NB: Conta anche il giorno stesso dell'ultimo novilunio
	  //Rappresenta l'eta' della luna
	  //Se la luna ha 30 giorni significa che e' ritornata nuova
	  //Se la luna ha 15 giorni significa che e' piena
	
	  int dat = getGiorno();
	  int cap;
	  if (getMese()>=3) cap = getMese()-2;
	  else cap = getMese()+10;
	  int ep = epatta();
	
	  int x = dat + cap + ep;
	
	  if(x>=  30) return (x-30);
	  else return x;
	}
	
	public int prossimaNuova()
	{
	
	  return 30-ultimaNuova(); //ultimaNuova vale da 0 a 29 quindi prossima nuova vale da 1-30
	}
	
	public int prossimaPiena()
	{
	
	  if (crescente()||nuova())
	  {
	      return 15-ultimaNuova(); //ultimanuova vale da 0 a 14
	  }
	  else if(piena())
	  {
	      return 30;
	  }
	  else if(calante())
	  {
	      return (prossimaNuova()+15);//ultimanuova vale da 16 a 29
	                                  //quindi prossimaNuova vale da 1 a 14
	  }
	  return 0;
	}
	
	public int ultimaPiena()
	{
	  if(calante())
	  {
	      return ultimaNuova()-15; //ultimaNuova vale da 16 a 29
	  }
	  else if(piena())
	  {
	      return 30;
	  }
	  else if(crescente()||nuova())
	  {
	      return ultimaNuova()+15; //ultimaNuova vale da 0 a 14
	  }
	  return 0;
	
	}
	
	public boolean piena()
	{
	
	  if (ultimaNuova()==15)
	      return true;
	  else
	      return false;
	}
	
	public boolean crescente() 
	{
	
	  if (ultimaNuova()>=1 && ultimaNuova()<=14)
	      return true;
	  else
	      return false;
	}
	
	public boolean nuova() 
	{
	
	  if (ultimaNuova()==0)
	      return true;
	  else
	      return false;
	}
	
	public boolean calante()
	{
	
	  if (ultimaNuova()>=16 && ultimaNuova()<=29)
	      return true;
	  else
	      return false;
	
	}
	
	//----------------------------------------------
	//DA RIDEFINIRE TENENDO CONTO DEL CAMBIO FASE
	//----------------------------------------------
	
	public void avanzaUnGiorno() throws overflow_error{
	  if(getGiorno()<giorniMese(getMese())) cambiaGiorno(getGiorno()+1);
	  else if (getMese()<12) {cambiaGiorno(1);cambiaMese(getMese()+1);}
	  else {cambiaGiorno(1); cambiaMese(1);cambiaAnno(getAnno()+1);}
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	}
	
	public void indietroUnGiorno() throws overflow_error{
	  if (getGiorno()>1) cambiaGiorno(getGiorno()-1);
	  else if (getMese()==1){cambiaAnno(getAnno()-1);cambiaMese(12);cambiaGiorno(31);} //era il 1 gennaio quindi vado anche indietro di un anno
	  else {
	      cambiaMese(getMese()-1); //e' il primo di un mese che non e' gennaio
	      cambiaGiorno(giorniMese(getMese())); //mese e' diminuito, devo sapere se casco nel 30 o nel 31 o nel 28/29
	  }
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	}
	
	
	public void avanzaTotGiorni(int n) throws overflow_error
	{
	
	  if(n<0) throw new overflow_error();
	
	  //caso "base" in cui devo avanzare di meno giorni di quelli che mancano alla fine del mese corrente
	  if ((giorniMese(getMese())-getGiorno())>=n){
	      cambiaGiorno(getGiorno()+n);
	  }
	  //se invece devo avanzare oltre, potrei dover cambiare anche piu' di un mese
	  else {
	      int aux = giorniMese(getMese())-getGiorno(); //giorni per cambiare mese(aux sicuramente minore stretto di n)
	      n = n -aux; //li tolgo a n, come se fossi all'ultimo giorno del mese (qui n e' sicuramente >0)
	      if(getMese()==12){
	          cambiaMese(1); //avanzo
	          cambiaAnno(getAnno()+1);
	      }
	      else {
	          cambiaMese(getMese()+1);
	      }
	      while (n!=0){
	          if(n<=giorniMese(getMese()))
	          {
	              cambiaGiorno(n); //non ho piu' mesi da andare avanti
	              n =0; //finiti giorni da procedere (sentinella while)
	          }
	          else//caso in cui devo andare avanti
	          {
	              n = n - giorniMese(getMese()); //tolgo i giorni del mese che devo saltare
	              if(getMese()==12){//avanzo al mese dopo
	                  cambiaMese(1);
	                  cambiaAnno(getAnno()+1);
	              }
	              else {
	                  cambiaMese(getMese()+1);
	              }
	          }
	      }
	  }
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	}
	
	public void indietroTotGiorni(int n) throws overflow_error
	{
	
	  if(n<0) throw new overflow_error();
	
	  //caso base in cui non torno indietro di neanche un mese
	  if(n<getGiorno()){
	      cambiaGiorno(getGiorno()-n);
	  }
	  //se invece devo andare indietro di 1 o pi� mesi
	  else
	  {
	      n = n-getGiorno(); //tolgo i giorni del mese in cui sono
	      if (getMese()==1){
	          cambiaAnno(getAnno()-1);
	          cambiaMese(12);
	          if(n==0) //ossia non entro nel while
	          {
	              cambiaGiorno(giorniMese(getMese())); //che in questo caso e' 31(Dicembre)
	          }
	      }
	      else{
	          cambiaMese(getMese()-1);
	          if(n==0)
	          {
	              cambiaGiorno(giorniMese(getMese()));
	          }
	      }
	      //Entro nel while qui SOLO se n effettivamente e' positivo, se non ci entro, significa che:
	      //1) n era minore del giorno e l'ho semplicemente sottratto
	      //2) n era UGUALE al giorno in cui sono, quindi vado comunque nel mese precedente all'ultimo giorno perche' non posso avere 0 come giorno
	      while (n!=0){
	          if(n<=giorniMese(getMese()))
	          {
	              cambiaGiorno(giorniMese(getMese())-n);
	              n =0;
	          }
	          else
	          {
	              n = n - giorniMese(getMese());
	              if (getMese()==1){
	                  cambiaAnno(getAnno()-1);
	                  cambiaMese(12);
	              }
	              else{
	                  cambiaMese(getMese()-1);
	              }
	          }
	      }
	  }
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	}
	
	public void SommaSec(int s) throws overflow_error
	{
	
	 if(s<0) throw new overflow_error();
	
	  //Bisogna tener conto che potrei voler sommare piu' di 86400 secondi, quindi devo prima avanzare di tot giorni
	
	  //NOTA BENE: Sec e' privato in orario,quindi devo usare getSec per leggerlo. Per poi modificarlo ho dovuto
	  //           aggiungere una funzione aggiornaSec() che possa cambiare sec
	  if (s>=86400)
	  {
	      while (s>=86400)
	      {
	          avanzaUnGiorno(); //avanzo e tolgo quel giorno aggiunto
	          s = s-86400;
	      }
	      //all'uscita s varra' i secondi rimasti, tolti i giorni, quindi sara' che s<86400
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
	
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	}
	
	public void SommaMin(int m) throws overflow_error
	{
	
	  if(m<0) throw new overflow_error();
	
	  //Stesso discorso se tento di sommare piu' di 1440 minuti (che fanno 1 giorno)
	
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
	
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	
	}
	public void SommaOra(int o) throws overflow_error
	{
	
	  if (o<0) throw new overflow_error();
	
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
	
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	}
	
	public void TogliSec(int s) throws overflow_error
	{
	
	  if(s<0) throw new overflow_error();
	
	  //Bisogna tener conto se si tolgono piu' di 86400 secondi, se cosi' fosse bisogna ciclare indietroUnGiorno()
	  //fino a che non finisci i giorni da togliere
	  if(s>=86400)//s e' maggior della grandezza di un giorno/i
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
	
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	}
	
	public void TogliMin(int m) throws overflow_error
	{
	
	  if(m<0) throw new overflow_error();
	
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
	
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	}
	public void TogliOra(int o) throws overflow_error
	{
	
	  if (o<0) throw new overflow_error();
	
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
	
	  //Aggiornamento fase
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	}
	
	public luna SommaOrario( orario o1) throws overflow_error
	{
	  luna d1 = new luna(this);
	  
	  if(d1.getSecTot()+o1.getSecTot()>=86400)
	  {
	      d1.avanzaUnGiorno();
	      d1.aggiornaSec((d1.getSecTot()+o1.getSecTot())%86400);
	  }
	  else
	  {
	      d1.aggiornaSec(d1.getSecTot()+o1.getSecTot());
	  }
	
	  //Aggiornamento fase
	  //Mi serve costruire un temporaneo con i nuovi giorno/mese/anno di d1
	  //Perche' e' nel costruttore che fase viene assegnato correttamente
	  //In questo modo, nel temporaneo "lu" ho la fase che mi serve
	  //che poi assegno a d1:
	  luna lu = new luna(d1.getGiorno(),d1.getMese(),d1.getAnno());
	  d1.fase=(lu.getFase());

	  return d1;
	}
	
	
	public luna SubOrario(orario o1) throws overflow_error
	{
	  if(o1.getSecTot()==0) return new luna(this);
	  luna d1=new luna(this);
	  if(d1.getSecTot()-o1.getSecTot()<0)
	  {
	      if(d1.getSecTot()==0)
	      {
	          d1.indietroUnGiorno();
	          d1.aggiornaSec(86400-(o1.getSecTot()));
	
	      }
	      else
	      {
	          d1.indietroUnGiorno();
	          d1.aggiornaSec(86400-(o1.getSecTot()%d1.getSecTot()));
	
	      }
	  }
	  else
	      d1.aggiornaSec(d1.getSecTot()-o1.getSecTot());
	
	
	  //Aggiornamento fase
	  //Mi serve costruire un temporaneo con i nuovi giorno/mese/anno di d1
	  //Perche' e' nel costruttore che fase viene assegnato correttamente
	  //In questo modo, nel temporaneo "lu" ho la fase che mi serve
	  //che poi assegno a d1:
	  luna lu = new luna(d1.getGiorno(),d1.getMese(),d1.getAnno());
	  d1.fase=(lu.getFase());

	  return d1;
	
	}
	
	public void print()
	{
	  super.print();
	  System.out.println("Fase lunare: "+ getFase()+".");
	}
	public void cambiaAnno(int a) throws overflow_error
	{
	
	  super.cambiaAnno(a);
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	
	}
	public void cambiaGiorno(int g) throws overflow_error
	{
	
	  super.cambiaGiorno(g);
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	}
	public void cambiaMese(int m) throws overflow_error
	{
	
	  super.cambiaMese(m);
	  luna aux = new luna(getGiorno(),getMese(),getAnno());
	  fase = aux.getFase();
	
	}
	


}
