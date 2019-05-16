#include "QskFunctions.h"

#include <qguiapplication.h>
#include <qmath.h>
#include <qscreen.h>

template< class Rect, class Value >
static inline Rect qskAlignedRect( const Rect& outerRect,
    Value width, Value height, Qt::Alignment alignment )
{
    Value x = outerRect.x();
    Value y = outerRect.y();

    switch ( alignment & Qt::AlignHorizontal_Mask )
    {
        case Qt::AlignHCenter:
            x += ( outerRect.width() - width ) / 2;
            break;

        case Qt::AlignRight:
            x += outerRect.width() - width;
            break;

        default:
            break;
    }

    switch ( alignment & Qt::AlignVertical_Mask )
    {
        case Qt::AlignVCenter:
            y += ( outerRect.height() - height ) / 2;
            break;

        case Qt::AlignBottom:
            y += outerRect.height() - height;
            break;

        default:
            break;
    }

    return Rect( x, y, width, height );
}

QRect qskAlignedRect( const QRect& outerRect,
    int width, int height, Qt::Alignment alignment )
{
    return qskAlignedRect< QRect, int >( outerRect, width, height, alignment );
}

QRectF qskAlignedRectF( const QRectF& outerRect,
    qreal width, qreal height, Qt::Alignment alignment )
{
    return qskAlignedRect< QRectF, qreal >( outerRect, width, height, alignment );
}

QRect qskInnerRect( const QRectF& rect )
{
    const int left = qCeil( rect.left() );
    const int top = qCeil( rect.top() );
    const int right = qFloor( rect.right() );
    const int bottom = qFloor( rect.bottom() );

    return QRect( left, top, right - left, bottom - top );
}

QRectF qskInnerRectF( const QRectF& rect )
{
    const qreal left = qCeil( rect.left() );
    const qreal top = qCeil( rect.top() );
    const qreal right = qFloor( rect.right() );
    const qreal bottom = qFloor( rect.bottom() );

    return QRectF( left, top, right - left, bottom - top );
}

QRectF qskValidOrEmptyInnerRect( const QRectF& rect, const QMarginsF& margins )
{
    qreal x, y, h, w;

    if ( rect.width() > 0.0 )
    {
        const qreal marginsWidth = margins.left() + margins.right();

        if ( marginsWidth > rect.width() )
        {
            x = rect.x() + rect.width() * ( margins.left() / marginsWidth );
            w = 0.0;
        }
        else
        {
            x = rect.x() + margins.left();
            w = rect.width() - marginsWidth;
        }
    }
    else
    {
        x = rect.x();
        w = 0.0;
    }

    if ( rect.height() > 0.0 )
    {
        const qreal marginsHeight = margins.top() + margins.bottom();
        if ( marginsHeight > rect.height() )
        {
            y = rect.y() + rect.height() * ( margins.top() / marginsHeight );
            h = 0.0;
        }
        else
        {
            y = rect.y() + margins.top();
            h = rect.height() - marginsHeight;
        }
    }
    else
    {
        y = rect.y();
        h = 0.0;
    }

    return QRectF( x, y, w, h );
}

qreal qskDpiScaled( qreal value )
{
    static qreal factor = 0.0;

    if ( factor <= 0.0 )
    {
        if ( const QScreen* screen = QGuiApplication::primaryScreen() )
            factor = screen->logicalDotsPerInchX();
        else
            factor = 100.0;

        factor /= 96.0;
    }

    return value * factor;
}
