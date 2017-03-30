/** ***********************************************************************
 *  Compilation:  javac LinkedListST.java
 *  Execution:    java LinkedListST
 *  Dependencies: StdIn.java StdOut.java
 *  Data files:   http://algs4.cs.princeton.edu/31elementary/tinyST.txt
 *
 *  Symbol table implementation with an ordered linked list.
 *
 *  % more tinyST.txt
 *  S E A R C H E X A M P L E
 *
 *  % java LinkedListST < tinyST.txt
 *  A 8
 *  C 4
 *  E 12
 *  H 5
 *  L 11
 *  M 9
 *  P 10
 *  R 3
 *  S 0
 *  X 7
 *
 *************************************************************************/

// The StdIn class provides static methods for reading strings and numbers from standard input.
// https://www.ime.usp.br/~pf/sedgewick-wayne/stdlib/documentation/index.html
// http://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/StdIn.html
import edu.princeton.cs.algs4.StdIn;

// This class provides methods for printing strings and numbers to standard output.
// https://www.ime.usp.br/~pf/sedgewick-wayne/stdlib/documentation/index.html
// http://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/StdOut.html
import edu.princeton.cs.algs4.StdOut;

// https://docs.oracle.com/javase/8/docs/api/java/util/Iterator.html
// http://codereview.stackexchange.com/questions/48109/simple-example-of-an-iterable-and-an-iterator-in-java
import java.util.Iterator;

/** This is an implementation of a symbol table whose keys are comparable.
 * The keys are kept in increasing order in an linked list.
 * Following our usual convention for symbol tables,
 * the keys are pairwise distinct.
 * <p>
 * For additional documentation, see
 * <a href="http://algs4.cs.princeton.edu/31elementary/">Section 3.1</a>
 * of "Algorithms, 4th Edition" (p.378 of paper edition),
 * by Robert Sedgewick and Kevin Wayne.
 *
 */

public class LinkedListST<Key extends Comparable<Key>, Value> {
    // atributos de estado
    private int n;
    private Node<Key, Value> head;

    private class Node<Key, Value> {
        private Key key;
        private Value val;
        private Node<Key, Value> next;
    }
    /** Constructor.
     * Creates an empty symbol table with default initial capacity.
     */
    public LinkedListST() {
        // escreva seu método a seguir
        head = null;
        n = 0;
    }

    /** Is the key in this symbol table?
     */
    public boolean contains(Key key) {
        // escreva seu método a seguir
        for (Key k : keys())
            if (k.compareTo(key) == 0)
                return true;
        return false;
    }

    /** Returns the number of (key,value) pairs in this symbol table.
     */
    public int size() {
        // escreva seu método a seguir
        return n;
    }

    /** Is this symbol table empty?
     */
    public boolean isEmpty() {
        // escreva seu método a seguir
        return (n == 0);
    }

    /** Returns the value associated with the given key,
     *  or null if no such key.
     *  Argument key must be nonnull.
     */
    public Value get(Key key) {
        if (key == null) throw new IllegalArgumentException("argument to get() is null");
        // escreva seu método a seguir
        for (Node<Key, Value> curr = head; curr != null; curr = curr.next)
            if (curr.key.compareTo(key) == 0)
                return curr.val;
        return null;
    }

    /** Returns the number of keys in the table
     *  that are strictly smaller than the given key.
     *  Argument key must be nonnull.
     */
    public int rank(Key key) {
        if (key == null) throw new IllegalArgumentException("argument to rank() is null");
        // escreva seu método a seguir
        int count = 0;
        for (Node<Key, Value> curr = head; curr != null && curr.key.compareTo(key) < 0; curr = curr.next)
            count++;
        return count;
    }


    /** Search for key in this symbol table.
     * If key is in the table, update the corresponing value.
     * Otherwise, add the (key,val) pair to the table.
     * Argument key must be nonnull.
     * If argument val is null, the key must be deleted from the table.
     */
    public void put(Key key, Value val)  {
        if (key == null) throw new IllegalArgumentException("argument to put() is null");
        if (val == null) {
            delete(key);
            return;
        }
        // escreva seu método a seguir
        Node<Key, Value> curr = head;
        Node<Key, Value> mem = null;
        if (curr != null && curr.key.compareTo(key) <= 0) {
            int comp = curr.key.compareTo(key);
            while (curr.next != null && comp < 0) {
                mem = curr;
                curr = curr.next;
                comp = curr.key.compareTo(key);
            }
            if (comp == 0) {
                curr.val = val;
            }
            else {
                Node<Key, Value> newNode = new Node<Key, Value>();
                newNode.key = key;
                newNode.val = val;
                if (comp > 0) {
                    newNode.next = mem.next;
                    mem.next = newNode;
                }
                else {
                    newNode.next = null;
                    curr.next = newNode;
                }
                n++;
            }
        }
        else {
            Node<Key, Value> newNode = new Node<Key, Value>();
            newNode.key = key;
            newNode.val = val;
            newNode.next = head;
            head = newNode;
            n++;
        }
    }


    /** Remove key (and the corresponding value) from this symbol table.
     * If key is not in the table, do nothing.
     */
    public void delete(Key key)  {
        if (key == null) throw new IllegalArgumentException("argument to put() is null");
        // escreva seu método a seguir
        Node<Key, Value> curr = head;
        if (curr == null)
            return ;
        while (curr.next != null && curr.next.key.compareTo(key) != 0)
            curr = curr.next;
        if (curr.next != null && curr.next.key.compareTo(key) == 0) {
            curr.next = curr.next.next;
            n--;
        }
    }

    /** Delete the minimum key and its associated value
     * from this symbol table.
     * The symbol table must be nonempty.
     */
    public void deleteMin() {
        if (isEmpty()) throw new java.util.NoSuchElementException("deleteMin(): Symbol table underflow error");
        // escreva seu método a seguir
        head = head.next;
        n--;
    }

    /** Delete the maximum key and its associated value
     * from this symbol table.
     */
    public void deleteMax() {
        if (isEmpty()) throw new java.util.NoSuchElementException("deleteMax(): Symbol table underflow error");
        // escreva seu método a seguir
        Node<Key, Value> curr = head;
        if (curr.next == null) {
            curr = null;
            n--;
            return ;
        }
        while (curr.next.next != null)
            curr = curr.next;
        curr.next = null;
        n--;
    }


   /***************************************************************************
    *  Ordered symbol table methods
    **************************************************************************/

    /** Returns the smallest key in this table.
     * Returns null if the table is empty.
     */
    public Key min() {
        // escreva seu método a seguir
        if (n == 0)
            return null;
        return head.key;
    }


    /** Returns the greatest key in this table.
     * Returns null if the table is empty.
     */
    public Key max() {
        // escreva seu método a seguir
        if (n == 0)
            return null;
        Node<Key, Value> curr = head;
        while (curr.next != null)
            curr = curr.next;
        return curr.key;
    }

    /** Returns a key that is strictly greater than
     * (exactly) k other keys in the table.
     * Returns null if k < 0.
     * Returns null if k is greater that or equal to
     * the total number of keys in the table.
     */
    public Key select(int k) {
        // escreva seu método a seguir
        if (k < 0 || k > n)
            return null;
        Node<Key, Value> curr = head;
        for (int i = 0; i < k; i++)
            curr = curr.next;
        return curr.key;
    }

    /** Returns the greatest key that is
     * smaller than or equal to the given key.
     * Argument key must be nonnull.
     * If there is no such key in the table
     * (i.e., if the given key is smaller than any key in the table),
     * returns null.
     */
    public Key floor(Key key) {
        if (key == null) throw new IllegalArgumentException("argument to floor() is null");
        // escreva seu método a seguir
        Node<Key, Value> curr = head;
        if (n == 0 || curr.key.compareTo(key) > 0)
            return null;
        while (curr.next != null && curr.next.key.compareTo(key) <= 0)
            curr = curr.next;
        return curr.key;
    }

    /** Returns the smallest key that is
     * greater than or equal to the given key.
     * Argument key must be nonnull.
     * If there is no such key in the table
     * (i.e., if the given key is greater than any key in the table),
     * returns null.
     */
    public Key ceiling(Key key) {
        if (key == null) throw new IllegalArgumentException("argument to ceiling() is null");
        // escreva seu método a seguir
        Node<Key, Value> curr = head;
        if (n == 0)
            return null;
        while (curr != null && curr.key.compareTo(key) < 0)
            curr = curr.next;
        if (curr == null)
            return null;
        return curr.key;

    }

    /** Returns all keys in the symbol table as an Iterable.
     * To iterate over all of the keys in the symbol table named st, use the
     * foreach notation: for (Key key : st.keys()).
     */
    public Iterable<Key> keys() {
        return new ListKeys();
    }

    /**
     * implements Iterable<Key> significa que essa classe deve
     * ter um método iterator(), acho...
     */
    private class ListKeys implements Iterable<Key> {
        /**
         * Devolve um iterador que itera sobre os itens da ST
         * da menor até a maior chave.<br>
         */
        public Iterator<Key> iterator() {
            return new KeysIterator();
        }

        private class KeysIterator implements Iterator<Key> {
            // variáveis do iterador
            private Node<Key, Value> curr = head;

            public boolean hasNext() {
                // escreva seu método a seguir
                return curr != null;
            }

            public Key next() {
                // escreva seu método a seguir
                if (curr == null)
                    return null;
                Key ret = curr.key;
                curr = curr.next;
                return ret;
            }

            public void remove() {
                throw new UnsupportedOperationException();
            }
        }
    }


   /***************************************************************************
    *   Check internal invariants: pode ser útil durante o desenvolvimento
    **************************************************************************/

    // are the items in the linked list in ascending order?
    private boolean isSorted() {
        // escreva seu método a seguir
        Node<Key, Value> curr = head;
        if (n <= 1)
            return true;
        while (curr.next != null && curr.key.compareTo(curr.next.key) < 0)
            curr = curr.next;
        return curr.next == null;
    }

   /** Test client.
    * Reads a sequence of strings from the standard input.
    * Builds a symbol table whose keys are the strings read.
    * The value of each string is its position in the input stream
    * (0 for the first string, 1 for the second, and so on).
    * Then prints all the (key,value) pairs.
    */
    public static void main(String[] args) {
        LinkedListST<String, Integer> st;
        st = new LinkedListST<String, Integer>();
        for (int i = 0; !StdIn.isEmpty(); i++) {
            String key = StdIn.readString();
            st.put(key, i);
        }
        // Tests Iterator
        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));

        StdOut.println("Size check: " + st.size());

        // Tests contains
        StdOut.println("Topper contains: " + st.contains("Topper"));
        StdOut.println("zzzzz contains: " + st.contains("zzzzz"));

        // Tests ceiling
        StdOut.println("ZZZZ ceiling: " + st.ceiling("ZZZZ"));
        StdOut.println("zzzz ceiling: " + st.ceiling("zzzz"));
        StdOut.println("AAAA ceiling: " + st.ceiling("AAAA"));

        // Tests floor
        StdOut.println("ZZZZ floor: " + st.floor("ZZZZ"));
        StdOut.println("zzzz floor: " + st.floor("zzzz"));
        StdOut.println("AAAA floor: " + st.floor("AAAA"));

        // Tests select
        StdOut.println(Integer.toString(1) + " select: " + st.select(1));
        StdOut.println(Integer.toString(5) + " select: " + st.select(5));
        StdOut.println(Integer.toString(100) + " select: " + st.select(100));

        // Tests rank
        StdOut.println("ZZZZ rank: " + st.rank("ZZZZ"));
        StdOut.println("zzzz rank: " + st.rank("zzzz"));
        StdOut.println("AAAA rank: " + st.rank("AAAA"));
        StdOut.println("Topper rank: " + st.rank("Topper"));

        // Tests min/max
        StdOut.println("Min: " + st.min());
        StdOut.println("Max: " + st.max());

        // Deleting the maximum key
        StdOut.println("Deleting the maximum key:");
        st.deleteMax();
        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));

        StdOut.println("Size check: " + st.size());

        // Deleteing the minimum key
        StdOut.println("Deleting the minimum key:");
        st.deleteMin();
        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));

        StdOut.println("Size check: " + st.size());

        // Deleting Topper
        StdOut.println("Deleting Topper:");
        st.delete("Topper");
        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));

        StdOut.println("Size check: " + st.size());

        // Deleteing ZZZZZ
        StdOut.println("Deleting ZZZZZ:");
        st.delete("ZZZZZ");
        for (String s : st.keys())
            StdOut.println(s + " " + st.get(s));

        StdOut.println("Size check: " + st.size());

    }
}
