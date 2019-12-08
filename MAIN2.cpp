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


int FindEdge(int s, int c, const int p, const vector <SEdge> & edges_v) { //вес пути из s и c или 0, если пути нет
    for (int i=0; i<p; i++)
        if (edges_v[i].m_node1==s && edges_v[i].m_node2==c) return edges_v[i].m_weight;
    return 0;
}
//INF
//s==c 0



//num - количсетво узлов в c_way
void step (int s, int f, int num, const int n, const int p, bool & found, 
           vector <int> & min_way, vector <int> & c_way, const vector <SEdge> & edges_v,
           int min_weight, int c_weight) { //рекурсивный поиск шага пути
 int c; //номер вершины, куда делаем шаг
 if (s==f) { //путь найден
  found = true; //поставить флажок "найдено"
  //min_way.clear();
  for (int i=0; i<num; i++) min_way.push_back(c_way[i]); //запомнить сам путь
 }
 else { //выбор очередной точки
  for (c=0; c<n; c++) { //проверяем все вершины
   int w = FindEdge(s,c,p,edges_v); //есть ли путь из s в c, сохраняем вес
   if (w && find(c_way.begin(), c_way.end(), c) == c_way.end() && (min_weight==0 || c_weight+w<min_weight)) { //нужная точка не включена?
    c_way.push_back(c); //включить точку в путь
    //c_way[num]=c; //включить точку в путь
    c_weight += w; //учесть в общем весе пути
    step (c,f,num+1,n,p,found,min_way,c_way,edges_v,min_weight,c_weight); //вызвать себя для поиска следующей точки
   // c_way[num]=0;     //вернуть всё как было
    c_way.erase(c_way.begin()+num-1,c_way.end()-1);
    c_weight -= w; 
   }
  }
 }
}




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
   for (int i=0; i<q; i++) {
       vector <int> c_way; //номера узлов текущего пути
        vector <int> min_way; //искомый самый короткий путь
        bool found=false;       //найден ли путь
        int min_weight=0; //найденный минимальный "вес" маршрута     //не надо делать 
        int c_weight=0; //текущий "вес" маршрута
        int start = pairs_v[i].m_node1; //узел-начало
        int finish = pairs_v[i].m_node2; //узел-конец
        c_way.push_back(start); //первую точку внесли в маршрут

        //unsigned int start_time = clock();   //начальное время

        step (start,finish,1,n,p,found,min_way,c_way,edges_v,min_weight,c_weight); //ищем вторую точку

       // unsigned int end_time = clock();   //конечное время
        //unsigned int search_time = end_time - start_time;   //искомое время
        //cout << "Search_time: " << search_time << endl;

        if (found) {
            out_file << min_way.size()<< endl;
            for (int i=0; i<min_way.size(); i++) 
                out_file << min_way[i] +1<< " ";        //+1 чтобы номера узлов были с нуля
            out_file << endl;
        }
        else out_file << "No way" << endl<<endl;
        //cout<< min_weight;
   }
    // cout << "Run_time: " << clock() << endl;
     
     return 0;
}