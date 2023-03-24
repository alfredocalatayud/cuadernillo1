#include "tlistacom.h"

//  TLISTANODO

TListaNodo::TListaNodo() {
    e = NULL;
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

    temp = !EsVacia && !p_lpos.EsVacia();

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

    if(pos != NULL && pos->siguiente != NULL)
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
    // TListaPos pos = p_lcom.Ultima();

    // while(!pos.EsVacia()) {
    //     TComplejo com = p_lcom. p_lcom.Obtener(pos);
    //     InsCabeza(com);
    //     pos = pos.Anterior();
    // }

    if (p_lcom.E)
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
    if(!p_lcom.EsVacia()) { // TODO: this!=&p_lcom
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
}

bool
TListaCom::EsVacia() const {
    return primero == NULL;
}

bool
TListaCom::InsCabeza(const TComplejo &p_com) {
    TListaNodo *aux = primero;
    TListaNodo *nodo = new TListaNodo();

    if (nodo == NULL) 
        return false;
    

    nodo->e = p_com;
    nodo->siguiente = this->primero;
    this->primero = nodo;

    return true;
}

bool
TListaCom::InsertaI(const TComplejo &p_com, const TListaPos &pos) {
    if (pos.EsVacia()) 
        return false;
    

    TListaNodo *nodo = new TListaNodo();
    if (nodo == NULL) 
        return false;
    
    // TODO: Revisar esta fumada
    nodo->e = p_com;
    nodo->siguiente = pos.pos;
    pos.pos->anterior->siguiente = nodo;
    nodo->anterior = pos.pos->anterior;
    pos.pos->anterior = nodo;

    return true;
}

bool
TListaCom::InsertaD(const TComplejo &p_com, const TListaPos &pos) {
    if (pos.EsVacia()) 
        return false;
    

    TListaNodo *nodo = new TListaNodo();
    if (nodo == NULL) 
        return false;
    
    // TODO: Hacer 

    return true;
}

bool 
TListaCom::Borrar(const TComplejo &p_com) {
    // if(!Buscar(p_com))
    //     return false;
    
    // TListaNodo *aux = primero;

    // if(primero->e == p_com) {
    //     primero = primero->siguiente;
    //     return true;
    // }

    // while(aux->siguiente != NULL) {
    //     if(aux->siguiente->e == p_com) {
    //         aux->siguiente = aux->siguiente->siguiente;
    //         return true;
    //     }
    //     aux = aux->siguiente;
    // }

    // return false;

    if(EsVacia()) 
        return false;
    
    TListaPos pos = Primera();

    while(!pos.EsVacia()) {
        TComplejo &elem = (*this).Obtener(pos);
    }
}

bool
TListaCom::Borrar(const TListaPos &pos) {
    if(EsVacia() || pos.EsVacia())
        return false;
    
    if (pos == Primera()) {
        TListaNodo *temp = pos.pos->siguiente;
        pos.pos->siguiente = temp->siguiente;
        delete temp;
    }
    else {
        TListaNodo *anterior = Primera().pos;
        while (anterior->siguiente != p.pos)
            anterior = anterior->siguiente;
        
        TListaNodo *temp = p.pos;
        anterior->siguiente  = temp->siguiente;
        delete temp;
    }

    return true;
}

void
TListaCom::Copia(const TListaCom &p_lcom) {
    TListaPos pos = p_lcom.Ultima();

        while(!pos.EsVacia()) {
            TComplejo com = p_lcom.Obtener(pos);
            InsCabeza(com);
            pos = pos.Anterior();
        }
}