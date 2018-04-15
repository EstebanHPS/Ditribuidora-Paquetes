#ifndef CABECERA_HXX_INCLUDED
#define CABECERA_HXX_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<list>
#include <stdlib.h>
#include <sstream>

///FUNCION AUXILIAR PARA ORGANIZAR LOS COMANDOS RECIBIDOS POR CONSOLA
std::list<std::string> UIlist(std::string linea)
{
    std::list<std::string> UI;
    std::string aux;
    char*aux3=(char*)linea.c_str();
    char* aux2;
    aux2=strtok(aux3," ");
    UI.push_back(aux2);
    while(aux2!=NULL)
    {
        UI.push_back(aux2);
        aux2=strtok(NULL," ");
    }
    UI.erase(UI.begin());
    return UI;
}

///FUNCIONES DE LOS TADS
Persona:: Persona()
{}

int OficinaGeneral::agregarPaquete(Paquete PaqueteA)
{
    list<Paquete> listaP = getListaPaquetes();
    list<Paquete>::iterator it;
    for (it = listaP.begin(); it != listaP.end(); it++)
    {
        if (it->getNumeroDeGuia() == PaqueteA.getNumeroDeGuia())
        {
            return 1;
        }
    }
    setListaPaquetes(PaqueteA);
    return 2;
}

Persona* OficinaGeneral::buscarPersona(string cc)
{
    list<Persona>* listp = this->getDirectorio();
    list<Persona>::iterator it;
    for(it=listp->begin(); it!=listp->end(); it++)
    {
        if(it->getNumeroIdentificacion()==cc)
        {
            return &(*it);
        }
    }
    return NULL;
}


Persona::Persona(string Nombre, string NumeroDeIdentificiacion,string Direccion,string Ciudad, string Telefono)
{
    this->nombre=Nombre;
    this->numeroDeIdentificiacion=NumeroDeIdentificiacion;
    this->direccion=Direccion;
    this->ciudad=Ciudad;
    this->telefono=Telefono;

}

///IMPLEMENTACION DE LAS FUNCIONES DEL MENÚ DEL SISTEMA
int cargarPersonas(string nombre_archivo, OficinaGeneral *LaOficina)//retorna 1 si no existe, 2 si no contiene info valida, 3 resultado exitoso
{
    ifstream input(nombre_archivo.c_str());
    if (!input)
    {
        //cout << "El archivo " << nombre_archivo << " no existe o es ilegible." << endl; ESTO VA EN MAIN
        return 1;
    }
    else
    {
        string input_line;
        getline(input, input_line,',');
        if (input_line != "Nombre")
        {
            //cout << "El archivo " << nombre_archivo << " no contiene informacion valida." << endl;ESTO VA EN MAIN
            return 2;
        }
        else
        {
            string nombre, apellidos, numeroId, direccion, ciudad, telefono;
            getline(input,input_line);
            while (getline(input,input_line))
            {
                stringstream tokens(input_line);
                string token;
                getline(tokens,token,',');
                nombre = token;
                getline(tokens,token,',');
                apellidos = token;
                getline(tokens,token,',');
                numeroId = token;
                getline(tokens,token,',');
                direccion = token;
                getline(tokens,token,',');
                ciudad = token;
                getline(tokens,token,',');
                telefono = token;
                string nep = nombre + " " + apellidos;
                (LaOficina->getDirectorio())->push_back(Persona(nep,numeroId,direccion,ciudad,telefono));
            }
            return 3;
        }

    }
}

int cargarPaquetes(string nombre_archivo, OficinaGeneral* LaOficina)
{
    ifstream input(nombre_archivo.c_str());
    if (!input)
    {
        //cout << "El archivo " << nombre_archivo << " no existe o es ilegible." << endl;
        return 1;
    }
    else
    {
        string input_line;
        getline(input, input_line,',');
        if (input_line != "cedulaRemitente")
        {
            //cout << "El archivo " << nombre_archivo << " no contiene informacion valida." << endl;
            return 2;
        }
        else
        {
            string ccRemitente, ccDestinatario, peso, tipoContenido, numGuia, codOficina, nomOficina, dirOficina, ciudadOficina, codRegion, nomRegion;
            getline(input,input_line);
            while (getline(input,input_line))
            {
                stringstream tokens(input_line);
                string token;
                getline(tokens,token,',');
                ccRemitente = token;
                getline(tokens,token,',');
                ccDestinatario = token;
                getline(tokens,token,',');
                peso = token;
                getline(tokens,token,',');
                tipoContenido = token;
                getline(tokens,token,',');
                numGuia = token;
                getline(tokens,token,',');
                codOficina = token;
                getline(tokens,token,',');
                nomOficina = token;
                getline(tokens,token,',');
                dirOficina = token;
                getline(tokens,token,',');
                ciudadOficina = token;
                getline(tokens,token,',');
                codRegion = token;
                getline(tokens,token,',');
                nomRegion = token;

                list<OficinaDeReparto> listaOR = LaOficina->getListaDeOficinasDeReparto();
                list<OficinaDeReparto>::iterator itr;
                OficinaDeReparto* oficinaR;
                RegionDeReparto* regionR;

                if (listaOR.size()==0)
                {
                    oficinaR = new OficinaDeReparto(codOficina, nomOficina, dirOficina, ciudadOficina);
                    regionR = new RegionDeReparto(nomRegion, codRegion);


                    Persona* rem = LaOficina->buscarPersona(ccRemitente);
                    Persona* des = LaOficina->buscarPersona(ccDestinatario);
                    double d=atof(peso.c_str());
                    Paquete* aux= new Paquete(numGuia, tipoContenido, d, rem, des );

                    regionR->setListaPaquetes(*aux);
                    oficinaR->setListaRegiones(*regionR);
                    LaOficina->setlistaDeOficionasDeReparto(*oficinaR);
                    int f = LaOficina->agregarPaquete(*aux);

                }

                else
                {
                    oficinaR= new OficinaDeReparto(codOficina, nomOficina, dirOficina, ciudadOficina);
                    regionR = new RegionDeReparto(nomRegion, codRegion);

                    Persona* rem = LaOficina->buscarPersona(ccRemitente);
                    Persona* des = LaOficina->buscarPersona(ccDestinatario);
                    double d=atof(peso.c_str());
                    Paquete* aux= new Paquete(numGuia, tipoContenido, d, rem, des );

                    regionR->setListaPaquetes(*aux);
                    oficinaR->setListaRegiones(*regionR);
                    LaOficina->setlistaDeOficionasDeReparto(*oficinaR);
                    int k = LaOficina->agregarPaquete(*aux);
                    ///se inserta paquete si la oficina y la region no existen
                }
            }
        }

    }


    return 3;
}

int registrarPersona( string Nombre, string NumeroDeIdentificiacion, string Direccion, string Ciudad, string Telefono, OficinaGeneral *LaOficina)
{

    list<Persona>::iterator it=LaOficina->getDirectorio()->begin();
    for(; it!=LaOficina->getDirectorio()->end(); it++)
    {
        if(it->getNumeroIdentificacion()==NumeroDeIdentificiacion)
            return 1;
    }
    LaOficina->getDirectorio()->push_back((Persona(Nombre,NumeroDeIdentificiacion,Direccion,Ciudad,Telefono)));
    return 2;
}

int registrarPaquete(OficinaGeneral* Oficina, string id_rem, string id_des, string peso, string tipo,string num)
{

    Persona* rem = Oficina->buscarPersona(id_rem);
    Persona* des = Oficina->buscarPersona(id_des);
    double d=atof(peso.c_str());
    Paquete* aux= new Paquete(num, tipo, d, rem, des );
    int p = Oficina->agregarPaquete(*aux);
    return p;
}

list<string> conteoPaquetes(OficinaGeneral* LaOficina)
{
    list<string> conteo;
    int cantidadTotal = 0;
    list<OficinaDeReparto> listaOR = LaOficina->getListaDeOficinasDeReparto();
    list<OficinaDeReparto>::iterator ito;
    for (ito = listaOR.begin(); ito != listaOR.end(); ito++)
    {
        list<RegionDeReparto> listaR = ito->getConjuntoDeRegiones();
        list<RegionDeReparto>::iterator itr;
        for(itr = listaR.begin(); itr != listaR.end(); itr++)
        {
            int cantidadR = itr->getPaquetes().size();
            ostringstream c;
            c << cantidadR;
            string cr = c.str();
            string nombreR = itr->getNombre();
            conteo.push_back(cr);
            conteo.push_back(nombreR);
            cantidadTotal = cantidadTotal + cantidadR;
        }
    }
    ostringstream t;
    t << cantidadTotal;
    string ct = t.str();
    conteo.push_back(ct);
    return conteo;
}





#endif // CABECERA_HXX_INCLUDED
