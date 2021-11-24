/**
 * shape : 모양에 해당한다
 * number : 카드의 숫자에 해당하며, J, Q, K 는 각각 11, 12, 13에 대응된다
 * CardShape : 카드의 모양을 나타낸다. enum으로 정의된다.
 */
public class Card {
	// 카드의 모양을 의미하며, 각각 하트, 스페이드, 다이아, 클로버 모양을 나타낸다.
	public enum CardShape{
		heart,
		spade,
		dia,
		clover
	}
	
	/**
	 * 카드의 모양을 나타내는 멤버 변수
	 */
	private CardShape shape;
	/**
	 * 카드의 숫자를 나타내는 멤버 변수
	 */
	private int number;
	
	public Card(int cardnum, int number)
	{
		this.setCard(cardnum, number);
	}
	
	/**
	 * 카드의 모양 및 숫자를 변경하는 setter 함수
	 * 편의성을 위해 CardShape 자체를 사용하지 않는다.
	 */
	public void setCard(int cardnum, int number)
	{
		switch(cardnum)
		{
		case 0:
			this.shape = CardShape.heart;
			break;
		case 1:
			this.shape = CardShape.spade;
			break;
		case 2:
			this.shape = CardShape.dia;
			break;
		case 3:
			this.shape = CardShape.clover;
			break;
		}
		this.number = number;
	}
	
	/**
	 * 카드의 모양을 돌려주는 getter 함수
	 */ 
	public CardShape getShape()
	{
		return this.shape;
	}
	/**
	 * 카드의 숫자를 돌려주는 getter 함수
	 */ 
	public int getNumber()
	{
		return this.number;
	}
	
	/**
	 * 현재 카드 정보를 string으로 반환한다.
	 */
	public String show()
	{
		return String.format("[%6s%3d]", shape,number);
	}
}
