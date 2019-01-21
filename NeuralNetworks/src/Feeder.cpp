//
// Created by v17012405 on 21/01/19.
//
#include "Feeder.h"
#include <cstdlib>
#include <Feeder.h>


std::vector<std::pair<std::vector<float >,std::vector<float>>> Feeder::entrieExit{} ;

/**
 * crée un vecteur d'association entré -> sortie
 *
 */
void Feeder::initEntrieAndExit() {

    std::pair<std::vector<float>, std::vector<float>> pair;

    for (unsigned i = 0; i < 100; ++i) {
        pair.first = {float(rand() % 2), float(rand() % 2), float(rand() % 2), float(rand() % 2)};
        pair.second = {1, 1, 1, 1};

        entrieExit.emplace_back(pair);
    }
}

/**
 *
 * @param entries Paramètre qui va contenir les entrés pour donner au réseaux de neurones
 * @param outputs Paramètre qui va contenir les sorties pour donner au réseaux de neurones
 */
void Feeder::createData(std::vector<std::vector<float>>  & entries, std::vector<std::vector<float> > & outputs){
        Feeder::initEntrieAndExit();
        for(unsigned i =0; i<entrieExit.size()-1; ++i){
            entries.emplace_back(entrieExit[i].first);
            outputs.emplace_back(entrieExit[i].second);
        }
}
