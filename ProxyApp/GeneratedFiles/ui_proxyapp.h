/********************************************************************************
** Form generated from reading UI file 'proxyapp.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROXYAPP_H
#define UI_PROXYAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProxyAppClass
{
public:
    QWidget *centralWidget;
    QPushButton *responseButton;
    QPushButton *spiderButton;
    QLabel *statusLabel;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QPlainTextEdit *clientRequestText;
    QPushButton *dumpButton;
    QPlainTextEdit *hostResponseText;
    QLabel *label_3;
    QLabel *label;
    QPushButton *requestButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProxyAppClass)
    {
        if (ProxyAppClass->objectName().isEmpty())
            ProxyAppClass->setObjectName(QString::fromUtf8("ProxyAppClass"));
        ProxyAppClass->resize(1160, 758);
        centralWidget = new QWidget(ProxyAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        responseButton = new QPushButton(centralWidget);
        responseButton->setObjectName(QString::fromUtf8("responseButton"));
        responseButton->setGeometry(QRect(520, 520, 121, 71));
        spiderButton = new QPushButton(centralWidget);
        spiderButton->setObjectName(QString::fromUtf8("spiderButton"));
        spiderButton->setGeometry(QRect(840, 650, 141, 31));
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(70, 710, 1061, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 30, 451, 16));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 651, 801, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 620, 801, 16));
        clientRequestText = new QPlainTextEdit(centralWidget);
        clientRequestText->setObjectName(QString::fromUtf8("clientRequestText"));
        clientRequestText->setGeometry(QRect(20, 60, 461, 531));
        dumpButton = new QPushButton(centralWidget);
        dumpButton->setObjectName(QString::fromUtf8("dumpButton"));
        dumpButton->setGeometry(QRect(1000, 650, 141, 31));
        hostResponseText = new QPlainTextEdit(centralWidget);
        hostResponseText->setObjectName(QString::fromUtf8("hostResponseText"));
        hostResponseText->setGeometry(QRect(680, 60, 461, 531));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(680, 30, 451, 16));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 710, 55, 20));
        requestButton = new QPushButton(centralWidget);
        requestButton->setObjectName(QString::fromUtf8("requestButton"));
        requestButton->setGeometry(QRect(520, 430, 121, 71));
        ProxyAppClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ProxyAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ProxyAppClass->setStatusBar(statusBar);

        retranslateUi(ProxyAppClass);

        QMetaObject::connectSlotsByName(ProxyAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProxyAppClass)
    {
        ProxyAppClass->setWindowTitle(QCoreApplication::translate("ProxyAppClass", "ProxyApp", nullptr));
        responseButton->setText(QCoreApplication::translate("ProxyAppClass", "Send response", nullptr));
        spiderButton->setText(QCoreApplication::translate("ProxyAppClass", "Spider", nullptr));
        statusLabel->setText(QCoreApplication::translate("ProxyAppClass", "Status", nullptr));
        label_2->setText(QCoreApplication::translate("ProxyAppClass", "Client request headers", nullptr));
        label_4->setText(QCoreApplication::translate("ProxyAppClass", "Website URL", nullptr));
        dumpButton->setText(QCoreApplication::translate("ProxyAppClass", "Dump", nullptr));
        label_3->setText(QCoreApplication::translate("ProxyAppClass", "Host response headers", nullptr));
        label->setText(QCoreApplication::translate("ProxyAppClass", "Status:", nullptr));
        requestButton->setText(QCoreApplication::translate("ProxyAppClass", "Send request", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProxyAppClass: public Ui_ProxyAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROXYAPP_H
