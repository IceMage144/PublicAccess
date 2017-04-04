import java.util.Iterator;

public class Deque<Item> implements Iterable<Item> {
    private class Node {
        public Item val;
        public Node next;
        public Node prev;
        public Node(Node p, Item item, Node n) {
            prev = p;
            val = item;
            next = n;
        }
    };
    private Node head;
    private Node tail;
    private int n;
    public Deque() {                           // construct an empty deque
        head = new Node(null, null, tail);
        tail = new Node(null, null, head);
        n = 0;
    }
    public boolean isEmpty() {                // is the deque empty?
        return n == 0;
    }
    public int size() {                       // return the number of items on the deque
        return n;
    }
    public void addFirst(Item item) {         // add the item to the front
        if (n == 0) {
            Node newNode = new Node(head, item, tail);
            head.next = newNode;
            tail.prev = newNode;
        }
        else {
            Node newNode = new Node(head, item, head.next);
            head.next = newNode;
        }
    }
    public void addLast(Item item) {          // add the item to the end
        if (n == 0) {
            Node newNode = new Node(head, item, tail);
            head.next = newNode;
            tail.prev = newNode;
        }
        else {
            Node newNode = new Node(tail.prev, item, tail);
            tail.prev = newNode;
        }
    }
    public Item removeFirst() {               // remove and return the item from the front
        if (n == 0) {
            return null; // Exception
        }
        Item ret = head.next.val;
        head.next.next.prev = head;
        head.next = head.next.next;
        return ret;
    }
    public Item removeLast() {                // remove and return the item from the end
        if (n == 0) {
            return null; // Exception
        }
        Item ret = tail.prev.val;
        tail.prev.prev.next = tail;
        tail.prev = tail.prev.prev;
        return ret;
    }
    public Iterator<Item> iterator() {        // return an iterator over items in order from front to end
        return new ListItens();
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
    public static void main(String[] args) {   // unit testing (required)
        
    }
}
