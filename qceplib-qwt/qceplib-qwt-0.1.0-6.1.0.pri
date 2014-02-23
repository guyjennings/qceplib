message(qceplib-qwt PWD = $${PWD})

QT += opengl printsupport svg concurrent

INCLUDEPATH += $${PWD}/qwt-6.1/src

HEADERS += \
  $${PWD}/qwt-6.1/src/qwt.h \
  $${PWD}/qwt-6.1/src/qwt_abstract_legend.h \
  $${PWD}/qwt-6.1/src/qwt_abstract_scale.h \
  $${PWD}/qwt-6.1/src/qwt_abstract_scale_draw.h \
  $${PWD}/qwt-6.1/src/qwt_abstract_slider.h \
  $${PWD}/qwt-6.1/src/qwt_analog_clock.h \
  $${PWD}/qwt-6.1/src/qwt_arrow_button.h \
  $${PWD}/qwt-6.1/src/qwt_clipper.h \
  $${PWD}/qwt-6.1/src/qwt_color_map.h \
  $${PWD}/qwt-6.1/src/qwt_column_symbol.h \
  $${PWD}/qwt-6.1/src/qwt_compass.h \
  $${PWD}/qwt-6.1/src/qwt_compass_rose.h \
  $${PWD}/qwt-6.1/src/qwt_compat.h \
  $${PWD}/qwt-6.1/src/qwt_counter.h \
  $${PWD}/qwt-6.1/src/qwt_curve_fitter.h \
  $${PWD}/qwt-6.1/src/qwt_date.h \
  $${PWD}/qwt-6.1/src/qwt_date_scale_draw.h \
  $${PWD}/qwt-6.1/src/qwt_date_scale_engine.h \
  $${PWD}/qwt-6.1/src/qwt_dial.h \
  $${PWD}/qwt-6.1/src/qwt_dial_needle.h \
  $${PWD}/qwt-6.1/src/qwt_dyngrid_layout.h \
  $${PWD}/qwt-6.1/src/qwt_event_pattern.h \
  $${PWD}/qwt-6.1/src/qwt_global.h \
  $${PWD}/qwt-6.1/src/qwt_graphic.h \
  $${PWD}/qwt-6.1/src/qwt_interval.h \
  $${PWD}/qwt-6.1/src/qwt_interval_symbol.h \
  $${PWD}/qwt-6.1/src/qwt_knob.h \
  $${PWD}/qwt-6.1/src/qwt_legend.h \
  $${PWD}/qwt-6.1/src/qwt_legend_data.h \
  $${PWD}/qwt-6.1/src/qwt_legend_label.h \
  $${PWD}/qwt-6.1/src/qwt_magnifier.h \
  $${PWD}/qwt-6.1/src/qwt_math.h \
  $${PWD}/qwt-6.1/src/qwt_matrix_raster_data.h \
  $${PWD}/qwt-6.1/src/qwt_null_paintdevice.h \
  $${PWD}/qwt-6.1/src/qwt_painter.h \
  $${PWD}/qwt-6.1/src/qwt_painter_command.h \
  $${PWD}/qwt-6.1/src/qwt_panner.h \
  $${PWD}/qwt-6.1/src/qwt_picker.h \
  $${PWD}/qwt-6.1/src/qwt_picker_machine.h \
  $${PWD}/qwt-6.1/src/qwt_pixel_matrix.h \
  $${PWD}/qwt-6.1/src/qwt_plot.h \
  $${PWD}/qwt-6.1/src/qwt_plot_abstract_barchart.h \
  $${PWD}/qwt-6.1/src/qwt_plot_barchart.h \
  $${PWD}/qwt-6.1/src/qwt_plot_canvas.h \
  $${PWD}/qwt-6.1/src/qwt_plot_curve.h \
  $${PWD}/qwt-6.1/src/qwt_plot_dict.h \
  $${PWD}/qwt-6.1/src/qwt_plot_directpainter.h \
  $${PWD}/qwt-6.1/src/qwt_plot_glcanvas.h \
  $${PWD}/qwt-6.1/src/qwt_plot_grid.h \
  $${PWD}/qwt-6.1/src/qwt_plot_histogram.h \
  $${PWD}/qwt-6.1/src/qwt_plot_intervalcurve.h \
  $${PWD}/qwt-6.1/src/qwt_plot_item.h \
  $${PWD}/qwt-6.1/src/qwt_plot_layout.h \
  $${PWD}/qwt-6.1/src/qwt_plot_legenditem.h \
  $${PWD}/qwt-6.1/src/qwt_plot_magnifier.h \
  $${PWD}/qwt-6.1/src/qwt_plot_marker.h \
  $${PWD}/qwt-6.1/src/qwt_plot_multi_barchart.h \
  $${PWD}/qwt-6.1/src/qwt_plot_panner.h \
  $${PWD}/qwt-6.1/src/qwt_plot_picker.h \
  $${PWD}/qwt-6.1/src/qwt_plot_rasteritem.h \
  $${PWD}/qwt-6.1/src/qwt_plot_renderer.h \
  $${PWD}/qwt-6.1/src/qwt_plot_rescaler.h \
  $${PWD}/qwt-6.1/src/qwt_plot_scaleitem.h \
  $${PWD}/qwt-6.1/src/qwt_plot_seriesitem.h \
  $${PWD}/qwt-6.1/src/qwt_plot_shapeitem.h \
  $${PWD}/qwt-6.1/src/qwt_plot_spectrocurve.h \
  $${PWD}/qwt-6.1/src/qwt_plot_spectrogram.h \
  $${PWD}/qwt-6.1/src/qwt_plot_svgitem.h \
  $${PWD}/qwt-6.1/src/qwt_plot_textlabel.h \
  $${PWD}/qwt-6.1/src/qwt_plot_tradingcurve.h \
  $${PWD}/qwt-6.1/src/qwt_plot_zoneitem.h \
  $${PWD}/qwt-6.1/src/qwt_plot_zoomer.h \
  $${PWD}/qwt-6.1/src/qwt_point_3d.h \
  $${PWD}/qwt-6.1/src/qwt_point_data.h \
  $${PWD}/qwt-6.1/src/qwt_point_mapper.h \
  $${PWD}/qwt-6.1/src/qwt_point_polar.h \
  $${PWD}/qwt-6.1/src/qwt_raster_data.h \
  $${PWD}/qwt-6.1/src/qwt_round_scale_draw.h \
  $${PWD}/qwt-6.1/src/qwt_samples.h \
  $${PWD}/qwt-6.1/src/qwt_sampling_thread.h \
  $${PWD}/qwt-6.1/src/qwt_scale_div.h \
  $${PWD}/qwt-6.1/src/qwt_scale_draw.h \
  $${PWD}/qwt-6.1/src/qwt_scale_engine.h \
  $${PWD}/qwt-6.1/src/qwt_scale_map.h \
  $${PWD}/qwt-6.1/src/qwt_scale_widget.h \
  $${PWD}/qwt-6.1/src/qwt_series_data.h \
  $${PWD}/qwt-6.1/src/qwt_series_store.h \
  $${PWD}/qwt-6.1/src/qwt_slider.h \
  $${PWD}/qwt-6.1/src/qwt_spline.h \
  $${PWD}/qwt-6.1/src/qwt_symbol.h \
  $${PWD}/qwt-6.1/src/qwt_system_clock.h \
  $${PWD}/qwt-6.1/src/qwt_text.h \
  $${PWD}/qwt-6.1/src/qwt_text_engine.h \
  $${PWD}/qwt-6.1/src/qwt_text_label.h \
  $${PWD}/qwt-6.1/src/qwt_thermo.h \
  $${PWD}/qwt-6.1/src/qwt_transform.h \
  $${PWD}/qwt-6.1/src/qwt_wheel.h \
  $${PWD}/qwt-6.1/src/qwt_widget_overlay.h

SOURCES += \
  $${PWD}/qwt-6.1/src/qwt_abstract_legend.cpp \
  $${PWD}/qwt-6.1/src/qwt_abstract_scale.cpp \
  $${PWD}/qwt-6.1/src/qwt_abstract_scale_draw.cpp \
  $${PWD}/qwt-6.1/src/qwt_abstract_slider.cpp \
  $${PWD}/qwt-6.1/src/qwt_analog_clock.cpp \
  $${PWD}/qwt-6.1/src/qwt_arrow_button.cpp \
  $${PWD}/qwt-6.1/src/qwt_clipper.cpp \
  $${PWD}/qwt-6.1/src/qwt_color_map.cpp \
  $${PWD}/qwt-6.1/src/qwt_column_symbol.cpp \
  $${PWD}/qwt-6.1/src/qwt_compass.cpp \
  $${PWD}/qwt-6.1/src/qwt_compass_rose.cpp \
  $${PWD}/qwt-6.1/src/qwt_counter.cpp \
  $${PWD}/qwt-6.1/src/qwt_curve_fitter.cpp \
  $${PWD}/qwt-6.1/src/qwt_date.cpp \
  $${PWD}/qwt-6.1/src/qwt_date_scale_draw.cpp \
  $${PWD}/qwt-6.1/src/qwt_date_scale_engine.cpp \
  $${PWD}/qwt-6.1/src/qwt_dial.cpp \
  $${PWD}/qwt-6.1/src/qwt_dial_needle.cpp \
  $${PWD}/qwt-6.1/src/qwt_dyngrid_layout.cpp \
  $${PWD}/qwt-6.1/src/qwt_event_pattern.cpp \
  $${PWD}/qwt-6.1/src/qwt_graphic.cpp \
  $${PWD}/qwt-6.1/src/qwt_interval.cpp \
  $${PWD}/qwt-6.1/src/qwt_interval_symbol.cpp \
  $${PWD}/qwt-6.1/src/qwt_knob.cpp \
  $${PWD}/qwt-6.1/src/qwt_legend.cpp \
  $${PWD}/qwt-6.1/src/qwt_legend_data.cpp \
  $${PWD}/qwt-6.1/src/qwt_legend_label.cpp \
  $${PWD}/qwt-6.1/src/qwt_magnifier.cpp \
  $${PWD}/qwt-6.1/src/qwt_math.cpp \
  $${PWD}/qwt-6.1/src/qwt_matrix_raster_data.cpp \
  $${PWD}/qwt-6.1/src/qwt_null_paintdevice.cpp \
  $${PWD}/qwt-6.1/src/qwt_painter.cpp \
  $${PWD}/qwt-6.1/src/qwt_painter_command.cpp \
  $${PWD}/qwt-6.1/src/qwt_panner.cpp \
  $${PWD}/qwt-6.1/src/qwt_picker.cpp \
  $${PWD}/qwt-6.1/src/qwt_picker_machine.cpp \
  $${PWD}/qwt-6.1/src/qwt_pixel_matrix.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_abstract_barchart.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_axis.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_barchart.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_canvas.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_curve.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_dict.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_directpainter.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_glcanvas.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_grid.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_histogram.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_intervalcurve.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_item.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_layout.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_legenditem.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_magnifier.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_marker.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_multi_barchart.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_panner.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_picker.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_rasteritem.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_renderer.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_rescaler.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_scaleitem.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_seriesitem.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_shapeitem.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_spectrocurve.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_spectrogram.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_svgitem.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_textlabel.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_tradingcurve.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_xml.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_zoneitem.cpp \
  $${PWD}/qwt-6.1/src/qwt_plot_zoomer.cpp \
  $${PWD}/qwt-6.1/src/qwt_point_3d.cpp \
  $${PWD}/qwt-6.1/src/qwt_point_data.cpp \
  $${PWD}/qwt-6.1/src/qwt_point_mapper.cpp \
  $${PWD}/qwt-6.1/src/qwt_point_polar.cpp \
  $${PWD}/qwt-6.1/src/qwt_raster_data.cpp \
  $${PWD}/qwt-6.1/src/qwt_round_scale_draw.cpp \
  $${PWD}/qwt-6.1/src/qwt_sampling_thread.cpp \
  $${PWD}/qwt-6.1/src/qwt_scale_div.cpp \
  $${PWD}/qwt-6.1/src/qwt_scale_draw.cpp \
  $${PWD}/qwt-6.1/src/qwt_scale_engine.cpp \
  $${PWD}/qwt-6.1/src/qwt_scale_map.cpp \
  $${PWD}/qwt-6.1/src/qwt_scale_widget.cpp \
  $${PWD}/qwt-6.1/src/qwt_series_data.cpp \
  $${PWD}/qwt-6.1/src/qwt_slider.cpp \
  $${PWD}/qwt-6.1/src/qwt_spline.cpp \
  $${PWD}/qwt-6.1/src/qwt_symbol.cpp \
  $${PWD}/qwt-6.1/src/qwt_system_clock.cpp \
  $${PWD}/qwt-6.1/src/qwt_text.cpp \
  $${PWD}/qwt-6.1/src/qwt_text_engine.cpp \
  $${PWD}/qwt-6.1/src/qwt_text_label.cpp \
  $${PWD}/qwt-6.1/src/qwt_thermo.cpp \
  $${PWD}/qwt-6.1/src/qwt_transform.cpp \
  $${PWD}/qwt-6.1/src/qwt_wheel.cpp \
  $${PWD}/qwt-6.1/src/qwt_widget_overlay.cpp

