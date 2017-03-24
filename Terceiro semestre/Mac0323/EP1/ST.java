/*
	Nome: João Gabriel Basi
    NUSP: 9793801
*/    

public class ST {
    private String[] keys = null;
    private int[] values = null;
    private int n = 0;
    private void makeBigger() {
        int[] tmpV = new int[2*n];
        String[] tmpS = new String[2*n];
        for (int i = 0; i < n; i++) {
            tmpV[i] = values[i];
            tmpS[i] = keys[i];
            keys[i] = null;
        }
        keys = tmpS;
        values = tmpV;
    }
    private void makeSmaller() {
        int[] tmpV = new int[n/2];
        String[] tmpS = new String[n/2];
        for (int i = 0; i < n; i++) {
            tmpV[i] = values[i];
            tmpS[i] = keys[i];
            keys[i] = null;
        }
        keys = tmpS;
        values = tmpV;
    }
    private int find(String key) {
        for (int i = 0; i < n; i++) {
            if (keys[i].equals(key)) {
                return i;
            }
        }
        return -1;
    }
    public ST() {
        keys = new String[1];
        values = new int[1];
    }
    public String toString() {
        String ret = "{";
        for (int i = 0; i < n-1; i++) {
            ret += "\'" + keys[i] + "\': " + values[i] + " , ";
        }
        if (n != 0) {
            ret += "\'" + keys[n-1] + "\': " + values[n-1] + "}";
        }
        else {
            ret += "}";
        }
        return ret;
    }
    public boolean isEmpty() {
        return (n == 0);
    }
    public int size() {
        return n;
    }
    public boolean contains(String key) {
        return (find(key) != -1);
    }
    public void put(String key) {
        int res = find(key);
        if (res == -1) {
            if (n == keys.length) {
                makeBigger();
            }
            if (n < keys.length/4 && n > 1) {
                makeSmaller();
            }
            keys[n] = key;
            values[n]++;
            n++;
        }
        else {
            values[res]++;
        }
    }
    public int get(String key) {
        int res = find(key);
        if (res == -1) {
            return -1;
        }
        return values[res];
    }
    public void delete(String key) {
        int res = find(key);
        if (res != -1) {
            for (int i = res+1; i < n; i++) {
                keys[i-1] = keys[i];
                values[i-1] = values[i];
            }
            n--;
            keys[n] = null;
            values[n] = 0;
        }
    }
    public String max() {
        int max = 0;
        for (int i = 0; i < n; i++) {
            if (values[i] > values[max]) {
                max = i;
            }
        }
        return keys[max];
    }
    public String[] keys() {
        String[] ret = new String[n];
        for (int i = 0; i < n; i++) {
            ret[i] = keys[i];
        }
        return ret;
    }
}
