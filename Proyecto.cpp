#include <iostream>
#include <fstream>
using namespace std;

struct Reservacion
{
    int codigo;
    char nombreCliente[50];
    char nit[11];
    char dpi[15];
    char telefono[15];
    char fechaIngreso[11];
    char fechaSalida[11];
    int dias;
    int cantidadHabitaciones;
    int habitaciones[50];
    float total;
};

void mostrarMenu()
{
    system("cls");
    cout << "----- MENU PRINCIPAL -----" << endl
         << endl;
    cout << "1. Ingreso de Reservacion" << endl;
    cout << "2. Busqueda de Reservacion" << endl;
    cout << "3. Salir" << endl
         << endl;
    cout << "Seleccione una opcion: ";
}

void cargarReservaciones(Reservacion reservaciones[], int &cantidadReservaciones)
{
    ifstream archivo("reservaciones.txt");
    cantidadReservaciones = 0;

    while (archivo >> reservaciones[cantidadReservaciones].codigo) //     Evalúa si al leer el codigo de reservacion, tiene exito, si lo tiene, se guarda el codigo y se ejecuta el while, si no, no se ejecuta nada
    {
        archivo.ignore(); // Para capturar el salto de linea que queda en el buffer, y que no altere los datos

        archivo.getline(reservaciones[cantidadReservaciones].nombreCliente, 50);
        archivo.getline(reservaciones[cantidadReservaciones].nit, 15);
        archivo.getline(reservaciones[cantidadReservaciones].dpi, 15);
        archivo.getline(reservaciones[cantidadReservaciones].telefono, 15);
        archivo.getline(reservaciones[cantidadReservaciones].fechaIngreso, 11);
        archivo.getline(reservaciones[cantidadReservaciones].fechaSalida, 11);
        archivo >> reservaciones[cantidadReservaciones].dias;

        archivo >> reservaciones[cantidadReservaciones].cantidadHabitaciones;
        for (int i = 0; i < reservaciones[cantidadReservaciones].cantidadHabitaciones; i++)
        {
            archivo >> reservaciones[cantidadReservaciones].habitaciones[i];
        };
        archivo >> reservaciones[cantidadReservaciones].total;

        cantidadReservaciones++;
    }
    archivo.close();
}

void guardarReservaciones(Reservacion reservaciones[], int cantidadReservaciones) 
{        
    ofstream archivo("reservaciones.txt");
    for (int i = 0; i < cantidadReservaciones; i++)
    {
        archivo << reservaciones[i].codigo << endl;
        archivo << reservaciones[i].nombreCliente << endl;
        archivo << reservaciones[i].nit << endl;
        archivo << reservaciones[i].dpi << endl;
        archivo << reservaciones[i].telefono << endl;
        archivo << reservaciones[i].fechaIngreso << endl;
        archivo << reservaciones[i].fechaSalida << endl;
        archivo << reservaciones[i].dias << endl;
        archivo << reservaciones[i].cantidadHabitaciones << endl;
        for (int j = 0; j < reservaciones[i].cantidadHabitaciones; j++)
        {
            archivo << reservaciones[i].habitaciones[j] << " ";
        };
        archivo <<endl<< reservaciones[i].total << endl;
    }
    archivo.close();
}

float calcularTotal(Reservacion reservacion)
{
    float total = 0;
    for (int i = 0; i < reservacion.cantidadHabitaciones; i++)
    {
        switch (reservacion.habitaciones[i])
        {
        case 101:
            total += 250;
            break;
        case 102:
            total += 500;
            break;
        case 103:
            total += 1000;
            break;
        }
    }
    total = total * reservacion.dias;
    return total;
}

void ingresarReserva(Reservacion reservaciones[], int &cantidadReservaciones)
{
    int repetir;
    do
    {

        Reservacion nuevaReserva;//Variable temporal para guardar info de esta reservacion, y luego colocarla en un array
        system("cls");
        cout << "-------Ingreso de Reservacion-------" << endl
             << endl;

        nuevaReserva.codigo=cantidadReservaciones+1;
        cout << "\t\t\tCodigo: "<<nuevaReserva.codigo<<endl;

        cout << "Nombre del cliente:\t\t";
        cin.ignore();//Queda guardado un salto de linea en el buffer, con esto se ignora el salto de linea, para que no se salte el ingreso de nombre
        cin.getline(nuevaReserva.nombreCliente, 50);

        cout << "NIT:\t\t\t\t";
        cin.getline(nuevaReserva.nit, 11);

        cout << "DPI:\t\t\t\t";
        cin.getline(nuevaReserva.dpi, 15);

        cout << "Telefono:\t\t\t";
        cin.getline(nuevaReserva.telefono, 15);

        cout << "Fecha de Ingreso (DD/MM/AAAA):\t";
        cin.getline(nuevaReserva.fechaIngreso, 11);

        cout << "Fecha de Salida (DD/MM/AAAA):\t";
        cin.getline(nuevaReserva.fechaSalida, 11);

        cout << "Dias de estadia:\t\t";
        cin >> nuevaReserva.dias;

        cout << "Cantidad de habitaciones:\t";
        cin >> nuevaReserva.cantidadHabitaciones;

        cout << endl //  lista codigos habitaciones
             << "Las habitaciones disponibles son las siguientes:" << endl
             << endl
             << "101\tBasica\t\tQ  250.00" << endl
             << "102\tPremium\t\tQ  500.00" << endl
             << "103\tDeluxe\t\tQ1,000.00" << endl
             << endl;
        if (nuevaReserva.cantidadHabitaciones == 1)
        {
            cout << "Ingrese el codigo de la habitacion elegida:" << endl;
        }
        else
        {
            cout << "Ingrese los codigos de las " << nuevaReserva.cantidadHabitaciones << " habitaciones elegidas:" << endl;
        };
        int habitacion;
        for (int i = 0; i < nuevaReserva.cantidadHabitaciones; i++)
        {
            cin >> habitacion;
            if (habitacion == 101 || habitacion == 102 || habitacion == 103)
            {
                nuevaReserva.habitaciones[i] = habitacion;
            }
            else
            {
                cout << "Codigo invalido, por favor ingreselo correctamente:" << endl;
                i--;
            }
        }

        // Calcular el total
        nuevaReserva.total = calcularTotal(nuevaReserva);
        cout << "Total a pagar: \t\t\tQ" << nuevaReserva.total <<".00"<< endl
             << endl;

        // Agregar la nueva reservacion al array y actualizar archivo
        reservaciones[cantidadReservaciones] = nuevaReserva;   // agrega al array
        cantidadReservaciones++;                          // aumenta la variable que contiene la cantidad
        guardarReservaciones(reservaciones, cantidadReservaciones); // manda a guardar el array

        cout << "Reservacion ingresada con exito" << endl
             << endl;
        cout << "Desea hacer otra reservacion?" << endl
             << "0. No" << endl
             << "1. Si" << endl;
        cin >> repetir;

    } while (repetir != 0);
}

void resultadosBusqueda(Reservacion reservaciones[], int coincidencia)
{
        cout << endl<<"\t\t\tCodigo: "<< reservaciones[coincidencia].codigo << endl;
        cout << "Nombre del cliente:\t\t"<< reservaciones[coincidencia].nombreCliente << endl;
        cout << "NIT:\t\t\t\t"<< reservaciones[coincidencia].nit << endl;
        cout << "DPI:\t\t\t\t"<< reservaciones[coincidencia].dpi << endl;
        cout << "Telefono:\t\t\t" << reservaciones[coincidencia].telefono << endl;    
        cout << "Fecha de Ingreso (DD/MM/AAAA):\t"<< reservaciones[coincidencia].fechaIngreso << endl;
        cout << "Fecha de Salida (DD/MM/AAAA):\t" << reservaciones[coincidencia].fechaSalida << endl;
        cout << "Dias de estadia:\t\t"<< reservaciones[coincidencia].dias << endl;
        cout << "Cantidad de habitaciones:\t"<< reservaciones[coincidencia].cantidadHabitaciones << endl;

        cout << "Habitaciones reservadas:\t";
            for (int i = 0; i < reservaciones[coincidencia].cantidadHabitaciones; i++)
            {
                cout << reservaciones[coincidencia].habitaciones[i] << " ";
            }
            cout << endl;

        cout << "Total a pagar: \t\t\tQ" << reservaciones[coincidencia].total <<".00"<< endl
             << endl<<endl;
}

void buscar(Reservacion reservaciones[], int cantidadReservaciones)
{
    int paraBuscar;
    int repetir;

    do
    {
    int coincidencia = -1;

    system("cls");
    cout << "-------Busqueda de Reservacion-------" << endl
         << "Ingrese el codigo de la reservacion, o bien, ingrese 0 para mostrar todas las reservaciones:"<<endl;
    cin >> paraBuscar;

    if (paraBuscar == 0)
    {
        if (cantidadReservaciones > 0)
        {
            for (int i = 0; i < cantidadReservaciones; i++)
            {
                resultadosBusqueda(reservaciones, i);
            }
        }
        else
        {
            cout <<endl<< "No hay ninguna reservacion registrada aun" << endl<<endl;
        }
    }
    else
    {
        for (int i = 0; i < cantidadReservaciones; i++)
        {
            if (reservaciones[i].codigo == paraBuscar)
            {
                coincidencia = i;
                break;
            }
        }
        if (coincidencia == -1)
        {
            cout << endl<<"No se han encontrado coincidencias" << endl<<endl;
        }
        else
        {
            resultadosBusqueda(reservaciones, coincidencia);
        }
    }

        cout << "Desea hacer otra busqueda?" << endl
             << "0. No" << endl
             << "1. Si" << endl;
        cin >> repetir;

    } while (repetir!=0);
}

int main() 
{
    Reservacion reservaciones[101];
    int cantidadReservaciones = 0;
    int opcion;

    cargarReservaciones(reservaciones, cantidadReservaciones); // Carga las reservaciones del archivo de texto a un array

    do
    { // loop del menú
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            ingresarReserva(reservaciones, cantidadReservaciones);
            break;
        case 2:
            buscar(reservaciones, cantidadReservaciones);
            break;
        case 3:
            system("cls");
            cout << "Cerrando el programa..." << endl;
            break;
        default:
            cout << "Ingrese una opcion valida" << endl;
        }
    } while (opcion != 3);

    return 0;
}