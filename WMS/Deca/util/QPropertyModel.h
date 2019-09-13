// QPropertyModel
// - a class for easily turning any QObject-derived subclass with properties into a one-row model
//
// Copyright 2013 - Harvey Chapman <hchapman@3gfp.com>
// Source: https://gist.github.com/sr105/7955969
// License:
// This work is licensed under the Creative Commons Attribution-ShareAlike
// 4.0 International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by-sa/4.0/deed.en_US.
//
// It's not required, but I'd appreciate it if any improvements were e-mailed
// back to me so I can share them with others. This code is specifically not
// GPL-like so you can use it commercially without worrying about it tainting
// the rest of your proprietary code.
// -- Harvey

#ifndef QPROPERTYMODEL_H
#define QPROPERTYMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QDataWidgetMapper>

class QPropertyModel;

// Convenience class that exposes the public methods of QPropertyModel
// without requiring casting.
class QPropertyDataWidgetMapper : public QDataWidgetMapper
{
    Q_OBJECT
public:
    QPropertyDataWidgetMapper(QObject *parent = 0) : QDataWidgetMapper(parent) {}

    // QDataWidgetMapper::model() re-written to return QPropertyDataWidgetMapper
    QPropertyModel *model() const;
    // For convenience, these automatically convert "property" into column numbers
    void addMapping(QWidget *widget, QString property);
    void addMapping(QWidget *widget, QString property, const QByteArray &propertyName);
    // Pass-thru methods to QDataWidgetMapper
    void addMapping(QWidget *widget, int section);
    void addMapping(QWidget *widget, int section, const QByteArray &propertyName);
};

// QPropertyModel creates a single row data model consisting of columns mapping
// to properties in a QObject. The column list can be retrieved as a QStringList,
// and a method exists to convert the property names to column numbers.
class QPropertyModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit QPropertyModel(QObject *source, QObject *parent = 0);

    // Return a QPropertyDataWidgetMapper wrapping a new instance of this class.
    static QPropertyDataWidgetMapper *newMapper(QObject *source, QObject *parent = 0);
    // Return a QPropertyDataWidgetMapper wrapping this existing instance
    QPropertyDataWidgetMapper *newMapper();

    QStringList propertyNames() const;
    int columnForProperty(QString name) const;
    QMap<int, QMetaProperty> properties() const;

protected:
    void connectToPropertyNotifySignals();

    // Pointer to our data source
    QObject *_source;

    QMap<int, int> _signalToColumnMap;

protected slots:
    void propertyChanged();

    // Required virtual function implementations. They mostly map
    // directly to the (getItem/setItem/itemChanged) methods above.
public:
    // read & write data
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    // returns the number of properties in _source
    virtual int columnCount(const QModelIndex &parent) const;

    // all hard-coded simple implementations
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &) const;

    // Helper method to make virtual methods easier to code
    virtual bool hasIndex(const QModelIndex &index) const;
};

#endif // QPROPERTYMODEL_H
