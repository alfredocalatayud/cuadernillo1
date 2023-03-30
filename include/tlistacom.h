#ifndef TLISTACOM_H_
#define TLISTACOM_H_

#include "tcomplejo.h"

class TListaNodo {    
	private:
		// El elemento del nodo
		TComplejo e;
		// El nodo anterior
		TListaNodo *anterior;
		// El nodo siguiente
		TListaNodo *siguiente;
		
	public:
		// Constructor por defecto
		TListaNodo();
		// Constructor de copia
		TListaNodo(const TListaNodo &);
		// Destructor
		~TListaNodo();
		// Sobrecarga del operador asignación
		TListaNodo & operator=(const TListaNodo &);

    friend class TListaPos;
    friend class TListaCom;
};

class TListaPos {
    private:
		// Puntero a un nodo de la lista
		TListaNodo *pos;
	
	public:
		// Constructor por defecto
		TListaPos();    
		// Constructor de copia
		TListaPos(const TListaPos &);
		// Destructor
		~TListaPos();
		// Sobrecarga del operador asignación
		TListaPos & operator=(const TListaPos &);
		
		// METODOS
		// Sobrecarga del operador igualdad
		bool operator==(const TListaPos &) const;
		// Sobrecarga del operador desigualdad
		bool operator!=(const TListaPos &);
		// Devuelve la posición anterior
		TListaPos Anterior() const;
		// Devuelve la posición siguiente
		TListaPos Siguiente() const;
		// Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
		bool EsVacia() const;

    friend class TListaCom;
    friend class TListaNodo;
};

class TListaCom {
	private:
		// Primer elemento de la lista
		TListaNodo *primero;
		// Ultimo elemento de la lista
		TListaNodo *ultimo;
        void Limpiar();
        void Copia(const TListaCom &);
	
	public:
		// Constructor por defecto
		TListaCom();
		// Constructor de copia
		TListaCom(const TListaCom &);
		// Destructor
		~TListaCom();
		// Sobrecarga del operador asignación
		TListaCom& operator=(const TListaCom &);
		
		// METODOS
		// Sobrecarga del operador igualdad
		bool operator==(const TListaCom &);
		// Sobrecarga del operador desigualdad
		bool operator!=(const TListaCom &);
		// Sobrecarga del operador suma
		TListaCom operator+(const TListaCom &);
		// Sobrecarga del operador resta
		TListaCom operator-(const TListaCom &);
		// Devuelve TRUE si la lista está vacía, false en caso contrario
		bool EsVacia() const;
		// Inserta el elemento en la cabeza de la lista
		bool InsCabeza(const TComplejo &);
		// Inserta el elemento en a la izquierda de la posición indicada
		bool InsertarI(const TComplejo &, const TListaPos &);
		// Inserta el elemento en a la derecha de la posición indicada
		bool InsertarD(const TComplejo &, const TListaPos &);
		// Buscar y borrar la primera ocurrencia del elemento
		bool Borrar(const TComplejo &);
		// Buscar y borrar todas las occurrencias del elemento
		bool BorrarTodos(const TComplejo &);
		// Borra el elemento que ocupa la posición indicada
		bool Borrar(const TListaPos &);
		// Obtiene el elemento que ocupa la posición indicada 
		TComplejo Obtener(const TListaPos &) const;
		// Devuelve TRUE si el elemento está en la lista, FALSE en caso contrario
		bool Buscar(const TComplejo &);
		// Devuelve la longitud de la lista
		int Longitud();
		// Devuelve la primera posición en la lista
		TListaPos Primera() const;
		// Devuelve la última posición en la lista
		TListaPos Ultima() const;
	
	// FUNCIONES AMIGAS
	// Sobrecarga del operador salida
	friend ostream& operator<<(ostream &, const TListaCom &); 
    friend class TListaNodo;
    friend class TListaPos;
};

#endif