package data_structures;

import java.util.Iterator;

/**
 * The Hash data structure has O(1) time complexity (best case) for add, remove, and find
 * for an object in the data structure. The methods in the Hash data structure are defined
 * by the HashI interface. The Hash consists of an array of Linked Lists,
 * the Linked Lists are defined by the HashListI interface.
 * 
 * @author Christian Cortez
 *
 * @param <K> The key for entries in the hash
 * @param <V> The value for entries in the hash
 */

public class Hash<K, V> implements HashI<K, V> {


	private class HashElement<K, V> implements Comparable<HashElement<K, V>> {

		K key;
		V value;
		public HashElement(K key,V value) {
			this.key = key;
			this.value = value;
		}
		public int compareTo(HashElement<K, V> o) {
			return ((Comparable<K>)key).compareTo((K)o.key);
		}
	}


	LinkedList<HashElement<K, V>>[] harray;
	int tblSize;
	int numElems;
	int newSize;
	double maxLoadFactor; 

	/**
	 *  The Hash constructor should accept a single parameter, an int, that
	 *  sets the initial size of the Dictionary.
	 */
	public Hash(int tblSize) {
		// TODO, create the hash
		this.tblSize = tblSize;
		harray = (LinkedList<HashElement<K, V>>[]) new LinkedList[tblSize];
		for (int i = 0; i < tblSize; i++) {
			harray[i] = new LinkedList<HashElement<K, V>>();
		}
		maxLoadFactor = 0.75; 
	}

	/**  
	 * Adds the given key/value pair to the dictionary.  Returns 
	 * false if the dictionary is full, or if the key is a duplicate. 
	 * Returns true if addition succeeded. 
	 *  
	 * @param key the key to add
	 * @param value the value associated with the key
	 * @return true if the key/value are added to the hash.
	 */
	@Override
	public boolean add(K key, V value) {
		// TODO Auto-generated method stub
		double loadFactor= 0.0;
		if(loadFactor > maxLoadFactor) { 
			resize(tblSize*2);
		}
		HashElement<K,V> newhe = new HashElement<K,V>(key,value);
		int hashval = (key.hashCode() & 0x7FFFFFFF) % tblSize;
		harray[hashval].add(newhe);
		numElems++;
		return true;
	}

	/**
	 * Deletes the key/value pair identified by the key parameter. 
	 * Returns true if the key/value pair was found and removed, 
	 * otherwise returns false.
	 *  
	 * @param key
	 * @return
	 */
	@Override
	public boolean remove(K key) {
		// TODO Auto-generated method stub
		int hashval = (key.hashCode() & 0x7FFFFFFF) % tblSize;
		HashElement<K, V> tmp = new HashElement<K,V>(key, null);
		if(!(harray[hashval].contains(tmp))){
			return false;
		}
		harray[hashval].remove(tmp);
		numElems--;
		return true;
	}

	/**
	 * Change the value associated with an existing key.
	 *
	 * @param key The key to change
	 * @param value The new value to assign to the key
	 * @return
	 */
	@Override
	public boolean changeValue(K key, V value) {
		// TODO Auto-generated method stub
		// Check if it contains the key, use the contains method on your linked list
		// if false return false
		// if true remove the element with the key // then add the new element taht has the same key but a new value
		HashElement<K, V> tmp = new HashElement<K,V>(key, null);
		int hashval = (key.hashCode() & 0x7FFFFFFF) % tblSize;
		if(!(harray[hashval].contains(tmp)))/** if it doesn't contain key return false*/
		{return false;}
		harray[hashval].remove(tmp);
		HashElement<K,V> newhe = new HashElement<K,V>(key,value); 
		harray[hashval].add(newhe);
		return true;
	}

	/**
	 * Test whether the hash has the entry associated with the key.
	 * Returns true if the key was found.
	 *
	 * @param key the key to look for
	 * @return whether it is there.
	 */
	@Override
	public boolean contains(K key) {
		// TODO Auto-generated method stub
		int hashval = (key.hashCode() & 0x7FFFFFFF) % tblSize;
		HashElement<K, V> tmp = new HashElement<K,V>(key, null);

		return harray[hashval].contains(tmp);
	}

	/**
	 * Returns the value associated with the parameter key. 
	 * Returns null if the key is not found or the dictionary is empty. 
	 *
	 * @param key the key to find the value for
	 * @return the value
	 */
	@Override
	public V getValue(K key) {
		// TODO Auto-generated method stub
		int hashval = (key.hashCode() & 0x7FFFFFFF) % tblSize;
		for(HashElement<K,V> he: harray[hashval]) {
			if (((Comparable<K>)key).compareTo(he.key) == 0)
			{return he.value;}
		}
		return null;
	}

	/**
	 * Returns the number of key/value pairs currently stored in the dictionary 
	 * @return
	 */
	@Override
	public int size() {
		// TODO Auto-generated method stub
		return numElems;
	}

	/**
	 * Returns true if the dictionary is empty 
	 *
	 * @return whether the dictionary is empty
	 */
	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		if(numElems== 0)
		{return true;}
		return false;
	}

	/**
	 * Make the dictionary empty
	 */
	@Override
	public void makeEmpty() {
		// TODO Auto-generated method stub
		numElems = 0;
		setMaxLoadFActor(0.0);
	}

	/**
	 * Returns the current load factor of the dictionary (lambda)
	 *
	 * @return the loadFactor
	 */
	@Override
	public double loadFactor() {
		// TODO Auto-generated method stub
		return (double)(numElems/tblSize);
	}

	/**
	 * Get the maximum load factor (at which point we need to resize)
	 *
	 * @return the maximum load factor of the hash
	 */
	@Override
	public double getMaxLoadFactor() {
		// TODO Auto-generated method stub
		return maxLoadFactor;
	}

	/**
	 * Set the maximum load factor (at which point we need to resize)
	 *
	 * @param loadfactor the maximum load factor
	 */
	@Override
	public void setMaxLoadFActor(double loadfactor) {
		// TODO Auto-generated method stub
		maxLoadFactor = loadfactor;
	}

	/**
	 * Resizes the dictionary
	 *
	 * @param newSize the size of the new dictionary
	 */
	@Override
	public void resize(int newSize) {
		// TODO Auto-generated method stub
		LinkedList<HashElement<K,V>>[] tmparray = (LinkedList<Hash<K, V>.HashElement<K, V>>[]) new LinkedList[newSize];
		for(int i = 0; i < newSize; i++) {
			tmparray[i] = new LinkedList<HashElement<K,V>>(); 
		}
		for(K key:this) {
			V val = getValue(key);
			HashElement<K,V> newhe = new HashElement<K,V>(key,val);
			int hashval = (key.hashCode() & 0x7FFFFFFF) % newSize;
			tmparray[hashval].add(newhe);
		}
		harray = tmparray;
		tblSize = newSize;
	}

	/**
	 * Returns an Iterator of the keys in the dictionary, in ascending 
	 * sorted order 
	 *
	 * @return an instance of an Iterator<K> inner class
	 */

	class KeyIteratorHelper<T> implements Iterator<T>{
		T[] keys;
		int posn;
		public KeyIteratorHelper() {
			keys = (T[]) new Object[numElems];
			int counter = 0;
			for(int i = 0;i < tblSize;i++) {
				for(HashElement<K,V> he: harray[i])
					keys[counter++] = (T)he.key;
			}
			posn= 0;
		}

		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return posn < keys.length;
		}

		@Override
		public T next() {
			// TODO Auto-generated method stub
			if (!hasNext())
			{return null;}
			return keys[posn++];
		}

	}
	@Override
	public Iterator<K> iterator() {
		// TODO Auto-generated method stub
		return new KeyIteratorHelper();
	}
}
