#include "utils.hpp"

bool fileEndsWithSuffix(string file,string suffix){
    // file name long enough?
    if (file.length() > suffix.length()){
        return (file.compare(file.length()-suffix.length(),suffix.length(),suffix) == 0);
    }
    return false;
}

void printCollisionMap(int collisionMap[]){
    for (int x = 0; x < DEFAULT_SCREEN_WIDTH; x++ ){
        for (int y = 0; y < DEFAULT_SCREEN_HEIGHT; y++){
            cout << collisionMap[POSITION_TO_INDEX(x,y)] << " ";
        }
    cout << endl;
    }
}