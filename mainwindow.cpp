#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("文本编辑器");
    this->resize(1024,728);
    this->setWindowIcon(QIcon(":/new/prefix1/qrc/write2file.png"));
    this->initMenuBar();
    this->initToolBar();
    this->mainEdit = new QTextEdit(this);
    this->setCentralWidget(this->mainEdit);

    //打开文件并读取到编辑区
    connect(this->openAction,&QAction::triggered,[=](){
        QString filter = "文本文件(*.txt);;所有文件(*.*);;代码文件(*.c *.py *.h *.cpp *.hpp *.js)";
        QString fileName = QFileDialog::getOpenFileName(this,"选择要打开的文件","./",filter);
        if(fileName.isNull()) return;
        //定义一个文件对象
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        if(!file.isOpen()) return ;
        QByteArray buffer = file.readAll();
        this->mainEdit->clear();
        this->mainEdit->append(QString(buffer));
        file.close();

    });
    //保存文件，写入到文件
    connect(this->saveAction,&QAction::triggered,[=](){
        QString filter = "文本文件(*.txt);;所有文件(*.*);;代码文件(*.c *.py *.h *.cpp *.hpp *.js)";
        QString fileName = QFileDialog::getSaveFileName(this,"保存文件","./",filter);
        if(fileName.isNull()) return;

        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        if(!file.isOpen()) return;
        QString buffer = this->mainEdit->toPlainText();
        file.write(buffer.toUtf8());
        file.close();

    });
    //功能：改变字体颜色
    connect(this->colorBtn,&QToolButton::clicked,[=](){
        QColor color = QColorDialog::getColor(Qt::white,this,"选择颜色");
        if(!color.isValid()) return ;
        QTextCharFormat fmt;
        fmt.setForeground(color);
        this->mainEdit->mergeCurrentCharFormat(fmt);
    });
    //功能：改变字体大小及样式
    connect(this->fontBtn,&QToolButton::clicked,[=](){
        bool ok;
        QFont font = QFontDialog::getFont(&ok,this);
        if(ok){
            QTextCharFormat fmt;
            fmt.setFont(font);
            this->mainEdit->mergeCurrentCharFormat(fmt);
        }
    });
    //新建
    connect(this->newAction,&QAction::triggered,[this](){
        if(!this->mainEdit->toPlainText().isEmpty()){
            if(QMessageBox::Yes == QMessageBox::warning(this,"警告","新建文件将清空当前内容？\n请确认数据已保存！",QMessageBox::Yes|QMessageBox::No)){
                this->mainEdit->clear();
            }
        }
    });
    //关闭
    connect(this->closeAction,&QAction::triggered,[this](){
        if(QMessageBox::Yes == QMessageBox::warning(this,"警告","关闭前请确认已经保存数据\n确认关闭！",QMessageBox::Yes|QMessageBox::No)){
                    this->close();
        }
    });
    //清空
    connect(this->clearAction,&QAction::triggered,[this](){
        if(QMessageBox::Yes == QMessageBox::warning(this,"警告","确认要清空所有内容吗？\n请谨慎操作！",QMessageBox::Yes|QMessageBox::No)){
            this->mainEdit->clear();
        }
    });
    //帮助
    connect(this->helppAction,&QAction::triggered,[this](){
        QMessageBox::about(this,"帮助","文本编辑器<br>GitHub主页: <a href='https://github.com/fdkang'>https://github.com/fdkang</a>");
    });
}

MainWindow::~MainWindow()
{
}

void MainWindow::initMenuBar()
{
    //设置主菜单以及子菜单
    this->MenuBar = this->menuBar();
    this->fileMenu = this->MenuBar->addMenu("文件");
    this->editMenu = this->MenuBar->addMenu("编辑");
    this->helpMenu = this->MenuBar->addMenu("帮助");
    //设置菜单触发
    this->newAction = this->fileMenu->addAction("新建文件");
    this->newAction->setIcon(QIcon(":/new/prefix1/qrc/Files.png"));
    this->openAction = this->fileMenu->addAction("打开文件");
    this->openAction->setIcon(QIcon(":/new/prefix1/qrc/fileopen.png"));
    this->saveAction = this->fileMenu->addAction("保存文件");
    this->saveAction->setIcon(QIcon(":/new/prefix1/qrc/Floppy.png"));
    this->closeAction = this->fileMenu->addAction("关闭文件");
    this->closeAction->setIcon(QIcon(":/new/prefix1/qrc/stop.png"));
    this->clearAction = this->editMenu->addAction("清空编辑区");
    this->clearAction->setIcon(QIcon(":/new/prefix1/qrc/Bin (empty).png"));
    this->helppAction = this->helpMenu->addAction("帮助");
    this->helppAction->setIcon(QIcon(":/new/prefix1/qrc/User.png"));
}

void MainWindow::initToolBar()
{
    this->fileToolBar = this->addToolBar("文件工具");
    this->fileToolBar->addAction(clearAction);

    this->fontToolBar = this->addToolBar("按钮工具栏");
    this->colorBtn = new QToolButton(this);
    this->colorBtn->setText("颜色按钮");
    this->colorBtn->setIcon(QIcon(":/new/prefix1/qrc/textcolor.png"));
    this->fontBtn = new QToolButton(this);
    this->fontBtn->setText("字体按钮");
    this->fontBtn->setIcon(QIcon(":/new/prefix1/qrc/Edit.png"));
    this->fontToolBar->addWidget(colorBtn);
    this->fontToolBar->addWidget(fontBtn);
}

