/********************************************************************************
** Form generated from reading UI file 'designerWzVtKp.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERWZVTKP_H
#define DESIGNERWZVTKP_H

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
    QLabel *label;
    QListWidget *listWidget;
    QLabel *label_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(471, 319);
        frame = new QFrame(Form);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 12, 451, 291));
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border: 3px solid white;\n"
"	border-radius: 10px;\n"
"}"));
        verticalLayoutWidget = new QWidget(frame);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, -1, 451, 291));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	border-radius: 0px;\n"
"	border: 0px solid #ccc;\n"
"	border-bottom: 3px solid #ccc;\n"
"	padding: 6px;\n"
"	color: #d89eff;\n"
"}"));

        verticalLayout->addWidget(label);

        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"	background-color: transparent;\n"
"	border: 0px;\n"
"	margin: 6px\n"
"}"));

        verticalLayout->addWidget(listWidget);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	border-radius: 0px;\n"
"	border: 0px;\n"
"	border-top: 3px solid white;\n"
"	padding: 6px;\n"
"	color: #86eba0;\n"
"}"));

        verticalLayout->addWidget(label_2);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "WorkSpace List:", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "Active:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERWZVTKP_H
