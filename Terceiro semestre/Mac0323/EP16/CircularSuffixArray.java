import edu.princeton.cs.algs4.*;

public class CircularSuffixArray {
    String text;
    Entry[] csa;
    private class Entry implements Comparable<Entry> {
        public int beg;
        public Entry(int beg) {
            this.beg = beg;
        }
        public int compareTo(Entry that) {
            int len = text.length();
            int ptr1 = beg;
            int ptr2 = that.beg;
            for (int i = 0; i < len; i++) {
                if (text.charAt(ptr1) != text.charAt(ptr2))
                    return (int)(text.charAt(ptr1) - text.charAt(ptr2));
                ptr1 = (ptr1+1)%len;
                ptr2 = (ptr2+1)%len;
            }
            return 0;
        }
    }
    // circular suffix array of s
    public CircularSuffixArray(String s) {
        if (s == null) throw new java.lang.NullPointerException();
        csa = new Entry[s.length()];
        text = s;
        for (int i = 0; i < s.length(); i++) {
            csa[i] = new Entry(i);
        }
        Merge.sort(csa);
    }
    // length of s
    public int length() {
        return csa.length;
    }
    // returns index of ith sorted suffix
    public int index(int i) {
        if (i >= length() || i < 0) throw new java.lang.IndexOutOfBoundsException();
        return csa[i].beg;
    }
    // unit testing (not graded)
    public static void main(String[] args) {
        String abra = "ABRACADABRA!";
        CircularSuffixArray csa = new CircularSuffixArray(abra);
        for (int i = 0; i < abra.length(); i++)
            StdOut.println(csa.index(i));
    }
}
