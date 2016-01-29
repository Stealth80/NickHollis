#include <QFileDialog>
#include <QTextCodec>
#include <cmath>
#include "mainForm.h"
#include "globals.h"
#include "fillerImage.h"

void saveImageToFile(string filename);
bool imageLoaded();
image* displayImage();
bool loadImageFromFile(string filename);
bool loadFillerImagesFromFolder(string folder);
void generateMosaic(int blockWidth, int blockHeight);
fillerImage* findBestFillerImage(pixel color);
bool mainForm::fillerImagesLoaded = false;

mainForm::mainForm() {
    widget.setupUi(this);
    connect(widget.openImageBtn, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(widget.loadFillerBtn, SIGNAL(clicked()), this, SLOT(loadImagesDialog()));
    connect(widget.saveBtn, SIGNAL(clicked()), this, SLOT(saveFileDialog()));
    connect(widget.generateMosaicBtn, SIGNAL(clicked()), this, SLOT(generateMosaicSlot()));
    connect(widget.lineEdit_BlkWidth, SIGNAL(textChanged(QString)), this, SLOT(updateSizeInfo(QString)));
    InitializeComponent();

    // for system language other than English
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
}

mainForm::~mainForm() {
}

void mainForm::InitializeComponent() {
    origImageWidth = 0;
    origImageHeight = 0;
    blockHeight = 0;
    isMosaicGenerated = false;

    widget.generateMosaicBtn->setDisabled(true);
    widget.saveBtn->setDisabled(true);
    widget.lineEdit_BlkWidth->setDisabled(true);
    widget.label_Image->setStyleSheet("QLabel { background-color : black;}");
}

void mainForm::openFileDialog() {
    QString filename;

    if ((filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.jpg *.png *.bmp)"))) != "") {
        if (!loadImageFromFile(filename.toStdString()))
            return;

        image* myImage = displayImage();

        if (myImage && myImage->getPixels()) {
            widget.saveBtn->setDisabled(false);
            widget.label_BlkWidth->setDisabled(false);
            widget.lineEdit_BlkWidth->setDisabled(false);

            char buffer[20];
            sprintf(buffer, "%d px", myImage->getHeight());
            widget.label_height_Old->setText(QString(buffer));

            sprintf(buffer, "%d px", myImage->getWidth());
            widget.label_width_Old->setText(QString(buffer));

            this->origImageHeight = myImage->getHeight();
            this->origImageWidth = myImage->getWidth();

            if (int(myImage->getWidth() / 50) > 0) {
                sprintf(buffer, "%d", myImage->getWidth() / 50);
                widget.lineEdit_BlkWidth->setText(QString(buffer));
                setBlockWidth(myImage->getWidth() / 50);
            } else {
                sprintf(buffer, "%d", 2);
                widget.lineEdit_BlkWidth->setText(QString(buffer));
                setBlockWidth(2);
            }

            this->isMosaicGenerated = false;
            enableGenerateMosaic();

            showImage(myImage);
        } else {
            cout << "The image could not be displayed because there is no pixel data!" << endl;
        }
    }
}

void mainForm::loadImagesDialog() {
    QString directoryName;

    if ((directoryName = QFileDialog::getExistingDirectory(this, tr("Directory"), "")) != "") {
        if (!loadFillerImagesFromFolder(directoryName.toStdString()))
            return;
        widget.fillerImageLbl->setAlignment(Qt::AlignLeft);
        widget.fillerImageLbl->setText(directoryName);
        mainForm::fillerImagesLoaded = true;
        enableGenerateMosaic();

    }
}

void mainForm::saveFileDialog() {
    string filename;

    if ((filename = QFileDialog::getSaveFileName(this, tr("Save Image to File"), "", tr("Image Files (*.jpg *.png *.bmp)")).toStdString()) != "") {
        saveImageToFile(filename);
    }
}

void mainForm::generateMosaicSlot() {
    bool ok;
    generateMosaic(widget.lineEdit_BlkWidth->text().toInt(&ok, 10), this->blockHeight);
    this->isMosaicGenerated = true;
    image* myImage = displayImage();
    if (myImage && myImage->getPixels()) {
        widget.lineEdit_BlkWidth->setDisabled(true);
        disableGenerateMosaic();
        showImage(myImage);
    } else {
        cout << "The image could not be displayed because there is no pixel data!" << endl;
    }
}

void mainForm::setBlockWidth(int width) {
    int newWidth = int(this->origImageWidth / width * FILLER_IMAGE_WIDTH);
    int height = int(ceil(float(width) * (float(FILLER_IMAGE_HEIGHT) / float(FILLER_IMAGE_WIDTH))));
    if (!height)
        height = 1;
    this->blockHeight = height;
    int newHeight = int(this->origImageHeight / height * FILLER_IMAGE_HEIGHT);
    char buffer[20];
    sprintf(buffer, "%d px", newHeight);
    widget.label_height_New->setText(QString(buffer));

    sprintf(buffer, "%d px", newWidth);
    widget.label_width_New->setText(QString(buffer));

    sprintf(buffer, "%d px", height);
    widget.label_height_Blk->setText(QString(buffer));
}

void mainForm::disableGenerateMosaic() {
    widget.generateMosaicBtn->setDisabled(true);

    if (!this->isMosaicGenerated) {
        widget.label_height_New->setText("N/A");
        widget.label_width_New->setText("N/A");
        widget.label_height_Blk->setText("N/A");
        widget.lineEdit_BlkWidth->setText("0");
    }
}

void mainForm::enableGenerateMosaic() {
    if (!this->isMosaicGenerated && mainForm::fillerImagesLoaded && imageLoaded())
        widget.generateMosaicBtn->setDisabled(false);
}

void mainForm::showImage(image* myImage) {
    if (myImage->getPixels() && myImage->getHeight() && myImage->getWidth()) {
        QImage out(myImage->getWidth(), myImage->getHeight(), QImage::Format_RGB32);
        widget.label_Image->setScaledContents(true); // TODO check this
        myImage->viewImage(&out);
        widget.label_Image->setPixmap(QPixmap::fromImage(out));

    }
}

void mainForm::updateSizeInfo(QString newString) {
    bool ok;
    int value = newString.toInt(&ok, 10);

    if (value && !this->isMosaicGenerated) {
        if (value > this->origImageHeight)
            value = origImageHeight;
        if (value > this->origImageWidth)
            value = origImageWidth;
        char buffer[20];
        sprintf(buffer, "%d", value);
        widget.lineEdit_BlkWidth->setText(QString(buffer));

        setBlockWidth(value);
        enableGenerateMosaic();
    } else {
        disableGenerateMosaic();
    }
}