#include <iostream>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <mutex>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <sys/wait.h>
#include <ctime>

using namespace std;
std::mutex key;

void download(string addr, ofstream& log)
{
	stringstream path;
	path << "./script.sh " << addr;
	system(path.str().c_str());
	key.lock();
	time_t now = time(0);
	tm* ltime = localtime(&now);
	file << "\nName:\t" << addr <<endl;
	file <<"ID:\t"<< this_thread::get_id() << endl;
	file << "Time:\t" <<ltime->tm_hour << ":";
	file <<ltime->tm_min << ":";
	file <<ltime->tm_sec << endl;
	key.unlock();
}

int main()
{
	std::ofstream log("info");
	int n;
	cout << "Input the number of pictures to download:\n";
	cin >> n;
	vector<string> addresses(n);
	vector<thread> threads(n);
	for (int i = 0; i < n; i++)
	{
		cin >> addresses[i];
		threads[i] = thread(download, addresses[i], ref(log));
	}
	for (int i = 0; i < n; i++)
	{
		threads[i].join();
	}
	file.close();
	return 0;
}