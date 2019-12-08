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

//ifstream cin("input.txt");
//ofstream cout("output.txt");

int n;   //n- количество узлов
vector<int> a;
vector <bool> used;
vector <vector<int>> all_ways;
vector <vector<int>> all_way;


void rec(int idx)
{
    if (idx == n)
    {
        all_ways.push_back(a);
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (used[i])
            continue;
        a[idx] = i;
        used[i]=true;
        rec(idx + 1);
        used[i]=false;
    } 
}

int main()
{
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
        edges_v.push_back(edge);
    }
    in_file >> q;
    for (int i=0; i<q; i++) {
        SPair pair;
        in_file>>pair.m_node1>>pair.m_node2;
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
    a = vector<int>(n);
    used=vector<bool>(n+1,false);
    rec(0);
    for (int i=0; i<all_ways.size(); i++) {
        for (int j=0; j<n; j++)
            cout<<all_ways[i][j]<<" ";
        cout << endl;
    } 
    cout<<endl<<endl;
    /*for (int m=0; m<q; m++) {
        int start=pairs_v[m].m_node1;
        int finish=pairs_v[m].m_node2;
        int min_weight=INF;
        vector<int> min_way;
        //temporary
        for (int i=0; i<all_ways.size(); i++) {
            if (all_ways[i][0]==start)
                    all_way.push_back(all_ways[i]);
        }
       
       for (int i=0; i<all_way.size(); i++) {
        for (int j=0; j<n; j++)
            cout<<all_way[i][j]<<" ";
        cout << endl;
      }
        //по строкам way
        for (int i=0; i<all_way.size();i++) {
            vector <int> str = all_way[i];

            int s=0; //временный старт
            int f=1; //временный финиш
            int weight=0;
            vector<int> way;
            way.push_back(start);


            bool str_pass=true;
            //по элементам строки
            for (int j=0; j<str.size(); j++) {
                //по всем ребрам в поисках пути
                bool way_exist=false;
                int edges_weight=INF;   //самый маленький вес из одинаковых ребер
                for (int k=0; k<p; k++)
                    if (edges_v[k].m_node1==str[s] && edges_v[k].m_node2==str[f]) {
                        if(edges_weight>edges_v[k].m_weight)
                            edges_weight=edges_v[k].m_weight;
                        way_exist=true;
                    }
                weight+=edges_weight;
                way.push_back(str[f]);
                if (way_exist==false) {
                    str_pass=false;
                    break;
                }
                if (str[f]==finish)
                    break;
                s++; f++;

            }
            if (str_pass)
                if (min_weight>weight) {
                    min_weight=weight;
                    min_way.clear();
                    min_way=way;
                }

        }
        if (min_weight==INF) 
            out_file<<"No way"<<endl<<endl;
        else {
            out_file<<min_way.size()<<endl;
            for (int i=0; i<min_way.size(); i++) {
                out_file<<min_way[i]<<" ";
            }
            out_file<<endl;
        }
    } */
    return 0;
}