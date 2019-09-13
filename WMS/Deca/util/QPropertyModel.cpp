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

#include "QPropertyModel.h"

#include <QDataWidgetMapper>
#include <QMetaProperty>
#include <QSignalMapper>
#include <QDebug>

QPropertyModel::QPropertyModel(QObject *source, QObject *parent) :
    QAbstractItemModel(parent),
    _source(source)
{
    connectToPropertyNotifySignals();
}

QPropertyDataWidgetMapper *QPropertyModel::newMapper(QObject *source, QObject *parent)
{
    QPropertyDataWidgetMapper *_mapper = new QPropertyDataWidgetMapper(parent);
    _mapper->setModel(new QPropertyModel(source, parent));
    return _mapper;
}

QPropertyDataWidgetMapper *QPropertyModel::newMapper()
{
    QPropertyDataWidgetMapper *_mapper = new QPropertyDataWidgetMapper(this);
    _mapper->setModel(this);
    return _mapper;
}

QStringList QPropertyModel::propertyNames() const
{
    static QStringList names;
    if (names.size())
        return names;

    foreach (const QMetaProperty &p, properties().values())
        names << QString::fromLatin1(p.name());
    return names;
}

int QPropertyModel::columnForProperty(QString name) const
{
    QMap<int, QMetaProperty> props = properties();
    foreach (int index, props.keys())
        if (props[index].name() == name)
        {
            return index;
        }
    qDebug("No property \"%s\" found!", qPrintable(name));
    return -1;
}

QMap<int, QMetaProperty> QPropertyModel::properties() const
{
    // TODO: should we filter out properties with no NOTIFY? Otherwise, how will
    // we know when they change? Maybe it doesn't matter. Just let the user
    // any QObject they want and deal with the consequences of the features
    // that their QObject properties support.
    static QMap<int, QMetaProperty> properties;
    if (properties.size())
        return properties;

    // Save a map of properties
    const QMetaObject* metaObject = _source->metaObject();
    // Start at 0 to get all inherited properties, too. Start at the offset for just this
    // subclass.
    // for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
    for(int i = 0; i < metaObject->propertyCount(); ++i)
        properties.insert(i, metaObject->property(i));
    return properties;
}

void QPropertyModel::connectToPropertyNotifySignals()
{
    QMap<int, QMetaProperty> props = properties();
    foreach (int index, props.keys()) {
        if (!props[index].hasNotifySignal())
            continue;

        _signalToColumnMap.insert(props[index].notifySignal().methodIndex(), index);
        connect(_source, props[index].notifySignal(),
                this, metaObject()->method(metaObject()->indexOfMethod("propertyChanged()")));
    }
}

void QPropertyModel::propertyChanged()
{
    //qDebug("columnChanged(%d)", column);
    int column = _signalToColumnMap.value(senderSignalIndex(), -1);
    if (column != -1)
    {
        QModelIndex index = createIndex(0, column);
        emit dataChanged(index, index);
    }
}

QVariant QPropertyModel::data(const QModelIndex& index, int role) const {
    Q_UNUSED(role)
    //qDebug() << "data(" << index << "," << role << ")";
    if (!hasIndex(index))
        return QVariant();

    return _source->property(properties().value(index.column()).name());
}

bool QPropertyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    //qDebug() << "setData(" << index << "," << value << "," << role << ")";
    if (!hasIndex(index) || role != Qt::EditRole)
        return QAbstractItemModel::setData(index, value, role);

    QMetaProperty mp = properties().value(index.column());
    bool rc = _source->setProperty(mp.name(), value);
    if (rc && !mp.hasNotifySignal())
        // property doesn't support NOTIFY, emit dataChanged()
        emit dataChanged(index, index);
    return rc;
}

int QPropertyModel::columnCount(const QModelIndex &/*parent*/) const {
    return properties().size();
}

int QPropertyModel::rowCount(const QModelIndex &/*parent*/) const {
    return 1;
}

Qt::ItemFlags QPropertyModel::flags(const QModelIndex &index) const {
    QMetaProperty mp = properties().value(index.column());
    return QAbstractItemModel::flags(index)
            | Qt::ItemIsSelectable
            | Qt::ItemIsEnabled
            | mp.isWritable() ? Qt::ItemIsEditable : Qt::NoItemFlags;
}

QModelIndex QPropertyModel::parent(const QModelIndex &/*child*/) const {
    return QModelIndex();
}

QModelIndex QPropertyModel::index(int row, int column, const QModelIndex &parent) const {
    if (QAbstractItemModel::hasIndex(row, column, parent))
        return createIndex(row, column);
    return QModelIndex();
}

bool QPropertyModel::hasIndex(const QModelIndex &index) const {
    return QAbstractItemModel::hasIndex(index.row(), index.column(), index.parent());
}

QPropertyModel *QPropertyDataWidgetMapper::model() const
{
    return qobject_cast<QPropertyModel*>(QDataWidgetMapper::model());
}

void QPropertyDataWidgetMapper::addMapping(QWidget *widget, QString property)
{
    if (model() && model()->columnForProperty(property) >= 0)
        QDataWidgetMapper::addMapping(widget, model()->columnForProperty(property));
}

void QPropertyDataWidgetMapper::addMapping(QWidget *widget, QString property, const QByteArray &propertyName)
{
    if (model() && model()->columnForProperty(property) >= 0)
        QDataWidgetMapper::addMapping(widget, model()->columnForProperty(property), propertyName);
}

void QPropertyDataWidgetMapper::addMapping(QWidget *widget, int section)
{
    QDataWidgetMapper::addMapping(widget, section);
}

void QPropertyDataWidgetMapper::addMapping(QWidget *widget, int section, const QByteArray &propertyName)
{
    QDataWidgetMapper::addMapping(widget, section, propertyName);
}
