/*
 * This class was added in order to run test files with AlternateStratImplTest
 * The method is the same with the exception that there is an extra argument, "the day of the week"
 */
package paystation.domain;

public class AlternateRateHardCode extends AlternateStrategyImpl {

    //Overload method involves an extra ineger, to hardcode the "day" , 0 = Sunday, etc.
    public int calculateTimeWithDay(int moneyInserted, int day) {

        int day_in_week = day;

        // calculate rates
        if (2 <= day_in_week && day_in_week <= 6) {
            LinearStrategyImpl linearPay = new LinearStrategyImpl();
            return linearPay.calculateTime(moneyInserted);
        } else {
            ProgressiveStrategyImpl progPay = new ProgressiveStrategyImpl();
            return progPay.calculateTime(moneyInserted);
        }//end else

    }//end calculateTime(int moneyInserted)
}//end AltRateHardcode
