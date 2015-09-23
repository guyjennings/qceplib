#ifndef QCEPMASKDATA_H
#define QCEPMASKDATA_H

#include "qcepimagedata.h"
#include "qcepmaskdata-ptr.h"

class QcepMaskData : public QcepImageData<short>
{
  Q_OBJECT

public:
  QcepMaskData(QcepSettingsSaverWPtr saver, int width, int height, int def, QcepObject *parent);
  ~QcepMaskData();

public slots:
  bool maskValue(int x, int y) const;
  void setMaskValue(int x, int y, bool mval);

  QcepMaskDataPtr copyMask(QcepObject *parent);

  void setCircularMask();
  void showMaskAll();
  void hideMaskAll();
  void invertMask();

  void growMask();
  void shrinkMask();

  void andMask(QcepMaskDataPtr mask);
  void orMask(QcepMaskDataPtr mask);
  void xorMask(QcepMaskDataPtr mask);
  void andNotMask(QcepMaskDataPtr mask);
  void orNotMask(QcepMaskDataPtr mask);
  void xorNotMask(QcepMaskDataPtr mask);

  void maskCircle(double cx, double cy, double r, bool val);

  int countMaskedPixels() const;
  int countUnmaskedPixels() const;
  int countOverflowPixels() const;

  QString summary();

  QImage thumbnailImage() const;
  QSize  thumbnailImageSize() const;

public:
  void copyMaskTo(QcepMaskDataPtr dest);

  short* mask();

  template <typename T> void setMaskRange(QSharedPointer< QcepImageData<T> > image,  T min, T max, bool inRange, bool setTo);
  template <typename T> void showMaskRange(QSharedPointer< QcepImageData<T> > image, T min, T max);
  template <typename T> void hideMaskRange(QSharedPointer< QcepImageData<T> > image, T min, T max);

private:
  enum {
    ThumbnailWidth = 24,
    ThumbnailHeight = 24
  };
};

#endif // QCEPMASKDATA_H