#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H
#include <QObject>
#include <QTableWidget>
#include <QWheelEvent>
#include <QHeaderView>
#include <QFont>
#include <QScrollBar>
#include <QCoreApplication>

class MyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    MyTableWidget(QWidget *parent);
    MyTableWidget(int rows, int cols, QWidget *parent);
    void normalize();
private:
    int prevCol;
    int prevRow;
    int focusCol;
    int focusRow;

signals:
protected:
    void wheelEvent(QWheelEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    bool event(QEvent*) override;
};

#endif // MYTABLEWIDGET_H
