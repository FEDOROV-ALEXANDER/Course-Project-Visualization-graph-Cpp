# Readme.md для Репозитория Программы

## Оглавление
1. [Обзор](#обзор)
2. [Использованные Средства](#использованные-средства)
   - [Boost](#boost)
   - [GraphViz](#graphviz)
3. [Детали Использования Boost](#детали-использования-boost)
4. [Функции и Классы Программы](#функции-и-классы-программы)
5. [Установка и Использование](#установка-и-использование)
6. [Лицензия](#лицензия)

## Обзор
Данный репозиторий содержит программу, которая позволяет добавлять и удалять вершины и ребра, а также визуализировать граф с помощью GraphViz. Программа использует библиотеку Boost для работы с графами и GraphViz для визуализации.

## Использованные Средства

### Boost
Boost — это набор библиотек C++, которые расширяют стандартную библиотеку и предоставляют широкий спектр функциональности, включая работу с графами, многопоточность, итераторы и обработку исключений. В данной программе используются следующие компоненты Boost:
- `boost::adjacency_list`: Представляет граф в виде списка смежности.
- `boost::vecS`: Используется для хранения вершин в векторе.
- `boost::undirectedS`: Обозначает, что граф неориентированный.
- `boost::vertex_color_t`: Используется для хранения цветов вершин.

### GraphViz
GraphViz — это набор программ для визуализации графов. В данной программе используется для создания графического представления графа в формате SVG.

## Детали Использования Boost
В программе используется `boost::adjacency_list` для представления графа. Тип графа определяется как неориентированный с использованием `boost::undirectedS` и вершины хранятся в векторе с использованием `boost::vecS`. Каждая вершина может иметь цвет, который хранится в `boost::vertex_color_t`.

## Функции и Классы Программы
- `addVertex(MyGraph& g)`: Добавляет новую вершину в граф.
- `removeVertex(MyGraph& g)`: Удаляет вершину из графа.
- `addEdge(MyGraph& g)`: Добавляет ребро между двумя вершинами.
- `removeEdge(MyGraph& g)`: Удаляет ребро между двумя вершинами.
- `ColorWriter`: Шаблонный класс, используемый для добавления атрибутов цвета вершин в файл .dot для GraphViz.

## Установка и Использование
1. Клонируйте репозиторий на свой компьютер.
2. Установите библиотеку Boost и GraphViz.
3. Скомпилируйте программу с помощью компилятора C++, поддерживающего стандарт C++11 или выше.
4. Запустите программу и используйте команды для управления графом.

## Лицензия
Программа распространяется свободно, мне не жалко.
