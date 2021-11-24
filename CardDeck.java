import java.util.ArrayList;
import java.util.Collections;

public class CardDeck {
	private ArrayList<Card> card_deck;

	public CardDeck()
	{
		Init(true);
	}
	public CardDeck(boolean make_deck)
	{
		Init(make_deck);
	}
	public void Init(boolean make_deck)
	{
		this.card_deck = new ArrayList<Card>();
		if(make_deck)
		{
			this.MakeCardDeck();
			this.shuffle();
		}
	}
	
	/**
	 * 카드의 덱을 채웁니다.
	 * 현재는 트럼프 카드를 전제로 하지만, 다른 카드 방식이 발생할 수 있다면 이를 다르게 만들 수 있습니다.
	 */
	private void MakeCardDeck()
	{
		for(int i = 0; i < 4; i++) // i : 모양을 정의
		{
			for(int j = 0; j < 13; j++) // j : 숫자를 정의
			{
				Card card = new Card(i, j+1);
				card_deck.add(card); // 덱에 카드를 넣는다.
			}
		}
	}
	
	public void shuffle() // 카드를 섞는다.
	{
		Collections.shuffle(this.card_deck);
	}
	
	/**
	 * 
	 * @param p : 플레이어
	 * @param card_deck : 플레이어가 카드를 뽑을 덱
	 * @param count : 뽑을 카드의 수.
	 */
	public void userGetCard(Player p, int count)
	{
		boolean hasCard = (card_deck.size() != 0); // 카드 덱이 비었는지 여부
		
		if(!hasCard) //덱에 더이상 카드가 없다면 소진했다고 표시.
		{
			System.out.println("덱의 모든 카드를 소진했습니다");
			return;
		}
		
		while(count > 0 && hasCard) // 카드가 텅 비거나, 정해진 개수만큼 뽑았을 때 탈출
		{
			hasCard = p.Card_draw(this); // 카드를 뽑는다
			//System.out.printf("|남은 드로우 수 %d|[%s]이/가 카드를 뽑았습니다! \n", count, p.getName());
			count--;
		}
	}
	
	/**
	 * 
	 * @return 남은 카드가 있다면 카드를, 없다면 null을 반환한다.
	 */
	public Card getOneCard()
	{
		int remain_card = card_deck.size();
		if(remain_card == 0)
		{
			return null;
		}
		return card_deck.remove(0);
	}
	
	public void showAllCard() {
		for(var card : this.card_deck)
		{
			System.out.printf("[%2d] : ", card);
			System.out.print(card.show()+" ");
		}//카드가 삽입된 모습을 봅니다.
		System.out.println();
	}

	public static void showAllCard(ArrayList<Card> deck) {
		for(var card : deck)
		{
			System.out.print(card.show()+" ");
		}//카드가 삽입된 모습을 봅니다.
		System.out.println();
	}
	/**
	 * @param card 패에 다시 넣을 카드.
	 */
	public void pushCard(Card card) {
		card_deck.add(card);//카드를 arraylist 맨 뒤에 넣는다.
	}
}
