#include "comboboxdelegate.h"
#include <QComboBox>
#include <QDebug>


ComboBoxDelegate::ComboBoxDelegate(QObject *parent) :
QItemDelegate(parent)
{
}

ComboBoxDelegate::~ComboBoxDelegate()
{
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
const QStyleOptionViewItem &,
const QModelIndex &) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("Not done");
    editor->addItem("Done");
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
