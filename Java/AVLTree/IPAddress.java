package dns_resolver;

import java.util.Iterator;

/**
 * The IPAddress is using iIPv4 and has dotted-decimal notation, with the network, two subnets, 
 * and host separated by periods. For example, the IP address 130.191.226.146 has 
 * a network of 130, a subnet of 191, the second subnet is 226, and the host address is 146.
 * 
 * Your IPAddress class should accept a string of dotted-decimal IPAddresses in the constructor
 * and separate them into the components. 
 *
 * Note: The templates for some methods have been provided, but you should consider which additional
 * methods to add to this class.
 * 
 * @see <a href="https://en.wikipedia.org/wiki/IP_address#IPv4_addresses">Wikipedia IPv4 addresses</a>
 * @author CS310
 *
 */

public class IPAddress implements Comparable<IPAddress> {

	private String ipaddress;
	private int network, subnet, subnet2, host;

	/**
	 * The constructor for the IPAddress class
	 * IP address split into string array then assigned and converted into each int element
	 * @param ip the dotted-decimal IP address
	 */
	public IPAddress(String ip) {
		ipaddress = ip;
		String data[] = ip.split("\\.");
		network = Integer.valueOf(data[0]);
		subnet = Integer.valueOf(data[1]);
		subnet2 = Integer.valueOf(data[2]);
		host = Integer.valueOf(data[3]);		
	}


	@Override
	public int hashCode() {
		//TODO write this method!
		int sum = 0;
		for(String s:ipaddress.split("\\.")) {
			sum = Integer.parseInt(s);
		}
		return sum;
	}

	@Override
	public boolean equals(Object obj) {
		//TODO write this method!
		if(obj == null)
			return false;
		IPAddress tmp = (IPAddress) obj;
		return ipaddress.equals(tmp.ipaddress);  
	}

	@Override
	public String toString() {
		//TODO write this method!
		return "IPAddress is: " + ipaddress;
	}

	@Override
	public int compareTo(IPAddress ip) {
		// TODO write this method!
		return ipaddress.compareTo(ip.ipaddress); 
	}

}
