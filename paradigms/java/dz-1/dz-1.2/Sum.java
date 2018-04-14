/* Feder Evgeniy, @dzaba, 08.02.2017 */
public class Sum {
	/* Start function of programme */
	public static void main(String[] args) {
		int sum = 0;

		for (int indArgs = 0; indArgs < args.length; indArgs++) {
			String curStr = args[indArgs].trim();
			int isNum = 0, beginInd = 0;

			/* Search numbers in string */
			for(int curInd = 0; curInd < curStr.length(); curInd++) {
				/* Miss whitespaces */
				if (Character.isWhitespace(curStr.charAt(curInd)) && isNum == 1) {
					sum += Integer.parseInt(curStr.substring(beginInd, curInd));
					isNum = 0;	
				}
				else if (!Character.isWhitespace(curStr.charAt(curInd)) && isNum == 0) {
					isNum = 1;
				  beginInd = curInd;
				}
			}
			/* check if we haven't whitespace at the end */
			if (isNum == 1)
				sum += Integer.parseInt(curStr.substring(beginInd, curStr.length()));	
		}
		System.out.println(sum);
	} /* End of 'main' function */
} /* End of 'Sum' class */