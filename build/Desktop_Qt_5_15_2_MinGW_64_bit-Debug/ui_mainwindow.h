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
    QAction *actiongetMCUStatus;
    QAction *actionUpdate;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_1;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit_infoOutput;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_device;
    QLabel *label_2;
    QLineEdit *lineEdit_peakingTime;
    QLabel *label;
    QPushButton *pushButton_setPeakingTime;
    QLabel *label_3;
    QLineEdit *lineEdit_measureTime;
    QLabel *label_4;
    QPushButton *pushButton_setMeasureTime;
    QLabel *label_5;
    QComboBox *comboBox_numOfBins;
    QLabel *label_6;
    QComboBox *comboBox_bytePerBin;
    QLabel *label_23;
    QLineEdit *lineEdit_DPPBoardTemp;
    QLabel *label_22;
    QLabel *label_7;
    QLineEdit *lineEdit_realTime;
    QLabel *label_11;
    QLabel *label_8;
    QLineEdit *lineEdit_liveTime;
    QLabel *label_12;
    QLabel *label_15;
    QLineEdit *lineEdit_outCount;
    QLabel *label_17;
    QLabel *label_16;
    QLineEdit *lineEdit_inCount;
    QLabel *label_18;
    QLabel *label_9;
    QLineEdit *lineEdit_outRate;
    QLabel *label_13;
    QLabel *label_10;
    QLineEdit *lineEdit_inRate;
    QLabel *label_14;
    QLabel *label_19;
    QLineEdit *lineEdit_libVersion;
    QLabel *label_20;
    QLineEdit *lineEdit_daemonVersion;
    QLabel *label_21;
    QLineEdit *lineEdit_firewareVersion;
    QPushButton *pushButton_startRun;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_50;
    QLineEdit *lineEdit_VIAMP_Status;
    QLabel *label_79;
    QLineEdit *lineEdit_sddTargetTmp;
    QLabel *label_80;
    QLabel *label_51;
    QLineEdit *lineEdit_VIAMP_Error;
    QLabel *label_82;
    QLineEdit *lineEdit_techotSideTmp;
    QLabel *label_81;
    QLabel *label_53;
    QLineEdit *lineEdit_viampAdc;
    QLabel *label_52;
    QLabel *label_83;
    QLineEdit *lineEdit_rdySta;
    QLabel *label_54;
    QLineEdit *lineEdit_Ring1;
    QLabel *label_55;
    QLabel *label_84;
    QLineEdit *lineEdit_almostrdySta;
    QLabel *label_56;
    QLineEdit *lineEdit_Back;
    QLabel *label_57;
    QLabel *label_85;
    QLineEdit *lineEdit_monSigFinal;
    QLabel *label_58;
    QLineEdit *lineEdit_RingX;
    QLabel *label_59;
    QLabel *label_86;
    QLineEdit *lineEdit_ctlSigFinal;
    QLabel *label_60;
    QLineEdit *lineEdit_itec;
    QLabel *label_61;
    QLabel *label_87;
    QLineEdit *lineEdit_iPartLimit;
    QLabel *label_74;
    QLineEdit *lineEdit_utec;
    QLabel *label_75;
    QLabel *label_88;
    QLineEdit *lineEdit_pPart;
    QLabel *label_76;
    QLineEdit *lineEdit_tecActive;
    QLabel *label_89;
    QLineEdit *lineEdit_iPart;
    QLabel *label_77;
    QLineEdit *lineEdit_sddTmp;
    QLabel *label_78;
    QLabel *label_90;
    QLineEdit *lineEdit_dPart;
    QLabel *label_91;
    QLineEdit *lineEdit_tecDac;
    QLabel *label_92;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_24;
    QLineEdit *lineEdit_VICO_AV_DV_Status;
    QLabel *label_36;
    QLineEdit *lineEdit_nhvDACSet;
    QLabel *label_37;
    QLabel *label_25;
    QLineEdit *lineEdit_VICO_AV_DV_Error;
    QLabel *label_38;
    QLineEdit *lineEdit_nhvActual;
    QLabel *label_39;
    QLabel *label_26;
    QLineEdit *lineEdit_vIn;
    QLabel *label_32;
    QLabel *label_40;
    QLineEdit *lineEdit_pwrSta;
    QLabel *label_27;
    QLineEdit *lineEdit_p5v;
    QLabel *label_33;
    QLabel *label_41;
    QLineEdit *lineEdit_usbSta;
    QLabel *label_28;
    QLineEdit *lineEdit_n5vActive;
    QLabel *label_42;
    QLineEdit *lineEdit_gpioSta;
    QLabel *label_29;
    QLineEdit *lineEdit_mcu3v3;
    QLabel *label_34;
    QLabel *label_43;
    QLineEdit *lineEdit_reqFlashSta;
    QLabel *label_30;
    QLineEdit *lineEdit_ref2v5;
    QLabel *label_31;
    QLabel *label_44;
    QLineEdit *lineEdit_fpga3v3;
    QLabel *label_45;
    QLabel *label_35;
    QLineEdit *lineEdit_nhvActive;
    QLabel *label_47;
    QLineEdit *lineEdit_therm1;
    QLabel *label_46;
    QLabel *label_48;
    QLineEdit *lineEdit_therm2;
    QLabel *label_49;
    QMenuBar *menubar;
    QMenu *menu_VICODaemon;
    QMenu *menuDevice;
    QMenu *menuscan;
    QMenu *menuMCU;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(953, 745);
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
        actiongetMCUStatus = new QAction(MainWindow);
        actiongetMCUStatus->setObjectName(QString::fromUtf8("actiongetMCUStatus"));
        actionUpdate = new QAction(MainWindow);
        actionUpdate->setObjectName(QString::fromUtf8("actionUpdate"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_1 = new QGroupBox(centralwidget);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        verticalLayout_2 = new QVBoxLayout(groupBox_1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textEdit_infoOutput = new QTextEdit(groupBox_1);
        textEdit_infoOutput->setObjectName(QString::fromUtf8("textEdit_infoOutput"));

        verticalLayout_2->addWidget(textEdit_infoOutput);


        gridLayout_4->addWidget(groupBox_1, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
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
        tableWidget_device->setMaximumSize(QSize(400, 101));
        tableWidget_device->setRowCount(1);
        tableWidget_device->setColumnCount(3);

        gridLayout_2->addWidget(tableWidget_device, 0, 0, 1, 5);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_peakingTime = new QLineEdit(groupBox);
        lineEdit_peakingTime->setObjectName(QString::fromUtf8("lineEdit_peakingTime"));
        lineEdit_peakingTime->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_peakingTime, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 2, 1, 1);

        pushButton_setPeakingTime = new QPushButton(groupBox);
        pushButton_setPeakingTime->setObjectName(QString::fromUtf8("pushButton_setPeakingTime"));
        pushButton_setPeakingTime->setMaximumSize(QSize(61, 23));

        gridLayout_2->addWidget(pushButton_setPeakingTime, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_measureTime = new QLineEdit(groupBox);
        lineEdit_measureTime->setObjectName(QString::fromUtf8("lineEdit_measureTime"));
        lineEdit_measureTime->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_measureTime, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 2, 1, 1);

        pushButton_setMeasureTime = new QPushButton(groupBox);
        pushButton_setMeasureTime->setObjectName(QString::fromUtf8("pushButton_setMeasureTime"));
        pushButton_setMeasureTime->setMaximumSize(QSize(61, 23));

        gridLayout_2->addWidget(pushButton_setMeasureTime, 2, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        comboBox_numOfBins = new QComboBox(groupBox);
        comboBox_numOfBins->setObjectName(QString::fromUtf8("comboBox_numOfBins"));
        comboBox_numOfBins->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(comboBox_numOfBins, 3, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        comboBox_bytePerBin = new QComboBox(groupBox);
        comboBox_bytePerBin->setObjectName(QString::fromUtf8("comboBox_bytePerBin"));
        comboBox_bytePerBin->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(comboBox_bytePerBin, 4, 1, 1, 1);

        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_2->addWidget(label_23, 4, 3, 1, 1);

        lineEdit_DPPBoardTemp = new QLineEdit(groupBox);
        lineEdit_DPPBoardTemp->setObjectName(QString::fromUtf8("lineEdit_DPPBoardTemp"));
        lineEdit_DPPBoardTemp->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_DPPBoardTemp, 4, 4, 1, 1);

        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 4, 5, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 5, 0, 1, 1);

        lineEdit_realTime = new QLineEdit(groupBox);
        lineEdit_realTime->setObjectName(QString::fromUtf8("lineEdit_realTime"));
        lineEdit_realTime->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_realTime, 5, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 5, 2, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 5, 3, 1, 1);

        lineEdit_liveTime = new QLineEdit(groupBox);
        lineEdit_liveTime->setObjectName(QString::fromUtf8("lineEdit_liveTime"));
        lineEdit_liveTime->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_liveTime, 5, 4, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 5, 5, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 6, 0, 1, 1);

        lineEdit_outCount = new QLineEdit(groupBox);
        lineEdit_outCount->setObjectName(QString::fromUtf8("lineEdit_outCount"));
        lineEdit_outCount->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_outCount, 6, 1, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 6, 2, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 6, 3, 1, 1);

        lineEdit_inCount = new QLineEdit(groupBox);
        lineEdit_inCount->setObjectName(QString::fromUtf8("lineEdit_inCount"));
        lineEdit_inCount->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_inCount, 6, 4, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_2->addWidget(label_18, 6, 5, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 7, 0, 1, 1);

        lineEdit_outRate = new QLineEdit(groupBox);
        lineEdit_outRate->setObjectName(QString::fromUtf8("lineEdit_outRate"));
        lineEdit_outRate->setMaximumSize(QSize(61, 16777215));

        gridLayout_2->addWidget(lineEdit_outRate, 7, 1, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 7, 2, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 7, 3, 1, 1);

        lineEdit_inRate = new QLineEdit(groupBox);
        lineEdit_inRate->setObjectName(QString::fromUtf8("lineEdit_inRate"));
        lineEdit_inRate->setMaximumSize(QSize(61, 21));

        gridLayout_2->addWidget(lineEdit_inRate, 7, 4, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 7, 5, 1, 1);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 8, 0, 1, 1);

        lineEdit_libVersion = new QLineEdit(groupBox);
        lineEdit_libVersion->setObjectName(QString::fromUtf8("lineEdit_libVersion"));
        lineEdit_libVersion->setMaximumSize(QSize(151, 16777215));

        gridLayout_2->addWidget(lineEdit_libVersion, 8, 1, 1, 2);

        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 9, 0, 1, 1);

        lineEdit_daemonVersion = new QLineEdit(groupBox);
        lineEdit_daemonVersion->setObjectName(QString::fromUtf8("lineEdit_daemonVersion"));
        lineEdit_daemonVersion->setMaximumSize(QSize(151, 16777215));

        gridLayout_2->addWidget(lineEdit_daemonVersion, 9, 1, 1, 2);

        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 10, 0, 1, 1);

        lineEdit_firewareVersion = new QLineEdit(groupBox);
        lineEdit_firewareVersion->setObjectName(QString::fromUtf8("lineEdit_firewareVersion"));
        lineEdit_firewareVersion->setMaximumSize(QSize(151, 16777215));

        gridLayout_2->addWidget(lineEdit_firewareVersion, 10, 1, 1, 2);

        pushButton_startRun = new QPushButton(groupBox);
        pushButton_startRun->setObjectName(QString::fromUtf8("pushButton_startRun"));
        pushButton_startRun->setMaximumSize(QSize(61, 23));

        gridLayout_2->addWidget(pushButton_startRun, 10, 4, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 1, 2, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_50 = new QLabel(groupBox_3);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        gridLayout_3->addWidget(label_50, 0, 0, 1, 1);

        lineEdit_VIAMP_Status = new QLineEdit(groupBox_3);
        lineEdit_VIAMP_Status->setObjectName(QString::fromUtf8("lineEdit_VIAMP_Status"));
        lineEdit_VIAMP_Status->setMaximumSize(QSize(111, 16777215));

        gridLayout_3->addWidget(lineEdit_VIAMP_Status, 0, 1, 1, 2);

        label_79 = new QLabel(groupBox_3);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        gridLayout_3->addWidget(label_79, 0, 3, 1, 1);

        lineEdit_sddTargetTmp = new QLineEdit(groupBox_3);
        lineEdit_sddTargetTmp->setObjectName(QString::fromUtf8("lineEdit_sddTargetTmp"));
        lineEdit_sddTargetTmp->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_sddTargetTmp, 0, 4, 1, 1);

        label_80 = new QLabel(groupBox_3);
        label_80->setObjectName(QString::fromUtf8("label_80"));

        gridLayout_3->addWidget(label_80, 0, 5, 1, 1);

        label_51 = new QLabel(groupBox_3);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_3->addWidget(label_51, 1, 0, 1, 1);

        lineEdit_VIAMP_Error = new QLineEdit(groupBox_3);
        lineEdit_VIAMP_Error->setObjectName(QString::fromUtf8("lineEdit_VIAMP_Error"));
        lineEdit_VIAMP_Error->setMaximumSize(QSize(111, 16777215));

        gridLayout_3->addWidget(lineEdit_VIAMP_Error, 1, 1, 1, 2);

        label_82 = new QLabel(groupBox_3);
        label_82->setObjectName(QString::fromUtf8("label_82"));

        gridLayout_3->addWidget(label_82, 1, 3, 1, 1);

        lineEdit_techotSideTmp = new QLineEdit(groupBox_3);
        lineEdit_techotSideTmp->setObjectName(QString::fromUtf8("lineEdit_techotSideTmp"));
        lineEdit_techotSideTmp->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_techotSideTmp, 1, 4, 1, 1);

        label_81 = new QLabel(groupBox_3);
        label_81->setObjectName(QString::fromUtf8("label_81"));

        gridLayout_3->addWidget(label_81, 1, 5, 1, 1);

        label_53 = new QLabel(groupBox_3);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        gridLayout_3->addWidget(label_53, 2, 0, 1, 1);

        lineEdit_viampAdc = new QLineEdit(groupBox_3);
        lineEdit_viampAdc->setObjectName(QString::fromUtf8("lineEdit_viampAdc"));
        lineEdit_viampAdc->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_viampAdc, 2, 1, 1, 1);

        label_52 = new QLabel(groupBox_3);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        gridLayout_3->addWidget(label_52, 2, 2, 1, 1);

        label_83 = new QLabel(groupBox_3);
        label_83->setObjectName(QString::fromUtf8("label_83"));

        gridLayout_3->addWidget(label_83, 2, 3, 1, 1);

        lineEdit_rdySta = new QLineEdit(groupBox_3);
        lineEdit_rdySta->setObjectName(QString::fromUtf8("lineEdit_rdySta"));
        lineEdit_rdySta->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_rdySta, 2, 4, 1, 1);

        label_54 = new QLabel(groupBox_3);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        gridLayout_3->addWidget(label_54, 3, 0, 1, 1);

        lineEdit_Ring1 = new QLineEdit(groupBox_3);
        lineEdit_Ring1->setObjectName(QString::fromUtf8("lineEdit_Ring1"));
        lineEdit_Ring1->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_Ring1, 3, 1, 1, 1);

        label_55 = new QLabel(groupBox_3);
        label_55->setObjectName(QString::fromUtf8("label_55"));

        gridLayout_3->addWidget(label_55, 3, 2, 1, 1);

        label_84 = new QLabel(groupBox_3);
        label_84->setObjectName(QString::fromUtf8("label_84"));

        gridLayout_3->addWidget(label_84, 3, 3, 1, 1);

        lineEdit_almostrdySta = new QLineEdit(groupBox_3);
        lineEdit_almostrdySta->setObjectName(QString::fromUtf8("lineEdit_almostrdySta"));
        lineEdit_almostrdySta->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_almostrdySta, 3, 4, 1, 1);

        label_56 = new QLabel(groupBox_3);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout_3->addWidget(label_56, 4, 0, 1, 1);

        lineEdit_Back = new QLineEdit(groupBox_3);
        lineEdit_Back->setObjectName(QString::fromUtf8("lineEdit_Back"));
        lineEdit_Back->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_Back, 4, 1, 1, 1);

        label_57 = new QLabel(groupBox_3);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_3->addWidget(label_57, 4, 2, 1, 1);

        label_85 = new QLabel(groupBox_3);
        label_85->setObjectName(QString::fromUtf8("label_85"));

        gridLayout_3->addWidget(label_85, 4, 3, 1, 1);

        lineEdit_monSigFinal = new QLineEdit(groupBox_3);
        lineEdit_monSigFinal->setObjectName(QString::fromUtf8("lineEdit_monSigFinal"));
        lineEdit_monSigFinal->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_monSigFinal, 4, 4, 1, 1);

        label_58 = new QLabel(groupBox_3);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        gridLayout_3->addWidget(label_58, 5, 0, 1, 1);

        lineEdit_RingX = new QLineEdit(groupBox_3);
        lineEdit_RingX->setObjectName(QString::fromUtf8("lineEdit_RingX"));
        lineEdit_RingX->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_RingX, 5, 1, 1, 1);

        label_59 = new QLabel(groupBox_3);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        gridLayout_3->addWidget(label_59, 5, 2, 1, 1);

        label_86 = new QLabel(groupBox_3);
        label_86->setObjectName(QString::fromUtf8("label_86"));

        gridLayout_3->addWidget(label_86, 5, 3, 1, 1);

        lineEdit_ctlSigFinal = new QLineEdit(groupBox_3);
        lineEdit_ctlSigFinal->setObjectName(QString::fromUtf8("lineEdit_ctlSigFinal"));
        lineEdit_ctlSigFinal->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_ctlSigFinal, 5, 4, 1, 1);

        label_60 = new QLabel(groupBox_3);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout_3->addWidget(label_60, 6, 0, 1, 1);

        lineEdit_itec = new QLineEdit(groupBox_3);
        lineEdit_itec->setObjectName(QString::fromUtf8("lineEdit_itec"));
        lineEdit_itec->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_itec, 6, 1, 1, 1);

        label_61 = new QLabel(groupBox_3);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        gridLayout_3->addWidget(label_61, 6, 2, 1, 1);

        label_87 = new QLabel(groupBox_3);
        label_87->setObjectName(QString::fromUtf8("label_87"));

        gridLayout_3->addWidget(label_87, 6, 3, 1, 1);

        lineEdit_iPartLimit = new QLineEdit(groupBox_3);
        lineEdit_iPartLimit->setObjectName(QString::fromUtf8("lineEdit_iPartLimit"));
        lineEdit_iPartLimit->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_iPartLimit, 6, 4, 1, 1);

        label_74 = new QLabel(groupBox_3);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        gridLayout_3->addWidget(label_74, 7, 0, 1, 1);

        lineEdit_utec = new QLineEdit(groupBox_3);
        lineEdit_utec->setObjectName(QString::fromUtf8("lineEdit_utec"));
        lineEdit_utec->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_utec, 7, 1, 1, 1);

        label_75 = new QLabel(groupBox_3);
        label_75->setObjectName(QString::fromUtf8("label_75"));

        gridLayout_3->addWidget(label_75, 7, 2, 1, 1);

        label_88 = new QLabel(groupBox_3);
        label_88->setObjectName(QString::fromUtf8("label_88"));

        gridLayout_3->addWidget(label_88, 7, 3, 1, 1);

        lineEdit_pPart = new QLineEdit(groupBox_3);
        lineEdit_pPart->setObjectName(QString::fromUtf8("lineEdit_pPart"));
        lineEdit_pPart->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_pPart, 7, 4, 1, 1);

        label_76 = new QLabel(groupBox_3);
        label_76->setObjectName(QString::fromUtf8("label_76"));

        gridLayout_3->addWidget(label_76, 8, 0, 1, 1);

        lineEdit_tecActive = new QLineEdit(groupBox_3);
        lineEdit_tecActive->setObjectName(QString::fromUtf8("lineEdit_tecActive"));
        lineEdit_tecActive->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_tecActive, 8, 1, 1, 1);

        label_89 = new QLabel(groupBox_3);
        label_89->setObjectName(QString::fromUtf8("label_89"));

        gridLayout_3->addWidget(label_89, 8, 3, 1, 1);

        lineEdit_iPart = new QLineEdit(groupBox_3);
        lineEdit_iPart->setObjectName(QString::fromUtf8("lineEdit_iPart"));
        lineEdit_iPart->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_iPart, 8, 4, 1, 1);

        label_77 = new QLabel(groupBox_3);
        label_77->setObjectName(QString::fromUtf8("label_77"));

        gridLayout_3->addWidget(label_77, 9, 0, 1, 1);

        lineEdit_sddTmp = new QLineEdit(groupBox_3);
        lineEdit_sddTmp->setObjectName(QString::fromUtf8("lineEdit_sddTmp"));
        lineEdit_sddTmp->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_sddTmp, 9, 1, 1, 1);

        label_78 = new QLabel(groupBox_3);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        gridLayout_3->addWidget(label_78, 9, 2, 1, 1);

        label_90 = new QLabel(groupBox_3);
        label_90->setObjectName(QString::fromUtf8("label_90"));

        gridLayout_3->addWidget(label_90, 9, 3, 1, 1);

        lineEdit_dPart = new QLineEdit(groupBox_3);
        lineEdit_dPart->setObjectName(QString::fromUtf8("lineEdit_dPart"));
        lineEdit_dPart->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_dPart, 9, 4, 1, 1);

        label_91 = new QLabel(groupBox_3);
        label_91->setObjectName(QString::fromUtf8("label_91"));

        gridLayout_3->addWidget(label_91, 10, 3, 1, 1);

        lineEdit_tecDac = new QLineEdit(groupBox_3);
        lineEdit_tecDac->setObjectName(QString::fromUtf8("lineEdit_tecDac"));
        lineEdit_tecDac->setMaximumSize(QSize(91, 16777215));

        gridLayout_3->addWidget(lineEdit_tecDac, 10, 4, 1, 1);

        label_92 = new QLabel(groupBox_3);
        label_92->setObjectName(QString::fromUtf8("label_92"));

        gridLayout_3->addWidget(label_92, 10, 5, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 1, 0, 2, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout->addWidget(label_24, 0, 0, 1, 1);

        lineEdit_VICO_AV_DV_Status = new QLineEdit(groupBox_2);
        lineEdit_VICO_AV_DV_Status->setObjectName(QString::fromUtf8("lineEdit_VICO_AV_DV_Status"));
        lineEdit_VICO_AV_DV_Status->setMaximumSize(QSize(111, 16777215));

        gridLayout->addWidget(lineEdit_VICO_AV_DV_Status, 0, 1, 1, 2);

        label_36 = new QLabel(groupBox_2);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout->addWidget(label_36, 0, 3, 1, 1);

        lineEdit_nhvDACSet = new QLineEdit(groupBox_2);
        lineEdit_nhvDACSet->setObjectName(QString::fromUtf8("lineEdit_nhvDACSet"));
        lineEdit_nhvDACSet->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_nhvDACSet, 0, 4, 1, 1);

        label_37 = new QLabel(groupBox_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout->addWidget(label_37, 0, 5, 1, 1);

        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout->addWidget(label_25, 1, 0, 1, 1);

        lineEdit_VICO_AV_DV_Error = new QLineEdit(groupBox_2);
        lineEdit_VICO_AV_DV_Error->setObjectName(QString::fromUtf8("lineEdit_VICO_AV_DV_Error"));
        lineEdit_VICO_AV_DV_Error->setMaximumSize(QSize(111, 16777215));

        gridLayout->addWidget(lineEdit_VICO_AV_DV_Error, 1, 1, 1, 2);

        label_38 = new QLabel(groupBox_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout->addWidget(label_38, 1, 3, 1, 1);

        lineEdit_nhvActual = new QLineEdit(groupBox_2);
        lineEdit_nhvActual->setObjectName(QString::fromUtf8("lineEdit_nhvActual"));
        lineEdit_nhvActual->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_nhvActual, 1, 4, 1, 1);

        label_39 = new QLabel(groupBox_2);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        gridLayout->addWidget(label_39, 1, 5, 1, 1);

        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout->addWidget(label_26, 2, 0, 1, 1);

        lineEdit_vIn = new QLineEdit(groupBox_2);
        lineEdit_vIn->setObjectName(QString::fromUtf8("lineEdit_vIn"));
        lineEdit_vIn->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_vIn, 2, 1, 1, 1);

        label_32 = new QLabel(groupBox_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout->addWidget(label_32, 2, 2, 1, 1);

        label_40 = new QLabel(groupBox_2);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        gridLayout->addWidget(label_40, 2, 3, 1, 1);

        lineEdit_pwrSta = new QLineEdit(groupBox_2);
        lineEdit_pwrSta->setObjectName(QString::fromUtf8("lineEdit_pwrSta"));
        lineEdit_pwrSta->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_pwrSta, 2, 4, 1, 1);

        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout->addWidget(label_27, 3, 0, 1, 1);

        lineEdit_p5v = new QLineEdit(groupBox_2);
        lineEdit_p5v->setObjectName(QString::fromUtf8("lineEdit_p5v"));
        lineEdit_p5v->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_p5v, 3, 1, 1, 1);

        label_33 = new QLabel(groupBox_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout->addWidget(label_33, 3, 2, 1, 1);

        label_41 = new QLabel(groupBox_2);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout->addWidget(label_41, 3, 3, 1, 1);

        lineEdit_usbSta = new QLineEdit(groupBox_2);
        lineEdit_usbSta->setObjectName(QString::fromUtf8("lineEdit_usbSta"));
        lineEdit_usbSta->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_usbSta, 3, 4, 1, 1);

        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout->addWidget(label_28, 4, 0, 1, 1);

        lineEdit_n5vActive = new QLineEdit(groupBox_2);
        lineEdit_n5vActive->setObjectName(QString::fromUtf8("lineEdit_n5vActive"));
        lineEdit_n5vActive->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_n5vActive, 4, 1, 1, 1);

        label_42 = new QLabel(groupBox_2);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout->addWidget(label_42, 4, 3, 1, 1);

        lineEdit_gpioSta = new QLineEdit(groupBox_2);
        lineEdit_gpioSta->setObjectName(QString::fromUtf8("lineEdit_gpioSta"));
        lineEdit_gpioSta->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_gpioSta, 4, 4, 1, 1);

        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 5, 0, 1, 1);

        lineEdit_mcu3v3 = new QLineEdit(groupBox_2);
        lineEdit_mcu3v3->setObjectName(QString::fromUtf8("lineEdit_mcu3v3"));
        lineEdit_mcu3v3->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_mcu3v3, 5, 1, 1, 1);

        label_34 = new QLabel(groupBox_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout->addWidget(label_34, 5, 2, 1, 1);

        label_43 = new QLabel(groupBox_2);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        gridLayout->addWidget(label_43, 5, 3, 1, 1);

        lineEdit_reqFlashSta = new QLineEdit(groupBox_2);
        lineEdit_reqFlashSta->setObjectName(QString::fromUtf8("lineEdit_reqFlashSta"));
        lineEdit_reqFlashSta->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_reqFlashSta, 5, 4, 1, 1);

        label_30 = new QLabel(groupBox_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout->addWidget(label_30, 6, 0, 1, 1);

        lineEdit_ref2v5 = new QLineEdit(groupBox_2);
        lineEdit_ref2v5->setObjectName(QString::fromUtf8("lineEdit_ref2v5"));
        lineEdit_ref2v5->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_ref2v5, 6, 1, 1, 1);

        label_31 = new QLabel(groupBox_2);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout->addWidget(label_31, 6, 2, 1, 1);

        label_44 = new QLabel(groupBox_2);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout->addWidget(label_44, 6, 3, 1, 1);

        lineEdit_fpga3v3 = new QLineEdit(groupBox_2);
        lineEdit_fpga3v3->setObjectName(QString::fromUtf8("lineEdit_fpga3v3"));
        lineEdit_fpga3v3->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_fpga3v3, 6, 4, 1, 1);

        label_45 = new QLabel(groupBox_2);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout->addWidget(label_45, 6, 5, 1, 1);

        label_35 = new QLabel(groupBox_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout->addWidget(label_35, 7, 0, 1, 1);

        lineEdit_nhvActive = new QLineEdit(groupBox_2);
        lineEdit_nhvActive->setObjectName(QString::fromUtf8("lineEdit_nhvActive"));
        lineEdit_nhvActive->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_nhvActive, 7, 1, 1, 1);

        label_47 = new QLabel(groupBox_2);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout->addWidget(label_47, 7, 3, 1, 1);

        lineEdit_therm1 = new QLineEdit(groupBox_2);
        lineEdit_therm1->setObjectName(QString::fromUtf8("lineEdit_therm1"));
        lineEdit_therm1->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_therm1, 7, 4, 1, 1);

        label_46 = new QLabel(groupBox_2);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout->addWidget(label_46, 7, 5, 1, 1);

        label_48 = new QLabel(groupBox_2);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout->addWidget(label_48, 8, 3, 1, 1);

        lineEdit_therm2 = new QLineEdit(groupBox_2);
        lineEdit_therm2->setObjectName(QString::fromUtf8("lineEdit_therm2"));
        lineEdit_therm2->setMaximumSize(QSize(91, 16777215));

        gridLayout->addWidget(lineEdit_therm2, 8, 4, 1, 1);

        label_49 = new QLabel(groupBox_2);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout->addWidget(label_49, 8, 5, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 953, 21));
        menu_VICODaemon = new QMenu(menubar);
        menu_VICODaemon->setObjectName(QString::fromUtf8("menu_VICODaemon"));
        menuDevice = new QMenu(menubar);
        menuDevice->setObjectName(QString::fromUtf8("menuDevice"));
        menuscan = new QMenu(menuDevice);
        menuscan->setObjectName(QString::fromUtf8("menuscan"));
        menuMCU = new QMenu(menuDevice);
        menuMCU->setObjectName(QString::fromUtf8("menuMCU"));
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
        menuDevice->addAction(menuMCU->menuAction());
        menuscan->addAction(actionUSB);
        menuscan->addAction(actionEthernet);
        menuMCU->addAction(actiongetMCUStatus);

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
        actiongetMCUStatus->setText(QCoreApplication::translate("MainWindow", "getMCUStatus", nullptr));
        actionUpdate->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("MainWindow", "Information Output", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Connection and start", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_device->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "serialNumber", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_device->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "interface", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_device->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "remark", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "peakingTime\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ns", nullptr));
        pushButton_setPeakingTime->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "measureTime\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        pushButton_setMeasureTime->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "numOfBins:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "bytePerBin:", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "DPPBdTmp:", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "realTime:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "liveTime:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "outCount:", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "count", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "inCount:", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "count", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "outRate:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "count/s", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "inRate:", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "count/s", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "libVersion:", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "daemonVersion:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "firewareVersion:", nullptr));
        pushButton_startRun->setText(QCoreApplication::translate("MainWindow", "startRun", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "LiveInfo2VIAMP", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "VIAMP sta:", nullptr));
        label_79->setText(QCoreApplication::translate("MainWindow", "sddTargetTmp:", nullptr));
        label_80->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_51->setText(QCoreApplication::translate("MainWindow", "VIAMP err:", nullptr));
        label_82->setText(QCoreApplication::translate("MainWindow", "techotTmp:", nullptr));
        label_81->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_53->setText(QCoreApplication::translate("MainWindow", "viampAdc:", nullptr));
        label_52->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_83->setText(QCoreApplication::translate("MainWindow", "rdySta:", nullptr));
        label_54->setText(QCoreApplication::translate("MainWindow", "Ring1:", nullptr));
        label_55->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_84->setText(QCoreApplication::translate("MainWindow", "almostrdySta:", nullptr));
        label_56->setText(QCoreApplication::translate("MainWindow", "Back:", nullptr));
        label_57->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_85->setText(QCoreApplication::translate("MainWindow", "monSigFinal:", nullptr));
        label_58->setText(QCoreApplication::translate("MainWindow", "RingX:", nullptr));
        label_59->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_86->setText(QCoreApplication::translate("MainWindow", "ctrlSigFinal:", nullptr));
        label_60->setText(QCoreApplication::translate("MainWindow", "itec:", nullptr));
        label_61->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        label_87->setText(QCoreApplication::translate("MainWindow", "iPartLimit:", nullptr));
        label_74->setText(QCoreApplication::translate("MainWindow", "utec:", nullptr));
        label_75->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_88->setText(QCoreApplication::translate("MainWindow", "pPart:", nullptr));
        label_76->setText(QCoreApplication::translate("MainWindow", "tecActive:", nullptr));
        label_89->setText(QCoreApplication::translate("MainWindow", "iPart:", nullptr));
        label_77->setText(QCoreApplication::translate("MainWindow", "sddTmp:", nullptr));
        label_78->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_90->setText(QCoreApplication::translate("MainWindow", "dPart:", nullptr));
        label_91->setText(QCoreApplication::translate("MainWindow", "tecDac:", nullptr));
        label_92->setText(QCoreApplication::translate("MainWindow", "mV", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "LiveInfo2VICO", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "VICO-AV/-DV sta:", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "-hvDACSet:", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "mV", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "VICO-AV/-DV err:", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "-hvActual:", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "vIn:", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "pwr:", nullptr));
        lineEdit_pwrSta->setText(QString());
        label_27->setText(QCoreApplication::translate("MainWindow", "p5v:", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "usb:", nullptr));
        lineEdit_usbSta->setText(QString());
        label_28->setText(QCoreApplication::translate("MainWindow", "n5vActive:", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "gpio:", nullptr));
        lineEdit_gpioSta->setText(QString());
        label_29->setText(QCoreApplication::translate("MainWindow", "mcu3v3:", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "reqfbl:", nullptr));
        lineEdit_reqFlashSta->setText(QString());
        label_30->setText(QCoreApplication::translate("MainWindow", "ref2v5:", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "fpga3v3:", nullptr));
        lineEdit_fpga3v3->setText(QString());
        label_45->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "-hvActive:", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "therm1:", nullptr));
        lineEdit_therm1->setText(QString());
        label_46->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "therm2:", nullptr));
        lineEdit_therm2->setText(QString());
        label_49->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        menu_VICODaemon->setTitle(QCoreApplication::translate("MainWindow", "VICODaemon Service", nullptr));
        menuDevice->setTitle(QCoreApplication::translate("MainWindow", "Device", nullptr));
        menuscan->setTitle(QCoreApplication::translate("MainWindow", "scan", nullptr));
        menuMCU->setTitle(QCoreApplication::translate("MainWindow", "MCU", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
