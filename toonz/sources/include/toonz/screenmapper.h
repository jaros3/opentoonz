#pragma once

#ifndef SCREEN_MAPPER_INCLUDED
#define SCREEN_MAPPER_INCLUDED

#include "orientation.h"
#include "sublayers.h"
#include "columnfan.h"

//! Class responsible for mapping logical (row, col) to screen XY and back
//! Gathers and hides all objects required to do so
//! All screen mapping requests should go through this,
//! so that when we want to change something it's done in single place.

//! Each XsheetViewer has a single instance of ScreenMapper.
//! ScreenMapper has internal state that lets XsheetViewer be customized
//! independently from other windows.

class XsheetViewer;

class ScreenMapper final {
  XsheetViewer *m_viewer;

  const Orientation *m_orientation;
  ColumnFanGeometry *m_columnFan;
  SubLayers *m_subLayers;
  // place for zoom-in variable here

public:
  ScreenMapper(XsheetViewer *viewer);
  ~ScreenMapper();

  XsheetViewer *viewer() const { return m_viewer; }
  TXsheet *xsheet() const;
  int getCurrentFrame() const;

  const Orientation *orientation() const { return m_orientation; }
  ColumnFanGeometry *columnFan() const { return m_columnFan; }
  SubLayers *subLayers() const { return m_subLayers; }

  // orientation

  void flipOrientation();

  CellPosition xyToPosition(const QPoint &point) const;
  QPoint positionToXY(const CellPosition &pos) const;

  int columnToLayerAxis(int layer) const;
  int rowToFrameAxis(int frame) const;

  NumberRange rowsToFrameAxis(const NumberRange &frames) const;
  NumberRange colsToLayerAxis(const NumberRange &layers) const;

  QPoint frameLayerToXY(int frameAxis, int layerAxis) const;

  QRect rect(PredefinedRect which) const { return orientation()->rect(which); }
  QLine line(PredefinedLine which) const { return orientation()->line(which); }
  int dimension(PredefinedDimension which) const { return orientation()->dimension(which); }
  QPainterPath path(PredefinedPath which) const { return orientation()->path(which); }
  QPoint point(PredefinedPoint which) const { return orientation()->point(which); }
  NumberRange range(PredefinedRange which) const { return orientation()->range(which); }

  // column fan

  void onColumnFanFoldedUnfolded(const ColumnFan *origin) const;
  void updateColumnFan() const;
};

#endif