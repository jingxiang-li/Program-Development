/* This program is just a copy of sample_1.dsl. You should write your CDAL program to multiply two
2-dimensional matrices and save it
in a file with this name. */

main () {
  matrix m1 = matrixRead("../samples/my_code_1_0.data") ;
  matrix m2 = matrixRead("../samples/my_code_1_1.data") ;
  matrix m = m1 * m2;
  print(m);
}



