package paystation.domain;

public class LinearStrategyImpl implements RateStrategy {

	@Override
	public int calculateTime(int moneyInserted) {
		return (moneyInserted * 2) / 5;
	}
}
