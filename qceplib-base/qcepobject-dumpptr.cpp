#define private public
#include <qsharedpointer.h>
#undef  private

#include "qcepobject.h"

void QcepObject::dumpObjectReferenceCounts()
{
  QtSharedPointer::ExternalRefCountData *d = NULL;

  {
    QcepObjectPtr me = sharedFromThis();

    if (me) {
      d = me.d;
    }
  }

  if (d) {
    const QMetaObject* metaObject = this->metaObject();

    if (d->strongref.load() > 1) {
      printLine(tr("<span style=\"color:red\">%1 : %2 : weakRefs : %3; strongRefs : %4</span>")
                .arg(objectName())
                .arg(metaObject->className())
                .arg(d->weakref.load())
                .arg(d->strongref.load()));
    } else {
      printLine(tr("%1 : %2 : weakRefs : %3; strongRefs : %4")
                .arg(objectName())
                .arg(metaObject->className())
                .arg(d->weakref.load())
                .arg(d->strongref.load()));
    }
  }
}
