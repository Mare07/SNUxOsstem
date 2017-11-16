#include <unistd.h>

int main() {
	char *arg1 = "VolumeFromSlices";
	char *arg2 = "./results/ct.res.%d.jpg";
	char *arg3 = "87";
	char *arg4 = "185";
	char *arg5 = "please.mha";
	execl("VolumeFromSlices", arg1, arg2, arg3, arg4, arg5, NULL);
}
