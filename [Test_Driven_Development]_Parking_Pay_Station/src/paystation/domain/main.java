package paystation.domain;
import java.util.*;
import java.util.Scanner;  // Import the Scanner class

public class main {
	
	public static void main(String args[]) throws IllegalCoinException{
	    
	    PayStationImpl ps = new PayStationImpl();
	    ps.setRateStrategy(1);
	    Scanner kb = new Scanner(System.in); //used to capture input from main
	    
	    while (true) {
	    	//menu options
            System.out.println("Choose an option from below:");
            System.out.println(" 1: Deposit Coin\n 2: Display\n 3: Buy Ticket\n 4: Cancel \n 5: ChangeRS");
		    System.out.print(">  ");
		    int choice = kb.nextInt();
		    // switch case
		    switch (choice) {
		        case 1:
		        	System.out.println("------------------------------------------");
		        	System.out.println("Enter amount you want to deposit? ");
		            System.out.println("Only accept: 5 cents, 10 cents, 25 cents");
		            //let method handle calculation
		            ps.addPayment(kb.nextInt());
		        	System.out.println("------------------------------------------");
		            break;
		        case 2:
		        	System.out.println("------------------------------------------");
		        	System.out.println(" You have " + ps.readDisplay() + " minutes");
		        	System.out.println("------------------------------------------");
		        	break;		
		        case 3:
		        	System.out.println("------------------------------------------");
                    System.out.println(" RECEIPT: " + ps.buy().value() + " minutes");
		        	System.out.println("------------------------------------------");
		            break;
		        case 4:
		        	System.out.println("------------------------------------------");
		        	System.out.println("All previous transactions cancelled.");
		        	System.out.println("Discharging: " + ps.empty());
		        	Map<Integer, Integer> map = ps.cancel();
		        	Iterator<Integer> itr = map.keySet().iterator();

		    		// For-each Loop
		    		for (Integer key : map.keySet()) {
		    			System.out.println("Coin type " + key + " : " + map.get(key));
		    		}
		        	System.out.println("------------------------------------------");
 		            break;
		        case 5:
		        	System.out.println("------------------------------------------");
		        	System.out.println("What town:\t 1:Alpha\t 2:Beta\t 3:Gamma");

                    int rsChoice = kb.nextInt();
                    while (rsChoice != 1 && rsChoice != 2 && rsChoice != 3) {
                    	System.out.println("INVALID town.");
                    	rsChoice = kb.nextInt();
                    }

	                System.out.println("You picked: " + rsChoice);
	                ps.setRateStrategy(rsChoice);
		        	System.out.println("//------------------------------------------//");
                    break;
		    }
	    }
	}
}//end class
