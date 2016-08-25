#include<iostream>
using namespace std;

struct Job{
	int deadline;
	float penalty;
	int length;
	float score;
};

Job* jobs;
int numJobs;

Job* mergeSort(Job* array1,int size1, Job* array2, int size2){
	int size = size1 + size2;
	Job* array = new Job[size];
	int i=0, j=0, k=0;
	while(i<size1 && j<size2){
		if(array1[i].score > array2[j].score){
			array[k] = array1[i];
			i++;
		}
		else{
			array[k] = array2[j];
			j++;
		}
		k++;
	}
	while(k < size){
		if(i == size1){
			array[k] = array2[j];
			j++;
		}
		else{
			array[k] = array1[i];
			i++;
		}
		k++;
	}
	return array;
}
	
Job* mSort(Job* array,int beg, int end){
	if(beg == end){
		Job* output = new Job[1];
		output[0] = array[beg];
		return output;
	}
	Job* array1 = mSort(array, beg, (beg+end)/2);
	Job* array2 = mSort(array, (beg+end)/2+1, end);
	int s1 = (beg+end)/2 - beg +1;
	int s2 = end - (beg+end)/2;
	Job* output = mergeSort(array1, s1, array2, s2);
	return output;
}

Job* mergeSortInc(Job* array1,int size1, Job* array2, int size2){
	int size = size1 + size2;
	Job* array = new Job[size];
	int i=0, j=0, k=0;
	while(i<size1 && j<size2){
		if(array1[i].deadline < array2[j].deadline){
			array[k] = array1[i];
			i++;
		}
		else{
			array[k] = array2[j];
			j++;
		}
		k++;
	}
	while(k < size){
		if(i == size1){
			array[k] = array2[j];
			j++;
		}
		else{
			array[k] = array1[i];
			i++;
		}
		k++;
	}
	return array;
}
	
Job* mSortInc(Job* array,int beg, int end){
	if(beg == end){
		Job* output = new Job[1];
		output[0] = array[beg];
		return output;
	}
	Job* array1 = mSortInc(array, beg, (beg+end)/2);
	Job* array2 = mSortInc(array, (beg+end)/2+1, end);
	int s1 = (beg+end)/2 - beg +1;
	int s2 = end - (beg+end)/2;
	Job* output = mergeSortInc(array1, s1, array2, s2);
	return output;
}

void enterJobSequence(){
	cout<<"Enter number of jobs";		cin>>numJobs;
	jobs = new Job[numJobs];
	cout<<"Enter job deadline, length and penality for each job: \n";
	for(int i=0; i<numJobs; i++){
		cin >> jobs[i].deadline >> jobs[i].length >> jobs[i].penalty;
		jobs[i].score = jobs[i].penalty / jobs[i].length;
	}
}

int sequenceJobs(){
	int deadline=0;
	float penalty = 0;
	Job* jobSequence = new Job[numJobs];
	int j=0;
	for(int i=0; i<numJobs; i++){
		if(deadline+jobs[i].length <= jobs[i].deadline){
			deadline += jobs[i].length;
			jobSequence[j++] = jobs[i];
		}
		else{
			bool x = true;
			jobSequence[j] = jobs[i]; 
			Job* temp = mSortInc(jobSequence, 0, j);
			int d=0;
			for(int k=0; k<=j; k++){
				d += temp[j].length;
				if(d > temp[j].deadline){
					x = false;
				}
			}
			if(x){
				deadline += jobs[i].length;
				jobSequence[j++] = jobs[i];
			} else{
				penalty += jobs[i].penalty;
			}
		}
	}
	return penalty;
}

int main(){
	// 7 4 1 70 2 1 60 4 1 50 3 1 40 1 1 30 4 1 20 6 1 10
	enterJobSequence();
	jobs = mSort(jobs, 0, numJobs-1);
	float penalty = sequenceJobs();
	cout<<"Total minimum penalty of sequencing these jobs: "<<penalty;
	return 0;
}
