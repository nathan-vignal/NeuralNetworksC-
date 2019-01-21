//
// Created by v17012405 on 21/01/19.
//

#include <cstdlib>
#include "Feeder.h"


void Feeder::initEntrieAndExit(){

std::pair<std::vector<float >,std::vector<float>> pair ;
for(unsigned i = 0 ; i< 100; ++i){
    pair.first = {float(random()%2),float(random()%2),float(random()%2),float(random()%2)};
    pair.second = {1,1,1,1};
    Feeder::entrieExit.emplace_back(pair);
}
}

void Feeder::createData(std::vector<std::vector<float>>  & entries, std::vector<std::vector<float> > & outputs){
        Feeder::initEntrieAndExit();
        for(unsigned i =0; i<entrieExit.size()-1; ++i){
            entries.emplace_back(entrieExit[i].first);
            outputs.emplace_back(entrieExit[i].second);
        }
}