template <typename T>
string_map<T>::string_map(): _size(0), raiz(new Nodo()){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    destruir(raiz);
    raiz = new Nodo(d.raiz);
    _size = d._size;
    return *this;
}

template <typename T>
void string_map<T>::destruir(Nodo* nodo) {
    for (int i = 0; i < nodo->siguientes.size(); ++i) {
        if (nodo->siguientes[i] != nullptr)
            destruir(nodo->siguientes[i]);
    }
    delete nodo->definicion;
    delete nodo;
}

template <typename T>
string_map<T>::~string_map(){
    destruir(raiz);
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& def) {
    if (raiz == nullptr)
        raiz = new Nodo();
    string clave = def.first;
    T* signi = new T(def.second);
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int letra = int(clave[i]);
        if (actual->siguientes[letra] == nullptr){
            actual->siguientes[letra] = new Nodo();
            actual = actual->siguientes[letra];
        } else {
            actual = actual->siguientes[letra];
        }
    }
    if (actual->definicion != nullptr) {
        delete actual->definicion;
        actual->definicion = signi;
    }else{
        actual->definicion = signi;
        _size ++;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if (raiz == nullptr)
        raiz = new Nodo();
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int letra = int(clave[i]);
        if (actual->siguientes[letra] == nullptr){
            actual->siguientes[letra] = new Nodo();
            actual = actual->siguientes[letra];
        } else {
            actual = actual->siguientes[letra];
        }
    }
    if (actual->definicion == nullptr) {
        actual->definicion = new T;
        _size++;
    }
    return *(actual->definicion);
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    if (raiz == nullptr)
        return 0;
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int letra = int(clave[i]);
        if (actual->siguientes[letra]==nullptr)
            return 0;
        actual = actual->siguientes[letra];
    }
    if (actual->definicion != nullptr)
        return 1;
    return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    const T res = at(clave);
    return res;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int letra = int(clave[i]);
        actual = actual->siguientes[letra];
    }
    return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    if (raiz == nullptr)
        return;
    Nodo* ultimo = raiz;
    Nodo* actual = raiz;
    int ultimaPos = 0;
    for (int i = 0; i < clave.size(); ++i) {
        int letra = int(clave[i]);
        if (actual->siguientes[letra]==nullptr)
            return;
        if (actual->siguientes[letra]->definicion != nullptr){
            ultimo = actual;
            ultimaPos = i+1;
        } else {
            for (int j = 0; j < actual->siguientes.size(); ++j) {
                if (j != letra && actual->siguientes[j] != nullptr){
                    ultimo = actual;
                    ultimaPos = i+1;
                    }
            }
        }
        actual = actual->siguientes[letra];
    }
    delete actual->definicion;
    actual->definicion = nullptr;
    bool tieneH = false;
    for (int i = 0; i < actual->siguientes.size(); ++i) {
        if (actual->siguientes[i]!= nullptr) {
            tieneH = true;
            break;
        }
    }
    if (!tieneH){
        int letra = int(clave[ultimaPos]);
        Nodo* siguiente = ultimo->siguientes[letra];
        ultimo->siguientes[letra] = nullptr;
        ultimo = siguiente;
        ultimaPos++;
        for (int i = ultimaPos; i < clave.size(); ++i) {
            letra = int(clave[ultimaPos]);
            siguiente = ultimo->siguientes[letra];
            delete ultimo;
            ultimo = siguiente;
        }
        delete ultimo;
    }
    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}