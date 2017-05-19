import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.MaxPQ;

public class KdTreeST<Value> {
    private Node root;
    private int n;
    private class Node {
        public Point2D key;
        public Value val;
        public Node left;
        public Node right;
        public boolean par;
        public Node(Point2D key, Value val, boolean par, Node left, Node right) {
            this.key = key;
            this.val = val;
            this.left = left;
            this.right = right;
            this.par = par;
        }
    }
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
    public KdTreeST() {
        root = null;
    }
    // is the symbol table empty?
    public boolean isEmpty() {
        return n == 0;
    }
    // number of points
    public int size() {
        return n;
    }
    // associate the value val with point p
    public void put(Point2D p, Value val) {
        if (p == null || val == null) throw new java.lang.NullPointerException();
        root = putHelper(root, p, val, true);
    }
    private Node putHelper(Node root, Point2D key, Value val, boolean par) {
        if (root == null) {
            n++;
            return new Node(key, val, par, null, null);
        }
        if (root.key.compareTo(key) == 0) {
            root.val = val;
            return root;
        }
        if ((par && key.x() < root.key.x()) || (!par && key.y() < root.key.y()))
            root.left = putHelper(root.left, key, val, !par);
        else
            root.right = putHelper(root.right, key, val, !par);
        return root;
    }
    // value associated with point p
    public Value get(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException();
        return getHelper(root, p);
    }
    // does the symbol table contain point p?
    public boolean contains(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException();
        return getHelper(root, p) != null;
    }
    public Value getHelper(Node root, Point2D p) {
        if (root == null) return null;
        if (root.key.compareTo(p) == 0) return root.val;
        boolean par = root.par;
        if ((par && p.x() < root.key.x()) || (!par && p.y() < root.key.y()))
            return getHelper(root.left, p);
        return getHelper(root.right, p);
    }
    // all points in the symbol table
    public Iterable<Point2D> points() {
        Stack<Point2D> ret = new Stack<Point2D>();
        if (root == null) return ret;
        Queue<Node> queue = new Queue<Node>();
        Node ptr = root;
        ret.push(ptr.key);
        if (ptr.left != null)
            queue.enqueue(ptr.left);
        if (ptr.right != null)
            queue.enqueue(ptr.right);
        while (!queue.isEmpty()) {
            ptr = queue.dequeue();
            ret.push(ptr.key);
            if (ptr.left != null)
                queue.enqueue(ptr.left);
            if (ptr.right != null)
                queue.enqueue(ptr.right);
        }
        return ret;
    }
    // all points that are inside the rectangle
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new java.lang.NullPointerException();
        Stack<Point2D> ret = new Stack<Point2D>();
        rectSearch(ret, rect, root);
        return ret;
    }
    private void rectSearch(Stack<Point2D> stk, RectHV rect, Node root) {
        if (root == null) return;
        boolean lessThanXMax = root.key.x() <= rect.xmax();
        boolean moreThanXMin = root.key.x() >= rect.xmin();
        boolean lessThanYMax = root.key.y() <= rect.ymax();
        boolean moreThanYMin = root.key.y() >= rect.ymin();
        if (moreThanXMin && lessThanXMax && moreThanYMin && lessThanYMax)
            stk.push(root.key);
        if (root.par) {
            if (lessThanXMax)
                rectSearch(stk, rect, root.right);
            if (moreThanXMin)
                rectSearch(stk, rect, root.left);
        }
        else {
            if (lessThanYMax)
                rectSearch(stk, rect, root.right);
            if (moreThanYMin)
                rectSearch(stk, rect, root.left);
        }
    }
    //======= Mudar ========//
    // a nearest neighbor to point p; null if the symbol table is empty
    public Point2D nearest(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException();
        if (root == null) return null;
        DPPair ret = new DPPair(null, 1.0/0.0);
        nearSearch(root, p, ret);
        return ret.p;
    }
    private void nearSearch(Node root, Point2D p, DPPair best) {
        if (root == null) return;
        double xdiff = root.key.x() - p.x();
        double ydiff = root.key.y() - p.y();
        double dist = Math.sqrt(xdiff*xdiff + ydiff*ydiff);
        if (dist < best.dist) {
            best.dist = dist;
            best.p = root.key;
        }
        if (root.par) {
            if (root.key.x() < p.x() + best.dist)
                nearSearch(root.right, p, best);
            if (root.key.x() > p.x() - best.dist)
                nearSearch(root.left, p, best);
        }
        else {
            if (root.key.y() < p.y() + best.dist)
                nearSearch(root.right, p, best);
            if (root.key.y() > p.y() - best.dist)
                nearSearch(root.left, p, best);
        }
    }
    // return an iterable with the k nearest neighbors to point p
    public Iterable<Point2D> nearest(Point2D p, int k) {
        if (p == null) throw new java.lang.NullPointerException();
        if (root == null || k == 0) return null;
        if (k >= n) return points();
        MaxPQ<DPPair> pq = new MaxPQ<DPPair>();
        kNearSearch(root, p, pq, k);
        Stack<Point2D> stk = new Stack<Point2D>();
        for (DPPair pair : pq)
            stk.push(pair.p);
        return stk;
    }
    private void kNearSearch(Node root, Point2D p, MaxPQ<DPPair> pq, int k) {
        if (root == null) return;
        double xdiff = root.key.x() - p.x();
        double ydiff = root.key.y() - p.y();
        double dist = Math.sqrt(xdiff*xdiff + ydiff*ydiff);
        Point2D best = root.key;
        if (pq.size() < k)
            pq.insert(new DPPair(root.key, dist));
        else {
            DPPair pqmax = pq.max();
            if (dist < pqmax.dist) {
                pq.delMax();
                pq.insert(new DPPair(root.key, dist));
            }
            else {
                best = pqmax.p;
                dist = pqmax.dist;
            }
        }
        if (root.par) {
            if (root.key.x() < best.x() + dist)
                kNearSearch(root.right, p, pq, k);
            if (root.key.x() > best.x() - dist)
                kNearSearch(root.left, p, pq, k);
        }
        else {
            if (root.key.y() < best.y() + dist)
                kNearSearch(root.right, p, pq, k);
            if (root.key.y() > best.y() - dist)
                kNearSearch(root.left, p, pq, k);
        }
    }
    // unit testing (required)
    public static void main(String[] args) {

    }
}
