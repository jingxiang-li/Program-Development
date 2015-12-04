/* Some matrix computations */

main ( ) {

matrix m [ 10: 10 ] i: j = i * j ;

int i ;
int j ;

repeat (i = 0 to 9 ) {
  repeat ( j = 0 to 9 ) {
    print ( m[i:j] ) ;
    print ("  ");
  }
  print ( "\n" ) ;
}

repeat (i = 0 to 9 ) {
  repeat ( j = 0 to 9 ) {
    m[i:j] = m[i:j] + 100 ;
  }
}

repeat (i = 0 to 9 ) {
  repeat ( j = 0 to 9 ) {
    print ( m[i:j] ) ;
    print ("  ");
  }
  print ( "\n" ) ;
}

}
