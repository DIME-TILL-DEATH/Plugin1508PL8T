#include "sinetab.h"

SineTab::SineTab(QWidget *parent)
    : QWidget(parent),
      mainGrid{new QGridLayout()}
{
    this->setLayout(mainGrid);

    quint16 rowNum = 0;

    mainGrid->addWidget(&clkFrqEdit, rowNum, 1);
    mainGrid->addWidget(new QLabel(tr("Тактовая частота, Гц"), this), rowNum++, 0);

    QLabel* modeLabel = new QLabel{tr("Режим:"), this};
    modeLabel->setFixedHeight(20);
    mainGrid->addWidget(modeLabel, rowNum++, 0, 1, 2, Qt::AlignHCenter);

    mainGrid->addWidget(&modeDivider, rowNum, 0);
    mainGrid->addWidget(&divEdit, rowNum++, 1);

    mainGrid->addWidget(&modeFreq, rowNum, 0);
    mainGrid->addWidget(&outFrqEdit, rowNum++, 1);

    QLabel* phaseLabel = new QLabel{tr("Начальная фаза, град:"), this};
    mainGrid->addWidget(phaseLabel, rowNum, 0);
    mainGrid->addWidget(&phaseEdit, rowNum++, 1);

   // mainGrid->addWidget(new QLabel(tr("Коэффициент деления")), rowNum++, 0);

    clkFrqEdit.setText("800e6");
    divEdit.setText("4");
    outFrqEdit.setText("200e6");
    phaseEdit.setText("0");
    modeDivider.setChecked(true);

    mainGrid->addWidget(&btnSetReg, rowNum, 0);
    mainGrid->addWidget(&checkDeviceWrite, rowNum++, 1);
    checkDeviceWrite.setChecked(true);

    checkCh1.setChecked(true);
    checkCh2.setChecked(true);
    mainGrid->addWidget(&checkCh1, rowNum, 0);
    mainGrid->addWidget(&checkCh2, rowNum++, 1);

    mainGrid->addWidget(&listView, rowNum++, 0, 1, 2, Qt::AlignCenter);

    connect(&btnSetReg, &QPushButton::clicked, this, &SineTab::btnSetFields);
}

QMap<QString, QString> SineTab::getSaveData()
{
    QMap<QString, QString> dataToSave;

    dataToSave["Синус_частота"] = clkFrqEdit.text();
    dataToSave["Синус_деление"] = divEdit.text();
    dataToSave["Синус_выходная_частота"] = outFrqEdit.text();
    dataToSave["Начальная_фаза"] = phaseEdit.text();

    dataToSave["Синус_канал_1_check"] = checkCh1.isChecked();
    dataToSave["Синус_канал_2_check"] = checkCh2.isChecked();

    return dataToSave;
}

void SineTab::setLoadData(const QMap<QString, QString>& dataToLoad)
{
    QString loadedData;

    loadedData = dataToLoad["Синус_частота"];
    if(loadedData != "") clkFrqEdit.setText(loadedData);

    loadedData = dataToLoad["Синус_деление"];
    if(loadedData != "") divEdit.setText(loadedData);

    loadedData = dataToLoad["Синус_выходная_частота"];
    if(loadedData != "") outFrqEdit.setText(loadedData);

    loadedData = dataToLoad["Начальная_фаза"];
    if(loadedData != "") phaseEdit.setText(loadedData);

    checkCh1.setCheckState(dataToLoad["Синус_канал_1_check"] == "\u0001" ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    checkCh2.setCheckState(dataToLoad["Синус_канал_2_check"] == "\u0001" ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void SineTab::btnSetFields()
{
    listView.clear();

    QStringList list;
    list << QDateTime::currentDateTime().toString();
    list << "";

    bool convResult;
    double clkFrq = clkFrqEdit.text().toDouble(&convResult);

    if(!convResult)
    {
        list << "Частота тактирования задана неверно";
        listView.addItems(list);
        return;
    }

    double divider = divEdit.text().toDouble(&convResult);

    if(!convResult)
    {
        list << "Делитель задан неверно";
        listView.addItems(list);
        return;
    }

    double resultFrequency;
    if(modeDivider.isChecked())
    {
        resultFrequency = clkFrq/divider;
        outFrqEdit.setText(QString::number(resultFrequency, 'g', 8));
    }
    else
    {
        resultFrequency = outFrqEdit.text().toDouble(&convResult);
        if(!convResult)
        {
            list << "Выходная частота задана неверно";
            listView.addItems(list);
            return;
        }
        divider = clkFrq/resultFrequency;
        divEdit.setText(QString::number(divider, 'g', 8));
    }
    list << "Результирующая частота: " + QString().setNum(resultFrequency) + " Гц";


    double phaseDeg = phaseEdit.text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Начальная фаза задана неверно";
        listView.addItems(list);
        return;
    }

    qulonglong freqControlWord = (resultFrequency/clkFrq) * pow(2, 48);

    list << "Управляющее слово частоты: 0x" + QString().setNum(freqControlWord, 16);
    list << "";


    double phaseRad = (phaseDeg * (2*M_PI)) / 360;
    qint16 phaseControlWord = phaseRad * pow(2, 15) / M_PI;

    list << "Управляющее слово фазы: 0x" + QString().setNum(phaseControlWord&0xFFFF, 16);
                                                  list << "";

    std::vector<WriteFieldStructure> dataToSend;
    if(checkCh1.isChecked())
    {
        dataToSend.push_back({"CH1 LS CTR","LS on", false});

        dataToSend.push_back({"CH1 profile", "dPh H", (freqControlWord >> 32)&0xFFFF});
        dataToSend.push_back({"CH1 profile", "dPh M", (freqControlWord >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 profile", "dPh L", (freqControlWord)&0xFFFF});

        dataToSend.push_back({"CH1 profile", "Phase", phaseControlWord&0xFFFF});

        list << "Установлено в регистр CH1 profile";
        list << "";
    }

    if(checkCh2.isChecked())
    {
        dataToSend.push_back({"CH2 LS CTR","LS on", false});

        dataToSend.push_back({"CH2 profile", "dPh H", (freqControlWord >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 profile", "dPh M", (freqControlWord >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 profile", "dPh L", (freqControlWord)&0xFFFF});

        dataToSend.push_back({"CH2 profile", "Phase", phaseControlWord});

        list << "Установлено в регистр CH2 profile";
        list << "";
    }

    listView.addItems(list);
    listView.scrollToBottom();

    emit setSineFields(dataToSend, checkDeviceWrite.checkState());
}
