#include "utils.hpp"

bool fileEndsWithSuffix(string file,string suffix){
    // file name long enough?
    if (file.length() > suffix.length()){
        return (file.compare(file.length()-suffix.length(),suffix.length(),suffix) == 0);
    }
    return false;
}