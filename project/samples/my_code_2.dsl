/* This program is just a copy of sample_1.dsl.
You should write your second interesting CDAL
program and save it in a file with this name. */

main() {
	int x;
	x = 5;
	int y;
	y = 10;
	
	int area;
	area = let int temp;
			temp = x * y;
			in temp end;
	print(area);
	print("\n");
	
	while (x > 1) {
    print(x);
    x = x - 1;
  }
  print("\n");
}



