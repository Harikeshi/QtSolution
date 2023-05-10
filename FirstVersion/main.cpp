#include "FirstVersion.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include "qopengl.h"

// Машина состояний, переходы

// TODO установить OpenGL



int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QLabel lbl1("Animated Windows1");
	QLabel lbl2("Animated Windows2");

	QPropertyAnimation* panim1 = new QPropertyAnimation(&lbl1, "geometry");
	panim1->setDuration(3000);
	panim1->setStartValue(QRect(120, 0, 100, 100));
	panim1->setEndValue(QRect(480, 380, 200, 200));
	panim1->setEasingCurve(QEasingCurve::InOutExpo);

	QPropertyAnimation* panim2 = new QPropertyAnimation(&lbl2, "pos");
	panim2->setDuration(3000);
	panim2->setStartValue(QPoint(240, 0));
	panim2->setEndValue(QPoint(240, 480));
	panim1->setEasingCurve(QEasingCurve::OutBounce);

	QParallelAnimationGroup group;
	group.addAnimation(panim1);
	group.addAnimation(panim2);
	group.setLoopCount(2);
	group.start();

	lbl1.show();
	lbl2.show();



	// Один единый виджет, который вызывает и дажее все виджетами










	return a.exec();
}
