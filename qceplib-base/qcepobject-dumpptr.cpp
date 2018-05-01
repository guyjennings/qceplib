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

void QcepObject::dumpObjectReferenceCounts(int lev)
{
  int weakRef   = weakReferenceCount();
  int strongRef = strongReferenceCount();

  if (strongRef >= lev) {
    const QMetaObject* metaObject = this->metaObject();

    if (strongRef > 1) {
      printLine(tr("<span style=\"color:red\">%1 : %2 : weakRefs : %3; strongRefs : %4</span>")
                .arg(objectName())
                .arg(metaObject->className())
                .arg(weakRef)
                .arg(strongRef));
    } else {
      printLine(tr("%1 : %2 : weakRefs : %3; strongRefs : %4")
                .arg(objectName())
                .arg(metaObject->className())
                .arg(weakRef)
                .arg(strongRef));
    }
  }
}
