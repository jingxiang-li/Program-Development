int result;
result = 1;
int num;
num = 1;
boolean flag;
flag = true;

while (flag) {
	result = result * num;
	num = num + 1;
	if (num > 10) {
		flag = false;
	}
}
