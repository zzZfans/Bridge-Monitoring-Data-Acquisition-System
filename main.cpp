#include <QApplication>

#include "main_widget.h"

#include"login_dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    main_widget w;

    w.setWindowOpacity(0.9);

    login_dialog ld;

    w.set_customer_type(ld.exec());

    if(w.get_customer_type()==1||w.get_customer_type()==2)
    {
        w.show();

        return a.exec();
    }

    return 0;
}
