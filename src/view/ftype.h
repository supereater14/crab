#ifndef FTYPE_H
#define FTYPE_H

typedef enum {
	UNKNOWN,
	AUDIO,
	VIDEO,
	MEDIA,
	IMAGE,
	TEXT,
	DOCUMENT,
	PRESENTATION,
	SPREADSHEET,
	SOURCE,
	BINARY
} filetype_t;

/* Retrieves the filetype tied to a given extension
 *
 * ext - File extension
 * returns - filetype_t containing detected filetype
 */
filetype_t get_type_ext(char *ext);

/* Retrieves the filetype of a given filename
 *
 * fname - Filename
 * returns - filetype_t containing detected filetype
 */
filetype_t get_type_fname(char *fname);

#endif
