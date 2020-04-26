package paystation.domain;

public class ProgressiveStrategyImpl implements RateStrategy {

    @Override
    public int calculateTime(int moneyInserted) {
        int timeBought = 0; //local variable used for return value

        //first check if money inserted will be in third hour
        if (moneyInserted >= 350) {

            moneyInserted = moneyInserted - 350;

            timeBought = 120 + moneyInserted / 5;

            //code logic here if moneyInserted < 350 (3rd hour) and if moneyInserted > 150 (2nd hour)
            //checked for between 1hour(60minutes) and 2hour(120 minutes) range
        } else if (moneyInserted >= 150) {

            moneyInserted = moneyInserted - 150;

            timeBought = 60 + moneyInserted / 10 * 3;
            //will check here if moneyInserted < 150 , the first hour logic which is linear    
        } else {

            timeBought = moneyInserted / 5 * 2;
        }
        return timeBought;

    }//end calculateTime()

}//end class progStrat
