#include <iostream>
#include <fstream>
#include <cmath>
#include "neuron.h"

using namespace std;

//GETTERS
double Neuron:: getMembranePotential() const
{
	return membranePotential_;
}
double Neuron:: getNbSpikes() const
{
	return nbSpikes_;
}
vector<double> Neuron:: getTimeSpikes() const
{
	return spikeTimes_;
}
bool Neuron:: isRefractory() const
{
	return refractory_;
}


//SETTERS
void Neuron:: setMembranePotential(double potential)
{
	membranePotential_= potential;
}
void Neuron:: setNbSpikes(double nb)
{
	nbSpikes_= nb;
}
void Neuron:: setRefractory(bool r)
{
	refractory_= r;
}

//To add one time at the spikeTimes table
void Neuron::addTimeSpike(double time)
{
	spikeTimes_.push_back(time);
}

//To update the simulation at each steps
void Neuron:: update(double simtime, double I_ext)
{
	if(isRefractory()){
		setMembranePotential(0.0);
		setRefractory(false);
		cout << getMembranePotential() << endl << "REFRACTORY" <<endl;
		}
	else if(getMembranePotential() > TH_POTENTIAL) {
		addTimeSpike(simtime);
		setRefractory(true);
		cout << getMembranePotential() << endl << "SPIKE JUST HAPPENED" <<endl;
		}
		
		setMembranePotential(solveDifferentialEquation(I_ext));
		
}
//To solve the equation of the potential
double Neuron:: solveDifferentialEquation(double I_ext) const
{
	return exp(-H/TAU) * getMembranePotential() + I_ext * R * (1-exp(-H/TAU));
}

//Constructor: we initialise the values at 0.0 and false
Neuron:: Neuron()
: membranePotential_(0.0), nbSpikes_(0.0), refractory_(false)
{}

//Destructor: we clear the times vector
Neuron:: ~Neuron()
{
	spikeTimes_.clear();
}



int main()
{	
	Neuron first;
	int simtime(0.0);
	

	//Ask the user wich current and simulation time he wants
	cout << "Enter the number of steps: " << endl;
	double nbSteps(0.0);
	cin >> nbSteps;
	if (nbSteps < 0.0){cout << "ERROR: steps number has to be a positive value.";}
	
	cout << "Enter a External Current: " << endl;
	double I_ext(0.0);
	cin >> I_ext;
	
	
	/*double nbSteps(100);
	double I_ext(1.01);*/
	
	ofstream sortie;
	sortie.open("potentiels.txt");
	
	
	while(simtime < (nbSteps*H))
	{
		first.update(simtime, I_ext);
		simtime+=H;
		
		sortie << first.getMembranePotential() <<endl;
	}
	 sortie.close();
	
	return 0;
	 
	 
}
