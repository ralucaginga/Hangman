class Hangman
{
	//atribute
private:
	char* cuvant;
	int* ghicit;
	int nrErori = 0;
	const int maxErori = 7;
	int litere[26];
	

	//metode
public:
	Hangman();
	void startJoc();
	~Hangman();
private:
	void generareCuvant(int);
	void scrieCuvant();
	void scrieLitereIntroduse();
	int stopJoc();
	int testLit(char);
};