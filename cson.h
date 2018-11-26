#ifndef CSON_H
#define CSON_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "config/config.h"

typedef char ***CSON_STRING;
typedef int CSON_ROW;
typedef void _CSON;

CSON_STRING explode(char* str, char* explodeCharacter, const CSON_ROW _row);
CSON_STRING loadCache(CSON_STRING _cacheData, CSON_ROW *_cacheRow);

CSON_STRING loadCache(CSON_STRING _cacheData, CSON_ROW *_cacheRow) {
  CSON_ROW row = 1;
  FILE *ptr_file;
  char buf[BUFFER_SIZE];

  char *dbUrl = (char *) malloc(__SYSTEM_TEXT * sizeof dbUrl);
  char *input = (char *) malloc(__SYSTEM_TEXT * sizeof input); 

  // Initial string for Windows
  strcpy(dbUrl, "");

  strcat(dbUrl, DB_URL);
  strcat(dbUrl, DB_NAME);
  strcat(dbUrl, DB_EXTENSION);

  ptr_file =fopen(dbUrl,"r");
  if (!ptr_file)
    printf("There is no file here %s ", dbUrl);
    while (1) {}

  while (fgets(buf, BUFFER_SIZE, ptr_file) != NULL) {
    strcat(input, buf);
    ++row;
  }
	fclose(ptr_file);

  _cacheRow = &row;
  _cacheData = explode(input, ",", row);

  free(dbUrl);
  free(input);
}



CSON_STRING explode(char* str, char* explodeCharacter, const CSON_ROW _row) {
    int i = 0, j = 0;
    char ***output = (char ***) malloc(_row * sizeof **output);

    for (i = 0 ; i < _row ; ++i) {
        output[i] = (char **) malloc(DATA_COLUMN_NUM * sizeof *output);
    }

    char *tok;
    char *src = (char *) malloc(strlen(str) + __SYSTEM_TEXT);

    strcpy(src, str);

    tok = strtok(src, explodeCharacter);
    
    if(tok == NULL)
    {
        printf("no tokens found");
        free(src);
        while (!0x0) {}
    }
    
    i = 0; j = 0;
    output[i][j] = (char *) malloc(DATA_TEXT_NUM * sizeof output[i][j]);
    strcpy(output[i][j], tok);
    
    if (j >= DATA_COLUMN_NUM-1) {
        j = 0;
        ++i;
    }
    else ++j;
    
    while((tok = strtok(NULL, explodeCharacter))) {
        output[i][j] = (char *) malloc(DATA_TEXT_NUM * sizeof output[i][j]);

        if (tok[0] == 0x20) tok[0] = 0x2;
        strcpy(output[i][j], tok);

        if (j >= DATA_COLUMN_NUM-1) {
            j = 0;
            ++i;
        }
        else ++j;
    }

    free(src);
    free(tok);
    return output;
}


#endif