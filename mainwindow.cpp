#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QTextBlock>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //ui->InputNum->setStyleSheet("background:rgb(255,0,0,0);border:1px solid white;");
    ui->show->setStyleSheet("background:rgb(255,0,0,0);border:1px solid white;");
    ui->plainTextEdit->setStyleSheet("background:rgb(255,0,0,0);border:1px solid white;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    s.clear();
    ui->show->clear();
    //QString num_str = ui->InputNum->text();

    //s.n = num_str.toInt();

    vector<string> ch;

    QTextDocument *doc = ui->plainTextEdit->document(); //文本对象
    int cnt=doc->blockCount () ;//回车符是一个 block

    //qDebug()<<s.n<<" "<<doc->blockCount()<<endl;
    for (int i = 0; i < cnt; i++)
    {

        QTextBlock textLine = doc->findBlockByNumber(i); // 文本中的一行
        QString temp_horn = textLine.text();
        if(temp_horn.length())
        {
            ch.push_back(temp_horn.toStdString());
        }

        //s.ch[i + 1] = temp_horn.toStdString();
        //s.q.push(make_pair(s.ch[i + 1], i + 1));
    }

    vector<string> res=s.solve(ch);

    for (const string& str:res)
    {
        ui->show->append(QString::fromStdString(str));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    s.clear();

    //清空文本框
    ui->show->clear();
    ui->plainTextEdit->clear();
}
