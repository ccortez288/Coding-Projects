package Lab2;
import java.util.ArrayList;
import java.util.List;

public class graphLab<T extends Comparable<T>> {

	/**Data will be stored in two ArrayLists
	 * One for the vertices and one for the edges
	 *  */
	private ArrayList<Vertex> verts;
	private ArrayList<Edge> edges;

	/**Constructor */
	public graphLab() {
		verts = new ArrayList<>();
		edges = new ArrayList<>();
	}

	/**Add method, adds to edge class which creates a 
	 * vertex instance automatically
	 *  */
	public void add(T from, T to, int weight) {
		Edge e = new Edge(from, to, weight);
		edges.add(e);
	}

	/**Returns the number of vertices in the Graph */
	public int numVerts() {
		return verts.size();
	}

	/**toString methods for the vertices and edges
	 * shows how the edges are onnected and which vertices
	 * have inb/outb/self edges  */
	public String edgesToString()
	{
		String qts = "";
		for (Edge each : edges)
		{
			qts += each + "\n";
		}
		return qts;
	}

	public String toString()
	{
		String qts = "";
		for (Vertex each : verts)
		{
			qts += each.toString() + "\n";
		}
		return qts;
	}

	/** Vertex node class for creating new 
	 * vertices, sorts between inbound and outbound
	 * toString method shows which vertices have inbound,
	 * outbound, and self edges when it prints out */
	class Vertex {

		T value;

		List<Vertex> inbound;
		List<Vertex> outbound;
		List<Vertex> selfEdges;

		public Vertex(T value) {
			this.value = value;
			inbound = new ArrayList<>();
			outbound = new ArrayList<>();
			selfEdges = new ArrayList<>();
		}

		public void addInbound(Vertex V) {
			inbound.add(V);
		}

		public void addOutbound(Vertex V) {
			outbound.add(V);
		}

		public void addSelfEdges(Vertex V) {
			selfEdges.add(V);
		}

		@Override
		public String toString() {
			String qts = "";
			qts += "Vertex: " + value + " : ";
			qts += " Inbound Edges: ";
			for (Vertex each : inbound)
				qts+= each.value + " ";
			qts += "Outbound Edges: ";
			for (Vertex each : outbound) 
				qts += each.value + " ";
			return qts;
		}
	}

	/**Edge class node automatically creates
	 * instances of vertex node class, this is where everything is
	 * added/organized */
	class Edge {
		Vertex from;
		Vertex to;
		int weight;

		public Edge(T vx1, T vx2, int weight) {

			if(((Comparable<T>)vx1).compareTo(vx2) == 0) {
				from = new Vertex(vx1);
				from.addSelfEdges(from);
			}

			from = findVertex(vx1);
			if(from == null) {
				from = new Vertex(vx1);
				verts.add(from);
			}
			to = findVertex(vx2);
			if(to == null) {
				to = new Vertex(vx2);
				verts.add(to);
			}
			this.weight = weight;
			from.addOutbound(to);
			to.addInbound(from);

		}

		@Override
		public String toString()
		{
			return "Edge From: " + from.value + " to: " + to.value + " weight: " + weight;
		}
	}

	/**Private helper function for adding in new vertices 
	 * This way if set is inputted twice the weight will get 
	 * updated instead of another coordinate being added in
	 * */
	private Vertex findVertex(T v) {
		for (Vertex each : verts)
		{
			if (each.value.compareTo(v)==0)
				return each;
		}
		return null;
	}
}
