#ifndef STRUCT_H
#define STRUCT_H
struct AirPort
{
    char code[5];
    char name[50];
    char phone[12];
    char addr[100];
};

struct AirPortList
{
    AirPort ds[20];
    int n=0;
};

//Ma trận kề của đồ thị (Adjacency-matrix)
struct AdjacencyMatrix
{
    int mt[20][20];
    int n=0;
};
#endif // STRUCT_H
