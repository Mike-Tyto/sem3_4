#include "latex.h"
#include "graph.h"
#include <sstream>

int main(){
    auto type = Graph<int, int, int>::Type::Directed;
    auto graph = Graph<int, int, int>();
    std::string file_name = "graph.tex";
    auto file = Latex(file_name);
    int choice;
    std::string node_name;
    int x;
    int y;
    int start_node;
    int end_node;
    int count_nodes = 0;
    std::string go_file = "go/test.txt";
    std::fstream go;
    std::string str = "@end";
    std::string word;

    while (true) {
        if (str=="" || str=="\n") {
            go.open(go_file);
            std::getline(go, str);
            go.close();
        }
        else if (str.substr(0, 4)=="@end") {
            go.open(go_file);
            std::getline(go, str);
            go.close();
            continue;
        }
        else {
            choice = std::stoi(str.substr(0, str.find(' ')));
            str = str.substr(str.find(' ')+1);
            if (choice==1) {
                node_name = str.substr(0, str.find(' '));
                str = str.substr(str.find(' ')+1);
                x = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                y = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                count_nodes++;
                file.make_node(node_name, x, y, count_nodes);
                graph.AddNodes({Pair<int, int> {count_nodes, int()}});
            }
            else if (choice==2) {
                start_node = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                end_node = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                file.make_edge(start_node, end_node);
                graph.AddEdges({Graph<int, int, int>::Edge {graph.GetNode(start_node), graph.GetNode(end_node), 1}});
            }
            else if (choice==3) {
                start_node = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                end_node = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                Graph<int, int, int>::Path path = graph.Dijkstra(start_node, end_node);
                std::cout << start_node << " " << end_node << " " << path << '\n';
                for (Graph<int, int, int>::Edge e : path.path) {
                    file.make_marked_edge(e.start->id, e.end->id);
                }
            }
            else if (choice==4) {
                // Graph<int, int, int>::Path path = graph.Dijkstra(start_node, end_node);
                // for (Graph<int, int, int>::Edge e : path.path) {
                //     file.make_edge(e.start->id, e.end->id);
                // }
                file.hide_path();
            }
            else if (choice==5) {
                start_node = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                end_node = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                file.remove_edge(start_node, end_node);
            }
            else if (choice==6) {
                start_node = std::stoi(str.substr(0, str.find(' ')));
                str = str.substr(str.find(' ')+1);
                file.remove_node(start_node);
            }
            go.open(go_file, std::ios_base::in|std::ios_base::out|std::ios_base::trunc);
            go << str << std::endl;
            go.close();
        }
    }
    return 0;
}