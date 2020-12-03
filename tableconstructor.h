#ifndef TABLECONSTRUCTOR_H
#define TABLECONSTRUCTOR_H

#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidget>
#include <QLayout>
#include <QHeaderView>
#include "mytablewidget.h"
#include "mygraphicsview.h"

class TableConstructor
{
public:
    TableConstructor(const QJsonArray&, QWidget*);
    TableConstructor();
    ~TableConstructor();
private:
    void construct(const QJsonArray&);
    void styling();
    MyTableWidget *tableView;
    QHBoxLayout *layout;
    QWidget* tab;
    int rows;
    int cols;
    QMap<int, QString> stages;
    static QMap<int, Qt::GlobalColor> colors;
};

#endif // TABLECONSTRUCTOR_H
