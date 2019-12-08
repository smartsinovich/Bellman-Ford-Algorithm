#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // для использования exit()
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

const int INF = 1e9;
struct SPoint
{
    double m_x;
    double m_y;
};

struct SEdge
{ 
    int m_node1;
    int m_node2;
    int m_weight;
};

struct SPair
{
    int m_node1;
    int m_node2;
};

int main(){
    string file_name = "";
    cin >> file_name;
    file_name +=".txt";
	ifstream in_file(file_name);
	// Если мы не можем открыть файл для чтения его содержимого
	if (!in_file)
	{
		cerr << "Uh oh, Input.txt could not be opened for reading!" << endl;
		exit(1);
	}
//ВХОДНЫЕ ДАННЫЕ
    int n=0; //количество узлов сети
    int p=0; //количество ребер сети
    int q=0; //количество пар точек

    vector <SPoint> coord_v; //вектор координат длины n
    vector <SEdge> edges_v; //вектор ребер длины p
    vector <SPair> pairs_v; //вектор пар точек длины q

    in_file >> n;
    for (int i=0; i<n; i++) {
        SPoint point;
        in_file>>point.m_x>>point.m_y;
        coord_v.push_back(point);
    }
    in_file >> p;
    for (int i=0; i<p; i++) {
        SEdge edge;
        in_file>>edge.m_node1>>edge.m_node2>>edge.m_weight;
        edge.m_node1 --;  edge.m_node2 --;       //чтобы номера узлов были с нуля
        edges_v.push_back(edge);
    }
    in_file >> q;
    for (int i=0; i<q; i++) {
        SPair pair;
        in_file>>pair.m_node1>>pair.m_node2;
        pair.m_node1 --;  pair.m_node2 --;       //чтобы номера узлов были с нуля
        pairs_v.push_back(pair);
    }

//НАЧАЛО ВЫВОДА В ФАЙЛ
	ofstream out_file("Output.txt");
 
	// Если мы не можем открыть этот файл для записи данных в него
	if (!out_file)
	{
		// То выводим сообщение об ошибке и выполняем exit()
		cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
		exit(1);
	}
 
	// Записываем в файл первую строку - количество пар
    out_file << q << endl;

//ОСНОВНОЕ
    unsigned int start_time = clock();   //начальное время
    for (int i=0; i<q; i++) {
        int start = pairs_v[i].m_node1; //узел-начало
        int finish = pairs_v[i].m_node2; //узел-конец
        if (start>n-1 || finish>n-1) {
            out_file << "No way" << endl;
            continue;
        }
        vector<int> d(n, INF); //расстояния до каждого узла из узла-начала
        d[start] = 0;
        vector<int> prev(n, -1); //хранит предков для каждого узла
        int x;      //для поиска цикла отрицательного веса
        for (int k=0; k<n; k++) {
        //for (;;) {    
            bool any = false;  //выполнилась ли хотя бы одна релаксация?
            x = -1;        //для поиска цикла отрицательного веса
            for (int j=0; j<p; ++j) {
                if (d[edges_v[j].m_node1] < INF)
                    if (d[edges_v[j].m_node2] > d[edges_v[j].m_node1] + edges_v[j].m_weight) {
                        d[edges_v[j].m_node2] = d[edges_v[j].m_node1] + edges_v[j].m_weight;
                        prev[edges_v[j].m_node2] = edges_v[j].m_node1;
                        x = edges_v[j].m_node2;      //для поиска цикла отрицательного веса
                        any = true;
                    }
            }
            if (!any)  break;
        }
        unsigned int end_time = clock();   //конечное время
        unsigned int search_time = end_time - start_time;   //искомое время
        cout << "Search_time: " << search_time << endl;

        if (d[finish] == INF)  {  //если путь не найден
            out_file << "No way" << endl << endl;
        }
        else if (x != -1) {      //если есть цикл отрицательного веса
            int y = x;
            for (int i=0; i<n; ++i) {
                y = prev[y];
                }
            vector<int> path;
            for (int cur=y; ; cur=prev[cur]) {
                path.push_back (cur);
                if (cur == y && path.size() > 1)  break;
                }
            reverse (path.begin(), path.end());
            out_file << "Negative cycle: ";
            for (size_t i=0; i<path.size(); ++i) {
                out_file << path[i]+1 << ' ';          //+1 чтобы номера узлов были с нуля
                }
        }
        else {                //все хорошо
            vector<int> path; //хранит путь от start до finish
            for (int cur=finish; cur!=-1; cur=prev[cur])
                path.push_back (cur);
            reverse (path.begin(), path.end());
    
            out_file << path.size() << endl;
            for (size_t j=0; j<path.size(); ++j)
                out_file << path[j]+1 << ' ';         //+1 чтобы номера узлов были с нуля
            out_file << endl;
        } 
    } 
     cout << "Run_time: " << clock() << endl;
     cout<<"1";
     return 0;
}