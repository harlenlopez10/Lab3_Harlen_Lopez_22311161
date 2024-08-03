#include "cframe.h"
#include "ui_cframe.h"
#include "ProductoConStock.h"
#include "ProductoConDescuento.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QDebug>

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);
}

cframe::~cframe()
{
    delete ui;
}


//FUNCIONES
void cframe::agregarProducto() {
    QString nombreProducto = ui->LE_Nombre_3->text();
    double precio = ui->spb_Precio_3->value();
    QString descripcion = ui->TE_Descripcion_3->toPlainText();
    int adicional = ui->spb_Adicional_3->value();

    int tipoProducto = ui->comboBox_Tipo_3->currentIndex();
    std::unique_ptr<Producto> producto;

    if (tipoProducto == 0) {
        if (adicional > 100) {
            QMessageBox::warning(this, "Advertencia", "El descuento no puede ser mayor al 100%");
            return;
        }
        if (adicional > 0) {
            producto = std::make_unique<ProductoConDescuento>(nombreProducto.toStdString(), precio, descripcion.toStdString(), adicional);
        } else {
            QMessageBox::warning(this, "Advertencia", "Para ProductoConDescuento el descuento debe ser mayor a 0.");
            return;
        }
    } else if (tipoProducto == 1) {
        producto = std::make_unique<ProductoConStock>(nombreProducto.toStdString(), precio, descripcion.toStdString(), adicional);
    } else {
        QMessageBox::warning(this, "Advertencia", "Tipo de producto no válido.");
        return;
    }

    if (producto) {
        inventario.agregarProducto(std::move(producto));
        QMessageBox::information(this, "Éxito", "El producto se ha agregado exitosamente al inventario.");
        size_t tamano = inventario.obtenerTamanioInventario();
        qDebug() << "El tamaño del inventario es:" << tamano;
    }
}
void cframe::eliminarProducto() {
    QString nombreProducto = ui->LE_NombreEliminar_3->text();

    if (!nombreProducto.isEmpty()) {
        bool eliminado = inventario.eliminarProducto(nombreProducto.toStdString());

        if (eliminado) {
            QMessageBox::information(this, "Producto Eliminado", "El producto ha sido eliminado exitosamente.");
        } else {
            QMessageBox::warning(this, "Error", "No se encontró el producto para eliminar.");
        }
    } else {
        QMessageBox::warning(this, "Advertencia", "Por favor, ingrese el nombre del producto a eliminar.");
    }
}

void cframe::mostrarProducto()
{
    inventario.mostrarInventario(ui->TE_ProductosLista_3);
}

void cframe::mostrarValorTotalInventario()
{
    double valorTotal = inventario.calcularValorInventario();

    QMessageBox::information(this, "Valor Total del Inventario", "Valor Total del Inventario: " + QString::number(valorTotal));
}


//IMPLEMENTACIÓN FUNCIONES A BOTONES
void cframe::on_pushButton_2_clicked()
{
    agregarProducto();
}

void cframe::on_pushButton_3_clicked()
{
    eliminarProducto();
}

void cframe::on_page1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void cframe::on_page2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    mostrarProducto();
}


void cframe::on_page3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void cframe::on_btn_close_released()
{
     QCoreApplication::quit();
}


void cframe::on_btn_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void cframe::on_btn_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void cframe::on_btn_back3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void cframe::on_btn_total_invent_clicked()
{
    mostrarValorTotalInventario();
}

// finishted

