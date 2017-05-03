import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RedBlackBST;

public class PointST<Value> {
    private RedBlackBST tree;
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
        if (p == null || val == null) throw new java.lang.NullPointerException;
        tree.put(p, val);
    }
    // value associated with point p
    public Value get(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException;
        return tree.get(p);
    }
    // does the symbol table contain point p?
    public boolean contains(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException;
        return tree.contains(p);
    }
    // all points in the symbol table
    public Iterable<Point2D> points() {
        return tree.keys();
    }
    // all points that are inside the rectangle
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new java.lang.NullPointerException;
        Point2D pmin = new Point2D(rect.xmin(), rect.ymin());
        Point2D pmax = new Point2D(rect.xmax(), rect.ymax());
        return tree.keys(pmin, pmax);
    }
    // a nearest neighbor to point p; null if the symbol table is empty
    public Point2D nearest(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException;
        if (tree.isEmpty()) return null;
        double dist = 1000000000.0;
        Point2D res = null;
        for (Point2D i : tree.keys()) {
            double iDist = (i.x()-p.x())*(i.x()-p.x()) + (i.y()-p.y())*(i.y()-p.y());
            if (iDist < dist) {
                dist = iDist;
                res = i;
            }
        }
        return res;

    }
    // unit testing (required)
    public static void main(String[] args) {

    }
}
