#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>

class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ComboBoxDelegate(QObject* parent=0);
    ~ComboBoxDelegate();

    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // COMBOBOXDELEGATE_H
