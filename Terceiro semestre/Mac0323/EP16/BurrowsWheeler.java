import edu.princeton.cs.algs4.*;

public class BurrowsWheeler {
    private static class Pair implements Comparable<Pair> {
        char c;
        int idx;
        public Pair(char ch) {
            c = ch;
            idx = 0;
        }
        public int compareTo(Pair that) {
            return (int)(c - that.c);
        }
    }
    // apply Burrows-Wheeler transform, reading from standard input and writing to standard output
    public static void transform() {
        String text = StdIn.readAll();
        CircularSuffixArray csa = new CircularSuffixArray(text);
        int len = text.length();
        char[] sb = new char[len];
        int ptr, first = 0, top = 0;
        for (int i = 0; i < len; i++) {
            ptr = (csa.index(i)+len-1)%len;
            sb[top] = text.charAt(ptr);
            top++;
            if (csa.index(i) == 0)
                first = i;
        }
        BinaryStdOut.write(first);
        for (char c : sb)
            BinaryStdOut.write(c);
        BinaryStdOut.flush();
    }

    // apply Burrows-Wheeler inverse transform, reading from standard input and writing to standard output
    public static void inverseTransform() {
        int first = BinaryStdIn.readInt();
        StringBuffer sb = new StringBuffer();
        Pair[] bw, cbw;
        while (!BinaryStdIn.isEmpty())
            sb.append(BinaryStdIn.readChar());
        int len = sb.length();
        bw = new Pair[len];
        cbw = new Pair[len];
        for (int i = 0; i < len; i++) {
            bw[i] = new Pair(sb.charAt(i));
            cbw[i] = bw[i];
        }
        Merge.sort(bw);
        for (int i = 0; i < len; i++)
            bw[i].idx = i;
        int next = first;
        char[] buff = new char[len];
        buff[0] = bw[next].c;
        next = cbw[next].idx;
        for (int i = len-1; i > 0; i--) {
            buff[i] = bw[next].c;
            next = cbw[next].idx;
        }
        for (char c : buff)
            StdOut.print(c);
    }

    // if args[0] is '-', apply Burrows-Wheeler transform
    // if args[0] is '+', apply Burrows-Wheeler inverse transform
    public static void main(String[] args) {
        if (args[0].compareTo("-") == 0)
            BurrowsWheeler.transform();
        else
            BurrowsWheeler.inverseTransform();
    }

}
