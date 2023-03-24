#include "tvectorcom.h"

TVectorCom::TVectorCom() {
    c = NULL;
    tamano = 0;
}

TVectorCom::TVectorCom(int p_tam) {
    if(p_tam <= 0) {
        c = NULL;
        tamano = 0;
    }
    else {
        tamano = p_tam;
        c = new TComplejo[p_tam];
    }

    // error = TComplejo();
}

TVectorCom::TVectorCom(const TVectorCom &p_vector) {
    this->~TVectorCom();
    tamano = p_vector.tamano;

    for (int i = 0; i < tamano; i++)
        c[i] = p_vector[i+1];
}

// void
// TVectorCom::vaciaVector() {
//     if(c != NULL)
//         delete [] c;
    
//     tamano = 0;
// }

TVectorCom::~TVectorCom() {
    if(c != NULL)
        delete [] c;
    
    tamano = 0;
}

TVectorCom&
TVectorCom::operator=(const TVectorCom &p_vector) {
    this->~TVectorCom();

    tamano = p_vector.tamano;
    c = new TComplejo[tamano]();

    for (int i = 0; i < tamano; i++) 
        c[i] = p_vector[i+1];

    return *this;
}

//  Métodos
bool
TVectorCom::operator==(const TVectorCom &p_vector) {
    if(tamano != p_vector.tamano)
        return false;
    
    for(int i = 0; i < tamano; i++)
        if(c[i] != p_vector[i+1])
            return false;
    
    return true;
}

bool
TVectorCom::operator!=(const TVectorCom &p_vector) {
    return !(*this == p_vector);
}

TComplejo&
TVectorCom::operator[](int n) {
    if (n <= 0)
        return error;
    
    return c != NULL ? c[n-1] : error;
}

TComplejo
TVectorCom::operator[](int n) const {
    if (n <= 0)
        return error;
    
    return c[n-1];
}

int
TVectorCom::Tamano() {
    return tamano;
}

int
TVectorCom::Ocupadas() {
    // TODO: podria hacerlo con el constructor y comparar
    int ocupadas = 0;

    for (int i = 0; i < tamano; i++)
        if(c[i].Re() != 0 || c[i].Im() != 0)
            ocupadas++;

    return ocupadas;
}

bool
TVectorCom::ExisteCom(const TComplejo &p_com) {
    for (int i = 0; i < tamano; i++)
        if (c[i] == p_com) 
            return true;
    
    return false;
}

void
TVectorCom::MostrarComplejos(double p_re) {
    TComplejo* v_com;
    TComplejo temp(p_re);
    TComplejo aux;

    bool coma = false;
    int n_mostrar = 0;

    for(int i = 0; i < tamano; i++) {
        aux = c[i]; // TODO: ¿creo uno nuevo? así debería ir
        if (aux.Re() >= temp.Re())
            n_mostrar++;
    }

    v_com = new TComplejo[n_mostrar]();
    n_mostrar = 0;

    for(int i = 0; i < tamano; i++) {
        aux = c[i]; // TODO: ¿creo uno nuevo? así debería ir
        if (aux.Re() >= temp.Re())
            v_com[n_mostrar++] = aux;
    }
    
    cout << "[";

    for(int i = 0; i < n_mostrar; i++) {
        if (coma) {
            cout << ", ";
            coma = false;
        }
        else 
            coma = true;
        
        cout << v_com[i];
    }

    cout << "]";

}

bool
TVectorCom::Redimensionar(int v_tam) {
    int tam;

    if (v_tam == tamano || v_tam <= 0)
        return false;

    TComplejo* aux = new TComplejo[v_tam]();

    v_tam > tamano ? tam = tamano : tam = v_tam;

    for (int i = 0; i < tam; i++)
        aux[i] = c[i];

    this->~TVectorCom();
    tamano = tam;
    c = aux;

    return true; 
}

ostream&
operator<<(ostream &s, const TVectorCom &obj) {
    s << "[";

    for (int i = 1; i <= obj.tamano; i++) {
        s << "(" << i << ") " << obj[i];

        if(i != obj.tamano)
            s << ", ";
    }

    s << "]";

    return s;
}