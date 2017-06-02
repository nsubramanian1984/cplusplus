#include <stdio.h>
#include <string.h>


#include "yajl/yajl_gen.h"
#include "yajl/yajl_parse.h"

#define UCL( string ) ( unsigned char* )( string ), strlen( string )

#define TRUE 1
#define FALSE 0

// CBelow function is taken from stack overflow.
void gen_random(char *s, const int len)
{
	int i;
	static const char alphanum[] =
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";

	srand(time(NULL));

	for (i = 0; i < len; ++i)
	{
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}

// Function to dump json to file.
static void file_cb( void* ctx, const char* str, size_t len )
{
	FILE* f = ctx;
	fwrite( str, 1, len, f );
}

int sample_json(yajl_gen gen)
{
	char buf[41] = {0};

	gen_random(buf, sizeof(buf));
	printf("random %s, size: %ld.\n", buf, strlen(buf));

	yajl_gen_map_open(gen);

	yajl_gen_string(gen, UCL("status"));
	if(strlen(buf) != 0)
		yajl_gen_string(gen, UCL("On"));
	else
		yajl_gen_string(gen, UCL("Off"));

	yajl_gen_string(gen, UCL("Token"));
	if(strlen(buf) != 0)
		yajl_gen_string(gen, UCL(buf));
	else
		yajl_gen_null(gen);

	yajl_gen_map_close(gen);

	// Always return true.
	return TRUE;
}

int main(void)
{
	FILE *file = NULL;
	file = fopen("./sample.json", "w+");

	if(file)
	{
		yajl_gen gen = NULL;

		int success = 0;

		gen = yajl_gen_alloc(NULL);
		yajl_gen_config(gen, yajl_gen_beautify, 1);
		yajl_gen_config(gen, yajl_gen_indent_string, "\t");

		//  PrintCallback function is used to save generated json in a file
		yajl_gen_config(gen, yajl_gen_print_callback, file_cb, file);

		if(sample_json(gen) && file)
		{
			fflush(file);

			// rewind(file);
			// char c;
			// while((c = fgetc(file)) != EOF)
			// 	printf("%c", c);

			// printf("\n");

			fclose(file);
		}
	}
	else
	{
		printf("Failed to create file.\n");
	}

	return 0;
}
