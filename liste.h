#include <iostream>
class Complex {
    friend class Matrix;
    friend std::istream& operator>> (std::istream &in, Complex &a);
    friend std::ostream& operator<< (std::ostream &out, const Complex &a);
private:
    double Re;
    double Im;
    int Lin;
    int Col;
public:
    /// Constructori
    Complex () {
        Re = Im = 0;
        Lin = Col = 0;
    }
    Complex (double a, double b, int c, int d) {
        Re = a;
        Im = b;
        Lin = c;
        Col = d;
    }
    /// Supraincarcarea operatorilor
    Complex operator +(const Complex a) {
        Complex number;
        number.Re =  Re + a.Re;
        number.Im =  Im + a.Im;
        number.Lin = Lin;
        number.Col = Col;
        return number;
    }
    Complex operator -(const Complex a) {
        Complex number;
        number.Re =  Re - a.Re;
        number.Im =  Im - a.Im;
        number.Lin = Lin;
        number.Col = Col;
        return number;
    }
    Complex operator *(const Complex a) {
        Complex number;
        number.Re =  Re * a.Re - Im * a.Im;
        number.Im =  Im * a.Im + Im * a.Re + Re * a.Im;
        number.Lin = Lin;
        number.Col = Col;
        return number;
    }
    Complex operator /(const Complex a) {
        Complex number;
        if(a.Re == 0 && a.Im == 0) {
            return a;
        }
        number.Re = (Re * a.Re + Im * a.Im) / (a.Re * a.Re + a.Im * a.Im);
        number.Im = (a.Re * Im + Re * a.Im) / (a.Re * a.Re + a.Im * a.Im);
        number.Lin = Lin;
        number.Col = Col;
        return number;
    }
    bool operator==(const Complex& it) const {
        if(it.Re == this->Re && it.Im == this->Im) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator!=(const Complex& it) const {
        if(it.Re != this->Re || it.Im != this->Im) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator<(const Complex& it) const {
        if(it.Re < this->Re){
            return true;
        }
        if(it.Re > this->Re) {
            return false;
        }
        return it.Im < this->Im;
    }
};

std::ostream& operator<< (std::ostream &out, const Complex &a) {
    out << a.Re << " + " << a.Im << " * i, ";
    return out;
}

std::istream& operator>> (std::istream &in, Complex &a) {
    in >> a.Re;
    in >> a.Im;
    return in;
}

class Lista {
    public:
    struct Iterator;
    Lista() {
        head = tail = nullptr;
    }
    ~Lista() {
        if(!isEmpty()) {
            clear();
        }
    }
    void push_front(Complex elem);
    void push_back(Complex elem);
    void insert_before(Complex elem, Iterator nod);
    void insert_after(Complex elem, Iterator nod);
    Iterator search(Complex value) const;
    void pop_front();
    void pop_back();
    void remove(Iterator nod);
    // Returneaza un iterator catre inceputul listei
    Iterator front() const {
        return Iterator(head);
    }
    // Returneaza un iterator catre sfarsitul listei
    Iterator end() const {
        return Iterator(nullptr);
    }
    bool isEmpty() const {
        return head == nullptr;
    }
    void clear();
    
    private:
    
    struct Nod  { // Clasa Helper; Implementeaza un nod de lista
        Complex data;   // informatia propriu-zisa
        Nod * next; // urm
    };
    Nod * head; // prim
    Nod * tail; // ultim
    public:
    
    struct Iterator {
        friend class Lista; // Lista are acces la membrii privati ai lui Iterator
        Iterator() {
            list = nullptr;
        }
        Iterator(Nod * ls) { list = ls; }
        // Supraincarc operatorul *
        Complex& operator*() {
            if(list != nullptr) {
                return list->data;
            }
            else{
                throw "Null iterator!";
            }
        }
        // Prefix - Trec la urmatorul nod
        Iterator& operator++() {
            list = list->next;
            return *this;
        }
        // Postfix
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const Iterator& it) const {
            if(it.list == this->list) {
                return true;
            }
            else {
                return false;
            }
        }
        bool operator!=(const Iterator& it) const {
            if(!(it == *this)) {
                return true;
            }
            else {
                return false;
            }
        }
    private:
        Nod * list;
    };
};

void Lista::push_front(Complex elem) {
    if(isEmpty()) {
        head = new Nod; // Aloc memorie pentru primul nod
        head->data = elem;
        head->next = nullptr; // Fiind singurul nod, urmatorul este NIMIC adica NULL
        tail = head; // si tail == head
    }
    else {
        Nod * nod = new Nod; // Aloc memorie pentru noul nod
        nod->data = elem;    // Scriu informatia in data
        nod->next = head;    // Leg nod de head
        head = nod;          // nod devine noul head
    }
}

void Lista::push_back(Complex elem) {
    if(isEmpty()) {
        head = new Nod; // Aloc memorie pentru primul nod
        head->data = elem;
        head->next = nullptr; // Fiind singurul nod, urmatorul este NIMIC adica NULL
        tail = head; // si tail == head
    }
    else {
        Nod * nod = new Nod; // Aloc memorie pentru noul nod
        nod->data = elem;    // Scriu informatia in data
        nod->next = nullptr; // Devenind nod terminal, va fi legat de NULL
        tail->next = nod;    // Fostul tail este legat de noul tail
        tail = nod;          // nod devine tail
    }
}

void Lista::insert_after(Complex elem, Iterator nod) {
    Nod * newNod = new Nod; // Aloc memorie pentru noul nod
    newNod->data = elem;    // Scriu informatia in data
    newNod->next = nod.list->next; // newNod se leaga de succesorul lui 'nod'
    nod.list->next = newNod; // Nodul 'nod' se leaga de newNod
    // Daca nodul 'nod' a fost ultimul nod, atunci nodul newNod devine nod terminal
    if(nod.list == tail) {
        tail = newNod;
    }
}

void Lista::insert_before(Complex elem, Iterator nod) {
    Nod * newNod = new Nod; // Aloc memorie pentru noul nod
    newNod->data = nod.list->data; // Copiez informatia din 'nod' in newNod
    nod.list->data = elem; // 'nod' va memora informatia care trebuie adaugata la lista
    newNod->next = nod.list->next; // newNod se leaga de succesorul lui 'nod'
    nod.list->next = newNod; // Nodul 'nod' se leaga de newNod
    // Daca nodul 'nod' a fost ultimul nod, atunci nodul newNod devine nod terminal
    if(nod.list == tail) {
        tail = newNod;
    }
}

Lista::Iterator Lista::search(Complex value) const {
    for(Nod* it = head; it != nullptr; it = it->next) {
        if(it->data == value) {
            return Iterator(it); // Daca am gasit nodul il returnez
        }
    }
    return end(); // Nu am gasit nimic
}

void Lista::pop_front() {
    if(isEmpty()) {
        throw "Empty List"; // Daca lista este vida
    }
    if(head == tail) {// Daca lista are un singur nod
        delete head;
        head = tail = nullptr;
        return;
    }
    Nod * temp = head; // Salvez adresa obiectului head
    head = head->next; // Succesorul lui head devine noul head
    delete temp; // Eliberez memoria ocupata de vechiul obiect head
}

void Lista::remove(Iterator nod) {
    if(isEmpty()) {
        throw "Empty List";
    }
    if(head == tail) {// Daca lista are un singur nod
        delete head;
        head = tail = nullptr;
        return;
    }
    Nod * temp = nod.list->next; // Salvez adresa succesorului lui 'nod'
    // Copiez toata informatia succesorului in 'nod'
    nod.list->data = nod.list->next->data;
    nod.list->next = nod.list->next->next;
    delete temp; // Eliberez memoria ocupata de succesor; il elimin
    if(nod.list->next == nullptr) {
        tail = nod.list;
    }
}

void Lista::pop_back() {
    if(isEmpty()) {
        throw "Empty List";
    }
    if(head == tail) {// Daca lista are un singur nod
        delete head;
        head = tail = nullptr;
        return;
    }
    // Caut predecesorul lui tail
    Nod * pred;
    for(pred = head; pred->next->next != nullptr; pred = pred->next); // For Vid
    pred->next = nullptr; // Predecesorul devine nod terminal
    delete tail; // Eliberez memoria ocupata de vechiul obiect tail
    tail = pred; // Predecesorul devine tail
}

void Lista::clear() {
    Nod *it = head, *temp;
    while(it != nullptr) {
        temp = it; // Salvez adresa nodului curent
        it = it->next; // Trec mai departe
        delete temp; // Distrug nodul curent
    }
    head = tail = nullptr; // Lista Vida
}

class Matrix {
    friend class Complex;
    friend std::istream& operator>> (std::istream &in, Matrix &a);
    friend std::ostream& operator<< (std::ostream &out, const Matrix &a);
private:
    Complex **Mat;
    int n, m;
public:
    Complex& operator()(int i, int j){
        return Mat[i][j];
    }
    Matrix (int n, int m) {
        Mat = new Complex*[n];
        for (int i = 0; i < n; ++i) {
            Mat[i] = new Complex[m];
        }
        this->n = n;
        this->m = m;
    }
    ~Matrix () {
        for(int i = 0; i < n; ++i) {
            delete [] Mat[i];
        }
    }
    ///Supraincarcarea operatorilor
    Matrix operator +(Matrix &b) {
        Matrix c(this->n, this->m);
        for(int i = 0; i < this->n; ++i) {
            for(int j = 0; j < this->m; ++j) {
                ///std::cout << this->Mat[i][j] << " " << b(i, j) << "\n";
                c.Mat[i][j] = this->Mat[i][j] + b(i, j);
            }
        }
        return c;
    }
    Matrix operator -(Matrix &b) {
        Matrix c(this->n, this->m);
        for(int i = 0; i < this->n; ++i) {
            for(int j = 0; j < this->m; ++j) {
                c.Mat[i][j] = this->Mat[i][j] - b(i, j);
            }
        }
        return c;
    }
    Matrix operator *(Matrix &b) {
        Matrix c(this->n, this->m);
        if(this->n != b.m) {
            return c;
        }
        for(int i = 0; i < this->n; ++i) {
            for(int j = 0; j < this->m; ++j) {
                for(int k = 0; k <  this->n; ++k){
                    c.Mat[i][j] = this->Mat[i][k] * b(k, j);
                }
            }
        }
        std::cout << c;
        return c;
    }
    /**
     3 3
1 0 2 0 3 0
4 0 1 0 1 0
3 0 2 0 1 0**/
    /// Determinant
    Complex det(int N, Matrix mat) {
        Matrix submat(N, N);
        Complex d;
        ///std::cout << 1 << "\n";
        if(N == 1) {
            return mat(0, 0);
        }
        if(N == 2) {
            return (mat(0, 0) * mat(1, 1)) - (mat(1, 0) * mat(0, 1));
        }
        else {
            Complex k(-1, 0, 0, 0);
            for(int c = 0; c < N; ++c) {
                int subi = 0;
                for(int i = 1; i < N; ++i) {
                    int subj = 0;
                    for(int j = 0; j < N; ++j) {
                        if (j == c) {
                            continue;
                        }
                        submat(subi, subj) = mat(i,j);
                        subj++;
                    }
                    subi++;
                }
                k.Re = -k.Re;
                ///std::cout << "\npentru submatricea:\n " << submat;
                ///std::cout << "imi  da det:" << det(N - 1, submat) << " " << mat(0, c) << " " << (mat(0, c) * det(N - 1, submat));
                ///std::cout << "\n";
                d = d + k * (mat(0, c) * det(N - 1, submat));
                ///std::cout << d;
            }
        }
        return d;
    }
    /// Inversa unei matrici
    Matrix Inv(int N, Matrix mat) {
        Matrix submat(N, N), ans(N, N);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                int subi = 0;
                for(int k = 0; k < N; ++k) {
                    if(k == i) {
                        continue;
                    }
                    int subj = 0;
                    for(int l = 0; l < N; ++l) {
                        if(l == j) {
                            continue;
                        }
                        submat(subi, subj) = mat(k, l);
                        ++subj;
                    }
                    ++subi;
                }
                ///std::cout << i << " " << j << "\n" << submat << "\n";
                ans(i, j) = det(N - 1, submat) / det(N, mat);
            }
        }
        return ans;
    }
};

std::ostream& operator<< (std::ostream &out, const Matrix &a) {
    for(int i = 0; i < a.n; ++i) {
        for(int j = 0; j < a.m; ++j) {
            out << a.Mat[i][j];
        }
        out << "\n";
    }
    return out;
}

std::istream& operator>> (std::istream &in, Matrix &a) {
    for(int i = 0; i < a.n; ++i) {
        for(int j = 0; j < a.m; ++j) {
            in >> a.Mat[i][j];
        }
    }
    return in;
}
