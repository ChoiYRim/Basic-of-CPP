#include <iostream>

namespace MyArray
{

class Array;
class Int;

class Array
{
private:
    friend Int;
    
    const int dim; // 배열의 총 차원 수
    int* size; // dim개의 차원의 각 크기를 저장
    
    struct Address
    {
        int level; // 현재 차원 레벨 저장 : dim-1 레벨에선 Int형 데이터를 저장함
        void* next; // 다음 차원의 데이터 리스트의 주소값 저장
    };
    
    Address* top;
        
public:
    class Iterator
    {
    private:
        int* location; // 예를 들어, 현재 iterator가 Array형 배열 arr[1][2][3]을 가리키고 있다면 location은 {1,2,3}을 저장
        Array* arr;
        
        friend Int;
        
    public:
        Iterator(Array* arr,int* loc = NULL) : arr(arr)
        {
            location = new int[arr->dim];
            for(int i = 0; i < arr->dim; i++)
                location[i] = (loc != NULL ? loc[i] : 0);
        }
        Iterator(const Iterator& it) : arr(it.arr)
        {
            location = new int[arr->dim];
            for(int i = 0; i < arr->dim; i++)
                location[i] = it.location[i];
        }
        ~Iterator()
        {
            delete[] location;
        }
        Iterator& operator++()
        {
            if(location[0] >= arr->size[0])
                return (*this);
            
            bool carry = false;
            int i = arr->dim-1;
            
            // 크기가 [1][2][3]인 배열에서 [0][0][2]를 가리키고 있는데 ++를 하면 [0][0][3]이 아니라 [0][1][0]을 가야함
            while(carry && i >= 0)
            {
                location[i]++;
                
                if(location[i] >= arr->size[i] && i >= 1)
                {
                    carry = true;
                    location[i] -= arr->size[i];
                    i--;
                }
                else
                    carry = false;
            }
            
            return (*this);
        }
        Iterator& operator=(const Iterator& it)
        {
            arr = it.arr;
            location = new int[it.arr->dim];
            for(int i = 0; i < arr->dim; i++)
                location[i] = it.location[i];
            
            return (*this);
        }
        Iterator operator++(int)
        {
            Iterator it(*this);
            ++(*this);
            return it;
        }
        bool operator!=(const Iterator& it)
        {
            if(it.arr->dim != arr->dim)
                return true;
            
            for(int i = 0; i < arr->dim; i++)
                if(it.location[i] != location[i])
                    return true;
            
            return false;
        }
        Int operator*();
    };
    
    friend Iterator;
    
    Array(int dim,int* array_size) : dim(dim)
    {
        size = new int[dim];
        for(int i = 0; i < dim; i++)
            size[i] = array_size[i];
        
        top = new Address;
        top->level = 0;
        
        initialize_address(top);
    }
    
    Array(const Array& arr) : dim(arr.get_dim())
    {
        int* arg_size = arr.get_size();
        
        size = new int[dim];
        for(int i = 0; i < dim && arg_size != NULL; i++)
            size[i] = arg_size[i];
        
        top = new Address;
        top->level = 0;
        
        initialize_address(top);
    }
    
    ~Array()
    {
        delete_address(top);
        delete[] size;
    }
    
    inline int get_dim() const;
    
    inline int* get_size() const;
    
    void initialize_address(Address* current);
    
    void delete_address(Address* current);
    
    Int operator[](const int index);
    
    Iterator begin()
    {
        int* arr = new int[dim];
        for(int i = 0; i < dim; i++)
            arr[i] = 0;
        
        Iterator tmp(this,arr);
        delete[] arr;
        
        return tmp;
    }
    Iterator end()
    {
        int* arr = new int[dim];
        arr[0] = size[0]; // 최고차원의 마지막 인덱스가 size[0]-1이므로 이 값만 고정으로 할당
        
        for(int i = 1; i < dim; i++)
            arr[i] = 0;
        
        Iterator tmp(this,arr); // 마지막 데이터 다음 위치를 가리키도록 초기화
        delete[] arr;
        
        return tmp;
    }
};

class Int
{
private:
    void* data;
    int level;
    Array* array;
    
public:
    Int(int index,int _level = 0,void* _data = NULL,Array* _array = NULL) : level(_level), data(_data), array(_array)
    {
        if(_level < 1 || index >= array->size[_level-1])
        {
            data = NULL;
            return;
        }
        if(level == array->dim) // 마지막 차원 -> 실제 데이터를 저장하는 구간
            data = static_cast<void*>(static_cast<int*>(static_cast<Array::Address*>(data)->next)+index);
        else
            data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next)+index);
    }
    
    Int(const Int& i) : data(i.data), level(i.level), array(i.array) { }
    
    operator int() //
    {
        if(data)
            return *static_cast<int*>(data);
        return 0;
    }
    
    Int operator[](const int index) //
    {
        if(!data)
            return 0;
        return Int(index,level+1,data,array);
    }
};

inline int Array::get_dim() const { return dim; }

inline int* Array::get_size() const { return size; }

void Array::initialize_address(Address *current)
{
    if(!current)
        return;
    if(current->level >= dim-1) // 마지막 직전의 차원에선 실제 데이터를 저장할 배열을 생성
    {
        current->next = new int[size[current->level]];
        return;
    }
    
    // 마지막-1 차원까진 주소값을 가진 배열을 생성하고 초기값을 넣어줌
    current->next = new Address[size[current->level]];
    for(int i = 0; i < size[current->level]; i++)
    {
        (static_cast<Address*>(current->next)+i)->level = current->level+1;
        initialize_address(static_cast<Address*>(current->next)+i);
    }
}

void Array::delete_address(Address *current)
{
    if(!current)
        return;
    for(int i = 0; current->level < dim-1 && i < size[current->level]; i++)
        delete_address(static_cast<Address*>(current->next)+i);
    
    delete[] current->next;
}

Int Array::operator[](const int index) //
{
    return Int(index,1,static_cast<void*>(top),this);
}

Int Array::Iterator::operator*() //
{
    Int start = arr->operator[](location[0]);
    for(int i = 1; i < arr->dim; i++)
        start = start.operator[](location[i]);
    return start;
}

}

int main()
{
    int size[] = {2,3,4};
    MyArray::Array arr(3,size);
    MyArray::Array::Iterator it = arr.begin();
    
    for(int i = 0; it != arr.end(); it++,i++)
        (*it) = i;
    
    for(it = arr.begin(); it != arr.end(); it++)
        std::cout << *it << '\n';
    
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                arr[i][j][k] = (i+1) * (j+1) * (k+1) + arr[i][j][k];
            }
        }
    }
    
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 4; k++)
                std::cout << i << " " << j << " " << k << " " << arr[i][j][k] << '\n';
        }
    }
    return 0;
}
