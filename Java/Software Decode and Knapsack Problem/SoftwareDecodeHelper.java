public class SoftwareDecodeHelper {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
			int data[] = {1,3,4,6,10,20};
			int data2[] = {10,15,20,30,40,60,90,100,200};
			SoftwareDecode test = new SoftwareDecode();
			
			System.out.print("Tests if neither pattern is found, should return -1 ");
			System.out.println("Answer to 3.6 #3: " + test.softwareDecode(data));
			System.out.println("Answer to 3.6 #4: " + test.softwareDecodeAlt(data));
			
			System.out.print("Tests if both pattern detectors work ");
			System.out.println("Answer to 3.6 #3: " + test.softwareDecode(data2));
			System.out.println("Answer to 3.6 #4: " + test.softwareDecodeAlt(data2));
	}

}
