/* This program is just a copy of sample_1.dsl. You should write your CDAL program to multiply two
2-dimensional matrices and save it
in a file with this name. */

main () {
  matrix m1 [2 : 2] i : j = 0;
  m1[0 : 0] = 1;
  m1[0 : 1] = 2;
  m1[1 : 0] = 3;
  m1[1 : 1] = 4;
  matrix m2 [2 : 2] i : j = 0;
  m2[0 : 0] = 4;
  m2[0 : 1] = 3;
  m2[1 : 0] = 2;
  m2[1 : 1] = 1;
  matrix m = m1 * m2;
  print(m);
}



