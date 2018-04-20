#ifndef QCEPBZLIB_H
#define QCEPBZLIB_H

#include "qceplib_global.h"
#include "bzlib.h"

extern QCEP_EXPORT BZFILE* qcepBZ2_bzWriteOpen (
      int*  bzerror,
      FILE* f,
      int   blockSize100k,
      int   verbosity,
      int   workFactor
   );

extern QCEP_EXPORT void qcepBZ2_bzWrite (
      int*    bzerror,
      BZFILE* b,
      void*   buf,
      int     len
   );

extern QCEP_EXPORT void qcepBZ2_bzWriteClose (
      int*          bzerror,
      BZFILE*       b,
      int           abandon,
      unsigned int* nbytes_in,
      unsigned int* nbytes_out
   );

#endif // QCEPBZLIB_H
