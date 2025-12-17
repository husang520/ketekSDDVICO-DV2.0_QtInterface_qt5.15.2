/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen;
    QAction *actionclose;
    QAction *actionUSB;
    QAction *actionEthernet;
    QAction *actionrefresh;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_10;
    QLabel *label_13;
    QLineEdit *lineEdit_peakingTime;
    QComboBox *comboBox_numOfBins;
    QLabel *label_8;
    QLineEdit *lineEdit_inCount;
    QComboBox *comboBox_bytePerBin;
    QLabel *label_3;
    QLineEdit *lineEdit_outRate;
    QLabel *label_5;
    QLineEdit *lineEdit_outCount;
    QLineEdit *lineEdit_realTime;
    QLineEdit *lineEdit_measureTime;
    QLineEdit *lineEdit_inRate;
    QLabel *label_9;
    QLabel *label_2;
    QLabel *label_16;
    QLabel *label_18;
    QLabel *label_11;
    QLabel *label_7;
    QLabel *label_17;
    QLabel *label_12;
    QLabel *label_6;
    QLabel *label_14;
    QPushButton *pushButton_setPeakingTime;
    QLineEdit *lineEdit_liveTime;
    QPushButton *pushButton_setMeasureTime;
    QPushButton *pushButton_startRun;
    QLabel *label_4;
    QTableWidget *tableWidget_device;
    QLabel *label_15;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox_1;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit_infoOutput;
    QMenuBar *menubar;
    QMenu *menu_VICODaemon;
    QMenu *menuDevice;
    QMenu *menuscan;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(854, 682);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QString::fromUtf8("actionopen"));
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName(QString::fromUtf8("actionclose"));
        actionUSB = new QAction(MainWindow);
        actionUSB->setObjectName(QString::fromUtf8("actionUSB"));
        actionEthernet = new QAction(MainWindow);
        actionEthernet->setObjectName(QString::fromUtf8("actionEthernet"));
        actionrefresh = new QAction(MainWindow);
        actionrefresh->setObjectName(QString::fromUtf8("actionrefresh"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_3->addWidget(lineEdit);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 8, 3, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 8, 2, 1, 1);

        lineEdit_peakingTime = new QLineEdit(groupBox);
        lineEdit_peakingTime->setObjectName(QString::fromUtf8("lineEdit_peakingTime"));

        gridLayout->addWidget(lineEdit_peakingTime, 1, 1, 1, 1);

        comboBox_numOfBins = new QComboBox(groupBox);
        comboBox_numOfBins->setObjectName(QString::fromUtf8("comboBox_numOfBins"));

        gridLayout->addWidget(comboBox_numOfBins, 3, 1, 2, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 6, 3, 1, 1);

        lineEdit_inCount = new QLineEdit(groupBox);
        lineEdit_inCount->setObjectName(QString::fromUtf8("lineEdit_inCount"));

        gridLayout->addWidget(lineEdit_inCount, 7, 4, 1, 1);

        comboBox_bytePerBin = new QComboBox(groupBox);
        comboBox_bytePerBin->setObjectName(QString::fromUtf8("comboBox_bytePerBin"));

        gridLayout->addWidget(comboBox_bytePerBin, 5, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_outRate = new QLineEdit(groupBox);
        lineEdit_outRate->setObjectName(QString::fromUtf8("lineEdit_outRate"));

        gridLayout->addWidget(lineEdit_outRate, 8, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        lineEdit_outCount = new QLineEdit(groupBox);
        lineEdit_outCount->setObjectName(QString::fromUtf8("lineEdit_outCount"));

        gridLayout->addWidget(lineEdit_outCount, 7, 1, 1, 1);

        lineEdit_realTime = new QLineEdit(groupBox);
        lineEdit_realTime->setObjectName(QString::fromUtf8("lineEdit_realTime"));

        gridLayout->addWidget(lineEdit_realTime, 6, 1, 1, 1);

        lineEdit_measureTime = new QLineEdit(groupBox);
        lineEdit_measureTime->setObjectName(QString::fromUtf8("lineEdit_measureTime"));

        gridLayout->addWidget(lineEdit_measureTime, 2, 1, 1, 1);

        lineEdit_inRate = new QLineEdit(groupBox);
        lineEdit_inRate->setObjectName(QString::fromUtf8("lineEdit_inRate"));

        gridLayout->addWidget(lineEdit_inRate, 8, 4, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 7, 3, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 7, 5, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 6, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 7, 2, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 6, 5, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 8, 5, 1, 1);

        pushButton_setPeakingTime = new QPushButton(groupBox);
        pushButton_setPeakingTime->setObjectName(QString::fromUtf8("pushButton_setPeakingTime"));

        gridLayout->addWidget(pushButton_setPeakingTime, 1, 4, 1, 1);

        lineEdit_liveTime = new QLineEdit(groupBox);
        lineEdit_liveTime->setObjectName(QString::fromUtf8("lineEdit_liveTime"));

        gridLayout->addWidget(lineEdit_liveTime, 6, 4, 1, 1);

        pushButton_setMeasureTime = new QPushButton(groupBox);
        pushButton_setMeasureTime->setObjectName(QString::fromUtf8("pushButton_setMeasureTime"));

        gridLayout->addWidget(pushButton_setMeasureTime, 2, 4, 1, 1);

        pushButton_startRun = new QPushButton(groupBox);
        pushButton_startRun->setObjectName(QString::fromUtf8("pushButton_startRun"));

        gridLayout->addWidget(pushButton_startRun, 4, 4, 2, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 2, 1, 1);

        tableWidget_device = new QTableWidget(groupBox);
        if (tableWidget_device->columnCount() < 3)
            tableWidget_device->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_device->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_device->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_device->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_device->rowCount() < 1)
            tableWidget_device->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_device->setVerticalHeaderItem(0, __qtablewidgetitem3);
        tableWidget_device->setObjectName(QString::fromUtf8("tableWidget_device"));
        tableWidget_device->setRowCount(1);
        tableWidget_device->setColumnCount(3);

        gridLayout->addWidget(tableWidget_device, 0, 0, 1, 6);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 7, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout_4->addWidget(lineEdit_2);


        gridLayout_2->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_1 = new QGroupBox(centralwidget);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        verticalLayout_2 = new QVBoxLayout(groupBox_1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textEdit_infoOutput = new QTextEdit(groupBox_1);
        textEdit_infoOutput->setObjectName(QString::fromUtf8("textEdit_infoOutput"));

        verticalLayout_2->addWidget(textEdit_infoOutput);


        gridLayout_2->addWidget(groupBox_1, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 854, 21));
        menu_VICODaemon = new QMenu(menubar);
        menu_VICODaemon->setObjectName(QString::fromUtf8("menu_VICODaemon"));
        menuDevice = new QMenu(menubar);
        menuDevice->setObjectName(QString::fromUtf8("menuDevice"));
        menuscan = new QMenu(menuDevice);
        menuscan->setObjectName(QString::fromUtf8("menuscan"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_VICODaemon->menuAction());
        menubar->addAction(menuDevice->menuAction());
        menu_VICODaemon->addAction(actionopen);
        menu_VICODaemon->addAction(actionclose);
        menuDevice->addAction(menuscan->menuAction());
        menuDevice->addAction(actionrefresh);
        menuscan->addAction(actionUSB);
        menuscan->addAction(actionEthernet);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionopen->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        actionclose->setText(QCoreApplication::translate("MainWindow", "close", nullptr));
        actionUSB->setText(QCoreApplication::translate("MainWindow", "USB", nullptr));
        actionEthernet->setText(QCoreApplication::translate("MainWindow", "Ethernet", nullptr));
        actionrefresh->setText(QCoreApplication::translate("MainWindow", "refresh", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Connection and start", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ns", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "inRate:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "count/s", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "liveTime:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "measureTime\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "numOfBins:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "outRate:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "peakingTime\357\274\232", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "inCount:", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "count", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "realTime:", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "count", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "bytePerBin:", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "count/s", nullptr));
        pushButton_setPeakingTime->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        pushButton_setMeasureTime->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        pushButton_startRun->setText(QCoreApplication::translate("MainWindow", "startRun", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_device->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "serialNumber", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_device->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "interface", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_device->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "remark", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "outCount:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("MainWindow", "Information Output", nullptr));
        menu_VICODaemon->setTitle(QCoreApplication::translate("MainWindow", "VICODaemon Service", nullptr));
        menuDevice->setTitle(QCoreApplication::translate("MainWindow", "Device", nullptr));
        menuscan->setTitle(QCoreApplication::translate("MainWindow", "scan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
