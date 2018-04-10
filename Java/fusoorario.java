import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
public class fusoorario extends data {
	private int zona;
	private static final Map<Integer ,Character> fasce;
	static 
	{
		Map<Integer , Character> result= new HashMap<Integer,Character>();
		result.put(-12,'Y');
	    result.put(-11,'X');
	    result.put(-10,'W');
	    result.put(-9,'V');
	    result.put(-8,'U');
	    result.put(-7,'T');
	    result.put(-6,'S');
	    result.put(-5,'R');
	    result.put(-4,'Q');
	    result.put(-3,'P');
	    result.put(-2,'O');
	    result.put(-1,'N');
	    result.put(0,'Z');
	    result.put(1,'A');
	    result.put(2,'B');
	    result.put(3,'C');
	    result.put(4,'D');
	    result.put(5,'E');
	    result.put(6,'F');
	    result.put(7,'G');
	    result.put(8,'H');
	    result.put(9,'I');
	    result.put(10,'K');
	    result.put(11,'L');
	    result.put(12,'M');
	    fasce=Collections.unmodifiableMap(result);
	}
	public fusoorario()  {
		zona=0;
	}
	public fusoorario(int fascia)throws overflow_error {
		super();
		zona=fascia;
		if(fascia>12 || fascia<-12) 
			throw new overflow_error();
		}
	public fusoorario(data oggi,int fascia) throws overflow_error
	{
		super(oggi);
		zona=fascia;
		if(fascia>12 || fascia<-12) 
			throw new overflow_error();
		}
	public fusoorario(int g,int m,int a,boolean e ,int fascia)  throws overflow_error 
	{
		super(g,m,a,e);
		zona=fascia;
		if(fascia>12 || fascia<-12) 
			throw new overflow_error();}
	fusoorario(fusoorario f) {
		super(f);
		zona=f.getZona();
	}
	public char getFascia() 
	{
	    return fasce.get(zona);
	}
	public int getZona() 
	{
	    return zona;
	}

	public static int dimmiFuso(char z) 
	{
	    boolean ok=true;
	    int aux=0;
	  for(int i=-12;i<13 && ok==true;i++)
	  {
	      if(fasce.get(i)==z)
	      {
	          ok=false;
	          aux=i;
	       }
	  }
	  return aux;
	}
	public int fusodiff(fusoorario fuso)
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
	public void sommafuso(int fuso)
	{
	    if(zona+fuso>12)
	    {
	        fuso=zona+fuso-12;
	        int zonaprec=zona;
	        zona=-12+fuso-1;
	        try {super.TogliOra(-zona+zonaprec);}
	        catch(overflow_error e) {e.getReason();}

	    }
	    else
	    {
	        zona=zona+fuso;
	        try{super.SommaOra(fuso);}
	        catch(overflow_error e) {e.getReason();}
	    }
	}

	public void toglifuso(int fuso)
	{
	    if(zona-fuso<-12)
	    {
	        fuso=-zona+fuso-12;
	        int zonaprec=zona;
	        zona=12-fuso+1;
	        try{super.SommaOra(zona-zonaprec);}
	        catch(overflow_error e) {e.getReason();}
	    }
	    else
	    {
	        zona=zona-fuso;
	        try{super.TogliOra(fuso);}
	        catch(overflow_error e) {e.getReason();}
	    }
	}
	public void Print()
	{
		super.print();
		System.out.println("Fascia: "+this.getFascia());
	}
	
	public fusoorario SommaOrario(orario o1)
	{
	    fusoorario d1=new fusoorario(this);
	    if(d1.getSecTot()+o1.getSecTot()>=86400)
	    {
	        try{d1.avanzaUnGiorno();}
	        catch(overflow_error e) {e.getReason();}
	        d1.aggiornaSec((d1.getSecTot()+o1.getSecTot())%86400);
	    }
	    else
	    {
	        d1.aggiornaSec(d1.getSecTot()+o1.getSecTot());
	    }
	    return d1;
	}
	public fusoorario SubOrario(orario o1)
	{
	    if (o1.getSecTot()==0) return new fusoorario(this);
	    fusoorario d1=new fusoorario(this);
	    if(d1.getSecTot()-o1.getSecTot()<0)
	    {
	        if(d1.getSecTot()==0)
	        {
	            try{d1.indietroUnGiorno();}
	            catch(overflow_error e) {e.getReason();}
	            d1.aggiornaSec(86400-(o1.getSecTot()));

	        }
	        else
	        {
	            try{d1.indietroUnGiorno();}
	            catch(overflow_error e) {e.getReason();}
	            d1.aggiornaSec(86400-(o1.getSecTot()%d1.getSecTot()));

	        }
	    }
	    else
	        d1.aggiornaSec(d1.getSecTot()-o1.getSecTot());

	    return d1;

	}

	public void reset()
	{
	    try{super.reset();}
	    catch(overflow_error e) {e.getReason();}
	   zona=0;
	}

}
