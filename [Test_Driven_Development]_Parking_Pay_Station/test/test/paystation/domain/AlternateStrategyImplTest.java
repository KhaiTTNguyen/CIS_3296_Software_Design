package test.paystation.domain;

import static java.time.Clock.*;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.Before;
import paystation.domain.*;
import java.util.Calendar;
import java.util.Date;

public class AlternateStrategyImplTest {

    private AlternateRateHardCode rsHardCode;

    @Before
    public void setUp() {
        rsHardCode = new AlternateRateHardCode();
    }//end before setUp()

//************TEST REMARK: WEEKDAY = linear , WEEKEND = progressive*************  
    //Test for 0 coins on Sunday
    @Test
    public void shouldReturn0For0Coins() {
        assertEquals("$0.00 in coin values is 0 minutes", 0, rsHardCode.calculateTimeWithDay(0, 0));
    }//end Test $0.00 return 0 minutes

    //Test for 720 coins on Sunday
    @Test
    public void shouldReturn194For720CoinsWeekend() {
        assertEquals("$0.00 in coin values is 0 minutes", 194, rsHardCode.calculateTimeWithDay(720, 0));
    }//end Test $7.20 return 194 minutes Weekend

    //Test for 720 coints on weekday, Fails with day = {0,1,7} 
    @Test
    public void shouldReturn288For720CoinsWeekday() {
        assertEquals("$0.00 in coin values is 0 minutes", 288, rsHardCode.calculateTimeWithDay(720, 3));
    }//end Test $7.20 return 288 minutes Weekday
}//end AlternateRateStrategyTest
