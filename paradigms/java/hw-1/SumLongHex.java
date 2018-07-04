/* Feder Evgeniy, @dzaba, 08.02.2017 */
public class SumLongHex {
	/* Start function of programme */
	public static void main(String[] args) {
		long sum = 0;

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
				if (curStr.length() > beginInd + 2 && curStr.substring(beginInd, beginInd + 2).toLowerCase().startsWith("0x")) {
					sum += Long.parseUnsignedLong(curStr.substring(beginInd + 2, curInd), 16);
				}
				else
					sum += Long.parseLong(curStr.substring(beginInd, curInd));
			}
		}
		System.out.println(sum);
	} /* End of 'main' function */
} /* End of 'Sum' class */