message("qceplib-base PWD = $${PWD} QCEPLIB_VERSION = $${QCEPLIB_VERSION}")

greaterThan(QT_MAJOR_VERSION,4) {
  QT += widgets concurrent
}

CONFIG += qt

QT += script

include(qceplib-base-include-$${CEPLIB_VERSION}.pri)

contains (DEFINES,HAVE_QWT) {
 message(qceplib-base wants qwt)
 include(../qceplib-qwt-include.pri)
} else {
 message(qceplib-base no qwt)
}

include(../qceplib-tiff-include.pri)

SOURCES += \
  $$PWD/qcepmacros.cpp \
  $$PWD/qcepdebug.cpp \
  $$PWD/qcepproperty.cpp \
  $$PWD/qcepvector3dproperty.cpp \
  $$PWD/qcepmatrix3x3property.cpp \
  $$PWD/qcepplotmarker.cpp \
  $$PWD/qcepplotmarkerlist.cpp \
  $$PWD/qcepplotmarkerlistproperty.cpp \
  $$PWD/qcepmutexlocker.cpp \
  $$PWD/qcepdocumentationdictionary.cpp \
  $$PWD/qcepimagedata.cpp \
  $$PWD/qcepimagequeue.cpp \
  $$PWD/qcepimagedataformatfactory.cpp \
  $$PWD/qcepimagedataformat.cpp \
  $$PWD/qcepobjectnamer.cpp \
  $$PWD/qcepexperiment.cpp \
  $$PWD/qceppropertyvalue.cpp \
  $$PWD/qcepmatrix3x3.cpp \
  $$PWD/qcepvector3d.cpp \
  $$PWD/qcepobject.cpp \
  $$PWD/qcepdataobject.cpp \
  $$PWD/qcepdatagroup.cpp \
  $$PWD/qcepdataarray.cpp \
  $$PWD/qcepdatacolumnscan.cpp \
  $$PWD/qcepdatacolumn.cpp \
  $$PWD/qcepdataset.cpp \
  $$PWD/qcepdatasetmodel.cpp \
  $$PWD/qcepdataarrayspreadsheetmodel.cpp \
  $$PWD/qcepdatacolumnspreadsheetmodel.cpp \
  $$PWD/qcepdatacolumnscanspreadsheetmodel.cpp \
  $$PWD/qcepdatagroupspreadsheetmodel.cpp \
  $$PWD/qcepdataobjectpropertiesmodel.cpp \
  $$PWD/qcepspreadsheetmodel.cpp \
  $$PWD/qceppropertiesmodel.cpp  \
  $$PWD/qcepintegrateddata.cpp \
  $$PWD/qcepintegrateddataqueue.cpp \
  $$PWD/qcepintegrateddataspreadsheetmodel.cpp \
  $$PWD/qcepmaskdata.cpp \
  $$PWD/qcepallocator.cpp \
  $$PWD/qcepapplication.cpp \
  $$PWD/qcepthread.cpp \
  $$PWD/qcepimagedataspreadsheetmodel.cpp \
  $$PWD/qcepnewdatagroupdialog.cpp \
  $$PWD/qcepnewdatacolumndialog.cpp \
  $$PWD/qcepnewcolumnscandialog.cpp \
  $$PWD/qcepnewimagedialog.cpp \
  $$PWD/qcepnewdataarraydialog.cpp \
  $$PWD/qcepdataobjectpropertieswindow.cpp \
  $$PWD/qcepdataobjectspreadsheetwindow.cpp \
  $$PWD/qcepscriptengine.cpp \
  $$PWD/qcepmainwindow.cpp \
  $$PWD/qcepscatterplotgraphmodel.cpp \
  $$PWD/qcepdatasetselectiondialog.cpp \
  $$PWD/qcepdataimportcommand.cpp \
  $$PWD/qcepdataexportcommand.cpp \
  $$PWD/qcepdataimportdialog.cpp \
  $$PWD/qcepdataexportdialog.cpp \
  $$PWD/qcepdataimportparameters.cpp \
  $$PWD/qcepdataexportparameters.cpp \
  $$PWD/qcepfileimporter.cpp \
  $$PWD/qcepfileimportertext.cpp \
  $$PWD/qcepfileimportertiff.cpp \
  $$PWD/qcepfileimporterhdf.cpp \
  $$PWD/qcepfileimportermultiple.cpp \
  $$PWD/qcepfileformatter.cpp \
  $$PWD/qcepfileformattertext.cpp \
  $$PWD/qcepfileformatterhdf.cpp \
  $$PWD/qcepfileformatternexus.cpp \
  $$PWD/qcepsetrangeofimagedialog.cpp \
  $$PWD/qcepsetdatavaluerangedialog.cpp \
  $$PWD/qcepfixupgainmapdialog.cpp \
  $$PWD/qcepfixupgainmapcommand.cpp \
  $$PWD/qcepsetdatavaluerangecommand.cpp \
  $$PWD/qcepsetrangeofimagecommand.cpp \
  $$PWD/qcepfixupdetectorpanelgains.cpp \
  $$PWD/qcepscandetectorpanelgains.cpp \
  $$PWD/qcepmainwindowsettings.cpp \
  $$PWD/qcepobjecttreemodel.cpp \
  $$PWD/qcepobjecttreewindow.cpp \
  $$PWD/qcepobjectpropertiesmodel.cpp \
  $$PWD/qnewthread.cpp \
  $$PWD/qceprunguard.cpp \
  $$PWD/qcepplotwidget.cpp \
  $$PWD/qcepplotwidgetsettings.cpp \
  $$PWD/qcepplotwidgetdialog.cpp \
  $$PWD/qcepplotcommand.cpp \
  $$PWD/qcepplotoverlay.cpp \
  $$PWD/qcepcolormaplibrary.cpp \
  $$PWD/qcepcolormap.cpp \
  $$PWD/qcepmaskcolormap.cpp \
  $$PWD/qcepplotcontextmenucommand.cpp \
  $$PWD/qcepautoscalecommand.cpp \
  $$PWD/qcepzoomincommand.cpp \
  $$PWD/qcepplotbuttoncommand.cpp \
  $$PWD/qcepzoomoutcommand.cpp \
  $$PWD/qcepzoomallcommand.cpp \
  $$PWD/qcepprintplotbutton.cpp \
  $$PWD/qcepplotpreferencesbutton.cpp \
  $$PWD/qcepprintplotcommand.cpp \
  $$PWD/qcepplotpreferencescommand.cpp \
  $$PWD/qcepaxissubmenucommand.cpp \
  $$PWD/qceprasterdata.cpp \
  $$PWD/qcepmaskrasterdata.cpp \
  $$PWD/qcepoverflowrasterdata.cpp \
  $$PWD/qcepimageplotwidgetsettings.cpp \
  $$PWD/qcepimageplotwidget.cpp \
  $$PWD/qcepimageplotwidgetdialog.cpp \
  $$PWD/qcepimageplot.cpp \
  $$PWD/qcepimageplotsettings.cpp \
  $$PWD/qcepaddpointcommand.cpp \
  $$PWD/qcepadjustdistancecommand.cpp \
  $$PWD/qcepadjustenergycommand.cpp \
  $$PWD/qcepadjustfitcommand.cpp \
  $$PWD/qcephistogramcommand.cpp \
  $$PWD/qcephistogramselector.cpp \
  $$PWD/qcepmaskstack.cpp \
  $$PWD/qcepmaskstackmodel.cpp \
  $$PWD/qcepmaskcirclescommand.cpp \
  $$PWD/qcepimageplotmeasurer.cpp \
  $$PWD/qcepmaskpicker.cpp \
  $$PWD/qcepmaskcommandbutton.cpp \
  $$PWD/qcepmaskpolygonscommand.cpp \
  $$PWD/qcepmeasurecommand.cpp \
  $$PWD/qceppowderpointpicker.cpp \
  $$PWD/qceppowderpointscommand.cpp \
  $$PWD/qcepdetectorgeometry.cpp \
  $$PWD/qcepcenterfinder.cpp \
  $$PWD/qcepcenterfinderpicker.cpp \
  $$PWD/qcepsetcentercommand.cpp \
  $$PWD/qcepplotslicer.cpp \
  $$PWD/qcepslicecommand.cpp \
  $$PWD/qcepcolormapsubmenucommand.cpp \
  $$PWD/qcepcontextseparatorcommand.cpp \
  $$PWD/qcepdelallpointscommand.cpp \
  $$PWD/qcepdelpointcommand.cpp \
  $$PWD/qcepdelringcommand.cpp \
  $$PWD/qcepdisableringcommand.cpp \
  $$PWD/qcepenableringcommand.cpp \
  $$PWD/qcepfitcirclecommand.cpp \
  $$PWD/qcepfitellipsecommand.cpp \
  $$PWD/qcepfitellipsescommand.cpp \
  $$PWD/qcepfitpeakcommand.cpp \
  $$PWD/qcepfitringpointcommand.cpp \
  $$PWD/qcepmissingringcommand.cpp \
  $$PWD/qcepnormalizeringscommand.cpp \
  $$PWD/qcepscalingsubmenucommand.cpp \
  $$PWD/qceptraceringcommand.cpp \
  $$PWD/qcepzappixelcommand.cpp \
  $$PWD/qcepfitter.cpp \
  $$PWD/qcepfitterpeakorring.cpp \
  $$PWD/qcepfitterpeakpoint.cpp \
  $$PWD/qcepfitterringpoint.cpp \
  $$PWD/qcepfitterringcircle.cpp \
  $$PWD/qcepfitterringellipse.cpp \
  $$PWD/qcepfittedrings.cpp \
  $$PWD/qcepcalibrantlibrarymodel.cpp \
  $$PWD/qcepcalibrantlibrary.cpp \
  $$PWD/qcepcalibrant.cpp \
  $$PWD/qcepcalibrantdspacingsmodel.cpp \
  $$PWD/qcepcalibrantdspacings.cpp \
  $$PWD/qcepcalibrantdspacing.cpp \
  $$PWD/qcepcentermarker.cpp \
  $$PWD/qceppowderpoint.cpp \
  $$PWD/qceppowderpointproperty.cpp \
  $$PWD/qceproimodel.cpp \
  $$PWD/qceproi.cpp \
  $$PWD/qceproicache.cpp \
  $$PWD/qceproicalculator.cpp \
  $$PWD/qceproicenteredshape.cpp \
  $$PWD/qceproishape.cpp \
  $$PWD/qceproipicker.cpp \
  $$PWD/qceproiellipse.cpp \
  $$PWD/qceproirectangle.cpp \
  $$PWD/qceproieditordialog.cpp \
  $$PWD/qceproipolygon.cpp \
  $$PWD/qceproioverlay.cpp \
  $$PWD/qceproirasterdata.cpp \
  $$PWD/qceproitypedelegate.cpp \
  $$PWD/qceproivector.cpp \
  $$PWD/qceppolygonpointsmodel.cpp \
  $$PWD/qceppowderringsmodel.cpp \
  $$PWD/qceppowderoverlay.cpp \
  $$PWD/triangulate.c \
  $$PWD/qcepplanefitter.cpp \
    $$PWD/qcepstartupwindowsettings.cpp \
    $$PWD/qcepstartupwindow.cpp \
    $$PWD/qcepoutputfileformatter.cpp \
    $$PWD/qcepoutputfileformatterhdf.cpp \
    $$PWD/qcepoutputfileformattersettings.cpp \
    $$PWD/qcepoutputfileformattertiff.cpp \
    $$PWD/qcepoutputfileformattertiff-bzip2.cpp \
    $$PWD/qcepoutputfileformattertiff-zip.cpp \
    $$PWD/qcepoutputfileformattertiff-gzip.cpp

contains (DEFINES, HAVE_DATAVIS) {
 SOURCES += \
  $$PWD/qcepdataobjectsurfaceplotwindow.cpp \
  $$PWD/qcepdataobjectsurfaceplotwidget.cpp
}

contains (DEFINES, HAVE_QWT) {
 SOURCES += \
  $$PWD/qcepdatasetbrowserview.cpp \
  $$PWD/qcepdataobjectgraphcontroller.cpp \
  $$PWD/qcepdataobjectgraphwindow.cpp \
  $$PWD/qcepscatterplotgraphcontrols.cpp \
  $$PWD/qcepscatterplotgraphcontroller.cpp \
  $$PWD/qcepimagedatagraphcontroller.cpp \
  $$PWD/qcepimagedatagraphcontrols.cpp \
  $$PWD/qcepimageslicegraphcontroller.cpp \
  $$PWD/qcepimageslicegraphcontrols.cpp \
  $$PWD/qcepimagehistogramgraphcontroller.cpp \
  $$PWD/qcepimagehistogramgraphcontrols.cpp \
  $$PWD/qcepgraphcontrolswidget.cpp \
  $$PWD/qcepplot.cpp \
  $$PWD/qcepplotsettings.cpp \
  $$PWD/qcepplotmeasurer.cpp \
  $$PWD/qcepplotzoomer.cpp \
  $$PWD/qwt_plot_piecewise_curve.cpp
}


HEADERS += \
  $$PWD/qceplib_global.h \
  $$PWD/qcepmacros.h \
  $$PWD/qcepsharedpointer.h \
  $$PWD/qcepdebug.h \
  $$PWD/qcepproperty.h \
  $$PWD/qcepproperty-ptr.h \
  $$PWD/qcepvector3dproperty.h \
  $$PWD/qcepmatrix3x3property.h \
  $$PWD/qcepplotmarker.h \
  $$PWD/qcepplotmarkerlist.h \
  $$PWD/qcepplotmarkerlistproperty.h \
  $$PWD/qcepmutexlocker.h \
  $$PWD/qcepdocumentationdictionary.h \
  $$PWD/qcepimagedata.h \
  $$PWD/qcepimagedata-ptr.h \
  $$PWD/qcepimagequeue-ptr.h \
  $$PWD/qcepimagequeue.h \
  $$PWD/qcepimagedataformatfactory.h \
  $$PWD/qcepimagedataformatfactory-ptr.h \
  $$PWD/qcepimagedataformat.h \
  $$PWD/qcepobjectnamer.h \
  $$PWD/qcepexperiment.h \
  $$PWD/qcepexperiment-ptr.h \
  $$PWD/qceppropertyvalue.h \
  $$PWD/qcepmatrix3x3.h \
  $$PWD/qcepvector3d.h \
  $$PWD/qcepobject.h \
  $$PWD/qcepobject-ptr.h \
  $$PWD/qcepdataobject.h \
  $$PWD/qcepdataobject-ptr.h \
  $$PWD/qcepdatagroup.h \
  $$PWD/qcepdatagroup-ptr.h \
  $$PWD/qcepdataarray.h \
  $$PWD/qcepdataarray-ptr.h \
  $$PWD/qcepdatacolumn.h \
  $$PWD/qcepdatacolumn-ptr.h \
  $$PWD/qcepdatacolumnscan.h \
  $$PWD/qcepdatacolumnscan-ptr.h \
  $$PWD/qcepdataset.h \
  $$PWD/qcepdataset-ptr.h \
  $$PWD/qcepdatasetmodel.h \
  $$PWD/qcepdatasetmodel-ptr.h \
  $$PWD/qcepdataarrayspreadsheetmodel.h \
  $$PWD/qcepdatacolumnspreadsheetmodel.h \
  $$PWD/qcepdatacolumnscanspreadsheetmodel.h \
  $$PWD/qcepdatagroupspreadsheetmodel.h \
  $$PWD/qcepintegrateddataspreadsheetmodel.h \
  $$PWD/qcepdataobjectpropertiesmodel.h \
  $$PWD/qcepspreadsheetmodel.h \
  $$PWD/qceppropertiesmodel.h \
  $$PWD/qcepmaskdata.h \
  $$PWD/qcepmaskdata-ptr.h \
  $$PWD/qcepallocator.h \
  $$PWD/qcepallocator-ptr.h \
  $$PWD/qcepintegrateddata.h \
  $$PWD/qcepintegrateddata-ptr.h \
  $$PWD/qcepapplication.h \
  $$PWD/qcepapplication-ptr.h \
  $$PWD/qcepthread.h \
  $$PWD/qcepintegrateddataqueue.h \
  $$PWD/qcepimagedataspreadsheetmodel.h \
  $$PWD/qcepnewdatagroupdialog.h \
  $$PWD/qcepnewdatacolumndialog.h \
  $$PWD/qcepnewcolumnscandialog.h \
  $$PWD/qcepnewimagedialog.h \
  $$PWD/qcepnewdataarraydialog.h \
  $$PWD/qcepdataobjectpropertieswindow.h \
  $$PWD/qcepdataobjectspreadsheetwindow.h \
  $$PWD/qcepscriptengine.h \
  $$PWD/qcepscriptengine-ptr.h \
  $$PWD/qcepmainwindow.h \
  $$PWD/qcepmainwindow-ptr.h \
  $$PWD/qcepscatterplotgraphmodel.h \
  $$PWD/qcepscatterplotgraphmodel-ptr.h \
  $$PWD/qcepdatasetselectiondialog.h \
  $$PWD/qcepdataimportcommand.h \
  $$PWD/qcepdataexportcommand.h \
  $$PWD/qcepdataimportdialog.h \
  $$PWD/qcepdataexportdialog.h \
  $$PWD/qcepdataimportparameters.h \
  $$PWD/qcepdataexportparameters.h \
  $$PWD/qcepdataexportparameters-ptr.h \
  $$PWD/qcepdataexportcommand-ptr.h \
  $$PWD/qcepdataimportparameters-ptr.h \
  $$PWD/qcepdataimportcommand-ptr.h \
  $$PWD/qcepfileimporter.h \
  $$PWD/qcepfileimportertext.h \
  $$PWD/qcepfileimportertiff.h \
  $$PWD/qcepfileimporterhdf.h \
  $$PWD/qcepfileimporter-ptr.h \
  $$PWD/qcepfileimportermultiple.h \
  $$PWD/qcepfileformatter.h \
  $$PWD/qcepfileformatter-ptr.h \
  $$PWD/qcepfileformattertext.h \
  $$PWD/qcepfileformatterhdf.h \
  $$PWD/qcepfileformatternexus.h \
  $$PWD/qcepsetrangeofimagedialog.h \
  $$PWD/qcepsetdatavaluerangedialog.h \
  $$PWD/qcepfixupgainmapdialog.h \
  $$PWD/qcepfixupgainmapcommand.h \
  $$PWD/qcepsetdatavaluerangecommand.h \
  $$PWD/qcepsetrangeofimagecommand.h \
  $$PWD/qcepsetrangeofimagecommand-ptr.h \
  $$PWD/qcepsetdatavaluerangecommand-ptr.h \
  $$PWD/qcepfixupgainmapcommand-ptr.h \
  $$PWD/qcepfixupdetectorpanelgains.h \
  $$PWD/qcepscandetectorpanelgains.h \
  $$PWD/qcepmainwindowsettings.h \
  $$PWD/qcepmainwindowsettings-ptr.h \
  $$PWD/qcepobjecttreemodel.h \
  $$PWD/qcepobjecttreewindow.h \
  $$PWD/qcepobjectpropertiesmodel.h \
  $$PWD/qthread-ptr.h \
  $$PWD/qnewthread.h \
  $$PWD/qnewthread-ptr.h \
  $$PWD/qcepthread-ptr.h \
  $$PWD/qapplication-ptr.h \
  $$PWD/qceprunguard.h \
  $$PWD/qcepdataobjectpropertiesmodel-ptr.h \
  $$PWD/qcepplotwidget.h \
  $$PWD/qcepplotwidget-ptr.h \
  $$PWD/qcepplotwidgetsettings.h \
  $$PWD/qcepplotwidgetsettings-ptr.h \
  $$PWD/qcepplotwidgetdialog.h \
  $$PWD/qcepplotwidgetdialog-ptr.h \
  $$PWD/qcepplotcommand.h \
  $$PWD/qcepplotcommand-ptr.h \
  $$PWD/qcepplotoverlay.h \
  $$PWD/qcepplotoverlay-ptr.h \
  $$PWD/qcepcolormaplibrary.h \
  $$PWD/qcepcolormaplibrary-ptr.h \
  $$PWD/qcepcolormap.h \
  $$PWD/qcepcolormap-ptr.h \
  $$PWD/qcepmaskcolormap.h \
  $$PWD/qcepplotcontextmenucommand.h \
  $$PWD/qcepmaskcolormap-ptr.h \
  $$PWD/qcepautoscalecommand.h \
  $$PWD/qcepzoomincommand.h \
  $$PWD/qcepplotbuttoncommand.h \
  $$PWD/qcepzoomoutcommand.h \
  $$PWD/qcepzoomallcommand.h \
  $$PWD/qcepprintplotbutton.h \
  $$PWD/qcepplotpreferencesbutton.h \
  $$PWD/qcepprintplotcommand.h \
  $$PWD/qcepplotpreferencescommand.h \
  $$PWD/qcepaxissubmenucommand.h \
  $$PWD/qceprasterdata-ptr.h \
  $$PWD/qceprasterdata.h \
  $$PWD/qcepmaskrasterdata.h \
  $$PWD/qcepoverflowrasterdata.h \
  $$PWD/qcepimageplotwidgetsettings-ptr.h \
  $$PWD/qcepimageplotwidget-ptr.h \
  $$PWD/qcepimageplotwidgetsettings.h \
  $$PWD/qcepimageplotwidget.h \
  $$PWD/qcepoverflowrasterdata-ptr.h \
  $$PWD/qcepimageplotwidgetdialog.h \
  $$PWD/qcepimageplotwidgetdialog-ptr.h \
  $$PWD/qcepimageplot.h \
  $$PWD/qcepimageplotsettings-ptr.h \
  $$PWD/qcepimageplotsettings.h \
  $$PWD/qcepmaskrasterdata-ptr.h \
  $$PWD/qcepimageplot-ptr.h \
  $$PWD/qcepaddpointcommand.h \
  $$PWD/qcepadjustdistancecommand.h \
  $$PWD/qcepadjustenergycommand.h \
  $$PWD/qcepadjustfitcommand.h \
  $$PWD/qcephistogramcommand.h \
  $$PWD/qcephistogramselector.h \
  $$PWD/qcephistogramselector-ptr.h \
  $$PWD/qcepmaskstack.h \
  $$PWD/qcepmaskstack-ptr.h \
  $$PWD/qcepmaskstackmodel-ptr.h \
  $$PWD/qcepmaskstackmodel.h \
  $$PWD/qcepmaskcirclescommand.h \
  $$PWD/qcepimageplotmeasurer.h \
  $$PWD/qcepmaskpicker.h \
  $$PWD/qcepmaskpicker-ptr.h \
  $$PWD/qcepmaskcommandbutton.h \
  $$PWD/qcepmaskpolygonscommand.h \
  $$PWD/qcepimageplotmeasurer-ptr.h \
  $$PWD/qcepmeasurecommand.h \
  $$PWD/qceppowderpointpicker-ptr.h \
  $$PWD/qceppowderpointpicker.h \
  $$PWD/qceppowderpointscommand.h \
  $$PWD/qcepdetectorgeometry.h \
  $$PWD/qcepdetectorgeometry-ptr.h \
  $$PWD/qcepcenterfinder-ptr.h \
  $$PWD/qcepcenterfinder.h \
  $$PWD/qcepcenterfinderpicker.h \
  $$PWD/qcepsetcentercommand.h \
  $$PWD/qcepplotslicer.h \
  $$PWD/qcepplotslicer-ptr.h \
  $$PWD/qcepslicecommand.h \
  $$PWD/qcepcolormapsubmenucommand.h \
  $$PWD/qcepcontextseparatorcommand.h \
  $$PWD/qcepdelallpointscommand.h \
  $$PWD/qcepdelpointcommand.h \
  $$PWD/qcepdelringcommand.h \
  $$PWD/qcepdisableringcommand.h \
  $$PWD/qcepenableringcommand.h \
  $$PWD/qcepfitcirclecommand.h \
  $$PWD/qcepfitellipsecommand.h \
  $$PWD/qcepfitellipsescommand.h \
  $$PWD/qcepfitpeakcommand.h \
  $$PWD/qcepfitringpointcommand.h \
  $$PWD/qcepmissingringcommand.h \
  $$PWD/qcepnormalizeringscommand.h \
  $$PWD/qcepscalingsubmenucommand.h \
  $$PWD/qceptraceringcommand.h \
  $$PWD/qcepzappixelcommand.h \
  $$PWD/qcepfitter.h \
  $$PWD/qcepfitterpeakorring.h \
  $$PWD/qcepfitterpeakpoint.h \
  $$PWD/qcepfitterringpoint.h \
  $$PWD/qcepfitterringcircle.h \
  $$PWD/qcepfitterringellipse.h \
  $$PWD/qcepfittedrings.h \
  $$PWD/qcepfittedrings-ptr.h \
  $$PWD/qcepcenterfinderpicker-ptr.h \
  $$PWD/qcepcalibrantlibrary-ptr.h \
  $$PWD/qcepcalibrantlibrarymodel-ptr.h \
  $$PWD/qcepcalibrantlibrarymodel.h \
  $$PWD/qcepcalibrantlibrary.h \
  $$PWD/qcepcalibrant-ptr.h \
  $$PWD/qcepcalibrant.h \
  $$PWD/qcepcalibrantdspacingsmodel-ptr.h \
  $$PWD/qcepcalibrantdspacingsmodel.h \
  $$PWD/qcepcalibrantdspacings-ptr.h \
  $$PWD/qcepcalibrantdspacings.h \
  $$PWD/qcepcalibrantdspacing.h \
  $$PWD/qcepcalibrantdspacing-ptr.h \
  $$PWD/qcepcentermarker.h \
  $$PWD/qceppowderpoint.h \
  $$PWD/qceppowderpointproperty.h \
  $$PWD/qceproimodel-ptr.h \
  $$PWD/qceproimodel.h \
  $$PWD/qceproi-ptr.h \
  $$PWD/qceproi.h \
  $$PWD/qceproicache-ptr.h \
  $$PWD/qceproicache.h \
  $$PWD/qceproicalculator-ptr.h \
  $$PWD/qceproicalculator.h \
  $$PWD/qceproicenteredshape-ptr.h \
  $$PWD/qceproicenteredshape.h \
  $$PWD/qceproishape-ptr.h \
  $$PWD/qceproishape.h \
  $$PWD/qceproipicker-ptr.h \
  $$PWD/qceproipicker.h \
  $$PWD/qceproiellipse.h \
  $$PWD/qceproirectangle.h \
  $$PWD/qceproieditordialog.h \
  $$PWD/qceproipolygon-ptr.h \
  $$PWD/qceproipolygon.h \
  $$PWD/qceproioverlay-ptr.h \
  $$PWD/qceproioverlay.h \
  $$PWD/qceproirasterdata.h \
  $$PWD/qceproitypedelegate.h \
  $$PWD/qceproivector-ptr.h \
  $$PWD/qceproivector.h \
  $$PWD/qceppolygonpointsmodel.h \
  $$PWD/qceppowderringsmodel-ptr.h \
  $$PWD/qceppowderringsmodel.h \
  $$PWD/qceppowderoverlay-ptr.h \
  $$PWD/qceppowderoverlay.h \
  $$PWD/triangulate.h \
  $$PWD/qcepplanefitter.h \
  $$PWD/qcepstartupwindowsettings.h \
  $$PWD/qcepstartupwindowsettings-ptr.h \
  $$PWD/qcepstartupwindow-ptr.h \
  $$PWD/qcepstartupwindow.h \
  $$PWD/qcommandlineparser-ptr.h \
  $$PWD/qsettings-ptr.h \
  $$PWD/qcommandlineoption-ptr.h \
    $$PWD/qcepoutputfileformatter.h \
    $$PWD/qcepoutputfileformatterhdf.h \
    $$PWD/qcepoutputfileformattersettings.h \
    $$PWD/qcepoutputfileformattertiff.h \
    $$PWD/qcepoutputfileformattersettings-ptr.h \
    $$PWD/qcepoutputfileformatter-ptr.h \
    $$PWD/qcepspreadsheetmodel-ptr.h

contains (DEFINES, HAVE_DATAVIS) {
 HEADERS += \
  $$PWD/qcepdataobjectsurfaceplotwindow.h \
  $$PWD/qcepdataobjectsurfaceplotwidget.h
}

contains (DEFINES, HAVE_QWT) {
 HEADERS += \
  $$PWD/qcepdatasetbrowserview.h \
  $$PWD/qcepdataobjectgraphcontroller-ptr.h \
  $$PWD/qcepdataobjectgraphcontroller.h \
  $$PWD/qcepdataobjectgraphwindow.h \
  $$PWD/qcepscatterplotgraphcontrols.h \
  $$PWD/qcepscatterplotgraphcontroller.h \
  $$PWD/qcepimagedatagraphcontroller.h \
  $$PWD/qcepimagedatagraphcontrols.h \
  $$PWD/qcepimagehistogramgraphcontroller.h \
  $$PWD/qcepimagehistogramgraphcontrols.h \
  $$PWD/qcepimageslicegraphcontroller.h \
  $$PWD/qcepimageslicegraphcontrols.h \
  $$PWD/qcepgraphcontrolswidget.h \
  $$PWD/qcepplot-ptr.h \
  $$PWD/qcepplot.h \
  $$PWD/qcepplotsettings-ptr.h \
  $$PWD/qcepplotsettings.h \
  $$PWD/qcepplotmeasurer-ptr.h \
  $$PWD/qcepplotmeasurer.h \
  $$PWD/qcepplotzoomer.h \
  $$PWD/qwt_plot_piecewise_curve-ptr.h \
  $$PWD/qwt_plot_piecewise_curve.h \
  $$PWD/qwt_plot_spectrogram-ptr.h \
  $$PWD/qwt_plot_picker-ptr.h
}

FORMS += \
  $$PWD/qcepnewdatagroupdialog.ui \
  $$PWD/qcepnewdatacolumndialog.ui \
  $$PWD/qcepnewcolumnscandialog.ui \
  $$PWD/qcepnewimagedialog.ui \
  $$PWD/qcepnewdataarraydialog.ui \
  $$PWD/qcepdataobjectpropertieswindow.ui \
  $$PWD/qcepdataobjectspreadsheetwindow.ui \
  $$PWD/qcepdatasetselectiondialog.ui \
  $$PWD/qcepdataimportdialog.ui \
  $$PWD/qcepdataexportdialog.ui \
  $$PWD/qcepsetrangeofimagedialog.ui \
  $$PWD/qcepsetdatavaluerangedialog.ui \
  $$PWD/qcepfixupgainmapdialog.ui \
  $$PWD/qcepobjecttreewindow.ui \
  $$PWD/qcepplotwidget.ui \
  $$PWD/qcepplotwidgetdialog.ui \
  $$PWD/qcepimageplotwidgetdialog.ui \
  $$PWD/qceproieditordialog.ui \
    $$PWD/qcepstartupwindow.ui

contains(DEFINES, HAVE_QWT) {
 FORMS += \
  $$PWD/qcepdataobjectgraphwindow.ui \
  $$PWD/qcepscatterplotgraphcontrols.ui \
  $$PWD/qcepimagedatagraphcontrols.ui \
  $$PWD/qcepimagehistogramgraphcontrols.ui \
  $$PWD/qcepimageslicegraphcontrols.ui
}

contains(DEFINES, HAVE_DATAVIS) {
 FORMS += \
  $$PWD/qcepdataobjectsurfaceplotwindow.ui \
  $$PWD/qcepdataobjectsurfaceplotwidget.ui
}

RESOURCES += \
  $$PWD/qcepresources.qrc
