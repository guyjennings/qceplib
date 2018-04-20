#include "qcepbzlib.h"

BZFILE* qcepBZ2_bzWriteOpen(int *bzerror,
                         FILE *f,
                         int blockSize100k,
                         int verbosity,
                         int workFactor)
{
  return BZ2_bzWriteOpen(bzerror,
                         f,
                         blockSize100k,
                         verbosity,
                         workFactor);
}

void qcepBZ2_bzWriteClose(int          *bzerror,
                             BZFILE       *b,
                             int           abandon,
                             unsigned int *nbytes_in,
                             unsigned int *nbytes_out)
{
  BZ2_bzWriteClose(bzerror,
                   b,
                   abandon,
                   nbytes_in,
                   nbytes_out);
}

void qcepBZ2_bzWrite(int    *bzerror,
                     BZFILE *b,
                     void   *buf,
                     int     len)
{
  BZ2_bzWrite(bzerror,
              b,
              buf,
              len);
}
