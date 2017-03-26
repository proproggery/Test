#include"stdio.h" 
#include<fstream> 
#include<iostream> 
#include<string> 
#include<cstring>
#include<stdlib.h>

using namespace std;

struct Komanda
{
	string name;
	int points;

};

int perevod1(string);
int perevod2(int, int);
void vvod(ifstream&, Komanda*, int);
int point(string);
void sort1(Komanda*, int);
void sort2(Komanda&, Komanda&);
void vyvod(ofstream&, Komanda*, int);


int main()
{
	ifstream fin("premier_league.csv");
	ofstream fout("results.csv");

	string s;
	getline(fin, s, '\n');
	int n = perevod1(s);

	Komanda *team;
	team = new Komanda[n];

	vvod(fin, team, n);
	sort1(team, n);
	vyvod(fout, team, n);

	delete[] team;

	return 0;
}

int perevod1(string s)
{
	int b = 0;
	for (int i = s.length() - 1; i >= 0; --i)
	{
		b += int(s[i] - 48) * perevod2(10, s.length() - 1 - i);
	}
	return b;
}


int perevod2(int a, int x)
{
	int b = 1;
	for (int i = 0; i < x; ++i)
	{
		b *= a;
	}
	return b;
}

void vvod(ifstream& fin, Komanda* tima, int amount)
{
	string s;

	for (int i = 0; i < amount; ++i)
	{

		getline(fin, s, ',');
		tima[i].name = s;
		tima[i].points = 0;
		for (int j = 0; j < 9; ++j)
		{

			getline(fin, s, ',');
			tima[i].points += point(s);
		}

		getline(fin, s, '\n');
		tima[i].points += point(s);
	}
}

int point(string result)
{
	//search colon (':')
	int d = 0;
	for (int i = 0; i < result.length(); ++i)
	{
		if (result[i] == ':')
		{
			d = i;
			break;
		}
	}
	int scoredgoals = 0,
		missedgoals = 0;
	for (int i = d - 1; i >= 0; --i)
	{
		scoredgoals += int(result[i] - 48);
	}
	for (int i = result.length() - 1; i > d; --i)
	{
		missedgoals += int(result[i] - 48);
	}

	if (scoredgoals > missedgoals)
	{
		return 3;
	}
	else if (scoredgoals == missedgoals)
	{
		return 1;
	}
	else {
		return 0;
	}
}

void sort1(Komanda* tima, int amount)
{
	for (int i = 0; i < amount - 1; ++i)
	{
		for (int j = 0; j < amount - 1 - i; ++j)
		{
			if (tima[j].points < tima[j + 1].points)
			{
				sort2(tima[j], tima[j + 1]);
			}
		}
	}
}

void sort2(Komanda& team1, Komanda& team2)
{
	Komanda temp = team1;
	team1 = team2;
	team2 = temp;
}

void vyvod(ofstream& fout, Komanda* tima, int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		fout << tima[i].name << ' ' << tima[i].points << endl;
	}
}