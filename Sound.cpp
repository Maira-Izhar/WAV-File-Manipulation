#include <iostream>
#include "wavfile.h"
using namespace std;


void playfile(char* str) {
	if (playWavFile(str) == 0)
		cout << "Error: File not found!" << endl;
}

//Sample function for reading and storing sound data
void read_data(char* str) {
	
		int sampleRate = 0, size = 100000000;
		unsigned char* ptr = new unsigned char[size];
		readWavFile(str, ptr, size, sampleRate);
		delete[] ptr;
	
}


//QUESTION 1
void AllocateArray(unsigned char*& arr, int size) {
	arr = new unsigned char[size];
}


//QUESTION 2
void deallocateArray(unsigned char*& arr) {
	delete[] arr;
}


//QUESTION 3 
void print(unsigned char*& arr, int size) {
	cout << endl << "Displaying Array: ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


//QUESTION 4 
void doubleArray(unsigned char*& arr, unsigned char*& dubble, int size) {
	int j = 0;
	for (int i = 0; i <= size; i++, j++) {
		dubble[j] = arr[i];
		dubble[++j] = arr[i];

	}
}


//QUESTION 5 
void shrinkArray(unsigned char*& arr, unsigned char*& shrink, int size) {
	int size1 = 0;
	/*if (size % 2 == 0) {
		size1 = size / 2;
	}
	else {
		size1 = (size + 1) / 2;
	}*/
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (i % 2 == 0) {
			shrink[j] = arr[i];
			j++;
		}
	}
}


//QUESTION 6
void FillWithMean(unsigned char* in, unsigned char*& out, int N, int size) {
	int count = 0, sum=0;
	for (int i = 0; i < size; i++) {
		sum = 0, count = 0;
		for (int j = i - N; j <= i + N; j++) {
			if (j >= 0 && j < size) {
				count++;
				sum += in[j];
			}
		}
		out[i] = sum / count;
	}
}


//QUESTION 8
void upSampleAudio(char* str) {
	int sampleRate = 0, size = 100000000;
	unsigned char* ptr = new unsigned char[size];
	readWavFile(str, ptr, size, sampleRate);
	unsigned char* ptr2 = new unsigned char[size * 2];
	doubleArray(ptr, ptr2, size);
	char upsample[20] = "upsample.wav";
	writeWavFile(upsample, ptr2, size*2, sampleRate);
	playWavFile(upsample);
}


//QUESTION 9
void downSampleAudio(char* str) {
	int sampleRate = 0, size = 100000000;
	unsigned char* ptr = new unsigned char[size];
	readWavFile(str, ptr, size, sampleRate);
	unsigned char* shrink = new unsigned char[size/2];
	shrinkArray(ptr, shrink, size);
	char downsample[20] = "downsample.wav";
	writeWavFile(downsample, shrink, size/2, sampleRate);
	playWavFile(downsample);
}


//QUESTION 10
void movingAverageFilter(char* str, int N) {
	int sampleRate = 0, size = 100000000;
	unsigned char* ptrin = new unsigned char[size];
	readWavFile(str, ptrin, size, sampleRate);
	unsigned char* ptrout = new unsigned char[size];
	FillWithMean(ptrin, ptrout, N, size);
	char averagefilter[20] = "filter.wav";
	writeWavFile(averagefilter, ptrout, size, sampleRate);
	playWavFile(averagefilter);
}


//QUESTION 11
void mergearray(unsigned char* arr1, int size1, unsigned char* arr2, int size2, unsigned char*& merge) {
	int j = 0, k=0, i=0;
	while (i < size1 && j < size2) {
		merge[k++] = arr1[i++];
		merge[k++] = arr2[j++];
	}


	while (i < size1) {
		merge[k++] = arr1[i++];
	}
	while (j < size2) {
		merge[k++] = arr2[j++];
	}
}

int main(){
	char str[50] = "";
	bool flag = true;
	int N;
	while (flag) {
		//You can add more options in menue function
		cout << "Enter file name with (.wav) or exit: ";
		cin >> str;
		if (strcmp(str, "exit") != 0) {
			read_data(str);
			playfile(str);
		}
		else
			flag = 0;


		int option;
		cout << endl << "MENU: " << endl;
		cout << "Enter a number for: " << endl;
		cout << "1. To Upsample the Audio file. " << endl;
		cout << "2. To downsample the Audio file. " << endl;
		cout << "3. For moving average filter. " << endl;
		cout << "4. To merge the Audio files. " << endl;
		cout << "0. To exit. " << endl;
		cin >> option;
		while (option != 0) {

			if (option == 1) {
				cout << endl << "Playing the upsampled file." << endl;
				upSampleAudio(str);
			}
			else if (option == 2) {
				cout << endl << "Playing the downsampled file." << endl;
				downSampleAudio(str);
			}
			else if (option == 3) {
				cout << "enter the value of N: ";
				cin >> N;
				cout << endl << "Playing the average filtered file." << endl;
				movingAverageFilter(str, N);
			}
			else if (option == 4) {
				char str2[50] = "";
				cout << "Enter file name to merge, with (.wav) or exit: ";
				cin >> str2;
				int size1 = 100000000;
				unsigned char* arr1 = new unsigned char[size1];
				int size2 = 100000000000, samplerate1, samplerate2;
				unsigned char* arr2 = new unsigned char[size2];
				readWavFile(str, arr1, size1, samplerate1);
				char wavfile1[20] = "file1.wav";
				readWavFile(str2, arr2, size2, samplerate2);
				char wavfile2[20] = "file2.wav";
				unsigned char* merge = new unsigned char[size1 + size2];
				mergearray(arr1, size1, arr2, size2, merge);
				writeWavFile(wavfile1, merge, (size1+size2), samplerate1);
				cout << "playing merged wav file with file 1 sample rate: ";
				playfile(wavfile1);
				writeWavFile(wavfile2, merge, (size2+size1), samplerate2);
				cout << "playing merged wav file with file 2 sample rate: ";
				playfile(wavfile2);
			}
			cout << endl << "MENU: " << endl;
			cout << "Enter a number for: " << endl;
			cout << "1. To Upsample the Audio file. " << endl;
			cout << "2. To downsample the Audio file. " << endl;
			cout << "3. For moving average filter. " << endl;
			cout << "4. To merge the Audio files. " << endl;
			cout << "0. To exit. " << endl;
			cin >> option;
		}
	}
	
	
	return 0;
}