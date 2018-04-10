public class data extends orario{
	
	private int giorno;
    private int mese;
    private int anno;
    private boolean emisfero;

    public data() 
    {
        super();
        giorno=1;
        mese=1;
        anno=2000;
    }
    public data(int g, int m, int a, boolean emis) throws overflow_error 
    {
        super();
        if(m<1||m>12)
            throw new overflow_error();
        else mese=m;

        //Controllo del giorno
        if(g<1||g>giorniMese(m)) //cosi' si lancia errore anche per il 30 Febbraio ad esempio
            throw new overflow_error();
        else giorno=g;

        //Controllo anno, va bene qualsiasi anno, tranne i negativi
        if(a<=0)
            throw new overflow_error();
        else anno=a;
        
        emisfero=emis;       
    }

    public data(int g, int m, int a, int o, int min,int s, boolean emis) throws overflow_error 
    {

        super(o,min,s);
        if(m<1||m>12)
            throw new overflow_error();
        else mese=m;

        //Controllo del giorno
        if(g<1||g>giorniMese(m)) //cosi' si lancia errore anche per il 30 Febbraio ad esempio
            throw new overflow_error();
        else giorno=g;

        //Controllo anno, va bene qualsiasi anno, tranne i negativi
        if(a<=0)
            throw new overflow_error();
        else anno=a;
        
        emisfero=emis;

    }

    public void reset() throws overflow_error
    {
        aggiornaSec(0);
        giorno=mese=1;
        emisfero=true;
        anno=2000;
    }

    public int oreDiStudio(data d,int ore) throws overflow_error 
    {
        if(ore<0)
            throw new overflow_error();
        else
        {
            int dur=durata(d);
            return ConvertiInOredate(dur,ore);
        }
    }

    public data(data d)
    {
            super(d);
            giorno=d.getGiorno();
            mese=d.getMese();
            anno=d.getAnno();
            emisfero=d.getEmisfero();   
    }
    public void print()
    {
        System.out.println(getGiorno()+"/" + getMese()+"/" + getAnno() );
        if (getEmisfero()) System.out.println("Emisfero boreale.");
        else System.out.println("Emisfero australe.");
        System.out.println(getOra()+":"+getMin()+":"+getSec());
    }

	
	public int getGiorno() 
	{
	    return giorno;
	}
	public int getMese() 
	{
	    return mese;
	}
	public int getAnno()  
	{
	    return anno;
	}
	public boolean getEmisfero()
	{
	    return emisfero;
	}
	public int countgiorni() throws overflow_error
	{
	    int count=giorno;
	    for(int i=1;i<mese;i++)
	    {
	       count=count+ giorniMese(i);
	    }

	    return count;
	}
	public static boolean bisestile(int a) throws overflow_error
	{
	    if(a<=0) throw new overflow_error();

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

	public int giorniMese(int m) throws overflow_error
	{

	    if(m<1||m>12) throw new overflow_error();

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

	public void avanzaUnGiorno() throws overflow_error
	{
	    if(giorno<giorniMese(mese)) giorno++;
	    else if (mese<12) {giorno=1;mese++;}
	    else {giorno=1; mese=1;anno++;}
	}
	public void indietroUnGiorno() throws overflow_error
	{
	    if (giorno>1) giorno--;
	    else if (mese==1){anno--;mese=12;giorno=31;} //era il 1 gennaio quindi vado anche indietro di un anno
	    else {
	        mese--; //e' il primo di un mese che non e' gennaio
	        giorno = giorniMese(mese); //mese e' diminuito, devo sapere se casco nel 30 o nel 31 o nel 28/29
	    }
	}

	public String giornoSettimana() throws overflow_error
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
	    return "";
	}

	public String stagione() throws overflow_error
	{
	    int aux=countgiorni();
	    if(aux<79 || aux>355)
	    {
	        if(emisfero==true)
	            return "Inverno";
	        else
	            return "Estate";
	    }
	    else if(aux>=79 && aux<172)
	    {
	        if(emisfero==true)
	            return "Primavera";
	        else
	            return "Autunno";
	    }
	    else if(aux>=172 && aux<263)
	    {
	        if(emisfero==true)
	            return "Estate";
	        else
	            return "Inverno";
	    }
	    else if(aux>=263 && aux<355)
	    {
	        if(emisfero==true)
	            return "Autunno";
	        else
	            return "Primavera";
	    }

	    return "";

	}

	public int settimanaanno() throws overflow_error
	{
	    data aux= new data(1,1,anno,emisfero);
	    String firstday=aux.giornoSettimana();
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

	public int settimanamese() throws overflow_error
	{
	    data aux= new data(this);
	    aux.cambiaGiorno(1);
	    String firstday=aux.giornoSettimana();//primo giorno del mese
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
		case(2):
	        if(giorno<7) return 1;
	        else{
	            if((giorno-6)%7==0)
	                return ((giorno-6)/7+1);
	            else
	                return ((giorno-6)/7+2);
	        }
		case(3):
	        if(giorno<6) return 1;
	        else{
	            if((giorno-5)%7==0)
	                return ((giorno-5)/7+1);
	            else
	                return ((giorno-5)/7+2);
	        }
		case(4):
	        if(giorno<5) return 1;
	        else{
	            if((giorno-4)%7==0)
	                return ((giorno-4)/7+1);
	            else
	                return ((giorno-4)/7+2);
	        }
		case(5):
	        if(giorno<4) return 1;
	        else{
	            if((giorno-3)%7==0)
	                return ((giorno-3)/7+1);
	            else
	                return ((giorno-3)/7+2);
	        }
		case(6):
	        if(giorno<3) return 1;
	        else{
	            if((giorno-2)%7==0)
	                return ((giorno-2)/7+1);
	            else
	                return ((giorno-2)/7+2);
	        }
		case(7):
	        if(giorno<2) return 1;
	        else{
	            if((giorno-1)%7==0)
	                return ((giorno-1)/7+1);
	            else
	                return ((giorno-1)/7+2);
	        }
	        }
	    return 0;

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

	}
	
    public void TogliSec(int s) throws overflow_error
	{

	    if(s<0) throw new overflow_error();
	    if(s==0) return;

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
	}
	public void TogliMin(int m) throws overflow_error
	{

	    if(m<0) throw new overflow_error();
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
	public void TogliOra(int o) throws overflow_error
	{

	    if (o<0) throw new overflow_error();
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

	public data SommaOrario(orario o1) throws overflow_error
	{
	    data d1=new data(this);
	    if(d1.getSecTot()+o1.getSecTot()>=86400)
	    {
	        d1.avanzaUnGiorno();
	        d1.aggiornaSec((d1.getSecTot()+o1.getSecTot())%86400);
	    }
	    else
	    {
	        d1.aggiornaSec(d1.getSecTot()+o1.getSecTot());
	    }
	    return d1;
	}

	public data SubOrario(orario o1) throws overflow_error
	{
	    if (o1.getSecTot()==0) return new data(this);
	    data d1=new data(this);
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

	    return d1;

	}

	public void avanzaTotGiorni(int n) throws overflow_error
	{

	    if(n<0) throw new overflow_error();
	    if (n==0) return;

	    //caso "base" in cui devo avanzare di meno giorni di quelli che mancano alla fine del mese corrente
	    if ((giorniMese(mese)-giorno)>=n){
	        giorno = giorno + n;
	    }
	    //se invece devo avanzare oltre, potrei dover cambiare anche piu' di un mese
	    else {
	        int aux = giorniMese(mese)-giorno; //giorni per cambiare mese(aux sicuramente minore stretto di n)
	        n = n -aux; //li tolgo a n, come se fossi all'ultimo giorno del mese (qui n e' sicuramente >0)
	        if(mese==12){
	            mese=1; //avanzo
	            anno++;
	        }
	        else {
	            mese++;
	        }
	        while (n!=0){
	            if(n<=giorniMese(mese))
	            {
	                giorno = n; //non ho piu' mesi da andare avanti
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
	public void indietroTotGiorni(int n) throws overflow_error
	{

	    if(n<0) throw new overflow_error();

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
	    //se invece devo andare indietro di 1 o piu' mesi
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
	        while (n!=0){
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
	public boolean maggioreDi(data d1) 
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
	   
	}

	public int durata(data d1) throws overflow_error
	{
		int year; //variabile di differenza anni
		int day=0;//giorni di differenza
		if(this.maggioreDi(d1))// caso in cui passo una data piu'piccola
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

	public void cambiaGiorno(int g) throws overflow_error
	{

	    if(g<1|| g>giorniMese(mese))
	        throw new overflow_error();
	    else
	        giorno=g;
	}

	public void cambiaMese(int m) throws overflow_error
	{

	    if(m<1||m>12)
	        throw new overflow_error();
	    else
	        mese=m;

	}
	public void cambiaAnno(int a) throws overflow_error
	{

	    if(a<=0)
	        throw new overflow_error();
	    else
	        anno=a;

	}
	public void cambiaEmis(boolean e)
	{
	    emisfero = e;
	}

}
