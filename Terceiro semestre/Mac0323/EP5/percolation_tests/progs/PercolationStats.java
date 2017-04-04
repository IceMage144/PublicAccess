import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.Stopwatch;
import edu.princeton.cs.algs4.StdOut;

public class PercolationStats {
    private double mi;
    private double sigma;
    private int trials;
    private Percolation tester;
    public PercolationStats(int n, int trials) {
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
                row = StdRandom.uniform(0, n)+1;
                col = StdRandom.uniform(0, n)+1;
                tester.open(row, col);
            }
            sites = tester.numberOfOpenSites()/sqn;
            msum += sites;
            ssum += sites*sites;
        }
        mi = msum/(double)trials;
        sigma = ssum/(double)(trials-1) - mi*mi;
    }
    public double mean() {
        return mi;
    }
    public double stddev() {
        return sigma; // Sigma, não sigma^2
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
