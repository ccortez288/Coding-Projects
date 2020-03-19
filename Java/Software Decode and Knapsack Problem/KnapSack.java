import java.util.Arrays;

class KnapSack {

	public boolean[] knapSack1(int weight, int length, int wts[], int vals[]) {
		boolean take[] = new boolean[length + 1]; // Used later for returning boolean values

		/**Returns an array full of false values if the length or weight is 0 */
		if(weight == 0 || length ==0) {
			Arrays.fill(take, Boolean.FALSE);
			return take;
		}

		/** Returns true if length is only 1 */
		if(length == 1) {
			boolean[] tmp = {true};
			return tmp;
		}

		/** ksHelper used to find max value of items with the given
		 * weight limit
		 * ksResolver used to give which items to include with given weight limit and given
		 * length
		 *  */
		int[][] ksHelper = new int[length+1][weight+1];
		boolean[][] ksResolver = new boolean[length+1][weight+1];

		for (int n = 1; n <= length; n++) {
			for (int w = 1; w <= weight; w++) {

				/**Item to not take, used for comparison in line 41-42*/
				int opt1 = ksHelper[n-1][w];

				/**Take in this item if the weight is less than the weight limit
				 * and use it as one of the options to compare */
				int opt2 = Integer.MIN_VALUE;
				if (wts[n] <= w) opt2 = vals[n] + ksHelper[n-1][w-wts[n]];

				/**Compare two options, use math.max to find max value between
				 * the two given options */
				ksHelper[n][w] = Math.max(opt1, opt2);
				ksResolver[n][w] = (opt2 > opt1);
			}
		}

		/**Used to find which values belong to maximize values (T/F)*/
		for (int n = length, w = weight; n > 0; n--) {
			if (ksResolver[n][w]) {
				take[n] = true;
				w = w - wts[n];
			}
			else {
				take[n] = false;
			}
		}

		return take;
	}
}
