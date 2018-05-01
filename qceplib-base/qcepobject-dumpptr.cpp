#define _ALLOW_KEYWORD_MACROS
#define private public
#include <qsharedpointer.h>
#undef  private

#include "qcepobject.h"

int QcepObject::strongReferenceCount()
{
  int res = -1;

  QtSharedPointer::ExternalRefCountData *d = NULL;

  {
    QcepObjectPtr me = sharedFromThis();

    if (me) {
      d = me.d;
    }
  }

  if (d) {
    res = d->strongref.load();
  }

  return res;
}

int QcepObject::weakReferenceCount()
{
  int res = -1;

  QtSharedPointer::ExternalRefCountData *d = NULL;

  {
    QcepObjectPtr me = sharedFromThis();

    if (me) {
      d = me.d;
    }
  }

  if (d) {
    res = d->weakref.load();
  }

  return res;
}
