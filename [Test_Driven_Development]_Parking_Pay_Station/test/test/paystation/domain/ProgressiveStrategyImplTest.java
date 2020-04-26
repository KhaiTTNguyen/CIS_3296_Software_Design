package test.paystation.domain;

import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.Before;
import paystation.domain.*;

public class ProgressiveStrategyImplTest {

    private RateStrategy rs; //set up instance of RateStrategy

    @Before
    public void setUp() {
        rs = new ProgressiveStrategyImpl();
    }//end before setUp()

    //*********Testing for < first hour(s)**************************************
    @Test
    public void shouldReturn50For125Coins() {
        assertEquals("$1.25 in coin values is 50 minutes", 50,
                rs.calculateTime(125));
    }//end Test $1.25 return 50 minutes

    @Test
    public void shouldReturn0For0Coins() {
        assertEquals("$0.00 in coin values is 0 minutes", 0,
                rs.calculateTime(0));
    }//end Test $0.00 return 0 minutes

    @Test
    public void shouldReturn60For150Coins() {
        assertEquals("$1.50 in coin values is 60 minutes", 60,
                rs.calculateTime(150));
    }//end Test $1.50 return 60 minutes

//*********Testing for < second hour(s)+ *****************************************
    //Based on the math from ProgStratImpl, these values should return correct
    @Test
    public void shouldReturn66For175Coins() {
        assertEquals("$1.75 in coin values is 66 minutes", 66,
                rs.calculateTime(175));
    }//end Test $1.75 return 66 minutes

    @Test
    public void shouldReturn75For200Coins() {
        assertEquals("$2.00 in coin values is 75 minutes", 75,
                rs.calculateTime(200));
    }//end Test $2.00 return 75 minutes

    @Test
    public void shouldReturn63For160Coins() {
        assertEquals("$1.60 in coin values is 63 minutes", 63,
                rs.calculateTime(160));
    }//end Test $1.60 return 63 minutes

//*********Testing for < third hour(s)+ *****************************************
    @Test
    public void shouldReturn120For350Coins() {
        assertEquals("$3.50 in coin values is 120 minutes", 120,
                rs.calculateTime(350));
    }//end Test $3.50 return 120 minutes

    @Test
    public void shouldReturn194For720Coins() {
        assertEquals("$7.20 in coin values is 194 minutes", 194,
                rs.calculateTime(720));
    }//end Test $7.20 return 194 minutes

    @Test
    public void shouldReturn130For400Coins() {
        assertEquals("$7.20 in coin values is 194 minutes", 130,
                rs.calculateTime(400));
    }//end Test $4.00 return 130 minutes

}//end class ProgStratImplTest
