/*
	main.c
	Algorithms and Analysis: Assignment 1
	Set ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#include "set.h"

/* declarations */

#define GETOPT_FINISHED			-1

/* command line options, you may add more to this if you wish */
struct cmdline_opt {
	int verbose;	/* if true, print out results */
	int profile;	/* optional flag, do what you want with this */
};

void print_usage(const char *name);
int parse_args(int argc, char **argv, struct cmdline_opt *optvals);
void process_datafile(const char *fname, set_t *set,
	struct cmdline_opt *optvals);

/* functions */

int main(int argc, char **argv)
{
	int i = 0;
	int arg_data_index = 0;
	struct cmdline_opt options;
	set_t *set;

	arg_data_index = parse_args(argc, argv, &options);
    if(options.profile)
      printf("%s( %s ): ", argv[0], argv[arg_data_index]);
	set = set_create();

	for (i = arg_data_index; i < argc; i++) {
		process_datafile(argv[i], set, &options);
	}

	set_destroy(set);

	return EXIT_SUCCESS;
}

void process_datafile(const char *fname, set_t *set,
	struct cmdline_opt *optvals)
{
	FILE *file;
	char cmd;
	int ret, val;
	int output_flag;
    int profile_flag;
    float start_time;
    float end_time;
    float elapsed_time;

	/* sanity check for pointers */
	assert(set);
	assert(optvals);

	output_flag = optvals->verbose;
    profile_flag = optvals->profile;


	if ((file = fopen(fname, "r")) == NULL) {
		fprintf(stderr,"Error: cannot open file %s.\n",	fname);
		return;
	}

    if (profile_flag) {
      start_time = (float)clock()/CLOCKS_PER_SEC;
    }

	/* we are assuming a well-formed datafile for this project */
	while (fscanf(file, "%c %d\n", &cmd, &val) > 0) {
		switch (cmd) {
		case 'I':
  
			/* insert */
          ret = set_insert(set, val);
			if (output_flag) {
				printf("insert:\t%d\t%s\n", val,
                       (ret ? "new" : "repeat"));
			}
			break;
		case 'D':
			/* delete */
			ret = set_delete(set, val);
			if (output_flag) {
				printf("delete:\t%d\t%s\n", val,
					(ret ? "removed" : "missing"));
			}
			break;
		case 'S':
			/* search */
			ret = set_search(set, val);
			if (output_flag) {
				printf("search:\t%d\t%s\n", val,
					(ret ? "present" : "absent"));
			}
			break;
		/* define your own commands if it helps with testing */
		case 'P':
			/* print, useful for debugging */
			if (output_flag) {
				set_print(set);
			}
			break;
		default:
			/* ignore any unrecognised commands */
			break;
		}
	}

	fclose(file);
    if (profile_flag) {
      end_time = (float)clock()/CLOCKS_PER_SEC;
      elapsed_time = end_time - start_time;
      printf("%.2fs\n", elapsed_time);
    }


}

int parse_args(int argc, char **argv, struct cmdline_opt *optvals)
{
	extern int optind;

	int opt = GETOPT_FINISHED;

	if (argc <= 1) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* set options to default */
	assert(optvals);
	optvals->verbose = 1;
	optvals->profile = 0;

	/*
		This uses getopt to read command line options.
		See the man page to learn more about getopt.
	*/
	while ((opt = getopt(argc, argv, "qvp")) != GETOPT_FINISHED) {
		switch (opt) {
		case 'q':
			/* quiet mode */
			optvals->verbose = 0;
			break;
		case 'v':
			/* verbose mode (default) */
			optvals->verbose = 1;
			break;
		case 'p':
			/* profiling mode (can do what you like) */
			optvals->profile = 1;
			break;
		default:
			print_usage(argv[0]);
			exit(EXIT_FAILURE);			
		}
	}

	return optind;
}

void print_usage(const char *name)
{
	fprintf(stderr, "Usage: %s [OPTIONS]... [FILES]...\n", name);
	fprintf(stderr, "Implements a basic set ADT for integers, "
		"performing the\noperations defined in FILES.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "  -q\t\tquiet mode "
		"(no output from operations)\n");
	fprintf(stderr, "  -v\t\tvetbose mode "
		"(default, output from operations)\n");
	fprintf(stderr, "  -p\t\tprofile mode "
		"(unimplemented, can do what you want)\n");
	fprintf(stderr, "\n");	
	fprintf(stderr, "File Format:\n");
	fprintf(stderr, "Data files consist of command lines: "
		"a character and a number.\n");
	fprintf(stderr, "I <number>\t\t"
		"insert <number> in the set\n");
	fprintf(stderr, "D <number>\t\t"
		"delete <number> from the set\n");
	fprintf(stderr, "S <number>\t\t"
		"search for <number> in the set\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Multiple files can be specified "
		"and they will run sequentially.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Example:\n  "
		"%s insert_list.txt search_list.txt\n", name);

	return;
}
