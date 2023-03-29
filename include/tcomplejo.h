#ifndef TCOMPLEJO_H_
#define TCOMPLEJO_H_

#include <iostream>

using namespace std;

class TComplejo {
	private:
		double re;	// PARTE REAL
		double im;	// PARTE IMAGINARIA
	
	public:
		// Constructor por defecto: PARTE REAL e IMAGINAR inicializamos a 0
		TComplejo();
		// Constructor a partir de la PARTE REAL
		TComplejo(double);
		// Constructor a partir de la PARTE REAL e IMAGINARIA
		TComplejo(double, double);
		// Constructor copia
		TComplejo(const TComplejo &);
		// Destructor
		~TComplejo();
		// Sobrecarga del operador asignación
		TComplejo& operator=(const TComplejo&);
		
		// METODOS
		// SOBRECARGA DE OPERADORES ARTIMÉTICOS
		TComplejo operator+(const TComplejo&);
		TComplejo operator-(const TComplejo&);
		TComplejo operator*(const TComplejo&);
		TComplejo operator+(double);
		TComplejo operator-(double);
		TComplejo operator*(double);
    
		// OTROS OPERADORES
		bool operator==(const TComplejo&);	// IGUALDAD de números complejos
		bool operator!=(const TComplejo&);	// DESIGUALDAD de números complejos
		
		double Re(void);	// Devuelve PARTE REAL
		double Im(void); 	// Devuelve PARTE IMAGINARIA
		
		void Re(double);	// Modifica PARTE REAL
		void Im(double);	// Modifica PARTE IMAGINARIA
		
		double Arg(void);	// Calcula el Argumento (en Radiales)
		double Mod(void);	// Calcula el Módulo
		
	// FUNCIONES AMIGAS
	friend ostream& operator<<(ostream &, const TComplejo &);
	
	friend TComplejo operator+(double, const TComplejo&);
	friend TComplejo operator-(double, const TComplejo&);
	friend TComplejo operator*(double, const TComplejo&);
};

#endif