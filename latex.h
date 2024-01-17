#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <limits>

class Latex{
private:
    std::fstream file;
    std::string file_name;
    int num_lines;

    void make_pdf(){
        const std::string command = std::string("latex ") + file_name;
        system(command.c_str());
    }

    void make_ending(){
        file << "\\end{tikzpicture}" << std::endl;
        file << "\\end{document}" << std::endl;
        // make_pdf();
        file.close();
        const std::string command = std::string("latex2png ") + file_name;
        system(command.c_str());
        // file.open(file_name, std::ios::out | std::ios::in);
    }

    // std::fstream& go_to_line(std::fstream& file){
    //     file.seekp(std::ios::beg);
    //     for(int i = 0; i < num_lines; i++){
    //         file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //     }
    //     return file;
    // }

public:
    Latex(std::string file_name){
        this->file_name = file_name;
        file.open(file_name, std::ios::trunc | std::ios::out | std::ios::in);
        file << "\\documentclass{minimal}" << std::endl;
        file << "\\usepackage{tikz}" << std::endl;
        file << "\\usetikzlibrary {graphs}" << std::endl;
        file << "\\begin{document}" << std::endl;
        file << "\\begin{tikzpicture}[node distance={15mm}, ";
        file << "thick, main/.style = {draw, circle}]" << std::endl;
        num_lines = 5;
        file << "% 20" << std::endl;
        make_ending();
    }

    // void make_node(std::string node_name,
    //               int node_x, int node_y, int node_id){
    //     // std::cout << file_name << std::endl;
    //     file.open(file_name, std::ios::out | std::ios::in);
        
    //     file << "\\node[main] at (" << node_x << ", " << node_y;
    //     file << ") (" << node_id << ") {$" << node_name << "$};" << std::endl;
    //     file << "% 20" << std::endl;
    //     num_lines++;
    //     make_ending();
    // }

    void make_node(std::string node_name,
                  int node_x, int node_y, int node_id){
        system("cp graph.tex buf.tex");
        std::fstream buf;
        std::string str;
        buf.open("buf.tex", std::ios::in | std::ios::out);
        file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
        while (true) {
            std::getline(buf, str);
            if (str == "% 20") {
                file << "\\node[main] at (" << node_x << ", " << node_y;
                file << ") (" << node_id << ") {$" << node_name << "$};" << std::endl;
                file << "% 20" << std::endl;
                std::cout << str << std::endl;
                num_lines++;
                break;
            }
            else {
                file << str << std::endl;
            }
        }
        make_ending();
        buf.close();
        file.close();
    }

    // void make_edge(int start_node, int end_node){
    //     file.open(file_name, std::ios::out | std::ios::in);
    //     go_to_line(file);
    //     file << "\\draw[->] (" << start_node << ") -- (";
    //     file << end_node << ");" << std::endl;
    //     file << "% 20" << std::endl;
    //     num_lines++;
    //     make_ending();
    // }

    void make_edge(int start_node, int end_node){
        system("cp graph.tex buf.tex");
        std::fstream buf;
        std::string str;
        buf.open("buf.tex", std::ios::in | std::ios::out);
        file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
        while (true) {
            std::getline(buf, str);
            if (str == "% 20") {
                file << "\\draw[->] (" << start_node << ") -- (";
                file << end_node << ");" << std::endl;
                file << "% 20" << std::endl;
                std::cout << str << std::endl;
                num_lines++;
                break;
            }
            else {
                file << str << std::endl;
            }
        }
        make_ending();
        buf.close();
        file.close();
    }

//     void make_marked_edge(int start_node, int end_node){
//         file.open(file_name, std::ios::out | std::ios::in);
//         go_to_line(file);
//         file << "\\draw[->, red] (" << start_node << ") -- (";
//         file << end_node << ");" << std::endl;
//         file << "% 20" << std::endl;
//         num_lines++;
//         make_ending();
//         file.close();
//     }

//     void remove_edge(int start_node, int end_node){
//         system("cp graph.tex buf.tex");
//         std::fstream buf;
//         std::string str;
//         buf.open("buf.tex", std::ios::in | std::ios::out);
//         file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
//         for (int i = 0; i < num_lines; i++) {
//             std::getline(buf, str);
//             if (str != "\\draw[->] (" + std::to_string(start_node) + ") -- (" + std::to_string(end_node) + ");") {
//                 file << str << std::endl;
//             }
//         }
//         num_lines--;
//         make_ending();
//         buf.close();
//         file.close();
//         // system("rm buf.tex");
//     }

//     void remove_node(int node_id){
//         system("cp graph.tex buf.tex");
//         std::fstream buf;
//         std::string str;
//         buf.open("buf.tex", std::ios::in | std::ios::out);
//         file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
//         for (int i = 0; i < num_lines; i++) {
//             std::getline(buf, str);
//             if (str.find("("+std::to_string(node_id)+")") == std::string::npos) {
//                 file << str << std::endl;
//                 std::cout << str << std::endl;
//             }
//             else {
//                 num_lines--;
//             }
//         }
//         file << "% 20" << std::endl;
//         make_ending();
//         buf.close();
//         file.close();
//         // system("rm buf.tex");
//     }
// };

void make_marked_edge(int start_node, int end_node){
        system("cp graph.tex buf.tex");
        std::fstream buf;
        std::string str;
        buf.open("buf.tex", std::ios::in | std::ios::out);
        file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
        while (true) {
            std::getline(buf, str);
            if (str == "% 20") {
                file << "\\draw[->, red] (" << start_node << ") -- (";
                file << end_node << ");" << std::endl;
                file << "% 20" << std::endl;
                std::cout << str << std::endl;
                num_lines++;
                break;
            }
            else {
                file << str << std::endl;
            }
        }
        make_ending();
        buf.close();
        file.close();
    }

    void remove_edge(int start_node, int end_node){
        system("cp graph.tex buf.tex");
        std::fstream buf;
        std::string str;
        buf.open("buf.tex", std::ios::in | std::ios::out);
        file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
        int limit = num_lines;
        for (int i = 0; i < limit; i++) {
            std::getline(buf, str);
            if (str != "\\draw[->] (" + std::to_string(start_node) + ") -- (" + std::to_string(end_node) + ");") {
                file << str << std::endl;
            }
            else {
                num_lines--;
            }
        }
        file << "% 20" << std::endl;
        make_ending();
        buf.close();
        file.close();
        // system("rm buf.tex");
    }

    void hide_path(){
        system("cp graph.tex buf.tex");
        std::fstream buf;
        std::string str;
        buf.open("buf.tex", std::ios::in | std::ios::out);
        file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
        int limit = num_lines;
        for (int i = 0; i < limit; i++) {
            std::getline(buf, str);
            if (str.find("red")==std::string::npos) {
                file << str << std::endl;
            }
            else {
                num_lines--;
            }
        }
        file << "% 20" << std::endl;
        make_ending();
        buf.close();
        file.close();
        // system("rm buf.tex");
    }

    void remove_node(int node_id){
        system("cp graph.tex buf.tex");
        std::fstream buf;
        std::string str;
        buf.open("buf.tex", std::ios::in | std::ios::out);
        file.open(file_name, std::ios::out | std::ios::in | std::ios_base::trunc);
        int limit = num_lines;
        for (int i = 0; i < limit; i++) {
            std::getline(buf, str);
            if (str.find("("+std::to_string(node_id)+")") == std::string::npos) {
                file << str << std::endl;
                std::cout << str << std::endl;
            }
            else {
                num_lines--;
            }
        }
        file << "% 20" << std::endl;
        make_ending();
        buf.close();
        file.close();
        // system("rm buf.tex");
    }
};