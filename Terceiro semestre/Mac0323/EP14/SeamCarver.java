import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;
import java.awt.Color;

public class SeamCarver {
    private double[][] energyM;
    private Color[][] pic;
    private int w, h;

    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        if (picture == null)
            throw new java.lang.NullPointerException();
        double delx, dely;
        w = picture.width();
        h = picture.height();
        energyM = new double[h][w];
        pic = new Color[h][w];
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                pic[i][j] = picture.get(j, i);
                delx = energy(picture.get((j-1+w)%w, i), picture.get((j+1)%w, i));
                dely = energy(picture.get(j, (i-1+h)%h), picture.get(j, (i+1)%h));
                energyM[i][j] = Math.sqrt(delx+dely);
            }
        }
    }
    // current picture
    public Picture picture() {
        Picture ret = new Picture(w, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                ret.set(j, i, pic[i][j]);
            }
        }
        return ret;
    }
    // width of current picture
    public int width() {
        return w;
    }
    // height of current picture
    public int height() {
        return h;
    }
    // energy of pixel at column x and row y
    public double energy(int x, int y) {
        if (x < 0 || x >= w || y < 0 || y >= h)
            throw new java.lang.IndexOutOfBoundsException();
        return energyM[y][x];
    }
    private double energy(Color col1, Color col2) {
        double[] vec1 = new double[3];
        double[] vec2 = new double[3];
        vec1[0] = col1.getBlue();
        vec1[1] = col1.getGreen();
        vec1[2] = col1.getRed();
        vec2[0] = col2.getBlue();
        vec2[1] = col2.getGreen();
        vec2[2] = col2.getRed();
        return Math.pow(vec1[0]-vec2[0],2) + Math.pow(vec1[1]-vec2[1],2) + Math.pow(vec1[2]-vec2[2],2);
    }
    // sequence of indices for vertical seam
    public int[] findVerticalSeam() {
        int[][] prev = new int[h][w];
        double[] total = new double[w];
        double[] newTotal;
        for (int j = 0; j < w; j++)
            total[j] = energyM[0][j];
        for (int i = 1; i < h; i++) {
            newTotal = new double[w];
            prev[i][0] = (total[0] <= total[1])? 0 : 1;
            newTotal[0] = energyM[i][0] + Math.min(total[0], total[1]);
            for (int j = 1; j < w-1; j++) {
                if (total[j] <= total[j-1] && total[j] <= total[j+1])
                    prev[i][j] = 0;
                else if (total[j-1] < total[j+1])
                    prev[i][j] = -1;
                else
                    prev[i][j] = 1;
                newTotal[j] = energyM[i][j] + Math.min(total[j-1], Math.min(total[j], total[j+1]));
            }
            prev[i][w-1] = (total[w-2] < total[w-1])? -1 : 0;
            newTotal[w-1] = energyM[i][w-1] + Math.min(total[w-2], total[w-1]);
            total = newTotal;
        }
        int index = findMinIndex(total);
        int[] path = new int[h];
        for (int i = h-1; i >= 0; i--) {
            path[i] = index;
            index += prev[i][index];
        }
        return path;
    }
    // sequence of indices for horizontal seam
    public int[] findHorizontalSeam() {
        int[][] prev = new int[h][w];
        double[] total = new double[h];
        double[] newTotal;
        for (int i = 0; i < h; i++)
            total[i] = energyM[i][0];
        for (int j = 1; j < w; j++) {
            newTotal = new double[h];
            prev[0][j] = (total[0] <= total[1])? 0 : 1;
            newTotal[0] = energyM[0][j] + Math.min(total[0], total[1]);
            for (int i = 1; i < h-1; i++) {
                if (total[i] <= total[i-1] && total[i] <= total[i+1])
                    prev[i][j] = 0;
                else if (total[i-1] < total[i+1])
                    prev[i][j] = -1;
                else
                    prev[i][j] = 1;
                newTotal[i] = energyM[i][j] + Math.min(total[i-1], Math.min(total[i], total[i+1]));
            }
            prev[h-1][j] = (total[h-2] < total[h-1])? -1 : 0;
            newTotal[h-1] = energyM[h-1][j] + Math.min(total[h-2], total[h-1]);
            total = newTotal;
        }
        int index = findMinIndex(total);
        int[] path = new int[w];
        for (int j = w-1; j >= 0; j--) {
            path[j] = index;
            index += prev[index][j];
        }
        return path;
    }
    private int findMinIndex(double[] vec) {
        int index = 0;
        double min = vec[0];
        for (int i = 0; i < vec.length; i++) {
            if (min > vec[i]) {
                min = vec[i];
                index = i;
            }
        }
        return index;
    }
    // remove horizontal seam from current picture
    public void removeHorizontalSeam(int[] seam) {
        if (seam == null)
            throw new java.lang.NullPointerException();
        if (h == 1 || w == 1)
            throw new java.lang.IllegalArgumentException();
        if (!verifySeam(seam, w, h))
            throw new java.lang.IllegalArgumentException();
        Color[][] newPic = new Color[h-1][w];
        double[][] newEnergyM = new double[h-1][w];
        int index;
        for (int j = 0; j < w; j++) {
            index = 0;
            for (int i = 0; i < h-1; i++, index++) {
                if (i == seam[j])
                    index++;
                newEnergyM[i][j] = energyM[index][j];
                newPic[i][j] = pic[index][j];
            }
        }
        h--;
        pic = newPic;
        recalcHorEnergy(newEnergyM, seam);
        energyM = newEnergyM;
    }
    private void recalcHorEnergy(double[][] energy, int[] seam) {
        double delx, dely;
        for (int j = 0; j < w; j++) {
            delx = energy(pic[seam[j]%h][(j-1+w)%w], pic[seam[j]%h][(j+1)%w]);
            dely = energy(pic[(seam[j]-1+h)%h][j], pic[(seam[j]+1)%h][j]);
            energy[seam[j]%h][j] = Math.sqrt(delx + dely);
            delx = energy(pic[(seam[j]-1+h)%h][(j-1+w)%w], pic[(seam[j]-1+h)%h][(j+1)%w]);
            dely = energy(pic[(seam[j]-2+h)%h][j], pic[seam[j]%h][j]);
            energy[(seam[j]-1+h)%h][j] = Math.sqrt(delx + dely);
        }
        delx = energy(pic[seam[0]%h][w-2], pic[seam[0]%h][0]);
        dely = energy(pic[(seam[0]-1+h)%h][w-1], pic[(seam[0]+1)%h][w-1]);
        energy[seam[0]%h][w-1] = Math.sqrt(delx + dely);
        delx = energy(pic[seam[w-1]%h][w-1], pic[seam[w-1]%h][1]);
        dely = energy(pic[(seam[w-1]-1+h)%h][0], pic[(seam[w-1]+1)%h][0]);
        energy[seam[w-1]%h][0] = Math.sqrt(delx + dely);
    }
    // remove vertical seam from current picture
    public void removeVerticalSeam(int[] seam) {
        if (seam == null)
            throw new java.lang.NullPointerException();
        if (h == 1 || w == 1)
            throw new java.lang.IllegalArgumentException();
        if (!verifySeam(seam, h, w))
            throw new java.lang.IllegalArgumentException();
        Color[][] newPic = new Color[h][w-1];
        double[][] newEnergyM = new double[h][w-1];
        int index;
        for (int i = 0; i < h; i++) {
            index = 0;
            for (int j = 0; j < w-1; j++, index++) {
                if (j == seam[i])
                    index++;
                newEnergyM[i][j] = energyM[i][index];
                newPic[i][j] = pic[i][index];
            }
        }
        w--;
        pic = newPic;
        recalcVerEnergy(newEnergyM, seam);
        energyM = newEnergyM;
    }
    private void recalcVerEnergy(double[][] energy, int[] seam) {
        double delx, dely;
        for (int i = 0; i < h; i++) {
            delx = energy(pic[i][(seam[i]-1+w)%w], pic[i][(seam[i]+1)%w]);
            dely = energy(pic[(i-1+h)%h][seam[i]%w], pic[(i+1)%h][seam[i]%w]);
            energy[i][seam[i]%w] = Math.sqrt(delx + dely);
            delx = energy(pic[i][(seam[i]-2+w)%w], pic[i][seam[i]%w]);
            dely = energy(pic[(i-1+h)%h][(seam[i]-1+w)%w], pic[(i+1)%h][(seam[i]-1+w)%w]);
            energy[i][(seam[i]-1+w)%w] = Math.sqrt(delx + dely);
        }
        delx = energy(pic[h-1][(seam[0]-1+w)%w], pic[h-1][(seam[0]+1)%w]);
        dely = energy(pic[h-2][seam[0]%w], pic[0][seam[0]%w]);
        energy[h-1][seam[0]%w] = Math.sqrt(delx + dely);
        delx = energy(pic[0][(seam[h-1]-1+w)%w], pic[0][(seam[h-1]+1)%w]);
        dely = energy(pic[h-1][seam[h-1]%w], pic[1][seam[h-1]%w]);
        energy[0][seam[h-1]%w] = Math.sqrt(delx + dely);
    }
    private boolean verifySeam(int[] seam, int mainDim, int auxDim) {
        if (seam.length != mainDim)
            return false;
        for (int i = 1; i < mainDim; i++) {
            if (seam[i] < 0 || seam[i] >= auxDim)
                return false;
            if (seam[i] - seam[i-1] > 1 || seam[i] - seam[i-1] < -1)
                return false;
        }
        return true;
    }
    // do unit testing of this class
    public static void main(String[] args) {

    }
}
