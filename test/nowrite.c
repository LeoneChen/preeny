#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dlfcn.h>
#include <unistd.h>

int main()
{
	char buffer[1024];

	// readonly
	int fRO = open("nowrite.c", O_RDONLY);
	assert(read(fRO, buffer, 1024) > 0);
	close(fRO);

	// writeonly
	int fWO = open("nowrite.c", O_WRONLY);
	assert(write(fWO, buffer, 1024) == -1);
	close(fWO);

	// read/write
	int fRW = open("nowrite.c", O_RDWR);
	assert(read(fRW, buffer, 1024) > 0);
	assert(write(fRW, buffer, 1024) == -1);
	close(fRW);

	// read + create
	int fCR = open("nowrite.ccc", O_WRONLY|O_CREAT, 0644);
	assert(write(fCR, buffer, 1024) == -1);
	close(fCR);

	// tempfile
	int fTM = open("nowrite.c", O_WRONLY|O_TMPFILE, 0644);
	assert(write(fTM, buffer, 1024) == -1);
	close(fTM);
}
