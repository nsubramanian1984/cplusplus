
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "yajl_gen.h"
#include "yajl_parse.h"

#define TRUE 1
#define FALSE 0

typedef int (* FP )( char*, char* );

typedef struct
{
	FP func_parse_cb;
	char key[100];
	char value[1024];
} Arguments;

static int json_has_errors = FALSE;

static int parse_null( void* ctx )
{
	Arguments* args = ( Arguments* )ctx;

	return ( TRUE );
}

static int parse_boolean( void* ctx, int boolean )
{
	Arguments* args = ( Arguments* )ctx;

	return ( TRUE );
}

static int parse_number( void* ctx, const char* number, size_t len )
{
	Arguments* args    = ( Arguments* )ctx;

	snprintf(args->value, (len + 1), "%s", number);
	printf("%s -> %s\n", __func__, args->value);	


	return ( TRUE );
}

static int parse_string( void* ctx, const unsigned char* string, size_t len )
{
	Arguments* args    = ( Arguments* )ctx;
	printf("%s -> %ld\n", __func__, len);

	snprintf(args->value, (len + 1), "%s", string);
	printf("%s -> %s\n", __func__, args->value);	

	return ( TRUE );
}

static int parse_map_key( void* ctx, const unsigned char* string, size_t len )
{
	Arguments* args    = ( Arguments* )ctx;

	printf("%s -> %ld\n", __func__, len);

	snprintf(args->key, (len + 1), "%s", string);
	printf("%s -> %s\n", __func__, args->key);

	return ( TRUE );
}

static int parse_start_map( void* ctx )
{
	Arguments* args    = ( Arguments* )ctx;

	printf("%s -> %s %s\n", __func__, args->key, args->value);

	return ( TRUE );
}


static int parse_end_map( void* ctx )
{
	Arguments* args    = ( Arguments* )ctx;

	printf("%s -> %s %s\n", __func__, args->key, args->value);

	return ( TRUE );
}

static int parse_start_array( void* ctx )
{
	Arguments* args    = ( Arguments* )ctx;

	printf("%s -> %s\n", __func__, args->key);

	return ( TRUE );
}

static int parse_end_array( void* ctx )
{
	Arguments* args    = ( Arguments* )ctx;

	printf("%s -> %s\n", __func__, args->key);

	return ( TRUE );
}

static int parse_json( FILE* f, FP func_parse_cb )
{
	static yajl_callbacks callbacks = {
		parse_null,
		parse_boolean,
	    NULL, /* integer */
	    NULL, /* double */
	    parse_number, /* since double & integer callback is not, this function will be used instead */
		parse_string,
		parse_start_map,
		parse_map_key,
		parse_end_map,
		parse_start_array,
		parse_end_array
	};
	Arguments*    args;
	yajl_handle           parse;

  // Allocate some storage for stor
	static unsigned char  filedata[1024];
	yajl_status stat;
	size_t rd;
	int success = 0;

	args = (Arguments *) malloc( sizeof( Arguments ) );
	args->func_parse_cb = func_parse_cb;

	parse = yajl_alloc( &callbacks, NULL, args );
	yajl_config( parse, yajl_allow_comments, 1 );

	fseek( f, 0, SEEK_SET );

	while( TRUE )
	{
		rd = fread( ( void* )filedata, 1, sizeof( filedata ) - 1, f );

		if( rd == 0 )
		{
			if( !feof( f ) )
			{
				printf( "Failed to read data from file.\n" );
			}
			break;
		}

		filedata[ rd ] = 0;

		stat = yajl_parse( parse, filedata, rd );

		if( stat != yajl_status_ok )
		{
			break;
		}
	}

	stat = yajl_complete_parse( parse );

	if( stat != yajl_status_ok )
	{
		unsigned char* str = yajl_get_error( parse, 1, filedata, rd );

		printf( "** Error ***\n%s", ( const char* ) str );
		yajl_free_error( parse, str );

		success = 0;
	}
	else
	{
		success = 1;
	}

	yajl_free( parse );

	free( args );

	return ( success );
}


int parse_key_value( char* key, char* value )
{

	printf("\nkey: %s, value: %s.\n", key, value);
	if( !strcmp( key, "status" ) )
	{

	}
	else if( !strcmp( key, "token" ) )
	{

	}
	else
	{
    // If json has other keys, we declare json has errors.
		json_has_errors = TRUE;
	}

	return !json_has_errors;
}

int main(int argc, char **argv)
{
	char fileName[32] = {0};

	if(argc < 2)
	{
		strcpy(fileName, "./sample.json");
	}
	else
	{
		strcpy(fileName, argv[1]);
	}

	printf("filename: %s.\n", fileName);

	FILE *file = fopen(fileName, "r+");
	int success = 0;

	if(file)
	{
		success = parse_json( file, &parse_key_value );
	}

	return 0;
}