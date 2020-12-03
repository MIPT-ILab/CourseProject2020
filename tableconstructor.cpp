#include "tableconstructor.h"

QMap<int, Qt::GlobalColor> TableConstructor::colors = { {0, Qt::darkRed},
                                                        {1, Qt::red},
                                                        {2, Qt::yellow},
                                                        {3, Qt::darkGreen},
                                                        {4, Qt::green} };

TableConstructor::TableConstructor(const QJsonArray &records, QWidget* tab)
{
    this->tab = tab;

    layout = new QHBoxLayout(tab);
    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);

    rows = 0;
    cols = 0;

    for (const auto& record : records){
        auto map = record.toVariant().toMap();
        if (map["type"] == "Record")
            rows++;
    }

    for (auto record = records.end(); record != records.begin(); record--) {
        auto map = record->toVariant().toMap();
        if (map["type"] == "Event") {
            cols = map["cycle"].toInt() + 1;
            break;
        }
    }

    tableView = new MyTableWidget(rows, cols, tab);

    for (int i = 0; i < cols; i++)
        tableView->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i)));

    layout->addWidget(tableView);

    construct(records);

    styling();
}

TableConstructor::TableConstructor() {

}

TableConstructor::~TableConstructor(){
    delete layout;
    delete tab;
}

void TableConstructor::construct(const QJsonArray &records) {
    for (auto record : records){
        auto map = record.toVariant().toMap();
        if (map["type"] == "Event") {
            int col = map["cycle"].toInt();
            int stage = map["stage"].toInt();
            int row = map["id"].toInt();
            tableView->setItem(row, col, new QTableWidgetItem(stages[stage]));
            tableView->item(row, col)->setBackground(colors[stage]);
         }
         else if (map["type"] == "Record")
             tableView->setVerticalHeaderItem(map["id"].toInt(), new QTableWidgetItem("disassembly: " + map["disassembly"].toString()));
         else if (map["type"] == "Stage") {
             stages.insert(map["id"].toInt(), map["description"].toString().at(0));
         }
     }
}

void TableConstructor::styling(){
    tableView->normalize();
}

