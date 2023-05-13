/**
 * PALLAV REGMI
 * CS 241L
*/


#include <stdio.h>
#include <stdlib.h>

int get_reverse_bits(unsigned char bytes[]) 
{
    int i;
    const int num_bytes = 4;
    const unsigned char mask = 0x03; /*mask to extract the last 2 bits*/
    int n = 0;
    i=0;
    while(i < num_bytes) 
    {
      unsigned char extracted_bits = bytes[i] & mask;
      n |= (extracted_bits << (i*2));
      i++;
    }
    return n;
}


int get_int(unsigned char bytes[]) 
{
    int i;
    const int num_bytes = 4;
    const int num_bits_per_byte = 8;
    int n = 0;

    for (i = num_bytes - 1; i >= 0; i--) 
    {
      n <<= num_bits_per_byte;
      n |= (int) bytes[i];
    }
  return n;
}


int main(int argc, char** argv)
{
  char* infilename = argv[1];

  unsigned char header[54];

  FILE* in = fopen(infilename, "rb");

  int pixelDataSize, i;

  /* read header into array */
  fread(header, 1, 54, in);

  pixelDataSize = get_int(&header[34]);

  for(i = 0; i < pixelDataSize/4; ++i)
  {
      unsigned char bytes[4];
      
      /* color order is BGR */ 
      fread(bytes, 1, 4, in);

      if(get_reverse_bits(bytes) != 0)
      {
        printf("%c", get_reverse_bits(bytes));
      }
      
      else
      {
        break;
      }
 }
  
  fclose(in);
  return 0;
}


