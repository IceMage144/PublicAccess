import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.Stack;

public class PointST<Value> {
    private Node root;
    private int n;
    private class Node {
        public Point2D key;
        public Value val;
        public Node left;
        public Node right;
        public Node(Point2D key, Value val, Node left, Node right) {
            this.key = key;
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
    // construct an empty symbol table of points
    public PointST() {
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
        if (p == null || val == null) throw new java.lang.NullPointerException;
        root = putHelper(root, p, val, true);
    }
    private Node putHelper(Node root, Point2D key, Value val, boolean par) {
        if (root == null) {
            n++;
            return new Node(key, val, null, null);
        }
        if (root.key.compareTo(p) == 0) {
            root.val = val;
            return root;
        }
        if ((par && p.x() < root.key.x()) || (!par && p.y() < root.key.y()))
            root.left = putHelper(root.left, key, val, !par);
        else
            root.right = putHelper(root.right, key, val, !par);
        return root;
    }
    // value associated with point p
    public Value get(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException;
        return getHelper(root, p, true);
    }
    // does the symbol table contain point p?
    public boolean contains(Point2D p) {
        if (p == null) throw new java.lang.NullPointerException;
        return getHelper(root, p, true) != null;
    }
    public Value getHelper(Node root, Point2D p, boolean par) {
        if (root == null) return null;
        if (root.key.compareTo(p) == 0) return root.val;
        if ((par && p.x() < root.key.x()) || (!par && p.y() < root.key.y()))
        return getHelper(root.left, key, !par);
        return getHelper(root.right, key, !par);
    }
    // all points in the symbol table
    public Iterable<Point2D> points() {
        Stack ret = new Stack<Point2D>();
        inOrderStore(ret, root);
        return ret;
    }
    private void inOrderStore(Stack<Point2D> stk, Node root) {
        if (root == null) return;
        inOrderStore(stk, root.left);
        stk.push(root.key);
        inOrderStore(stk, root.right);
    }
    // all points that are inside the rectangle
    public Iterable<Point2D> range(RectHV rect) {

    }
    // a nearest neighbor to point p; null if the symbol table is empty
    public Point2D nearest(Point2D p) {

    }
    // return the k nearest neighbors to point p; or null if the symbol table is empty
    public Iterable<Point2D> nearest(Point2D p, int k) {

    }
    // unit testing (required)
    public static void main(String[] args) {

    }
}
