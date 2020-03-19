package data_structures;

// the only import statement you are allowed.
import java.util.Iterator;
// do not import anything else.
import java.util.NoSuchElementException;


public class LinkedList<E> implements ListI<E> {

	class Node<E> {
		E data;
		Node<E> next;
		public Node(E obj) {
			data = obj;
			next = null;
		}
	}



	private Node<E> head, tail;
	private int currentSize;

	public LinkedList() {
		head = tail = null;
		currentSize = 0;
	}


	public void addFirst(E obj) {   /** Adds an object to the beginning of the list */		
		Node <E> newNode = new Node<E>(obj);
		newNode.next = head;
		if(head == null) {
			head = tail = newNode;
			currentSize++;
			return;
		}
		newNode.next = head;
		head = newNode;
		currentSize++;
	}

	public void addLast(E obj){ /** Adds an object to the end of the list. */

		Node<E> newNode = new Node<E>(obj);
		if(head == null) {
			head = tail = newNode;
			currentSize++;
			return;
		}
		tail.next = newNode;
		tail = newNode;
		currentSize++;
	}

	public E removeFirst(){ /** removes first object in the list and returns it */

		if(head == null)
			return null;
		E tmp = head.data;
		if(head == tail)
			head = tail = null;
		else
			head = head.next;
		currentSize--;
		return tmp;
	} 

	public E removeLast() { /** removes last object in the list and returns it */
		if(head == null)
			return null;
		if(head == tail)
			return removeFirst();
		Node<E> previous = null, current = head;
		while(current.next != null) {
			previous = current;
			current = current.next;
		}
		previous.next = null;
		tail = previous;
		currentSize--;
		return current.data;

	} 

	public E peekFirst() { /** returns first obj in list witthout removing*/ 
		if( head == null)
		{return null;}
		return head.data;
	}

	/**
	 * Returns the last Object in the list, but does not remove it. 
	 * Returns null if the list is empty.
	 * @return the object at the end of the list.
	 */
	public E peekLast() {
		if (tail == null)
			return null;
		return tail.data;
	}
	/**
	 * Return the list to an empty state.
	 * This should generally be a constant time operation.
	 */
	public void makeEmpty() {
		head = null;
		tail = null;
		currentSize = 0;
	}

	/**
	 * Test whether the list is empty.
	 * @return true if the list is empty, otherwise false
	 */
	public boolean isEmpty() {
		if(head == null)
		{return true;}
		return false;
	}
	public boolean isFull() { /** Return false since LLs are never full */
		return false;
	}

	public int size() { /** return # of objs in List */
		return currentSize;
	}

	/** @param obj The object to look for in the list
	 * @return true if the object is found in the list, false if it is not found*/
	public boolean contains(E obj) { /** Test whether the list contains an object. compareTo methodm */
		Node<E> tmp = head;
		while (tmp != null)
		{
			if(((Comparable<E>)tmp.data).compareTo(obj) == 0)
			{return true;}
			tmp = tmp.next;
		}
		return false;
	}

	/**
	 * Returns an Iterator of the values in the list, presented in
	 * the same order as the list.
	 * @see java.lang.Iterable#iterator()
	 */
	
	
	class IteratorHelper implements Iterator<E> {

		Node<E> index;
		public IteratorHelper() {
			index = head;
		}
		public boolean hasNext() {
			return index != null;
		}
		public E next() {
			if(!hasNext())
				throw new NoSuchElementException();
			E tmp = index.data;
			index = index.next;
			return tmp;
		}
	}

	@Override
	public Iterator<E> iterator() {
		// TODO Auto-generated method stub
		return new IteratorHelper();
	}
}


