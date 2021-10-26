#include <cmath>
#include <iostream>

class Point
{
private:
    int x;
    int y;
    
public:
    Point() : x(0) , y(0) { }
    
    Point(int pos_x,int pos_y) : x(pos_x), y(pos_y) { }
    
    int GetX() { return x; }
    
    int GetY() { return y; }
    
    void print() { std::cout << "[" << x << "," << y << "]"; }
    
    bool operator=(const Point point);
};

bool Point::operator=(const Point point)
{
    this->x = point.x;
    this->y = point.y;
    return true;
}

class Geometry
{
private:
    int number_of_points;
    Point* point_array[128];
    
public:
    Geometry() = default;
    
    Geometry(Point** point_list);
    
    void AddPoint(const Point& point);
    
    void PrintDistance();    
};

Geometry::Geometry(Point** point_list)
{
    int i = 0;
    
    while(i < 128)
    {
        Point* ptr = *(point_list+i);
        if(!ptr)
            break;
        point_array[i] = ptr;
        i++;
    }
    
    number_of_points = i;
}

void Geometry::AddPoint(const Point& point)
{
    for(int i = 0; i < 128; i++)
    {
        if(point_array[i])
            continue;
        *point_array[i] = point;
        break;
    }
}

void Geometry::PrintDistance()
{
    for(int i = 0; i < number_of_points; i++)
    {
        for(int j = 0; j < number_of_points; j++)
        {
            if(!*(point_array+i) || !*(point_array+j))
                continue;
            if(i-j == 0)
                continue;
            
            Point A = *point_array[i];
            Point B = *point_array[j];
            
            int height = std::abs(A.GetY()-B.GetY());
            int width = std::abs(A.GetX()-B.GetX());
            int dist = sqrt(height*height+width*width);
            
            std::cout <<
            "Distance between [" << A.GetX() << "," << A.GetY() << "] and [" << B.GetX() << "," << B.GetY() << "] is " << dist << '\n';
        }
    }
}

int main(void)
{
    Point* plist[128] = {nullptr,};
    
    for(int i = 0; i < 10; i++)
        plist[i] = new Point({i,i});
    
    Geometry geo(plist);
    geo.PrintDistance();
    
    return 0;
}
