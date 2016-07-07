/* input.c
 *
 * Reads input from the given stream, source or
 * standard input. Parses the given input into
 * a useful format to populate the data structures
 * and executes Executor functions in Read–eval–print
 * loop (REPL).
 */

#include <stdio.h>
#include <string.h>
#include "../../inc/memory.h"
#include "../../inc/input.h"
#include <stdint.h>

/**** Input and String Manipulation ****/

  /*
   * Reads in each line one at a time from the input file
   * Reads until first newline character or end of file,
   * excluded in returned char array. Automatically adds
   * null character at end of string. Returns NULL
   * if no more lines to read or error encountered.
   */
  char *read_input(FILE *stream) {
    int i = 0;
    int n = 64;
    uint8_t *ss, *s = NULL;
    for (;;) {
      alloc_array(s, uint8_t, n + i);
      ss = fgets(&s[i], sizeof(uint8_t)*n, stream);
      if (s == NULL || ss == NULL || (i = strlen(s)) == 0) {
        if (i == 0) {
          delete(s);
        }
        break;
      }
      if (strchr(s, '\n') != NULL) {
        s[i - 1] = '\0';
        break;
      }
      n *= 2;
    }
    return s;
  }

  /*
   * Given a string, returns an array of strings of tokens split by the
   * given delims string of delimiter characters. The original string is
   * modified in the process. If the given nunber of tokens is greater than
   * zero, limits the number tokens to that specified, otherwises tokenizes
   * until the end of string. Updates the value of the number of tokens to
   * number of tokens returned.
   */
  char **tokenize(char *str, char *delims, int *n_tok) {
    int i = 0, max_tok = *n_tok;
    char *saveptr = NULL;
    char **tokens = NULL;
    *n_tok = 0;
    for (;;) {
      alloc_array(tokens, char*, (i + 1));
      if (max_tok > 0 && max_tok == *n_tok) {
        break;
      }
      if ((tokens[i++] = strtok_r(str, delims, &saveptr)) == NULL) {
        break;
      }
      str = NULL;
      *n_tok += 1;
    }
    return tokens;
  }

