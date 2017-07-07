import edu.princeton.cs.algs4.*;

public class CBSPaths {
    public static void main(String[] args) {
        int mpBeg, endNum;
        String from, to;
        boolean b;
        double time, mpDist;
        int counter = 0;
        int n = StdIn.readInt();
        int m = StdIn.readInt();
        int k = StdIn.readInt();
        int[] cbsBegs = new int[k];
        AdjMatrixEdgeWeightedDigraph graph = new AdjMatrixEdgeWeightedDigraph(n);
        LinearProbingHashST<String, Integer> nameToNum = new LinearProbingHashST<>(n);
        MinPQ<String> pq = new MinPQ<>();
        for (int i = 0; i < m; i++) {
            from = StdIn.readString();
            to = StdIn.readString();
            time = StdIn.readDouble();
            if (!nameToNum.contains(from))
                nameToNum.put(from, counter++);
            if (!nameToNum.contains(to))
                nameToNum.put(to, counter++);
            graph.addEdge(new DirectedEdge(nameToNum.get(from), nameToNum.get(to), time));
        }
        for (int i = 0; i < k; i++)
            cbsBegs[i] = nameToNum.get(StdIn.readString());
        mpBeg = nameToNum.get(StdIn.readString());
        FloydWarshall dists = new FloydWarshall(graph);
        for (String endName : nameToNum.keys()) {
            endNum = nameToNum.get(endName);
            mpDist = dists.dist(mpBeg, endNum);
            b = false;
            for (int cbsBeg : cbsBegs) {
                if (dists.dist(cbsBeg, endNum) >= mpDist) {
                    b = true;
                    break;
                }
            }
            if (!b)
                pq.insert(endName);
        }
        if (pq.isEmpty())
            StdOut.println("VENHA COMIGO PARA CURITIBA");
        else {
            for (String key : pq)
                StdOut.println(key);
        }
    }
}
