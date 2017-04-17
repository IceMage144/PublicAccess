import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private WeightedQuickUnionUF ufop;
    private WeightedQuickUnionUF uffu;
    private int side;
    private int openSites;
    private boolean[][] opened;
    private final int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    public Percolation(int n) {
        if (n <= 0)
            throw new java.lang.IllegalArgumentException();
        ufop = new WeightedQuickUnionUF((n+2)*n);
        uffu = new WeightedQuickUnionUF((n+1)*n);
        opened = new boolean[n+2][n];
        side = n;
        openSites = 0;
        opened[0][0] = true;
        opened[n+1][0] = true;
        for (int i = 1; i < n; i++) {
            opened[0][i] = true;
            opened[n+1][i] = true;
            uffu.union(i-1, i);
            ufop.union(i-1, i);
            ufop.union((n+1)*n + i - 1, (n+1)*n + i);
        }
    }
    public void open(int row, int col) {
        if (row < 0 || row > side-1 || col < 0 || col > side-1)
            throw new java.lang.IndexOutOfBoundsException();
        if (opened[row+1][col] == true) return;
        int nrow;
        int ncol;
        opened[row+1][col] = true;
        for (int i = 0; i < 4; i++) {
            nrow = row + dirs[i][0];
            ncol = col + dirs[i][1];
            if (ncol < side && ncol >= 0 && opened[nrow+1][ncol] == true) {
                ufop.union(side*(row+1)+col, side*(nrow+1)+ncol);
                if (nrow < side)
                    uffu.union(side*(row+1)+col, side*(nrow+1)+ncol);
            }
        }
        openSites++;
    }
    public boolean isOpen(int row, int col) {
        if (row < 0 || row > side-1 || col < 0 || col > side-1)
            throw new java.lang.IndexOutOfBoundsException();
        return opened[row+1][col];
    }
    public boolean isFull(int row, int col) {
        if (row < 0 || row > side-1 || col < 0 || col > side-1)
            throw new java.lang.IndexOutOfBoundsException();
        return uffu.connected(0, side*(row+1)+col);
    }
    public int numberOfOpenSites() {
        return openSites;
    }
    public boolean percolates() {
        return ufop.connected(0, side*(side+1));
    }

}
