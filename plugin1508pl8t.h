#ifndef PLUGIN1508PL8T_H
#define PLUGIN1508PL8T_H

#include <QtWidgets>
#include <QMainWindow>

#include <QtPlugin>
#include <QObject>
#include <QDebug>

#include "controlpanelinterface.h"

#include "writefieldstructure.h"
#include "sinetab.h"
#include "lfmtab.h"


class Plugin1508PL8T : public QMainWindow, public ControlPanelInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "com.vniirt.controlpanel")
    Q_INTERFACES(ControlPanelInterface)

public:
    explicit Plugin1508PL8T(QWidget *parent = nullptr);
    ~Plugin1508PL8T() {};

    void showPanel() override;
    void closePanel() override;

    void setTargetDeviceNumber(quint16 number) override;
    quint16 targetDeviceNumber() override;

signals:
    void setFieldValue(QString registerName, QString fieldName, QVariant value) override;
    void getFieldValue(QString registerName, QString fieldName, QVariant& value) override;
    void writeRegisterSequence(QStringList registerNames) override;
    void writeRegisterSequence() override;

public slots:

    void setFields(std::vector<WriteFieldStructure> dataToSet, bool writeToDevice);

    void saveRequest(QString plugInName, QMap<QString, QString>& dataToSave) override;
    void loadRequest(QString plugInName, const QMap<QString, QString>& dataToLoad) override;

private:
    QString m_name = "Контрольная панель 1508ПЛ8Т";
    quint16 m_pluginNumber;

    QTabWidget tabWidget;

    SineTab* sineTab;
    LFMTab* lfmTab;
};

#endif // PLUGIN1508PL8T_H
