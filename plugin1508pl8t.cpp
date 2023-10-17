#include "plugin1508pl8t.h"

Plugin1508PL8T::Plugin1508PL8T(QWidget *parent)
    : QMainWindow{parent}
{
    setCentralWidget(&tabWidget);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    sineTab = new SineTab();
    tabWidget.addTab(sineTab, tr("Синус"));

    lfmTab = new LFMTab();
    tabWidget.addTab(lfmTab, tr("ЛЧМ"));

    connect(sineTab, &SineTab::setSineFields, this, &Plugin1508PL8T::setFields);
    connect(lfmTab, &LFMTab::setLfmFields, this, &Plugin1508PL8T::setFields);
}

void Plugin1508PL8T::showPanel()
{
    show();
}

void Plugin1508PL8T::closePanel()
{
    close();
}

void Plugin1508PL8T::setTargetDeviceNumber(quint16 number)
{
    m_pluginNumber = number;
}

quint16 Plugin1508PL8T::targetDeviceNumber()
{
    return m_pluginNumber;
}

void Plugin1508PL8T::setFields(std::vector<WriteFieldStructure> dataToSet, bool writeToDevice)
{
    QStringList registerNames;
    foreach(WriteFieldStructure fieldData, dataToSet)
    {
        registerNames << fieldData.registerName();
        emit setFieldValue(fieldData.registerName(), fieldData.fieldName(), fieldData.value());
    }

    if(writeToDevice)
    {
        registerNames.removeDuplicates();
        emit writeRegisterSequence(registerNames);
    }
}

void Plugin1508PL8T::saveRequest(QString plugInName, QMap<QString, QString> &dataToSave)
{
    if(plugInName == m_name)
    {
        dataToSave.clear();
        dataToSave.insert(sineTab->getSaveData());
        dataToSave.insert(lfmTab->getSaveData());
    }
}

void Plugin1508PL8T::loadRequest(QString plugInName, const QMap<QString, QString> &dataToLoad)
{
    if(plugInName == m_name)
    {
        sineTab->setLoadData(dataToLoad);
        lfmTab->setLoadData(dataToLoad);
    }
}
