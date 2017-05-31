import edu.princeton.cs.algs4.SeparateChainingHashST;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;

public class WordFinder {
    private SeparateChainingHashST<String, Integer> gst;
    private SeparateChainingHashST<String, Boolean>[] stVec;
    private int n;
    public WordFinder(String[] vec) {
        if (vec == null) throw new java.lang.NullPointerException();
        n = vec.length;
        stVec = (SeparateChainingHashST<String, Boolean>[]) new SeparateChainingHashST[n];
        gst = new SeparateChainingHashST<>();
        for (int i = 0; i < n; i++)
            stVec[i] = new SeparateChainingHashST<>();
        for (int i = 0; i < n; i++) {
            for (String s : vec[i].split(" ")) {
                if (stVec[i].get(s) == null) {
                    stVec[i].put(s, true);
                    if (gst.get(s) == null)
                        gst.put(s, 1);
                    else
                        gst.put(s, gst.get(s)+1);
                }
            }
        }

    }

    public String getMax() {
        int top = 0;
        int mem = 0;
        String ret = null;
        for (String s : gst.keys()) {
            mem = gst.get(s);
            if (mem > top) {
                top = mem;
                ret = s;
            }
        }
        return ret;
    }

    public String containedIn(int a, int b) {
        for (String s : stVec[a].keys()) {
            if (stVec[b].contains(s))
                return s;
        }
        return null;
    }

    public int[] appearsIn(String s) {
        if (s == null) throw new java.lang.NullPointerException();
        Queue<Integer> queue = new Queue<>();
        for (int i = 0; i < n; i++) {
            if (stVec[i].contains(s))
                queue.enqueue(i);
        }
        int[] ret = new int[queue.size()];
        int counter = 0;
        for (int i : queue) {
            ret[counter] = i;
            counter++;
        }
        return ret;
    }

    public String vec2str(int[] vec) {
        StringBuilder res = new StringBuilder();
        res.append("[");
        for (int i = 0; i < vec.length; i++)
            res.append(" " + vec[i] + ((i == vec.length-1)? " " : ","));
        res.append("]");
        return res.toString();
    }

    public static void main(String[] args) {
        Queue<String> queue = new Queue<>();
        /*for (int i = 0; !StdIn.isEmpty(); i++) {
            String line = StdIn.readLine();
            queue.enqueue(line);
            StdOut.println("Gotcha!");
        }*/
        queue.enqueue("Hello how are you");
        queue.enqueue("Im fine and you");
        queue.enqueue("Im fine too");
        queue.enqueue("nyan nyan nyan nyan");
        queue.enqueue("how fine are you too");
        StdOut.println("========== Inputs ===========");
        StdOut.println("0: \"Hello how are you\"");
        StdOut.println("1: \"Im fine and you\"");
        StdOut.println("2: \"Im fine too\"");
        StdOut.println("3: \"nyan nyan nyan nyan\"");
        StdOut.println("4: \"how fine are you too\"");

        String[] vec = new String[queue.size()];
        int counter = 0;
        for (String s : queue) {
            vec[counter] = s;
            counter++;
        }
        WordFinder wf = new WordFinder(vec);

        StdOut.println("========== Results ==========");
        StdOut.println("Get max: " + wf.getMax());
        StdOut.println("Contained in 1 and 4: " + wf.containedIn(1, 4));
        StdOut.println("Contained in 0 and 3: " + wf.containedIn(0, 3));
        StdOut.println("Contained in 2 and 4: " + wf.containedIn(2, 4));
        StdOut.println("Contained in 3 and 3: " + wf.containedIn(3, 3));
        StdOut.println("\"nyan\" appears in: " + wf.vec2str(wf.appearsIn("nyan")));
        StdOut.println("\"too\" appears in: " + wf.vec2str(wf.appearsIn("too")));
        StdOut.println("\"fine\" appears in: " + wf.vec2str(wf.appearsIn("fine")));
        StdOut.println("\"Im\" appears in: " + wf.vec2str(wf.appearsIn("Im")));
        StdOut.println("\"nothing\" appears in: " + wf.vec2str(wf.appearsIn("nothing")));
    }
}
