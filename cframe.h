#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include "Inventario.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

    void agregarProducto();
    void eliminarProducto();
    void mostrarProducto();
    void mostrarValorTotalInventario();

private slots:
    //void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_page1_clicked();

    void on_page2_clicked();

    void on_page3_clicked();

    void on_btn_close_released();

    void on_btn_back_clicked();


    void on_btn_back2_clicked();

    void on_btn_back3_clicked();

    void on_btn_total_invent_clicked();

private:
    Ui::cframe *ui;

    Inventario inventario;
};
#endif // CFRAME_H
