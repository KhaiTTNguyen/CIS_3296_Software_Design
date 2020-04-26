package test.paystation.domain;

import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.Before;
import paystation.domain.*; 

public class LinearStrategyImplTest {

    private RateStrategy rs; //set up instance of RateStrategy

    @Before
    public void setUp() {
        rs = new LinearStrategyImpl();
    }//end before setUp()

    //Testing for entering 0 coins should return 0 minutes
    @Test
    public void shouldReturn0For0Coins() {
        assertEquals("$0.00 in coin values is 0 minutes", 0,
                rs.calculateTime(0));
    }//end Test $0.00 return 0 minutes

    //Testing for entering 5 coins should return 2 minutes
    @Test
    public void shouldReturn2For5Coins() {
        assertEquals("$0.05 in coin values is 2 minutes", 2,
                rs.calculateTime(5));
    }//end Test $0.05 return 2 minutes

    //Testing for entering 2500 coins should return 1000 minutes
    @Test
    public void shouldReturn1000For2500Coins() {
        assertEquals("$25.00 in coin values is 1000 minutes", 1000,
                rs.calculateTime(2500));
    }//end Test $25.00 return 1000 minutes

    //Testing for entering 105 coins should return 42 minutes
    @Test
    public void shouldReturn42For105Coins() {
        assertEquals("$1.05 in coin values is 42 minutes", 42,
                rs.calculateTime(105));
    }//end Test $1.05 return 42 minutes
}//end LinStratImplTest

