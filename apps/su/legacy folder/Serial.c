#include "../inc/input.h"
#include "../inc/memory.h"
#include "../inc/Serial.h"


int main(int argc, char const *argv[]) {
  FILE *in, *out;
  char *endptr, *str, **tokens;
  int i, n_tok, tmp;
  uint8_t *bytes;
  int result = 0;

  in  = (argc > 1) ? fopen(argv[1], "r") : stdin;
  out = (argc > 2) ? fopen(argv[2], "w") : stdout;

  for (;;) {
    str = read_input(in);
    if (str == NULL) {
      break;
    }

    n_tok = 0;
    tokens = tokenize(str, " ", &n_tok);
    bytes = NULL; alloc_array(bytes, uint8_t, n_tok);

    for (i = 0; i < n_tok; i++) {
      endptr = NULL;
      tmp = strtoul(tokens[i], &endptr, 16);
      if (tokens[i] < endptr) {
        bytes[i] = (uint8_t)tmp;
      }
    }

    for (i = 0; i < n_tok; i++) {
      fprintf(out, "Sending %02x%c", bytes[i], i < n_tok - 1 ? ' ' : '\n');
    }

    char devicename[80] = "/dev/ttyS0";
    long Baud_Rate = B115200;
    int fd = 0;

    if((fd = SerialOpen (devicename, Baud_Rate)) == -1) // Open Serial Port
        return -1;

    result = write(fd, &(bytes), sizeof(bytes) - 1 );
     if(result < 0) {
        fprintf(stdout, "Failed to write to the serial port.\n");
    }
    else {
    fprintf(stdout, "The write to the serial port was successful.\n");
    }
    free(str);
    free(tokens);
    free(bytes);
  }

  free(str);
  fclose(in);
  fclose(out);

  return 0;
}
