#include <cmath>
#include <iostream>
#include "Matrix.h"

int main () {
matrix data = matrixRead("../samples/myData.dat");
int rows;
rows = numRows(data);
int cols;
cols = numCols(data);
int season_length;
season_length = 7;
int years;
years = ceil(cols * 1.000000 / season_length);
matrix avgScore(rows, 1);
for (int row = 0; row != avgScore.numRows(); row++)
for (int irrelevant = 0; irrelevant != avgScore.numCols(); irrelevant++) {
avgScore[row][irrelevant] = ({
matrix pt(years, season_length);
for (int i = 0; i != pt.numRows(); i++)
for (int j = 0; j != pt.numCols(); j++) {
pt[i][j] = ({
int k;
k = i * season_length + j;
k >= cols ? 0.000000 - 25 : data[row][k];
});
}
matrix comparisonMatrix(years, years);
for (int i = 0; i != comparisonMatrix.numRows(); i++)
for (int j = 0; j != comparisonMatrix.numCols(); j++) {
comparisonMatrix[i][j] = j <= i ? 0.000000 : ({
float diff ;
diff = 0;
int k;
for (k = 0; k <= season_length - 1; k++) {
diff = diff + pt[i][k] - pt[j][k];
}
diff / season_length;
});
}
matrix modelAvgScore(years, 1);
for (int yr = 0; yr != modelAvgScore.numRows(); yr++)
for (int dontcare = 0; dontcare != modelAvgScore.numCols(); dontcare++) {
modelAvgScore[yr][dontcare] = ({
int x;
int y;
float score1 ;
score1 = 0.000000;
for (x = 0; x <= yr; x++) {
for (y = yr + 1; y <= years - 1; y++) {
score1 = score1 + comparisonMatrix[x][y];
}
}
score1 = score1 * 2 / (yr * (years - yr));
float score2 ;
score2 = 0.000000;
for (x = 0; x <= yr; x++) {
for (y = 0; y <= yr; y++) {
score2 = score2 + comparisonMatrix[x][y];
}
}
score2 = score2 / ((yr - 1) * yr / 2);
float score3 ;
score3 = 0.000000;
for (x = yr + 1; x <= years - 1; x++) {
for (y = yr + 1; y <= years - 1; y++) {
score3 = score3 + comparisonMatrix[x][y];
}
}
score3 = score3 / ((years - yr) * (years - yr - 1) / 2);
score1 - score2 - score3;
});
}
float maximum ;
maximum = 0.000000 - 25;
int k;
k = 0;
for (k = 0; k <= years - 1; k++) {
if ( modelAvgScore[k][0] > maximum ) {
maximum = modelAvgScore[k][0];
}
}
maximum;
});
}
int j;
for (j = 0; j <= rows - 1; j++) {
std::cout << avgScore[j][0];
std::cout << "\n";
}
}
