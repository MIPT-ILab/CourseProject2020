#include "mytablewidget.h"

MyTableWidget::MyTableWidget(QWidget *parent) : QTableWidget (parent) {
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MyTableWidget::MyTableWidget(int rows, int cols, QWidget *parent) : QTableWidget (rows, cols, parent) {
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MyTableWidget::wheelEvent(QWheelEvent *event) {
    focusCol = horizontalScrollBar()->value() + horizontalScrollBar()->pageStep() / 2;
    focusRow = verticalScrollBar()->value() + verticalScrollBar()->pageStep() / 2;
    QFont font = horizontalHeader()->font();
    int ceilSize = verticalHeader()->defaultSectionSize();
    int fontSize = font.pointSize();
    if (event->delta() > 0 && fontSize < 9) {
        font.setPointSize(fontSize + 1);
        setFont(font);
        horizontalHeader()->setDefaultSectionSize(ceilSize + 4);
        verticalHeader()->setDefaultSectionSize(ceilSize + 4);
    } else if (event->delta() <= 0 && fontSize > 1) {
        font.setPointSize(fontSize - 1);
        setFont(font);
        horizontalHeader()->setDefaultSectionSize(ceilSize - 4);
        verticalHeader()->setDefaultSectionSize(ceilSize - 4);
    }

    QCoreApplication::postEvent(this, new QEvent(QEvent::Type::User));
}

bool MyTableWidget::event(QEvent *event) {
    if (event->type() == QEvent::Type::User){
        int newHorValue = focusCol - horizontalScrollBar()->pageStep() / 2;
        int newVerValue = focusRow - verticalScrollBar()->pageStep() / 2;
        horizontalScrollBar()->setValue(newHorValue);
        verticalScrollBar()->setValue(newVerValue);
        return true;
    }
    return QTableWidget::event(event);
}

void MyTableWidget::mouseMoveEvent(QMouseEvent * event) {
    int currentRow = rowAt(event->y());
    int currentCol = columnAt(event->x());

    int currentPos = horizontalScrollBar()->value();
    horizontalScrollBar()->setValue(currentPos - currentCol + prevCol);

    currentPos = verticalScrollBar()->value();
    verticalScrollBar()->setValue(currentPos - currentRow + prevRow);
}

void MyTableWidget::mousePressEvent(QMouseEvent * event) {
    prevCol = columnAt(event->x());
    prevRow = rowAt(event->y());
}

void MyTableWidget::normalize(){
    QFont font = horizontalHeader()->font();
    font.setPointSize(9);
    setFont(font);
    horizontalHeader()->setDefaultSectionSize(47);
    verticalHeader()->setDefaultSectionSize(47);
}
