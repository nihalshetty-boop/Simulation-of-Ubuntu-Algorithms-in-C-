#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
using namespace std;
//-----------------------------------------------------------------Dhruv Patel---------------------------------------------------------------------------------------//
struct process{
    char process_id[50];
    int burst_time;
    int arrival_time;
    int wait_time;
    float response_ratio=0;
}a[50];
void read(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        cout<<"Enter the Process Name, Arrival Time and Burst Time for Process "<<i+1<<": ";
        cin>>a[i].process_id;
        cin>>a[i].arrival_time;
        cin>>a[i].burst_time;
        a[i].response_ratio=0;
        a[i].wait_time=-a[i].arrival_time;
    }
}
bool btimeSort(process a,process b)
{
    return a.burst_time<b.burst_time;
}
bool atimeSort(process a,process b)
{
    return a.arrival_time<b.arrival_time;
}
bool rrtimeSort(process a,process b)
{
    return a.response_ratio>b.response_ratio;
}
void display(int n)
{
    sort(a,a+n,btimeSort);
    sort(a,a+n,atimeSort);
    int ttime=0,i;
    int j,completion_time[n];
    for(i=0;i<n;i++)
        {
           j=i;
           while(a[j].arrival_time<=ttime&&j!=n)
           {
               j++;
           }
           for(int q = i;q<j;q++)
              {
                 a[q].wait_time=ttime-a[q].arrival_time;
                 a[q].response_ratio=(float)(a[q].wait_time+a[q].burst_time)/(float)a[q].burst_time;
              }
           sort(a+i,a+j,rrtimeSort);
           completion_time[i]=ttime;
           cout<<endl;
           ttime+=a[i].burst_time;
        }
    completion_time[i] = ttime;
    float averageWaitingTime=0;
    float averageResponseTime=0;
    float averageTAT=0;
    cout<<"\n";
    cout<<"P.Name  AT\tBT\tCT\tTAT\tWT\tRT\n";

    for (i=0; i<n; i++)
    {
        cout<<'P'<< a[i].process_id << "\t";
        cout<< a[i].arrival_time << "\t";
        cout<< a[i].burst_time << "\t";
        cout<< completion_time[i+1] << "\t";
        cout<< completion_time[i]-a[i].arrival_time+a[i].burst_time << "\t";
        averageTAT+=completion_time[i]-a[i].arrival_time+a[i].burst_time;
        cout<< a[i].wait_time << "\t";
        averageWaitingTime+=completion_time[i]-a[i].arrival_time;
        cout<< completion_time[i]-a[i].arrival_time << "\t";
        averageResponseTime+=completion_time[i]-a[i].arrival_time;
        cout<<"\n";
    }
    cout<<"\n";
    cout<<"\nGantt Chart\n";
    for (i=0; i<n; i++){
        cout <<"|  P"<< a[i].process_id << "   ";
    }
    cout<<"\n";
    for (i=0; i<n+1; i++){
        cout << completion_time[i] << "\t";
    }
    cout<<"\n";
    cout<<"Average Response time: "<<(float)averageResponseTime/(float)n<<endl;
    cout<<"Average Waiting time: "<<(float)averageWaitingTime/(float)n<<endl;
    cout<<"Average TA time: "<<(float)averageTAT/(float)n<<endl;
}
//-----------------------------------------------------------------Ishaan Kangriwala---------------------------------------------------------------------------------------//
int total_tracks = 200;

void CLOOK(int arr[], int head, int size)
{
	int total_headmovement = 0, distance, current_track;
	vector<int> left, right;
	vector<int> seek_sequence;

	for (int i=0; i<size; i++)
    {
		if(arr[i]<head)
        {
            left.push_back(arr[i]);
        }

		if (arr[i]>head)
        {
            right.push_back(arr[i]);
        }

	}


	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());


	for (int i=0; i<right.size(); i++)
    {
		current_track = right[i];
		seek_sequence.push_back(current_track);
		distance = abs(current_track - head);
		total_headmovement += distance;
		head = current_track;
	}

	total_headmovement += abs(head - left[0]);
	head = left[0];

	for (int i = 0; i < left.size(); i++)
    {
		current_track = left[i];
		seek_sequence.push_back(current_track);
		distance = abs(current_track - head);
		total_headmovement += distance;
		head = current_track;
	}

	cout<<"Total Head Movement = "<<total_headmovement<<endl;
	cout<<"The Seek Sequence is"<<endl;

	for (int i = 0; i<seek_sequence.size(); i++)
    {
		cout<<seek_sequence[i]<< endl;
	}
}
//-----------------------------------------------------------------Paarth Kapasi---------------------------------------------------------------------------------------//
int size;
vector<pair<int, int>> free_list[100000];
map<int, int> mp;

void initialize(int max_size)
{
	int n= ceil(log(max_size) / log(2));
	size= n+1;

	for(int i = 0; i <= n; i++)
    {
		free_list[i].clear();
    }
	free_list[n].push_back(make_pair(0, max_size-1));
}

void allocate(int max_size)
{
	int n= ceil(log(max_size)/log(2));


	if (free_list[n].size()>0)
	{
		pair<int, int> temp= free_list[n][0];

		free_list[n].erase(free_list[n].begin());
		cout<<"Memory from "<<temp.first<<" to "<<temp.second<<" allocated"<< "\n";

		mp[temp.first] = temp.second-temp.first+1;
	}
	else
	{
		int i;
		for(i= n+1; i<size; i++)
		{

			if(free_list[i].size() != 0)
				break;
		}

		if(i==size)
		{
			cout<<"Sorry, failed to allocate memory \n";
		}

		else
		{
			pair<int, int> temp;
			temp = free_list[i][0];


			free_list[i].erase(free_list[i].begin());
			i--;

			for(; i >= n; i--)
			{


				pair<int, int> pair1, pair2;
				pair1 = make_pair(temp.first, temp.first + (temp.second - temp.first) / 2);

				pair2 = make_pair(temp.first + (temp.second - temp.first + 1) / 2, temp.second);

				free_list[i].push_back(pair1);


				free_list[i].push_back(pair2);
				temp = free_list[i][0];


				free_list[i].erase(free_list[i].begin());
			}
			cout << "Memory from " << temp.first<< " to " << temp.second<< " allocated" << "\n";

			mp[temp.first] = temp.second - temp.first + 1;
		}
	}
}

void deallocate(int id)
{

    if(mp.find(id)==mp.end())
    {
        cout<<"Sorry, invalid free request\n";
        return;
    }

    int n=ceil(log(mp[id])/log(2));
    int i, buddyNumber, buddyAddress;

    free_list[n].push_back(make_pair(id, id+pow(2, n)-1));
    cout<<"Memory block from"<<id
         <<"to"<<id+pow(2, n)-1
         <<" freed\n";

    buddyNumber=id/mp[id];

    if (buddyNumber % 2 != 0)
    {
            buddyAddress = id - pow(2, n);
    }
    else
    {
            buddyAddress = id + pow(2, n);
    }

    for(i=0; i<free_list[n].size(); i++)
    {

        if(free_list[n][i].first==buddyAddress)
        {

            if(buddyNumber%2==0)
            {
                free_list[n + 1].push_back(make_pair(id, id + 2 * (pow(2, n) - 1)));

                cout<<"Coalescing of blocks starting at"<<id<<" and "<<buddyAddress<<" was done"<<"\n";
            }
            else
            {
                free_list[n + 1].push_back(make_pair(buddyAddress, buddyAddress + 2 * (pow(2, n))));

                cout<<"Coalescing of blocks starting at "<< buddyAddress <<" and "<<id <<" was done" <<"\n";
            }
            free_list[n].erase(free_list[n].begin() + i);
            free_list[n].erase(free_list[n].begin() +
            free_list[n].size() - 1);
            break;
        }
    }
    mp.erase(id);
}
//-----------------------------------------------------------------Nihal Shetty---------------------------------------------------------------------------------------//
string hexatobinary(string s)
{

	unordered_map<char, string> mp;
	mp['0'] = "0000";
	mp['1'] = "0001";
	mp['2'] = "0010";
	mp['3'] = "0011";
	mp['4'] = "0100";
	mp['5'] = "0101";
	mp['6'] = "0110";
	mp['7'] = "0111";
	mp['8'] = "1000";
	mp['9'] = "1001";
	mp['A'] = "1010";
	mp['B'] = "1011";
	mp['C'] = "1100";
	mp['D'] = "1101";
	mp['E'] = "1110";
	mp['F'] = "1111";
	string bin = "";
	for (int i = 0; i < s.size(); i++)
    {
		bin += mp[s[i]];
	}
	return bin;
}
string binarytohexa(string s)
{

	unordered_map<string, string> mp;
	mp["0000"] = "0";
	mp["0001"] = "1";
	mp["0010"] = "2";
	mp["0011"] = "3";
	mp["0100"] = "4";
	mp["0101"] = "5";
	mp["0110"] = "6";
	mp["0111"] = "7";
	mp["1000"] = "8";
	mp["1001"] = "9";
	mp["1010"] = "A";
	mp["1011"] = "B";
	mp["1100"] = "C";
	mp["1101"] = "D";
	mp["1110"] = "E";
	mp["1111"] = "F";
	string hex = "";
	for (int i = 0; i < s.length(); i += 4) {
		string ch = "";
		ch += s[i];
		ch += s[i + 1];
		ch += s[i + 2];
		ch += s[i + 3];
		hex += mp[ch];
	}
	return hex;
}

string permutation(string k, int* arr, int n)
{
	string permute = "";
	for (int i = 0; i < n; i++)
    {
		permute += k[arr[i] - 1];
	}
	return permute;
}

string left_shift(string k, int shifts)
{
	string s = "";
	for (int i=0; i<shifts; i++)
    {
		for (int j=1; j<28; j++)
		{
			s+=k[j];
		}
		s+= k[0];
		k= s;
		s= "";
	}
	return k;
}

string exor(string a, string b)
{
	string ans = "";
	for (int i=0; i<a.size(); i++)
    {
		if (a[i] == b[i])
		{
			ans+="0";
		}
		else
		{
			ans+="1";
		}
	}
	return ans;
}
string encryption(string plaintext, vector<string> RoundKey_binary, vector<string> roundkeys)
{

	plaintext= hexatobinary(plaintext);


	int initial_permutation[64]= { 58, 50, 42, 34, 26, 18, 10, 2,
							60, 52, 44, 36, 28, 20, 12, 4,
							62, 54, 46, 38, 30, 22, 14, 6,
							64, 56, 48, 40, 32, 24, 16, 8,
							57, 49, 41, 33, 25, 17, 9, 1,
							59, 51, 43, 35, 27, 19, 11, 3,
							61, 53, 45, 37, 29, 21, 13, 5,
							63, 55, 47, 39, 31, 23, 15, 7 };

	plaintext= permutation(plaintext, initial_permutation, 64);
	cout << "After initial permutation: " << binarytohexa(plaintext) << endl;


	string left= plaintext.substr(0, 32);
	string right= plaintext.substr(32, 32);
	cout<<"After splitting: L0="<<binarytohexa(left)<<" R0="<<binarytohexa(right)<<endl;

	int expansion_dbox[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
					6, 7, 8, 9, 8, 9, 10, 11,
					12, 13, 12, 13, 14, 15, 16, 17,
					16, 17, 18, 19, 20, 21, 20, 21,
					22, 23, 24, 25, 24, 25, 26, 27,
					28, 29, 28, 29, 30, 31, 32, 1 };


	int sbox[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
						{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

						{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
						{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
						{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
						{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
						{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
						{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };


	int permute[32] = { 16, 7, 20, 21,
					29, 12, 28, 17,
					1, 15, 23, 26,
					5, 18, 31, 10,
					2, 8, 24, 14,
					32, 27, 3, 9,
					19, 13, 30, 6,
					22, 11, 4, 25 };

	cout << endl;
	for (int i=0; i<16; i++)
        {

            string right_expanded= permutation(right, expansion_dbox, 48);


            string x= exor(RoundKey_binary[i], right_expanded);


            string op= "";
            for (int i= 0; i<8; i++)
                {
                    int row= 2*int(x[i*6]-'0')+int(x[i*6+5]-'0');
                    int col= 8*int(x[i*6+1]-'0')+4*int(x[i*6+2]-'0')+2*int(x[i*6+3]-'0')+int(x[i*6+4]-'0');
                    int val= sbox[i][row][col];
                    op+= char(val/8+'0');
                    val= val% 8;
                    op+= char(val/4+'0');
                    val= val% 4;
                    op+= char(val/2+'0');
                    val= val% 2;
                    op+= char(val+'0');
                }

            op= permutation(op, permute, 32);
            x= exor(op, left);

            left= x;

            if(i!= 15)
            {
                swap(left, right);
            }
            cout<<"Round "<<i + 1<<" "<< binarytohexa(left) <<" "<<binarytohexa(right)<<" "<<roundkeys[i]<<endl;
        }

	string combine =left + right;

	int final_permutation[64] ={ 40, 8, 48, 16, 56, 24, 64, 32,
                        39, 7, 47, 15, 55, 23, 63, 31,
						38, 6, 46, 14, 54, 22, 62, 30,
						37, 5, 45, 13, 53, 21, 61, 29,
						36, 4, 44, 12, 52, 20, 60, 28,
						35, 3, 43, 11, 51, 19, 59, 27,
						34, 2, 42, 10, 50, 18, 58, 26,
						33, 1, 41, 9, 49, 17, 57, 25 };

	string ciphertext = binarytohexa(permutation(combine, final_permutation, 64));
	return ciphertext;
}
//-----------------------------------------------------------------Main Function---------------------------------------------------------------------------------------//
int main()
{
    int c;
    do
    {
        cout<<"\nEnter your choice:\n1.Process Management: HRRN Algorithm\n2.I/O Management: C-LOOK Algorithm\n3.Memory Management: Buddy Memory Allocation\n4.File Management: Data Encryption Standard Algorithm\n";
        cin>>c;


        switch(c)
        {
           case 1:
               {
               int nop,choice,i;
               cout<<"Enter number of processes: ";
               cin>>nop;
               read(nop);
               display(nop);
               break;
               }
           case 2:
               {
               int arr[100], head, size;

               cout<<"Enter the number of elements in the seek sequence: ";
               cin>>size;

               cout<<"Enter the request sequence: ";
               for(int i=0;i<size;i++)
                   cin>>arr[i];

               cout<<"Enter the current head position: ";
               cin>>head;

               CLOOK(arr, head, size);
               break;
               }

           case 3:
               {
                    int total,c,req;
                    char ch='Y';
                    cout<<"Enter Total Memory Size (in Bytes) => ";
                    cin>>total;
                    initialize(total);
                    label:
                    do
                    {
                        cout<<"\n1. Add Process into Memory\n2. Remove Process \n3. Exit\n=> ";
                        cin>>c;
                        switch(c)
                        {
                            case 1:
                            {
                                cout<<"Enter Process Size (in Bytes) => ";
                                cin>>req;
                                cout<<"\n===>";
                                if(req >= 0)
                                {
                                    allocate(req);
                                }
                                else
                                {
                                    cout<<"Enter positive value for allocation"<<endl;
                                }
                                break;
                            }

                            case 2:
                            {
                                cout<<"Enter Starting Address => ";
                                cin>>req;
                                cout<<"\n===>";
                                deallocate(req);
                                break;
                            }

                            case 3:
                            {
                                cout<<"Do you wish to continue? Press N to exit";
                                cin>>ch;
                                if(ch=='N')
                                {
                                    break;
                                }
                            }
                        }

                    }while(ch!='N');
                    break;
               }
            case 4:
                {
                    string plaintext, key;
                    cout<<"Enter plaintext(in hexadecimal): ";
                    cin>>plaintext;
                    cout<<"Enter key(in hexadecimal): ";
                    cin>>key;

                    key = hexatobinary(key);

                   int keyp[56] = { 57, 49, 41, 33, 25, 17, 9,
                                    1, 58, 50, 42, 34, 26, 18,
                                    10, 2, 59, 51, 43, 35, 27,
                                    19, 11, 3, 60, 52, 44, 36,
                                    63, 55, 47, 39, 31, 23, 15,
                                    7, 62, 54, 46, 38, 30, 22,
                                    14, 6, 61, 53, 45, 37, 29,
                                    21, 13, 5, 28, 20, 12, 4 };

                   key = permutation(key, keyp, 56);


                   int shift_table[16] = { 1, 1, 2, 2,
                                           2, 2, 2, 2,
                                           1, 2, 2, 2,
                                           2, 2, 2, 1 };

                   int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                                        3, 28, 15, 6, 21, 10,
                                        23, 19, 12, 4, 26, 8,
                                        16, 7, 27, 20, 13, 2,
                                        41, 52, 31, 37, 47, 55,
                                        30, 40, 51, 45, 33, 48,
                                        44, 49, 39, 56, 34, 53,
                                        46, 42, 50, 36, 29, 32 };


                   string left = key.substr(0, 28);
                   string right = key.substr(28, 28);

                   vector<string> RoundKey_binary;
                   vector<string> roundkeys;

                   for (int i = 0; i < 16; i++)
                    {
                       left = left_shift(left, shift_table[i]);
                       right = left_shift(right, shift_table[i]);

                       string combine = left + right;


                       string RoundKey = permutation(combine, key_comp, 48);

                       RoundKey_binary.push_back(RoundKey);
                       roundkeys.push_back(binarytohexa(RoundKey));
                    }

                   cout << "\nEncryption:\n\n";
                   string ciphertext = encryption(plaintext, RoundKey_binary, roundkeys);
                   cout << "\nCipher Text: " << ciphertext << endl;

                   cout << "\nDecryption\n\n";
                   reverse(RoundKey_binary.begin(), RoundKey_binary.end());
                   reverse(roundkeys.begin(), roundkeys.end());
                   string text = encryption(ciphertext, RoundKey_binary, roundkeys);
                   cout << "\nPlain Text: " << text << endl;
                   break;
                }

            default:
                cout<<"Enter a valid input";
                break;



        }
    }
    while(c!=5);
}
