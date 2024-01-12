/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_a;
    QLineEdit *lineEdit_b;
    QPushButton *pushButton_start;
    QLabel *label_result;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit_a = new QLineEdit(centralwidget);
        lineEdit_a->setObjectName(QString::fromUtf8("lineEdit_a"));

        verticalLayout->addWidget(lineEdit_a);

        lineEdit_b = new QLineEdit(centralwidget);
        lineEdit_b->setObjectName(QString::fromUtf8("lineEdit_b"));

        verticalLayout->addWidget(lineEdit_b);

        pushButton_start = new QPushButton(centralwidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));

        verticalLayout->addWidget(pushButton_start);

        label_result = new QLabel(centralwidget);
        label_result->setObjectName(QString::fromUtf8("label_result"));

        verticalLayout->addWidget(label_result);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_start, SIGNAL(clicked()), MainWindow, SLOT(on_pushButton_start_clicked()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        pushButton_start->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_result->setText(QString());
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
