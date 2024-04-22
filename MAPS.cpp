#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

const int MAX=1000;

int idx=0;
string data[MAX]; // max data 1000 kota, dgn panjang nama 100
double graph[MAX][MAX]={0};
double jarak_antar[MAX][MAX];

void menu(){
	cout<<"Welcome to MAPS\n\n";
	cout<<"[--PROGRAM MENU--]--\n\n";
	cout<<"1. Tambah Lokasi\n";
	cout<<"2. Cari Rute\n";
	cout<<"3. EXIT\n";	
}

bool compareStrings(string& str1, string& str2){
    if (str1.length() != str2.length())
        return false;

    for (int i = 0; i < str1.length(); ++i) {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }

    return true;
}

int find_idx(string kota){

	for(int i=0; i<idx; i++){
		if(compareStrings(kota, data[i])){
			return i;
		}
	}
	data[idx]=kota;
	idx++;
	return idx-1;
}

int found(string kota){

	for(int i=0; i<idx; i++){
		if(compareStrings(kota, data[i])){
			return i;
		}
	}
	return -1;
}

void add(){
	int lokasi1=-1, lokasi2=-2;
	string kota1, kota2;
	do{
		cout<<"Input Lokasi pertama ";
		cin>>kota1;
		
		cout<<"Input Lokasi kedua ";
		cin>>kota2;
		if(compareStrings(kota1, kota2)){
			system("CLS");
			cout<<"Lokasi 1 dan 2 tidak boleh mempunya nama yang sama, mohon input ulang\n";
		}
		
	}while(compareStrings(kota1, kota2));
	
	lokasi1=find_idx(kota1);	
	lokasi2=find_idx(kota2);
	
	cout<<"Input jarak antar 2 lokasi tersebut (input berupa angka)(km) "; // input tidak pakai satuan, untuk aka desimal pakai '.' contoh 11.2
	double jarak;
	cin>>jarak;
	
	graph[lokasi1][lokasi2]=jarak;
	graph[lokasi2][lokasi1]=jarak;
	
	system("CLS");
	cout<<"\njarak antara "<<data[lokasi1]<<" dan "<<data[lokasi2]<<" sejauh "<<graph[lokasi2][lokasi1]<<"km sudah ditambahkan ke data!\n\n";
	
}

void printall(){
	if(idx==0){
		cout<<"\nDATA EMPTY!\n\n";
		return;
	}
	else cout<<"DATA\n";
	for(int i=0; i<idx; i++){
		for(int j=0; j<idx; j++){
			if(graph[i][j]==0)continue;
			cout<<data[i]<<" ke "<<data[j]<<" = "<< graph[i][j]<<"km\n";
		}
	}
}

void printPath(int currentVertex, double parents[]){
 	
    if (currentVertex == -1) {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout << data[currentVertex] << " -> ";
}
 


void printSolution(double distances[], double parents[], int end){   
    printPath(end, parents);
    cout<<(double)distances[end]<<"km ";
}
 

 
double dijkstra(int start, int end){
    
    // shortestDistances[i] will hold the
    // shortest distance from src to i
    double shortestDistances[idx];
 
    // added[i] will true if vertex i is
    // included / in shortest path tree
    // or shortest distance from src to
    // i is finalized
    bool added[idx];
 
    // Initialize all distances as
    // INFINITE and added[] as false
    for (int vertexIndex = 0; vertexIndex < idx;vertexIndex++) {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }
 
    // Distance of source vertex from
    // itself is always 0
    shortestDistances[start] = 0;
 
    // Parent array to store shortest
    // path tree
    double parents[idx];
 
    // The starting vertex does not
    // have a parent
    parents[start] = -1;
 
    // Find shortest path for all
    // vertices
    for (int i = 1; i < idx; i++) {
 
        // Pick the minimum distance vertex
        // from the set of vertices not yet
        // processed. nearestVertex is
        // always equal to startNode in
        // first iteration.
        int nearestVertex = -1;
        double shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < idx; vertexIndex++) {
            if (!added[vertexIndex]&& shortestDistances[vertexIndex] < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance = shortestDistances[vertexIndex];
            }
        }
 
        // Mark the picked vertex as
        // processed
        added[nearestVertex] = true;
 
        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
        for (int vertexIndex = 0; vertexIndex < idx; vertexIndex++) {
            double edgeDistance= graph[nearestVertex][vertexIndex];
 
            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[vertexIndex])){
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }
 
    printSolution(shortestDistances, parents, end);
    return shortestDistances[end];
}

void cari(){
	if(idx==0)return;	
	int lokasi1=-1, lokasi2=-2;
	string kota1, kota2;
	do{
		cout<<"Input Start ";
		cin>>kota1;
		
		cout<<"Input Finish ";
		cin>>kota2;
		lokasi1=found(kota1);// cari apakah kotanya sudah ada di data	
		lokasi2=found(kota2);
		if(compareStrings(kota1, kota2)){
			system("CLS");
			cout<<"Lokasi 1 dan 2 tidak boleh mempunya nama yang sama, mohon input ulang\n";
			printall();
		}
		else if(lokasi1==-1||lokasi2==-1){
			system("CLS");
			cout<<"Lokasi tidak ada di data\n";
			printall();
		}
		
	}while(compareStrings(kota1, kota2)||lokasi1==-1||lokasi2==-1);
	lokasi1=find_idx(kota1);	
	lokasi2=find_idx(kota2);
	
	
	cout<<"Kendaraan apa yang dipakai (motor{50km/jam}/mobil{80km/jam})? "; 
	string kendaraan, mobil="mobil", motor="motor";
	cin>>kendaraan;
	while(!compareStrings(kendaraan, mobil)&&!compareStrings(kendaraan, motor)){
		cout<<"Input kendaraan yang sesuai(mobil/motor) "; 
		cin>>kendaraan;
	}
	system("CLS");
	puts("");
	double time = (double)dijkstra(lokasi1, lokasi2);
	cout<<"dengan "<<kendaraan<<" akan memakan waktu selama ";
	if(compareStrings(kendaraan, mobil)){
		time=(double)time/80;
		if(time>=1){
			cout<<(int)time<<"jam ";
			time-=(int)time;
		}
		cout<<(double)time*60<<"menit";
	}
	else if(compareStrings(kendaraan, motor)){
		time=(double)time/50;
		if(time>=1){
			cout<<(int)time<<"jam ";
			time-=(int)time;
		}
		cout<<(double)time*60<<"menit";
	}
	puts("");
}



int main(){
	
	
	while(1){
		menu();
		cout<<"Pilih Opsi(1-3) ";
		
		string input;
		cin>>input;
		
		while(input[0]>'3'||input[0]<'1'||input.size()!=1){
			system("CLS");
			menu();
			cout<<"Mohon masukan input yang benar(1-3) ";
			cin>>input;
		}
		
		if(input[0]=='1'){
			system("CLS");
			add();
		}
		else if(input[0]=='2'){
			system("CLS");
			printall();
			cari();
		}
		else if(input[0]=='3'){
			system("CLS");
			cout<<"goodbye :(";
			return 0;
		}
	}
}
