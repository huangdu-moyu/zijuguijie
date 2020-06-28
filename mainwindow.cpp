#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ziju.h"
#include <QString>
#include <QTextBlock>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->show->append("123");    //调试语句
    QString num_str = ui->InputNum->text();

    n = num_str.toInt();

    QTextDocument *doc = ui->plainTextEdit->document(); //文本对象
    //int cnt=doc->blockCount () ;//回车符是一个 block
    for (int i = 0; i < n; i++)
    {

        QTextBlock textLine = doc->findBlockByNumber(i); // 文本中的一行
        QString temp_horn = textLine.text();
        ch[i + 1] = temp_horn.toStdString();
        q.push(make_pair(ch[i + 1], i + 1));
    }

    solve();

    sort(qq + 1, qq + tt + 1);
    int gg = 0;
    for (int i = 1; i <= tt; i++)
    {
        if (qq[i] == qq[i - 1])
        {
            continue;
        }
        ha[qq[i]] = ++gg;
    }
    string str;
    QString qstr;
    for (int i = 1; i <= n; i++)
    {
        if (!ha[i])
        {
            continue;
        }
        if (i < 10)
        {
            str = "  " + to_string(ha[i]) + ":  " + ch[i];
        }
        else
        {
            str = " " + to_string(ha[i]) + ":  " + ch[i];
        }
        //cout<<setw(3)<<ha[i]<<":  "<<ch[i];
        if (i > 10)
        {
            str += " ";
            str += "(";
            str += to_string(ha[ff1[i]]);
            str += ")+(";
            str += to_string(ha[ff2[i]]);
            str += ")";
            //cout<<" "<<"("<<ha[ff1[i]]<<")+("<<ha[ff2[i]]<<")";
            if (bb[i])
            {
                str += "    ";
                str += kk2[i] + "/" + kk1[i];
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
    //将所有全局变量清零
    n = 0;
    //string ch[505];
    memset(ch, 0, sizeof(ch));
    //extern bool fgg[505][505];
    memset(fgg, 0, sizeof(fgg));
    ss1 = "";
    ss2 = "";

    //extern int qq[505];
    memset(qq, 0, sizeof(qq));
    tt = 0;
    ha.clear();
    //extern string kk1[505],kk2[505];
    memset(kk1, 0, sizeof(kk1));
    memset(kk2, 0, sizeof(kk2));
    //extern bool bb[505];
    memset(bb, 0, sizeof(bb));
    //extern int ff1[505],ff2[505];
    memset(ff1, 0, sizeof(ff1));
    memset(ff2, 0, sizeof(ff2));
    //extern queue<pair<string,int> >q;
    queue<pair<string, int>> empty;
    swap(empty, q);

    //清空文本框
    ui->show->clear();
    ui->InputNum->clear();
    ui->plainTextEdit->clear();
}
