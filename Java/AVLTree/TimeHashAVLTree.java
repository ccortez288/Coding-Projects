package time_data_structures;

import data_structures.*;
import dns_resolver.*;
import java.util.HashMap;
import java.util.TreeMap;

/**Was not able to pass in the file data so instead tested with my own data sets
 * added manually strings and integers into the hashes */

public class TimeHashAVLTree {
	public static void main(String[] args)  {
		HashListI<IPAddress> list = new LinkedList<IPAddress>(); 
		AVLTreeI<Integer, Integer> list2 = new AVLTree<Integer, Integer>();
		HashI<String, Integer> list3 = new Hash<String, Integer>(50000);
		HashMap<String, Integer> list4 = new HashMap<String, Integer>();	
		TreeMap<Integer, Integer> list5 = new TreeMap<Integer, Integer>();

		/** 
		 Insertion Tests. Each data structure is timed and then the time differences are printed 
		 */
		System.out.println("Insertion Tests:"); 
		/**Insert into the hash*/
		long start = System.currentTimeMillis();

		list3.add("0", 5);
		list3.add("1", 6);
		list3.add("2", 7);
		list3.add("3", 8);
		list3.add("4", 9);
		list3.add("5", 10);
		list3.add("6", 11);
		list3.add("7", 12);
		list3.add("8", 13);
		list3.add("9", 14);
		long stop = System.currentTimeMillis();
		System.out.print("Time to add into my Hash: ");
		System.out.println((double)stop - (double)start);

		/**
		Insert into the AVLTree */

		start = System.currentTimeMillis();

		list2.add(12, 46);
		list2.add(13, 78);
		list2.add(16, 98);
		list2.add(17, 98);
		list2.add(18, 98);
		list2.add(19, 98);
		list2.add(20, 98);
		list2.add(21, 98);
		list2.add(22, 98);
		list2.add(23, 98);
		list2.add(24, 98);
		list2.add(25, 98);
		list2.add(26, 98);
		list2.add(27, 98);
		list2.add(28, 98);
		list2.add(29, 98);
		list2.add(30, 98);
		list2.add(31, 98);
		list2.add(32, 98);
		list2.add(33, 98);
		list2.add(34, 98);
		list2.add(35, 98);
		list2.add(36, 98);
		list2.add(37, 98);
		list2.add(38, 98);
		list2.add(39, 98);
		list2.add(40, 98);
		list2.add(41, 98);
		list2.add(42, 98);
		list2.add(43, 98);
		list2.add(44, 98);
		list2.add(45, 98);
		stop = System.currentTimeMillis();
		System.out.print("Time to add into my AVLTree: ");
		System.out.println((double)stop - (double)start); 

		/**Insert into the hashmap */
		start = System.currentTimeMillis();

		list4.put("0", 5);
		list4.put("1", 6);
		list4.put("2", 7);
		list4.put("3", 8);
		list4.put("4", 9);
		list4.put("5", 10);
		list4.put("6", 11);
		list4.put("7", 12);
		list4.put("8", 13);
		list4.put("9", 14);
		stop = System.currentTimeMillis();
		System.out.println("Time to add into JavaAPI HashMap: ");
		System.out.println((double)stop - (double)start);

		/**Insert into the treeMap */
		start = System.currentTimeMillis();

		for (Integer i = 0; i < 100;i++) {
			for(Integer j = 5;j < 105;j++) {
				list5.put(i, j);
			}
		}
		stop = System.currentTimeMillis();
		System.out.print("Time to add into JavaAPI TreeMap: ");
		System.out.println((double)stop - (double)start);

		/**End of insertion tests, moving onto searching tests */

		System.out.println("+++++++++++++++++++++++++++++++");
		System.out.println("Search Tests:");

		/**Searching the hash*/
		start = System.currentTimeMillis();
		list3.getValue("7");
		stop = System.currentTimeMillis();
		System.out.print("Time to search my Hash: ");
		System.out.println((double)stop - (double)start);
		System.out.println("Value retrieved:" + list3.getValue("7"));

		/**Searching the AVLTree*/
		start = System.currentTimeMillis();
		list2.getValue(12);
		stop = System.currentTimeMillis();
		System.out.print("Time to search my AVLTree: ");
		System.out.println((double)stop - (double)start);
		System.out.println("Value retrieved:" + list2.getValue(12));

		/**Searching the hashmap */
		start = System.currentTimeMillis();
		list4.get("7");
		stop = System.currentTimeMillis();
		System.out.println("Time to search JavaAPI HashMap: ");
		System.out.println((double)stop - (double)start);
		System.out.println("Value retrieved:" + list4.get("7"));

		/**Searching the treemap*/
		start = System.currentTimeMillis();
		list5.get(70);
		stop = System.currentTimeMillis();
		System.out.print("Time to search JavaAPI TreeMap: ");
		System.out.println((double)stop - (double)start); 
		System.out.println("Value retrieved:" + list5.get(70));
		System.out.println("End of tests");

		System.out.println(System.currentTimeMillis());
	}
}
