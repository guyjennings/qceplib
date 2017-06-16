message(qceplib-qwt PWD = $${PWD} QCEPLIB_QWT_VERSION = $${QCEPLIB_QWT_VERSION})

#contains (DEFINES,HAVE_BASE) {
#  error(must include qceplib-qwt prior to including qceplib-qwt)
#}

greaterThan(QT_MAJOR_VERSION,4): QT += printsupport concurrent

QT += opengl svg

QWTBASE = $${PWD}/qwt-6.1.3/src

INCLUDEPATH += $${QWTBASE}

HEADERS += \
  $${QWTBASE}/qwt.h \
  $${QWTBASE}/qwt_abstract_legend.h \
  $${QWTBASE}/qwt_abstract_scale.h \
  $${QWTBASE}/qwt_abstract_scale_draw.h \
  $${QWTBASE}/qwt_abstract_slider.h \
  $${QWTBASE}/qwt_analog_clock.h \
  $${QWTBASE}/qwt_arrow_button.h \
  $${QWTBASE}/qwt_clipper.h \
  $${QWTBASE}/qwt_color_map.h \
  $${QWTBASE}/qwt_column_symbol.h \
  $${QWTBASE}/qwt_compass.h \
  $${QWTBASE}/qwt_compass_rose.h \
  $${QWTBASE}/qwt_compat.h \
  $${QWTBASE}/qwt_counter.h \
  $${QWTBASE}/qwt_curve_fitter.h \
  $${QWTBASE}/qwt_date.h \
  $${QWTBASE}/qwt_date_scale_draw.h \
  $${QWTBASE}/qwt_date_scale_engine.h \
  $${QWTBASE}/qwt_dial.h \
  $${QWTBASE}/qwt_dial_needle.h \
  $${QWTBASE}/qwt_dyngrid_layout.h \
  $${QWTBASE}/qwt_event_pattern.h \
  $${QWTBASE}/qwt_global.h \
  $${QWTBASE}/qwt_graphic.h \
  $${QWTBASE}/qwt_interval.h \
  $${QWTBASE}/qwt_interval_symbol.h \
  $${QWTBASE}/qwt_knob.h \
  $${QWTBASE}/qwt_legend.h \
  $${QWTBASE}/qwt_legend_data.h \
  $${QWTBASE}/qwt_legend_label.h \
  $${QWTBASE}/qwt_magnifier.h \
  $${QWTBASE}/qwt_math.h \
  $${QWTBASE}/qwt_matrix_raster_data.h \
  $${QWTBASE}/qwt_null_paintdevice.h \
  $${QWTBASE}/qwt_painter.h \
  $${QWTBASE}/qwt_painter_command.h \
  $${QWTBASE}/qwt_panner.h \
  $${QWTBASE}/qwt_picker.h \
  $${QWTBASE}/qwt_picker_machine.h \
  $${QWTBASE}/qwt_pixel_matrix.h \
  $${QWTBASE}/qwt_plot.h \
  $${QWTBASE}/qwt_plot_abstract_barchart.h \
  $${QWTBASE}/qwt_plot_barchart.h \
  $${QWTBASE}/qwt_plot_canvas.h \
  $${QWTBASE}/qwt_plot_curve.h \
  $${QWTBASE}/qwt_plot_dict.h \
  $${QWTBASE}/qwt_plot_directpainter.h \
  $${QWTBASE}/qwt_plot_glcanvas.h \
  $${QWTBASE}/qwt_plot_grid.h \
  $${QWTBASE}/qwt_plot_histogram.h \
  $${QWTBASE}/qwt_plot_intervalcurve.h \
  $${QWTBASE}/qwt_plot_item.h \
  $${QWTBASE}/qwt_plot_layout.h \
  $${QWTBASE}/qwt_plot_legenditem.h \
  $${QWTBASE}/qwt_plot_magnifier.h \
  $${QWTBASE}/qwt_plot_marker.h \
  $${QWTBASE}/qwt_plot_multi_barchart.h \
  $${QWTBASE}/qwt_plot_panner.h \
  $${QWTBASE}/qwt_plot_picker.h \
  $${QWTBASE}/qwt_plot_rasteritem.h \
  $${QWTBASE}/qwt_plot_renderer.h \
  $${QWTBASE}/qwt_plot_rescaler.h \
  $${QWTBASE}/qwt_plot_scaleitem.h \
  $${QWTBASE}/qwt_plot_seriesitem.h \
  $${QWTBASE}/qwt_plot_shapeitem.h \
  $${QWTBASE}/qwt_plot_spectrocurve.h \
  $${QWTBASE}/qwt_plot_spectrogram.h \
  $${QWTBASE}/qwt_plot_svgitem.h \
  $${QWTBASE}/qwt_plot_textlabel.h \
  $${QWTBASE}/qwt_plot_tradingcurve.h \
  $${QWTBASE}/qwt_plot_zoneitem.h \
  $${QWTBASE}/qwt_plot_zoomer.h \
  $${QWTBASE}/qwt_point_3d.h \
  $${QWTBASE}/qwt_point_data.h \
  $${QWTBASE}/qwt_point_mapper.h \
  $${QWTBASE}/qwt_point_polar.h \
  $${QWTBASE}/qwt_raster_data.h \
  $${QWTBASE}/qwt_round_scale_draw.h \
  $${QWTBASE}/qwt_samples.h \
  $${QWTBASE}/qwt_sampling_thread.h \
  $${QWTBASE}/qwt_scale_div.h \
  $${QWTBASE}/qwt_scale_draw.h \
  $${QWTBASE}/qwt_scale_engine.h \
  $${QWTBASE}/qwt_scale_map.h \
  $${QWTBASE}/qwt_scale_widget.h \
  $${QWTBASE}/qwt_series_data.h \
  $${QWTBASE}/qwt_series_store.h \
  $${QWTBASE}/qwt_slider.h \
  $${QWTBASE}/qwt_spline.h \
  $${QWTBASE}/qwt_symbol.h \
  $${QWTBASE}/qwt_system_clock.h \
  $${QWTBASE}/qwt_text.h \
  $${QWTBASE}/qwt_text_engine.h \
  $${QWTBASE}/qwt_text_label.h \
  $${QWTBASE}/qwt_thermo.h \
  $${QWTBASE}/qwt_transform.h \
  $${QWTBASE}/qwt_wheel.h \
  $${QWTBASE}/qwt_widget_overlay.h

SOURCES += \
  $${QWTBASE}/qwt_abstract_legend.cpp \
  $${QWTBASE}/qwt_abstract_scale.cpp \
  $${QWTBASE}/qwt_abstract_scale_draw.cpp \
  $${QWTBASE}/qwt_abstract_slider.cpp \
  $${QWTBASE}/qwt_analog_clock.cpp \
  $${QWTBASE}/qwt_arrow_button.cpp \
  $${QWTBASE}/qwt_clipper.cpp \
  $${QWTBASE}/qwt_color_map.cpp \
  $${QWTBASE}/qwt_column_symbol.cpp \
  $${QWTBASE}/qwt_compass.cpp \
  $${QWTBASE}/qwt_compass_rose.cpp \
  $${QWTBASE}/qwt_counter.cpp \
  $${QWTBASE}/qwt_curve_fitter.cpp \
  $${QWTBASE}/qwt_date.cpp \
  $${QWTBASE}/qwt_date_scale_draw.cpp \
  $${QWTBASE}/qwt_date_scale_engine.cpp \
  $${QWTBASE}/qwt_dial.cpp \
  $${QWTBASE}/qwt_dial_needle.cpp \
  $${QWTBASE}/qwt_dyngrid_layout.cpp \
  $${QWTBASE}/qwt_event_pattern.cpp \
  $${QWTBASE}/qwt_graphic.cpp \
  $${QWTBASE}/qwt_interval.cpp \
  $${QWTBASE}/qwt_interval_symbol.cpp \
  $${QWTBASE}/qwt_knob.cpp \
  $${QWTBASE}/qwt_legend.cpp \
  $${QWTBASE}/qwt_legend_data.cpp \
  $${QWTBASE}/qwt_legend_label.cpp \
  $${QWTBASE}/qwt_magnifier.cpp \
  $${QWTBASE}/qwt_math.cpp \
  $${QWTBASE}/qwt_matrix_raster_data.cpp \
  $${QWTBASE}/qwt_null_paintdevice.cpp \
  $${QWTBASE}/qwt_painter.cpp \
  $${QWTBASE}/qwt_painter_command.cpp \
  $${QWTBASE}/qwt_panner.cpp \
  $${QWTBASE}/qwt_picker.cpp \
  $${QWTBASE}/qwt_picker_machine.cpp \
  $${QWTBASE}/qwt_pixel_matrix.cpp \
  $${QWTBASE}/qwt_plot.cpp \
  $${QWTBASE}/qwt_plot_abstract_barchart.cpp \
  $${QWTBASE}/qwt_plot_axis.cpp \
  $${QWTBASE}/qwt_plot_barchart.cpp \
  $${QWTBASE}/qwt_plot_canvas.cpp \
  $${QWTBASE}/qwt_plot_curve.cpp \
  $${QWTBASE}/qwt_plot_dict.cpp \
  $${QWTBASE}/qwt_plot_directpainter.cpp \
  $${QWTBASE}/qwt_plot_glcanvas.cpp \
  $${QWTBASE}/qwt_plot_grid.cpp \
  $${QWTBASE}/qwt_plot_histogram.cpp \
  $${QWTBASE}/qwt_plot_intervalcurve.cpp \
  $${QWTBASE}/qwt_plot_item.cpp \
  $${QWTBASE}/qwt_plot_layout.cpp \
  $${QWTBASE}/qwt_plot_legenditem.cpp \
  $${QWTBASE}/qwt_plot_magnifier.cpp \
  $${QWTBASE}/qwt_plot_marker.cpp \
  $${QWTBASE}/qwt_plot_multi_barchart.cpp \
  $${QWTBASE}/qwt_plot_panner.cpp \
  $${QWTBASE}/qwt_plot_picker.cpp \
  $${QWTBASE}/qwt_plot_rasteritem.cpp \
  $${QWTBASE}/qwt_plot_renderer.cpp \
  $${QWTBASE}/qwt_plot_rescaler.cpp \
  $${QWTBASE}/qwt_plot_scaleitem.cpp \
  $${QWTBASE}/qwt_plot_seriesitem.cpp \
  $${QWTBASE}/qwt_plot_shapeitem.cpp \
  $${QWTBASE}/qwt_plot_spectrocurve.cpp \
  $${QWTBASE}/qwt_plot_spectrogram.cpp \
  $${QWTBASE}/qwt_plot_svgitem.cpp \
  $${QWTBASE}/qwt_plot_textlabel.cpp \
  $${QWTBASE}/qwt_plot_tradingcurve.cpp \
  $${QWTBASE}/qwt_plot_xml.cpp \
  $${QWTBASE}/qwt_plot_zoneitem.cpp \
  $${QWTBASE}/qwt_plot_zoomer.cpp \
  $${QWTBASE}/qwt_point_3d.cpp \
  $${QWTBASE}/qwt_point_data.cpp \
  $${QWTBASE}/qwt_point_mapper.cpp \
  $${QWTBASE}/qwt_point_polar.cpp \
  $${QWTBASE}/qwt_raster_data.cpp \
  $${QWTBASE}/qwt_round_scale_draw.cpp \
  $${QWTBASE}/qwt_sampling_thread.cpp \
  $${QWTBASE}/qwt_scale_div.cpp \
  $${QWTBASE}/qwt_scale_draw.cpp \
  $${QWTBASE}/qwt_scale_engine.cpp \
  $${QWTBASE}/qwt_scale_map.cpp \
  $${QWTBASE}/qwt_scale_widget.cpp \
  $${QWTBASE}/qwt_series_data.cpp \
  $${QWTBASE}/qwt_slider.cpp \
  $${QWTBASE}/qwt_spline.cpp \
  $${QWTBASE}/qwt_symbol.cpp \
  $${QWTBASE}/qwt_system_clock.cpp \
  $${QWTBASE}/qwt_text.cpp \
  $${QWTBASE}/qwt_text_engine.cpp \
  $${QWTBASE}/qwt_text_label.cpp \
  $${QWTBASE}/qwt_thermo.cpp \
  $${QWTBASE}/qwt_transform.cpp \
  $${QWTBASE}/qwt_wheel.cpp \
  $${QWTBASE}/qwt_widget_overlay.cpp

