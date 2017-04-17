import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import java.util.Iterator;

public class Solver {
    private MinPQ<SearchNode> pq;
    private Stack<Board> tracer;
    // This class holds a board and some informations about it
    private class SearchNode implements Comparable<SearchNode> {
        public Board b;
        public SearchNode prev;
        public SearchNode tprev;
        public int move;
        public int pri;
        public SearchNode(Board b, SearchNode prev, SearchNode tprev, int move) {
            this.b = b;
            this.prev = prev;
            this.tprev = tprev;
            this.move = move;
            pri = b.manhattan()+move;
        }
        public int compareTo(SearchNode that) {
            if (pri < that.pri)
                return -1;
            else if (pri > that.pri)
                return 1;
            return 0;
        }
    }
    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial) {
        if (initial == null)
            throw new java.lang.NullPointerException();
        SearchNode ptr = new SearchNode(initial, null, null, 0);
        SearchNode tprev = null;
        int move;
        tracer = new Stack<Board>();
        if (!initial.isSolvable()) {
            StdOut.println("Unsolvable puzzle");
            throw new java.lang.IllegalArgumentException();
        }
        pq = new MinPQ<SearchNode>();
        while (!ptr.b.isGoal()) {
            move = ptr.move;
            tprev = ptr.tprev;
            for (Board b : ptr.b.neighbors()) {
                if ((tprev != null && !tprev.b.equals(b)) || tprev == null)
                    pq.insert(new SearchNode(b, ptr, ptr.prev, move+1));
            }
            ptr = pq.delMin();
        }
        //StdOut.println(ptr.b);
        while (ptr != null) {
            tracer.push(ptr.b);
            ptr = ptr.prev;
        }
    }
    // min number of moves to solve initial board
    public int moves() {
        return tracer.size()-1;
    }
    // sequence of boards in a shortest solution
    public Iterable<Board> solution() {
        return tracer;
    }
    // unit testing
    public static void main(String[] args) {
        String filename = args[0];
        In in = new In(filename);
        int size = in.readInt();
        int[][] tileAt = new int[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                tileAt[i][j] = in.readInt();
            }
        }
        Board ini = new Board(tileAt);
        Solver solv = new Solver(ini);
        for (Board b : solv.solution()) {
            StdOut.println(b);
        }
    }
}
