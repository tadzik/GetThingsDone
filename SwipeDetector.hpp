#ifndef _SWIPEDETECTOR_HPP_
#define _SWIPEDETECTOR_HPP_
#include <QMouseEvent>
#include <QPoint>

class SwipeDetector : public QObject {
    Q_OBJECT;

private:
    QPoint from_;
    int threshold_;

public:
    SwipeDetector(int threshold = 0) : threshold_(threshold) {}
    void setThreshold(int t) { threshold_ = t; }
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void horizontalSwipe(int, const QPoint&, const QPoint&);
    void verticalSwipe(int, const QPoint&, const QPoint&);
};

#endif
