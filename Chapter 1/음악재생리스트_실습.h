#pragma once

#include <iostream>
#include <initializer_list>

template<typename T>
struct cir_list_node
{
    T* data;
    cir_list_node* next;
    cir_list_node* prev;
    
    ~cir_list_node()
    {
        delete data;
    }
};

template<typename T>
struct cir_list
{
public:
    using node = cir_list_node<T>;
    using node_ptr = node*;
    
private:
    node_ptr head;
    size_t n;
    
public:
    cir_list() : n(0)
    {
        head = new node{NULL,NULL,NULL};
        head->next = head;
        head->prev = head;
    }
    
    size_t size() const
    {
        return n;
    }
    
    void insert(const T& value)
    {
        node_ptr newNode = new node{new T(value),NULL,NULL};
        n++;
        
        auto dummy = head->prev; // dummy : [last node]
        dummy->next = newNode; // [last node] -> newNode
        newNode->prev = dummy; // [last node] <-> newNode
        
        if(head != dummy)
        {
            newNode->next = head; // [last node] <-> newNode -> head
            head->prev = newNode; // [last node] <-> newNode <-> head
            head = newNode; // [last node] <-> head <-> [previous head]
            return;
        }
        
        dummy->prev = newNode;
        newNode->next = dummy;
        head = newNode;
    }
    
    void erase(const T& value)
    {
        auto cur = head,dummy = head->prev; // dummy : [last node]
        while(cur != dummy)
        {
            if(*(cur->data) == value) // hit
            {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                if(cur == head)
                    head = head->next;
                delete cur;
                n--;
                break;
            }
            cur = cur->next;
        }
    }
    
    
    struct cir_list_it
    {
    public:
        cir_list_it(node_ptr p) : ptr(p) { }
        
        T& operator*()
        {
            return *(ptr->data);
        }
        
        node_ptr get()
        {
            return ptr;
        }
        
        cir_list_it& operator++() // ?????? ???????????? ??????????????? ??????
        {
            ptr = ptr->next;
            return *this;
        }
        
        cir_list_it operator++(int) // int??? ????????? ??????-?????? ???????????? ???????????? ????????? ??????
        {
            cir_list_it it = *this; // ?????? ???????????? ?????? ????????? ????????????
            ++(*this);
            return it; // ?????? ????????? ?????? -> ????????? ?????? ???????????? ???????????? ??? ?????? ??????????????? ?????????????????? ?????????
        }
        
        cir_list_it& operator--()
        {
            ptr = ptr->prev;
            return *this;
        }
        
        cir_list_it operator--(int)
        {
            cir_list_it it = *this;
            --(*this);
            return it;
        }
        
        friend bool operator==(const cir_list_it& it1,const cir_list_it& it2)
        {
            return it1.ptr == it2.ptr;
        }
        
        friend bool operator!=(const cir_list_it& it1,const cir_list_it& it2)
        {
            return it1.ptr != it2.ptr;
        }
        
    private:
        node_ptr ptr;
    };
    
    cir_list_it begin()
    {
        return cir_list_it{head};
    }
    
    cir_list_it begin() const
    {
        return cir_list_it{head};
    }
    
    cir_list_it end()
    {
        return cir_list_it{head->prev};
    }
    
    cir_list_it end() const
    {
        return cir_list_it{head->prev};
    }
    
    cir_list(const cir_list<T>& other) : cir_list()
    {
        for(const auto& i : other)
            insert(i);
    }
    
    cir_list(const std::initializer_list<T>& il) : head(NULL), n(0)
    {
        for(const auto& i : il)
            insert(i);
    }
    
    ~cir_list()
    {
        while(size())
            erase(*(head->data));
        
        delete head;
    }
    
    typedef cir_list_it iterator;
};

struct playlist
{
    cir_list<int> list;
    
    void insert(int song)
    {
        list.insert(song);
    }
    void erase(int song)
    {
        list.erase(song);
    }
    void print_list()
    {
        for(auto& song : list)
        {
            std::cout << song << " ";
        }
        std::cout << std::endl;
    }
};
