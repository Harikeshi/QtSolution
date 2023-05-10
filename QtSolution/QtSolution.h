#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtSolution.h"

class QtSolution : public QMainWindow
{
    Q_OBJECT

public:
    QtSolution(QWidget *parent = nullptr);
    ~QtSolution();

private:
    Ui::QtSolutionClass ui;
};
