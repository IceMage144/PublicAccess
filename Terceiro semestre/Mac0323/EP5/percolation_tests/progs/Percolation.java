import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private WeightedQuickUnionUF uf;
    private int side;
    private int openSites;
    private boolean[][] opened;
    private final int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    public Percolation(int n) {
        uf = new WeightedQuickUnionUF((n+2)*n);
        opened = new boolean[n+2][n];
        side = n;
        openSites = 0;
        opened[0][0] = true;
        opened[n+1][0] = true;
        for (int i = 1; i < n; i++) {
            opened[0][i] = true;
            opened[n+1][i] = true;
            uf.union(i-1, i);
            uf.union((n+1)*n + i - 1, (n+1)*n + i);
        }
    }
    public void open(int row, int col) {
        if (row < 1 || row > side || col < 1 || col > side) return;
        if (opened[row][col-1] == true) return;
        int nrow;
        int ncol;
        opened[row][col-1] = true;
        for (int i = 0; i < 4; i++) {
            nrow = row + dirs[i][0];
            ncol = col + dirs[i][1];
            if (ncol <= side && ncol > 0 && opened[nrow][ncol-1] == true) {
                //StdOut.println((side*row+col-1) + " united with " + (side*nrow+ncol-1));
                uf.union(side*row+col-1, side*nrow+ncol-1);
            }
        }
        openSites++;
    }
    public boolean isOpen(int row, int col) {
        if (row < 1 || row > side || col < 1 || col > side) return false;
        return opened[row][col-1];
    }
    public boolean isFull(int row, int col) {
        if (row < 1 || row > side || col < 1 || col > side) return false;
        return uf.connected(0, side*row+col-1);
    }
    public int numberOfOpenSites() {
        return openSites;
    }
    public boolean percolates() {
        return uf.connected(0, side*(side+1));
    }

}
