#include <fstream>
#include <vector>
#include <iostream>
#include <utils.hpp>
#include "IMDbParser.hpp"

//Функция поиска уникального идентификатора режиссёра (nconst) по имени
std::string getNconstByName (std::fstream& nameBasics, std::string name) {
    std::string inputString;
    std::string empty;
    std::getline(nameBasics, inputString, '\n');
    std::vector<std::string> currString = splitString(inputString, '\t');
    if (currString.size()!=6) {
        std::cerr << "File name.basics.tsv is corrupted: not enough columns" << std::endl;
        exit (-1);
    }
    if (currString[0]!="nconst" || currString[1]!="primaryName") {
        std::cerr << "File name.basics.tsv is corrupted: wrong column contents" << std::endl;
        exit (-1);
    }
    while (std::getline(nameBasics, inputString, '\n')) {
        currString = splitString(inputString, '\t');
        if (currString[1]==name) { 
            std::vector<std::string> roles = splitString(currString[4], ',');
            if (findInVector(roles, "director")!=-1)  return currString[0]; else return empty;
        }
    }
    return empty;
}

//Функция поиска уникальных идентификаторов (tconst) всех тайтлов режиссёра по его уникальному идентификатору (nconst)
std::vector<std::string> getDirectorFilms (std::fstream& titleCrew, std::string nconst) {
    std::vector<std::string> result;
    std::string inputString;
    std::getline(titleCrew, inputString, '\n');
    std::vector<std::string> currString = splitString(inputString, '\t');
    if (currString.size()!=3) {
        std::cerr << "File title.crew.tsv is corrupted: not enough columns" << std::endl;
        exit (-1);
    }
    if (currString[0]!="tconst" || currString[1]!="directors") {
        std::cerr << "File title.crew.tsv is corrupted: wrong column contents" << std::endl;
        exit (-1);
    }
    while (std::getline(titleCrew, inputString, '\n')) {
        currString = splitString(inputString, '\t');
        std::vector<std::string> directors = splitString(currString[1], ',');
        if (findInVector(directors, nconst)!=-1)  result.push_back(currString[0]);
    }
    return result;
}

//Функция поиска фильмов не для взрослых среди всех фильмов режиссёра
std::vector<Movie> getNotAdultMovies (std::fstream& titleBasics, std::vector<std::string> tconsts) {
    std::vector<Movie> result;
    std::string inputString;
    std::getline(titleBasics, inputString, '\n');
    std::vector<std::string> currString = splitString(inputString, '\t');
    if (currString.size()!=9) {
        std::cerr << "File title.basics.tsv is corrupted: not enough columns" << std::endl;
        exit (-1);
    }
    if (currString[0]!="tconst" || currString[1]!="titleType" || currString[4]!="isAdult" || currString[3]!="originalTitle") {
        std::cerr << "File title.basics.tsv is corrupted: wrong column contents" << std::endl;
        exit (-1);
    }
    while (std::getline(titleBasics, inputString, '\n')) {
        currString = splitString(inputString, '\t');
        if (currString[1]=="movie" && currString[4]!="1") {                     //Эффективнее сначала отсеивать фильмы не для взрослых, а уже потом смотреть режиссёров
            int pos = findInVector(tconsts, currString[0]);
            if (pos!=-1) {
                Movie movie;
                movie.tconst=currString[0];
                movie.originName = currString[3];
                result.push_back(movie);
                tconsts.erase(tconsts.begin()+pos);                             //Если тайтл нашёлся, вычёркиваем его из поиска
                if(currString[0] == tconsts[tconsts.size()-1]) return result;   //Так как все тайтлы отсортированы в файле и в векторе, если мы нашли последний из вектора, можно прекращать поиск
            }
        }
    }
    return result;
}

//Функция поиска русских названий фильмов режиссёра. Если русского названия нет - возвращается оригинальное название.
std::vector<Movie> getRussianMoviesNames (std::fstream& titleAkas, std::vector<Movie> movies) {
    std::vector<Movie> result;
    std::string inputString;
    std::getline(titleAkas, inputString, '\n');
    std::vector<std::string> currString = splitString(inputString, '\t');
    if (currString.size()!=8) {
        std::cerr << "File title.akas.tsv is corrupted: not enough columns" << std::endl;
        exit (-1);
    }
    if (currString[0]!="titleId" || currString[2]!="title" || currString[3]!="region") {
        std::cerr << "File title.akas.tsv is corrupted: wrong column contents" << std::endl;
        exit (-1);
    }
    while (std::getline(titleAkas, inputString, '\n')) {
        currString = splitString(inputString, '\t');
        if (currString[3]=="RU") {                                                      //Эффективнее сначала отсеивать фильм по языку локализации, а уже потом смотреть режиссёров
            int pos = findInMovieVector(movies, currString[0]);
            if (pos!=-1) {
                movies[pos].originName = currString[2];
                result.push_back(movies[pos]);
                movies.erase(movies.begin()+pos); //Если фильм нашёлся, вычёркиваем его из поиска
                if(currString[0] == movies[movies.size()-1].tconst) {result.insert(result.end(), movies.begin(), movies.end()); return result;} //Так как все фильмы отсортированы в файле и в векторе, если мы нашли последний из вектора, можно прекращать поиск. При возврате присоединяем ненайденное, чтобы вывести оригинальные названия.
            }
        }
    }
    result.insert(result.end(), movies.begin(), movies.end()); //При возврате присоединяем ненайденное, чтобы вывести оригинальные названия.
    return result;
}