#include "creator.h"

Creator::Creator(QApplication *parent)
    : main_window(new MainWindow())
    , manager(new Manager(this)){
    main_window->show();
    connect(main_window, SIGNAL(form_worked(const Current_settings*)), manager, SLOT(processing(const Current_settings*)));
    connect(manager, SIGNAL(has_problem_with_files(const QList<QString>)), main_window, SLOT(problem_with_files(const QList<QString>)));
}

Creator::~Creator(){
    delete main_window;
    delete manager;
}
