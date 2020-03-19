/**
 * 
 */
package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.LinkedList.Node;

/**
 * The linked list for our hash will only implement the
 * methods in the HashListI interface, a reduced set of
 * methods compared to the linked list from Assignment 1.
 * 
 * @author Christian Cortez II 
 *
 */
public class LinkedList<E> implements HashListI<E> {

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

	@Override
	public void add(E obj) {
		// TODO Auto-generated method stub
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

	@Override
	public E remove(E obj) {
		// TODO Auto-generated method stub
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

	@Override
	public void makeEmpty() {
		// TODO Auto-generated method stub
		head = null;
		tail = null;
		currentSize = 0;
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		if(currentSize == 0)
		{return true;}
		return false;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return currentSize;
	}

	@Override
	public boolean contains(E obj) {
		// TODO Auto-generated method stub
		Node<E> tmp = head;
		while (tmp != null)
		{
			if(((Comparable<E>)tmp.data).compareTo(obj) == 0)
			{return true;}
			tmp = tmp.next;
		}
		return false;
	}


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
