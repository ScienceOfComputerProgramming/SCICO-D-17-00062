#include "../stubs.h"

#define ADDRSIZE        500 // originally 500
#define PSBUFSIZE       BASE_SZ
#define MAXNAME		(4 * BASE_SZ / 5)
#define NOCHAR		-1
#define TRUE 1
#define FALSE 0

int main (void)
{
  // originally function arguments
  char addr[ADDRSIZE];
  char pvpbuf[PSBUFSIZE];

  int p, q, q_old;
  int c;

  int pvpbuf_end = sizeof (pvpbuf);

  int bslashmode;
  int i;

  // alternative method to initialize addr to attack string
  /*
  for(i=0; i<20; i=i+2)
  {
    addr[i] = '\\';
    addr[i+1] = '\377'; // when cast to int, gets sign extended to -1 (NOCHAR)
  }
  */

  p = 0;
  q = 0;
  bslashmode = FALSE;

  c = NOCHAR;

  q_old = q;
  do
  {
    // bounds check and write lookahead (c) to pvpbuf
    if (c != NOCHAR && !bslashmode)
    {
      if (q >= pvpbuf_end - 1)
	return 0;
      pvpbuf[q] = c;
      q++;
    }

    // read next input char
    c = addr[p] & 0xff; // mask out high bits to prevent sign extension
    p++;
    if (c == EOS)
      break;

    //assert (q < pvpbuf_end);
    /* OK */  
    pvpbuf[q] = EOS; // precautiously write EOS to dest

    if (bslashmode)
    {
      bslashmode = FALSE;

      //assert (q < pvpbuf_end);
      /* OK */	
      pvpbuf[q] = '\\';
      q++;
      continue;
    }

    if (c == '\\')
      bslashmode = TRUE;
    if (c == NOCHAR) // not supposed to be in the input alphabet
      continue; // skip bounds check on next for loop so another \ can be copied
    if (c == EOS)
      break;
  } while (1);

  if (q_old != q)
  {
    //assert (q < pvpbuf_end);
    /* OK */
    pvpbuf[q] = 0;
    q++;

    if (q - q_old > MAXNAME)
      return 0;
  }

  return 0;
}