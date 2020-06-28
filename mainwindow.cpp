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
    ui->InputNum->setStyleSheet("background:rgb(255,0,0,0);border:1px solid white;");
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
    ch.push_back("");//暂时从1开始编号
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
    s.init(ch);

    s.solve();

    sort(s.qq + 1, s.qq + s.tt + 1);
    int gg = 0;
    for (int i = 1; i <= s.tt; i++)
    {
        if (s.qq[i] == s.qq[i - 1])
        {
            continue;
        }
        s.ha[s.qq[i]] = ++gg;
    }
    string str;
    QString qstr;
    for (int i = 1; i <= s.n; i++)
    {
        if (!s.ha[i])
        {
            continue;
        }
        if (i < 10)
        {
            str = "  " + to_string(s.ha[i]) + ":  " + s.ch[i];
        }
        else
        {
            str = " " + to_string(s.ha[i]) + ":  " + s.ch[i];
        }
        //cout<<setw(3)<<ha[i]<<":  "<<ch[i];
        if (i > 10)
        {
            str += " ";
            str += "(";
            str += to_string(s.ha[s.ff1[i]]);
            str += ")+(";
            str += to_string(s.ha[s.ff2[i]]);
            str += ")";
            //cout<<" "<<"("<<ha[ff1[i]]<<")+("<<ha[ff2[i]]<<")";
            if (s.bb[i])
            {
                str += "    ";
                str += s.kk2[i] + "/" + s.kk1[i];
                //cout<<"    "<<kk2[i]<<"/"<<kk1[i];
            }
        }
        //cout<<endl;
        qstr = QString::fromStdString(str);
        ui->show->append(qstr);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    s.clear();

    //清空文本框
    ui->show->clear();
    ui->InputNum->clear();
    ui->plainTextEdit->clear();
}
