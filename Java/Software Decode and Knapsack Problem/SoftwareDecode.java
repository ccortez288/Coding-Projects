
class SoftwareDecode {
	/** Answer to 3,6 #3
	 * takes in a data array and creates 3 variables
	 * loops through and compares them to each other to find if they fit the 
	 * +20 conditions, then returns the elements # where it starts which
	 * is "i"
	 * */
	public int softwareDecode(int data[]) {
		for(int i = 0; i < data.length;++i) {
			for(int j = i +1; j < data.length; ++j) {
				for(int k = j+1; k < data.length;++k) {
					if ((data[i]) + 20 == data[j] && (data[j] + 20 == data[k]))
						return i;
				}
			}
		}

		return -1; 
	}

	/** Answer to 3.6 #4
	 * Basically the same concept but with only 2 variables
	 * Checks if the two fit the condition pattern of +20
	 *  then it uses my private helper function to make sure it meets 
	 *  the other condition of not being =+/- 40 to any other element in the array
	 *  */
	public int softwareDecodeAlt(int data[]) {
		for(int i = 0; i < data.length;++i) {
			for(int j = i +1; j < data.length; ++j) {
				for(int k = 0; k < data.length; k++ ) {
					if ((data[i]) + 20 == data[j] && decodeHelper(i,data) == true )
						return i;
				}
			}
		}
		return -1; 
	}

	private static boolean decodeHelper(int n, int data[]) {
		for(int i = 0; i < data.length; i++) {
			if(data[i] + 40 == data[n] || data[i] - 40 == data[n]) {
				return false;
			}
		}
		return true;
	}
}
