//
// Created by v17012405 on 21/01/19.
//

#ifndef NEURALNETWORKSC_FEEDER_H
#define NEURALNETWORKSC_FEEDER_H


#include <vector>

class Feeder {

public :
    static  std::vector<std::pair<std::vector<float >,std::vector<float>>> entrieExit;
    static void createData( std::vector<std::vector<float>>  & entries, std::vector<std::vector<float> > & outputs);
    static void  initEntrieAndExit();


};


#endif //NEURALNETWORKSC_FEEDER_H
