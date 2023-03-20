#ifndef IMDBPARSER_HPP
#define IMDBPARSER_HPP
#include <vector>
#include "utils.hpp"
std::string getNconstByName (std::fstream& nameBasics, std::string name);
std::vector<std::string> getDirectorFilms (std::fstream& titleCrew, std::string nconst);
std::vector<Movie> getNotAdultMovies (std::fstream& titleBasics, std::vector<std::string> nconsts);
std::vector<Movie> getRussianMoviesNames (std::fstream& titleAkas, std::vector<Movie> nconsts);
#endif