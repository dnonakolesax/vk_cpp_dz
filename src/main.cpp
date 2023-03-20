#include <string.h>
#include <iostream>
#include <fstream>
#include "IMDbParser.hpp"
#include "utils.hpp"
#include <clocale>

int main (int argc, char* argv[]) {
    std::setlocale(LC_ALL, ".UTF-8");
    std::string crewPath, basicsPath, namesPath, akasPath, director;
    if (argc<10) {
        std::cerr << "Usage: ./dz1 <director name> --<file name>-path <path to file>." << std::endl;
        std::cerr << "Files required: name.basics.tsv, title.akas.tsv, title.basics.tsv, title.crew.tsv" << std::endl;
        return -1;
    }
    director = std::string(argv[1]);
    for (size_t i = 2; i<argc; i+=2) {
        std::string arg(argv[i]);
        if (arg == "--name-basics-path")
            namesPath = std::string(argv[i+1]); else
        if (arg == "--title-akas-path")
            akasPath = std::string(argv[i+1]); else
        if (arg == "--title-basics-path")
            basicsPath = std::string(argv[i+1]); else
        if (arg == "--title-crew-path")
            crewPath = std::string(argv[i+1]);
    }
    std::fstream nameBasics (namesPath);
    if (!nameBasics) {
        std::cerr << "Failed to open names.basics.tsv" << std::endl;
        return -1;
    } 
    std::fstream titleAkas(akasPath);
    if (!titleAkas) {
        std::cerr << "Failed to open title.akas.tsv" << std::endl;
        return -1;
    } 
    std::fstream titleBasics(basicsPath);
    if (!titleBasics) {
        std::cerr << "Failed to open title.basics.tsv" << std::endl;
        return -1;
    } 
    std::fstream titleCrew(crewPath);
    if (!titleCrew) {
        std::cerr << "Failed to open title.crew.tsv" << std::endl;
        return -1;
    }
    std::string nconst = getNconstByName(nameBasics, director);
    if (nconst.empty()) {
        std::cerr << "No such director! " << director << std::endl;
        return (-1);
    }
    nameBasics.close();
    std::vector<std::string> directorFilms = getDirectorFilms(titleCrew, nconst);
    if (directorFilms.empty()) {
        std::cerr << "This director has no titles!" << std::endl;
        return (-1);
    }
    titleCrew.close();
    std::vector<Movie> notAdultMovies = getNotAdultMovies(titleBasics, directorFilms);
    if (notAdultMovies.empty()) {
        std::cerr << "This director has no not-adult movies!" << std::endl;
        return (-1);
    }
    titleBasics.close();
    std::vector<Movie> russianMovies = getRussianMoviesNames(titleAkas, notAdultMovies); //не делаем проверку на empty, так как гарантированно вернутся хотя бы оригинальные названия фильмов
    titleAkas.close();
    for (int i = 0; i < russianMovies.size(); i++) {
        std::cout << russianMovies[i].originName << std::endl;
    }
    return 0;
}
