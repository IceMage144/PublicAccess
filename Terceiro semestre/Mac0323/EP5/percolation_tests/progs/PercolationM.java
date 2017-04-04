public class Percolation {
    private int[][] opened;
    private int n;
    private int openSites;
    private final int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    public Percolation(int n) {
        this.n = n;
        opened = new int[n+2][n];
        openSites = 0;
        for (int i = 0; i < n; i++) {
            opened[0][i] = 2;
            opened[n+1][i] = 1;
        }
    }
    public void open(int row, int col) {
        if (row < 1 || row > n || col < 1 || col > n) return;
        if (opened[row][col-1] == 1) return;
        opened[row][col-1] = 1;
        openSites++;
        for (int i = 0; i < 4; i++)
            refresh(row + dirs[i][0], col + dirs[i][1] - 1, 1);
    }
    public boolean isFull(int row, int col) {
        if (row < 1 || row > n || col < 1 || col > n) return false;
        return opened[row][col-1] == 2;
    }
    public boolean isOpen(int row, int col) {
        if (row < 1 || row > n || col < 1 || col > n) return false;
        return opened[row][col-1] == 1;
    }
    public int numberOfOpenSites() {
        return openSites;
    }
    public boolean percolates() {
        return opened[n+1][0] == 2;
    }
    private void refresh(int row, int col, int state) {
        if (row < 0 || row > n+1 || col < 0 || col >= n) return;
        if (opened[row][col] == state || opened[row][col] == 0) return;
        state = Math.max(state, opened[row][col]);
        opened[row][col] = state;
        for (int i = 0; i < 4; i++)
            refresh(row + dirs[i][0], col + dirs[i][1], state);
    }
}
