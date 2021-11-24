import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

/**
 * @author HJ-Lee 
 *         
 *         트럼프 카드를 생성한다 2명의 유저 -> 10장씩 뽑는다 남아있는 카드 중 한장을 공개한다. random 함수를
 *         이용하여 순서를 정한다(ArrayList에 넣는 순서) 공개된 카드 모양 혹은 숫자가 일칳면 카드를 낸다. 낼 카드가 없으면
 *         공개된 카드 중 랜덤하게 뽑는다. 낼 카드가 있으면 한장 뽑거나, 한장을 낸다.
 * 
 */

public class CardGame {
    private ArrayList<Player> players; // 플레이어
    private CardDeck card_deck; // 카드 덱
    private CardDeck remain_card_deck;
    private static int num_player = 0;
    private static int num_card = 0;

    private InputHelper helper;

    public CardGame() {
        helper = new InputHelper(); // input 도와주는 함수.
        System.out.println("게임 시작!");
        players = new ArrayList<Player>();
        card_deck = new CardDeck();
        remain_card_deck = new CardDeck(false);
        initGame(); // 플레이어를 설정한다.
    }

    public static void main(String[] args) {
        var game = new CardGame();
        int idx = game.PlayGame();
        Player winner = game.players.get(idx);
        System.out.println("유저" + winner.getName() + "의 승리입니다!");
    }

    /**
     * 
     * @return 승자의 index
     */
    private int PlayGame() {
        var player_score = new HashMap<Player, Integer>();
        setPlayerScore(player_score);

        System.out.println("playgame");

        for (int index = 0; index < num_player; index++) {
            Player p = players.get(index);
            player_score.put(p, 0); // 초기 점수를 초기화한다.
        }

        int num_round = 1;

        while (true) {// 각 게임 한판에 대응된다.
            System.out.printf("\n[%d 번째 라운드]\n", num_round);
            var round_player_score = new HashMap<Player, Integer>();
            setPlayerScore(round_player_score);
            // 현재 라운드에서 플레이어가 가지는 스코어
            selectOrder(); // 플레이어를 랜덤으로 섞는다.
            printOrder(); // 플레이어를 순서대로 출력한다.
            initRound(); // 게임 초기화
            boolean can_submit_heart = false;
            // 각 판을 낼 수 있는지 여부.

            var Q_conditions = new HashMap<Player, Integer>(); // Q를 4장 가지면 이기는데, 이 조건에 사용되는 값.
            setPlayerScore(Q_conditions);

            /** 1번의 트릭에 대응된다. */
            for (int trick = 0; trick < CardGame.num_card; trick++)
            {
                System.out.printf("\n[%d번째 트릭]\n", trick + 1);
                var cards = new ArrayList<Card>(); // 1 턴에 발생하는 카드

                for (int index = 0; index < num_player; index++) // 모든 유저가 카드를 선택한다.
                {
                    Player p = players.get(index); // 현재 유저 p
                    Card card;
                    if(index == 0 && !can_submit_heart && p.cardAll((c) -> c.getShape() == Card.CardShape.heart)) // 첫 유저가 heart를 낼 수 없는 상황에 heart 밖에 없다면...
                    {
                        showOpenedCards(cards);
                        showCurrentState(p); // 선택지를 보여준다.
                        card = p.submitCard(0); // 패에 존재하는 첫번째 카드를 무조건 낸다.
                        System.out.printf("선택 가능한 카드가 없으므로, 첫번째 카드인 %s를 제출합니다.", card.show());
                    }
                    else {
                        card = playerChoose(p, cards, can_submit_heart);
                    }

                    if (card.getNumber() == 12) // 이번에 꺼낸 카드가 Q라면, 컨디션 번호를 1 증가시킨다.
                    {
                        setPlayerScore(Q_conditions, p, 1);
                    }

                    if (Q_conditions.get(p) == 4) // Q 4장을 얻는다면 이런 결과가 나옴.
                    {
                        System.out.printf("\n[%s가 Q를 4개 뽑았습니다!]\n",p.getName());
                        return index; // 현재 인덱스에 해당하는 사람이 승자이므로, 이 인덱스를 반환한다.
                    }

                    cards.add(card);
                    can_submit_heart = true; // 첫 사람이 아니라면, 반드시 can_submit_heart는 참
                }

                int idx_loser = checkLoser(cards); // 현재 트릭에서의 패배자의 인덱스를 얻는다.
                int score = calculateScore(cards); // 패배자의 점수에 더할 값.
                setPlayerScore(round_player_score, players.get(idx_loser), score); // 패배자의 점수에 더한다.
                System.out.printf("[%s가 패를 가져갑니다]\n", players.get(idx_loser).getName());
                // 다음 트릭에 하트를 낼 수 있는지 여부를 초기화한다.
                can_submit_heart = canSubmitHeart(cards);
                setOrder(idx_loser);// 해당 트릭의 패배자의 인덱스에 대해서 순서를 재설정한다.

                for(var elem: cards)
                {
                    remain_card_deck.pushCard(elem);// 현재 얻은 카드들은 remain_card_deck에 넣는다.
                }
            }

            boolean is_game_end = false;
            int winner_idx = 0;

            // 한 라운드에서 생성된 점수를 더한다.
            for(int i = 0; i < players.size(); i++)
            {
                var p = players.get(i);
                setPlayerScore(player_score,p,round_player_score.get(p));

                if(player_score.get(p) > 30) // 누군가 30점을 넘기면
                {
                    is_game_end = true; // 게임 끝.
                }
                if(player_score.get(p) < player_score.get(players.get(winner_idx))) // 승자의 점수보다 현재 점수가 더 작다면 -> 현재 플레이어가 승자
                {
                    winner_idx = i;
                }
            }

            // 플레이어의 점수를 출력한다.
            System.out.println("현재까지의 점수");
            for(var p : players)
            {
                System.out.printf("[%s] : %d (+ %d)\n", p.getName(), player_score.get(p), round_player_score.get(p));
            }

            if(is_game_end) return winner_idx; // 게임이 끝났다면, 인덱스를 반환

            Card temp = remain_card_deck.getOneCard(); // 원래 카드 덱을 다시 만든다.
            while(temp != null)
            {
                card_deck.pushCard(temp);
                temp = remain_card_deck.getOneCard();
            }
            num_round++;
        }
    }

    /**
     * 플레이어의 점수를 0으로 설정한다
     * 
     * @param scores // 점수가 저장되는 공간
     */
    private void setPlayerScore(HashMap<Player, Integer> scores) {
        for (var p : players) {
            scores.put(p, 0); // 처음에는 항상 0.
        }
    }

    /**
     * 주어진 점수를 플레이어 점수에 더한다
     * 
     * @param scores 점수가 저장되는 공간
     * @param p      점수를 더할 플레이어
     * @param score  더할 점수
     */
    private void setPlayerScore(HashMap<Player, Integer> scores, Player p, int score) {
        scores.put(p, scores.get(p) + score);
    }

    private int calculateScore(ArrayList<Card> cards) {
        int score = 0;
        for (var elem : cards) {
            if (elem.getShape() == Card.CardShape.heart) // 카드가 하트면
            {
                score += 1; // 점수 1
            } else if (elem.getShape() == Card.CardShape.spade) // 카드 모양이 스페이드면
            {
                if (elem.getNumber() == 1) // 스페이드 A 이면
                {
                    score += 5;
                } else if (elem.getNumber() == 12) // 스페이드 Q 이면
                {
                    score += 3;
                }
            }
        }

        return score;
    }

    /**
     * 
     * @param cards 평가 대상이 되는 카드들
     * @return 한 트릭에서의 패배자의 인덱스
     */
    private int checkLoser(ArrayList<Card> cards) {
        int idx_loser = 0; // 초기의 패배자는 맨 처음 낸 사람
        for (int i = 1; i < cards.size(); i++) {
            Card cur = cards.get(i);
            Card loser = cards.get(idx_loser);
            if (cur.getShape() == loser.getShape()// 현재 카드의 모양이 현재 패배자의 모양과 같다면
                    && getScore(cur) > getScore(loser)) // 현재 카드가 패배자의 카드보다 높은 스코어라면
                idx_loser = i;
        }

        return idx_loser;
    }

    private boolean canSubmitHeart(ArrayList<Card> cards) {
        for (var elem : cards) {
            if (elem.getShape() == Card.CardShape.heart)
                return true;
        }
        return false;
    }

    /**
     * 해당 카드와 관련된 점수를 반환한다.
     * @param card 현재 카드 
     * @return 카드에 해당하는 점수.
     */
    private int getScore(Card card) {
        switch (card.getNumber()) {
        case 1:
            return 13; // A 이면 13점을 반환. A가 최대 점수.
        default:
            return card.getNumber() - 1; //
        }
    }

    /**
     * @param player 현재 선택하는 플레이어 플레이어가 낼 카드가 있다면 선택지를 준다. 없다면 해당 게임을 종료한다.
     * @param can_submit_heart 하트를 낼 수 있는지 여부
     * @return Card 플레이어가 선택한 카드.
     */
    public Card playerChoose(Player player, ArrayList<Card> cards, boolean can_submit_heart) {
        // 카드를 낼 수 있는지 보고, 못내면 해당 게임 종료
        System.out.print("\n[플레이어 " + player.getName() + "]");// 현 유저

        while (true) {
            showOpenedCards(cards);
            showCurrentState(player); // 선택지를 보여준다.
            int idx = -1;
            idx = helper.getInt();
            if (idx < player.remain_card() && idx >= 0) // 존재하는 카드라면
            {
                if (can_submit_heart) // 하트도 낼 수 있다면
                {
                    return player.submitCard(idx); // 그냥 반환한다.
                } else { // 하트는 낼 수 없다면
                    if (player.showCardInfo(idx).getShape() != Card.CardShape.heart) // 해당 카드가 하트가 아니면
                    {
                        return player.submitCard(idx);
                    } else {
                        System.out.println("해당 카드는 현재 낼 수 없습니다.");
                    }
                }
            } else // 존재하지 않는 카드(잘못된 인덱스)
            {
                System.out.println("해당 카드를 가지고 있지 않습니다.");
                continue;
            }
        }
    }

    /**
     * 플레이어를 생성, 해당 정보를 알려준다.
     */
    private void initGame() {
        setPlayers(); // 플레이어의 정보를 초기화
        System.out.println("플레이어의 수 : " + CardGame.num_player);
    }

    /**
     * 현재 라운드의 카드 정보를 초기화한다.
     */
    private void initRound() {
        SetCardDeck(CardGame.num_card); // 남는 카드는 remain_card_deck에 넣는다.
        card_deck.shuffle();// 카드 덱을 한번 섞는다.

        for (Player p : players) {
            card_deck.userGetCard(p, CardGame.num_card);
        } // 유저들은 카드를 가진다.
        setOrder(); // 플레이어 순서를 지정한다.
    }

    /**
	 * 여러 유저 사이의 순서를 정한다. 
	 * 랜덤으로 생성된 0~ 1 사이의 값에 따라 이미 들어간 플레이어의 순서를 바꾼다.
	 * [0	1	2	3] // 4개의 숫자를 상대로 random
	 * 1	[0	2	3] // 3개의 숫자를 상대로 random
	 * 1	3	[0	2] // 2개의 숫자를 상대로 random
	 * Collections.swap을 사용한다.
	 */
	private void selectOrder() 
	{
		for(int i = 0; i < CardGame.num_player - 1; i++) // 마지막 전 사람까지
		{
			int rest  = CardGame.num_player - i; // 남은 사람 수.
			var rand = Math.random();
			int selected = (int)(rest * rand) + i;
			Collections.swap(players, i, selected);
		}
        
	}

    private void printOrder(){
        System.out.println("[현재 라운드에서의 유저들이 앉은 순서]");
        
        for(int i = 0 ; i < players.size(); i++)
        {

            players.get(i).showPlayerInfo();
        }
    }

    /**
     * 플레이어의 순서를 지정하는 메서드 1. 변수가 없다면, 클로버 2를 가진 사람이 등장할 때까지 계속 플레이어를 넣고 뺀다 2. 변수가
     * 있다면, 해당 인덱스만큼 for문을 돌려 플레이어 순서를 맞춘다.
     */
    private void setOrder() {
        while (true) {
            Player p = players.get(0);
            if (!p.have_card(Card.CardShape.clover, 2)) { // 해당 플레이어가 클로버 2가 없다면
                players.remove(0); // 맨 앞의 p를 빼서
                players.add(p); // 맨 뒤로 넣는다.
            } else { // 해당 플레이어가 클로버 2를 가진다면
                break; // 순서 설정을 종료한다.
            }
        }
    }

    private void setOrder(int index) {
        for (int i = 0; i < index; i++) {
            var temp = players.remove(0);
            players.add(temp);
        }
    }

    /**
     * remain_card_deck에 넣을 카드를 설정한다.
     */
    private void SetCardDeck(int num_card) {
        int num_dropped_card = 52 - num_player * num_card;
        // 버릴 카드의 수를 설정한다.
        // 카드를 실제로 버리되, 클로버 2라면 안버리고 섞고 다시 버린다.
        for (int i = 0; i < num_dropped_card; i++) {
            Card card = card_deck.getOneCard();
            while (card.getShape() == Card.CardShape.clover && card.getNumber() == 2) // 해당 카드가 클로버 2라면 계속.
            {
                card_deck.pushCard(card); // 카드를 다시 넣고
                card_deck.shuffle(); // 섞은 후
                card = card_deck.getOneCard();// 다시 한 장을 뽑는다
            }
            remain_card_deck.pushCard(card);
        }
    }

    /**
     * 플레이어 관련 정보를 설정하는 코드. 플레이어의 수(4~6), 플레이어의 정보(이름, 나이, 직업)
     */
    private void setPlayers() {
        System.out.println("게임 초기화...");
        setPlayerNum();

        for (int i = 0; i < CardGame.num_player; i++) {
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            System.out.println(i + "번째 플레이어의 정보 입력...");
            Player p = getNewPlayer(); // i + 1 번째 플레이어
            players.add(p);// 플레이어 넣기.
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        } // 플레이어를 정함
    }

    /**
     * 플레이어의 숫자를 CargGame.num_player으로 설정한다.
     */
    private void setPlayerNum() {
        int val = -1;
        while (true) {
            System.out.print("플레이어의 수를 입력하세요 (4 ~ 6) : ");
            val = helper.getInt();
            if (val < 4 || val > 6) {
                System.out.println("적절하지 않은 플레이어의 수입니다. 4 ~ 6 사이 숫자를 입력하세요\n");
                continue;
            }
            CardGame.num_player = val; // 플레이어의 숫자를 설정한다.
            CardGame.num_card = 52/CardGame.num_player;

            System.out.printf("플레이어의 숫자를 %d로 설정했습니다.\n", CardGame.num_player);
            break;
        }
    }

    /**
     * 
     * @return Player : 정보가 입력되고 생성된 플레이어 정보를 반환한다.
     */
    private Player getNewPlayer() {
        String name;
        int age;
        String job;

        System.out.print("이름 입력 :");
        name = helper.getString(); // 이름을 입력

        while (true) {
            System.out.print("나이 입력 : ");
            age = helper.getInt();
            if (age < 0) {
                System.out.println("나이는 0세 이상의 숫자만 지원됩니다.");
                continue;
            }
            break;
        }

        System.out.print("직업 입력 :");
        job = helper.getString(); // 직업을 입력

        return new Player(name, age, job);
    }

    /**
     * 현재 카드 정보를 출력한다
     * 
     * @param player 현재 플레이 중인 유저
     */
    private void showCurrentState(Player player) {
        System.out.println("\n[선택 가능한 카드들]");
        player.showCards();
        System.out.println();
    }

    private void showOpenedCards(ArrayList<Card> cards) {
        System.out.println("\n[현재 오픈된 카드들]");
        CardDeck.showAllCard(cards);
        System.out.print("\t");
    }
}