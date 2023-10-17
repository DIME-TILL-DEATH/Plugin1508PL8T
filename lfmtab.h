#ifndef LFMTAB_H
#define LFMTAB_H

#include <QtWidgets>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "writefieldstructure.h"

class LFMTab : public QWidget
{
    Q_OBJECT
public:
    explicit LFMTab(QWidget *parent = nullptr);

    QMap<QString, QString> getSaveData();
    void setLoadData(const QMap<QString, QString>& dataToLoad);

private:
    QGridLayout* mainGrid;

    QLineEdit* frqEdit;

    QGridLayout* gridStage1;
    QLineEdit* lenghtEditStage1;
    QLineEdit* lowFrqEditStage1;
    QLineEdit* highFrqEditStage1;

    QGridLayout* gridStage2;
    QLineEdit* lenghtEditStage2;

    QGridLayout* gridStage3;
    QLineEdit* lenghtEditStage3;
    QLineEdit* lowFrqEditStage3;
    QLineEdit* highFrqEditStage3;

    QGridLayout* gridStage4;
    QLineEdit* lenghtEditStage4;

    QPushButton btnSetReg{tr("Установить регистры")};
    QCheckBox checkDeviceWrite{tr("Записть в устройство")};

    QCheckBox checkCh1{tr("Канал 1")};
    QCheckBox checkCh2{tr("Канал 2")};

    QListWidget* listView;

signals:
    void setLfmFields(std::vector<WriteFieldStructure> data, bool writeToDevice);
public slots:
    void btnSetFields();
};

#endif // LFMTAB_H
