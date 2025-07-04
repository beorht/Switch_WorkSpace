/********************************************************************************
** Form generated from reading UI file 'guiVpdGbh.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GUIVPDGBH_H
#define GUIVPDGBH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QFrame *frame;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QLabel *label;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(510, 373);
        frame = new QFrame(Form);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 12, 491, 351));
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"   border: 3px solid white;\n"
"   border-radius: 10px;\n"
"}"));
        verticalLayoutWidget = new QWidget(frame);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, -1, 491, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QFont font;
        font.setPointSize(14);
        listWidget->setFont(font);
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"   background-color: transparent;\n"
"   border: 0px;\n"
"   margin: 6px\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"        background-color: #5c6bc0;   /* \321\206\320\262\320\265\321\202 \321\204\320\276\320\275\320\260 \320\277\321\200\320\270 \320\262\321\213\320\261\320\276\321\200\320\265 */\n"
"        color: #ffffff;              /* \321\206\320\262\320\265\321\202 \321\202\320\265\320\272\321\201\321\202\320\260 */\n"
"        border-radius: 6px;\n"
"        margin: 2px;\n"
"    }"));
        listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        verticalLayout->addWidget(listWidget);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"   border-radius: 0px;\n"
"   border: 0px;\n"
"   border-top: 3px solid white;\n"
"   padding: 10px;\n"
"   color: #86eba0;\n"
"}"));

        verticalLayout->addWidget(label);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "Active:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GUIVPDGBH_H
