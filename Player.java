import java.util.ArrayList;

@FunctionalInterface
interface CardConditionFunc {
	public abstract boolean check(Card elem);
}

public class Player {
	//2018112070 이희준 6주차 코드
	private String name;
	private int age;
	private String  job;
	private ArrayList<Card> cardDeck = new ArrayList<Card>();
	
	public Player(String name, int age, String job)
	{
		this.Init(name,age,job);
	}
	
	/**
	 * 이름을 지정한다
	 * @param name : player의 이름
	 * 
	 * 단 한번만 실행해야 한다!
	 */
	private void Init(String name, int age, String job)
	{
		this.cardDeck = new ArrayList<Card>();
		this.name = name;
		this.age = age;
		this.job = job;
	}
	
	public String getName()
	{
		return this.name;
	}
	/**
	 * card_deck으로부터 카드를 한장 가져온다
	 * @param card_deck : 카드를 가져올 카드 덱.
	 * 						카드를 뽑은 후 cardDeck에 집어넣는다.
	 */
	public boolean Card_draw(CardDeck card_deck)
	{
		Card selected_card = card_deck.getOneCard(); // card_deck에서 카드를 꺼낸다.
		if(selected_card != null) //카드가 실제로 존재할 때
		{
			this.cardDeck.add(selected_card);//꺼낸 카드를 player의 카드 덱에 넣는다.
			return true;
		}
		else
		{
			return false;
		}
		
	}
	
	/**
	 * 
	 * @return 남은 카드의 수
	 */
	public int remain_card()
	{
		return this.cardDeck.size();
	}
	/**
     * 
     * @param shape     찾는 카드 모양
     * @param number    찾는 카드의 숫자
     * @return          해당 카드가 있는지 여부 반환
     */
    public boolean have_card(Card.CardShape shape, int number)
    {
        for(var elem : cardDeck)
        {
            if(elem.getShape() == shape && elem.getNumber() == number)
            {
                return true;
            }
        }

        return false;
    }

	/**
	 * 
	 * @param index 반환할 카드의 인덱스
	 * @return		반환되는 카드.
	 */
	public Card submitCard(int index)
	{
		Card card = cardDeck.remove(index);
		return card;
	}
	
	/**
	 * 가지고 있는 카드를 인덱스 정보와 함께 보여준다.
	 * 카드는 1줄에 최대 6개씩 보여준다.
	 */
	public void showCards()
	{
		final int colCount = 6; // 최대 열의 개수 
		if(cardDeck.size() == 0)
		{
			System.out.println("가진 카드가 없습니다.");
			return;
		}
		for(int i = 0; i < cardDeck.size(); i++)
		{
			if(i%colCount == 0)
			{
				System.out.println();
			}
			System.out.printf("(%d)%s\t", i,cardDeck.get(i).show()); //인덱스, 카드정보
		}
	}
	public Card showCardInfo(int index)
	{
		return cardDeck.get(index);
	}
	
	public void showPlayerInfo()
	{
		System.out.printf("이름: %s, 나이: %d, 직업: %s\n", name, age, job);
	}

	public boolean cardAll(CardConditionFunc func)
	{
		for(var elem: cardDeck)
		{
			if (func.check(elem) == false)
				return false;
		}
		return true;
	}
}