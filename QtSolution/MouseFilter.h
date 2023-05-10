#pragma once
#include <QtWidgets>

class MouseFilter : public QObject
{
protected:
	virtual bool eventFilter(QObject* pobj, QEvent* pe);
public:
	MouseFilter(QObject* pobj = 0);
};