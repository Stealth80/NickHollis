#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include "ui_mainForm.h"
#include <iostream>
#include "image.h"

using namespace std;

class mainForm : public QDialog {
    Q_OBJECT
public:
    mainForm();
    void InitializeComponent();
    virtual ~mainForm();

private:
    Ui::mainForm widget;
    int origImageWidth;
    int origImageHeight;
    int blockHeight;
    bool isMosaicGenerated;
    static bool fillerImagesLoaded;

    void setBlockWidth(int width);
    void disableGenerateMosaic();
    void enableGenerateMosaic();
    void showImage(image* myImage);

public slots:
    void openFileDialog();
    void loadImagesDialog();
    void generateMosaicSlot();
    void saveFileDialog();
    void updateSizeInfo(QString newString);
};

#endif	/* _MAINFORM_H */

