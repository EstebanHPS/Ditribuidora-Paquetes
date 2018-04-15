#include "cabecera.h"
void cls()
{
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
}


int main()
{
    string nom, id, dir, ciu, tel;///variables para ingresar persona
    string id_rem,id_des, peso, tipo, num;///variables para agregar paquete
    int yeah;
    char cadena[50];
    Persona auxPersona;
    OficinaGeneral LaOficina;

    list<Persona>:: iterator iteradorPersonas;
    std::list<std::string>::iterator iterador;
    std::list<std::string>UI; //Esto lo modifico Esteban--------------
    OficinaDeReparto oficina;
    while(1)
    {

        string c="*", c1="*";
        cout<<"$";
        cin.getline(cadena,50);
        //list<string>UI=UIlist(cadena);
        if(UI.size() == 0)			//   y
        {
            //esto
            UI = UIlist(cadena);
        }
        else
        {
            UI.clear();
            UI = UIlist(cadena);
        }							//tambien


        iterador=UI.begin();

        for(int i=0; iterador!=UI.end(); iterador++)
        {
            if(i==0)
            {
                c=(*iterador);
            }

            if(i==1)
            {
                c1=(*iterador);
            }

            i++;
        }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
        if(c=="imprimirPersonas")///Comando para imprimir la lista de personas
        {
            iteradorPersonas=LaOficina.getDirectorio()->begin();
            for(; iteradorPersonas!=LaOficina.getDirectorio()->end(); iteradorPersonas++)
            {
                cout<<iteradorPersonas->getNombre()<<endl;
            }
            cls();
        }

        if(c=="imprimirPaquetes")///Comando para imprimir la lista de personas
        {
            list<Paquete> listaP = LaOficina.getListaPaquetes();
            list<Paquete>::iterator itP;
            for(itP = listaP.begin(); itP!=listaP.end(); itP++)
            {
                cout<<itP->getNumeroDeGuia() << endl;
            }
            cls();
        }


        if(c=="cargarPersonas")///PARA CARGAR PERSONAS------------------TERMINADO-----------------------------------------
        {
            if(c1!="*")
            {
                yeah=cargarPersonas(c1,&LaOficina);
                if(yeah==1)
                {
                    cout<<"El archivo "<<c1<<"no contiene informacion valida\n"<<endl;
                }
                else if(yeah==2)
                {
                    cout<<"El archivo "<<c1<<"no existe o es ilegible\n"<<endl;
                }
                else
                {
                    cout<<"La informacion desde el archivo "<< c1 <<" ha sido cargada exitosamente.\n"<<endl;
                }
            }
        }
        else if(c=="cargarPaquetes")
        {

            if(c1!="*")
            {
                yeah=cargarPaquetes(c1,&LaOficina);
                if(yeah==1)
                {
                    cout<<"El archivo "<<c1<<"no contiene informacion valida\n"<<endl;
                }
                else if(yeah==2)
                {
                    cout<<"El archivo "<<c1<<"no existe o es ilegible\n"<<endl;
                }
                else
                {
                    cout<<"La informacion desde el archivo "<< c1 <<"ha sido cargada exitosamente.\n"<<endl;
                }

                list<OficinaDeReparto> listaOr = LaOficina.getListaDeOficinasDeReparto();
                list<OficinaDeReparto>::iterator it;
                list<RegionDeReparto>::iterator it2;
                list<Paquete>::iterator it3;
                for (it = listaOr.begin(); it!=listaOr.end(); it++)
                {
                    list<RegionDeReparto> listaRr = it->getConjuntoDeRegiones();
                }
            }
        }

        else if(c=="registrarPersona")///-----------------------------------TERMINADO------------------------------------------------------------
        {
            cout<<"Ingrese la siguiente informacion basica de la persona"<<endl;
            cout<<"Nombre: ";

            cin.ignore(); //  Limpia el buffer de la cadena de caracteres


            getline(cin,nom);

            cout<<endl<<"Identificacion: ";

            getline(cin,id);

            cout<<endl<<"Direccion: ";
            getline(cin,dir);

            cout<<endl<<"Ciudad: ";
            getline(cin,ciu);

            cout<<endl<<"Telefono: ";
            getline(cin,tel);
            cout<<endl;

            yeah=registrarPersona(nom, id, dir, ciu, tel, &LaOficina);///FUNCION PARA REGISTRAR PERSONA

            if(yeah==1)
            {
                cout<<"\nLa persona con identificacion "<<id<<"ya se encuentra registrada en el sistema.\n"<<endl;
            }
            else
            {
                cout<<"\nLa persona con identificacion "<<id<<" ha sido registrada exitosamente.\n"<<endl;
            }
        }

        else if(c=="registrarPaquete")
        {
            cout<<"Ingrese la siguiente informacion basica del paquete"<<endl;
            cout<<"Identificacion remitente: ";
            getline(cin,id_rem);
            cout<<endl<<"Identificacion destinatario: ";
            getline(cin,id_des);
            cout<<endl<<"Peso: ";
            getline(cin,peso);
            cout<<endl<<"Tipo de contenido: ";
            getline(cin,tipo);
            cout<<endl<<"Numero guia: ";
            getline(cin,num);
            cout<<endl;
            yeah=registrarPaquete(&LaOficina, id_rem, id_des, peso, tipo, num);///FUNCION PARA REGISTRAR PAQUETE
            if(yeah==1)
            {
                cout<<"El paquete con numero de guia "<<num<<" ya se encuentra registrado en el sistema."<<endl;
            }
            else
            {
                cout<<"El paquete con numero de guia "<<num<<" ha sido registrada exitosamente."<<endl;
            }
        }

        else if(c=="conteoPaquetes")
        {
            list<string> lista = conteoPaquetes(&LaOficina);
            list<string>::iterator it;
            list<string>::reverse_iterator it1;
            it1 = lista.rbegin();
            cout << "Se encuentra en el sistema " + *it1 + " paquetes pendientes por entregar. Estan distribuidos asi:" << endl;
            int cont = 0;
            int con1 = lista.size()-1;
            for (it = lista.begin(); it != lista.end()--; it++)
            {
                if (con1!=0)
                {
                    if (cont%2==0)
                    {
                        cout << *it + " paquetes en la region de reparto ";
                    }
                    else
                    {
                        cout << *it << endl;

                    }
                    cont++;
                }
                con1--;

            }
        }

        else if(c=="ayuda")///PARA SOLICITAR LA AYUDA
        {
            if(c1!="*")
            {
                if(c1=="cargarPersonas")
                    cout<<"Carga en memoria la información contenida en el archivo identificado por nombre_archivo,la cual debe corresponder a la información básica de un grupo de personas. El comando debe estructurar lainformación a partir del archivo para almacenarla de forma adecuada de acuerdo a la descripción del sistema de información."<<endl;
                if(c1=="cargarPaquetes")
                    cout<<"Carga en memoria la información contenida en el archivo identificado por nombre_archivo, la cual debe corresponder a la información básica de un grupo de paquetes. El comando debe estructurar la información a partir del archivo para almacenarla de forma adecuada de acuerdo a la descripción del sistema de información. "<<endl;
                if(c1=="registrarPersona")
                    cout<<"Permite insertar en el sistema la información asociada de una persona, para usarla posteriormente como remitente o destinatario de un paquete a enviar. La información básica de la persona (nombres, identificación, dirección, ciudad, teléfono) debe solicitarse al usuario por teclado y validarse adecuadamente."<<endl;
                if(c1=="registrarPaquete")
                    cout<<"Permite insertar en el sistema un paquete a entregar con toda su información asociada. La información básica del paquete (identificación remitente, identificación destinatario, peso, tipo de contenido, número de guía) debe solicitarse al usuario por teclado y validarse adecuadamente."<<endl;
                if(c1=="conteoPaquetes")
                    cout<<"De acuerdo a la información almacenada, realiza el conteo de los paquetes registrados que se encuentran pendientes por entregar. Se debe informar el total de paquetes pendientes (valor cant_paquetes) y el conteo parcial por cada una de las regiones de reparto. "<<endl;
                if(c1=="salir")
                    cout<<"Termina la ejecución de la aplicación."<<endl;

            }
            else
            {
                cout<<"cargarPersonas nombre_archivo"<<endl
                    <<"cargarPaquetes nombre_archivo"<<endl
                    <<"registrarPersona"<<endl
                    <<"registrarPaquete"<<endl
                    <<"conteoPaquetes"<<endl
                    <<"salir"<<endl;
            }

        }
        else if(c=="salir")///PARA SALIR
        {
            return 1;
        }
//--------------------------------------------------------------------------------------------------------------------------------
    }


    return 0;
}
