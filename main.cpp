#include <iostream>
#include <fstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/property_map.hpp>

#define _SCL_SECURE_NO_WARNINGS

using namespace std;

// Тип данных для графа
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
    boost::property<boost::vertex_color_t, boost::default_color_type>> MyGraph;

// Функция-writer для добавления цветов вершин в файл .dot
template <typename VertexColorMap>
class ColorWriter {
public:
    ColorWriter(VertexColorMap colorMap) : colorMap(colorMap) {}

    template <typename Vertex>
    void operator()(ostream& out, const Vertex& v) const {
        out << "[color=" << (get(colorMap, v) == boost::red_color ? "red" : "green") << "]";
    }

private:
    VertexColorMap colorMap;
};

// Функции для работы с графом
void addVertex(MyGraph& g) {
    auto v = boost::add_vertex(g);
    cout << "Добавлена вершина " << v << endl;
}

void removeVertex(MyGraph& g) {
    auto vi = vertices(g);
    if (vi.first == vi.second) {
        cout << "Граф пуст, нечего удалять." << endl;
        return;
    }

    auto v = *(vi.first);
    boost::remove_vertex(v, g);
    cout << "Удалена вершина " << v << endl;
}

void addEdge(MyGraph& g) {
    auto vi = vertices(g);
    if (vi.first == vi.second) {
        cout << "Граф пуст, нечего добавлять." << endl;
        return;
    }

    int v1, v2;
    cout << "Введите номера вершин для добавления ребра: ";
    cin >> v1 >> v2;
    if (v1 >= 0 && v1 < num_vertices(g) && v2 >= 0 && v2 < num_vertices(g)) {
        boost::add_edge(v1, v2, g);
        cout << "Добавлено ребро между вершинами " << v1 << " и " << v2 << endl;
    }
    else {
        cout << "Неверные номера вершин." << endl;
    }
}

void removeEdge(MyGraph& g) {
    auto vi = vertices(g);
    if (vi.first == vi.second) {
        cout << "Граф пуст, нечего удалять." << endl;
        return;
    }

    int v1, v2;
    cout << "Введите номера вершин для удаления ребра: ";
    cin >> v1 >> v2;
    if (v1 >= 0 && v1 < num_vertices(g) && v2 >= 0 && v2 < num_vertices(g)) {
        auto edge_exists = boost::edge(v1, v2, g).second;
        if (edge_exists) {
            boost::remove_edge(v1, v2, g);
            cout << "Удалено ребро между вершинами " << v1 << " и " << v2 << endl;
        }
        else {
            cout << "Ребро между указанными вершинами не существует." << endl;
        }
    }
    else {
        cout << "Неверные номера вершин." << endl;
    }
}

int main() {
    MyGraph g;
    string command;
    setlocale(LC_ALL, "Russian");
    // Создание начального графа
    auto v1 = boost::add_vertex(g);
    auto v2 = boost::add_vertex(g);
    boost::add_edge(v1, v2, g);

    while (true) {
        cout << "Введите команду (add_vertex, remove_vertex, add_edge, remove_edge, draw, exit): ";
        cin >> command;

        if (command == "add_vertex") {
            addVertex(g);
        }
        else if (command == "remove_vertex") {
            removeVertex(g);
        }
        else if (command == "add_edge") {
            addEdge(g);
        }
        else if (command == "remove_edge") {
            removeEdge(g);
        }
        else if (command == "draw") {
            ofstream f("graph.dot");
            boost::write_graphviz(f, g, ColorWriter<boost::property_map<MyGraph, boost::vertex_color_t>::type>(get(boost::vertex_color, g)));
            f.close();

            system("\"C:/Program Files/Graphviz/bin/dot.exe\" graph.dot -Kcirco -Tsvg -o graph.svg");
            system("start graph.svg");
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда" << endl;
        }
    }

    return 0;
}