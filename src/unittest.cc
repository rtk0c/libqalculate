#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

void print_usage() {
	puts("Usage: ./unittest [filename]");
	puts("       ./unittest [qalc executable] [.batch files folder]");
	puts("If the first variant is used, qalc is assumed to be at ./unittest");
}

void run_unit_test(const char *qalcExe, const char *filename) {
	char buffer[1000];
	snprintf(buffer, 1000, "%s --test-file=\"%s\"", qalcExe, filename);
	int ret = system(buffer);
	if(ret == EXIT_SUCCESS) return;
	if(ret == -1 && ret != EXIT_FAILURE) puts(RED "Cannot start qalc!" RESET);
	exit(EXIT_FAILURE);
}

int ends_with(const char *str, const char *suffix) {
	if(!str || !suffix) return 0;
	size_t lenstr = strlen(str);
	size_t lensuffix = strlen(suffix);
	if(lensuffix >  lenstr) return 0;
	return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main(int argc, char *argv[]) {

	if (argc == 3) {
		puts("Running all unit tests\n");
		const char *qalcExe = argv[1];
		const char *path = argv[2];
		DIR *d;
		struct dirent *dir;
		d = opendir(path);
		if(d) {
			while((dir = readdir(d)) != NULL) {
#ifdef _DIRENT_HAVE_D_TYPE
				if(dir->d_type != DT_REG) continue;
#endif
				char *filename = dir->d_name;
				if(!ends_with(filename, ".batch")) continue;
				printf("Running unit tests from '%s'\n", filename);
				char fullPath[4096] = "";
				strcat(fullPath, path);
#ifdef _WIN32
				fflush(stdout);
				strcat(fullPath, "\\");
#else
				strcat(fullPath, "/");
#endif
				strcat(fullPath, filename);
				run_unit_test(qalcExe, fullPath);
			}
			closedir(d);
		}
	} else if(argc == 2) {
		char *filename = argv[1];
#ifdef _WIN32
		run_unit_test(".\\qalc.exe", filename);
#else
		run_unit_test("./qalc", filename);
#endif
	} else {
		print_usage();
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
