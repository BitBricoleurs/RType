//
// Created by Clément Lagasse on 28/09/2023.
//

#include "Body.hpp"

void Network::Body::addData(std::vector <std::uint8_t> &data)
{
    this->_data.insert(this->_data.end(), data.begin(), data.end());
}

std::vector<std::uint8_t> &Network::Body::getData()
{
    return this->_data;
}

unsigned int Network::Body::getSize()
{
    return this->_data.size();
}