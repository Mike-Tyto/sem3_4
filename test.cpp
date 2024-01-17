#ifndef UI_FORM1_H
#define UI_FORM1_H
 
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <QPainter>
 
QT_BEGIN_NAMESPACE
 
class Ui_Form1
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
 
    void setupUi(QWidget *Form1)
    {
        if (Form1->objectName().isEmpty())
            Form1->setObjectName(QString::fromUtf8("Form1"));
        Form1->resize(360, 240);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form1->sizePolicy().hasHeightForWidth());
        Form1->setSizePolicy(sizePolicy);
        Form1->setMinimumSize(QSize(360, 240));
        Form1->setMaximumSize(QSize(360, 240));
        pushButton = new QPushButton(Form1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 190, 75, 23));
        label = new QLabel(Form1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(38, 31, 141, 121));
        label_2 = new QLabel(Form1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 40, 131, 131));
        label_2->setPixmap(QPixmap(QPainter(":/C:/Qt/Wordfinder/Icon1.ico")));
 
        retranslateUi(Form1);
        QObject::connect(pushButton, SIGNAL(clicked()), Form1, SLOT(close()));
 
        QMetaObject::connectSlotsByName(Form1);
    } // setupUi
 
    void retranslateUi(QWidget *Form1)
    {
        Form1->setWindowTitle(QApplication::translate("Form1", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form1", "\320\236\320\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form1", "\320\236\321\200\321\204\320\276\320\263\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \321\201\320\273\320\276\320\262\320\260\321\200\321\214\n"
"\n"
"\320\222\320\265\321\200\321\201\320\270\321\217 1.01\n"
"\n"
"\320\220\320\262\321\202\320\276\321\200: \320\224\320\274\320\270\321\202\321\200\320\270\320\271 \320\250\320\265\320\262\320\265\320\273\320\265\320\262 \n"
"\n"
"\320\223\321\200\321\203\320\277\320\277\320\260 \320\221 3119\n"
"\n"
"\320\224\320\222\320\244\320\243 2012", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
    } // retranslateUi
 
};
 
namespace Ui {
    class Form1: public Ui_Form1 {};
} // namespace Ui
 
QT_END_NAMESPACE
 
#endif // UI_FORM1_H