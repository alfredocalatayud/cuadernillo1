#include "tlistacom.h"

//  TLISTANODO

TListaNodo::TListaNodo() {
    e = TComplejo();
    siguiente = NULL;
    anterior = NULL;
}

TListaNodo::TListaNodo(const TListaNodo &p_nodo) {
    e = p_nodo.e;
    siguiente = p_nodo.siguiente;
    anterior = p_nodo.anterior;
}

TListaNodo::~TListaNodo() {
    e.~TComplejo();
    siguiente = NULL;
    anterior = NULL;
}


// TODO: no hay operador desigualdad creado
TListaNodo&
TListaNodo::operator=(const TListaNodo &p_nodo) {
    if(this != &p_nodo) {
        (*this).~TListaNodo();

        e = p_nodo.e;
        siguiente = p_nodo.siguiente;
        anterior = p_nodo.anterior;
    }
    
    return *this;
}

// TLISTA POS

TListaPos::TListaPos() {
    pos = NULL;
}

TListaPos::TListaPos(const TListaPos &p_lpos) {
    pos = new TListaNodo(*p_lpos.pos);
}

TListaPos::~TListaPos() {
    // pos->~TListaNodo();
    pos = NULL;
}

TListaPos&
TListaPos::operator=(const TListaPos &p_lpos) {
    if(this != &p_lpos) {
        (*this).~TListaPos();
        pos = p_lpos.pos;
    }

    return *this;
}

bool
TListaPos::operator==(const TListaPos &p_lpos) const{
    bool temp;

    temp = !EsVacia() && !p_lpos.EsVacia();

    while (temp) {
        if (EsVacia() || p_lpos.EsVacia()) 
            return false;
        
        if(pos->e == p_lpos.pos->e) {
            temp = (Siguiente()==p_lpos.Siguiente()) && (Anterior()==p_lpos.Anterior());
            return temp;
        }
        else
            return false;
    }

    return true;
}

bool
TListaPos::operator!=(const TListaPos &p_lpos) {
    return !(*this == p_lpos);
}

TListaPos
TListaPos::Anterior() const {
    TListaPos *aux = new TListaPos();

    if(pos != NULL && pos->anterior != NULL)
        aux->pos = pos->anterior;

    return *aux;
}

TListaPos
TListaPos::Siguiente() const {
    TListaPos *aux = new TListaPos();

    
    if(pos != NULL)
        aux->pos = pos->anterior;

    return *aux;
}

bool
TListaPos::EsVacia() const{
    return (pos == NULL);
}

// TLISTACOM
TListaCom::TListaCom() {
    primero = NULL;
    ultimo = NULL;
}

TListaCom::TListaCom(const TListaCom &p_lcom) {
    primero = NULL;
    ultimo = NULL;

    Copia(p_lcom);
}

TListaCom::~TListaCom() {
    TListaNodo *aux1;
    TListaNodo *aux2 = primero;

    while(aux2 != NULL) {
        aux1 = aux2;
        aux2 = aux2->siguiente;
        delete aux1;
    }

    primero = NULL;
    ultimo = NULL;
}

TListaCom&
TListaCom::operator=(const TListaCom &p_lcom) {
    if(!p_lcom.EsVacia() || this !=&p_lcom) { // TODO: this!=&p_lcom
        (*this).~TListaCom();
        Copia(p_lcom);
    }

    return *this;
}

bool 
TListaCom::operator==(const TListaCom &p_lcom) {
    TListaPos pos1 = Primera();
    TListaPos pos2 = p_lcom.Primera();

    while(!pos1.EsVacia() && !pos2.EsVacia()) {
        if (pos1 != pos2)
            return false;
        
        pos1 = pos1.Siguiente();
        pos2 = pos2.Siguiente();
    }

    if(!pos1.EsVacia() || !pos2.EsVacia())
        return false;

    return true;
}

bool
TListaCom::operator!=(const TListaCom &p_lcom) {
    return !(*this == p_lcom);
}


// TODO: ¿Lo estoy haciendo al reves?
TListaCom
TListaCom::operator+(const TListaCom &p_lcom) {
    TListaCom suma(*this);
    TListaPos pos = p_lcom.Primera();

    while(!pos.EsVacia()) {
        suma.InsCabeza(p_lcom.Obtener(pos));
        pos = pos.Siguiente();
    }

    return suma;
}

TListaCom
TListaCom::operator-(const TListaCom &p_lcom) {
    TListaCom resta(*this);
    TListaPos pos = p_lcom.Primera();

    while(!pos.EsVacia()) {
        resta.Borrar(p_lcom.Obtener(pos));
        pos = pos.Siguiente();
    }

    return resta;
}

bool
TListaCom::EsVacia() const {
    return primero == NULL;
}

bool
TListaCom::InsCabeza(const TComplejo &p_com) {
    TListaNodo *nodo_cabeza = new TListaNodo();

    if (nodo_cabeza == NULL) 
        return false;
    
    
    nodo_cabeza->e = p_com;
    nodo_cabeza->siguiente = primero;

    if(primero != NULL) {
        primero->anterior = nodo_cabeza;
    }

    primero = nodo_cabeza;

    return true;
}

bool
TListaCom::InsertaI(const TComplejo &p_com, const TListaPos &pos) {
    if (pos.EsVacia()) 
        return false;
    

    TListaNodo *nodo = new TListaNodo();
    if (nodo == NULL) 
        return false;
    
    TListaNodo *nodo_pos = pos.pos;

    nodo->e = p_com;
    nodo->siguiente = nodo_pos;
    nodo->anterior = nodo_pos->anterior;

    if(nodo_pos->anterior != NULL)
        nodo_pos->anterior = nodo;

    return true;
}

bool
TListaCom::InsertaD(const TComplejo &p_com, const TListaPos &p_pos) {
    if (p_pos.EsVacia()) 
        return false;
    
    // TListaNodo *nodo = new TListaNodo();
    
    // if(nodo == nullptr)
    //     return false;
    
    
    // TListaNodo *nodo_pos = pos.pos;

    // nodo->e = p_com;
    // nodo->anterior = nodo_pos;
    // nodo->siguiente = nodo_pos->siguiente;

    // if(nodo_pos->siguiente != NULL)
    //     nodo_pos->siguiente->anterior = nodo;
    
    // nodo_pos->siguiente = nodo;

    TListaNodo *actual = primero;
    TListaNodo *anterior = NULL;

    while(actual != NULL && actual != p_pos.pos) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) 
        return false;

    TListaNodo *nodonuevo = new TListaNodo();
    if(nodonuevo == NULL) 
        return false;

    nodonuevo->e = p_com;
    nodonuevo->siguiente = actual->siguiente;
    actual->siguiente = nodonuevo;

    if (ultimo == actual) 
        ultimo = nodonuevo;
    
    return true;
}

bool 
TListaCom::Borrar(const TComplejo &p_com) {    
    TListaNodo *nodo = primero;
    while (nodo != NULL && nodo->e != p_com)
        nodo = nodo->siguiente;

    if (nodo != NULL) {
        if (nodo == primero) 
            primero = primero->siguiente;
        else
            nodo->anterior->siguiente = nodo->siguiente;

        if (nodo == ultimo)
            ultimo = nodo->anterior;
        else
            nodo->siguiente->anterior = nodo->anterior;

        delete nodo;
        return true;
    }

    return false;
} 

bool
TListaCom::BorrarTodos(const TComplejo &p_com) {
    TListaNodo *nodo = primero;

    while (nodo != NULL && nodo->e != p_com)
        nodo = nodo->siguiente;

    bool borrado = false;
    while(nodo != NULL) {
        if (nodo->e == p_com) {
            if(nodo == primero)
                primero = nodo->siguiente;
            else 
                nodo->anterior->siguiente = nodo->siguiente;
            
            if(nodo == ultimo)
                ultimo = nodo->anterior;
            else 
                nodo->siguiente->anterior = nodo->anterior;

            TListaNodo *borra_nodo = nodo;
            nodo = nodo->siguiente;
            delete borra_nodo;

            borrado = true;
        }
        else 
            nodo = nodo->siguiente;
    }

    return borrado;
}

bool
TListaCom::Borrar(const TListaPos &p_pos) {
    if(EsVacia() || p_pos.EsVacia())
        return false;
    
    if (p_pos == Primera()) { 
        TListaNodo *sig = p_pos.pos->siguiente;
        delete p_pos.pos;
        primero = sig;

        if (primero == NULL)  
            ultimo = NULL; 
        else
            primero->anterior = NULL;
    }
    else if (p_pos == Ultima()) {
        TListaNodo *ant = p_pos.pos->anterior;
        delete p_pos.pos;
        ultimo = ant;
        ultimo->siguiente = NULL;
    }
    else {
        TListaNodo *sig = p_pos.pos->anterior;
        TListaNodo *ant = p_pos.pos->siguiente;
        delete p_pos.pos;

        ant->siguiente = sig;
        sig->anterior = ant;
    }

    p_pos.~TListaPos();
    // p_pos.pos = NULL;
    return true;    
}

TComplejo
TListaCom::Obtener(const TListaPos &p_pos) const {
    if(p_pos.EsVacia())
        return TComplejo();
    
    return p_pos.pos->e;
}

bool
TListaCom::Buscar(const TComplejo &p_com) {
    TListaPos pos = Primera();

    while(!pos.EsVacia()) {
        TComplejo c = Obtener(pos);

        if(c == p_com) 
            return true;

        pos = pos.Siguiente();        
    }

    return false;
} 

int
TListaCom::Longitud() {
    int longitud = 0;

    TListaPos pos = Primera();

    while(!pos.EsVacia()) {
        longitud++;
        pos = pos.Siguiente();
    }

    return longitud;
}

TListaPos 
TListaCom::Primera() const {
    if(EsVacia()) 
        return TListaPos();

    TListaPos pri;
    pri.pos = primero;

    return pri;
}

TListaPos 
TListaCom::Ultima() const {
    if(EsVacia()) 
        return TListaPos();

    TListaPos ult;
    ult.pos = ultimo;

    return ult;
}

ostream&
operator<<(ostream &s, const TListaCom &obj) {
    s << "{";
    TListaPos aux = obj.Primera();

    while ((!aux.EsVacia())) {
        TComplejo complejo = obj.Obtener(aux);
        s << complejo;
        cout << "aux" << endl;
        aux = aux.Siguiente();
        
        if(!aux.EsVacia())
            s << " ";
    }
    
    s << "}";

    return s;
}

void
TListaCom::Copia(const TListaCom &p_lcom) {
    TListaPos pos = p_lcom.Primera();

    while(!pos.EsVacia()) {
        TComplejo complejo = p_lcom.Obtener(pos);

        cout << complejo << endl;
        if(ultimo == NULL) 
            InsCabeza(complejo);
        else
            InsertaD(complejo, Ultima());

        pos = pos.Siguiente();
    }
}