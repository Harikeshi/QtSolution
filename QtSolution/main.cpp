#include "QtSolution.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "MouseFilter.h"


void mousePress(QWidget* w, int x = 0, int y = 0,
	Qt::MouseButton bt = Qt::LeftButton, Qt::MouseButton bts = Qt::LeftButton)
{
	if (w)
	{
		QMouseEvent* pe = new QMouseEvent(QEvent::MouseButtonPress,
			QPoint(x, y), bt, bts, Qt::NoModifier);
		QApplication::postEvent(w, pe);
	}
}

class test
{

public:
	test(){}
	void member(){}
};

void f(){}


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QSize sz(100, 200);
	
	QPushButton lbl("");
	lbl.installEventFilter(new MouseFilter(&lbl));
	lbl.resize(200, 100);
	lbl.show();

	test* t =  new test();

	mousePress(&lbl);

	return a.exec();
}
