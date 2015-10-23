int result = 1;
int num = 1;
boolean flag = true;

while (flag) {
	result = result * num;
	num = num + 1;
	if (num > 10) {
		flag = false;
	}
}
