package Lab2;
import java.io.*;



public class DriverClass{
	private final static String COMMA_DELIMITER = ",";
	public static void main(String[] args) {
		graphLab graph = new graphLab();
		String s = "J,K,15";
		String data[] = s.split(",");
		graph.add(data[0],data[1],Integer.parseInt(data[2]));
		System.out.println(graph.numVerts() + "\n");
		System.out.println(graph.edgesToString() + "\n");
		System.out.println(graph.toString());
	}
}	

