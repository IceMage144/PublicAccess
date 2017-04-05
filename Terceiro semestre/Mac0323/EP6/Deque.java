import java.util.Iterator;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;

public class Deque<Item> implements Iterable<Item> {
    private class Node {
        public Item val;
        public Node prev;
        public Node next;
        public Node(Node p, Item item, Node n) {
            prev = p;
            val = item;
            next = n;
        }
    };
    private Node head;
    private Node tail;
    private int n;
    // Construct an empty deque
    public Deque() {
        head = new Node(null, null, null);
        tail = new Node(head, null, null);
        head.next = tail;
        n = 0;
    }
    // Is the deque empty?
    public boolean isEmpty() {
        return n == 0;
    }
    // Return the number of items on the deque
    public int size() {
        return n;
    }
    // Add the item to the front
    public void addFirst(Item item) {
        if (item == null) throw new java.lang.NullPointerException();
        Node newNode = new Node(head, item, head.next);
        head.next.prev = newNode;
        head.next = newNode;
        n++;
    }
    // Add the item to the end
    public void addLast(Item item) {
        if (item == null) throw new java.lang.NullPointerException();
        Node newNode = new Node(tail.prev, item, tail);
        tail.prev.next = newNode;
        tail.prev = newNode;
        n++;
    }
    // Remove and return the item from the front
    public Item removeFirst() {
        if (n == 0) throw new java.util.NoSuchElementException();
        Item ret = head.next.val;
        head.next.next.prev = head;
        head.next = head.next.next;
        n--;
        return ret;
    }
    // Remove and return the item from the end
    public Item removeLast() {
        if (n == 0) throw new java.util.NoSuchElementException();
        Item ret = tail.prev.val;
        tail.prev.prev.next = tail;
        tail.prev = tail.prev.prev;
        n--;
        return ret;
    }
    // Return an iterator over items in order from front to end
    public Iterator<Item> iterator() {
        return new ListIterator();
    }
    private class ListIterator implements Iterator<Item> {
        Node ptr;
        public ListIterator() {
            ptr = head.next;
        }
        public boolean hasNext() {
            return (n != 0 && ptr.next != null);
        }
        public Item next() {
            if (!hasNext()) {
                return null;
            }
            Item ret = ptr.val;
            ptr = ptr.next;
            return ret;
        }
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
    // Unit testing
    public static void main(String[] args) {
        Deque<String> dq = new Deque<String>();
        int num = 0;
        for (int i = 0; !StdIn.isEmpty(); i++) {
            String key = StdIn.readString();
            dq.addFirst(key);
            num++;
        }
        // Testing the iterator
        for (String str : dq) {
            StdOut.println(str);
        }
    }
}
