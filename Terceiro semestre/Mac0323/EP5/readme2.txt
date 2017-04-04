/******************************************************************************
 *  Name:
 *  NetID:
 *  Precept:
 *
 *  Partner Name:    N/A
 *  Partner NetID:   N/A
 *  Partner Precept: N/A
 *
 *  Operating system:
 *  Compiler:
 *  Text editor / IDE:
 *
 *  Have you taken (part of) this course before:
 *  Have you taken (part of) the Coursera course Algorithm, Part I:
 *
 *  Hours to complete assignment (optional):
 *
 ******************************************************************************/


/******************************************************************************
 *  Describe how you implemented Percolation.java. How did you check
 *  whether the system percolates?
 *****************************************************************************/
Foi feita uma grade de n+2 linhas por n colunas. Cada casa da grade recebeu um
número, de 0 à n*(n+2)-1. O número de uma casa é definido por linha*n+coluna-1.
Se duas casas estão abertas e são vizinhas, então elas são unidas. As casas da
primeira e última linhas não fazem parte da vizualização da grade, estão
inicialmente abertas e unidas com as outras de sua respectiva linha, assim, se
uma casa estiver no grupo da primeira linha, ela está cheia, e se uma casa da
última linha está no grupo de uma casa da primeira linha, o sistema percola.


/******************************************************************************
 *  Using Percolation with QuickFindUF.java,  fill in the table below such that
 *  the N values are multiples of each other.

 *  Give a formula (using tilde notation) for the running time (in seconds) of
 *  PercolationStats.java as a function of both N and T. Be sure to give both
 *  the coefficient and exponent of the leading term. Your coefficients should
 *  be based on empirical data and rounded to two significant digits, such as
 *  5.3*10^-8 * N^5.0 T^1.5.
 *****************************************************************************/

T = 100 (keep T constant)

 N          time (seconds)
------------------------------
32              0.045   => 104857600 * 0,000000000429
64              0.358   => 1677721600 * 0,000000000213
128             4.909   => 26843545600 * 0,000000000183
256            76.509   => 429496729600 * 0,000000000178
512            // TODO: Estimated => 1216s = 20min


N = 100 (keep N constant)

 T          time (seconds)
------------------------------
32              0.666   =>  3200000000 * 0,000000000208
64              1.364   =>  6400000000 * 0,000000000213
128             2.706   =>  12800000000 * 0,000000000211
256             5.522   =>  25600000000 * 0,000000000211
512            11.081   =>  51200000000 * 0,000000000216


running time as a function of N and T:  ~(N^4*T*2*10^(-11))


/******************************************************************************
 *  Repeat the previous question, but use WeightedQuickUnionUF.java.
 *****************************************************************************/

T = 100 (keep T constant)

 N          time (seconds)
------------------------------
32              0.023      =>  777600  *  0,000000029578
64              0.061      =>  4665600  *  0,000000013074
128             0.125      =>  27993600  *  0,000000004465
256             0.424      =>  167961600  *  0,000000002524
512             1.766      =>  1007769600  *  0,000000001752
1024           10.955      =>  6046617600  *  0,000000001812
2048           60.776      =>  36279705600  *  0,000000001675


N = 100 (keep N constant)

 T          time (seconds)
------------------------------ 6,64385619
32              0.053      =>  4732329,542927103  *  0,0000000112
64              0.08       =>  9464659,085854206  *  0,000000008452
128             0.119      =>  18929318,171708412  *  0,000000006287
256             0.187      =>  37858636,343416823  *  0,000000004939
512             0.358      =>  75717272,686833646  *  0,000000004728
1024            0.665      =>  151434545,373667293  *  0,000000004391


running time as a function of N and T:  ~(T*N*3^(log(N)))     (log base 2)

/**********************************************************************
 *  How much memory (in bytes) does a Percolation object (which uses
 *  WeightedQuickUnionUF.java) use to store an N-by-N grid? Use the
 *  64-bit memory cost model from Section 1.4 of the textbook and use
 *  tilde notation to simplify your answer. Briefly justify your
 *  answers.
 *
 *  Include the memory for all referenced objects (deep memory).
 **********************************************************************/











/******************************************************************************
 *  After reading the course collaboration policy, answer the
 *  following short quiz. This counts for a portion of your grade.
 *  Write down the answers in the space below.
 *****************************************************************************/
1.
2.
3.

1. How much help can you give a fellow student taking COS 226?
(a) None. Only the preceptors and lab TAs can help.
(b) You can discuss ideas and concepts but students can get help
    debugging their code only from a preceptor, lab TA, or
    student who has already passed COS 226.
(c) You can help a student by discussing ideas, selecting data
    structures, and debugging their code.
(d) You can help a student by emailing him/her your code.

2. What are the rules when partnering?
 (a) You and your partner must both be present while writing code.
     But after that only one person needs to do the analysis.
 (b) You and your partner must both be present while writing code
     and during the analysis, but, after that, only one person
     needs to be present while submitting the code and the
     readme.
 (c) You and your partner must both be present while writing code,
     during the analysis, and while submitting the code and the
     readme. Failure to do so is a violation of the course
     collaboration policy.

3. For any programming assignment, I am permitted to use code that
   I found on a website other than the COS 226 or algs4 website
   (e.g., on GitHub or StackOverflow):
 (a) Only when the online code was written by a person who does not
     and did not go to Princeton.
 (b) Only when the online code implemented different assignment
     specifications than the ones I'm currently working on.
 (c) Always, because online code is available to everyone.
 (d) Never, because such websites are an impermissible "outside
     source".

/******************************************************************************
 *  Known bugs / limitations.
 *****************************************************************************/




/******************************************************************************
 *  Describe whatever help (if any) that you received.
 *  Don't include readings, lectures, and precepts, but do
 *  include any help from people (including course staff, lab TAs,
 *  classmates, and friends) and attribute them by name.
 *****************************************************************************/


/******************************************************************************
 *  Describe any serious problems you encountered.
 *****************************************************************************/




/******************************************************************************
 *  List any other comments here. Feel free to provide any feedback
 *  on how much you learned from doing the assignment, and whether
 *  you enjoyed doing it.
 *****************************************************************************/
