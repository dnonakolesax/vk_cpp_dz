#include <vector>
std::string getNconstByName (std::fstream& nameBasics, std::string name);
std::vector<std::string> getDirectorFilms (std::fstream& titleCrew, std::string nconst);
std::vector<std::string> getNotAdultMovies (std::fstream& titleBasics, std::vector<std::string> nconsts);
std::vector<std::string> getRussianMoviesNames (std::fstream& titleAkas, std::vector<std::string> nconsts);