namespace MyCustomCxxLib {

int process_data(const char *in, char *out) {
  // Pretend like this is interesing and meaningful processing.
  // Let's say we're gathering sensor readings from 'in', and normalizaing
  // them or whatever into 'out'.

  char buf[100];

  int i = 0;

  char *tmp = &buf[0];
  while(*in)
    *tmp++ = *in++ ^ (i++ % 7);

  out[0] = 'x';
  out[1] = 'y';
  out[2] = 'z';
  out[3] = 'z';
  out[4] = 'y';
  for(int j = 0; j < i; j++)
    out[j+5] = buf[i - j - 1];

  return i;
}

}
