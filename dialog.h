#ifndef DIALOG_H
#define DIALOG_H

#include "recipe.h"

#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void updateView();
    void updateForm();

private slots:

    void on_newButton_clicked();

    void on_openButton_clicked();

    void on_nextButton_clicked();

    void on_updateButton_clicked();

    void on_addIngridientButton_clicked();

    void on_addOperationButton_clicked();

    void on_popButton_clicked();

    void on_removeAllButton_clicked();

    void on_saveButton_clicked();

    void on_lowerSaveButton_clicked();

private:
    Ui::Dialog *ui;
    Recipe rec {};
    Recipe::iterator itr;
    int flagForAddition;
    QString recipeTitle;
};

#endif // DIALOG_H
