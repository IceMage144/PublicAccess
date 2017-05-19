import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RedBlackBST;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.MaxPQ;

public class PointST<Value> {
    private RedBlackBST<Point2D, Value> tree;
    private class DPPair implements Comparable<DPPair>{
        public double dist;
        public Point2D p;
        public DPPair(Point2D p, double dist) {
            this.p = p;
            this.dist = dist;
        }
        public int compareTo(DPPair that) {
            if (dist < that.dist)
                return -1;
            else if (dist > that.dist)
                return 1;
            return 0;
        }
    }
    // construct an empty symbol table of points
    public PointST() {
        tree = new RedBlackBST<Point2D, Value>();
    }
    // is the symbol table empty?
    public boolean isEmpty() {
        return tree.isEmpty();
    }
    // number of points
    public int size() {
        return tree.size();
    }
    // associate the value val with point p
    public void put(Point2D p, Value val) {
        if (p == null || val == null) throw new java.lang.NullPointerException();
        tree.put(p, val);
    }
    // value associated with point p
    public Value get(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException();
        return tree.get(p);
    }
    // does the symbol table contain point p?
    public boolean contains(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException();
        return tree.contains(p);
    }
    // all points in the symbol table
    public Iterable<Point2D> points() {
        return tree.keys();
    }
    // all points that are inside the rectangle
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new java.lang.NullPointerException();
        Point2D pmin = new Point2D(rect.xmin(), rect.ymin());
        Point2D pmax = new Point2D(rect.xmax(), rect.ymax());
        Stack<Point2D> ret = new Stack<Point2D>();
        for (Point2D p : tree.keys(pmin, pmax)) {
            if (p.x() >= pmin.x() && p.x() <= pmax.x())
                ret.push(p);
        }
        return ret;
    }
    // a nearest neighbor to point p; null if the symbol table is empty
    public Point2D nearest(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException();
        if (tree.isEmpty()) return null;
        double dist = 1.0/0.0;
        Point2D res = null;
        for (Point2D i : tree.keys()) {
            double xdiff = i.x()-p.x();
            double ydiff = i.y()-p.y();
            double iDist = xdiff*xdiff + ydiff*ydiff;
            if (iDist < dist) {
                dist = iDist;
                res = i;
            }
        }
        return res;
    }
    // return an iterable with the k nearest neighbors to point p
    public Iterable<Point2D> nearest(Point2D p, int k) {
        if (p == null) throw new java.lang.NullPointerException();
        if (tree.size() == 0 || k == 0) return null;
        if (k >= tree.size()) return points();
        MaxPQ<DPPair> pq = new MaxPQ<DPPair>();
        insertKNearest(p, k, pq);
        Stack<Point2D> stk = new Stack<Point2D>();
        for (DPPair pair : pq)
            stk.push(pair.p);
        return stk;
    }
    private void insertKNearest(Point2D p, int k, MaxPQ<DPPair> pq) {
        for (Point2D i : tree.keys()) {
            double dist = (i.x()-p.x())*(i.x()-p.x()) + (i.y()-p.y())*(i.y()-p.y());
            if (pq.size() < k)
                pq.insert(new DPPair(i, dist));
            else {
                DPPair pqmax = pq.max();
                if (dist < pqmax.dist) {
                    pq.delMax();
                    pq.insert(new DPPair(i, dist));
                }
            }
        }
    }
    // unit testing (required)
    public static void main(String[] args) {

    }
}
