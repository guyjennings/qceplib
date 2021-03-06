#ifndef QCEPPLOTMEASURER_H
#define QCEPPLOTMEASURER_H

#include <qwt_plot_picker.h>

#include "qcepplot-ptr.h"

class QcepPlotMeasurer : public QwtPlotPicker
{
  Q_OBJECT

public:
  QcepPlotMeasurer(QWidget *canvas, QcepPlotPtr plot);

  virtual QwtText trackerTextF(const QPointF &pos) const;

private:
  QcepPlotPtr m_Plot;
};

#endif // QCEPPLOTMEASURER_H
