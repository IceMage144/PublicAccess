import java.util.Iterator;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private Item[] itens;
    private int maxN;
    private int n;
    private boolean forced;
    // Construct an empty randomized queue
    public RandomizedQueue() {
        itens = (Item[])new Object[1];
        maxN = 1;
        n = 0;
        forced = false;
    }
    // Private method for a custom randomized queue
    private RandomizedQueue(int n) {
        itens = (Item[])new Object[n];
        maxN = n;
        n = 0;
        forced = true;
    }
    // Is the queue empty?
    public boolean isEmpty() {
        return n == 0;
    }
    // Return the number of items on the queue
    public int size() {
        return n;
    }
    // Add the item
    public void enqueue(Item item) {
        if (item == null) throw new java.lang.NullPointerException();
        if (!forced && n == maxN) makeBigger();
        itens[n] = item;
        n++;
    }
    // Remove and return a random item
    public Item dequeue() {
        if (isEmpty()) throw new java.util.NoSuchElementException();
        if (!forced && n < maxN/4) makeSmaller();
        int rand = StdRandom.uniform(0, n);
        Item ret = itens[rand];
        n--;
        itens[rand] = itens[n];
        itens[n] = null;
        return ret;
    }
    // Return a random item (but do not remove it)
    public Item sample() {
        if (isEmpty()) throw new java.util.NoSuchElementException();
        int rand = StdRandom.uniform(0, n);
        return itens[rand];
    }
    // Return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new ListIterator();
    }
    private class ListIterator implements Iterator<Item> {
        RandomizedQueue<Item> list = new RandomizedQueue<Item>(n);
        public ListIterator() {
            for (int i = 0; i < n; i++)
                list.enqueue(itens[i]);
        }
        public boolean hasNext() {
            return !list.isEmpty();
        }
        public Item next() {
            if (!hasNext())
                return null;
            return list.dequeue();
        }
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
    private void makeBigger() {
        Item[] newV = (Item[])new Object[2*maxN];
        for (int i = 0; i < maxN; i++)
            newV[i] = itens[i];
        itens = newV;
        maxN *= 2;
    }
    private void makeSmaller() {
        Item[] newV = (Item[])new Object[maxN/2];
        for (int i = 0; i < n; i++)
            newV[i] = itens[i];
        itens = newV;
        maxN /= 2;
    }
    // Unit testing
    public static void main(String[] args) {}
}
