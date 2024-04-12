#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QTextEdit>
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <QColor>
#include <QFontDialog>
#include <QFont>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QMenuBar* MenuBar; //菜单栏
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;

    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* closeAction;
    QAction* clearAction;
    QAction* helppAction;

    QToolBar* fileToolBar; //文件工具栏
    QToolBar* fontToolBar; //字体工具栏

    QToolButton* colorBtn;
    QToolButton* fontBtn;

    QTextEdit* mainEdit;

    void initMenuBar();
    void initToolBar();
};
#endif // MAINWINDOW_H
