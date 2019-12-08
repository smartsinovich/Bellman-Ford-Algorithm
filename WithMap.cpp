#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // для использования exit()
#include <vector>
#include <map>
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

void rec(int s, const int finish, vector<int> vec, vector<vector<int>> & pos_ways,
         map<int,vector<int>> & map_ways) 
{
    for(int j=0; j<map_ways[s].size();j++) {
                if (find(vec.begin(), vec.end(), map_ways[s][j]) == vec.end())     //если в векторе еще нет такого узла
                    vec.push_back( map_ways[s][j]);
                else continue;
                if (vec[vec.size()-1]!=finish) {
                    s = map_ways[s][j];
                    rec(s,finish, vec, pos_ways,map_ways);

                }
                else  pos_ways.push_back(vec);
                vec.pop_back();
                s = vec[vec.size()-1];
            }
        
}

//ifstream cin("input.txt");
//ofstream cout("output.txt");

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
    int n=0; //количество узлов
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
    int start = pairs_v[0].m_node1; //узел-начало
    int finish = pairs_v[0].m_node2; //узел-конец
    /*for (int i=0; i<edges_v.size(); i++) {

        cout<<edges_v[i].m_node1<<" "<<edges_v[i].m_node2<<" "<<edges_v[i].m_weight;
        cout << endl;
    } 
    cout<<endl;*/

    //проверка на одинаковые ребра
    vector <int> to_erase;
    for (int i=0; i<p-1; i++) {
        for (int j=i+1; j<p; j++) {
            if (edges_v[i].m_node1==edges_v[j].m_node1 && edges_v[i].m_node2==edges_v[j].m_node2) {
                if (edges_v[i].m_weight<edges_v[j].m_weight)
                    to_erase.push_back(j);
                else to_erase.push_back(i);
            }
        }
    }
    for (int i=0; i<to_erase.size();i++) 
        edges_v.erase(edges_v.begin() + to_erase[i]);

    //создали словарь: узел1 -> узел2, узел2, ..., узел2
    map <int, vector<int>> map_ways;
    for (int i=0; i<p; i++) {
        map_ways[edges_v[i].m_node1].push_back(edges_v[i].m_node2);
    }

    std::map<int, vector<int>>::iterator it;
    for (it=map_ways.begin(); it!=map_ways.end(); it++) {
        cout << it->first << "   ";
        for (int i=0; i<it->second.size(); i++)
            cout<<it->second[i]<<" ";
        cout << endl;
    }
    cout<<endl;

    vector<vector<int>> pos_ways;
    int s = start;
    vector <int> vec;
    vec.push_back(s);
    rec(s, finish, vec, pos_ways, map_ways);


    /*for (int i=0; i<map_ways[s].size();i++) {
        vec.push_back( map_ways[s][i]);
        if (vec[vec.size()-1]!=finish) { 
            s = map_ways[s][i];

            for(int j=0; j<map_ways[s].size();j++) {
                vec.push_back( map_ways[s][j]);
                if (vec[vec.size()-1]!=finish) {
                    s = map_ways[s][j];

                    for(int k=0; k<map_ways[s].size();k++) {
                        vec.push_back( map_ways[s][k]);
                        pos_ways.push_back(vec);      //создаем строку
                        vec.pop_back();
                    }

                }
                else  pos_ways.push_back(vec);
                vec.pop_back();
                s = vec[vec.size()-1];
            }
        }
        else pos_ways.push_back(vec);
        vec.pop_back();
        s = vec[vec.size()-1];
    }*/


    for (int i=0; i<pos_ways.size(); i++) {
        for (int j=0; j<pos_ways[i].size(); j++)
            cout<<pos_ways[i][j]<<" ";
        cout << endl;
    } 



    return 0;
}