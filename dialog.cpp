#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->updateButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();
    recipeTitle = "untitled";
    ui->titleLabel->setText(recipeTitle + "   "
                            + QString::number(rec.size()) + " items");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateView()
{
    ui->listWidget->clear();
    for (Recipe::iterator it = rec.begin(); it != rec.end(); it++)
    {
        if ((*it)->identify() == 1)
        {
            Ingridient *ing = dynamic_cast<Ingridient*>(*it);
            ui->listWidget->addItem(QString::fromStdString(ing->getName())
                                    + ": "
                                    + QString::number(ing->getAmount())
                                    + ' '
                                    + QString::fromStdString(ing->getMeasure()));
        }
        else
        {
            Operation *op = dynamic_cast<Operation*>(*it);
            ui->listWidget->addItem("-" + QString::fromStdString(op->getName())
                                    + " for "
                                    + QString::number(op->getDuration())
                                    + ' '
                                    + QString::fromStdString(op->getMeasure()));
        }
    }
    itr = rec.begin();
    updateForm();
    ui->titleLabel->setText(recipeTitle + "   "
                            + QString::number(rec.size()) + " items");
}

void Dialog::updateForm()
{
    if (itr != NULL)
    {
        if ((*itr)->identify() == 1)
        {
            Ingridient *ing = dynamic_cast<Ingridient*>(*itr);
            ui->label_2->setText("name");
            ui->lineEdit->setText(QString::fromStdString(ing->getName()));
            ui->label_3->setText("measure");
            ui->lineEdit_2->setText(QString::fromStdString(ing->getMeasure()));
            ui->label_4->setText("amount");
            ui->lineEdit_3->setText(QString::number(ing->getAmount()));
        }
        else
        {
            Operation *op = dynamic_cast<Operation*>(*itr);
            ui->label_2->setText("name");
            ui->lineEdit->setText(QString::fromStdString(op->getName()));
            ui->label_3->setText("duration");
            ui->lineEdit_2->setText(QString::number(op->getDuration()));
            ui->label_4->setText("measure");
            ui->lineEdit_3->setText(QString::fromStdString(op->getMeasure()));
        }
    }
    else
    {
        ui->label_2->setText("");
        ui->lineEdit->setText("");
        ui->label_3->setText("");
        ui->lineEdit_2->setText("");
        ui->label_4->setText("");
        ui->lineEdit_3->setText("");
        ui->label_2->setText("");
        ui->lineEdit->setText("");
        ui->label_3->setText("");
        ui->lineEdit_2->setText("");
        ui->label_4->setText("");
        ui->lineEdit_3->setText("");
        ui->updateButton->setDisabled(true);
        ui->nextButton->setDisabled(true);
    }
}

void Dialog::on_newButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    ui->updateButton->setDisabled(true);
    rec.removeAll();
    recipeTitle = "untitled";
    updateView();
}

void Dialog::on_openButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open recipe",
                                                    QDir::homePath(),
                                                    "Txt files (rec_*.txt)");
    std::string path = fileName.toUtf8().constData();
    std::string strRecipeTitle;
    rec.readFromFile(path, strRecipeTitle);
    recipeTitle = QString::fromStdString(strRecipeTitle);
    updateView();
    if (path != "")
    {
        ui->updateButton->setDisabled(false);
        ui->nextButton->setDisabled(false);
    }
}

void Dialog::on_nextButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    ++itr;
    updateForm();
}

void Dialog::on_updateButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    if (ui->updateButton->text() == "Update")
    {
        if ((*itr)->identify() == 1)
        {
            Ingridient *ing = dynamic_cast<Ingridient*>(*itr);
            std::string s = ui->lineEdit->text().toUtf8().constData();
            ing->setName(s);
            s = ui->lineEdit_2->text().toUtf8().constData();
            ing->setMeasure(s);
            double n = ui->lineEdit_3->text().toDouble();
            ing->setAmount(n);
        }
        else
        {
            Operation *op = dynamic_cast<Operation*>(*itr);
            std::string s = ui->lineEdit->text().toUtf8().constData();
            op->setName(s);
            int n = ui->lineEdit_2->text().toInt();
            op->setDuration(n);
            s = ui->lineEdit_3->text().toUtf8().constData();
            op->setMeasure(s);
        }
    }
    else
    {
        if (flagForAddition == 1)
        {
            std::string name = ui->lineEdit->text().toUtf8().constData();
            std::string measure = ui->lineEdit_2->text().toUtf8().constData();
            double amount = ui->lineEdit_3->text().toDouble();
            Ingridient *ing = new Ingridient(name, measure, amount);
            rec.push(ing);
        }
        else
        {
            std::string name = ui->lineEdit->text().toUtf8().constData();
            int duration = ui->lineEdit_2->text().toInt();
            std::string measure = ui->lineEdit_3->text().toUtf8().constData();
            Operation *op = new Operation(name, duration, measure);
            rec.push(op);
        }
    }
    ui->updateButton->setText("Update");
    ui->nextButton->setDisabled(false);
    updateView();
}

void Dialog::on_addIngridientButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    itr = NULL;
    updateForm();
    ui->label_2->setText("name");
    ui->label_3->setText("measure");
    ui->label_4->setText("amount");
    ui->updateButton->setText("Add");
    ui->updateButton->setDisabled(false);
    flagForAddition = 1;
}

void Dialog::on_addOperationButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    itr = NULL;
    updateForm();
    ui->label_2->setText("name");
    ui->label_3->setText("duration");
    ui->label_4->setText("measure");
    ui->updateButton->setText("Add");
    ui->updateButton->setDisabled(false);
    flagForAddition = 2;
}

void Dialog::on_popButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    rec.pop();
    updateView();
}

void Dialog::on_removeAllButton_clicked()
{
    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();

    rec.removeAll();
    updateView();
}

void Dialog::on_saveButton_clicked()
{
    ui->label->show();
    ui->lineEdit_5->show();
    ui->lowerSaveButton->show();
}

void Dialog::on_lowerSaveButton_clicked()
{
    QString fileName = ui->lineEdit_5->text();
    if (fileName == "")
    {
        fileName = "untitled";
    }
    recipeTitle = fileName;
    fileName.prepend("/rec_");
    fileName.append(".txt");
    fileName.prepend(QDir::homePath());
    std::string strRecipeTitle = recipeTitle.toUtf8().constData();
    std::string path = fileName.toUtf8().constData();
    rec.writeToFile(path, strRecipeTitle);

    ui->lowerSaveButton->hide();
    ui->lineEdit_5->hide();
    ui->label->hide();
    updateView();
}
