import java.lang.*;
public class use {

	public static void main(String[] args) {
		orario o=new orario();
		data d=new data();
		fusoorario f=new fusoorario();
		luna l=new luna();
		
		
		try {
			//funzionalita' orario
		      System.out.println("Operazioni orario");
		      o.aggiornaSec(10);
		      o.print();
		      int res=orario.ConvertiInOredate(12,4);
		      System.out.println(res);
		      o.SommaMin(4);
		      o.SommaSec(4);
		      o.SommaOra(4);
		      o.print();
		      o.TogliMin(4);
		      o.TogliSec(4);
		      o.TogliOra(4);
		      o.print();
		      o=o.SommaOrario(new orario(2,2,2));
		      o.print();
		      o=o.SubOrario(new orario(2,2,2));
		      o.print();
		      o.SommaOra(14);
		      res=o.formato();
		      System.out.println(res);
		      //funzionalita' fusoorario
		      System.out.println("Operazioni fusoorario");
		      res=fusoorario.dimmiFuso('R');
		      System.out.println(res);
		      res=f.fusodiff(new fusoorario(12));
		      System.out.println(res);
		      f.sommafuso(4);
		      f.Print();
		      f.toglifuso(4);
		      f.Print();
		      //funzionalita' data
		      System.out.println("Operazioni Data");
		      res=d.oreDiStudio(new data(14,1,2000,true), 3);
		      System.out.println(res);
		      d.cambiaAnno(2018);
		      d.cambiaEmis(false);
		      d.cambiaGiorno(12);
		      d.cambiaMese(1);
		      d.print();
		      res=d.durata(new data(21,12,2012,true));
		      System.out.println(res);
		      res=d.giorniMese(d.getMese());
		      System.out.println(res);
		      String s=d.giornoSettimana();
		      System.out.println(s);
		      res=d.settimanamese();
		      System.out.println(res);
		      res=d.settimanaanno();
		      System.out.println(res);
		      d.print();
		      d.indietroUnGiorno();
		      d.print();
		      d.indietroTotGiorni(3);
		      d.print();
		      d.avanzaUnGiorno();
		      d.print();
		      d.avanzaTotGiorni(2);
		      d.print();
		      s=d.stagione();
		      String r;
		      if(d.getEmisfero()==true)
		        r="Boreale";
		        else
		          r="Australe";
		      System.out.println("Emisfero"+r+" "+s);
		      res=d.countgiorni();
		      System.out.println(res);
		      boolean var=data.bisestile(2016);
		      if(var==true)
		        System.out.println("Era bisestile");
		      else
		        System.out.println("Non era bisestile");
		      var=data.bisestile(2015);
		      if(var==true)
		        System.out.println("Era bisestile");
		      else
		        System.out.println("Non era bisestile");
		      d.print();
		      d.SommaOra(25);
		      d.SommaMin(2);
		      d.SommaSec(2);
		      d.print();
		      d.TogliMin(25);
		      d.TogliOra(2);
		      d.TogliSec(2);
		      d.print();
			//funzionalita' luna
			System.out.println("Fase lunare attuale: "+l.getFase());
			System.out.println("Epatta dell'anno alla data corrente: "+l.epatta()+".");
			System.out.println("Prossima luna piena in "+l.prossimaPiena()+" giorni.");
			System.out.println("Prossima luna nuova in "+l.prossimaNuova()+" giorni.");
			System.out.println("Ultima luna piena e' stata "+l.ultimaPiena()+" giorni fa.");
			System.out.println("Ultima luna nuova e' stata "+l.ultimaNuova()+" giorni fa.");
			
		}
		catch(overflow_error e)
		{
			System.out.println(e.getReason());
		}

	}

}
