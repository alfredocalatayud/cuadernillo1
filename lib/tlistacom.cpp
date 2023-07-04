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
    // bool temp;

    // temp = !EsVacia() && !p_lpos.EsVacia();

    // while (temp) {
    //     if (EsVacia() || p_lpos.EsVacia())
    //         return false;

    //     if(pos->e == p_lpos.pos->e) {
    //         temp = (Siguiente()==p_lpos.Siguiente()) && (Anterior()==p_lpos.Anterior());
    //         return temp;
    //     }
    //     else
    //         return false;
    // }

    // return true;

    return p_lpos.pos == pos;
}

bool
TListaPos::operator!=(const TListaPos &p_lpos) {
    return !(*this == p_lpos);
}

TListaPos
TListaPos::Anterior() const {
    TListaPos aux;

    if(pos != NULL && pos->anterior != NULL)
        aux.pos = pos->anterior;

    return aux;
}

TListaPos
TListaPos::Siguiente() const {
    //TListaPos *aux = new TListaPos();
    TListaPos siguiente;

    if(pos != NULL)
        //aux->pos = pos->siguiente;
        siguiente.pos = pos->siguiente;

    return siguiente;
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
    // Limpiar();

    // Copia(p_lcom);
    primero = NULL;
    ultimo = NULL;

    *this = p_lcom;
}

void
TListaCom::Limpiar() {
    TListaPos pos;

    while(!EsVacia()) {
        pos = Primera();
        primero = primero->siguiente;
        delete pos.pos;
    }

    ultimo = NULL;
}

void
TListaCom::Copia(const TListaCom &p_lcom)  {
    // TListaPos pos = p_lcom.Primera();

    // while(!pos.EsVacia()) {
    //     TComplejo complejo = p_lcom.Obtener(pos);

    //     // cout << complejo << endl;
    //     if(ultimo == NULL)
    //         InsCabeza(complejo);
    //     else
    //         InsertaD(complejo, Ultima());

    //     pos = pos.Siguiente();
    // }

    // TListaNodo *nodoactual = new TListaNodo();

    // if (!p_lcom.EsVacia()) {
    //     nodoactual = p_lcom.ultimo;

    //     while (nodoactual != NULL) {
    //         InsCabeza(nodoactual->e);
    //         nodoactual = nodoactual->siguiente;
    //     }
    // }
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
    if(this != &p_lcom) {
        if(!EsVacia())
            (*this).~TListaCom();

        TListaNodo *nodo_actual = new TListaNodo();

        nodo_actual = p_lcom.ultimo;

        while (nodo_actual != NULL)
        {
            InsCabeza(nodo_actual->e);
            nodo_actual = nodo_actual -> anterior;
        }

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


// TODO: ¿Lo estoy haciendo al reves? SI XDDDDDDDDDD
TListaCom
TListaCom::operator+(const TListaCom &p_lcom) {
    TListaCom suma(*this);
    TListaNodo *aux;

    aux = p_lcom.primero;
    while(aux != NULL) {
        suma.InsertarD(aux->e, suma.Ultima());
        aux = aux->siguiente;
    }

    return suma;
}

// TODO: revisar, porque si la suma estaba mal esta también lo va a estar. Pasa el test, pero eso no quiere decir que está bien :)
TListaCom
TListaCom::operator-(const TListaCom &p_lcom) const{
    TListaCom resta;
    TListaNodo *actual;

    if (primero != NULL && p_lcom.ultimo != NULL and &p_lcom != NULL) {
        actual = ultimo;

        while(actual != NULL) {
            if(p_lcom.Buscar(actual->e) == false)
                resta.InsCabeza(actual->e);
            actual = actual->anterior;
        }
    }

    return resta;
}

bool
TListaCom::EsVacia() const {
    return (primero == NULL && ultimo == NULL);
}

bool
TListaCom::InsCabeza(const TComplejo &p_com) {
    TListaNodo *nodo_cabeza = new TListaNodo();

    if (nodo_cabeza == NULL)
        return false;


    nodo_cabeza->e = p_com;

    // nodo_cabeza->siguiente = primero;

    // if(primero != NULL) {
    //     primero->anterior = nodo_cabeza;
    // }

    // primero = nodo_cabeza;

    if(EsVacia() )
        primero = ultimo = nodo_cabeza;
    else {
        nodo_cabeza->siguiente = primero;
        primero->anterior = nodo_cabeza;
        primero = nodo_cabeza;
    }

    return true;
}

bool
TListaCom::InsertarI(const TComplejo &p_com, const TListaPos &p) {
    if (p.EsVacia())
        return false;


    // nodo->e = p_com;
    // nodo->siguiente = p.pos;

    // if(nodo->anterior != NULL)
    //     nodo->anterior->siguiente = nodo;
    // else
    //     primero = nodo;

    // p.pos->anterior = nodo;

    // return true;

    TListaNodo *nodo = new TListaNodo();
    TListaNodo *aux = new TListaNodo();
    if (nodo == NULL || aux == NULL)
        return false;



    aux->e.operator=(p_com);
    nodo = Primera().pos;

    while(nodo != NULL) {
        if(nodo == p.pos) {
            if(nodo->anterior != NULL)
                aux->anterior = nodo->anterior;

            aux->siguiente = nodo;

            if(nodo->anterior!=NULL)
                nodo->anterior->siguiente=aux;

            nodo->anterior = aux;

            if(primero == nodo)
                primero = aux;

            return true;
        }
        nodo = nodo->siguiente;
    }
    return false;
}

bool
TListaCom::InsertarD(const TComplejo &p_com, const TListaPos &p_pos) {
    if (p_pos.EsVacia())
        return false;

    TListaNodo *nodo = new TListaNodo();
    if(nodo == NULL)
        return false;

    nodo->e = p_com;
    nodo->siguiente = p_pos.pos->siguiente;
    nodo->anterior = p_pos.pos;

    if(p_pos.pos->siguiente != NULL)
        p_pos.pos->siguiente->anterior = nodo;
    else
        ultimo = nodo;

    p_pos.pos->siguiente = nodo;

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
        TListaNodo *sig = p_pos.pos->siguiente;
        TListaNodo *ant = p_pos.pos->anterior;
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
TListaCom::Buscar(const TComplejo &p_com) const{
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
    // if(EsVacia()) TODO: ESTA COMPROBACIÓN DEBERÍA HACERSE
    //     return TListaPos();

    TListaPos pri;
    pri.pos = primero;

    return pri;
}

TListaPos
TListaCom::Ultima() const {
    // if(ultimo==NULL)
    //     return TListaPos();

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
        aux = aux.Siguiente();

        if(!aux.EsVacia())
            s << " ";
    }

    s << "}";

    return s;
}

