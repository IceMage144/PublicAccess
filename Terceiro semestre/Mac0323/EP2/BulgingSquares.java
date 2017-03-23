/*
    Nome: João Gabriel Basi
    NUSP: 9793801
*/


/******************************************************************************
 *  Compilation:  javac BulgingSquares.java
 *  Execution:    java BulgingSquares
 *  Dependencies: StdDraw.java, java.awt.Color
 *
 *  Program draws an optical illusion from Akiyoshi Kitaoka. The center appears
 *  to bulge outwards even though all squares are the same size.
 *
 *  meu_prompt > java BulgingSquares
 *
 *  Exercise 14 http://introcs.cs.princeton.edu/java/15inout/
 *
 ******************************************************************************/

// Standard draw. This class provides a basic capability for creating
// drawings with your programs. It uses a simple graphics model that
// allows you to create drawings consisting of points, lines, and
// curves in a window on your computer and to save the drawings to a
// file.
// https://www.ime.usp.br/~pf/sedgewick-wayne/stdlib/documentation/index.html
// http://introcs.cs.princeton.edu/java/stdlib/javadoc/StdDraw.html
import edu.princeton.cs.algs4.StdDraw; // StdDraw.setXscale, StdDraw.setYscale, ...

import edu.princeton.cs.algs4.StdOut;

import java.awt.Color; // StdDraw.WHITE, StdDraw.BLACK

public class BulgingSquares {
    // constantes... vixe! use se desejar
    private static final double XMIN   = -75;
    private static final double XMAX   =  75;
    private static final double YMIN   = -75;
    private static final double YMAX   =  75;
    private static final double MARGIN =   2;
    private static final double RMAX   =   5;
    private static final double DMAX   =   2*RMAX;
    private static final double RMIN   =   DMAX/7.0;
    private static final double DMIN   =   2*RMIN;

    public static void main(String[] args) {
        // set the scale of the coordinate system
        StdDraw.setXscale(XMIN-MARGIN, XMAX+MARGIN);
        StdDraw.setYscale(YMIN-MARGIN, YMAX+MARGIN);
        StdDraw.enableDoubleBuffering();

        // clear the background
        StdDraw.clear(StdDraw.WHITE);

        // Escreva sua solução a seguir
        StdDraw.setPenColor();
        double parity = 1.0;
        for (double i = XMIN + RMAX; i < XMAX; i += DMAX) {
            parity = (parity == 0.0)? 1.0 : 0.0;
            for (double j = YMIN + RMAX + parity*DMAX; j < YMAX; j += 2*DMAX)
                StdDraw.filledSquare(i, j, RMAX);
        }
        double i = 5*RMIN;
        double j = 2*RMIN;
        double k = i;
        while (i < XMAX) {
            j = 2*RMIN;
            k = i;
            parity = 0.0;
            while (k > 0) {
                if (k < XMAX - DMAX && j < YMAX - DMAX) {
                    StdDraw.filledSquare(k, j, RMIN);
                    StdDraw.filledSquare(-k, j, RMIN);
                    StdDraw.filledSquare(k, -j, RMIN);
                    StdDraw.filledSquare(-k, -j, RMIN);
                }
                j += (parity + 3)*RMIN;
                k -= (parity + 3)*RMIN;
                parity = (parity == 0.0)? 1.0 : 0.0;
            }
            i += DMAX;
            if (StdDraw.getPenColor() == StdDraw.WHITE)
                StdDraw.setPenColor(StdDraw.BLACK);
            else
                StdDraw.setPenColor(StdDraw.WHITE);
        }
        StdDraw.setPenColor(StdDraw.WHITE);
        j = 5*RMIN + 2*DMAX;
        k = XMAX - (1.5*RMIN + 2*DMAX);
        parity = 1.0;
        while (k > 5*RMAX) {
            StdDraw.filledSquare(k, j, RMIN);
            StdDraw.filledSquare(-k, j, RMIN);
            StdDraw.filledSquare(k, -j, RMIN);
            StdDraw.filledSquare(-k, -j, RMIN);
            j += (parity + 3)*RMIN;
            k -= (parity + 3)*RMIN;
            parity = (parity == 0.0)? 1.0 : 0.0;
        }

        // copy offscreen buffer to onscreen
        StdDraw.show();
    }

}
