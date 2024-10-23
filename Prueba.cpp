#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class reservacion
{
public:
    int codigoreservacion;
    string nombreCliente;
    string fechaIngreso;
    string fechaSalida;
    vector<int> habitaciones; // Almacena los codigos de las habitaciones reservaciondas
    vector<double> precios;   // Almacena los precios de las habitaciones reservaciondas

    reservacion() : codigoreservacion(0) {}

    // Metodo para ingresar nueva reservacion
    void ingresarDatos()
    {
        cout << "Ingrese el codigo de la reservacion: ";
        cin >> codigoreservacion;
        cin.ignore();
        cout << "Nombre del cliente: ";
        getline(cin, nombreCliente);
        cout << "Fecha de ingreso (dd/mm/yyyy): ";
        getline(cin, fechaIngreso);
        cout << "Fecha de salida (dd/mm/yyyy): ";
        getline(cin, fechaSalida);

        int opcion;
        do
        {
            cout << "\nSeleccione la habitacion (101: Sencilla Q.250, 103: Suite Q.600): ";
            int habitacion;
            cin >> habitacion;
            habitaciones.push_back(habitacion);

            if (habitacion == 101)
                precios.push_back(250.00);
            else if (habitacion == 103)
                precios.push_back(600.00);

            cout << "Desea agregar otra habitacion? (1 = Si, 0 = No): ";
            cin >> opcion;
        } while (opcion == 1);
    }

    // Metodo para calcular el total de la reservacion
    double calcularTotal()
    {
        double total = 0;
        for (double precio : precios)
        {
            total += precio;
        }
        return total;
    }

    // Metodo para guardar la reservacion en un archivo
    void guardarEnArchivo()
    {
        ofstream archivo("reservacions.txt", ios::app);
        if (archivo.is_open())
        {
            archivo << "Codigo de reservacion: " << codigoreservacion << "\n";
            archivo << "Nombre del cliente: " << nombreCliente << "\n";
            archivo << "Fecha de ingreso: " << fechaIngreso << "\n";
            archivo << "Fecha de salida: " << fechaSalida << "\n";
            archivo << "Habitaciones reservaciondas: ";
            for (int habitacion : habitaciones)
            {
                archivo << habitacion << " ";
            }
            archivo << "\nTotal: Q. " << calcularTotal() << "\n\n";
            archivo.close();
        }
        else
        {
            cout << "No se pudo abrir el archivo.\n";
        }
    }

    // Metodo para buscar una reservacion por codigo
    void buscar(int codigo)
    {
        ifstream archivo("reservacions.txt");
        string linea;
        bool encontrado = false;

        if (archivo.is_open())
        {
            while (getline(archivo, linea))
            {
                if (linea.find("Codigo de reservacion: " + to_string(codigo)) != string::npos)
                {
                    encontrado = true;
                    cout << linea << endl;
                    for (int i = 0; i < 6; i++)
                    { // Imprime las siguientes lineas de detalles
                        getline(archivo, linea);
                        cout << linea << endl;
                    }
                    break;
                }
            }
            archivo.close();
        }
        if (!encontrado)
        {
            cout << "reservacion con codigo " << codigo << " no encontrada.\n";
        }
    }
};

int main()
{
    reservacion reservacion;
    int opcion;

    do
    {
        system("cls");
        cout << endl
             << "------ MENU PRINCIPAL ------" << endl
             << endl;
        cout << "1. Ingreso de reservacion" << endl;
        cout << "2. Busqueda de reservacion" << endl;
        cout << "3. Salir" << endl
             << endl;
        cout << "Ingrese numero de opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int opcion;

            do
            {
                cout<<endl;
                reservacion.ingresarDatos();
                reservacion.guardarEnArchivo();
                cout <<endl<< "Reservacion guardada con exito. Desea realizar otra reserva?" << endl
                     << "0. No" << endl
                     << "1. Si" << endl;
                cin>>opcion;
            } while (opcion == 1);
            break;
        }
        case 2:
        {
            int opcion;
            do
            {
                int codigo;
                cout << endl
                     << "Ingrese el codigo de la reservacion a buscar: ";
                cin >> codigo;
                reservacion.buscar(codigo);
                cout<<"Desea realizar otra busqueda?"<<endl
                     << "0. No" << endl
                     << "1. Si" << endl;
                cin>>opcion;
            } while (opcion == 1);
            break;
        }
        case 3:
            cout << "Saliendo del programa...";
            system("cls");
            break;
        default:
            cout << "Opcion invalida, intente nuevamente."<<endl;
            break;
        };
    } while (opcion != 3);

    return 0;
}