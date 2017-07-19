import edu.princeton.cs.algs4.*;

public class MoveToFront {
    private static int findAndMove(int[] arr, int num) {
        int aux;
        int mem = arr[0];
        for (int i = 0; i < arr.length; i++) {
            aux = arr[i];
            arr[i] = mem;
            mem = aux;
            if (mem == num) {
                arr[0] = mem;
                return i;
            }
        }
        return -1;
    }
    private static char moveAndFind(char[] arr, int pos) {
        char mem = arr[pos];
        for (int i = pos; i > 0; i--)
            arr[i] = arr[i-1];
        arr[0] = mem;
        return arr[0];
    }
    // apply move-to-front encoding, reading from standard input and writing to standard output
    public static void encode() {
        int[] alpha = new int[256];
        char pos;
        int c;
        for (int i = 0; i < 256; i++)
            alpha[i] = i;
        while (!BinaryStdIn.isEmpty()) {
            c = BinaryStdIn.readChar();
            pos = (char)findAndMove(alpha, c);
            BinaryStdOut.write(pos);
        }
        BinaryStdOut.flush();
    }

    // apply move-to-front decoding, reading from standard input and writing to standard output
    public static void decode() {
        char[] alpha = new char[256];
        char c;
        int pos;
        for (int i = 0; i < 256; i++)
            alpha[i] = (char)i;
        while (!BinaryStdIn.isEmpty()) {
            pos = (int)BinaryStdIn.readChar();
            //StdOut.println(pos);
            c = moveAndFind(alpha, pos);
            StdOut.print(c);
        }
    }

    // if args[0] is '-', apply move-to-front encoding
    // if args[0] is '+', apply move-to-front decoding
    public static void main(String[] args) {
        if (args[0].compareTo("-") == 0)
            MoveToFront.encode();
        else
            MoveToFront.decode();
    }
}
