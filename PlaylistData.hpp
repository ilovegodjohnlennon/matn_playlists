#pragma once
#include "Playlist.hpp"

class PlaylistData{
private:
    std::vector<std::unique_ptr<Playlist>> playlists;
public:
    void load(std::string const& fileName){
        std::ifstream file {fileName};

        for(
            std::string line;
            std::getline(file, line);
        ){
            if(line.empty()) continue;
            playlists.push_back(std::make_unique<Playlist>(line, file));
        }

        std::cout << "Successfully loaded " << playlists.size() << " playlists!\n";
    }

    PlaylistData(std::string const& fileName){
        load(fileName);
    }

    void debugPrint() const{
        for(auto& p: playlists){
            p->debugPrint();
        }
    }

    void fullPrint() const{

        std::cout << 
            std::setw(40) << "Name" <<
            std::setw(10) << "Avg." <<
            std::setw(10) << "Total" <<
            std::setw(10) << "Sigma" <<
            std::setw(10) << "First" <<
            std::setw(10) << "Last" <<
            std::setw(10) << "Ratio";
        
        std::cout << "\n\n";

        for(auto& p: playlists){
            p->fullPrint();
            std::cout << '\n';
        }
    }

    void sortByTotalViews(){
        std::sort(
            playlists.begin(),
            playlists.end(),
            [](std::unique_ptr<Playlist> const& p1, std::unique_ptr<Playlist> const& p2){
                return p1->getStats().totalViews > p2->getStats().totalViews;
            }
        );
    }

    void sortByAvgViews(){
        std::sort(
            playlists.begin(),
            playlists.end(),
            [](std::unique_ptr<Playlist> const& p1, std::unique_ptr<Playlist> const& p2) {
                return p1->getStats().avgViews > p2->getStats().avgViews;
            }
        );
    }

    void sortByFirstViews() {
        std::sort(
            playlists.begin(),
            playlists.end(),
            [](std::unique_ptr<Playlist> const& p1, std::unique_ptr<Playlist> const& p2) {
                return p1->getStats().first > p2->getStats().first;
            }
        );
    }

    void sortByLastViews() {
        std::sort(
            playlists.begin(),
            playlists.end(),
            [](std::unique_ptr<Playlist> const& p1, std::unique_ptr<Playlist> const& p2) {
                return p1->getStats().last > p2->getStats().last;
            }
        );
    }

    void sortByRatio() {
        std::sort(
            playlists.begin(),
            playlists.end(),
            [](std::unique_ptr<Playlist> const& p1, std::unique_ptr<Playlist> const& p2) {
                return p1->getStats().ratio > p2->getStats().ratio;
            }
        );
    }





};
