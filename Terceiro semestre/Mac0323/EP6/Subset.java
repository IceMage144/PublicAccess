import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;

public class Subset {
    public static void main(String[] args) {
        if (args.length < 1) {
            StdOut.println("Usage: Subset <number of dequeues>");
            return;
        }
        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        int qnt = Integer.parseInt(args[0]);
        int inputs = 0;
        for (int i = 0; !StdIn.isEmpty(); i++) {
            String key = StdIn.readString();
            rq.enqueue(key);
            inputs++;
        }
        for (String str : rq)
            StdOut.println(str);
        StdOut.println("===========");
        for (int i = 0; i < qnt && i < inputs; i++)
            StdOut.println(rq.dequeue());
    }
}
