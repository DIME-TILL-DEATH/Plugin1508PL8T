#include "lfmtab.h"

LFMTab::LFMTab(QWidget *parent)
    : QWidget(parent),
      mainGrid{new QGridLayout()},
      frqEdit{new QLineEdit()},
      gridStage1{new QGridLayout()},
      lenghtEditStage1{new QLineEdit()},
      lowFrqEditStage1{new QLineEdit()},
      highFrqEditStage1{new QLineEdit()},
      gridStage2{new QGridLayout()},
      lenghtEditStage2{new QLineEdit()},
      gridStage3{new QGridLayout()},
      lenghtEditStage3{new QLineEdit()},
      lowFrqEditStage3{new QLineEdit()},
      highFrqEditStage3{new QLineEdit()},
      gridStage4{new QGridLayout()},
      lenghtEditStage4{new QLineEdit()},
      listView{new QListWidget()}
{
    this->setLayout(mainGrid);

    mainGrid->addWidget(new QLabel(tr("Тактовая частота")), 0,0);
    mainGrid->addWidget(frqEdit, 0, 1);
    frqEdit->setText("800e6");

    int gridHMargins = this->width()/100;
    int gridVMargins = this->height()/100;

    QFrame* frameStage1 = new QFrame();
    frameStage1->setFrameStyle(QFrame::Box | QFrame::Raised);
    mainGrid->addWidget(frameStage1, 1, 0, 1, 2);
    gridStage1->setContentsMargins(gridHMargins, gridVMargins, gridHMargins, gridVMargins);
    mainGrid->addLayout(gridStage1, 1, 0, 1, 2);
    gridStage1->addWidget(new QLabel(tr("Стадия 1")), 0, 0, 1, 2, Qt::AlignCenter);
    gridStage1->addWidget(new QLabel(tr("Длительность стадии")), 1, 0);
    gridStage1->addWidget(lenghtEditStage1, 1, 1);
    lenghtEditStage1->setText("100e-6");
    gridStage1->addWidget(new QLabel(tr("Начальная частота ЛЧМ")), 2, 0);
    gridStage1->addWidget(lowFrqEditStage1, 2, 1);
    lowFrqEditStage1->setText("10e6");
    gridStage1->addWidget(new QLabel(tr("Конечная частота ЛЧМ")), 3, 0);
    gridStage1->addWidget(highFrqEditStage1, 3, 1);
    highFrqEditStage1->setText("50e6");

    QFrame* frameStage2 = new QFrame();
    frameStage2->setFrameStyle(QFrame::Box | QFrame::Raised);
    mainGrid->addWidget(frameStage2, 2, 0, 1, 2);
    gridStage2->setContentsMargins(gridHMargins, gridVMargins, gridHMargins, gridVMargins);
    mainGrid->addLayout(gridStage2, 2, 0, 1, 2);
    gridStage2->addWidget(new QLabel(tr("Стадия 2")), 0, 0, 1, 2, Qt::AlignCenter);
    gridStage2->addWidget(new QLabel(tr("Длительность стадии")), 1, 0);
    gridStage2->addWidget(lenghtEditStage2, 1, 1);
    lenghtEditStage2->setText("1000e-6");

    QFrame* frameStage3 = new QFrame();
    frameStage3->setFrameStyle(QFrame::Box | QFrame::Raised);
    mainGrid->addWidget(frameStage3, 3, 0, 1, 2);
    mainGrid->addLayout(gridStage3, 3, 0, 1, 2);
    gridStage3->setContentsMargins(gridHMargins, gridVMargins, gridHMargins, gridVMargins);
    gridStage3->addWidget(new QLabel(tr("Стадия 3")), 0, 0, 1, 2, Qt::AlignCenter);
    gridStage3->addWidget(new QLabel(tr("Длительность стадии")), 1, 0);
    gridStage3->addWidget(lenghtEditStage3, 1, 1);
    lenghtEditStage3->setText("0");
    gridStage3->addWidget(new QLabel(tr("Начальная частота ЛЧМ")), 2, 0);
    gridStage3->addWidget(lowFrqEditStage3, 2, 1);
    lowFrqEditStage3->setText("10e6");
    gridStage3->addWidget(new QLabel(tr("Конечная частота ЛЧМ")), 3, 0);
    gridStage3->addWidget(highFrqEditStage3, 3, 1);
    highFrqEditStage3->setText("50e6");

    QFrame* frameStage4 = new QFrame();
    frameStage4->setFrameStyle(QFrame::Box | QFrame::Raised);
    mainGrid->addWidget(frameStage4, 4, 0, 1, 2);
    gridStage4->setContentsMargins(gridHMargins, gridVMargins, gridHMargins, gridVMargins);
    mainGrid->addLayout(gridStage4, 4, 0, 1, 2);
    gridStage4->addWidget(new QLabel(tr("Стадия 4")), 0, 0, 1, 2, Qt::AlignCenter);
    gridStage4->addWidget(new QLabel(tr("Длительность стадии")), 1, 0);
    gridStage4->addWidget(lenghtEditStage4, 1, 1);
    lenghtEditStage4->setText("0");

    checkCh1.setChecked(true);
    checkCh2.setChecked(true);
    mainGrid->addWidget(&checkCh1, 5, 0);
    mainGrid->addWidget(&checkCh2, 5, 1);

    checkDeviceWrite.setChecked(true);
    mainGrid->addWidget(&btnSetReg, 6,0);
    mainGrid->addWidget(&checkDeviceWrite, 6,1);

    mainGrid->addWidget(listView, 7, 0, 1, 2, Qt::AlignCenter);

    connect(&btnSetReg, &QPushButton::clicked, this, &LFMTab::btnSetFields);
}

QMap<QString, QString> LFMTab::getSaveData()
{
    QMap<QString, QString> dataToSave;

    dataToSave["ЛЧМ_частота"] = frqEdit->text();

    dataToSave["ЛЧМ_длительность_стадия1"] = lenghtEditStage1->text();
    dataToSave["ЛЧМ_нижняя_частота_стадия1"] = lowFrqEditStage1->text();
    dataToSave["ЛЧМ_верхняя_частота_стадия1"] = highFrqEditStage1->text();

    dataToSave["ЛЧМ_длительность_стадия2"] = lenghtEditStage2->text();

    dataToSave["ЛЧМ_длительность_стадия3"] = lenghtEditStage3->text();
    dataToSave["ЛЧМ_нижняя_частота_стадия3"] = lowFrqEditStage3->text();
    dataToSave["ЛЧМ_верхняя_частота_стадия3"] = highFrqEditStage3->text();

    dataToSave["ЛЧМ_длительность_стадия4"] = lenghtEditStage4->text();

    dataToSave["ЛЧМ_канал_1_check"] = checkCh1.isChecked();
    dataToSave["ЛЧМ_канал_2_check"] = checkCh2.isChecked();

    return dataToSave;
}

void LFMTab::setLoadData(const QMap<QString, QString> &dataToLoad)
{
    frqEdit->setText(dataToLoad["ЛЧМ_частота"]);

    lenghtEditStage1->setText(dataToLoad["ЛЧМ_длительность_стадия1"]);
    lowFrqEditStage1->setText(dataToLoad["ЛЧМ_нижняя_частота_стадия1"]);
    highFrqEditStage1->setText(dataToLoad["ЛЧМ_верхняя_частота_стадия1"]);

    lenghtEditStage2->setText(dataToLoad["ЛЧМ_длительность_стадия2"]);

    lenghtEditStage3->setText(dataToLoad["ЛЧМ_длительность_стадия3"]);
    lowFrqEditStage3->setText(dataToLoad["ЛЧМ_нижняя_частота_стадия3"]);
    highFrqEditStage3->setText(dataToLoad["ЛЧМ_верхняя_частота_стадия3"]);

    lenghtEditStage4->setText(dataToLoad["ЛЧМ_длительность_стадия4"]);

    checkCh1.setCheckState(dataToLoad["ЛЧМ_канал_1_check"] == "\u0001" ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    checkCh2.setCheckState(dataToLoad["ЛЧМ_канал_2_check"] == "\u0001" ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void LFMTab::btnSetFields()
{
    listView->clear();

    QStringList list;
    list << QDateTime::currentDateTime().toString();
    list << "";

    bool convResult;
    double fClk = frqEdit->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Частота тактирования задана неверно";
        listView->addItems(list);
        return;
    }

    double tStage1 = lenghtEditStage1->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Длительность первой стадии задана неверно";
        listView->addItems(list);
        return;
    }
    double tStage2 = lenghtEditStage2->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Длительность второй стадии задана неверно";
        listView->addItems(list);
        return;
    }
    double tStage3 = lenghtEditStage3->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Длительность третьей стадии задана неверно";
        listView->addItems(list);
        return;
    }
    double tStage4 = lenghtEditStage4->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Длительность четвёртой стадии задана неверно";
        listView->addItems(list);
        return;
    }

    qulonglong resultTPH1 = tStage1*fClk/4;
    list << "TPH1: " + QString().setNum(resultTPH1, 16);
    qulonglong resultTPH2 = tStage2*fClk/4;
    list << "TPH2: " + QString().setNum(resultTPH2, 16);
    qulonglong resultTPH3 = tStage3*fClk/4;
    list << "TPH3: " + QString().setNum(resultTPH3, 16);
    qulonglong resultTPH4 = tStage4*fClk/4;
    list << "TPH4: " + QString().setNum(resultTPH4, 16);

    double fStartStage1 = lowFrqEditStage1->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Начальная частота стадии 1 задана неверно";
        listView->addItems(list);
        return;
    }
    double fStartStage3 = lowFrqEditStage3->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Начальная частота стадии 3 задана неверно";
        listView->addItems(list);
        return;
    }

    qulonglong resultChLsF1 = (fStartStage1/fClk) * pow(2, 48);
    list << "CH1 LS F1: " + QString().setNum(resultChLsF1, 16);
    qulonglong resultChLsF3 = (fStartStage3/fClk) * pow(2, 48);
    list << "CH1 LS F2: " + QString().setNum(resultChLsF3, 16);

    double fEndStage1 = highFrqEditStage1->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Конечная частота стадии 1 задана неверно";
        listView->addItems(list);
        return;
    }
    double fEndStage3 = highFrqEditStage3->text().toDouble(&convResult);
    if(!convResult)
    {
        list << "Конечная частота стадии 3 задана неверно";
        listView->addItems(list);
        return;
    }

    qlonglong resultChLsdF1 = ((fEndStage1-fStartStage1)/(tStage1*fClk/4))*pow(2, 48)/fClk;
    list << "CH1 LS dF1: " + QString().setNum(resultChLsdF1, 16);
    qlonglong resultChLsdF3 = ((fEndStage3-fStartStage3)/(tStage3*fClk/4))*pow(2, 48)/fClk;
    list << "CH1 LS dF2: " + QString().setNum(resultChLsdF3, 16);

    // TODO переключение в режим ЛЧМ, отключение сигнала во 2й и 4й стадии, нулевая начальная фаза
    std::vector<WriteFieldStructure> dataToSend;
    if(checkCh1.isChecked())
    {
        dataToSend.push_back({"CH1 LS TPH1", "СH1 LS TPH1 L", (resultTPH1)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH1", "СH1 LS TPH1 M", (resultTPH1 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH1", "СH1 LS TPH1 H", (resultTPH1 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS TPH2", "СH1 LS TPH2 L", (resultTPH2)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH2", "СH1 LS TPH2 M", (resultTPH2 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH2", "СH1 LS TPH2 H", (resultTPH2 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS TPH3", "СH1 LS TPH3 L", (resultTPH3)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH3", "СH1 LS TPH3 M", (resultTPH3 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH3", "СH1 LS TPH3 H", (resultTPH3 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS TPH4", "СH1 LS TPH4 L", (resultTPH4)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH4", "СH1 LS TPH4 M", (resultTPH4 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS TPH4", "СH1 LS TPH4 H", (resultTPH4 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS F1", "СH1 LS F1 L", (resultChLsF1)&0xFFFF});
        dataToSend.push_back({"CH1 LS F1", "СH1 LS F1 M", (resultChLsF1 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS F1", "СH1 LS F1 H", (resultChLsF1 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS F2", "СH1 LS F2 L", (resultChLsF3)&0xFFFF});
        dataToSend.push_back({"CH1 LS F2", "СH1 LS F2 M", (resultChLsF3 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS F2", "СH1 LS F2 H", (resultChLsF3 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS dF1", "СH1 LS dF1 L", (resultChLsdF1)&0xFFFF});
        dataToSend.push_back({"CH1 LS dF1", "СH1 LS dF1 M", (resultChLsdF1 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS dF1", "СH1 LS dF1 H", (resultChLsdF1 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS dF2", "СH1 LS dF2 L", (resultChLsdF3)&0xFFFF});
        dataToSend.push_back({"CH1 LS dF2", "СH1 LS dF2 M", (resultChLsdF3 >> 16)&0xFFFF});
        dataToSend.push_back({"CH1 LS dF2", "СH1 LS dF2 H", (resultChLsdF3 >> 32)&0xFFFF});

        dataToSend.push_back({"CH1 LS CTR","frq reset 3", true});
        dataToSend.push_back({"CH1 LS CTR","frq reset 1", true});
        dataToSend.push_back({"CH1 LS CTR","ph reset 3", true});
        dataToSend.push_back({"CH1 LS CTR","ph reset 1", true});
        dataToSend.push_back({"CH1 LS CTR","auto", true});

        dataToSend.push_back({"CLR","LS1 start", true});

        dataToSend.push_back({"CH1 LS CTR","LS on", true});

        list << "Установлено в регистры:\nCH1 LS TPH1...TPH4\nCH1 LS F1...F2\nCH1 LS dF1...dF2\nCh1 LS CTR";
        list << "";
    }

    if(checkCh2.isChecked())
    {
        dataToSend.push_back({"CH2 LS TPH1", "СH2 LS TPH1 H", (resultTPH1 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH1", "СH2 LS TPH1 M", (resultTPH1 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH1", "СH2 LS TPH1 L", (resultTPH1)&0xFFFF});

        dataToSend.push_back({"CH2 LS TPH2", "СH2 LS TPH2 H", (resultTPH2 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH2", "СH2 LS TPH2 M", (resultTPH2 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH2", "СH2 LS TPH2 L", (resultTPH2)&0xFFFF});

        dataToSend.push_back({"CH2 LS TPH3", "СH2 LS TPH3 H", (resultTPH3 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH3", "СH2 LS TPH3 M", (resultTPH3 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH3", "СH2 LS TPH3 L", (resultTPH3)&0xFFFF});

        dataToSend.push_back({"CH2 LS TPH4", "СH2 LS TPH4 H", (resultTPH4 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH4", "СH2 LS TPH4 M", (resultTPH4 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS TPH4", "СH2 LS TPH4 L", (resultTPH4)&0xFFFF});

        dataToSend.push_back({"CH2 LS F1", "СH2 LS F1 H", (resultChLsF1 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS F1", "СH2 LS F1 M", (resultChLsF1 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS F1", "СH2 LS F1 L", (resultChLsF1)&0xFFFF});

        dataToSend.push_back({"CH2 LS F2", "СH2 LS F2 H", (resultChLsF3 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS F2", "СH2 LS F2 M", (resultChLsF3 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS F2", "СH2 LS F2 L", (resultChLsF3)&0xFFFF});

        dataToSend.push_back({"CH2 LS dF1", "СH2 LS dF1 H", (resultChLsdF1 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS dF1", "СH2 LS dF1 M", (resultChLsdF1 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS dF1", "СH2 LS dF1 L", (resultChLsdF1)&0xFFFF});

        dataToSend.push_back({"CH2 LS dF2", "СH2 LS dF2 H", (resultChLsdF3 >> 32)&0xFFFF});
        dataToSend.push_back({"CH2 LS dF2", "СH2 LS dF2 M", (resultChLsdF3 >> 16)&0xFFFF});
        dataToSend.push_back({"CH2 LS dF2", "СH2 LS dF2 L", (resultChLsdF3)&0xFFFF});

        dataToSend.push_back({"CH2 LS CTR","frq reset 3", true});
        dataToSend.push_back({"CH2 LS CTR","frq reset 1", true});
        dataToSend.push_back({"CH2 LS CTR","ph reset 3", true});
        dataToSend.push_back({"CH2 LS CTR","ph reset 1", true});
        dataToSend.push_back({"CH2 LS CTR","auto", true});

        dataToSend.push_back({"CLR","LS2 start", true});

        dataToSend.push_back({"CH2 LS CTR","LS on", true});
        list << "Установлено в регистры:\nCH2 LS TPH1...TPH4\nCH2 LS F1...F2\nCH2 LS dF1...dF2\nCh2 LS CTR";
        list << "";
    }

    listView->addItems(list);
    listView->scrollToBottom();

    emit setLfmFields(dataToSend, checkDeviceWrite.checkState());
}
