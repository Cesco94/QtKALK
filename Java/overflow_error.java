public class overflow_error extends Exception {
	
	private static final long serialVersionUID = 1L;

	public overflow_error() {}
	
	// Throwable.getMessage()
	public String getReason() { return "Intero selezionato non permesso"; }

}
