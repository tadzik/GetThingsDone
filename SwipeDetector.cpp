#include "SwipeDetector.hpp"
#include <cmath>
#include <QDebug>

void SwipeDetector::mousePressEvent(QMouseEvent *e)
{
    from_ = e->globalPos();
}

void SwipeDetector::mouseReleaseEvent(QMouseEvent *e)
{
    QPoint p2 = e->globalPos();
    // assume horizontal swipe
    qDebug() << "possible horizontal swipe";

    int y = p2.y() - from_.y();
    int x = p2.x() - from_.x();

    int len = qMax(abs(x), abs(y));
    qDebug() << "threshold is " << threshold_ << "move is" << abs(len);
    if (len < threshold_) {
        qDebug() << "swipe too short (" << len << "), threshold being"
                 << threshold_ << ", ignoring";
        return;
    }

    int at = abs(2 * atan((double)x/y));
    if (at >= 2) {
        if (x > 0) {
            qDebug() << "swipe RIGHT";
            emit(horizontalSwipe(1, from_, p2));
        } else {
            qDebug() << "swipe LEFT";
            emit(horizontalSwipe(-1, from_, p2));
        }
    } else if (at <= 1) {
        if (y > 0) {
            qDebug("swipe DOWN");
            emit(verticalSwipe(-1, from_, p2));
        } else {
            qDebug("swipe UP");
            emit(verticalSwipe(1, from_, p2));
        }
    }
}
