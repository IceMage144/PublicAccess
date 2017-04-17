import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.Stopwatch;
import edu.princeton.cs.algs4.StdOut;

public class PercolationStats {
    private double mi;
    private double sigma;
    private int trials;
    private Percolation tester;
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0)
            throw new java.lang.IllegalArgumentException();
        int row;
        int col;
        double sites;
        double msum = 0;
        double ssum = 0;
        double sqn = (double)(n*n);
        this.trials = trials;
        for (int i = 0; i < trials; i++) {
            tester = new Percolation(n);
            while (!tester.percolates()) {
                row = StdRandom.uniform(0, n);
                col = StdRandom.uniform(0, n);
                tester.open(row, col);
            }
            sites = tester.numberOfOpenSites()/sqn;
            msum += sites;
            ssum += sites*sites;
        }
        mi = msum/trials;
        sigma = Math.sqrt((ssum - trials*mi*mi)/(trials-1));
    }
    public double mean() {
        return mi;
    }
    public double stddev() {
        return sigma;
    }
    public double confidenceLow() {
        return mi - 1.96*sigma/Math.sqrt((double)trials);
    }
    public double confidenceHigh() {
        return mi + 1.96*sigma/Math.sqrt((double)trials);
    }
    public static void main(String[] args) {
        if (args.length < 2) {
            StdOut.println("Usage: PercolationStats <side of the grid> <trials>");
            return;
        }
        int side = Integer.parseInt(args[0]);
        int trials = Integer.parseInt(args[1]);
        Stopwatch sw = new Stopwatch();
        PercolationStats stats = new PercolationStats(side, trials);
        StdOut.println("Analisis time: " + sw.elapsedTime());
        StdOut.println("Mean: " + stats.mean());
        StdOut.println("Standard deviation: " + stats.stddev());
        StdOut.println("Confidence interval: [" + stats.confidenceLow() + ", " + stats.confidenceHigh() + "]");
    }
}
