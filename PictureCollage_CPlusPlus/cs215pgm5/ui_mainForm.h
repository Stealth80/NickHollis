/********************************************************************************
** Form generated from reading UI file 'mainForm.ui'
**
** Created: Tue Nov 8 21:33:23 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_mainForm
{
public:
    QPushButton *openImageBtn;
    QGroupBox *groupBox_Info;
    QLabel *label_ImgWidth;
    QLabel *label_width_Old;
    QLabel *label_ImgHeight;
    QLabel *label_height_Old;
    QGroupBox *groupBox_Info_2;
    QLabel *label_ImgWidth_2;
    QLabel *label_width_New;
    QLabel *label_ImgHeight_2;
    QLabel *label_height_New;
    QLabel *label_BlkWidth;
    QLabel *label_BlkHeight;
    QLabel *label_height_Blk;
    QLineEdit *lineEdit_BlkWidth;
    QLabel *label_px;
    QPushButton *generateMosaicBtn;
    QPushButton *saveBtn;
    QLabel *label_Image;
    QPushButton *loadFillerBtn;
    QLabel *fillerImageLbl;
    QLabel *directoryPromptLbl;

    void setupUi(QDialog *mainForm)
    {
        if (mainForm->objectName().isEmpty())
            mainForm->setObjectName(QString::fromUtf8("mainForm"));
        mainForm->resize(1015, 658);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainForm->sizePolicy().hasHeightForWidth());
        mainForm->setSizePolicy(sizePolicy);
        mainForm->setMaximumSize(QSize(1015, 658));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../../../\347\275\221\347\253\231/NeoSunrise/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        mainForm->setWindowIcon(icon);
        openImageBtn = new QPushButton(mainForm);
        openImageBtn->setObjectName(QString::fromUtf8("openImageBtn"));
        openImageBtn->setGeometry(QRect(840, 190, 151, 23));
        groupBox_Info = new QGroupBox(mainForm);
        groupBox_Info->setObjectName(QString::fromUtf8("groupBox_Info"));
        groupBox_Info->setGeometry(QRect(810, 220, 201, 81));
        label_ImgWidth = new QLabel(groupBox_Info);
        label_ImgWidth->setObjectName(QString::fromUtf8("label_ImgWidth"));
        label_ImgWidth->setGeometry(QRect(10, 23, 85, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_ImgWidth->setFont(font);
        label_width_Old = new QLabel(groupBox_Info);
        label_width_Old->setObjectName(QString::fromUtf8("label_width_Old"));
        label_width_Old->setGeometry(QRect(111, 23, 71, 16));
        label_ImgHeight = new QLabel(groupBox_Info);
        label_ImgHeight->setObjectName(QString::fromUtf8("label_ImgHeight"));
        label_ImgHeight->setGeometry(QRect(10, 50, 89, 16));
        label_ImgHeight->setFont(font);
        label_height_Old = new QLabel(groupBox_Info);
        label_height_Old->setObjectName(QString::fromUtf8("label_height_Old"));
        label_height_Old->setGeometry(QRect(111, 51, 71, 16));
        groupBox_Info_2 = new QGroupBox(mainForm);
        groupBox_Info_2->setObjectName(QString::fromUtf8("groupBox_Info_2"));
        groupBox_Info_2->setGeometry(QRect(810, 300, 201, 131));
        label_ImgWidth_2 = new QLabel(groupBox_Info_2);
        label_ImgWidth_2->setObjectName(QString::fromUtf8("label_ImgWidth_2"));
        label_ImgWidth_2->setGeometry(QRect(10, 78, 85, 16));
        label_ImgWidth_2->setFont(font);
        label_width_New = new QLabel(groupBox_Info_2);
        label_width_New->setObjectName(QString::fromUtf8("label_width_New"));
        label_width_New->setGeometry(QRect(111, 78, 71, 16));
        label_ImgHeight_2 = new QLabel(groupBox_Info_2);
        label_ImgHeight_2->setObjectName(QString::fromUtf8("label_ImgHeight_2"));
        label_ImgHeight_2->setGeometry(QRect(10, 105, 89, 16));
        label_ImgHeight_2->setFont(font);
        label_height_New = new QLabel(groupBox_Info_2);
        label_height_New->setObjectName(QString::fromUtf8("label_height_New"));
        label_height_New->setGeometry(QRect(111, 106, 71, 16));
        label_BlkWidth = new QLabel(groupBox_Info_2);
        label_BlkWidth->setObjectName(QString::fromUtf8("label_BlkWidth"));
        label_BlkWidth->setGeometry(QRect(10, 23, 85, 16));
        label_BlkWidth->setFont(font);
        label_BlkHeight = new QLabel(groupBox_Info_2);
        label_BlkHeight->setObjectName(QString::fromUtf8("label_BlkHeight"));
        label_BlkHeight->setGeometry(QRect(10, 50, 89, 16));
        label_BlkHeight->setFont(font);
        label_height_Blk = new QLabel(groupBox_Info_2);
        label_height_Blk->setObjectName(QString::fromUtf8("label_height_Blk"));
        label_height_Blk->setGeometry(QRect(110, 51, 71, 16));
        lineEdit_BlkWidth = new QLineEdit(groupBox_Info_2);
        lineEdit_BlkWidth->setObjectName(QString::fromUtf8("lineEdit_BlkWidth"));
        lineEdit_BlkWidth->setGeometry(QRect(100, 21, 71, 20));
        label_px = new QLabel(groupBox_Info_2);
        label_px->setObjectName(QString::fromUtf8("label_px"));
        label_px->setGeometry(QRect(178, 23, 30, 12));
        generateMosaicBtn = new QPushButton(mainForm);
        generateMosaicBtn->setObjectName(QString::fromUtf8("generateMosaicBtn"));
        generateMosaicBtn->setGeometry(QRect(840, 440, 151, 23));
        saveBtn = new QPushButton(mainForm);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setGeometry(QRect(840, 488, 151, 23));
        label_Image = new QLabel(mainForm);
        label_Image->setObjectName(QString::fromUtf8("label_Image"));
        label_Image->setGeometry(QRect(12, 12, 800, 600));
        label_Image->setStyleSheet(QString::fromUtf8("QLabel { background-color : black;}"));
        label_Image->setFrameShape(QFrame::Box);
        label_Image->setFrameShadow(QFrame::Raised);
        label_Image->setLineWidth(1);
        label_Image->setMidLineWidth(0);
        label_Image->setAlignment(Qt::AlignCenter);
        loadFillerBtn = new QPushButton(mainForm);
        loadFillerBtn->setObjectName(QString::fromUtf8("loadFillerBtn"));
        loadFillerBtn->setGeometry(QRect(840, 110, 151, 23));
        fillerImageLbl = new QLabel(mainForm);
        fillerImageLbl->setObjectName(QString::fromUtf8("fillerImageLbl"));
        fillerImageLbl->setGeometry(QRect(820, 80, 191, 21));
        fillerImageLbl->setAlignment(Qt::AlignCenter);
        directoryPromptLbl = new QLabel(mainForm);
        directoryPromptLbl->setObjectName(QString::fromUtf8("directoryPromptLbl"));
        directoryPromptLbl->setGeometry(QRect(850, 50, 151, 21));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        directoryPromptLbl->setFont(font1);

        retranslateUi(mainForm);

        QMetaObject::connectSlotsByName(mainForm);
    } // setupUi

    void retranslateUi(QDialog *mainForm)
    {
        mainForm->setWindowTitle(QApplication::translate("mainForm", "CS215 Image Mosaic Creator", 0, QApplication::UnicodeUTF8));
        openImageBtn->setText(QApplication::translate("mainForm", "Open Image", 0, QApplication::UnicodeUTF8));
        groupBox_Info->setTitle(QApplication::translate("mainForm", "Original Image", 0, QApplication::UnicodeUTF8));
        label_ImgWidth->setText(QApplication::translate("mainForm", "Image Width:", 0, QApplication::UnicodeUTF8));
        label_width_Old->setText(QApplication::translate("mainForm", "0 px", 0, QApplication::UnicodeUTF8));
        label_ImgHeight->setText(QApplication::translate("mainForm", "Image Height:", 0, QApplication::UnicodeUTF8));
        label_height_Old->setText(QApplication::translate("mainForm", "0 px", 0, QApplication::UnicodeUTF8));
        groupBox_Info_2->setTitle(QApplication::translate("mainForm", "New Image", 0, QApplication::UnicodeUTF8));
        label_ImgWidth_2->setText(QApplication::translate("mainForm", "Image Width:", 0, QApplication::UnicodeUTF8));
        label_width_New->setText(QApplication::translate("mainForm", "N/A", 0, QApplication::UnicodeUTF8));
        label_ImgHeight_2->setText(QApplication::translate("mainForm", "Image Height:", 0, QApplication::UnicodeUTF8));
        label_height_New->setText(QApplication::translate("mainForm", "N/A", 0, QApplication::UnicodeUTF8));
        label_BlkWidth->setText(QApplication::translate("mainForm", "Block Width:", 0, QApplication::UnicodeUTF8));
        label_BlkHeight->setText(QApplication::translate("mainForm", "Block Height:", 0, QApplication::UnicodeUTF8));
        label_height_Blk->setText(QApplication::translate("mainForm", "N/A", 0, QApplication::UnicodeUTF8));
        label_px->setText(QApplication::translate("mainForm", "px", 0, QApplication::UnicodeUTF8));
        generateMosaicBtn->setText(QApplication::translate("mainForm", "Generate Mosaic", 0, QApplication::UnicodeUTF8));
        saveBtn->setText(QApplication::translate("mainForm", "Save Image", 0, QApplication::UnicodeUTF8));
        label_Image->setText(QString());
        loadFillerBtn->setText(QApplication::translate("mainForm", "Load Directory", 0, QApplication::UnicodeUTF8));
        fillerImageLbl->setText(QApplication::translate("mainForm", "N/A", 0, QApplication::UnicodeUTF8));
        directoryPromptLbl->setText(QApplication::translate("mainForm", "File Images Directory:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainForm: public Ui_mainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
