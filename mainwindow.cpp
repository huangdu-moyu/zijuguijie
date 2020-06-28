#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QTextBlock>
#include <vector>

const int quesheng_size=10;
QString quesheng[quesheng_size]={"K(A,A)|K(B,A)|K(C,A)","~K(x1,A)|H(x1,A)","~H(A,x2)|~H(C,x2)"
                     ,"H(A,A)","H(A,C)","R(x3,A)|H(B,x3)","~H(A,x4)|H(B,x4)"
                     ,"~H(x5,A)|~H(x5,B)|~H(x5,C)","~K(x6,A)|~R(x6,A)","~K(x7,A)|ANSWER(x7)"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //ui->InputNum->setStyleSheet("background:rgb(255,0,0,0);border:1px solid white;");
    ui->show->setStyleSheet("background:rgb(255,0,0,0);border:1px solid white;");
    ui->plainTextEdit->setStyleSheet("background:rgb(255,0,0,0);border:1px solid white;");
    for(int i=0;i<quesheng_size;i++)
    {
        ui->plainTextEdit->appendPlainText(quesheng[i]);
    }
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
