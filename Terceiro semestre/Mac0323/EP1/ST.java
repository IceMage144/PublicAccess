// Input. This class provides methods for reading strings and numbers from standard input,
// file input, URLs, and sockets.
// https://www.ime.usp.br/~pf/sedgewick-wayne/stdlib/documentation/index.html
// http://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/In.html
import edu.princeton.cs.algs4.In; // arquivo

// The StdIn class provides static methods for reading strings and numbers from standard input.
// https://www.ime.usp.br/~pf/sedgewick-wayne/stdlib/documentation/index.html
// http://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/StdIn.html
import edu.princeton.cs.algs4.StdIn; 

// This class provides methods for printing strings and numbers to standard output.
// https://www.ime.usp.br/~pf/sedgewick-wayne/stdlib/documentation/index.html
// http://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/StdOut.html
import edu.princeton.cs.algs4.StdOut; 

// Stopwatch. This class is a data type for measuring the running time (wall clock) of a program.
// https://www.ime.usp.br/~pf/sedgewick-wayne/algs4/documentation/index.html
import edu.princeton.cs.algs4.Stopwatch; // arquivo

// https://docs.oracle.com/javase/8/docs/api/java/util/Iterator.html //f//
// http://codereview.stackexchange.com/questions/48109/simple-example-of-an-iterable-and-an-iterator-in-java
import java.util.Iterator; //f//

public class ST <Key, Value> {
    private String[] keys = null;
    private int[] values = null;
    private int n = 0;
    private void makeBigger() {
        int[] tmpV = new int[2*n];
        String[] tmpS = new String[2*n];
        for (int i = 0; i < n; i++) {
            tmpV[i] = values[i];
            tmpS[i] = keys[i];
            keys[i] = null;
        }
        keys = tmpS;
        values = tmpV;
    }
    private void makeSmaller() {
        int[] tmpV = new int[n/2];
        String[] tmpS = new String[n/2];
        for (int i = 0; i < n; i++) {
            tmpV[i] = values[i];
            tmpS[i] = keys[i];
            keys[i] = null;
        }
        keys = tmpS;
        values = tmpV;
    }
    private int find(String key) {
        for (int i = 0; i < n; i++) {
            if (keys[i].equals(key)) {
                return i;
            }
        }
        return -1;
    }
    public ST() {
        keys = new String[1];
        values = new int[1];
    }
    public boolean isEmpty() {
        return (n == 0);
    }
    public int size() {
        return n;
    }
    public boolean contains(String key) {
        return (find(key) != -1);
    }
    public void put(String key) {
        int res = find(key);
        if (res == -1) {
            if (n == keys.length) {
                makeBigger();
            }
            if (n < keys.length/4 && n > 1) {
                makeSmaller();
            }
            keys[n] = key;
            values[n]++;
            n++;
        }
        else {
            values[res]++;
        }
    }
    public int get(String key) {
        int res = find(key);
        if (res == -1) {
            return -1;
        }
        return values[res];
    }
    public void delete(String key) {
        int res = find(key);
        if (res != -1) {
            for (int i = res+1; i < n; i++) {
                keys[i-1] = keys[i];
                values[i-1] = values[i];
            }
            n--;
            keys[n] = null;
            values[n] = 0;
        }
    }
    public String max() {
        int max = 0;
        for (int i = 0; i < n; i++) {
            if (values[i] > values[max]) {
                max = i;
            }
        }
        return keys[max];
    }
    public String[] keys() {
        return keys;
    }
}