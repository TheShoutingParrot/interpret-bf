#include "interpret-bf.h"

int main(int argv, char *argc[]) {
	if(argv < 2)
		die(USAGE_MSG, stderr);

	// TODO: add more arguments

	pc = 0;

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
				i++;
			default:
				break;
		}

	if(i < 1)
		die("File \"%s\" contains no bf commands", fname);
	
	program = (char *)calloc(i, sizeof(CELL_TYPE));
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
				*(program+i++) = ch;
			default:
				break;
		}
}

void interpret_command(void) {
	uint32_t l, endl;

	switch(*(program+pc)) {
		case '>':
			++cell;
			break;
		case '<':
			--cell;
			break;
		case '+':
			++*cell;
			break;
		case '-':
			--*cell;
			break;
		case '.':
			putchar(*cell);
			break;
		case ',':
			fscanf(stdin, "%c", cell);
			break;
		case '[':
			l = ++pc;

			endl = get_end_of_loop();

			while(true) {
				if(!(*cell))
					break;
				for(pc = l; pc < endl; pc++) {
					interpret_command();
				}
			}
			break;
		default:
			break;
	}
}

uint32_t get_end_of_loop(void) {
	while(*(program+pc) != NULL) {
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
