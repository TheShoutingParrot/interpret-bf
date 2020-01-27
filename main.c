#include "interpret-bf.h"

int main(int argv, char *argc[]) {
	cell_n = 0;
	pc = 0;

	if(argv < 2)
		die(USAGE_MSG, stderr);

	// TODO: add more arguments

	cell = (CELL_TYPE *)calloc(N_OF_CELLS, sizeof(CELL_TYPE));
	if(cell == (CELL_TYPE *)NULL)
		die("Memory allocation failed:");

	fname = (char *)malloc(1096);
	if(fname == (char *)NULL)
		die("Memory allocation failed:");

	strcpy(fname, argc[argv-1]);
	if(!realloc(fname, strlen(fname)))
		die("Reallocation failed:");

	FILE *fp;
	fp = fopen(fname, "r");

	if(fp == (FILE *)NULL)
		die("Failed to open file \"%s\":", fname);

	remove_extra_chars(fp);

	fclose(fp);

	while(*(program+pc) != NULL) {
		interpret_command();
		pc++;
	}

	return 0;
}

void remove_extra_chars(FILE *fp) { // TODO: rename this function
	char ch;
	uint32_t i;

	line_n = 1;
	i = 0;

	while((ch = fgetc(fp)) != EOF)
		switch(ch) {
			case '<':
			case '>':
			case '+':
			case '-':
			case '.':
			case ',':
			case '[':
			case ']':
			case '\n':
				i++;
			default:
				break;
		}
	
	program = (char *)malloc(i * sizeof(CELL_TYPE));
	if(program == NULL)
		die("Memory allocation failed:");
	i = 0;

	rewind(fp);

	while((ch = fgetc(fp)) != EOF)
		switch(ch) {
			case '<':
			case '>':
			case '+':
			case '-':
			case '.':
			case ',':
			case '[':
			case ']':
			case '\n':
				*(program+i++) = ch;
			default:
				break;
		}
}

void interpret_command(void) {
	uint32_t l, endl;

	switch(*(program+pc)) {
		case '>':
			if(cell_n >= N_OF_CELLS)
				die(DEFAULT_ERROR_MSG, line_n, CELL_NOT_ACCESSIBLE_MSG);
			++cell_n;
			break;
		case '<':
			if(cell_n <= 0)
				die(DEFAULT_ERROR_MSG, line_n, CELL_NOT_ACCESSIBLE_MSG);
			--cell_n;
			break;
		case '+':
			++*(cell+cell_n);
			break;
		case '-':
			--*(cell+cell_n);
			break;
		case '.':
			putchar(*(cell+cell_n));
			break;
		case ',':
			fscanf(stdin, "%c", (cell+cell_n));
			break;
		case '[':
			l = ++pc;

			endl = get_end_of_loop();

			while(true) {
				if(!(*(cell+cell_n)))
					break;
				for(pc = l; pc < endl; pc++) {
					interpret_command();
				}
			}
			break;

		case '\n':
			line_n++;
			break;
		default:
			break;
	}
}

uint32_t get_end_of_loop(void) {
	while(true) {
		if(*(program+pc) == NULL)
			die(DEFAULT_ERROR_MSG, line_n, MISMATCHED_BRACKETS_MSG);
		if(*(program+pc) == ']')
			break;
		else if(*(program+pc) == '[') {
			pc++;
			get_end_of_loop();
			pc++;
		}
		else
			pc++;
	}

	return pc;
}
