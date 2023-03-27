#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utils.hpp>

#include "IMDbParser.hpp"


int findInMovieVector(std::vector<movie_t> input, std::string value) {
    for (size_t i=0; i < input.size(); i++) {
        if (input[i].tconst == value)
            return i;
    }
    return -1;
}


crew_member_t stringIntoCrewMember(std::string inputString) {
    auto currString = splitString(inputString, '\t');
    return crew_member_t(currString[NBASICS_NCONST_INDX],
                         currString[NBASICS_NAME_INDX]);
}


title_directors_t stringIntoTitleDirectors(std::string inputString) {
    auto currString = splitString(inputString, '\t');
    auto directors = splitString(currString[TCREW_DIRECTORS_INDX], ',');
    return title_directors_t(currString[TCREW_TCONST_INDX], directors);
}


title_data_t stringIntoTitleData(std::string inputString) {
    auto currString = splitString(inputString, '\t');
    return title_data_t(currString[TBASICS_TCONST_INDX],
                        currString[TBASICS_ORIGTITLE_INDX],
                        currString[TBASICS_ISADULT_INDX],
                        currString[TBASICS_TITLETYPE_INDX]);
}

localised_movie_t stringIntoLocalisedMovie(std::string inputString) {
        auto currString = splitString(inputString, '\t');
        return localised_movie_t(currString[TAKAS_TCONST_INDX],
                                 currString[TAKAS_LOCTITLE_INDX],
                                currString[TAKAS_LOCALE_INDX]);
}


// Функция поиска уникального идентификатора режиссёра (nconst) по имени
std::string getNconstByName(std::istream& nameBasics, std::string name) {
    std::string inputString;
    std::string empty;
    std::vector<std::string> currString;
    // пропустить строку с описанием колонок
    std::getline(nameBasics, inputString);

    while (std::getline(nameBasics, inputString)) {
        auto currCrewMember = stringIntoCrewMember(inputString);
        if (currCrewMember.name == name) {
            return currCrewMember.nconst;
        }
    }

    return empty;
}


// Функция поиска уникальных идентификаторов (tconst) всех тайтлов режиссёра
// по его уникальному идентификатору (nconst)
std::vector<std::string> getDirectorFilms(std::istream& titleCrew, std::string nconst) {
    std::vector<std::string> result;
    std::string inputString;
    std::vector<std::string> currString;
    std::getline(titleCrew, inputString);

    while (std::getline(titleCrew, inputString)) {
        auto currTitleDirectors = stringIntoTitleDirectors(inputString);
        if (std::find(currTitleDirectors.directors.begin(),
                      currTitleDirectors.directors.end(),
                      nconst) != currTitleDirectors.directors.end())
            result.push_back(currTitleDirectors.tconst);
    }

    return result;
}


// Функция поиска фильмов не для взрослых среди всех фильмов режиссёра
std::vector<movie_t> getNotAdultMovies(std::istream& titleBasics, std::vector<std::string> tconsts) {
    std::vector<movie_t> result;
    std::string inputString;
    std::vector<std::string> currString;

    while (std::getline(titleBasics, inputString)) {
        auto titleData = stringIntoTitleData(inputString);
        // Эффективнее сначала отсеивать фильмы не для взрослых,
        // а уже потом смотреть режиссёров
        if (titleData.titleType == REQUIRED_TITLE_TYPE &&
            titleData.isAdult != REQUIRED_ISADULT) {
            auto pos = std::find(tconsts.begin(), tconsts.end(),
                                 titleData.tconst);
            if (pos != tconsts.end()) {
                result.emplace_back(titleData.tconst, titleData.originalName);
                /* Если тайтл нашёлся, вычёркиваем его из вектора поиска, 
                чтобы не тратить время на сравнение уже найденных фильмов
                с очередным tconst */
                tconsts.erase(pos);
            }
        }
    }

    return result;
}


// Функция поиска русских названий фильмов режиссёра.
// Если русского названия нет - возвращается оригинальное название.
std::vector<movie_t> getRussianMoviesNames(std::istream& titleAkas, std::vector<movie_t> movies) {
    std::vector<movie_t> result;
    std::string inputString;
    std::vector<std::string> currString;

    while (std::getline(titleAkas, inputString)) {
        auto localMovie = stringIntoLocalisedMovie(inputString);
        // Эффективнее сначала отсеивать фильм по языку локализации,
        // а уже потом смотреть режиссёров
        if (localMovie.region == "RU") {
            int pos = findInMovieVector(movies, localMovie.tconst);
            if (pos != -1) {
                movies[pos].originName = localMovie.localName;
                result.push_back(movies[pos]);
                 /*Если фильм нашёлся, вычёркиваем его из поиска, 
                 *чтобы не тратить время на сравнение уже найденных фильмов 
                 с очередным tconst*/
                movies.erase(movies.begin() + pos);
            }
        }
    }
    // При возврате присоединяем ненайденное,
    // чтобы вывести оригинальные названия.
    result.insert(result.end(), movies.begin(), movies.end());
    return result;
}
