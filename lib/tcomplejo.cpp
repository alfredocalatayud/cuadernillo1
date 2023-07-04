#include "tcomplejo.h"
#include <cmath>

TComplejo::TComplejo() {
    re = im = 0;
}

TComplejo::TComplejo(double p_re) {
    re = p_re;
    im = 0;
}

TComplejo::TComplejo(double p_re, double p_im) {
    re = p_re;
    im = p_im;
}

TComplejo::TComplejo(const TComplejo & c) {
    re = c.re;
    im = c.im;
}

TComplejo::~TComplejo() {
    re = im = 0;
}

TComplejo&
TComplejo::operator=(const TComplejo &op2) {
    if(this != &op2) {
        (*this).~TComplejo();

        re = op2.re;
        im = op2.im;
    }

    return *this;
}

//  Operadores aritméticos
TComplejo
TComplejo::operator+(const TComplejo &op2) {
    TComplejo temp;

    temp.re = re + op2.re;
    temp.im = im + op2.im;

    return temp;
}

TComplejo
TComplejo::operator-(const TComplejo &op2) {
    TComplejo temp;

    temp.re = re - op2.re;
    temp.im = im - op2.im;

    return temp;
}

TComplejo
TComplejo::operator*(const TComplejo &op2) {
    TComplejo temp;

    temp.re = re * op2.re;
    temp.im = im * op2.im;

    return temp;
}

TComplejo
TComplejo::operator+(double p_re) {
    TComplejo temp(p_re);

    temp.re = re + temp.re;
    temp.im = im;

    return temp;
}

TComplejo
TComplejo::operator-(double p_re) {
    TComplejo temp(p_re);

    temp.re = re - temp.re;
    temp.im = im;

    return temp;
}

TComplejo
TComplejo::operator*(double p_re) {
    TComplejo temp;

    temp.re = re * p_re;
    temp.im = im * p_re;

    return temp;
}

//  Otros operadores
bool
TComplejo::operator==(const TComplejo &op2) {
    bool temp;

    temp = (re==op2.re && im==op2.im) ? true : false;

    return temp;
}

bool
TComplejo::operator!=(const TComplejo &op2) {
    return !(*this == op2);
}

double
TComplejo::Re(void) {
    return re;
}

double
TComplejo::Im(void) {
    return im;
}

void
TComplejo::Re(double p_re) {
    re = p_re;
}

void
TComplejo::Im(double p_im) {
    im = p_im;
}

double
TComplejo::Arg(void) {
    double argumento = atan2(im, re);

    return argumento;
}

double
TComplejo::Mod(void) {
    double modulo = sqrt(pow(re, 2) + pow(im, 2));

    return modulo;
}

//  Funciones amigas
ostream&
operator<<(ostream &s, const TComplejo &obj) {
    s << "(" << obj.re << " " << obj.im << ")";

    return s;
}

TComplejo
operator+(double v_re, const TComplejo &op2) {
    TComplejo temp(op2);

    temp.re = temp.re + v_re;

    return temp;
}

TComplejo
operator-(double v_re, const TComplejo &op2) {
    TComplejo temp(op2);

    temp.re = v_re - temp.re;
    temp.im = -op2.im;

    return temp;
}

TComplejo
operator*(double v_re, const TComplejo &op2) {
    TComplejo temp(op2);

    temp.re = temp.re * v_re;
    temp.im = temp.im * v_re;

    return temp;
}