#include "qcepoutputfileformatter.h"
#include "qcepimagedata.h"
#include "qcepoutputfileformattersettings.h"
#include "zlib.h"

void QcepOutputFileFormatter::compressOutputDataGzip()
{
  gzFile gzf = gzopen(qPrintable(m_FileName), "w");

  gzwrite(gzf, (void*) m_OutputBuffer, m_OutputCount);

  gzclose(gzf);
}
