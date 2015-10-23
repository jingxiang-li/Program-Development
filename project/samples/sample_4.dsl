
main () {

matrix a [10:10] ia: ja = ia + ja ;

matrix m [10:10] mi: mj =
  let x = 7 ;
      matrix n [10:10] ni: ni = mi + mj ;
  in  n [mi: mj] * 2 end ;

}
