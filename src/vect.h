#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <string>
#include <memory>


// deklaracija potrebna za testiranje
template <typename> class VectTest;

template <typename T>
class Vect
{
    friend class VectTest<T>;  // da testovi mogu dohvatiti privatne varijable
    friend class VectTestPair;
    
public:

    // template<typename U>
    // friend std::ostream& operator<<( std::ostream& f, const Vect<U>& obj);

    template<typename U>
    friend Vect<U> operator+( const Vect<U> &, const Vect<U> & );

    template<typename U>
    friend Vect<U> operator-( const Vect<U> &, const Vect<U> & ); 

    explicit Vect(size_t n = 0, T v= {});  // Ctor
    // Kontrola kopiranja dolazi ovdje
    // CCtor
    Vect(const Vect<T>& obj);
    // MCtor
    Vect(Vect && obj)noexcept;
    // OP
    Vect& operator=(const Vect& obj);//ide li tu Vect<T>?
    // MOP
    Vect& operator=(Vect && obj)noexcept;
    // DTOR
    ~Vect();

    // dohvat elemenata (operator [])
    T operator[](size_t i) const { return *(mdata + i); }
    T& operator[](size_t i) { return *(mdata +i); }
    // push_back metoda
    void push_back (const T& elem);

     // info rutine size() i capacity()
    size_t size() const{ return mfirst_free - mdata; }
    size_t capacity() const{ return mend - mdata; };
     // operatori +=, -=, *=
    Vect& operator+=(const Vect& obj);
    Vect& operator-=(const Vect& obj);
    Vect& operator*=(T const & scalar); 

     // euklidska norma vraća double !
     double two_norm() const;
private:
        T *mdata;       // pokazivač na prvi element
        T *mfirst_free; // pokazivač na prvo slobodno mjesto
        T *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)
  
        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();

      	// realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je 
        // vektor prazan alociraj jedan element. 
        void reallocate();

        // dodati vlastite privatne metode.
	
        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo 
        // statičkim. Ne zaboraviti definirati ga.
        static std::allocator<T> alloc;
};

template<typename T>
std::allocator<T> Vect<T>::alloc;

// Deklaracija operator +, - i << 
template<typename T>
Vect<T> operator+ ( const Vect<T> & obj1, const Vect<T> & obj2);

template<typename T>
Vect<T> operator- ( const Vect<T> & obj1, const Vect<T> & obj2);

template<typename T>
std::ostream& operator<<( std::ostream& f, const Vect<T> & obj );

// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
