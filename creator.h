#ifndef CREATOR_H
#define CREATOR_H

#include <QObject>

#include "mainwindow.h"
#include "manager.h"

class Creator:  public QObject {
    Q_OBJECT

    MainWindow* main_window;
    Manager* manager;

public:
    Creator(QApplication *parent = nullptr);
    ~Creator();
    Creator(Creator const& other)            = delete;
    Creator& operator=(Creator const& other) = delete;
    Creator(Creator && other)                = delete;
    Creator& operator=(Creator && other)     = delete;
};

#endif // CREATOR_H
