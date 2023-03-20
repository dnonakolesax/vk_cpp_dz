#include <fstream>
#include <vector>
#include <iostream>
#include <utils.hpp>
#include "IMDbParser.hpp"

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
            if (findInVector(roles, "director"))  return currString[0]; else return empty;
        }
    }
    return empty;
}

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
        if (findInVector(directors, nconst))  result.push_back(currString[0]);
    }
    return result;
}

std::vector<std::string> getNotAdultMovies (std::fstream& titleBasics, std::vector<std::string> nconsts) {
    std::vector<std::string> result;
    std::string inputString;
    std::getline(titleBasics, inputString, '\n');
    std::vector<std::string> currString = splitString(inputString, '\t');
    if (currString.size()!=9) {
        std::cerr << "File title.basics.tsv is corrupted: not enough columns" << std::endl;
        exit (-1);
    }
    if (currString[0]!="tconst" || currString[1]!="titleType" || currString[4]!="isAdult") {
        std::cerr << "File title.basics.tsv is corrupted: wrong column contents" << std::endl;
        exit (-1);
    }
    while (std::getline(titleBasics, inputString, '\n')) {
        currString = splitString(inputString, '\t');
        if (findInVector(nconsts, currString[0])) {
            if (currString[1]=="movie" && currString[4]!="1") {
                result.push_back(currString[0]);
            }
            if(currString[0] == nconsts[nconsts.size()-1]) return result;
        }
    }
    return result;
}

std::vector<std::string> getRussianMoviesNames (std::fstream& titleAkas, std::vector<std::string> nconsts) {
    std::vector<std::string> result;
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
        if (findInVector(nconsts, currString[0])) {
            if (currString[3]=="RU") {
                result.push_back(currString[2]);
            }
            if(currString[0] == nconsts[nconsts.size()-1]) return result;
        }
    }
    return result;
}