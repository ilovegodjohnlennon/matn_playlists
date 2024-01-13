#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

struct Stats{
    double totalViews = 0.0;
    double avgViews = 0.0;
    double sigma = 0.0;
    double first = 0.0;
    double last = 0.0;
    double ratio = 0.0;

};

class Playlist{
private:
    std::string name;
    std::vector<double> videoViews;

    Stats stats;
public:
    void calculateStats(){
        stats.totalViews = std::accumulate(
            videoViews.begin(),
            videoViews.end(),
            0.0
        );

        stats.avgViews = stats.totalViews / videoViews.size();
        double mean = stats.avgViews;

        double sq_sum = std::inner_product(
            videoViews.begin(),
            videoViews.end(),
            videoViews.begin(),
            0.0,
            std::plus<double>(),
            [mean](double const& x, double const& y){
                return (x - mean) * (y - mean);
            }
        );

        stats.sigma = std::sqrt(sq_sum / videoViews.size());

        stats.first = videoViews.front();
        stats.last = videoViews.back();
        stats.ratio = stats.last / stats.first;
    }

    void loadInfo(std::ifstream& file){
        for(
            std::string line;
            std::getline(file, line);
        ){
            if(line.empty()) break;
            videoViews.push_back(std::stod(line));
        }

    }

    Playlist(std::string const& name, std::ifstream& file): name(name){
        loadInfo(file);
        calculateStats();
    }

    void debugPrint() const{
        std::cout << name << " (" << videoViews.size() << " videos)\n";
    }

    Stats getStats() const{
        return stats;
    }

    std::vector<double> const& getVideos() const{
        return videoViews;
    }

    void fullPrint() const{
        std::cout
            << std::fixed << std::setprecision(0) <<
            std::setw(40) << name <<
            std::setw(10) << stats.avgViews <<
            std::setw(10) << stats.totalViews <<
            std::setw(10) << stats.sigma <<
            std::setw(10) << videoViews.front() <<
            std::setw(10) << videoViews.back() <<
            std::setw(9) << 100.0 * stats.ratio << '%';
    }


};