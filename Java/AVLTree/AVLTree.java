/**
 * 
 */
package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * @author cortez
 *
 */
public class AVLTree<K, V> implements AVLTreeI<K, V> {

	class Node<K, V> {
		K key;
		V value;
		Node<K, V> leftChild, rightChild, parent;
		public Node(K key, V value) {
			this.key = key;
			this.value = value;
			leftChild = rightChild = parent = null;
		}
	}
	private Node<K, V> root;
	private int numElems;

	public AVLTree() {
		root = null;
		int numElems = 0;// TODO Auto-generated constructor stub
	}

	/**
	 * The method to add to the AVLTree.  It will not allow duplicate additions.
	 * @param key the key to add
	 * @param value the value associated with the key
	 */
	@Override
	public void add(K key, V value) {
		// TODO Auto-generated method stub 
		Node<K, V> node = new Node<K, V>(key,value);
		if (root == null) {
			root = node;
			numElems++;
			return;
		}
		else {
			insert(key, value, root, null, false);
		}
		numElems++;
	}
	/** private insert method that uses recursion to insert quicker
	 after every recursive insert there is a check for the height differences
	 that either does a rotate or a doublerotate if necessary 
	 */

	private void insert(K k, V val, Node<K, V> node, Node<K, V> p, boolean wasLeft) {
		if(node == null) {
			if(wasLeft) p.leftChild = new Node<K, V>(k, val);
			p.rightChild = new Node<K, V>(k, val);
			return;
		}
		if(((Comparable<K>)k).compareTo((K)node.key) < 0) { //leads to a left insertion if condition is true
			insert(k, val, node.leftChild, node, true);
			if(height(node.leftChild) - height(node.rightChild) > 2) { //height differences checked
				if(((Comparable<K>)k).compareTo((K)node.leftChild.key) < 0) { //rotations done as necessary

					node = leftRotate(node);
				}
				else
					node = rightLeftRotate(node);
			}
		}
		else
			insert(k, val, node.rightChild, node, false); // same process but with rightChild
		if((height(node.rightChild) - height(node.leftChild)) > 2) {

			if(((Comparable<K>)k).compareTo((K)node.rightChild.key) < 0) {
				node = rightRotate(node);
			}
			else
				node = leftRightRotate(node);
		}
	}

	/**
	 * Tests whether the AVLTree contains the key
	 * @param key the key to look for
	 * @return whether the key is found
	 */
	@Override
	public boolean contains(K key) {
		// TODO Auto-generated method stub
		return contains(key, root);
	}

	/**Recursive method for contains */
	private boolean contains(K k, Node<K, V> node) {
		if(node == null )
			return false;
		int cmp = ((Comparable<K>) k).compareTo(node.key);
		if(cmp < 0) 
			return contains(k, node.leftChild);
		if(cmp > 0)
			return contains(k, node.rightChild);
		return true;
	}

	/**
	 * Get the value associated with a given key
	 * @param key the key to get the value for
	 * @return the current value
	 */
	@Override
	public V getValue(K key) {
		// TODO Auto-generated method stub
		return find(key, root);
	}

	/** recursive method find that getValue uses */
	private V find(K key, Node<K, V> node) {
		if(node == null) { 
			return null;
		}
		if(((Comparable<K>)key).compareTo(node.key) == 0) {
			return node.value;
		}
		if(((Comparable<K>)key).compareTo(node.key) < 0) { //go left 
			return find(key, node.leftChild);
		}
		if(((Comparable<K>)key).compareTo(node.key) > 0) { // go right 
			return find(key, node.rightChild);
		}	
		return (V) node.value;
	}

	/**
	 * Returns the number of elements in the AVLTree
	 * @return the number of elements in the tree
	 */
	@Override
	public int size() {
		// TODO Auto-generated method stub
		return numElems;
	}

	/**
	 * Test whether the AVLTree is empty
	 * @return <code>true</code> if the tree is empty
	 * 		   <code>false</code> if the tree is not empty 
	 */
	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		if (root == null)
			return true;
		return false;
	}

	/**
	 * The height of the tree. Recall that a tree with 
	 * only a root node has height 0. You will also need
	 * to have a private method that is not included here
	 * that overloads the height() method.
	 * @return the height of the tree at the root node
	 */
	@Override
	public int height() {
		// TODO Auto-generated method stub
		return height(root);
	}
	/**Recursive method for height to use */
	private int height(Node<K, V> node) {
		// TODO Auto-generated method stub
		if(node == null) {
			return 0;
		}
		if(node.leftChild == null && node.rightChild == null) {
			//leaf
			return 0; 
		}
		int leftHeight = 0, rightHeight = 0;
		if( node.leftChild != null) {
			leftHeight = height(node.leftChild)+1;
		}
		if(node.rightChild != null) {
			rightHeight = height(node.rightChild)+1;
		}
		if(rightHeight > leftHeight) {
			return rightHeight;
		}

		return leftHeight;	
	}

	/**
	 * An iterator for all the keys in the AVLTree. This will
	 * iterate over the keys using <b>InOrder Traversal</b>
	 * @see java.lang.Iterable#iterator()
	 */
	@Override
	public Iterator<K> iterator() {
		// TODO Auto-generated method stub
		return new TreeIteratorHelper<K>(root);
	}

	class TreeIteratorHelper<T> implements Iterator<T>{
		private Node<K, V> next;

		public TreeIteratorHelper(Node<K, V> root) {
			next = root;
			if(next == null)
				return;
			while(next.leftChild != null) {
				next = next.leftChild;
			}
		}
		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return next != null;
		}

		@Override
		public T next() {
			// TODO Auto-generated method stub
			if(!hasNext())
				throw new NoSuchElementException();
			Node<K, V> r = next;

			if(next.rightChild != null) {
				next = next.rightChild;
				while(next.leftChild != null) 
					next = next.leftChild;
				return (T)r;
			}

			while(true) {
				if(next.parent == null) {
					next = null;
					return (T)r;
				}
				next = next.parent;
			}
		}

	}

	@Override
	public void print() {
		// TODO Auto-generated method stub
		/*for(K n: this) {
			System.out.println(n);
		} */
		inOrder(root);
	}  
	/** 
	 * In oder traversal and print of the tree 
	 *  Iterator was displaying odd results so I added this 
	 *  to get something printed
	 *  @param is the tree to print
	 */
	private void inOrder(Node<K, V> node) {
		if(node != null ) {
			inOrder(node.leftChild);
			System.out.println(node.key);
			inOrder(node.rightChild);
			
		}
	}

	/**Rotation methods, left, right, leftright, rightleft */

	private Node<K, V> leftRotate(Node<K, V> node) {
		if(node.leftChild == null || node.rightChild == null) return root;
		Node<K, V> tmp = node.rightChild;
		node.rightChild = tmp.leftChild;
		tmp.leftChild = node;
		return tmp;
	}

	private Node<K, V> rightRotate(Node<K, V> node) {
		if(node.leftChild == null || node.rightChild == null) return root;
		Node<K, V> tmp = node.leftChild;
		node.leftChild = tmp.rightChild;
		tmp.rightChild = node;
		return tmp;
	}

	private Node<K, V> leftRightRotate(Node<K, V> node) {
		if(node.leftChild == null || node.rightChild == null) return root;
		node.rightChild = rightRotate(node.rightChild);
		return leftRotate(node);
	}
	private Node<K, V> rightLeftRotate(Node<K, V> node) {
		if(node.leftChild == null || node.rightChild == null) return root;
		node.leftChild = leftRotate(node.leftChild);
		return rightRotate(node);
	}
}
