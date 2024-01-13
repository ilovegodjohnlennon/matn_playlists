#include "PlaylistData.hpp"
 
int main(){
    PlaylistData pd {"stats.txt"};

    std::cout << "\n\n\nBy total views:\n\n";

    pd.sortByTotalViews();
    pd.fullPrint();

    std::cout << "\n\n\nBy average views:\n\n";

    pd.sortByAvgViews();
    pd.fullPrint();

    std::cout << "\n\n\nBy views on first video:\n\n";

    pd.sortByFirstViews();
    pd.fullPrint();

    std::cout << "\n\n\nBy views on last video:\n\n";

    pd.sortByLastViews();
    pd.fullPrint();

    std::cout << "\n\n\nBy ratio of views on last video to first video:\n\n";

    pd.sortByRatio();
    pd.fullPrint();





    return 0;
}