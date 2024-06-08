#include <iostream>
#include <fstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/property_map.hpp>

#define _SCL_SECURE_NO_WARNINGS

using namespace std;

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

int main() {
    // Тип данных для графа
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::property<boost::vertex_color_t, boost::default_color_type>> MyGraph;

    // Создание графа с 3 вершинами
    MyGraph g;
    auto v1 = boost::add_vertex(g);
    auto v2 = boost::add_vertex(g);
    auto v3 = boost::add_vertex(g);

    // Добавление ребер
    boost::add_edge(v1, v2, g);
    boost::add_edge(v2, v3, g);
    boost::add_edge(v3, v1, g);

    // Сохранение графа в формате DOT
    ofstream f("graph.dot");
    boost::write_graphviz(f, g);
    f.close();

    // Обработка графа с помощью Graphviz
    system("\"C:/Program Files/Graphviz/bin/dot.exe\" graph.dot -Kcirco -Tsvg -o graph.svg");
    system("start graph.svg");

    // Удаление ребер
    boost::remove_edge(v1, v2, g);
    boost::remove_edge(v2, v3, g);

    // Добавление новых вершин и ребер
    auto v4 = boost::add_vertex(g);
    auto v5 = boost::add_vertex(g);
    boost::add_edge(v1, v4, g);
    boost::add_edge(v2, v5, g);
    boost::add_edge(v4, v5, g);

    // Раскраска вершин
    boost::property_map<MyGraph, boost::vertex_color_t>::type colorMap = get(boost::vertex_color, g);
    auto vi = vertices(g);
    for (auto it = vi.first; it != vi.second; ++it) {
        colorMap[*it] = (it - vi.first) % 2 == 0 ? boost::red_color : boost::green_color;
    }

    // Сохранение изменённого графа в формате DOT с указанием цветов вершин
    f.open("graph.dot");
    boost::write_graphviz(f, g, ColorWriter<boost::property_map<MyGraph, boost::vertex_color_t>::type>(colorMap));
    f.close();

    // Обработка графа с помощью Graphviz
    system("\"C:/Program Files/Graphviz/bin/dot.exe\" graph.dot -Kcirco -Tsvg -o graph_updated.svg");
    system("start graph_updated.svg");

    return 0;
}