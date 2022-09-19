/********************************************************************************
** Form generated from reading UI file 'myprocess.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYPROCESS_H
#define UI_MYPROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyProcess
{
public:
    QPushButton *pushButton_log;
    QPushButton *pushButton_config;
    QPushButton *pushButton_noRemoveTwo;
    QPushButton *pushButton_force_cover;
    QPushButton *stop;
    QPushButton *file_exist;
    QPushButton *Github;

    void setupUi(QWidget *MyProcess)
    {
        if (MyProcess->objectName().isEmpty())
            MyProcess->setObjectName(QString::fromUtf8("MyProcess"));
        MyProcess->resize(800, 600);
        pushButton_log = new QPushButton(MyProcess);
        pushButton_log->setObjectName(QString::fromUtf8("pushButton_log"));
        pushButton_log->setGeometry(QRect(80, 20, 341, 71));
        pushButton_config = new QPushButton(MyProcess);
        pushButton_config->setObjectName(QString::fromUtf8("pushButton_config"));
        pushButton_config->setGeometry(QRect(80, 100, 341, 71));
        pushButton_noRemoveTwo = new QPushButton(MyProcess);
        pushButton_noRemoveTwo->setObjectName(QString::fromUtf8("pushButton_noRemoveTwo"));
        pushButton_noRemoveTwo->setGeometry(QRect(80, 180, 341, 71));
        pushButton_force_cover = new QPushButton(MyProcess);
        pushButton_force_cover->setObjectName(QString::fromUtf8("pushButton_force_cover"));
        pushButton_force_cover->setGeometry(QRect(80, 260, 341, 71));
        stop = new QPushButton(MyProcess);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(80, 340, 341, 71));
        file_exist = new QPushButton(MyProcess);
        file_exist->setObjectName(QString::fromUtf8("file_exist"));
        file_exist->setGeometry(QRect(80, 420, 261, 141));
        Github = new QPushButton(MyProcess);
        Github->setObjectName(QString::fromUtf8("Github"));
        Github->setGeometry(QRect(430, 340, 271, 71));

        retranslateUi(MyProcess);

        QMetaObject::connectSlotsByName(MyProcess);
    } // setupUi

    void retranslateUi(QWidget *MyProcess)
    {
        MyProcess->setWindowTitle(QCoreApplication::translate("MyProcess", "MyProcess", nullptr));
        pushButton_log->setText(QCoreApplication::translate("MyProcess", "\347\234\213\344\275\240\346\217\220\344\272\244\346\227\245\345\277\227", nullptr));
        pushButton_config->setText(QCoreApplication::translate("MyProcess", "\346\237\245\347\234\213\346\234\254\345\234\260\344\273\223\345\272\223\351\205\215\347\275\256", nullptr));
        pushButton_noRemoveTwo->setText(QCoreApplication::translate("MyProcess", "\346\212\212\346\234\254\345\234\260\345\272\223\346\217\220\344\272\244\344\270\212\345\216\273\344\275\206\346\230\257\344\270\215\345\216\273\351\207\215", nullptr));
        pushButton_force_cover->setText(QCoreApplication::translate("MyProcess", "\345\274\272\345\210\266\346\212\212\346\234\254\345\234\260\344\273\223\345\272\223\344\273\243\347\240\201\350\246\206\347\233\226", nullptr));
        stop->setText(QCoreApplication::translate("MyProcess", "stop", nullptr));
        file_exist->setText(QCoreApplication::translate("MyProcess", "\346\234\252\345\256\214\345\226\204", nullptr));
        Github->setText(QCoreApplication::translate("MyProcess", "Github", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyProcess: public Ui_MyProcess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPROCESS_H
