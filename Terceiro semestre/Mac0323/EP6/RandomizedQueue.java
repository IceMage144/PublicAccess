import java.util.Iterator;
import edu.princeton.cs.algs4.StdRandom;

public class RandomizedQueue<Item> implements Iterable<Item> {


    public RandomizedQueue() {                // construct an empty randomized queue

    }
    public boolean isEmpty() {                // is the queue empty?

    }
    public int size() {                       // return the number of items on the queue

    }
    public void enqueue(Item item) {          // add the item

    }
    public Item dequeue() {                   // remove and return a random item

    }
    public Item sample() {                    // return a random item (but do not remove it)

    }
    public Iterator<Item> iterator() {        // return an independent iterator over items in random order

    }
    private class ListItens implements Iterable<Item> {
        public Iterator<Item> iterator() {
            return new ListIterator();
        }
        private class ListIterator implements Iterator<Item> {
            Node ptr = head.next;
            public boolean hasNext() {
                return ptr.next == null;
            }
            public Item next() {
                if (!hasNext())
                    return null;
                Item ret = ptr.val;
                ptr = ptr.next;
                return ret;
            }
            public void remove() {
                throw new UnsupportedOperationException();
            }
        }
    }
    public static void main(String[] args)   // unit testing (required)
}
