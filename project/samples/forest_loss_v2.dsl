/* The forest-loss detection algorithm specified in the proposed
   domain specific language.

   Elements of this language design may change slightly.
 */

main() {

  // Read in satellite data - To Design
  matrix data = matrixRead ( "../samples/myData.dat" ) ;

  int rows;
  rows = numRows(data);
  int cols;
  cols = numCols(data);
  
  int season_length;
  season_length = 7;
  
  int years; 
  years = ceil(  cols * 1.0 / season_length ) ;

  // Begin real code
  
  matrix avgScore[rows: 1] row: irrelevant = 
    let
      matrix pt[years: season_length] i:j = 
        let
          int k;
          k = i*season_length + j;
        in
          if k >= cols 
          then 0.0-25 
          else data[row: k]
        end;
  
      matrix comparisonMatrix[years: years] i:j =
        if j <= i then 0.0
        else 
          let
          // diff these two years
            float diff;
            diff = 0;
            int k;
            repeat(k = 0  to  season_length-1) {
              diff = diff + pt[i:k] - pt[j:k];
            }
          in 
            diff / season_length
          end;

      matrix modelAvgScore[years: 1] yr: dontcare =
        let
          int x;
          int y;
         
          float score1;
          score1 = 0.0;
          repeat(x = 0  to  yr) {
            repeat(y = yr+1  to  years-1) {
              score1 = score1 + comparisonMatrix[x:y];
            }
          }
          score1 = score1 * 2 / (yr * (years - yr));
         
          float score2;
          score2 = 0.0;
          repeat(x = 0  to  yr) {
            repeat(y = 0  to  yr) {
              score2 = score2 + comparisonMatrix[x:y];
            }
          }
          score2 = score2 / ((yr-1) * yr / 2);
         
          float score3;
          score3 = 0.0;
          repeat(x = yr+1  to  years-1) {
            repeat(y = yr+1  to  years-1) {
              score3 = score3 + comparisonMatrix[x:y];
            }
          }
          score3 = score3 / ((years-yr)*(years-yr-1)/2);
        in
          score1 - score2 - score3
        end;

       
      float maximum;
      maximum = 0.0-25;
      int k;
      k = 0;
      repeat(k = 0  to  years-1) {
        if(modelAvgScore[k:0] > maximum) {
           maximum = modelAvgScore[k:0] ;
        }
      }

    in // back to defining avgScore
      maximum
    end;
    
  // Output results  
  int j;
  repeat(j = 0  to  rows-1) {
    print(avgScore[j:0]);
    print("\n");
  }
  
}
