/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paystation.domain;

/**
 *
 * @author Dumpus
 */
public interface RateStrategy {
    
	/**
     * @return timeBought based on moneyInserted
     */
    public int calculateTime(int moneyInserted);
    
}
