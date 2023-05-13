/**
 * PALLAV REGMI
 * CS 241L
*/

#include <stdio.h>
#include <stdlib.h>

void get_bits(unsigned int n, unsigned char bytes[]) 
{
  int i;
  const int num_bytes = 4;
  const int num_bits_to_extract = 2;
  const unsigned char mask = 0x03; /*mask to extract the last 2 bits*/

  for (i = 0; i < num_bytes; i++) 
  {
    int shift = i * num_bits_to_extract;
    unsigned char extracted_bits = (n >> shift) & mask;
    bytes[i] = extracted_bits | (bytes[i] & ~mask);
  }
}


int get_Int(unsigned char bytes[]) 
{
    int i;
    const int num_bytes = 4;
    int n = 0;

    for (i = 0; i < num_bytes; i++) 
    {
        n |= ((int) bytes[i]) << (i * 8);
    }
    return n;
}



int main(int argc, char** argv)
{
  char* infilename = argv[1];
  char* outfilename = argv[2];

  unsigned char header[54];

  FILE* in = fopen(infilename, "rb");
  FILE* out = fopen(outfilename, "wb");


  int pixelDataSize;
  int flag =1;
  int i;

  /* read header into array */
  fread(header, 1, 54, in);

  /* is this really a bitmap? */
  if(header[0] != 'B' || header[1] != 'M')
  {
    printf("Input file is not a bitmap\n");
  }

  /* Is the header size what we expect? */
  if(get_Int(&header[10]) != 54)
  {
    printf("Unexpected header size\n");
  }

  /* How many bits per pixel? Expecting 24*/
  if(!(header[28] == 24 && header[29] == 0))
  {
    printf("Unexpected number of bits/pixel\n");
  }

  pixelDataSize = get_Int(&header[34]);

  /* write header to output file */
  fwrite(header, 1, sizeof(header), out);

  for(i = 0; i < pixelDataSize/4; ++i)
  {
      unsigned char bytes[4];
      
      char c = getchar();
      fread(bytes, 1, 4, in);
        if(c != EOF)
        {
            get_bits(c, bytes);
        }
        else if(flag)
        {
            flag = 0;
            get_bits(0, bytes);
        }
      fwrite(bytes, 1, 4, out);
    }
  fclose(in);
  fclose(out);
  return 0;
}
