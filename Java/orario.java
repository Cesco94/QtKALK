import java.lang.*;
public class orario{


	private int sec;
	public orario() 
	{
		sec=0;
	}
	public orario(int o) throws overflow_error
	{
	    if(o<0 || o>23)
	       throw new overflow_error();
	    else
	        sec=o*3600;
	}

	public orario(int o,int m) throws overflow_error
	{
	    if(o<0 || o>23 || m<0 || m>59)
	        throw new overflow_error();
	    else
	        sec=o*3600+m*60;
	}
	public orario(int o,int m,int s) throws overflow_error
	{
	    if(o<0 || o>23 || m<0 || m>59 || s<0 || s>59)
	        throw new overflow_error();
	    else
	        sec=o*3600+m*60+s;
	}


	public void reset() throws overflow_error{
	    sec =0;
	}

	public orario(orario o) 
		{
			sec=getSecTot();
		}


	//OPERAZIONI

	public void SommaSec(int s) throws overflow_error
	{
	    if (s<0) throw new overflow_error();
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
	public void SommaMin(int m) throws overflow_error
	{
	    if (m<0) throw new overflow_error();
	    if(sec+m*60>=86400)
	    {
	        int aux=(sec+m*60)%86400;
	        sec=aux;
	    }
	    else
	       sec+=m*60;
	}
	public void SommaOra(int o) throws overflow_error
	{
	    if (o<0) throw new overflow_error();
	    if(sec+o*3600>=86400)
	    {
	        int aux=(sec+o*3600)%86400;
	        sec=aux;
	    }
	    else
	        sec+=o*3600;
	}

	public void TogliSec(int s) throws overflow_error
	{
	    if (s<0) throw new overflow_error();
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

	public void TogliMin(int m) throws overflow_error
	{
	    if (m<0) throw new overflow_error();
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

	public void TogliOra(int o) throws overflow_error
	{
	    if (o<0) throw  new overflow_error();
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

	public static int ConvertiInOredate(int giorni,int ore) throws overflow_error//modificarla passando anche le ore lavorative
	{
	    if(giorni<=0)
	        throw new overflow_error();
	    else
	        return giorni*ore;
	}

	public int formato()
	{
	    if(getOra()>12)
	        return getOra()%12;
	    else
	        return getOra();
	}

	//SOMMA TRA ORARI
	public orario SommaOrario(orario  o1) throws overflow_error 
	{
		if(o1.getSecTot()==0) return new orario(this);
	    orario o2=new orario();
	    if(sec+o1.getSecTot()>=86400)
	        o2.sec=(sec+o1.getSecTot())%86400;
	    else
	        o2.sec=sec+o1.getSecTot();
	  return o2;
	}
	public orario SubOrario(orario  o1) throws overflow_error 
	{
		if(o1.getSecTot()==0) return new orario(this);
	    orario o2=new orario();
	    if(o1.maggioreDi(this))
	    {
	        if(sec==0)
	        {
	            o2.sec=86400-(o1.getSecTot());
	        }
	        else
	        {
	            o2.sec=86400-(o1.getSecTot()%sec);

	        }

	    }
	    else
	        o2.sec=sec-o1.getSecTot();
	    return o2;
	}

	public int getOra() 
	{
	    return sec/3600;
	}
	public int getMin() 
	{
	    return (sec/60)%60;
	}
	public int getSec() 
	{
	    return sec%60;
	}

	public int getSecTot() 
	{
	    return sec;
	}


	public void aggiornaSec(int s)
	{
	    sec=s;
	}
	
	public void print() {
		
		System.out.println(getOra()+":"+getMin()+":"+getSec());
	}
	public boolean maggioreDi(orario o1) {
		
		 if(getSecTot()> o1.getSecTot())
		        return true;
		    else
		        return false;
	}

}
