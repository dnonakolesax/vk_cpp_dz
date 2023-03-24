#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <clocale>

#include "IMDbParser.hpp"
#include "utils.hpp"


#define TAKAS_COLUMNS_AMNT 8
#define NBASICS_COLUMNS_AMNT 6
#define TBASICS_COLUMNS_AMNT 9
#define TCREW_COLUMNS_AMNT 3


std::map<std::string, std::string> processArgs (int argc, char* argv[]) {
    std::map<std::string, std::string> progArgs;

    if (argc<10) { //имя программы + 4 ключа + 4 файла + имя режиссёра
        std::cerr << "Usage: ./dz1 <director name> --<file name>-path <path to file>." << std::endl;
        std::cerr << "Files required: name.basics.tsv, title.akas.tsv, title.basics.tsv, title.crew.tsv" << std::endl;
        throw std::invalid_argument ("Not enough programm args!");
    }

    progArgs["director"] = std::string(argv[1]);
    
    for (size_t i = 2; i<argc; i+=2) {
        std::string arg(argv[i]);
        if (arg == "--name-basics-path")
            progArgs["namesPath"] = std::string(argv[i+1]); else
        if (arg == "--title-akas-path")
            progArgs["akasPath"] = std::string(argv[i+1]); else
        if (arg == "--title-basics-path")
            progArgs["basicsPath"] = std::string(argv[i+1]); else
        if (arg == "--title-crew-path")
            progArgs["crewPath"] = std::string(argv[i+1]);
    }
    
    if (progArgs.size()!=5) { //4 требуемых файла + имя режиссёра
        std::cerr << "Usage: ./dz1 <director name> --<file name>-path <path to file>." << std::endl;
        std::cerr << "Files required: name.basics.tsv, title.akas.tsv, title.basics.tsv, title.crew.tsv" << std::endl;
        throw std::invalid_argument ("Some of required files are missing!");
    }
    
    return progArgs;
}


bool checkFiles (std::map<std::string, std::string> progArgs) {
    std::string inputString;

    std::fstream nameBasics (progArgs["namesPath"]);
    if (!nameBasics) {
        throw std::invalid_argument ("Failed to open names.basics.tsv !");
    } 
    std::getline(nameBasics, inputString);
    std::vector<std::string> header = splitString(inputString, '\t');
    if (header.size()!=NBASICS_COLUMNS_AMNT) {
        throw std::invalid_argument ("File name.basics.tsv is corrupted: not enough columns!");
    }
    if (header[NBASICS_NCONST_INDX]!=NBASICS_NCONST_COLNAME || header[NBASICS_NAME_INDX]!=NBASICS_NAME_COLNAME) {
         throw std::invalid_argument ("File name.basics.tsv is corrupted: wrong column contents.");
    }
    nameBasics.close();

    std::fstream titleAkas(progArgs["akasPath"]);
    if (!titleAkas) {
        throw std::invalid_argument("Failed to open title.akas.tsv");
    } 
    std::getline(titleAkas, inputString);
    header = splitString(inputString, '\t');
    if (header.size()!=TAKAS_COLUMNS_AMNT) {
        throw std::invalid_argument ("File title.akas.tsv is corrupted: not enough columns");
    }
    if (header[TAKAS_TCONST_INDX]!=TAKAS_TCONST_COLNAME || header[TAKAS_LOCTITLE_INDX]!=TAKAS_LOCTITLE_COLNAME || header[TAKAS_LOCALE_INDX]!=TAKAS_LOCALE_COLNAME) {
        throw std::invalid_argument("File title.akas.tsv is corrupted: wrong column contents");
    }
    titleAkas.close();

    std::fstream titleBasics(progArgs["basicsPath"]);
    if (!titleBasics) {
        throw std::invalid_argument("Failed to open title.basics.tsv");
    } 
    std::getline(titleBasics, inputString);
    header = splitString(inputString, '\t');
    if (header.size()!=TBASICS_COLUMNS_AMNT) {
        throw std::invalid_argument("File title.basics.tsv is corrupted: not enough columns");
    }
    if (header[TBASICS_TCONST_INDX]!=TBASICS_TCONST_COLNAME || header[TBASICS_TITLETYPE_INDX]!=TBASICS_TITLETYPE_COLNAME || header[TBASICS_ISADULT_INDX]!=TBASICS_ISADULT_COLNAME || header[TBASICS_ORIGTITLE_INDX]!=TBASICS_ORIGTITLE_COLNAME) {
        throw std::invalid_argument("File title.basics.tsv is corrupted: wrong column contents");
    }
    titleBasics.close();

    std::fstream titleCrew(progArgs["crewPath"]);
    if (!titleCrew) {
        throw std::invalid_argument("Failed to open title.crew.tsv");
    }
    std::getline(titleCrew, inputString);
    header = splitString(inputString, '\t');
    if (header.size()!=TCREW_COLUMNS_AMNT) {
        throw std::invalid_argument("File title.crew.tsv is corrupted: not enough columns");
    }
    if (header[TCREW_TCONST_INDX]!=TCREW_TCONST_COLNAME || header[TCREW_DIRECTORS_INDX]!=TCREW_DIRECTORS_COLNAME) {
        throw std::invalid_argument("File title.crew.tsv is corrupted: wrong column contents");
    }
    titleCrew.close();

    return true;
}


std::vector<movie_t> getRussianLocalNames (std::map<std::string, std::string> progArgs) {
    std::vector <movie_t> russianLocalNames;

    std::ifstream nameBasics (progArgs["namesPath"]);
    std::string nconst = getNconstByName(nameBasics, progArgs["director"]);
    if (nconst.empty()) {
        std::cerr << "No such director! " << progArgs["director"] << std::endl;
        return russianLocalNames;
    }
    nameBasics.close();
    
    std::ifstream titleCrew (progArgs["crewPath"]);
    std::vector<std::string> directorFilms = getDirectorFilms(titleCrew, nconst);
    if (directorFilms.empty()) {
        std::cerr << "This director has no titles!" << std::endl;
        return russianLocalNames;
    }
    titleCrew.close();
    
    std::ifstream titleBasics (progArgs["basicsPath"]);
    std::vector<movie_t> notAdultMovies = getNotAdultMovies(titleBasics, directorFilms);
    if (notAdultMovies.empty()) {
        std::cerr << "This director has no not-adult movies!" << std::endl;
        return russianLocalNames;
    }
    titleBasics.close();

    std::ifstream titleAkas (progArgs["akasPath"]);
    russianLocalNames = getRussianMoviesNames(titleAkas, notAdultMovies); //не делаем проверку на empty, так как гарантированно вернутся хотя бы оригинальные названия фильмов
    titleAkas.close();
    
    return russianLocalNames;
}


int main (int argc, char* argv[]) {
    std::map<std::string, std::string> progArgs;
    std::setlocale(LC_ALL, ".UTF-8");
    try {
        progArgs = processArgs(argc, argv);
        checkFiles(progArgs);
    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what() << " Restart program with right input" << std::endl;
        return (-1);
    }
    auto russianMovies = getRussianLocalNames(progArgs);
    if (russianMovies.empty()) {
        return (-1);
    }
    for (size_t i = 0; i < russianMovies.size(); i++) {
        std::cout << russianMovies[i].originName << std::endl;
    }
    return 0;
}
//./build/dz1 "Alfred Hitchcock" --title-akas-path content/title.akas.tsv --title-basics-path content/title.basics.tsv --title-crew-path content/title.crew.tsv --name-basics-path content/name.basics.tsv - на этом тесте работает полторы минуты