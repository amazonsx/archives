#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#define MAX 1000		/* no semicolon ending */
#define SMALL 50
#define TABSIZE 8
#define MAX_LINE 50
#define MEDIUM 200

int main(void) 
{
	/* 1-1 */
	char *str = "Hello, "\
		    "World!"\
		    "\n";
	printf(str);
	printf("\tEND\n");

	/* 1-2 */
	/*
	 * The standard says that 
	 * if the escape sequence char is not valid,
	 * the consequence is undefined.
	 * It seems that the gcc just give a warning and ignore it.
	 */
	//printf("invalid escape sequence \c\n");

	/* 1-3 */
	extern void temp_conv_f_to_c();
	temp_conv_f_to_c();

	/* 1-4 */
	extern void temp_conv_c_to_f();
	temp_conv_c_to_f();

	/* 1-5 */
	extern void temp_conv_f_to_c_in_reverse();
	temp_conv_f_to_c_in_reverse();

	/* 1-6 */
	/* verify the value of expr getchar() != EOF */
	/*
	printf("Input Ctrl+D, which is equal with EOF\n");
	printf("The value of getchar() = EOF is %d\n", (getchar() == EOF));
	printf("Input a, which is not equal with EOF\n");
	printf("The value of getchar() != EOF is %d\n", (getchar() == EOF));
	*/

	/* 1-7 */
	/* The value of EOF is -1 */
	printf("The value of EOF is %d\n", EOF);

	/* 1-8 */
	/* programs to count blanks, tabs, newlines from stdin */
	extern int count_white_space();
	//printf("The count of white space is %d\n", count_white_space());
	
	/* 1-9 */
	/* copy stdin to stdout by replacing multiple space char to single one*/
	extern void cp_input_output(FILE *, FILE *);
	//cp_input_output(stdin, stdout);

	/* 1-10 */
	/* copy stdin to stdout without escape sequences mappint \t \b \\ */
	extern void cp_input_output_no_mapping(FILE *, FILE *);
	//cp_input_output_no_mapping(stdin, stdout);

	/* 1-11 */
	/* 
	 * test word_count/wc 
	 * regular string
	 * only contains white space chars
	 * 0 lines
	 * serverl empty lines
	 */
	extern void word_count(FILE *);
	//word_count(stdin);

	/* 1-12 */
	/* print word per line from input */
	extern void print_word_per_line(FILE *);
	//print_word_per_line(stdin);


	/* 1-13 */
	/* print word length from input in vertical histogram */
	extern void print_word_len(FILE *);
	//print_word_len(stdin);

	/* 1-14 */
	/* print alphanum frequency */
	extern void print_char_fre(FILE *);
	//print_char_fre(stdin);
	
	/* 1-15 */
	/* same with 1-5 */

	/* 1-16 */
	/* get the true len of a line and its contents as many as possible */
	extern void max_line(FILE *);
	//max_line(stdin);

	/* 1-17 */
	/* print all lines longer than 80 */
	extern void print_longer_lines(int, FILE *);
	//print_longer_lines(80, stdin);

	/* 1-18 */
	/* remove trailing blanks and tabs and blank lines*/
	extern void print_modified_lines(FILE *);
	//print_modified_lines(stdin);

	/* 1-19 */
	/* reverse string by line */
	extern void reverse(FILE *);
	//reverse(stdin);

	/* 1-20 */
	extern void detab(FILE *in, FILE *out, int ts_interval);
	//detab(stdin, stdout, 12);

	/* 1-21 */
	/* see the commentary of the function */
	extern void entab(FILE *in, FILE *out);
	//entab(stdin, stdout);

	/* 1-22 */
	extern void fold_lines(FILE *in, FILE *out);
	//fold_lines(stdin, stdout);

	/* 1-23 */
	extern void rm_comments(FILE *in, FILE *out);
	/*
	char rmode = 'r';
	char wmode = 'w';
	FILE *in = fopen("c1.c", &rmode); //comments_sample
	FILE *out = fopen("comments_output", &wmode);
	rm_comments(in, out);
	*/

	/* 1-24 */
	extern int chk_syntax(FILE *in);
	//escape sequence test
	//printf("this is a sequence\ ttest\n\ n"); //invalid
	char rmode = 'r';
	FILE *in = fopen("syntax_sample", &rmode); //comments_sample
	printf("Syntax of the source file is %s\n", chk_syntax(in) ? "valid" : "invalid");

	exit(0);
}

/* 
 * temperature conversion:
 * from fahrenheit to celsius
 */
void temp_conv_f_to_c() 
{
	float min_f = 0, max_f = 300;
	printf("%13s   %13s\n", "Fahrenheit", "Celsius");
	for (float i = min_f; i <= max_f; i += 20) {
		float tmp = (i - 32) * 5 / 9;
		printf ("%13.2f   %13.2f\n", i, tmp);
	}
}

/* 
 * temperature conversion:
 * from fahrenheit to celsius
 */
void temp_conv_f_to_c_in_reverse() 
{
	float min_f = 0, max_f = 300;
	printf("%13s   %13s\n", "Fahrenheit", "Celsius");
	for (float i = max_f; i >= min_f; i -= 20) {
		float tmp = (i - 32) * 5 / 9;
		printf ("%13.2f   %13.2f\n", i, tmp);
	}
}

/* 
 * temperature conversion:
 * from celsius to fahrenheit
 */
void temp_conv_c_to_f() 
{
	float min_f = 0, max_f = 300;
	printf("%13s   %13s\n", "Celsius", "Fahrenheit");
	for (float i = min_f; i <= max_f; i += 20) {
		float tmp = i * 9 / 5 + 32;
		printf ("%13.2f   %13.2f\n", i, tmp);
	}
}


/* 1-7 */
/* programs to count blanks, tabs, newlines from stdin */
int count_white_space() 
{
	int c = 0;
	int count = 0;
	while ((c=getchar()) != EOF) {
		if (c == '\n' || c == ' ' || c == '\t')
			count ++;
	}
	return count;
}

/* 
 * cp input stream to output stream with a buffer 
 * request that in and out has been opened.
 */
void cp_input_output(FILE *in, FILE *out) 
{
	int i = 0; 
	int c = 0;
	int space_flag = 0;
	char buf[MAX]; 
	while ((c=getc(in)) != EOF && i < MAX) {
		if (c != ' ') {
			space_flag = 0;
		} else {
			if (space_flag == 1)
				continue;
			space_flag = 1;
		}
		buf[i++] = c;
	}
	buf[i] = '\000';
	fputs(buf, out);
}
/*
 * cp with escape sequence recovering
 */
void cp_input_output_no_mapping(FILE *in, FILE *out) 
{
	int i = 0; 
	int c = 0;
	char buf[MAX]; 
	while ((c=getc(in)) != EOF && i < MAX) {
		switch (c) {
		case '\t':
			buf[i++] = '\\';
			buf[i++] = 't';
			break;
		case '\b':
			buf[i++] = '\\';
			buf[i++] = 'b';
			break;
		case '\\':
			buf[i++] = '\\';
			buf[i++] = '\\';
			break;
		default:
			buf[i++] = c;
			break;

		}
	}
	buf[i] = '\000';
	fputs(buf, out);
}

/* count lines, words, and charaters in input */
void word_count(FILE *in)
{
	int wc = 0, cc = 0, lc = 0;
	int inword = 0;
	int c = 0;
	while ((c=getc(in)) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t') {
			cc ++;
			if (inword == 0)
				wc ++;
			inword = 1;
		} else {
			if (c == '\n')
				lc ++;
			inword = 0;
		}
	}
	printf("The input contains %d words,"\
		" %d chars and %d lines\n", wc, cc, lc);
}

void print_word_per_line(FILE *in)
{
	char word[SMALL] = {0};
	int c = 0;
	int i = 0;
	while ((c=getc(in)) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t') {
			word[i++] = c;
		} else if (i > 0) {
			word[i] = 0;
			printf("%s\n", word);
			i = 0;
		}
	}
}

void print_word_len(FILE *in)
{
	int counts[MAX] = {0};	
	int c = 0;
	int word_len = 0;
	int word_count = 0;
	int max = 0;
	while ((c=getc(in)) != EOF) {
		if (c != '\t' && c != ' ' && c != '\n') {
			word_len ++;
		} else if (word_len) {
			counts[word_count++] = word_len;
			if (word_len > max)
				max = word_len;
			word_len = 0;
		}
	}
	if (word_len)
		counts[word_count++] = word_len;
	while (max > 0) {
		for (int i = 0; i < word_count; i++) {
			if (counts[i] == max) {
				printf("x");
				counts[i]--;
			} else {
				printf(" ");
			}
		}
		printf("\n");
		max--;
	}
}

void print_char_fre(FILE *in)
{		
	int alnum[37] = {0};
	int c = 0;
	int indice = 0;
	int max = 0;
	while ((c=getc(in)) != EOF) {
		if (isalpha(c))
			indice = c - 'a';
		else if (isdigit(c))
			indice = 26 + c - '0';
		if (++alnum[indice] > max)
			max = alnum[indice];
	}
	while (max > 0) {
		for ( int i = 0; i < (int)(sizeof(alnum)/sizeof(int)); i++) {
			if (alnum[i] == max) {
				--alnum[i];
				printf("xx");
			} else {
				printf("  ");
			}
		}
		printf("\n");
		--max;
	}
}

static int getline(char *buf, FILE *in)
{
	int c = 0;
	int count = 0;
	while ((c = getc(in)) != EOF) {
		if (c == '\n') 
			break;
		buf[count++] = c;
	}
	if (c == EOF)
		return EOF;
	buf[count] = 0;
	return count;
}

void max_line(FILE *in) 
{
	char buf[MAX] = {0};
	char tmp[MAX] = {0};
	int max_len = 0;
	int len = 0;
	while((len = getline(tmp, in)) != EOF) { 
		if (len <= max_len) 
			continue;
		memcpy(buf, tmp, len);
		max_len = len;
	}
	printf("The longest line length is %d\n", max_len);
	printf("The line is %s\n", buf);
}

void print_longer_lines(int min_len, FILE *in)
{
	char buf[MAX] = {0};
	int len = 0;
	while ((len=getline(buf, in)) != EOF) {
		if (len >= min_len) {
			printf("The line len is %d\n", len);
			printf("The line is :%s\n", buf);
		}
	}
}

void print_modified_lines(FILE *in)
{
	char buf[MAX] = {0};
	int c = 0;
	int i = 0;
	int last_tail = -1;
	while ((c=getc(in)) != EOF) {
		buf[i] = c;
		if (c != '\n' && c != '\t' && c != ' ') {
			last_tail = ++i;
		} else if (c == '\n') {
			// no blank line
			if (last_tail != -1 && buf[last_tail] != '\n') {
				buf[++last_tail] = '\n';
			}
			i = last_tail + 1;
		}
	}
	if (last_tail != -1 && buf[last_tail] != '\n')
		buf[++last_tail] = '\n';
	buf[++last_tail] = 0;
	printf("The input is \n%s", buf);
}

void reverse(FILE *in)
{
	int len = 0;
	char buf[MAX] = {0};
	while ((len=getline(buf, in)) != EOF) {
		for (int i = len - 1; i >= 0; i--) {
			putchar(buf[i]);
		}
		printf("\n");
	}
}

void detab(FILE *in, FILE *out, int ts_interval)
{
	int index = 0;
	char buf[MAX] = {0};
	int c = 0;
	int i = 0;
	while ((c=getc(in)) != EOF) {
		if (c != '\t') {
			buf[i++] = c;
			index++;
			if (c == '\n')
				index = 0;
		} else {
			int space_count = ts_interval - index % ts_interval;
			while (space_count-- > 0) {
				buf[i++] = ' ';
				index++;
			}
		}
	}
	printf("The input string is :\n");
	fputs(buf, out);
}

/* not connect with detab? */
/* how to simulate the tab stop in word processor 
 * It seems that the exercise wants 
 * to let you print to the next tab stop 
 * when contiguous spaces across through a tab stop
 */
void entab(FILE *in, FILE *out)
{
	char buf[MAX] = {0};
	int c = 0;
	int space_count = 0;
	int i = 0;
	while ((c=getc(in)) != EOF) {
		if (c != ' ') {
			for (; space_count/TABSIZE > 0; space_count-=TABSIZE)
				buf[i++] =  '\t';
			for (; space_count > 0; space_count--)
				buf[i++] = ' ';
			buf[i++] = c;
		} else {
			space_count++;
		}
	}
	for (;space_count/TABSIZE > 0; space_count--)
		buf[i++] =  '\t';
	for (; space_count > 0; space_count--)
		buf[i++] = ' ';
	fputs("The Output String is:\n", out);
	fputs(buf, out);
}

/* if a line is too long, say longger than MAX_LINE,
 * it's necessary to fold lines to more shorter lines.
 * fold these lines by the last non-char appears before MAX_LINE column
 *
 * I think its better to keep word-intergrity that may be spilitted
 * So I'd like to print these words on the next line
 */
void fold_lines(FILE *in, FILE *out)
{
	char line_buf[MEDIUM] = {0};
	char buf[MAX] = {0};
	int i = 0;
	int j = 0;
	int len = 0;
	while((len = getline(line_buf, in)) != EOF) {
		if (len > MAX_LINE) {
			j = -1;
			/* discards the last \n */
			while (j < len) { 
				int k = j + 1;
				j += MAX_LINE - 1;
				while (j < len && line_buf[j] != '\t' && line_buf[j] != ' ')
					j--;
				memcpy(buf + i, line_buf + k, (j >= len) ? len - k : j - k + 1);
				i += (j >= len) ? len - k : j - k + 1;
				buf[i++] = '\n';
			}
		} else {
			memcpy(buf + i, line_buf, len);
			i += len;
			buf[i++] = '\n';
		}
	}
	fputs("The Output String is \n", out);
	fputs(buf, out);
}

/* no nested comments in c 
 * check comments_sample
 */
void rm_comments(FILE *in, FILE *out)
{
	int is_ml_comments = 0;
	int is_sl_comments = 0;
	int is_string = 0;
	int is_char = 0;
	int c = 0;
	while ((c = getc(in)) != EOF) {
		if (is_ml_comments) {
			if (c == '*' && (c=getc(in)) == '/')
				is_ml_comments = 0;
			continue;
		}
		if (is_sl_comments) {
			while ((c=getc(in)) != '\n');
			is_sl_comments = 0;
			putc('\n', out);
			continue;
		}
		// escape sequences
		if (c == '\\') {
			putc(c, out);
			c = getc(in);
			putc(c, out);
		} else if (c == '\"') {
			putc(c, out);
			is_string = 1 - is_string;
		} else if (c == '\'') {
			putc(c, out);
			is_char = 1 - is_char;
		//} else if (!is_string && !is_char && c == '/' && (c = getc(in)) == '/') { //error like this!!!
		} else if (!is_string && !is_char && c == '/') {
			if ((c=getc(in)) == '/') {
				is_sl_comments = 1;
			} else if (c == '*') {
				is_ml_comments = 1;
			} else {
				putc('/', out); 
				putc(c, out);
			}
		//} else if (!is_string && !is_char && c == '/' && (c = getc(in)) == '*') {
		} else {
			putc(c, out);
		}
	}
	assert(!is_string);
	assert(!is_char);
	assert(!is_ml_comments);
	assert(!is_sl_comments);
}

/* check braces, brackets, parentheses, single and double quotes */
int chk_syntax(FILE *in)
{
	char incld_stack[SMALL] = {0};
	int sp = 0;
	int in_string = 0;
	
	int c = 0;
	while ((c=getc(in)) != EOF) {
		if (c == '\\') {
			c = getc(in);
			continue;
		}
		if (c == '\"') {
			if (incld_stack[sp-1] == c)
				--sp;
			else 
				incld_stack[sp++] = c;
			in_string = 1 - in_string;
		}
		if (!in_string)
			continue;
		switch (c) {
		case '(': 
		case '[':
		case '{':
			incld_stack[sp++] = c;
			break;
		case ')':
			if (incld_stack[--sp] != '(')
				return 0;
			break;
		case ']':
			if (incld_stack[--sp] != '[')
				return 0;
			break;
		case '}':
			if (incld_stack[--sp] != '{')
				return 0;
			break;
		case '\'':
			if (incld_stack[sp-1] == c) 
				--sp;
			else
				incld_stack[sp++] = c;
			break;
		default:
			break;
		}
	}
	if (sp) 
		return 0;
	return 1;
}


