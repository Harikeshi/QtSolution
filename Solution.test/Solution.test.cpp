#ifdef _WIN32
#  include <Windows.h>
#else
#  include <sys/stat.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rw_files.h"
#include "recurse.h"
#include "zipper.h"

static const char* excel = "D:/Projects/work/actual/excel.zip";

static const char* zipname = "test.zip";
static const char* f1_name = "Moneypenny.txt";
static const char* f2_name = "Bond.txt";
static const char* f3_name = "Up/M.txt";
static const char* f4_name = "Down/Q.tt";
static const char* f1_data = "secretary\n";
static const char* f2_data = "secret agent\n";
static const char* f3_data = "top guy\n";
static const char* f4_data = "bottom guy\n";
static const char* d1_name = "Up/";
static const char* d2_name = "Around/";
static const char* d3_name = "Bound/A/B";

static bool create_test_zip(void)
{
	zipFile zfile;

	zfile = zipOpen64(zipname, 0);
	if (zfile == NULL) {
		printf("Could not open %s for zipping\n", zipname);
		zipClose(zfile, NULL);
		return false;
	}

	printf("adding dir: %s\n", d2_name);
	if (!zipper_add_dir(zfile, d2_name)) {
		printf("failed to write dir %s\n", d2_name);
		zipClose(zfile, NULL);
		return false;
	}

	printf("adding dir: %s\n", d3_name);
	if (!zipper_add_dir(zfile, d3_name)) {
		printf("failed to write dir %s\n", d3_name);
		zipClose(zfile, NULL);
		return false;
	}

	printf("adding file: %s\n", f1_name);
	if (!zipper_add_buf(zfile, f1_name, (const unsigned char*)f1_data, strlen(f1_data))) {
		printf("failed to write %s\n", f1_name);
		zipClose(zfile, NULL);
		return false;
	}

	printf("adding file: %s\n", f2_name);
	if (!zipper_add_buf(zfile, f2_name, (const unsigned char*)f2_data, strlen(f2_data))) {
		printf("failed to write %s\n", f2_name);
		zipClose(zfile, NULL);
		return false;
	}

	printf("adding file: %s\n", f3_name);
	if (!zipper_add_buf(zfile, f3_name, (const unsigned char*)f3_data, strlen(f3_data))) {
		printf("failed to write %s\n", f3_name);
		zipClose(zfile, NULL);
		return false;
	}

	printf("adding dir: %s\n", d1_name);
	if (!zipper_add_dir(zfile, d1_name)) {
		printf("failed to write dir %s\n", d1_name);
		zipClose(zfile, NULL);
		return false;
	}

	printf("adding file: %s\n", f4_name);
	if (!zipper_add_buf(zfile, f4_name, (const unsigned char*)f4_data, strlen(f4_data))) {
		printf("failed to write %s\n", f4_name);
		zipClose(zfile, NULL);
		return false;
	}

	zipClose(zfile, NULL);
	return true;
}

static bool unzip_test_zip(void)
{
	unzFile          uzfile;
	char* zfilename;
	unsigned char* buf;
	size_t           buflen;
	zipper_result_t  zipper_ret;
	uint64_t         len;

	uzfile = unzOpen64(excel);
	//uzfile = unzOpen64(zipname);

	if (uzfile == NULL) {
		printf("Could not open %s for unzipping\n", zipname);
		return false;
	}

	do {
		zipper_ret = ZIPPER_RESULT_SUCCESS;
		zfilename = zipper_filename(uzfile, NULL);
		if (zfilename == NULL)
			return true;

		if (zipper_isdir(uzfile)) 
		{
			printf("reading dir: %s\n", zfilename);
			recurse_mkdir(zfilename);
			unzGoToNextFile(uzfile);
			free(zfilename);
			
			continue;
		}

		len = zipper_filesize(uzfile);
		printf("reading file (%llu bytes): %s\n", len, zfilename);
		zipper_ret = zipper_read_buf(uzfile, &buf, &buflen);
		if (zipper_ret == ZIPPER_RESULT_ERROR) {
			free(zfilename);
			break;
		}

		recurse_mkdir(zfilename);
		rw_write_file(zfilename, buf, buflen, false); //TODO: exchange write_file
		free(buf);
		free(zfilename);
	} while (zipper_ret == ZIPPER_RESULT_SUCCESS);

	if (zipper_ret == ZIPPER_RESULT_ERROR) {
		printf("failed to read file\n");
		return false;
	}

	unzClose(uzfile);
	return true;
}

int main(int argc, char* argv[])
{
	FILE* file_in, * file_out;
	const char* path_in = "D:\\Projects\\work\\actual\\excel.zip";
	const char* path_out = "D:\\Projects\\work\\actual\\test1.txt";
	if (!create_test_zip())
		return 1;
	unzip_test_zip();

	return 0;

	//system();
}