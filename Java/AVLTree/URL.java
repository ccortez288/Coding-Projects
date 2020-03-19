package dns_resolver;

/**
 * A URL Object is a representation of the URL that we have been giving. 
 * It knows how to compare URLs!
 *
 * Note: The templates for some methods have been provided, but you should consider which additional
 * methods to add to this class.
 * 
 * @author CS310
 *
 */
public class URL implements Comparable<URL> {

	private String URL;
	/** constructor */
	public URL(String url) {
		this.URL = url;
	}

	@Override
	public int hashCode() {
		byte[] b = URL.getBytes();
		long hash = 0;
		for(byte c:b) {
			hash = (hash<<5) + c;
		}
		return (int)hash;
	}
	@Override
	public boolean equals(Object obj) {
		//TODO write this method!
		if(obj == null)
			return false;
		URL tmp = (URL) obj;
		return URL.equals(tmp.URL);  
	}

	@Override
	public String toString() {
		//TODO write this method!
		return "URL is: " + URL;
	}

	@Override
	public int compareTo(URL obj) {
		// TODO You need to write this method (and the others!)
		return URL.compareTo(obj.URL);
	}
}
