#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<list>
#include <string.h>
#include <stdlib.h>

std::list<std::string> UIlist(std::string linea);

using namespace std;

/*class CadenaDeCaracteresAlfanumericos
{
	private:
    string codigo;
    char letras[3];
    int digitos[5];

	public:
    codigoDeIdentificacion ();

};*/



class Persona
{
private:
    string nombre;
    string numeroDeIdentificiacion;
    string direccion;
    string ciudad;
    string telefono;
public:
    string getNombre()
    {
        return nombre;
    }
    string getNumeroIdentificacion()
    {
        return numeroDeIdentificiacion;
    }
    string getDireccion()
    {
        return direccion;
    }
    string getCiudad()
    {
        return ciudad;
    }
    string getTelefono()
    {
        return telefono;
    }

    Persona(string Nombre, string NumeroDeIdentificiacion,string Direccion,string Ciudad, string Telefono);
    Persona();
};

class Paquete
{
private:
    Persona* remitente=NULL;
    Persona* destinatario=NULL;
    double peso;
    string tipoDeContenido;
    string numeroDeGuia;
public:
    string getNumeroDeGuia()
    {
        return numeroDeGuia;
    }
    double setPeso()
    {
        return peso;
    }
    string setTipoDeContenido()
    {
        return tipoDeContenido;
    }
    string setNumeroDeGuia()
    {
        return numeroDeGuia;
    }
    Paquete(string NumeroDeGuia, string TipoDeContenido, double Peso, Persona* rem, Persona* des)
    {
        this->numeroDeGuia=NumeroDeGuia;
        this->tipoDeContenido=TipoDeContenido;
        this->peso=Peso;
        this->destinatario=des;
        this->remitente=rem;
    }

    Paquete(Persona *remitente, Persona *destinatario, string NumeroDeGuia, string TipoDeContenido, double Peso)
    {
        this->remitente = remitente;
        this->destinatario = destinatario;
        this->numeroDeGuia=NumeroDeGuia;
        this->tipoDeContenido=TipoDeContenido;
        this->peso=Peso;
    }
};

class RegionDeReparto
{
private:
    string nombre;
    string Codigo;
    list<Paquete> paquetes;
public:
    string getCodigo()
    {
        return Codigo;
    }
    //Paquete buscarPaquete(string numeroGuia);

    list<Paquete> getPaquetes()
    {
        return paquetes;
    }

    string getNombre()
    {
        return nombre;
    }

    void setListaPaquetes(Paquete paquete)
    {
        paquetes.push_back(paquete);
    }

    RegionDeReparto(string Nombre, string codigo)
    {
        this->nombre=Nombre;
        this->Codigo=codigo;
    }
};

class OficinaDeReparto
{
private:
    string codigoDeIdentificacionIndividual;
    string Nombre;
    string Direccion;
    string Ciudad;
    list<RegionDeReparto> ConjuntoDeRegiones;

public:
    string getCodigoDeIdentificacionIndividual()
    {
        return codigoDeIdentificacionIndividual;
    }

    RegionDeReparto* buscarRegion(string codRegion);

    list<RegionDeReparto> getConjuntoDeRegiones()
    {
        return ConjuntoDeRegiones;
    }

    void setListaRegiones(RegionDeReparto regionDeReparto)
    {
        ConjuntoDeRegiones.push_back(regionDeReparto);
    }

    OficinaDeReparto( string CodigoDeIdentificacionIndividual, string nombre, string direccion, string ciudad)
    {
        this->codigoDeIdentificacionIndividual=CodigoDeIdentificacionIndividual;
        this->Nombre=nombre;
        this->Direccion=direccion;
        this->Ciudad=ciudad;
    }
    bool estaRegion(string codRegion);
    void insertarPaquete(string codRegion, Paquete paq);

    OficinaDeReparto()
    {

    }
};

class OficinaGeneral
{
private:
    string nombre;
    list<OficinaDeReparto> listaDeOficionasDeReparto;
    list<Persona> Directorio;
    list<Paquete> Paquetes;

public:
    void setlistaDeOficionasDeReparto(OficinaDeReparto OficinaDeReparto)
    {
        listaDeOficionasDeReparto.push_back(OficinaDeReparto);
    }

    void setListaPaquetes(Paquete Paquete)
    {
        Paquetes.push_back(Paquete);
    }

    list<Paquete> getListaPaquetes()
    {
        return Paquetes;
    }

    list<OficinaDeReparto> getListaDeOficinasDeReparto()
    {
        return listaDeOficionasDeReparto;
    }

    OficinaDeReparto* buscarOficinaDeReparto(string codigoOficina);

    list<Persona> *getDirectorio()
    {
        return &Directorio;
    }
    bool estaOficina(string codOficina);
    int agregarPaquete(Paquete paquete);
    Persona* buscarPersona(string cc);
    void agregarRegion(OficinaDeReparto* oficinaR, RegionDeReparto regionR);

};
///FUNCIONES DEL MENÚ DEL SISTEMA
int cargarPersonas(string nombre_archivo, list<Persona> *listaPersonas);
int registrarPersona(string Nombre, string NumeroDeIdentificiacion, string Direccion, string Ciudad, string Telefono, list<Persona> *listaPersonas);
int cargarPaquetes(string nombre_archivo, OficinaGeneral *LaOficina);
int registrarPaquete(OficinaGeneral* Oficina, string id_rem, string id_des, double peso, string tipo,string num);
#include "cabecera.hxx"


#endif // CABECERA_H_INCLUDED
