#include <cmath>

template<typename T>
Vect<T>::Vect(size_t n, T v){
    if( n != 0 ){
        mdata = alloc.allocate(n);
        mend = mdata + n;
        mfirst_free = mend;

        std::uninitialized_fill(mdata,mend,v);
    }
    else {
        mdata = mfirst_free = mend = nullptr;
    }
}

template<typename T>
void Vect<T>::free(){

    //prvo destroy
    for( size_t i = 0; i < size(); ++i){
        alloc.destroy(mdata + i);
    }
    //onda deallocate
    alloc.deallocate(mdata,capacity());
    //mozda pripazit sta ako je vec prazno
}

template<typename T>
void Vect<T>::reallocate(){
    
    size_t velicina = size();
    if( velicina != 0){
        T * mndata = alloc.allocate(2 * velicina);

        std::uninitialized_copy(mdata,mend,mndata);

        //tu unistimo ovu staru memoriju
        free();

        mend = mndata + (2 * velicina);
        mfirst_free = mndata + velicina;
        mdata = mndata;
    }
    else {
        mdata = alloc.allocate(1);
        mend = mdata + 1;
        mfirst_free = mdata;
    }

}
//CCtor
template<typename T>
Vect<T>::Vect( const Vect<T>& obj){
    mdata = alloc.allocate(obj.capacity()); // ili obj.size()
    mfirst_free = mdata + obj.size();
    mend = mdata + obj.capacity();

    std::uninitialized_copy(obj.mdata,obj.mfirst_free,mdata);
}
//MCtor
template<typename T>
Vect<T>::Vect( Vect<T> && obj )noexcept{
    mdata = obj.mdata;
    mfirst_free = obj.mfirst_free;
    mend = obj.mend;

    obj.mdata = obj.mfirst_free = obj.mend = nullptr;
}
//OP
template<typename T>
Vect<T>& Vect<T>::operator= ( const Vect<T> & obj ){
    //moramo pazit na a = a
    if( mdata == obj.mdata ) return *this;
    free(); //mozda pripazit sto ako je vec prazno

    mdata = alloc.allocate(obj.capacity());
    mfirst_free = mdata + obj.size();
    mend = mdata + obj.capacity();

    std::uninitialized_copy(obj.mdata,obj.mfirst_free,mdata);
    return *this;
}
//MOP
template<typename T>
Vect<T>& Vect<T>::operator=( Vect<T> && obj )noexcept{
    if(mdata == obj.mdata) return *this;
    free();
    mdata = obj.mdata;
    mfirst_free = obj.mfirst_free;
    mend = obj.mend;

    obj.mdata = obj.mfirst_free = obj.mend = nullptr;
    return *this;
}
//DTor
template<typename T>
Vect<T>::~Vect(){
    //mozda pripazit sta ako je vec prazno
    free();
}

template<typename T>
void Vect<T>::push_back( const T & elem ){
    if(mfirst_free == mend){
        this->reallocate();
    }
    *mfirst_free = elem;
    mfirst_free++;
}

template<typename T>
double Vect<T>::two_norm()const{
    //if(mdata == mfirst_free) return 0;
    
    double rezultat = 0;
    //auto it = mdata; it < mfirst_free; ++it
    for( size_t i = 0; i < this->size(); ++i ){
        rezultat += ((*this)[i]) * ((*this)[i]);
    }
    return sqrt(rezultat);
}

template<typename T>
Vect<T>& Vect<T>::operator+=( const Vect<T> & obj ){
    if( this->size() == obj.size() ){
        // ili auto it = mdata, ILI if != mfirst_free
        //T* it = mdata; it < mfirst_free; ++it
        for( size_t i = 0; i < size(); ++i ){
            *(mdata + i) = *(mdata + i) + obj[i];
        }
    }
    // ako nisu iste velicine ne radimo nista
    return *this;
}

template<typename T>
Vect<T>& Vect<T>::operator-=( const Vect<T> & obj ){
    if( this->size() == obj.size() ){
        // ili auto it = mdata, ILI if != mfirst_free
        //T* it = mdata; it < mfirst_free; ++it
        for( size_t i = 0; i < size(); ++i ){
            *(mdata + i) = *(mdata + i) - obj[i];
        }
    }
    // ako nisu iste velicine ne radimo nista
    return *this;
}

template<typename T>
Vect<T>& Vect<T>::operator*= ( T const & scalar ){
    for( size_t i = 0; i < size(); ++i ){
        *(mdata + i) = (*(mdata + i)) * scalar;
    }
    return *this;
}

template<typename T>
Vect<T> operator+ ( const Vect<T> & obj1, const Vect<T> & obj2){
    //ako nisu istih dimenzija vracam kopiju prvog vektora
    if( obj1.size() == obj2.size() ){
        // ili auto it = mdata, ILI if != mfirst_free
        //T* it = mdata; it < mfirst_free; ++it
        Vect<T> rezV;
        for( size_t i = 0; i < obj1.size(); ++i ){
            rezV.push_back( obj1[i] + obj2[i] );
        }
        return rezV;
    }
    return obj1;
}

template<typename T>
Vect<T> operator- ( const Vect<T> & obj1, const Vect<T> & obj2){
    //ako nisu istih dimenzija vracam kopiju prvog vektora
    if( obj1.size() == obj2.size() ){
        // ili auto it = mdata, ILI if != mfirst_free
        //T* it = mdata; it < mfirst_free; ++it
        Vect<T> rezV;
        for( size_t i = 0; i < obj1.size(); ++i ){
            rezV.push_back( obj1[i] - obj2[i] );
        }
        return rezV;
    }
    return obj1;
}

//Treba popraviti, overload

template<typename T>
std::ostream& operator<<( std::ostream& f, const Vect<T> & obj ){
    f << "[";
    if( obj.size() != 0 ) f << obj[0];
    for( size_t i = 1; i < obj.size(); ++i ){
        f << "," << obj[i];
    }
    f << "]";
    return f;
}


