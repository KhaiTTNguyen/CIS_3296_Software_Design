package paystation.domain;

import java.util.Calendar;
import java.util.Date;

public class AlternateStrategyImpl implements RateStrategy {

    public int calculateTime(int moneyInserted) {

        // take system date
        Date now = new Date();
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(now);
        int day_in_week = calendar.get(Calendar.DAY_OF_WEEK); // the day of the week in numerical format

        // calculate rates
        if (2 <= day_in_week && day_in_week <= 6) {
            LinearStrategyImpl linearPay = new LinearStrategyImpl();
            return linearPay.calculateTime(moneyInserted);
        } else {
            ProgressiveStrategyImpl progPay = new ProgressiveStrategyImpl();
            return progPay.calculateTime(moneyInserted);
        }

    }//end calculateTime(int moneyInserted)

}//end class AltStratImpl
