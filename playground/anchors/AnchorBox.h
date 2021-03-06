/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef ANCHOR_BOX_H
#define ANCHOR_BOX_H

#include "QskControl.h"

class AnchorBox : public QskControl
{
    Q_OBJECT

    using Inherited = QskControl;

  public:
    AnchorBox( QQuickItem* parent = nullptr );
    ~AnchorBox() override;

    void addAnchor( QQuickItem*, Qt::AnchorPoint, Qt::AnchorPoint );
    void addAnchor( QQuickItem*, Qt::AnchorPoint, QQuickItem*, Qt::AnchorPoint );

    QSizeF boxHint( Qt::SizeHint );

  protected:
    void geometryChangeEvent( QskGeometryChangeEvent* ) override;
    void updateLayout() override;

  private:
    void setItemGeometries( const QRectF& );

    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

#endif

