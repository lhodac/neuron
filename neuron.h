#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

//CONSTANTES NEURONE
constexpr double R(20);
constexpr double TAU(20);
constexpr double H(1); //1ms
constexpr double TH_POTENTIAL(20);
//constexpr double REFRACTORY_TIME(0.001);Inutile car 1 passage dans la boucle du main correspond a ce temps.


class Neuron {
	
private:
		
	double membranePotential_;
	double nbSpikes_;
	bool refractory_;
	std::vector<double> spikeTimes_;
	

public:
	double getMembranePotential() const;
	double getNbSpikes() const;
	std::vector<double> getTimeSpikes() const;
	bool isRefractory() const;


	
	void setMembranePotential(double potential);
	void setNbSpikes(double nb);
	void setRefractory(bool r);


	void update(double simtime, double I_ext);
	void addTimeSpike(double time);
	double solveDifferentialEquation(double I_ext) const;
	
	Neuron();
	~Neuron();
	
	
	};




#endif
