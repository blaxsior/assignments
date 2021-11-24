import java.util.Scanner;

public class InputHelper {
	private Scanner scanner;
	
	public InputHelper()
	{
		this.scanner = new Scanner(System.in);
	}
	
	public int getInt()
	{
		int val = 0;
		while(true)
		{
			try {
				 val = scanner.nextInt();
			}
			catch(Exception err) {
				scanner.nextLine();
				System.out.print("숫자를 입력해야합니다 : ");
				continue;
			}
			return val;
		}
	}
	
	public String getString()
	{
		return scanner.next();
	}
}