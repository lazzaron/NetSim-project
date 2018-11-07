#include "network.h"
#include "random.h"
#include <iostream>
#include <algorithm>

void Network::resize(const size_t& n){
	values.resize(n);
	RNG.normal(values,0,1);
}

 bool Network::add_link(const size_t& a, const size_t& b){
	if(a!=b and a<size() and b< size()){
		for(auto it = links.find(a); it!=links.end();++it){
			if (it->second==b){
				return false;
			}
		}
		links.insert({{a,b},{b,a}});
		return true;
	}
	else{
		return false;
	}
}
		
		

size_t Network::random_connect(const double& mean){
	links.clear();
	std::vector<size_t> otherNodes;
	std:: vector<int> n_link(size());
	for(size_t n(0); n<size(); n++){
		otherNodes.push_back(n);
	}
	RNG.poisson(n_link,mean);
	for(size_t n(0);n<size();++n){
		RNG.shuffle(otherNodes);
		for(size_t i(0); i< otherNodes.size(); ++i){
			if((degree(n)<size_t (n_link[n])) and( size_t (n_link[otherNodes[i]])>degree(otherNodes[i]))){
				
				add_link(n,otherNodes[i]);
			}
		}
	}
	return links.size();
	
}
		
	
	
	


size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t &_n) const{
	return links.count(_n);
}

size_t Network::set_values(const std::vector<double>& newValues){
	
	if(newValues.size()<=size()){
		for(size_t n(0); n<newValues.size();++n){
			values[n]=newValues[n];
			}
		return newValues.size();
		}
	
	for(size_t n(0); n<size();++n){
			values[n]=newValues[n];
	}
	return size();
}

double Network::value(const size_t &_n) const{
	return values[_n]; 
}

std::vector<double> Network::sorted_values() const{
	std::vector<double> sortvalues(values);
	std::sort(sortvalues.begin(),sortvalues.end(), std::greater<double>());
	return sortvalues;
}

std::vector<size_t> Network::neighbors(const size_t& n) const{
	std::vector<size_t> neighbor;
	for(auto I :links){
		if(I.first ==n){
			neighbor.push_back(I.second);
		}
	}
	return neighbor;
}
       		
		
