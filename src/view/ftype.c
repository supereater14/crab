#include "ftype.h"
#include <unistd.h>

char *get_ext(char *fname){
	char *curr;

	/* Fast-forward to the end of the string */
	curr = fname;
	while(curr != '\0'){
		curr++;
	}

	/* Rewind until we hit a . or the start of the string */
	while(*curr != '.' && curr != fname){
		curr--;
	}

	/* If we rewound to a ., advance one and return. */
	if(*curr == '.'){
		curr++;
		return curr;
	}

	/* If we failed to find an extension, return NULL */
	return NULL;
}

filetype_t check_ascii(char *fname){
	const int block_size = 2048;
	int file_handle;
	int data_read;
	int i;
	unsigned char data[block_size];

	/* Open the file for reading */
	file_handle = open(fname, O_RDONLY);
	if(file_handle < 0){
		return UNKNOWN;
	}

	/* Sweep through the file, looking for non-printable characters */
	while((data_read = read(file_handle, data, block_size)) > 0){
		for(i = 0; i < data_read; i++){
			if(data[i] < 0x20 || data[i] > 0x7f){
				close(file_handle);
				return BINARY;
			}
		}
	}

	/* Close the file and return */
	close(file_handle);
	return TEXT;
}

filetype_t get_type_ext(char *ext){
	/* TODO */
}

filetype_t get_type_fname(char *fname){
	char *ext;
	filetype_t type;

	/* Get the extension. If none found, mark as ascii text or binary. */
	ext = get_ext(fname);
	if(ext == NULL){
		return check_ascii(fname);
	}

	/* Get the type based on the extension. */
	type = get_type_ext(ext);
	if(type == UNKNOWN){
		return check_ascii(fname);
	}

	/* Return the found type */
	return type;
}
