import java.util.Arrays;
import java.util.Random;

public class HWTester {
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		SoftwareDecode test = new SoftwareDecode();
		KnapSack ksTester = new KnapSack();

		/**Testing for the Software Decoder problem */
		int data[] = {1,3,4,6,10,20};
		int data2[] = {10,15,20,30,40,60,90,100,200};

		System.out.println("Tests if neither pattern is found, should return -1 ");
		System.out.println("Answer to 3.6 #3: " + test.softwareDecode(data));
		System.out.println("Answer to 3.6 #4: " + test.softwareDecodeAlt(data) + "\n");

		System.out.println("Tests if both pattern detectors work ");
		System.out.println("Answer to 3.6 #3: " + test.softwareDecode(data2));
		System.out.println("Answer to 3.6 #4: " + test.softwareDecodeAlt(data2) + "\n");

		/**Testing for KnapSack Problem */
		int weightLim = 20;
		int length = 10;
		int weights[] = new int[length + 1];
		int values[] = new int[length + 1];
		Random randomNums = new Random();

		System.out.print("Testing with an array of length 10 and weight limit 20, arrays of values and weights ");
		System.out.println("are filled with random numbers.");
		for (int n = 1; n <= length ; n++) {
			values[n] = randomNums.nextInt(1000);
			weights[n] = randomNums.nextInt(weightLim);
		}
		System.out.println("Array of values: " + Arrays.toString(values));
		System.out.println("Array of weights: " +Arrays.toString(weights));
		System.out.println("Array of boolean values: " + Arrays.toString(ksTester.knapSack1(weightLim,length,weights,values)) + "\n");

		System.out.println("Testing for the other conditions(if length is 0 or 1, should return false for 0 and then true for 1");
		System.out.println("Array of boolean values: " + Arrays.toString(ksTester.knapSack1(weightLim,0,weights,values)));
		System.out.println("Array of boolean values: " + Arrays.toString(ksTester.knapSack1(weightLim,1,weights,values)));
	}
}
