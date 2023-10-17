#include "sinetab.h"

SineTab::SineTab(QWidget *parent)
    : QWidget(parent),
      mainGrid{new QGridLayout()}
{
    this->setLayout(mainGrid);

    quint16 rowNum = 0;

    mainGrid->addWidget(&clkFrqEdit, rowNum, 1);
    mainGrid->addWidget(new QLabel(tr("Тактовая частота")), rowNum++, 0);

    QLabel* modeLabel = new QLabel{tr("Режим:")};
    modeLabel->setFixedHeight(20);
    mainGrid->addWidget(modeLabel, rowNum++, 0, 1, 2, Qt::AlignHCenter);

    mainGrid->addWidget(&modeDivider, rowNum, 0);
    mainGrid->addWidget(&divEdit, rowNum++, 1);

    mainGrid->addWidget(&modeFreq, rowNum, 0);
    mainGrid->addWidget(&outFrqEdit, rowNum++, 1);

   // mainGrid->addWidget(new QLabel(tr("Коэффициент деления")), rowNum++, 0);

    clkFrqEdit.setText("800e6");
    divEdit.setText("4");
    outFrqEdit.setText("200e6");
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

    dataToSave["Синус_канал_1_check"] = checkCh1.isChecked();
    dataToSave["Синус_канал_2_check"] = checkCh2.isChecked();

    return dataToSave;
}

void SineTab::setLoadData(const QMap<QString, QString>& dataToLoad)
{
    QString loadedData;


    clkFrqEdit.setText(dataToLoad["Синус_частота"]);
    divEdit.setText(dataToLoad["Синус_деление"]);

    loadedData = dataToLoad["Синус_выходная_частота"];
    if(loadedData != "") outFrqEdit.setText(loadedData);

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

    qulonglong controlWord = (resultFrequency/clkFrq) * pow(2, 48);

    list << "Управляющее слово: 0x" + QString().setNum(controlWord, 16);
    list << "";

    std::vector<WriteFieldStructure> dataToSend;
    if(checkCh1.isChecked())
    {
        dataToSend.push_back({"CH1 LS CTR","LS on", false});

        dataToSend.push_back({"CH1 profile", "dPh H", (controlWord >> 32)&0xFFFF});
        dataToSend.push_back({"CH1 profile", "dPh M", (controlWord >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 profile", "dPh L", (controlWord)&0xFFFF});

        list << "Установлено в регистр CH1 profile";
        list << "";
    }

    if(checkCh2.isChecked())
    {
        dataToSend.push_back({"CH2 LS CTR","LS on", false});

        dataToSend.push_back({"CH2 profile", "dPh H", (controlWord >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 profile", "dPh M", (controlWord >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 profile", "dPh L", (controlWord)&0xFFFF});

        list << "Установлено в регистр CH2 profile";
        list << "";
    }

    listView.addItems(list);
    listView.scrollToBottom();

    emit setSineFields(dataToSend, checkDeviceWrite.checkState());
}
