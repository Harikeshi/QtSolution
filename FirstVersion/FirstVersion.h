#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FirstVersion.h"

class FirstVersion : public QMainWindow
{
    Q_OBJECT

public:
    FirstVersion(QWidget *parent = nullptr);
    ~FirstVersion();

private:
    Ui::FirstVersionClass ui;
};
