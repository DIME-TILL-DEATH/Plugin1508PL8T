#ifndef SINETAB_H
#define SINETAB_H

#include <QtWidgets>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "writefieldstructure.h"

class SineTab : public QWidget
{
    Q_OBJECT

public:
    explicit SineTab(QWidget *parent = nullptr);

    QMap<QString, QString> getSaveData();
    void setLoadData(const QMap<QString, QString>& dataToLoad);

private:
    QGridLayout* mainGrid;

    QPushButton btnSetReg{tr("Установить регистры")};
    QCheckBox checkDeviceWrite{tr("Запись в устройство")};

    QRadioButton modeDivider{tr("Делитель")};
    QRadioButton modeFreq{tr("Выходная частота")};

    QLineEdit clkFrqEdit;
    QLineEdit divEdit;
    QLineEdit outFrqEdit;
    QLineEdit phaseEdit;

    QListWidget listView;

    QCheckBox checkCh1{tr("Канал 1")};
    QCheckBox checkCh2{tr("Канал 2")};

signals:
    void setSineFields(std::vector<WriteFieldStructure> data, bool writeToDevice);

public slots:
    void btnSetFields();
};

#endif // SINETAB_H
