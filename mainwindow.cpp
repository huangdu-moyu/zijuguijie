#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextBlock>
#include <QString>
#include "ziju.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    ui->show->append("123");    //调试语句
    QString num_str=ui->InputNum->text();

    n= num_str.toInt();

    QTextDocument* doc=ui->plainTextEdit->document () ; //文本对象
    //int cnt=doc->blockCount () ;//回车符是一个 block
    for (int i=0; i<n;i++)
    {

        QTextBlock textLine=doc->findBlockByNumber(i) ; // 文本中的一行
        QString temp_horn=textLine.text();
        ch[i+1]=temp_horn.toStdString();
        q.push(make_pair(ch[i+1],i+1));

    }

    solve();
}

void MainWindow::on_pushButton_2_clicked()
{
    sort(qq+1,qq+tt+1);
        int gg=0;
        for(int i=1;i<=tt;i++)
        {
            if(qq[i]==qq[i-1])
            {
                continue;
            }
            ha[qq[i]]=++gg;

        }
        string str;
        QString qstr;
        for(int i=1;i<=n;i++)
        {
            if(!ha[i])
            {
                continue;
            }
            if(i<10)
            {
                str="  "+to_string(ha[i])+":  "+ch[i];
            }
            else
            {
                str=" "+to_string(ha[i])+":  "+ch[i];
            }
            //cout<<setw(3)<<ha[i]<<":  "<<ch[i];
            if(i>10)
            {
                str+=" ";
                str+="(";
                str+=to_string(ha[ff1[i]]);
                str+=")+(";
                str+=to_string(ha[ff2[i]]);
                str+=")";
                //cout<<" "<<"("<<ha[ff1[i]]<<")+("<<ha[ff2[i]]<<")";
                if(bb[i])
                {
                    str+="    ";
                    str+=kk2[i]+"/"+kk1[i];
                    //cout<<"    "<<kk2[i]<<"/"<<kk1[i];
                }
            }
            //cout<<endl;
            qstr=QString::fromStdString(str);
            ui->show->append(qstr);
        }
}
