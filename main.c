#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PROMPT "db > "

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();
void print_prompt();
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);

int main(int argc, char* arcv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  if (input_buffer == NULL) {
    fprintf(stderr, "Unable to allocate memory for input buffer\n");
  }

  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer -> buffer, "exit") == 0) { 
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }

  return EXIT_SUCCESS;
}

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  if (input_buffer == NULL) {
    return NULL;
  }

  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt() {
  printf(PROMPT);
}

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  if (input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
  }
}

