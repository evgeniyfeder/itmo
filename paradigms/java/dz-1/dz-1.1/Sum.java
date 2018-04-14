/* Feder Evgeniy, @dzaba, 08.02.2017 */
public class Sum {
	/* Start function of programme */
	public static void main(String[] args) {
		int sum = 0;

		for (int indArgs = 0; indArgs < args.length; indArgs++) {
			String curStr = args[indArgs].trim();
			int curInd = 0;

			/* Search numbers in string */
			while (curInd < curStr.length()) {
				/* Miss whitespaces */
				if (Character.isWhitespace(curStr.charAt(curInd))) {
					curInd++;
					continue;
				}

				/* Create number */
				int beginInd = curInd;				
				while (curInd < curStr.length() && 
							   !Character.isWhitespace(curStr.charAt(curInd))) {
					curInd++;
				}

				/* Add number */
				sum += Integer.parseInt(curStr.substring(beginInd, curInd));
			}
		}
		System.out.println(sum);
	} /* End of 'main' function */
} /* End of 'Sum' class */