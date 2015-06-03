#include "Ga.h"
#include "Individual.h"
#include "Util.h"
#include <algorithm>
#include <limits.h>

Ga::Ga(){

}

void Ga::setPopulation(int x){
	mPopulationSize=x;
}

void Ga::setMutation(int x){
	mMutation=x;
}

void Ga::setGeneration(int x){
	mGeneration=x;
}

void Ga::setChildNum(int x){
	mChildNum=x;
}

void Ga::execute(){
	int g=0;
	initialize();
	
	while(g<mGeneration){
		crossOver();
		g++;
	}

	//printPopulation();
	printMinFitness();
}

void Ga::printPopulation(){
	for(int i=0;i<mPopulation.size();i++){
		mPopulation[i]->print();
	}
}

void Ga::initialize(){
	for(int i=0;i<mPopulationSize;i++){
		Individual* ind=new Individual();
		ind->initGene();
		mPopulation.push_back(ind);
	}
}

void Ga::crossOver(){
	random_shuffle(mPopulation.begin(),mPopulation.end());
//	for(int i=0;i<mPopulationSize/2;i+=2){
	vector<Individual*> family;
	family.push_back(mPopulation[0]);
	family.push_back(mPopulation[1]);
	jox(family);
	mPopulation[0]=family[0];
	mPopulation[1]=family[1];
//	}
}

void Ga::jox(vector<Individual*> &family){
	#ifdef DEBUG
		cout<<"parent1"<<endl;
		family[0]->print();
		cout<<"parent2"<<endl;
		family[1]->print();
		cout<<"================"<<endl;
	#endif
	for(int i=0;i<mChildNum;i+=2){
		vector<int> saveJob;
		for(int j=0;j<family[0]->getJobNum();j++){
			int r=Util::getRand(0,1);
			if(r==1)
				continue;
			saveJob.push_back(j);
		}
		#ifdef DEBUG
			cout<<"saveJob"<<endl;
			for(int j=0;j<saveJob.size();j++)
				cout<<saveJob[j]<<" ";
			cout<<endl;
			cout<<"======================"<<endl;
		#endif
		Individual *c1=new Individual(family[0]->getMachineNum(),family[0]->getJobNum());
		Individual *c2=new Individual(family[0]->getMachineNum(),family[0]->getJobNum());
		for(int m=0;m<family[0]->getMachineNum();m++){
			vector<int> notSaveJob1,notSaveJob2;
			for(int j=0;j<family[0]->getJobNum();j++){
				int value=(*family[0])[m][j];
				if(Util::includeVector(saveJob,value)){
					(*c1)[m][j]=value;
				}else{
					notSaveJob1.push_back(value);
				}
				value=(*family[1])[m][j];
				if(Util::includeVector(saveJob,value)){
					(*c2)[m][j]=value;
				}else{
					notSaveJob2.push_back(value);
				}
			}
			for(int j=0,k=0,l=0;j<family[0]->getJobNum();j++){
				if((*c1)[m][j]==-1){
					(*c1)[m][j]=notSaveJob2[k];
					k++;
				}
				if((*c2)[m][j]==-1){
					(*c2)[m][j]=notSaveJob1[l];
					l++;
				}
			}
		}
		#ifdef DEBUG
			cout<<"before mutation"<<endl;
			cout<<"c1"<<endl;
			for(int i=0;i<c1->getMachineNum();i++){
				for(int j=0;j<c1->getJobNum();j++){
					cout<<(*c1)[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"c2"<<endl;
			for(int i=0;i<c2->getMachineNum();i++){
				for(int j=0;j<c2->getJobNum();j++){
					cout<<(*c2)[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"==============================="<<endl;
		#endif
		
		mutation(c1);
		mutation(c2);
		
		#ifdef DEBUG
			cout<<"after mutation"<<endl;
			cout<<"c1"<<endl;
			for(int i=0;i<c1->getMachineNum();i++){
				for(int j=0;j<c1->getJobNum();j++){
					cout<<(*c1)[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"c2"<<endl;
			for(int i=0;i<c2->getMachineNum();i++){
				for(int j=0;j<c2->getJobNum();j++){
					cout<<(*c2)[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"==============================="<<endl;
		#endif
		c1->fixGene();
		c2->fixGene();
		
		family.push_back(c1);
		family.push_back(c2);
	}
	
	sort(family.begin(),family.end(),Individual::less);
	#ifdef DEBUG
		cout<<"fitness"<<endl;
		for(int i=0;i<family.size();i++){
			family[i]->print();
		}
		cout<<"============"<<endl;
	#endif
	for(int i=2;i<family.size();i++){
		delete(family[i]);
	}
	
}

void Ga::mutation(Individual* individual){
	int r=Util::getRand(1,100);
	if(r<=mMutation){
		#ifdef DEBUG
			cout<<endl;
			cout<<"mutation"<<endl;
			cout<<endl;
		#endif
		int job=Util::getRand(0,individual->getJobNum()-1);
		for(int m=0;m<individual->getMachineNum();m++){
			vector<int> order;
			int jobIndex;
			for(int j=0;j<individual->getJobNum();j++){
				if((*individual)[m][j]==job){
					jobIndex=j;
					continue;
				}
				order.push_back(j);
			}

			int s=Util::getRand(0,order.size()-1);
			shiftChange((*individual)[m],jobIndex,order[s]);
			#ifdef DEBUG
				cout<<"job="<<job<<endl;
				cout<<"jobIndex="<<jobIndex<<endl;
				cout<<"order[s]="<<order[s]<<endl;
			#endif
		}
	}
}

void Ga::shiftChange(vector<int> &vec,int src,int dst){
	int value=vec[src];
	if(src<dst){
		for(int i=src;i<dst;i++){
			vec[i]=vec[i+1];
		}
		vec[dst]=value;
	}else{
		for(int i=src-1;i>=dst;i--){
			vec[i+1]=vec[i];
		}
		vec[dst]=value;
	}
}

void Ga::printMinFitness(){
	int temp=INT_MAX;
	for(int i=0;i<mPopulationSize;i++){
		int t=mPopulation[i]->getFitness();
		if(temp>t){
			temp=t;
		}
	}
	cout<<"min="<<temp<<endl;
}

Ga::~Ga(){
	for(int i=0;i<mPopulation.size();i++){
		delete(mPopulation[i]);
	}
}