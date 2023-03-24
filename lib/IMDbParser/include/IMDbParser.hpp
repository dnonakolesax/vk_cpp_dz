#ifndef IMDBPARSER_HPP
#define IMDBPARSER_HPP


#include <vector>
#include "utils.hpp"


#define TAKAS_TCONST_INDX 0
#define TAKAS_TCONST_COLNAME "titleId"
#define TAKAS_LOCALE_INDX 3
#define TAKAS_LOCALE_COLNAME "region"
#define TAKAS_LOCTITLE_INDX 2
#define TAKAS_LOCTITLE_COLNAME "title"

#define TCREW_TCONST_INDX 0
#define TCREW_TCONST_COLNAME "tconst"
#define TCREW_DIRECTORS_INDX 1
#define TCREW_DIRECTORS_COLNAME "directors"

#define TBASICS_TCONST_INDX 0
#define TBASICS_TCONST_COLNAME "tconst"
#define TBASICS_ISADULT_INDX 4
#define TBASICS_ISADULT_COLNAME "isAdult"
#define TBASICS_ORIGTITLE_INDX 3
#define TBASICS_ORIGTITLE_COLNAME "originalTitle"
#define TBASICS_TITLETYPE_INDX 1
#define TBASICS_TITLETYPE_COLNAME "titleType"

#define NBASICS_NCONST_INDX 0
#define NBASICS_NCONST_COLNAME "nconst"
#define NBASICS_NAME_INDX 1
#define NBASICS_NAME_COLNAME "primaryName"


struct movie_t {
    std::string tconst;
    std::string originName;
    movie_t (std::string _tc, std::string _name) : tconst(_tc), originName (_name) {}; 
};

struct crew_member_t {
    std::string nconst;
    std::string name;
    crew_member_t (std::string _nc, std::string _name) : nconst(_nc), name (_name) {};
};

struct title_directors_t {
    std::string tconst;
    std::vector<std::string> directors;
    title_directors_t (std::string _tc, std::vector<std::string> _dirs) : tconst(_tc), directors(_dirs) {};
};

struct title_data_t {
    std::string tconst;
    std::string originalName;
    std::string isAdult;
    std::string titleType;
    title_data_t (std::string _tc, std::string _name, std::string _isAdult, std::string _tt) : tconst(_tc), originalName(_name), isAdult(_isAdult), titleType (_tt) {};
};

struct localised_movie_t {
    std::string tconst;
    std::string localName;
    std::string region;
    localised_movie_t (std::string _tc, std::string _lname, std::string _reg) : tconst(_tc), localName(_lname), region(_reg) {};
};


std::string getNconstByName (std::istream& nameBasics, std::string name);
std::vector<std::string> getDirectorFilms (std::istream& titleCrew, std::string nconst);
std::vector<movie_t> getNotAdultMovies (std::istream& titleBasics, std::vector<std::string> nconsts);
std::vector<movie_t> getRussianMoviesNames (std::istream& titleAkas, std::vector<movie_t> nconsts);

crew_member_t stringIntoCrewMember (std::string inputString);
title_directors_t stringIntoTitleDirectors (std::string inputString);
title_data_t stringIntoTitleData (std::string inputString);
localised_movie_t stringIntoLocalisedMovie (std::string inputString);

int findInMovieVector (std::vector<movie_t> input, std::string value);

#endif
