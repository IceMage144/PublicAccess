import java.util.Iterator;

public class Board {
    private final int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    private Board[] neighs;
    private int[][] tiles;
    private int n;
    private int ham;
    private int man;
    private int[] zero;
    // construct a board from an N-by-N array of tiles
    // (where tiles[i][j] = tile at row i, column j)
    public Board(int[][] tiles) {
        this.tiles = tiles;
        n = tiles.length;
        ham = 0;
        man = 0;
        zero = new int[2];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tiles[i][j] == 0) {
                    zero[0] = i;
                    zero[1] = j;
                    continue;
                }
                if (i*n+j+1 != tiles[i][j]) {
                    int val = tiles[i][j]-1;
                    man += Math.abs(i-val/n) + Math.abs(j-val%n);
                    ham++;
                }
            }
        }
    }
    // return tile at row i, column j (or 0 if blank)
    public int tileAt(int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= n)
            throw new java.lang.IndexOutOfBoundsException();
        return tiles[i][j];
    }
    // board size N
    public int size() {
        return n;
    }
    // number of tiles out of place
    public int hamming() {
        return ham;
    }
    // sum of Manhattan distances between tiles and goal
    public int manhattan() {
        return man;
    }
    // is this board the goal board?
    public boolean isGoal() {
        return (man == 0);
    }
    // is this board solvable?
    public boolean isSolvable() {
        int inversions = 0;
        int zrow = 0;
        int beg;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tiles[i][j] == 0)
                    zrow = i;
                else {
                    for (int k = i; k < n; k++) {
                        beg = (k == i)? j+1 : 0;
                        for (int l = beg; l < n; l++) {
                            if (tiles[i][j] != 0 && tiles[k][l] != 0 && tiles[i][j] > tiles[k][l])
                                inversions++;
                        }
                    }
                }
            }
        }
        if (n%2 == 1)
            return (inversions%2 == 0);
        return ((inversions+zrow)%2 == 1);
    }
    // does this board equal y?
    public boolean equals(Object y) {
        if (y == this) return true;
        if (y == null) return false;
        if (y.getClass() != this.getClass()) return false;
        Board that = (Board)y;
        if (that.manhattan() != manhattan() || that.hamming() != hamming()) return false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tileAt(i, j) != that.tileAt(i, j))
                    return false;
            }
        }
        return true;
    }
    // all neighboring boards
    public Iterable<Board> neighbors() {
        return new ListBoards();
    }
    // string representation of this board (in the output format specified below)
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(n + "\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                res.append(String.format(" %2d ", tileAt(i, j)));
            res.append("\n");
        }
        return res.toString();
    }
    private void swap(int[][] mat, int[] pos1, int[] pos2) {
        int aux = mat[pos1[0]][pos1[1]];
        mat[pos1[0]][pos1[1]] = mat[pos2[0]][pos2[1]];
        mat[pos2[0]][pos2[1]] = aux;
    }
    private class ListBoards implements Iterable<Board> {
        private Board[] list;
        private int top = 0;
        public Iterator<Board> iterator() {
            int[][] mptr;
            int[] npos = new int[2];
            list = new Board[4];
            for (int i = 0; i < 4; i++) {
                npos[0] = zero[0]+dirs[i][0];
                npos[1] = zero[1]+dirs[i][1];
                if (npos[0] >= 0 && npos[0] < n && npos[1] >= 0 && npos[1] < n) {
                    mptr = new int[n][n];
                    for (int j = 0; j < n; j++)
                        mptr[j] = tiles[j].clone();
                    swap(mptr, zero, npos);
                    list[top] = new Board(mptr);
                    top++;
                }
            }
            return new BoardsIterator();
        }
        private class BoardsIterator implements Iterator<Board> {
            private int counter = 0;
            public boolean hasNext() {
                return counter < top;
            }
            public Board next() {
                Board ptr = list[counter];
                counter++;
                return ptr;
            }
            public void remove() {
                throw new UnsupportedOperationException();
            }
        }
    }
    // unit testing
    public static void main(String[] args) {

    }
}
